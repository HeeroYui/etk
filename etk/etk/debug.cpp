/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/debug.hpp>

int32_t etk::getLogId() {
	static int32_t g_val = elog::registerInstance("etk");
	return g_val;
}

