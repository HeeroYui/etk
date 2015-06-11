/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <test-debug/debug.h>

int32_t test::getLogId() {
	static int32_t g_val = etk::log::registerInstance("test");
	return g_val;
}

