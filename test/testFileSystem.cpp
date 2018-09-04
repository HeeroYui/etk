/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */

#include <etest/etest.hpp>
#include <test-debug/debug.hpp>
#include <etk/fs/fileSystem.hpp>

TEST(TestFileSystem, checkHomePath) {
	etk::String basicPath = getenv("HOME");
	EXPECT_EQ(etk::fs::getHomePath(), basicPath);
}

