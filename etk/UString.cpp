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

std::string to_u8string(const std::u32string& _obj) {
	std::vector<char32_t> tmpp;
	for (size_t iii=0; iii<_obj.size(); ++iii) {
		tmpp.push_back(_obj[iii]);
	}
	std::vector<char> output_UTF8;
	unicode::convertUnicodeToUtf8(tmpp, output_UTF8);
	output_UTF8.push_back('\0');
	std::string out = &output_UTF8[0];
	return out;
}

std::u32string to_u32string(const std::string& _obj) {
	// TODO : Change this ...
	std::vector<char> transformData;
	for ( size_t iii=0; iii< _obj.size(); ++iii) {
		transformData.push_back(_obj[iii]);
	}
	std::vector<char32_t> output_Unicode;
	unicode::convertUtf8ToUnicode(transformData, output_Unicode);
	if(    0 == output_Unicode.size()
	    || output_Unicode[output_Unicode.size()-1] != 0) {
		return U"";
	}
	std::u32string out;
	for ( size_t iii=0; iii< output_Unicode.size(); ++iii) {
		transformData.push_back((char32_t)output_Unicode[iii]);
	}
	return out;
}
std::u32string to_u32string(const char* _obj) {
	if (_obj == NULL) {
		return U"";
	}
	int64_t len = strlen(_obj);
	// TODO : Change this ...
	std::vector<char> transformData;
	for ( size_t iii=0; iii < len; ++iii) {
		transformData.push_back(_obj[iii]);
	}
	std::vector<char32_t> output_Unicode;
	unicode::convertUtf8ToUnicode(transformData, output_Unicode);
	if(    0 == output_Unicode.size()
	    || output_Unicode[output_Unicode.size()-1] != 0) {
		return U"";
	}
	std::u32string out;
	for ( size_t iii=0; iii< output_Unicode.size(); ++iii) {
		transformData.push_back((char32_t)output_Unicode[iii]);
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
	return std::string(_obj, startPos, stopPos);
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
	return std::u32string(_obj, startPos, stopPos);
}

std::vector<std::string> string_split(const std::string& _input, char _val) {
	std::vector<std::string> list;
	size_t lastStartPos = 0;
	for(size_t iii=0; iii<_input.size(); iii++) {
		if (_input[iii]==_val) {
			list.push_back(std::string(_input, lastStartPos, iii));
			lastStartPos = iii+1;
		}
	}
	if (lastStartPos<_input.size()) {
		list.push_back(std::string(_input, lastStartPos));
	}
	return list;
}

#if 0


int32_t strlen(const char32_t * _data) {
	if (NULL == _data) {
		return 0;
	}
	int32_t iii=0;
	while (*_data != 0) {
		_data++;
		iii++;
		if (iii > 0x7FFFFFF0) {
			return iii;
		}
	}
	return iii;
}

#undef __class__
#define __class__	"std::string"

etk::CCout& etk::operator <<(etk::CCout& _os, const std::string& _obj) {
	std::vector<char> output_UTF8;
	unicode::convertUnicodeToUtf8(_obj.m_data, output_UTF8);
	output_UTF8.push_back('\0');
	_os << &output_UTF8[0];
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

std::string::UString(void)
{
	//TK_INFO("new std::string()");
	m_data.push_back(char32_t::Null);
}


std::string::UString(const char* _data, enum unicode::charset _inputCharset) {
	// TODO : Change this ...
	std::vector<char> transformData;
	while (*_data != '\0') {
		transformData.push_back(*_data);
		_data++;
	}
	m_data.clear();
	if (unicode::charsetUTF8 == _inputCharset) {
		unicode::convertUtf8ToUnicode(transformData, m_data);
	} else {
		unicode::convertIsoToUnicode(_inputCharset, transformData, m_data);
	}
	if(    0 == m_data.size()
	    || m_data[m_data.size()-1]!=char32_t::Null) {
		m_data.push_back(char32_t::Null);
	}
}


// single element adding
std::string::UString(const bool _inputData, enum std::string::printMode _mode, bool _preset) {
	m_data.clear();
	if (_preset==true) {
		switch(_mode) {
			case std::string::printModeBinary :
				m_data.push_back('0');
				m_data.push_back('b');
				break;
			case std::string::printModeOctal :
				m_data.push_back('0');
				m_data.push_back('o');
				break;
			case std::string::printModeDecimal :
				break;
			case std::string::printModeHexadecimal :
				m_data.push_back('0');
				m_data.push_back('x');
				break;
			default:
			case std::string::printModeString :
				break;
		}
	}
	switch(_mode) {
		case std::string::printModeBinary :
		case std::string::printModeOctal :
		case std::string::printModeDecimal :
		case std::string::printModeHexadecimal :
			if (true == _inputData) {
				m_data.push_back('1');
			} else {
				m_data.push_back('0');
			}
			break;
		default:
		case std::string::printModeString :
			if (true == _inputData) {
				m_data.push_back('t');
				m_data.push_back('r');
				m_data.push_back('u');
				m_data.push_back('e');
			} else {
				m_data.push_back('f');
				m_data.push_back('a');
				m_data.push_back('l');
				m_data.push_back('s');
				m_data.push_back('e');
			}
			break;
	}
	m_data.push_back(char32_t::Null);
}

std::string::UString(const std::string& _obj)
{
	//etk_INFO("Constructeur de recopie");
	m_data = _obj.m_data;
}

std::string::UString(char32_t _inputData)
{
	m_data.push_back(_inputData);
	m_data.push_back(char32_t::Null);
}

std::string::UString(const float _inputData)
{
	// TODO : Rework this ...
	char tmpVal[256];
	// generate the UString : 
	sprintf(tmpVal, "%f", _inputData);
	// set the internal data : 
	set(tmpVal);
}

std::string::UString(const double _inputData)
{
	// TODO : Rework this ...
	char tmpVal[256];
	// generate the UString : 
	sprintf(tmpVal, "%lf", _inputData);
	int32_t len=strlen(tmpVal);
	if (NULL!=strchr(tmpVal, '.')) {
		//have a '.'
		// remove the .000000000 at the end of the string
		for (int32_t iii=len-1; iii>=0 ; --iii) {
			if (tmpVal[iii] == '0') {
				tmpVal[iii] = '\0';
			} else {
				if (tmpVal[iii] == '.') {
					tmpVal[iii] = '\0';
				}
				break;
			}
		}
	}
	// set the internal data : 
	set(tmpVal);
}

// TODO : Does not work at all ...
/*
std::string std::string::WrapHidenChar(void) const
{
	std::string out;
	for (int32_t iii=0; iii<Size(); iii++) {
		if (m_data[iii]=='\r') {
			out += "\r";
		} else if (m_data[iii]=='\t') {
			out += "\t";
		} else {
			out += m_data[iii];
		}
	}
	return out;
}
*/


void std::string::setNumber(bool _negative, const uint64_t& _inputData, enum std::string::printMode _mode, bool _preset, int32_t _leadingZero)
{
	m_data.clear();
	if (true==_negative) {
		if (_mode == std::string::printModeString) {
			m_data.push_back('l');
			m_data.push_back('e');
			m_data.push_back('s');
			m_data.push_back('s');
			m_data.push_back(' ');
		} else {
			m_data.push_back('-');
		}
	}
	if (_preset==true) {
		switch(_mode) {
			case std::string::printModeBinary :
				m_data.push_back('0');
				m_data.push_back('b');
				break;
			case std::string::printModeOctal :
				m_data.push_back('0');
				m_data.push_back('o');
				break;
			case std::string::printModeDecimal :
				break;
			case std::string::printModeHexadecimal :
				m_data.push_back('0');
				m_data.push_back('x');
				break;
			default:
			case std::string::printModeString :
				break;
		}
	}
	if (_mode == std::string::printModeString) {
		m_data.push_back('T');
		m_data.push_back('O');
		m_data.push_back('D');
		m_data.push_back('O');
		m_data.push_back('.');
		m_data.push_back('.');
		m_data.push_back('.');
	} else {
		int32_t base=8;
		//char ploppp[256]="";
		switch(_mode) {
			case std::string::printModeBinary :
				base=2;
				break;
			case std::string::printModeOctal :
				//sprintf(ploppp, "%llo", _inputData);
				base=8;
				break;
			default:
			case std::string::printModeDecimal :
				//sprintf(ploppp, "%llu", _inputData);
				base=10;
				break;
			case std::string::printModeHexadecimal :
				//sprintf(ploppp, "%llx", _inputData);
				base=16;
				break;
		}
		//printf("lmkmlj %llX\n", _inputData);
		//printf("lmkmlk %s\n", ploppp);
		uint64_t tmpVal = _inputData;
		std::string tmpString;
		while (tmpVal>0) {
			uint64_t quotient = tmpVal / base;
			uint64_t rest = tmpVal - quotient*base;
			if (rest<=9) {
				tmpString.add(0,(char)(rest+'0'));
			} else {
				tmpString.add(0,(char)(rest-10+'A'));
			}
			tmpVal = quotient;
		}
		if (tmpString.size() == 0) {
			tmpString = "0";
		}
		for (int32_t iii=tmpString.size(); iii<_leadingZero; iii++){
			tmpString.add(0,'0');
		}
		*this += tmpString;
		
		//TK_ERROR ("        " << ploppp);
	}
	if (m_data.size()==0) {
		m_data.push_back(char32_t::Null);
	} else if (m_data[m_data.size()-1]!=char32_t::Null) {
		m_data.push_back(char32_t::Null);
	}
	//TK_ERROR(" convert : " << _inputData << " in : " << *this << " len=" << m_data.Size());
}

void std::string::set(const int64_t& _inputData, enum std::string::printMode _mode, bool _preset, int32_t _leadingZero)
{
	if (_preset==true && _mode != std::string::printModeString) {
		setNumber(false, (uint64_t)_inputData, _mode, _preset, _leadingZero);
		return;
	}
	if (_inputData < 0) {
		uint64_t tmpData = (uint64_t)((int64_t)_inputData * (int64_t)(-1));
		setNumber(true, (uint64_t)tmpData, _mode, _preset, _leadingZero);
	} else {
		setNumber(false, (uint64_t)_inputData, _mode, _preset, _leadingZero);
	}
}

void std::string::set(const uint64_t& _inputData, enum std::string::printMode _mode, bool _preset, int32_t _leadingZero)
{
	setNumber(false, (uint64_t)_inputData, _mode, _preset, _leadingZero);
}

// multiple element add
std::string::UString(const char32_t* _inputData, int32_t _len)
{
	set(_inputData, _len);
}

std::string::UString(const char* _inputData, int32_t _len)
{
	set(_inputData, _len);
}

std::string::UString(const std::vector<char>& _inputData)
{
	set(_inputData);
}

std::string::UString(const std::vector<int8_t>& _inputData)
{
	set(_inputData);
}

std::string::UString(const std::vector<char32_t>& _inputData)
{
	set(_inputData);
}


void std::string::set(const std::vector<char>& _inputData)
{
	if (_inputData.size()==0) {
		clear();
		return;
	}
	std::vector<char32_t> output_Unicode;
	unicode::convertUtf8ToUnicode(_inputData, output_Unicode);
	set(output_Unicode);
}

void std::string::set(const std::vector<int8_t>& _inputData)
{
	if (_inputData.size()==0) {
		clear();
		return;
	}
	std::vector<char32_t> output_Unicode;
	unicode::convertUtf8ToUnicode(_inputData, output_Unicode);
	set(output_Unicode);
}


void std::string::set(const std::vector<char32_t>& _inputData)
{
	m_data = _inputData;
	if (m_data.size()>0) {
		if (m_data[m_data.size()-1] != char32_t::Null) {
			m_data.push_back(char32_t::Null);
		}
	} else {
		m_data.push_back(char32_t::Null);
	}
	//TK_DEBUG("m_dataLen="<<m_dataLen << " m_dataLenUTF8="<<m_dataLenUTF8 << " description=" << m_data);
}

void std::string::set(const char* _inputData, int32_t _len)
{
	// clear all the data
	m_data.clear();
	if (NULL == _inputData) {
		m_data.push_back(char32_t::Null);
		// nothing to add ... ==> just exit
		return;
	}
	// overwrite the len if needed : 
	if ((-1) == _len) {
		_len = strlen(_inputData);
	}
	// convert the string
	std::vector<char> tmpChar;
	for (int32_t iii=0; iii<_len; iii++) {
		// clip the string in case of error of len ...
		if (_inputData[iii]=='\0') {
			break;
		}
		tmpChar.push_back(_inputData[iii]);
	}
	// add it ...
	if (_len != 0) {
		// copy the data ...
		unicode::convertUtf8ToUnicode(tmpChar, m_data);
	}
	if (m_data.size()==0) {
		m_data.push_back(char32_t::Null);
	} else if (m_data[m_data.size()-1]!=char32_t::Null) {
		m_data.push_back(char32_t::Null);
	}
}

void std::string::set(const char32_t* _inputData, int32_t _len)
{
	// clear all the data
	m_data.clear();
	if (NULL == _inputData) {
		m_data.push_back(char32_t::Null);
		// nothing to add ... ==> just exit
		return;
	}
	// overwrite the len if needed :
	if ((-1) == _len) {
		_len = strlen(_inputData);
	}
	if (_len != 0) {
		// copy the data ...
		m_data.push_back(_inputData, _len);
	}
	if (m_data.size()==0) {
		m_data.push_back(char32_t::Null);
	} else if (m_data[m_data.size()-1]!=char32_t::Null) {
		m_data.push_back(char32_t::Null);
	}
}


const std::string& std::string::operator= (const std::string& _obj )
{
	//TK_INFO("OPERATOR de recopie");
	if( this != &_obj ) {
		m_data = _obj.m_data;
	}
	return *this;
}


bool std::string::operator> (const std::string& _obj) const
{
	if( this != &_obj ) {
		for (int32_t iii=0; iii < m_data.size() && iii < _obj.m_data.size(); iii++) {
			//TK_DEBUG("    compare : '" << (char)m_data[iii] << "'>'" << (char)_obj.m_data[iii] << "' ==> " << changeOrder(m_data[iii]) << ">" << changeOrder(_obj.m_data[iii]) << "");
			char32_t elemA = m_data[iii].changeOrder();
			char32_t elemB = _obj.m_data[iii].changeOrder();
			if (elemA != elemB) {
				if (elemA > elemB) {
					return true;
				}
				return false;
			}
		}
		if (m_data.size() > _obj.m_data.size()) {
			return true;
		}
	}
	return false;
}

bool std::string::operator>= (const std::string& _obj) const
{
	if( this != &_obj ) {
		for (int32_t iii=0; iii < m_data.size() && iii < _obj.m_data.size(); iii++) {
			char32_t elemA = m_data[iii].changeOrder();
			char32_t elemB = _obj.m_data[iii].changeOrder();
			if (elemA != elemB) {
				if (elemA > elemB) {
					return true;
				}
				return false;
			}
		}
		if (m_data.size() >= _obj.m_data.size()) {
			return true;
		}
	}
	return false;
}

bool std::string::operator< (const std::string& _obj) const
{
	if( this != &_obj ) {
		for (int32_t iii=0; iii < m_data.size() && iii < _obj.m_data.size(); iii++) {
			char32_t elemA = m_data[iii].changeOrder();
			char32_t elemB = _obj.m_data[iii].changeOrder();
			if (elemA != elemB) {
				if (elemA < elemB) {
					return true;
				}
				return false;
			}
		}
		if (m_data.size() < _obj.m_data.size()) {
			return true;
		}
	}
	return false;
}

bool std::string::operator<= (const std::string& _obj) const
{
	if( this != &_obj ) {
		for (int32_t iii=0; iii < m_data.size() && iii < _obj.m_data.size(); iii++) {
			char32_t elemA = m_data[iii].changeOrder();
			char32_t elemB = _obj.m_data[iii].changeOrder();
			if (elemA != elemB) {
				if (elemA < elemB) {
					return true;
				}
				return false;
			}
		}
		if (m_data.size() <= _obj.m_data.size()) {
			return true;
		}
	}
	return false;
}


bool std::string::operator== (const std::string& _obj) const
{
	if( this != &_obj ) {
		if (_obj.m_data.size() != m_data.size()) {
			return false;
		}
		for (int32_t iii= 0; iii<m_data.size(); iii++) {
			if (_obj.m_data[iii]!= m_data[iii]){
				return false;
			}
		}
		return true;
	}
	return true;
}

bool std::string::compareNoCase(const std::string& _obj) const
{
	if( this != &_obj ) {
		if (_obj.m_data.size() != m_data.size()) {
			return false;
		}
		for (int32_t iii= 0; iii<m_data.size(); iii++) {
			if (false==m_data[iii].compareNoCase(_obj.m_data[iii])){
				return false;
			}
		}
		return true;
	}
	return true;
}


bool std::string::operator!= (const std::string& _obj) const
{
	return !(*this == _obj);
}

const std::string& std::string::operator+= (const std::string &_obj)
{
	if (0 < _obj.size()) {
		// remove the last '\0'
		m_data.popBack();
		// copy the data ...
		m_data += _obj.m_data;
		// This previous include the \0 in case of the 2 UString are different...
		if( this == &_obj ) {
			// add the removed end UString
			m_data.push_back(char32_t::Null);
		}
	}
	return *this;
}

std::string std::string::operator+ (const std::string &_obj) const
{
	std::string temp;
	temp += *this;
	temp += _obj;
	return temp;
}


bool std::string::isEmpty(void) const
{
	if(1 >= m_data.size() ) {
		return true;
	} else {
		return false;
	}
}


int32_t std::string::size(void) const
{
	if (m_data.size() == 0) {
		return 0;
	} else {
		return m_data.size() - 1;
	}
}


void std::string::add(int32_t _currentID, const char* _inputData)
{
	std::string tmpString(_inputData);
	add(_currentID, tmpString.pointer() );
}


void std::string::add(int32_t _currentID, const char32_t* _inputData)
{
	// get the input lenght
	int32_t len = strlen(_inputData);
	if (0 == len) {
		TK_WARNING("no data to add on the current UString");
		return;
	} else if (_currentID < 0) {
		TK_WARNING("Curent ID(" << _currentID << ") < 0   ==> Add at the start");
		_currentID = 0;
	} else if (_currentID > size() ) {
		TK_ERROR("Curent ID(" << _currentID << ") > maxSize ... (" << size() << ")  ==> add at the end ...");
		m_data.push_back(_inputData, len);
		return;
	}
	m_data.insert(_currentID, _inputData, len);
}


void std::string::add(int32_t _currentID, const char32_t _inputData)
{
	char32_t data[2];
	data[0] = _inputData;
	data[1] = char32_t::Null;
	add(_currentID, data);
}

void std::string::append(char32_t _inputData)
{
	m_data.popBack();
	m_data.push_back(_inputData);
	m_data.push_back(char32_t::Null);
}


void std::string::remove(int32_t _currentID, int32_t _len)
{
	if (0 >= _len) {
		TK_ERROR("no data to remove on the current UString");
		return;
	}
	// TODO : check the size of the data
	m_data.eraseLen(_currentID, _len);
}


void std::string::clear(void)
{
	m_data.clear();
	m_data.push_back(char32_t::Null);
}

int32_t std::string::findForward(const char32_t _element, int32_t _startPos) const
{
	if (_startPos < 0) {
		_startPos = 0;
	} else if (_startPos >= size() ) {
		return -1;
	}
	for (int32_t iii=_startPos; iii< size(); iii++) {
		if (m_data[iii] == _element) {
			return iii;
		}
	}
	return -1;
}

int32_t std::string::findBack(const char32_t _element, int32_t _startPos) const
{
	if (_startPos < 0) {
		return -1;
	} else if (_startPos >= size() ) {
		_startPos = size();
	}
	for (int32_t iii=_startPos; iii>=0; iii--) {
		if (m_data[iii] == _element) {
			return iii;
		}
	}
	return -1;
}


std::string std::string::extract(int32_t _posStart, int32_t _posEnd) const
{
	std::string out;
	if (_posStart < 0) {
		_posStart = 0;
	} else if (_posStart >= size() ) {
		return out;
	}
	if (_posEnd < 0) {
		return out;
	} else if (_posEnd >= size() ) {
		_posEnd = size();
	}
	out.m_data = m_data.extract(_posStart, _posEnd);
	out.m_data.push_back(char32_t::Null);
	return out;
}

std::string std::string::extractLine(int32_t _pos) const
{
	// search back : '\n'
	int32_t startPos = findBack('\n', _pos);
	if (startPos == _pos) {
		startPos = 0;
	} else {
		startPos++;
	}
	// search forward : '\n'
	int32_t stopPos = _pos;
	if (m_data[_pos] != '\n') {
		stopPos = findForward('\n', _pos);
		if (stopPos == _pos) {
			stopPos = size();
		}
	}
	std::string out;
	if (startPos < 0) {
		startPos = 0;
	} else if (startPos >= size() ) {
		return out;
	}
	if (stopPos < 0) {
		return out;
	} else if (stopPos >= size() ) {
		stopPos = size();
	}
	out.m_data = m_data.extract(startPos, stopPos);
	out.m_data.push_back(char32_t::Null);
	return out;
}

std::vector<char32_t> std::string::getVector(void)
{
	std::vector<char32_t> out = m_data;
	out.popBack();
	return out;
}


bool std::string::startWith(const std::string& _data, bool _caseSensitive) const
{
	if (_data.size() == 0) {
		return false;
	}
	if (_data.size() > size()) {
		return false;
	}
	if (true == _caseSensitive) {
		for (int32_t iii=0; iii<_data.size(); iii++) {
			if (_data[iii] != m_data[iii]) {
				return false;
			}
		}
	} else {
		for (int32_t iii=0; iii<_data.size(); iii++) {
			if (false==m_data[iii].compareNoCase(_data[iii])) {
				return false;
			}
		}
	}
	return true;
}


bool std::string::endWith(const std::string& _data, bool _caseSensitive) const
{
	if (_data.size() == 0) {
		return false;
	}
	if (_data.size() > size()) {
		return false;
	}
	if (true == _caseSensitive) {
		for( int32_t iii=size()-1, jjj=_data.size()-1;
		     iii>=0 && jjj>=0;
		     iii--, jjj--) {
			if (_data[jjj] != m_data[iii]) {
				return false;
			}
		}
	} else {
		for( int32_t iii=size()-1, jjj=_data.size()-1;
		     iii>=0 && jjj>=0;
		     iii--, jjj--) {
			if (false==m_data[iii].compareNoCase(_data[jjj])) {
				return false;
			}
		}
	}
	return true;
}


etk::Char std::string::c_str(void) const
{
	etk::Char tmpVar;
	std::vector<char> tmpData;
	// UTF8 generation :
	tmpData.clear();
	unicode::convertUnicodeToUtf8(m_data, tmpData);
	tmpVar.setValue(tmpData);
	return tmpVar;
}

std::vector<std::string> std::string::split(char32_t _val)
{
	std::vector<std::string> list;
	int32_t lastStartPos=0;
	for(int32_t iii=0; iii<size(); iii++) {
		if (m_data[iii]==_val) {
			list.push_back(extract(lastStartPos, iii));
			lastStartPos = iii+1;
		}
	}
	if (lastStartPos<size()) {
		list.push_back(extract(lastStartPos));
	}
	return list;
}


void std::string::replace(char32_t _out, char32_t _in)
{
	for(int32_t iii=0 ; iii<m_data.size() ; iii++) {
		if (m_data[iii]==_out) {
			m_data[iii]=_in;
		}
	}
}

void std::string::lower(void)
{
	for( int32_t iii=0 ; iii<m_data.size() ; iii++) {
		m_data[iii].lower();
	}
}

std::string std::string::toLower(void) const
{
	std::string ret = *this;
	ret.lower();
	return ret;
}

void std::string::upper(void)
{
	for( int32_t iii=0 ; iii<m_data.size() ; iii++) {
		m_data[iii].upper();
	}
}

std::string std::string::toUpper(void) const
{
	std::string ret = *this;
	ret.upper();
	return ret;
}

bool std::string::toBool(void) const
{
	if(    true == compareNoCase("true")
	    || true == compareNoCase("enable")
	    || true == compareNoCase("yes")
	    || *this == "1") {
		return true;
	}
	return false;
}

int64_t std::string::toInt64(void) const
{
	int64_t ret=0;
	bool isOdd = false;
	for (int32_t iii=0; iii<m_data.size(); iii++) {
		if(    iii==0
		    && (    m_data[iii] == '-'
		         || m_data[iii] == '+') ) {
			if(m_data[iii] == '-') {
				isOdd = true;
			}
		} else {
			if (true==m_data[iii].isInteger()) {
				int32_t val = m_data[iii].toInt32();
				ret = ret*10 + val;
			} else {
				break;
			}
		}
	}
	if (isOdd == true) {
		ret *= -1;
	}
	return ret;
}

uint64_t std::string::toUInt64(void) const
{
	uint64_t ret=0;
	for (int32_t iii=0; iii<m_data.size(); iii++) {
		if(    iii==0
		    && (    m_data[iii] == '-'
		         || m_data[iii] == '+') ) {
			if(m_data[iii] == '-') {
				return 0;
			}
		} else {
			if (true==m_data[iii].isInteger()) {
				int32_t val = m_data[iii].toInt32();
				ret = ret*10 + val;
			} else {
				break;
			}
		}
	}
	return ret;
}

int32_t std::string::toInt32(void) const
{
	int64_t parse = toInt64();
	return etk_avg((int64_t)INT32_MIN, parse, (int64_t)INT32_MAX);
}
int16_t std::string::toInt16(void) const
{
	int64_t parse = toInt64();
	return etk_avg((int64_t)INT16_MIN, parse, (int64_t)INT16_MAX);
}
int8_t std::string::toInt8(void) const
{
	int64_t parse = toInt64();
	return etk_avg((int64_t)INT8_MIN, parse, (int64_t)INT8_MAX);
}

uint32_t std::string::toUInt32(void) const
{
	uint64_t parse = toUInt64();
	return etk_avg((int64_t)0, parse, (int64_t)UINT32_MAX);
}
uint16_t std::string::toUInt16(void) const
{
	uint64_t parse = toUInt64();
	return etk_avg((int64_t)0, parse, (int64_t)UINT16_MAX);
}
uint8_t std::string::toUInt8(void) const
{
	uint64_t parse = toUInt64();
	return etk_avg((int64_t)0, parse, (int64_t)UINT8_MAX);
}

double std::string::toDouble(void) const
{
	double ret=0;
	bool isOdd = false;
	float dotPos = -1;
	for (int32_t iii=0; iii<m_data.size(); iii++) {
		if(    iii==0
		    && (    m_data[iii] == '-'
		         || m_data[iii] == '+') ) {
			if(m_data[iii] == '-') {
				isOdd = true;
			}
		} else {
			TK_VERBOSE( *this << " curent val " << m_data[iii] << "out=" << ret);
			if (dotPos == -1) {
				if (m_data[iii] == '.') {
					dotPos = 0.1;
					// jump at the next element
					continue;
				}
			}
			if (true==m_data[iii].isInteger()) {
				int32_t val = m_data[iii].toInt32();
				double val2 = val;
				if (dotPos>0) {
					ret += val2*dotPos;
					dotPos/=10.0;
				} else {
					ret = ret*10.0 + val2;
				}
			} else {
				break;
			}
		}
	}
	if (isOdd == true) {
		ret *= -1.0;
	}
	TK_VERBOSE( *this << " end =" << ret);
	return ret;
}


float std::string::toFloat(void) const
{
	return (float)toDouble();
}

#endif
