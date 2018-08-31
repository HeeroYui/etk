/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */

#include <etest/etest.hpp>
#include <test-debug/debug.hpp>
#include <etk/fileSystem/Path.hpp>

TEST(TestPath, defaultContructor) {
	etk::Path path;
	EXPECT_EQ(path.getType(), etk::fileSystem::Type::Unknow);
	EXPECT_EQ(path.get(), "");
}
