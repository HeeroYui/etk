/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/types.hpp>
#include <test-debug/debug.hpp>
#include <etk/Vector.hpp>
#include <etk/String.hpp>
#include <etk/etk.hpp>
#include <etk/stdTools.hpp>
#include <etk/String.hpp>


#include <etest/etest.hpp>

int main(int argc, const char *argv[]) {
	// init test engine:
	etk::init(argc, argv);
	etest::init(argc, argv);
	TEST_INFO("TEST ETK");
	int out = RUN_ALL_TESTS();
	etest::unInit();
	etk::unInit();
	return out;
}
