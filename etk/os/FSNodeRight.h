/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_FILE_SYSTEM_NODE_RIGHT_H__
#define __ETK_FILE_SYSTEM_NODE_RIGHT_H__

#include <etk/UString.h>

namespace etk
{
	class FSNodeRight
	{
		private:
			uint16_t m_rights;
		public:
			FSNodeRight(void);
			FSNodeRight(int16_t _newRight);
			~FSNodeRight(void) { };
			// copy operator :
			const etk::FSNodeRight& operator=  (const etk::FSNodeRight &_obj );
			// set right :
			const etk::FSNodeRight& operator=  (const int32_t _newVal );
			
			void Clear(void) { m_rights = 0; };
			// User
			bool IsUserReadable(void) const;
			bool IsUserWritable(void) const;
			bool IsUserRunable(void) const;
			void SetUserReadable(bool _newStatus);
			void SetUserWritable(bool _newStatus);
			void SetUserRunable(bool _newStatus);
			// group
			bool IsGroupReadable(void) const;
			bool IsGroupWritable(void) const;
			bool IsGroupRunable(void) const;
			void SetGroupReadable(bool _newStatus);
			void SetGroupWritable(bool _newStatus);
			void SetGroupRunable(bool _newStatus);
			// other
			bool IsOtherReadable(void) const;
			bool IsOtherWritable(void) const;
			bool IsOtherRunable(void) const;
			void SetOtherReadable(bool _newStatus);
			void SetOtherWritable(bool _newStatus);
			void SetOtherRunable(bool _newStatus);
			
			etk::UString GetRight(void) const;
	};
	etk::CCout& operator <<(etk::CCout &_os, const etk::FSNodeRight &_obj);
};

#endif

