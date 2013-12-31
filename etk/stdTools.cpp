/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/stdTools.h>
#include <etk/debug.h>

#undef __class__
#define __class__ "u32char"

etk::CCout& etk::operator <<(etk::CCout& _os, const std::string& _obj) {
	_os << _obj.c_str();
	return _os;
}

etk::CCout& etk::operator <<(etk::CCout& _os, const std::vector<std::string>& _obj) {
	_os << "{";
	for (size_t iii=0; iii< _obj.size(); iii++) {
		if (iii>0) {
			_os << " ~ ";
		}
		_os << _obj[iii];
	}
	_os << "}";
	return _os;
}

etk::CCout& etk::operator <<(etk::CCout& _os, const std::u32string& _obj) {
	_os << std::to_string(_obj).c_str();
	return _os;
}

etk::CCout& etk::operator <<(etk::CCout& _os, const std::vector<std::u32string>& _obj) {
	_os << "{";
	for (size_t iii=0; iii< _obj.size(); iii++) {
		if (iii>0) {
			_os << " ~ ";
		}
		_os << _obj[iii];
	}
	_os << "}";
	return _os;
}

const char32_t u32char::Null('\0');
const char32_t u32char::Return('\n');
const char32_t u32char::CarrierReturn('\r');
const char32_t u32char::Tabulation('\t');
const char32_t u32char::Suppress((const char)127);
const char32_t u32char::Delete((const char)8);
const char32_t u32char::Space(' ');
const char32_t u32char::Escape((const char)27);

bool u32char::isWhiteChar(char32_t _val) {
	if(    _val == ' '
	    || _val == '\t'
	    || _val == '\n'
	    || _val == '\r') {
		return true;
	}
	return false;
}

bool u32char::isSpecialChar(char32_t _val) {
	if(    _val < '0'
	    || (_val > '9' && _val < 'A')
	    || (_val > 'Z' && _val < 'a')
	    || (_val > 'z' && _val < 0xFF) ) {
		return true;
	}
	return false;
}

bool u32char::isInteger(char32_t _val) {
	if(    _val >= (uint32_t)'0'
	    && _val <= (uint32_t)'9') {
		return true;
	}
	return false;
}

int32_t u32char::toInt(char32_t _val) {
	return _val - (uint32_t)'0';
}


char32_t u32char::changeOrder(char32_t _val) {
	if (_val >= 'A' && _val <= 'Z') {
		return (_val - (uint32_t)'A')*2 + 'A';
	}
	if (_val >= 'a' && _val <= 'z') {
		return (_val - (uint32_t)'a')*2 + 'A' + 1;
	}
	if (_val >= ':' && _val <= '@') {
		return _val + 52;
	}
	if (_val >= '[' && _val <= '`') {
		return _val +26;
	}
	return _val;
}

static uint32_t getUtf8Val(char32_t _val) {
	uint32_t output = 0;
	if (_val <= 127) {
		output = _val;
	} else if (_val <= 2047) {
		// output ==> 00000000 00000000 110xxxxx 10xxxxxx
		// input ==>  -------- -------- -----222 22111111
		output = 0x0000C080;
		output+= (_val & 0x000007C0)<<2;
		output+=  _val & 0x0000003F;
	} else if (_val <= 65535) {
		// output ==> 00000000 1110xxxx 10xxxxxx 10xxxxxx
		// input ==>  -------- -------- 33332222 22111111
		output = 0x00E08080;
		output+= (_val & 0x0000F000)<<4;
		output+= (_val & 0x00000FC0)<<2;
		output+=  _val & 0x0000003F;
	} else if (_val <= 1114111) {
		// output ==> 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
		// input ==>  -------- ---44433 33332222 22111111
		output = 0xF0808080;
		output+= (_val & 0x001C0000)<<6;
		output+= (_val & 0x0003F000)<<4;
		output+= (_val & 0x00000FC0)<<2;
		output+=  _val & 0x0000003F;
	} else {
		//TK_ERROR("NON UTF8 caracter input...");
		printf("not an utf8 char : %#08x\n", _val);
		return 0;
	}
	//printf("utf8convertion : %d=%08x ==> %08x\n",value, value, output);
	return output;
}

int8_t u32char::convertUtf8(char32_t _val, char _output[5]) {
	uint32_t value = getUtf8Val(_val);
	if (0xFF >= value) {
		_output[0] = (char)value;
		_output[1] = '\0';
		return 1;
	} else if (0xFFFF >= value) {
		_output[0] = (char)((value>>8)  & 0x000000FF);
		_output[1] = (char)value;
		_output[2] = '\0';
		return 2;
	} else if (0xFFFFFF >= value) {
		_output[0] = (char)((value>>16) & 0x000000FF);
		_output[1] = (char)((value>>8)  & 0x000000FF);
		_output[2] = (char)value;
		_output[3] = '\0';
		return 3;
	} else {
		_output[0] = (char)((value>>24) & 0x000000FF);
		_output[1] = (char)((value>>16) & 0x000000FF);
		_output[2] = (char)((value>>8)  & 0x000000FF);
		_output[3] = (char)value;
		_output[4] = '\0';
		return 4;
	}
}


#undef __class__
#define __class__ "utf8"


static uint8_t sizeElement(const char* _data, int32_t _lenMax) {
	uint8_t size = 0;
	TK_ASSERT(0 <= _lenMax, "size can not be < 0 ...");
	if (0 > _lenMax) {
		return 0;
	}
	//4 case
	if(    _lenMax >= 1
	    && (_data[0] & 0x80) == 0x00 ) {
		// One Char Element
		size = 1;
	} else if(    _lenMax >= 2
	           && (_data[0] & 0xE0) == 0xC0
	           && (_data[1] & 0xC0) == 0x80) {
		size = 2;
	} else if(    _lenMax >= 3
	           && (_data[0] & 0xF0) == 0xE0
	           && (_data[1] & 0xC0) == 0x80
	           && (_data[2] & 0xC0) == 0x80) {
		size = 3;
	} else if(    _lenMax >= 4
	           && (_data[0] & 0xF8) == 0xF0
	           && (_data[1] & 0xC0) == 0x80
	           && (_data[2] & 0xC0) == 0x80
	           && (_data[3] & 0xC0) == 0x80) {
		size = 4;
	}
	return size;
}

char32_t utf8::convertChar32(const char* _input) {
	char32_t value = 0;
	if (NULL == _input) {
		return value;
	}
	int32_t len = strlen(_input);
	len = sizeElement(_input, len);
	switch (len) {
		default:
			// case 0 : An error occured...
			value = _input[0];
			return value;
		case 1:
			value = (uint8_t)(_input[0]) & 0x7F;
			return value;
		case 2:
			value  = (((uint8_t)_input[0]) & 0x1F)<< 6;
			value +=  ((uint8_t)_input[1]) & 0x3F;
			return value;
		case 3:
			value  = (((uint8_t)_input[0]) & 0x0F)<< 12;
			value += (((uint8_t)_input[1]) & 0x3F)<< 6;
			value +=  ((uint8_t)_input[2]) & 0x3F;
			return value;
		case 4:
			value  = (((uint8_t)_input[0]) & 0x07)<< 18;
			value += (((uint8_t)_input[1]) & 0x3F)<< 12;
			value += (((uint8_t)_input[2]) & 0x3F)<< 6;
			value +=  ((uint8_t)_input[3]) & 0x3F;
			return value;
	}
}

int8_t utf8::theoricLen(const char _input) {
	if((_input&0x80) == 0x00 ) {
		return 1;
	}
	if((_input&0xE0) == 0xC0) {
		return 2;
	}
	if((_input&0xF0) == 0xE0) {
		return 3;
	}
	if((_input&0xF8) == 0xF0) {
		return 4;
	}
	return 1;
}

bool utf8::theoricFirst(const char _input) {
	// When started with the bit 0 then the size is signle element.
	if((_input&0x80) == 0x00 ) {
		return true;
	}
	// for multiple element size, we just need to check the second element (might be != 1)
	if((_input&0x40) == 0x40 ) {
		return true;
	}
	return false;
}


#undef __class__
#define __class__ "std"

std::string std::to_string(const std::u32string& _input) {
	std::string out;
	for (size_t iii=0; iii<_input.size(); ++iii) {
		char output[10];
		u32char::convertUtf8(_input[iii], output);
		out += output;
	}
	return out;
}

std::u32string std::to_u32string(const std::string& _input) {
	return std::to_u32string(_input.c_str());
}
std::u32string std::to_u32string(const char* _input) {
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
		out += utf8::convertChar32(tmpData);
	}
	return out;
}


std::u32string std::to_u32string(int _val) {
	return std::to_u32string(std::to_string(_val));
};
std::u32string std::to_u32string(long _val) {
	return std::to_u32string(std::to_string(_val));
};
std::u32string std::to_u32string(long long _val) {
	return std::to_u32string(std::to_string(_val));
};
std::u32string std::to_u32string(unsigned _val) {
	return std::to_u32string(std::to_string(_val));
};
std::u32string std::to_u32string(unsigned long _val) {
	return std::to_u32string(std::to_string(_val));
};
std::u32string std::to_u32string(unsigned long long _val) {
	return std::to_u32string(std::to_string(_val));
};
std::u32string std::to_u32string(float _val) {
	return std::to_u32string(std::to_string(_val));
};
std::u32string std::to_u32string(double _val) {
	return std::to_u32string(std::to_string(_val));
};
std::u32string std::to_u32string(long double _val) {
	return std::to_u32string(std::to_string(_val));
};

bool std::stob(const std::u32string& _str) {
	if(    true == compare_no_case(_str, U"true")
	    || true == compare_no_case(_str, U"enable")
	    || true == compare_no_case(_str, U"yes")
	    || _str == U"1") {
		return true;
	}
	return false;
}

double std::stod(const std::u32string& _str, size_t* _idx) {
	return std::stod(std::to_string(_str), _idx);
}

float std::stof(const std::u32string& _str, size_t* _idx) {
	return std::stof(std::to_string(_str), _idx);
}

int std::stoi(const std::u32string& _str, size_t* _idx, int _base) {
	return std::stoi(std::to_string(_str), _idx, _base);
}

long std::stol(const std::u32string& _str, size_t* _idx, int _base) {
	return std::stol(std::to_string(_str), _idx, _base);
}

long double std::stold(const std::u32string& _str, size_t* _idx) {
	return std::stold(std::to_string(_str), _idx);
}

long long std::stoll(const std::u32string& _str, size_t* _idx, int _base) {
	return std::stoll(std::to_string(_str), _idx, _base);
}

unsigned long std::stoul(const std::u32string& _str, size_t* _idx, int _base ) {
	return std::stoul(std::to_string(_str), _idx, _base);
}

unsigned long long std::stoull(const std::u32string& _str, size_t* _idx, int _base ) {
	return std::stoull(std::to_string(_str), _idx, _base);
}

bool std::stob(const std::string& _str) {
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
#if (defined(__TARGET_OS__Android) || defined(__TARGET_OS__MacOs))
	std::string std::to_string(int _val) {
		char tmpVal[256];
		sprintf(tmpVal, "%d", _val);
		return tmpVal;
	}
	std::string std::to_string(long _val) {
		char tmpVal[256];
		sprintf(tmpVal, "%ld", _val);
		return tmpVal;
	}
	std::string std::to_string(long long _val) {
		char tmpVal[256];
		sprintf(tmpVal, "%lld", _val);
		return tmpVal;
	}
	std::string std::to_string(unsigned _val) {
		char tmpVal[256];
		sprintf(tmpVal, "%u", _val);
		return tmpVal;
	}
	std::string std::to_string(unsigned long _val) {
		char tmpVal[256];
		sprintf(tmpVal, "%lu", _val);
		return tmpVal;
	}
	std::string std::to_string(unsigned long long _val) {
		char tmpVal[256];
		sprintf(tmpVal, "%llu", _val);
		return tmpVal;
	}
	std::string std::to_string(float _val) {
		char tmpVal[256];
		sprintf(tmpVal, "%f", _val);
		return tmpVal;
	}
	std::string std::to_string(double _val) {
		char tmpVal[256];
		sprintf(tmpVal, "%f", _val);
		return tmpVal;
	}
	std::string std::to_string(long double _val) {
		char tmpVal[256];
		sprintf(tmpVal, "%lf", _val);
		return tmpVal;
	}
#endif

std::u32string std::to_u32string(bool _val) {
	if (_val == true) {
		return U"true";
	}
	return U"false";
}

bool std::compare_no_case(const std::u32string& _obj, const std::u32string& _val) {
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

bool std::compare_no_case(const std::string& _obj, const std::string& _val) {
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

struct doublette {
	char32_t lower;
	char32_t upper;
};
struct doublette convertionTable[] = {
	{U'ç', U'Ç'},

	{U'á', U'Á'}, {U'à', U'À'}, {U'ä', U'Ä'}, {U'â', U'Â'}, {U'å', U'Å'}, {U'ã', U'Ã'},
	{U'é', U'É'}, {U'è', U'È'}, {U'ë', U'Ë'}, {U'ê', U'Ê'}, 
	{U'ú', U'Ú'}, {U'ù', U'Ù'}, {U'ü', U'Ü'}, {U'û', U'Û'},
	{U'í', U'Í'}, {U'ì', U'Ì'}, {U'ï', U'Ï'}, {U'î', U'Î'},
	{U'ó', U'Ó'}, {U'ò', U'Ò'}, {U'ö', U'Ö'}, {U'ô', U'Ô'}, {U'õ', U'Õ'},
	{U'ý', U'Ý'}, {U'ỳ', U'Ỳ'}, {U'ÿ', U'Ÿ'}, {U'ŷ', U'Ŷ'},

	{U'ñ', U'Ñ'}, {U'ǹ', U'Ǹ'},

	{U'ḧ', U'Ḧ'}, {U'ĥ', U'Ĥ'},

	{U'ẅ', U'Ẅ'}, {U'ŵ', U'Ŵ'}, {U'ẁ', U'Ẁ'},

	{U'ẍ', U'Ẍ'},

	{U'æ', U'Æ'},
	{U'ð', U'Ð'},
	{U'ø', U'Ø'}
};
size_t convertionTableSize = sizeof(convertionTable)/sizeof(struct doublette);

static char32_t localToUpper(char32_t _input) {
	if (_input >= 'a' && _input <= 'z') {
		return _input + ((int)'A'-(int)'a');
	}
	for (size_t iii = 0; iii < convertionTableSize; ++iii) {
		if (convertionTable[iii].lower == _input) {
			return convertionTable[iii].upper;
		}
	}
	return _input;
}

static char32_t localToLower(char32_t _input) {
	if (_input >= 'A' && _input <= 'Z') {
		return _input + ((int)'a'-(int)'A');
	}
	for (size_t iii = 0; iii < convertionTableSize; ++iii) {
		if (convertionTable[iii].upper == _input) {
			return convertionTable[iii].lower;
		}
	}
	return _input;
}


std::string std::tolower(std::string _obj) {
	for(size_t iii=0 ; iii<_obj.size() ; iii++) {
		_obj[iii] = std::tolower(_obj[iii]);
	}
	return _obj;
}
std::u32string std::tolower(std::u32string _obj) {
	for(size_t iii=0 ; iii<_obj.size() ; iii++) {
		_obj[iii] = localToLower(_obj[iii]);
	}
	return _obj;
}

std::string std::toupper(std::string _obj) {
	for(size_t iii=0 ; iii<_obj.size() ; iii++) {
		_obj[iii] = std::toupper(_obj[iii]);
	}
	return _obj;
}

std::u32string std::toupper(std::u32string _obj) {
	for(size_t iii=0 ; iii<_obj.size() ; iii++) {
		_obj[iii] = localToUpper(_obj[iii]);
	}
	return _obj;
}

bool std::end_with(const std::string& _obj, const std::string& _val, bool _caseSensitive) {
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

bool std::end_with(const std::u32string& _obj, const std::u32string& _val, bool _caseSensitive) {
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

bool std::start_with(const std::string& _obj, const std::string& _val, bool _caseSensitive) {
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

bool std::start_with(const std::u32string& _obj, const std::u32string& _val, bool _caseSensitive) {
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

std::u32string std::replace(const std::u32string& _obj, char32_t _val, char32_t _replace) {
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

std::string std::replace(const std::string& _obj, char _val, char _replace) {
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

std::string std::extract_line(const std::string& _obj, int32_t _pos) {
	// search back : '\n'
	size_t startPos = _obj.rfind('\n', _pos);
	if ((int64_t)startPos == (int64_t)_pos) {
		startPos = 0;
	} else {
		startPos++;
	}
	// search forward : '\n'
	size_t stopPos = _pos;
	if (_obj[_pos] != '\n') {
		stopPos = _obj.find('\n', _pos);
		if ((int64_t)stopPos == _pos) {
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

std::u32string std::extract_line(const std::u32string& _obj, int32_t _pos) {
	// search back : '\n'
	size_t startPos = _obj.rfind('\n', _pos);
	if ((int64_t)startPos == _pos) {
		startPos = 0;
	} else {
		startPos++;
	}
	// search forward : '\n'
	size_t stopPos = _pos;
	if (_obj[_pos] != '\n') {
		stopPos = _obj.find('\n', _pos);
		if ((int64_t)stopPos == _pos) {
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

std::vector<std::string> std::split(const std::string& _input, char _val) {
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

std::vector<std::u32string> std::split(const std::u32string& _input, char32_t _val) {
	std::vector<std::u32string> list;
	size_t lastStartPos = 0;
	for(size_t iii=0; iii<_input.size(); iii++) {
		if (_input[iii]==_val) {
			list.push_back(std::u32string(_input, lastStartPos, iii - lastStartPos));
			lastStartPos = iii+1;
		}
	}
	if (lastStartPos<_input.size()) {
		list.push_back(std::u32string(_input, lastStartPos));
	}
	return list;
}

#if (defined(__TARGET_OS__Android) || defined(__TARGET_OS__MacOs))
double std::stod(const std::string& _str, size_t* _idx) {
	double ret = 0;
	sscanf(_str.c_str(), "%Lf", &ret);
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
	sscanf(_str.c_str(), "%Lf", &ret);
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



void std::sort(std::vector<std::string *> &_list) {
	std::vector<std::string *> tmpList(_list);
	_list.clear();
	for(size_t iii=0; iii<tmpList.size(); iii++) {
		size_t findPos = 0;
		for(size_t jjj=0; jjj<_list.size(); jjj++) {
			//EWOL_DEBUG("compare : \""<<*tmpList[iii] << "\" and \"" << *m_listDirectory[jjj] << "\"");
			if (*tmpList[iii] > *_list[jjj]) {
				findPos = jjj+1;
			}
		}
		//EWOL_DEBUG("position="<<findPos);
		_list.insert(_list.begin()+findPos, tmpList[iii]);
	}
}

void std::sort(std::vector<std::u32string *> &_list) {
	std::vector<std::u32string *> tmpList(_list);
	_list.clear();
	for(size_t iii=0; iii<tmpList.size(); iii++) {
		size_t findPos = 0;
		for(size_t jjj=0; jjj<_list.size(); jjj++) {
			//EWOL_DEBUG("compare : \""<<*tmpList[iii] << "\" and \"" << *m_listDirectory[jjj] << "\"");
			if (*tmpList[iii] > *_list[jjj]) {
				findPos = jjj+1;
			}
		}
		//EWOL_DEBUG("position="<<findPos);
		_list.insert(_list.begin()+findPos, tmpList[iii]);
	}
}


