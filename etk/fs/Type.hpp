/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/types.hpp>
#include <etk/Stream.hpp>

#pragma once

namespace etk {
	namespace fs {
		/**
		 * @brief Type of the file/folder/... accessible in the Node
		 */
		enum class Type {
			Unknow, //!< Unknow type of the node (many time no file name seted)
			// user might done abstraction ==> acces of the sdcard when possible ...
			Direct, //!< Access at the file System with a direct naming like "/home/plop/xxx.txt"
			// depend on case
			//     - PC      : ~/
			//     - Android : /sdcard/
			//     - Apple   : ????
			Home, //!< acces at the home path of the system (with name of the current user)
			// depend of the case
			//     - PC      : /usr/shared/programName/
			//     - Android : Internal at the executable file (pointer on static area)
			//     - Apple   : Internal at the executable file
			Data, //!< Access on the application data (internal application data are the one provided with the binary)
			// depend on case
			//     - PC      : ~/.local/programName/
			//     - Android : /data/data/programName/files/
			//     - Apple   : ????
			UserData, //!< Access on the user application data (where the data are stored when the application stop)
			// depend on case
			//     - PC      : ~/.programName/cache/
			//     - Android : /data/data/programName/cache/
			//     - Apple   : ????
			Cache, //!< Access on the application temporary path (remove when user want and whe the compter restart or have not enought memory)
			// depend on case
			//     - try on USER_DATA:/theme/themeName/xxx
			//     - try on DATA:/theme/themeName/xxx
			//     and jump to the default theme file
			//     - try on USER_DATA:/theme/default/xxx
			//     - try on DATA:/theme/default/xxx
			Theme, //!< Theme area
			ThemeData //!< Theme data area
		};
	}
	
	//! @not_in_doc
	etk::Stream& operator <<(etk::Stream &_os, const etk::fs::Type &_obj);
}

