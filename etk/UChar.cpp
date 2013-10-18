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

#include <etk/DebugInternal.h>
#include <etk/Stream.h>
#include <etk/Vector.h>
#include <etk/Char.h>

const etk::UChar etk::UChar::Null('\0');
const etk::UChar etk::UChar::Return('\n');
const etk::UChar etk::UChar::CarrierReturn('\r');
const etk::UChar etk::UChar::Tabulation('\t');
const etk::UChar etk::UChar::Suppress((const char)127);
const etk::UChar etk::UChar::Delete((const char)8);
const etk::UChar etk::UChar::Space(' ');
const etk::UChar etk::UChar::Escape((const char)27);

void etk::UChar::lower(void)
{
	if(    m_value>=(uint32_t)'A'
	    && m_value<=(uint32_t)'Z') {
		m_value += (uint32_t)'a' - (uint32_t)'A';
	}
}

etk::UChar etk::UChar::toLower(void) const
{
	if(    m_value>=(uint32_t)'A'
	    && m_value<=(uint32_t)'Z') {
		return m_value + (uint32_t)'a' - (uint32_t)'A';
	}
	return m_value;
}

void etk::UChar::upper(void)
{
	if(    m_value>=(uint32_t)'a'
	    && m_value<=(uint32_t)'z') {
		m_value += (uint32_t)'A' - (uint32_t)'a';
	}
}

etk::UChar etk::UChar::toUpper(void) const
{
	if(    m_value>=(uint32_t)'a'
	    && m_value<=(uint32_t)'z') {
		return m_value + (uint32_t)'A' - (uint32_t)'a';
	}
	return m_value;
}



bool etk::UChar::compareNoCase(const etk::UChar& _obj) const
{
	return toUpper() == _obj.toUpper();
}


etk::UChar etk::UChar::changeOrder(void) const
{
	if (m_value >= 'A' && m_value <= 'Z') {
		return (m_value - (uint32_t)'A')*2 + 'A';
	}
	if (m_value >= 'a' && m_value <= 'z') {
		return (m_value - (uint32_t)'a')*2 + 'A' + 1;
	}
	if (m_value >= ':' && m_value <= '@') {
		return m_value + 52;
	}
	if (m_value >= '[' && m_value <= '`') {
		return m_value +26;
	}
	return m_value;
}


bool etk::UChar::isWhiteChar(void) const
{
	if(    m_value == ' '
	    || m_value == '\t'
	    || m_value == '\n'
	    || m_value == '\r') {
		return true;
	}
	return false;
}

bool etk::UChar::isSpecialChar(void) const
{
	if(    m_value < '0'
	    || (m_value > '9' && m_value < 'A')
	    || (m_value > 'Z' && m_value < 'a')
	    || (m_value > 'z' && m_value < 0xFF) ) {
		return true;
	}
	return false;
}

bool etk::UChar::isInteger(void) const
{
	if(    m_value>=(uint32_t)'0'
	    && m_value<=(uint32_t)'9') {
		return true;
	}
	return false;
}

int32_t etk::UChar::toInt32(void) const
{
	return m_value - (uint32_t)'0';
}
/*
etk::CCout& etk::operator <<(etk::CCout& _os, const etk::UChar& _obj)
{
	char output_UTF8[8];
	unicode::convertUnicodeToUtf8(_obj, output_UTF8);
	_os << &output_UTF8[0];
	return _os;
}
*/


uint32_t etk::UChar::getUtf8(void) const
{
	uint32_t output = 0;
	if (m_value <= 127) {
		output = m_value;
	} else if (m_value <= 2047) {
		// output ==> 00000000 00000000 110xxxxx 10xxxxxx
		// input ==>  -------- -------- -----222 22111111
		output = 0x0000C080;
		output+= (m_value & 0x000007C0)<<2;
		output+=  m_value & 0x0000003F;
	} else if (m_value <= 65535) {
		// output ==> 00000000 1110xxxx 10xxxxxx 10xxxxxx
		// input ==>  -------- -------- 33332222 22111111
		output = 0x00E08080;
		output+= (m_value & 0x0000F000)<<4;
		output+= (m_value & 0x00000FC0)<<2;
		output+=  m_value & 0x0000003F;
	} else if (m_value <= 1114111) {
		// output ==> 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
		// input ==>  -------- ---44433 33332222 22111111
		output = 0xF0808080;
		output+= (m_value & 0x001C0000)<<6;
		output+= (m_value & 0x0003F000)<<4;
		output+= (m_value & 0x00000FC0)<<2;
		output+=  m_value & 0x0000003F;
	} else {
		TK_ERROR("NON UTF8 caracter input...");
		return 0;
	}
	//printf("utf8convertion : %d=%08x ==> %08x\n",value, value, output);
	return output;
}

int8_t etk::UChar::getUtf8(char _output[5]) const
{
	uint32_t value = getUtf8();
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
/*
etk::Vector<int8_t> etk::UChar::GetUtf8(void) const
{
	etk::Vector<int8_t> ret;
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


int8_t etk::UChar::setUtf8(const char* _input)
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

int8_t etk::UChar::theoricUTF8Len(const char _input)
{
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

bool etk::UChar::theoricUTF8First(const char _input)
{
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
