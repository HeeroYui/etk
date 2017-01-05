/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/types.hpp>
#include <test-debug/debug.hpp>
#include <vector>
#include <string>
#include <etk/Hash.hpp>
#include <etk/os/FSNode.hpp>
#include <etk/archive/Archive.hpp>
#include <etk/etk.hpp>
#include <etk/Color.hpp>
#include <etk/stdTools.hpp>
#include <string>

#define NAME "Empty"
#include <gtest/gtest.h>
#include "testArchive.hpp"
#include "testColor.hpp"
#include "testFSNode.hpp"
#include "testHash.hpp"
#include "testStdShared.hpp"

int main(int argc, const char *argv[]) {
	// init Google test :
	::testing::InitGoogleTest(&argc, const_cast<char **>(argv));
	// the only one init for etk:
	etk::init(argc, argv);
	etk::initDefaultFolder("ewolApplNoName");
	return RUN_ALL_TESTS();
}

