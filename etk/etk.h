/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ETK_H__
#define __ETK_H__

#include <string>

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

#endif
