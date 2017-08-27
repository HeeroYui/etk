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

#include <etk/os/FSNode.hpp>
#include <gtest/gtest.h>

int main(int argc, const char *argv[]) {
	// init Google test :
	::testing::InitGoogleTest(&argc, const_cast<char **>(argv));
	// the only one init for etk:
	etk::init(argc, argv);
	etk::initDefaultFolder("ewolApplNoName");
	//testRegExp();
	return RUN_ALL_TESTS();
}

