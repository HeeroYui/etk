/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/UString.h>
#include <etk/unicode.h>
#include <etk/debug.h>

#undef __class__
#define __class__	"std::u32string"

etk::CCout& etk::operator <<(etk::CCout& _os, const std::string& _obj) {
	_os << _obj.c_str();
	return _os;
}

etk::CCout& etk::operator <<(etk::CCout& _os, const std::vector<std::string>& _obj) {
	_os << "{";
	for (int32_t iii=0; iii< _obj.size(); iii++) {
		if (iii>0) {
			_os << " ~ ";
		}
		_os << _obj[iii];
	}
	_os << "}";
	return _os;
}

etk::CCout& etk::operator <<(etk::CCout& _os, const std::u32string& _obj) {
	_os << to_u8string(_obj).c_str();
	return _os;
}

etk::CCout& etk::operator <<(etk::CCout& _os, const std::vector<std::u32string>& _obj) {
	_os << "{";
	for (int32_t iii=0; iii< _obj.size(); iii++) {
		if (iii>0) {
			_os << " ~ ";
		}
		_os << _obj[iii];
	}
	_os << "}";
	return _os;
}

std::string to_u8string(const std::u32string& _input) {
	std::string out;
	for (int32_t iii=0; iii<_input.size(); ++iii) {
		char output[10];
		etk::getUtf8(_input[iii], output);
		out += output;
	}
	return out;
}

std::u32string to_u32string(const std::string& _input) {
	return to_u32string(_input.c_str());
}
std::u32string to_u32string(const char* _input) {
	if (_input == NULL) {
		return U"";
	}
	std::u32string out;
	char tmpData[20];
	int64_t pos = 0;
	int64_t inputLen = strlen(_input);
	while (pos < inputLen) {
		int32_t lenMax = inputLen - pos;
		//4 case
		if (    1<=lenMax
		     && 0x00 == (_input[pos+0] & 0x80) ) {
			tmpData[0] = _input[pos+0];
			tmpData[1] = '\0';
			pos += 1;
		} else if (    2<=lenMax
		            && 0xC0 == (_input[pos+0] & 0xE0)
		            && 0x80 == (_input[pos+1] & 0xC0) ) {
			tmpData[0] = _input[pos+0];
			tmpData[1] = _input[pos+1];
			tmpData[2] = '\0';
			pos += 2;
		} else if (    3<=lenMax
		            && 0xE0 == (_input[pos+0] & 0xF0)
		            && 0x80 == (_input[pos+1] & 0xC0)
		            && 0x80 == (_input[pos+2] & 0xC0)) {
			tmpData[0] = _input[pos+0];
			tmpData[1] = _input[pos+1];
			tmpData[2] = _input[pos+2];
			tmpData[3] = '\0';
			pos += 3;
		} else if (    4<=lenMax
		            && 0xF0 == (_input[pos+0] & 0xF8)
		            && 0x80 == (_input[pos+1] & 0xC0)
		            && 0x80 == (_input[pos+2] & 0xC0)
		            && 0x80 == (_input[pos+3] & 0xC0)) {
			tmpData[0] = _input[pos+0];
			tmpData[1] = _input[pos+1];
			tmpData[2] = _input[pos+2];
			tmpData[3] = _input[pos+3];
			tmpData[4] = '\0';
			pos += 4;
		} else {
			tmpData[0] = '\0';
			pos += 1;
		}
		out += etk::setUtf8(tmpData);
	}
	return out;
}

// TODO :  Might remove this when it will be port on STL ...
std::u32string to_u32string(int _val) {
	return to_u32string(std::to_string(_val));
}

std::u32string to_u32string(long _val) {
	return to_u32string(std::to_string(_val));
}

std::u32string to_u32string(long long _val) {
	return to_u32string(std::to_string(_val));
}

std::u32string to_u32string(unsigned _val) {
	return to_u32string(std::to_string(_val));
}

std::u32string to_u32string(unsigned long _val) {
	return to_u32string(std::to_string(_val));
}

std::u32string to_u32string(unsigned long long _val) {
	return to_u32string(std::to_string(_val));
}

std::u32string to_u32string(float _val) {
	return to_u32string(std::to_string(_val));
}

std::u32string to_u32string(double _val) {
	return to_u32string(std::to_string(_val));
}

std::u32string to_u32string(long double _val) {
	return to_u32string(std::to_string(_val));
}

double stod(const std::u32string& _str, size_t* _idx) {
	std::string tmp = to_u8string(_str);
	return std::stod(tmp, _idx);
}

float stof(const std::u32string& _str, size_t* _idx) {
	std::string tmp = to_u8string(_str);
	return std::stof(tmp, _idx);
}

int stoi(const std::u32string& _str, size_t* _idx, int _base) {
	std::string tmp = to_u8string(_str);
	return std::stoi(tmp, _idx, _base);
}

long stol(const std::u32string& _str, size_t* _idx, int _base) {
	std::string tmp = to_u8string(_str);
	return std::stol(tmp, _idx, _base);
}

long double stold(const std::u32string& _str, size_t* _idx) {
	std::string tmp = to_u8string(_str);
	return std::stold(tmp, _idx);
}

long long stoll(const std::u32string& _str, size_t* _idx, int _base) {
	std::string tmp = to_u8string(_str);
	return std::stoll(tmp, _idx, _base);
}

unsigned long stoul(const std::u32string& _str, size_t* _idx, int _base) {
	std::string tmp = to_u8string(_str);
	return std::stoul(tmp, _idx, _base);
}

unsigned long long stoull(const std::u32string& _str, size_t* _idx, int _base) {
	std::string tmp = to_u8string(_str);
	return std::stoull(tmp, _idx, _base);
}

bool stobool(const std::u32string& _str) {
	if(    true == compare_no_case(_str, U"true")
	    || true == compare_no_case(_str, U"enable")
	    || true == compare_no_case(_str, U"yes")
	    || _str == U"1") {
		return true;
	}
	return false;
}

bool stobool(const std::string& _str) {
	if(    true == compare_no_case(_str, "true")
	    || true == compare_no_case(_str, "enable")
	    || true == compare_no_case(_str, "yes")
	    || _str == u8"1") {
		return true;
	}
	return false;
}

std::string std::to_string(bool _val) {
	if (_val == true) {
		return "true";
	}
	return "false";
}

std::u32string to_u32string(bool _val) {
	if (_val == true) {
		return U"true";
	}
	return U"false";
}

bool compare_no_case(const std::u32string& _obj, const std::u32string& _val) {
	if (_val.size() != _obj.size()) {
		return false;
	}
	for(size_t iii=0; iii<_val.size(); ++iii) {
		if (tolower(_val[iii]) != tolower(_obj[iii])) {
			return false;
		}
	}
	return true;
}

bool compare_no_case(const std::string& _obj, const std::string& _val) {
	if (_val.size() != _obj.size()) {
		return false;
	}
	for(size_t iii=0; iii<_val.size(); ++iii) {
		if (tolower(_val[iii]) != tolower(_obj[iii])) {
			return false;
		}
	}
	return true;
}

std::string to_lower(const std::string& _obj) {
	std::string out;
	for(size_t iii=0 ; iii<_obj.size() ; iii++) {
		out.push_back(tolower(_obj[iii]));
	}
	return out;
}
std::u32string to_lower(const std::u32string& _obj) {
	std::u32string out;
	for(size_t iii=0 ; iii<_obj.size() ; iii++) {
		out.push_back(tolower(_obj[iii]));
	}
	return out;
}

std::string to_upper(const std::string& _obj) {
	std::string out;
	for(size_t iii=0 ; iii<_obj.size() ; iii++) {
		out.push_back(toupper(_obj[iii]));
	}
	return out;
}

std::u32string to_upper(const std::u32string& _obj) {
	std::u32string out;
	for(size_t iii=0 ; iii<_obj.size() ; iii++) {
		out.push_back(toupper(_obj[iii]));
	}
	return out;
}

bool end_with(const std::string& _obj, const std::string& _val, bool _caseSensitive) {
	if (_val.size() == 0) {
		return false;
	}
	if (_val.size() > _obj.size()) {
		return false;
	}
	if (true == _caseSensitive) {
		for( int64_t iii=_val.size()-1, jjj=_obj.size()-1;
		     iii>=0 && jjj>=0;
		     iii--, jjj--) {
			if (_obj[jjj] != _val[iii]) {
				return false;
			}
		}
		return true;
	}
	for( int64_t iii=_val.size()-1, jjj=_obj.size()-1;
	     iii>=0 && jjj>=0;
	     iii--, jjj--) {
		if (tolower(_val[iii]) != tolower(_obj[jjj])) {
			return false;
		}
	}
	return true;
}

bool end_with(const std::u32string& _obj, const std::u32string& _val, bool _caseSensitive) {
	if (_val.size() == 0) {
		return false;
	}
	if (_val.size() > _obj.size()) {
		return false;
	}
	if (true == _caseSensitive) {
		for( int64_t iii=_val.size()-1, jjj=_obj.size()-1;
		     iii>=0 && jjj>=0;
		     iii--, jjj--) {
			if (_obj[jjj] != _val[iii]) {
				return false;
			}
		}
		return true;
	}
	for( int64_t iii=_val.size()-1, jjj=_obj.size()-1;
	     iii>=0 && jjj>=0;
	     iii--, jjj--) {
		if (tolower(_val[iii]) != tolower(_obj[jjj])) {
			return false;
		}
	}
	return true;
}

bool start_with(const std::string& _obj, const std::string& _val, bool _caseSensitive) {
	if (_val.size() == 0) {
		return false;
	}
	if (_val.size() > _obj.size()) {
		return false;
	}
	if (true == _caseSensitive) {
		for( size_t iii = 0;
		     iii < _val.size();
		     iii++) {
			if (_obj[iii] != _val[iii]) {
				return false;
			}
		}
		return true;
	}
	for( size_t iii = 0;
	     iii < _val.size();
	     iii++) {
		if (tolower(_val[iii]) != tolower(_obj[iii])) {
			return false;
		}
	}
	return true;
}

bool start_with(const std::u32string& _obj, const std::u32string& _val, bool _caseSensitive) {
	if (_val.size() == 0) {
		return false;
	}
	if (_val.size() > _obj.size()) {
		return false;
	}
	if (true == _caseSensitive) {
		for( size_t iii = 0;
		     iii < _val.size();
		     iii++) {
			if (_obj[iii] != _val[iii]) {
				return false;
			}
		}
		return true;
	}
	for( size_t iii = 0;
	     iii < _val.size();
	     iii++) {
		if (tolower(_val[iii]) != tolower(_obj[iii])) {
			return false;
		}
	}
	return true;
}

std::u32string replace(const std::u32string& _obj, char32_t _val, char32_t _replace) {
	std::u32string copy(_obj);
	for( size_t iii = 0;
	     iii < copy.size();
	     iii++) {
		if (copy[iii] == _val) {
			copy[iii] = _replace;
		}
	}
	return copy;
}

std::string replace(const std::string& _obj, char _val, char _replace) {
	std::string copy(_obj);
	for( size_t iii = 0;
	     iii < copy.size();
	     iii++) {
		if (copy[iii] == _val) {
			copy[iii] = _replace;
		}
	}
	return copy;
}

std::string extract_line(const std::string& _obj, int32_t _pos) {
	// search back : '\n'
	size_t startPos = _obj.rfind('\n', _pos);
	if (startPos == _pos) {
		startPos = 0;
	} else {
		startPos++;
	}
	// search forward : '\n'
	size_t stopPos = _pos;
	if (_obj[_pos] != '\n') {
		stopPos = _obj.find('\n', _pos);
		if (stopPos == _pos) {
			stopPos = _obj.size();
		}
	}
	if (startPos == std::string::npos) {
		startPos = 0;
	} else if (startPos >= _obj.size() ) {
		return "";
	}
	if (stopPos == std::string::npos) {
		return "";
	} else if (stopPos >= _obj.size() ) {
		stopPos = _obj.size();
	}
	return std::string(_obj, startPos, stopPos - startPos);
}

std::u32string extract_line(const std::u32string& _obj, int32_t _pos) {
	// search back : '\n'
	size_t startPos = _obj.rfind('\n', _pos);
	if (startPos == _pos) {
		startPos = 0;
	} else {
		startPos++;
	}
	// search forward : '\n'
	size_t stopPos = _pos;
	if (_obj[_pos] != '\n') {
		stopPos = _obj.find('\n', _pos);
		if (stopPos == _pos) {
			stopPos = _obj.size();
		}
	}
	if (startPos == std::string::npos) {
		startPos = 0;
	} else if (startPos >= _obj.size() ) {
		return U"";
	}
	if (stopPos == std::string::npos) {
		return U"";
	} else if (stopPos >= _obj.size() ) {
		stopPos = _obj.size();
	}
	return std::u32string(_obj, startPos, stopPos - startPos);
}

std::vector<std::string> string_split(const std::string& _input, char _val) {
	std::vector<std::string> list;
	size_t lastStartPos = 0;
	for(size_t iii=0; iii<_input.size(); iii++) {
		if (_input[iii]==_val) {
			list.push_back(std::string(_input, lastStartPos, iii - lastStartPos));
			lastStartPos = iii+1;
		}
	}
	if (lastStartPos<_input.size()) {
		list.push_back(std::string(_input, lastStartPos));
	}
	return list;
}

#ifdef __TARGET_OS__Android
double std::stod(const std::string& _str, size_t* _idx) {
	double ret = 0;
	sscanf(_str.c_str(), "%lf", &ret);
	return ret;
}

float std::stof(const std::string& _str, size_t* _idx) {
	float ret = 0;
	sscanf(_str.c_str(), "%f", &ret);
	return ret;
}

int std::stoi(const std::string& _str, size_t* _idx, int _base) {
	int ret = 0;
	sscanf(_str.c_str(), "%d", &ret);
	return ret;
}

long std::stol(const std::string& _str, size_t* _idx, int _base) {
	long ret = 0;
	sscanf(_str.c_str(), "%ld", &ret);
	return ret;
}

long double std::stold(const std::string& _str, size_t* _idx) {
	long double ret = 0;
	sscanf(_str.c_str(), "%llf", &ret);
	return ret;
}

long long std::stoll(const std::string& _str, size_t* _idx, int _base) {
	long long ret = 0;
	sscanf(_str.c_str(), "%lld", &ret);
	return ret;
}

unsigned long std::stoul(const std::string& _str, size_t* _idx, int _base) {
	unsigned long ret = 0;
	sscanf(_str.c_str(), "%lu", &ret);
	return ret;
}

unsigned long long std::stoull(const std::string& _str, size_t* _idx, int _base) {
	unsigned long long ret = 0;
	sscanf(_str.c_str(), "%llu", &ret);
	return ret;
}
#endif