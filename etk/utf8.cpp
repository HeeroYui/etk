/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/stdTools.hpp>
#include <etk/debug.hpp>
#include <etk/String.hpp>



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
		//TK_ERROR("NOT UTF8 character input...");
		printf("not an utf8 char : %#08x\n", _val);
		return 0;
	}
	//printf("utf-8 conversion : %d=%08x ==> %08x\n",value, value, output);
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
#if __CPP_VERSION__ >= 2011
	etk::String u32char::convertToUtf8(const etk::UString& _input) {
		TK_TODO("implement this function ...");
		return "TODO ... etk::String u32char::convertToUtf8(const etk::UString& _input)";
	}
#endif

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
	if (nullptr == _input) {
		return value;
	}
	int32_t len = strlen(_input);
	len = sizeElement(_input, len);
	switch (len) {
		default:
			// case 0 : An error occurred...
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
#if __CPP_VERSION__ >= 2011
	etk::UString utf8::convertUnicode(const etk::String& _input) {
		TK_TODO("implement this function ...");
		return U"TODO ... etk::UString utf8::convertUnicode(const etk::String& _input)";
	}
#endif
