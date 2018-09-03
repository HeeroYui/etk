/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>

namespace etk {
	namespace io {
		/**
		 * @brief Seek mode availlable (just to wrap it ...)
		 */
		enum class OpenMode {
			Read, //!< request File open in read
			Write, //!< request File open in write
			Append, //!< request File open in append
		};
		//! @not_in_doc
		etk::Stream& operator <<(etk::Stream &_os, const enum etk::io::OpenMode &_obj);
	}
}
