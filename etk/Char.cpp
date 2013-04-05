/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/Char.h>
#include <etk/os/Memory.h>


etk::Char::Char(void) {
	m_data.PushBack('\0');
}

etk::Char::~Char(void)
{
	
}

etk::Char::operator const char *()
{
	return &m_data[0];
};

etk::Char::operator void *()
{
	return &m_data[0];
};


void etk::Char::SetValue(const etk::Vector<char>& data)
{
	m_data = data;
	// check presence of '\0' (note : start by the end might be faster ...
	for (int32_t iii=m_data.Size()-1; iii>=0; iii--) {
		if (m_data[iii] == '\0') {
			return;
		}
	}
	m_data.PushBack('\0');
}



