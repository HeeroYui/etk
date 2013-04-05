/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_CHAR_H__
#define __ETK_CHAR_H__

#include <etk/DebugInternal.h>
#include <etk/Stream.h>
#include <etk/Vector.h>

namespace etk
{
	class Char
	{
		private:
			etk::Vector<char> m_data;
		public:
			Char(void);
			~Char(void);
			operator const char *();
			operator void *();
			void SetValue(const etk::Vector<char>& data);
	};
};


#endif

