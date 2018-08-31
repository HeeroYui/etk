/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */

#include <etest/etest.hpp>
#include <test-debug/debug.hpp>
#include <etk/fileSystem/filesystem.hpp>

TEST(TestFileSystem, checkHomePath) {
	EXPECT_EQ(etk::fileSystem::getHomePath(), "/home/heero");
}

TEST(TestEtkFSNode, checkHomePath) {
	etk::String homePath = etk::FSNodeGetHomePath();
	EXPECT_EQ(homePath, "/home/heero");
	etk::FSNode myNodeTest1("HOME:filePresent.txt");
	EXPECT_EQ(myNodeTest1.getNameFile(), "filePresent.txt");
	EXPECT_EQ(myNodeTest1.getFileSystemName(), homePath + "/filePresent.txt");
	EXPECT_EQ(myNodeTest1.getNameFolder(), "/home/heero");
	etk::FSNode myNodeTest2("HOME:/filePresent.txt");
	EXPECT_EQ(myNodeTest2.getNameFile(), "filePresent.txt");
	EXPECT_EQ(myNodeTest2.getFileSystemName(), homePath + "/filePresent.txt");
	EXPECT_EQ(myNodeTest2.getNameFolder(), "/home/heero");
	etk::FSNode myNodeTest3("~/filePresent.txt");
	EXPECT_EQ(myNodeTest3.getNameFile(), "filePresent.txt");
	EXPECT_EQ(myNodeTest3.getFileSystemName(), homePath + "/filePresent.txt");
	EXPECT_EQ(myNodeTest3.getNameFolder(), "/home/heero");