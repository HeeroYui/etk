/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etest/debug.hpp>

int32_t etest::getLogId() {
	static int32_t g_val = elog::registerInstance("etest");
	return g_val;
}

