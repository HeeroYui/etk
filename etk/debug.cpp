/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/debug.h>

int32_t etk::getLogId(void) {
	static int32_t g_val = etk::log::registerInstance("etk");
	return g_val;
}

