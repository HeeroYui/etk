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
		enum class SeekMode {
			Start, //!< request seek position start at the START of the file
			End, //!< request seek position start at the END of the file
			Current, //!< request seek position start at the CURRENT position in the file
		};
		//! @not_in_doc
		etk::Stream& operator <<(etk::Stream &_os, const enum etk::io::SeekMode &_obj);
	}
}
