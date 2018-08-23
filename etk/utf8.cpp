/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/utf8.hpp>
//#include <etk/debug.hpp>
#include <etk/String.hpp>
#include <etk/UString.hpp>



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

int8_t u32char::convertUtf8(char32_t _val, char _output[7]) {
	if (_val <= 127) {
		// input  ==>                   -------- -------- -------- -1111111
		// output ==> 00000000 00000000 00000000 00000000 00000000 0xxxxxxx
		_output[0] = (char)_val;
		_output[1] = 0;
		return 1;
	} else if (_val <= 0x000007FF) {
		// input  ==>                   -------- -------- -----222 22111111
		// output ==> 00000000 00000000 00000000 00000000 110xxxxx 10xxxxxx
		_output[0] = 0xC0 | ( (_val & 0x000007C0) >>  6 );
		_output[1] = 0x80 | ( (_val & 0x0000003F)       );
		_output[2] = 0;
		return 2;
	} else if (_val <= 0x0000FFFF) {
		// input  ==>                   -------- -------- 33332222 22111111
		// output ==> 00000000 00000000 00000000 1110xxxx 10xxxxxx 10xxxxxx
		_output[0] = 0xE0 | ( (_val & 0x0000F000) >> 12 );
		_output[1] = 0x80 | ( (_val & 0x00000FC0) >>  6 );
		_output[2] = 0x80 | ( (_val & 0x0000003F)       );
		_output[3] = 0;
		return 3;
	} else if (_val <= 0x001FFFFF) {
		// input  ==>                   -------- ---44433 33332222 22111111
		// output ==> 00000000 00000000 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
		_output[0] = 0xF0 | ( (_val & 0x001C0000) >> 18 );
		_output[1] = 0x80 | ( (_val & 0x0003F000) >> 12 );
		_output[2] = 0x80 | ( (_val & 0x00000FC0) >>  6 );
		_output[3] = 0x80 | ( (_val & 0x0000003F)       );
		_output[4] = 0;
		return 4;
	// the next element is my personal interpretation...
	} else if (_val <= 0x03FFFFFF) {
		// input  ==>                   ------55 44444433 33332222 22111111
		// output ==> 00000000 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
		_output[0] = 0xF8 | ( (_val & 0x03000000) >> 24 );
		_output[1] = 0x80 | ( (_val & 0x00FC0000) >> 18 );
		_output[2] = 0x80 | ( (_val & 0x0003F000) >> 12 );
		_output[3] = 0x80 | ( (_val & 0x00000FC0) >>  6 );
		_output[4] = 0x80 | ( (_val & 0x0000003F)       );
		_output[5] = 0;
		return 5;
	} else {
		// input  ==>                   66555555 44444433 33332222 22111111
		// output ==> 111111xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
		_output[0] = 0xFC | ( (_val & 0xC0000000) >> 30 );
		_output[1] = 0x80 | ( (_val & 0x3F000000) >> 24 );
		_output[2] = 0x80 | ( (_val & 0x00FC0000) >> 18 );
		_output[3] = 0x80 | ( (_val & 0x0003F000) >> 12 );
		_output[4] = 0x80 | ( (_val & 0x00000FC0) >>  6 );
		_output[5] = 0x80 | ( (_val & 0x0000003F)       );
		_output[6] = 0;
		return 6;
	}
}

etk::String u32char::convertToUtf8(const etk::UString& _input) {
	return etk::toString(_input);
}

size_t u32char::strlen(const char32_t* _input) {
	uint32_t out = 0;
	while (*_input != 0) {
		out++;
		_input++;
	}
	return out;
}
class DoubleChar {
	public:
		char32_t lower;
		char32_t upper;
};
DoubleChar conversionTable[] = {
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
size_t conversionTableSize = sizeof(conversionTable)/sizeof(DoubleChar);

char32_t u32char::toUpper(char32_t _input) {
	if (_input >= 'a' && _input <= 'z') {
		return _input + ((int)'A'-(int)'a');
	}
	for (size_t iii = 0; iii < conversionTableSize; ++iii) {
		if (conversionTable[iii].lower == _input) {
			return conversionTable[iii].upper;
		}
	}
	return _input;
}

char32_t u32char::toLower(char32_t _input) {
	if (_input >= 'A' && _input <= 'Z') {
		return _input + ((int)'a'-(int)'A');
	}
	for (size_t iii = 0; iii < conversionTableSize; ++iii) {
		if (conversionTable[iii].upper == _input) {
			return conversionTable[iii].lower;
		}
	}
	return _input;
}



static uint8_t sizeElement(const char* _data, int32_t _lenMax) {
	uint8_t size = 0;
	//TK_ASSERT(0 <= _lenMax, "size can not be < 0 ...");
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
	} else if(    _lenMax >= 5
	           && (_data[0] & 0xFC) == 0xF8
	           && (_data[1] & 0xC0) == 0x80
	           && (_data[2] & 0xC0) == 0x80
	           && (_data[3] & 0xC0) == 0x80
	           && (_data[4] & 0xC0) == 0x80) {
		size = 5;
	} else if(    _lenMax >= 6
	           && (_data[0] & 0xFC) == 0xFC
	           && (_data[1] & 0xC0) == 0x80
	           && (_data[2] & 0xC0) == 0x80
	           && (_data[3] & 0xC0) == 0x80
	           && (_data[4] & 0xC0) == 0x80
	           && (_data[5] & 0xC0) == 0x80) {
		size = 6;
	}
	return size;
}

char32_t utf8::convertChar32(const char* _input) {
	char32_t value = 0;
	if (null == _input) {
		return value;
	}
	int32_t len = strlen(_input);
	len = sizeElement(_input, len);
	switch (len) {
		case 1:
			// input  ==> 00000000 00000000 00000000 00000000 00000000 0xxxxxxx
			// output ==>                   -------- -------- -------- -1111111
			value = (uint8_t)(_input[0]) & 0x7F;
			return value;
		case 2:
			// input  ==> 00000000 00000000 00000000 00000000 110xxxxx 10xxxxxx
			// output ==>                   -------- -------- -----222 22111111
			value  = (((uint8_t)_input[0]) & 0x1F)<< 6;
			value += (((uint8_t)_input[1]) & 0x3F);
			return value;
		case 3:
			// input  ==> 00000000 00000000 00000000 1110xxxx 10xxxxxx 10xxxxxx
			// output ==>                   -------- -------- 33332222 22111111
			value  = (((uint8_t)_input[0]) & 0x0F)<< 12;
			value += (((uint8_t)_input[1]) & 0x3F)<< 6;
			value += (((uint8_t)_input[2]) & 0x3F);
			return value;
		case 4:
			// input  ==> 00000000 00000000 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
			// output ==>                   -------- ---44433 33332222 22111111
			value  = (((uint8_t)_input[0]) & 0x07)<< 18;
			value += (((uint8_t)_input[1]) & 0x3F)<< 12;
			value += (((uint8_t)_input[2]) & 0x3F)<< 6;
			value += (((uint8_t)_input[3]) & 0x3F);
			return value;
		case 5:
			// input  ==> 00000000 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
			// output ==>                   ------55 44444433 33332222 22111111
			value  = (((uint8_t)_input[0]) & 0x03)<< 24;
			value += (((uint8_t)_input[1]) & 0x3F)<< 18;
			value += (((uint8_t)_input[2]) & 0x3F)<< 12;
			value += (((uint8_t)_input[3]) & 0x3F)<< 6;
			value += (((uint8_t)_input[4]) & 0x3F);
			return value;
		case 6:
			// input  ==> 111111xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
			// output ==>                   66555555 44444433 33332222 22111111
			value  = (((uint8_t)_input[0]) & 0x03)<< 30;
			value += (((uint8_t)_input[1]) & 0x3F)<< 24;
			value += (((uint8_t)_input[2]) & 0x3F)<< 18;
			value += (((uint8_t)_input[3]) & 0x3F)<< 12;
			value += (((uint8_t)_input[4]) & 0x3F)<< 6;
			value += (((uint8_t)_input[5]) & 0x3F);
			return value;
	}
	// An error occurred...
	value = _input[0];
	return value;
}

int8_t utf8::length(const char _input) {
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
	if((_input&0xFC) == 0xF8) {
		return 5;
	}
	if((_input&0xFC) == 0xFC) {
		return 5;
	}
	return 1;
}

bool utf8::first(const char _input) {
	// When started with the bit 0 then the size is single element.
	if((_input&0x80) == 0x00 ) {
		return true;
	}
	// for multiple element size, we just need to check the second element (might be != 1)
	if((_input&0x40) == 0x40 ) {
		return true;
	}
	return false;
}

etk::UString utf8::convertUnicode(const char* _input) {
	if (_input == null) {
		return U"";
	}
	etk::UString out;
	char tmpData[20];
	int64_t pos = 0;
	int64_t inputLen = strlen(_input);
	while (pos < inputLen) {
		int32_t lenMax = inputLen - pos;
		uint8_t tmpPos = sizeElement(&_input[pos], lenMax);
		out += utf8::convertChar32(&_input[pos]);
		pos += tmpPos;
	}
	return out;
}

etk::UString utf8::convertUnicode(const etk::String& _input) {
	return utf8::convertUnicode(_input.c_str());
}
