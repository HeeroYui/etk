/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <string>
/**
 * @brief basic namespace of the etk library. (it might contain all the etk fuctions/class/structures without macro)
 */
namespace etk {
	/**
	 * @brief Initialize etk
	 * @param[in] _argc Number of argument list
	 * @param[in] _argv List of arguments
	 */
	void init(int _argc, const char** _argv);
	
	/**
	 * @brief Get application name.
	 * @return The application name
	 */
	std::string getApplicationName();
}

