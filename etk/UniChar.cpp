/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/types.h>
#include <etk/UniChar.h>
#include <etk/unicode.h>

#include <etk/DebugInternal.h>
#include <etk/Stream.h>
#include <etk/Vector.h>
#include <etk/Char.h>

void etk::UniChar::Lower(void)
{
	if(    m_value>=(uint32_t)'A'
	    && m_value<=(uint32_t)'Z') {
		m_value += (uint32_t)'a' - (uint32_t)'A';
	}
}

etk::UniChar etk::UniChar::ToLower(void) const
{
	if(    m_value>=(uint32_t)'A'
	    && m_value<=(uint32_t)'Z') {
		return m_value + (uint32_t)'a' - (uint32_t)'A';
	}
	return m_value;
}

void etk::UniChar::Upper(void)
{
	if(    m_value>=(uint32_t)'a'
	    && m_value<=(uint32_t)'z') {
		m_value += (uint32_t)'A' - (uint32_t)'a';
	}
}

etk::UniChar etk::UniChar::ToUpper(void) const
{
	if(    m_value>=(uint32_t)'a'
	    && m_value<=(uint32_t)'z') {
		return m_value + (uint32_t)'A' - (uint32_t)'a';
	}
	return m_value;
}



bool etk::UniChar::CompareNoCase(const etk::UniChar& _obj) const
{
	return ToUpper() == _obj.ToUpper();
}


etk::UniChar etk::UniChar::ChangeOrder(void) const
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


bool etk::UniChar::IsInteger(void) const
{
	if(    m_value>=(uint32_t)'0'
	    && m_value<=(uint32_t)'9') {
		return true;
	}
	return false;
}

int32_t etk::UniChar::ToInt32(void) const
{
	return m_value - (uint32_t)'0';
}
/*
etk::CCout& etk::operator <<(etk::CCout& _os, const etk::UniChar& _obj)
{
	char output_UTF8[8];
	unicode::convertUnicodeToUtf8(_obj, output_UTF8);
	_os << &output_UTF8[0];
	return _os;
}
*/


uint32_t etk::UniChar::GetUtf8(void) const
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

int8_t etk::UniChar::GetUtf8(char _output[5]) const
{
	uint32_t value = GetUtf8();
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

void etk::UniChar::SetUtf8(const char* _input)
{
	m_value = 0;
	if (NULL == _input) {
		return;
	}
	int32_t len = strlen(_input);
	switch (len) {
		case 1:
			m_value = (uint8_t)(_input[0]) & 0x7F;
			break;
		case 2:
			m_value  = (((uint8_t)_input[0]) & 0x1F)<< 6;
			m_value +=  ((uint8_t)_input[1]) & 0x3F;
			break;
		case 3:
			m_value  = (((uint8_t)_input[0]) & 0x0F)<< 12;
			m_value += (((uint8_t)_input[1]) & 0x3F)<< 6;
			m_value +=  ((uint8_t)_input[2]) & 0x3F;
			break;
		default:
			m_value  = (((uint8_t)_input[0]) & 0x07)<< 18;
			m_value += (((uint8_t)_input[1]) & 0x3F)<< 12;
			m_value += (((uint8_t)_input[2]) & 0x3F)<< 6;
			m_value +=  ((uint8_t)_input[3]) & 0x3F;
			break;
	}
}
