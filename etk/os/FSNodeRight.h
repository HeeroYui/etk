/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <etk/types.h>

#ifndef __ETK_FILE_SYSTEM_NODE_RIGHT_H__
#define __ETK_FILE_SYSTEM_NODE_RIGHT_H__

namespace etk {
	class FSNodeRight {
		private:
			uint16_t m_rights;
		public:
			FSNodeRight();
			FSNodeRight(int16_t _newRight);
			~FSNodeRight() { };
			// copy operator :
			const etk::FSNodeRight& operator= (const etk::FSNodeRight &_obj );
			// set right :
			const etk::FSNodeRight& operator= (const int32_t _newVal );
			
			void clear() {
				m_rights = 0;
			};
			// User
			bool isUserReadable() const;
			bool isUserWritable() const;
			bool isUserRunable() const;
			void setUserReadable(bool _newStatus);
			void setUserWritable(bool _newStatus);
			void setUserRunable(bool _newStatus);
			// group
			bool isGroupReadable() const;
			bool isGroupWritable() const;
			bool isGroupRunable() const;
			void setGroupReadable(bool _newStatus);
			void setGroupWritable(bool _newStatus);
			void setGroupRunable(bool _newStatus);
			// other
			bool isOtherReadable() const;
			bool isOtherWritable() const;
			bool isOtherRunable() const;
			void setOtherReadable(bool _newStatus);
			void setOtherWritable(bool _newStatus);
			void setOtherRunable(bool _newStatus);
			
			std::u32string getURight() const;
			std::string getRight() const;
	};
	std::ostream& operator <<(std::ostream &_os, const etk::FSNodeRight &_obj);
};

#endif

