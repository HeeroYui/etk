/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/types.hpp>

#pragma once

namespace etk {
	namespace theme {
		/**
		 * @brief initialize the theme system
		 */
		void init();
		/**
		 * @brief un-initialize the theme system
		 */
		void unInit();
		/**
		 * @brief Set the Folder of a subset of a theme ...
		 * @param[in] _refName Theme cathegorie ex : "GUI" "SHADER" "DEFAULT" 
		 * @param[in] _folderName The associated folder of the Theme (like "myTheme/folder/folder2/")
		 */
		void setName(const etk::String& _refName, const etk::String& _folderName);
		/**
		 * @brief get the folder from a Reference theme
		 * @param[in] _refName Theme cathegorie ex : "GUI" "SHADER" "DEFAULT" 
		 * @return the path of the theme
		 */
		etk::String getName(const etk::String& _refName);
		/**
		 * @brief Set the default folder of a subset of a theme ...
		 * @param[in] _refName Theme cathegorie ex : "GUI" "SHADER" "DEFAULT" 
		 * @param[in] _folderName The associated default folder of the Theme (like "myTheme/color/default/")
		 */
		void setNameDefault(const etk::String& _refName, const etk::String& _folderName);
		/**
		 * @brief get the default folder from a Reference theme 
		 * @param[in] _refName Theme cathegorie ex : "GUI" "SHADER" "DEFAULT" 
		 * @return the path of the theme
		 */
		etk::String getNameDefault(const etk::String& _refName);
		/**
		 * @brief Get the list of all the theme folder availlable in the user Home/appl
		 * @return The list of elements
		 */
		etk::Vector<etk::String> list();
	}
}

