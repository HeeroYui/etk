/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_FILE_SYSTEM_NODE_RIGHT_H__
#define __ETK_FILE_SYSTEM_NODE_RIGHT_H__

#include <etk/types.h>

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
			
			void clear(void) { m_rights = 0; };
			// User
			bool isUserReadable(void) const;
			bool isUserWritable(void) const;
			bool isUserRunable(void) const;
			void setUserReadable(bool _newStatus);
			void setUserWritable(bool _newStatus);
			void setUserRunable(bool _newStatus);
			// group
			bool isGroupReadable(void) const;
			bool isGroupWritable(void) const;
			bool isGroupRunable(void) const;
			void setGroupReadable(bool _newStatus);
			void setGroupWritable(bool _newStatus);
			void setGroupRunable(bool _newStatus);
			// other
			bool isOtherReadable(void) const;
			bool isOtherWritable(void) const;
			bool isOtherRunable(void) const;
			void setOtherReadable(bool _newStatus);
			void setOtherWritable(bool _newStatus);
			void setOtherRunable(bool _newStatus);
			
			std::u32string getURight(void) const;
			std::string getRight(void) const;
	};
	etk::CCout& operator <<(etk::CCout &_os, const etk::FSNodeRight &_obj);
};

#endif

