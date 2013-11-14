/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/types.h>
#include <etk/UChar.h>
#include <etk/unicode.h>

#include <etk/debug.h>
#include <etk/Stream.h>
#include <vector>
#include <etk/Char.h>

const char32_t etk::UChar::Null('\0');
const char32_t etk::UChar::Return('\n');
const char32_t etk::UChar::CarrierReturn('\r');
const char32_t etk::UChar::Tabulation('\t');
const char32_t etk::UChar::Suppress((const char)127);
const char32_t etk::UChar::Delete((const char)8);
const char32_t etk::UChar::Space(' ');
const char32_t etk::UChar::Escape((const char)27);

bool etk::isWhiteChar(char32_t _val) {
	if(    _val == ' '
	    || _val == '\t'
	    || _val == '\n'
	    || _val == '\r') {
		return true;
	}
	return false;
}

bool etk::isSpecialChar(char32_t _val) {
	if(    _val < '0'
	    || (_val > '9' && _val < 'A')
	    || (_val > 'Z' && _val < 'a')
	    || (_val > 'z' && _val < 0xFF) ) {
		return true;
	}
	return false;
}

bool etk::isInteger(char32_t _val) {
	if(    _val >= (uint32_t)'0'
	    && _val <= (uint32_t)'9') {
		return true;
	}
	return false;
}

int32_t etk::toInt32(char32_t _val) {
	return _val - (uint32_t)'0';
}

char32_t etk::toLower(char32_t _val) {
	if(    _val>=(uint32_t)'A'
	    && _val<=(uint32_t)'Z') {
		return _val + (uint32_t)'a' - (uint32_t)'A';
	}
	return _val;
}

char32_t etk::toUpper(char32_t _val) {
	if(    _val>=(uint32_t)'a'
	    && _val<=(uint32_t)'z') {
		return _val + (uint32_t)'A' - (uint32_t)'a';
	}
	return _val;
}

bool etk::compareNoCase(char32_t _val1, char32_t _val2) {
	return toUpper(_val1) == toUpper(_val2);
}


char32_t etk::changeOrder(char32_t _val) {
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
		TK_ERROR("NON UTF8 caracter input...");
		return 0;
	}
	//printf("utf8convertion : %d=%08x ==> %08x\n",value, value, output);
	return output;
}

int8_t etk::getUtf8(char32_t _val, char _output[5]) {
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

uint8_t sizeElement(const char* _data, int32_t _lenMax)
{
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

char32_t etk::setUtf8(const char* _input) {
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

int8_t etk::UChar::theoricUTF8Len(const char _input) {
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

bool etk::UChar::theoricUTF8First(const char _input) {
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


#if 0



bool char32_t::isWhiteChar(void) const
{
	if(    m_value == ' '
	    || m_value == '\t'
	    || m_value == '\n'
	    || m_value == '\r') {
		return true;
	}
	return false;
}

bool char32_t::isSpecialChar(void) const
{
	if(    m_value < '0'
	    || (m_value > '9' && m_value < 'A')
	    || (m_value > 'Z' && m_value < 'a')
	    || (m_value > 'z' && m_value < 0xFF) ) {
		return true;
	}
	return false;
}

bool char32_t::isInteger(void) const
{
	if(    m_value>=(uint32_t)'0'
	    && m_value<=(uint32_t)'9') {
		return true;
	}
	return false;
}

int32_t char32_t::toInt32(void) const
{
	return m_value - (uint32_t)'0';
}
/*
etk::CCout& etk::operator <<(etk::CCout& _os, char32_t _obj)
{
	char output_UTF8[8];
	unicode::convertUnicodeToUtf8(_obj, output_UTF8);
	_os << &output_UTF8[0];
	return _os;
}
*/



/*
std::vector<int8_t> char32_t::GetUtf8(void) const
{
	std::vector<int8_t> ret;
	uint32_t value = GetUtf8();
	if (0xFF >= value) {
		ret.PushBack((char)value);
	} else if (0xFFFF >= value) {
		ret.PushBack((char)((value>>8)  & 0x000000FF));
		ret.PushBack((char)value);
	} else if (0xFFFFFF >= value) {
		ret.PushBack((char)((value>>16) & 0x000000FF));
		ret.PushBack((char)((value>>8)  & 0x000000FF));
		ret.PushBack((char)value);
	} else {
		ret.PushBack((char)((value>>24) & 0x000000FF));
		ret.PushBack((char)((value>>16) & 0x000000FF));
		ret.PushBack((char)((value>>8)  & 0x000000FF));
		ret.PushBack((char)value);
	}
	return ret;
}
*/
uint8_t sizeElement(const char* _data, int32_t _lenMax)
{
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


int8_t char32_t::setUtf8(const char* _input)
{
	m_value = 0;
	if (NULL == _input) {
		return 0;
	}
	int32_t len = strlen(_input);
	len = sizeElement(_input, len);
	switch (len) {
		default:
			// case 0 : An error occured...
			m_value = _input[0];
			return 0;
		case 1:
			m_value = (uint8_t)(_input[0]) & 0x7F;
			return 1;
		case 2:
			m_value  = (((uint8_t)_input[0]) & 0x1F)<< 6;
			m_value +=  ((uint8_t)_input[1]) & 0x3F;
			return 2;
		case 3:
			m_value  = (((uint8_t)_input[0]) & 0x0F)<< 12;
			m_value += (((uint8_t)_input[1]) & 0x3F)<< 6;
			m_value +=  ((uint8_t)_input[2]) & 0x3F;
			return 3;
		case 4:
			m_value  = (((uint8_t)_input[0]) & 0x07)<< 18;
			m_value += (((uint8_t)_input[1]) & 0x3F)<< 12;
			m_value += (((uint8_t)_input[2]) & 0x3F)<< 6;
			m_value +=  ((uint8_t)_input[3]) & 0x3F;
			return 4;
	}
}

#endif
