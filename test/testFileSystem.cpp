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

TEST(TestFileSystem, checkTmpPath) {
	EXPECT_EQ(etk::fs::getTemporaryPath(), "/tmp");
}

TEST(TestFileSystem, getBinaryName) {
	EXPECT_EQ(etk::fs::getBinaryName(), "etk-test");
}

TEST(TestFileSystem, getBinaryPath) {
	EXPECT_EQ(etk::fs::getBinaryPath().getString().split('/').size() > 2, true);
}

TEST(TestFileSystem, randomProcessPath) {
	etk::Path path1 = etk::fs::getTemporaryProcessPath();
	etk::Path path2 = etk::fs::getTemporaryProcessPath();
	EXPECT_EQ(path1,path2);
}

TEST(TestFileSystem, randomPath) {
	etk::Path path1 = etk::fs::getTemporaryRandomPath();
	etk::Path path2 = etk::fs::getTemporaryRandomPath();
	EXPECT_NE(path1,path2);
}

TEST(TestFileSystem, create_and_remove_directory_relative) {
	etk::Path path = "hello";
	EXPECT_EQ(etk::fs::exist(path), false);
	EXPECT_EQ(etk::fs::makeDirectory(path), true);
	EXPECT_EQ(etk::fs::exist(path), true);
	EXPECT_EQ(etk::fs::makeDirectory(path), true);
	EXPECT_EQ(etk::fs::removeDirectory(path), true);
	EXPECT_EQ(etk::fs::exist(path), false);
}

TEST(TestFileSystem, createDirectory_relative_error) {
	etk::Path path = "hello/sdfsdf";
	EXPECT_EQ(etk::fs::exist(path), false);
	EXPECT_EQ(etk::fs::makeDirectory(path), false);
	EXPECT_EQ(etk::fs::exist(path), false);
}

TEST(TestFileSystem, create_and_remove_directories) {
	etk::Path pathRandom = etk::fs::getTemporaryRandomPath();
	etk::Path path = pathRandom / "eee" / "kjlk" / "kjhkjh";
	TEST_DEBUG("path tmp: " << path);
	EXPECT_EQ(etk::fs::exist(path), false);
	EXPECT_EQ(etk::fs::makeDirectories(path), true);
	EXPECT_EQ(etk::fs::exist(path), true);
	EXPECT_EQ(etk::fs::removeDirectories(pathRandom), true);
	EXPECT_EQ(etk::fs::exist(pathRandom), false);
	EXPECT_EQ(etk::fs::exist(path), false);
}

TEST(TestFileSystem, create_and_remove_directories_error) {
	etk::Path pathRandom = etk::fs::getTemporaryRandomPath();
	etk::Path path = etk::Path("home") / "eee" / "kjlk" / "kjhkjh";
	TEST_DEBUG("path tmp: " << path);
	EXPECT_EQ(etk::fs::exist(path), false);
	EXPECT_EQ(etk::fs::makeDirectories(path), false);
	EXPECT_EQ(etk::fs::exist(path), false);
}

TEST(TestFileSystem, move_directory) {
	etk::Path pathRandom = etk::fs::getTemporaryRandomPath();
	etk::Path path1 = pathRandom / "eee1";
	etk::Path path2 = pathRandom / "eee2";
	etk::Path offset = etk::Path("kjlk") / "kjhkjh";
	EXPECT_EQ(etk::fs::exist(path1), false);
	EXPECT_EQ(etk::fs::exist(path2), false);
	EXPECT_EQ(etk::fs::exist(path1 / offset), false);
	EXPECT_EQ(etk::fs::exist(path2 / offset), false);
	EXPECT_EQ(etk::fs::makeDirectories(path1 / offset), true);
	EXPECT_EQ(etk::fs::exist(path1), true);
	EXPECT_EQ(etk::fs::exist(path2), false);
	EXPECT_EQ(etk::fs::exist(path1 / offset), true);
	EXPECT_EQ(etk::fs::exist(path2 / offset), false);
	EXPECT_EQ(etk::fs::move(path1, path2), true);
	EXPECT_EQ(etk::fs::exist(path1), false);
	EXPECT_EQ(etk::fs::exist(path2), true);
	EXPECT_EQ(etk::fs::exist(path1 / offset), false);
	EXPECT_EQ(etk::fs::exist(path2 / offset), true);
	EXPECT_EQ(etk::fs::removeDirectories(pathRandom), true);
	EXPECT_EQ(etk::fs::exist(pathRandom), false);
}

TEST(TestFileSystem, touch) {
	etk::Path pathRandom = etk::fs::getTemporaryRandomPath();
	etk::Path path = pathRandom / "eee" / "kjlk" / "kjhkjh.txt";
	TEST_DEBUG("path tmp: " << path);
	EXPECT_EQ(etk::fs::exist(path), false);
	EXPECT_EQ(etk::fs::touch(path), false);
	EXPECT_EQ(etk::fs::makeDirectories(path.getParent()), true);
	EXPECT_EQ(etk::fs::exist(path), false);
	EXPECT_EQ(etk::fs::touch(path), true);
	EXPECT_EQ(etk::fs::exist(path), true);
	uint64_t touch1 = etk::fs::getModifyTime(path);
	EXPECT_EQ(etk::fs::touch(path), true);
	EXPECT_EQ(etk::fs::exist(path), true);
	uint64_t touch2 = etk::fs::getModifyTime(path);
	EXPECT_NE(touch1, touch2);
	/*
	EXPECT_EQ(etk::fs::removeDirectories(pathRandom), true);
	EXPECT_EQ(etk::fs::exist(pathRandom), false);
	EXPECT_EQ(etk::fs::exist(path), false);
	*/
}

/*
TEST(TestFileSystem, move_file) {
	etk::Path pathRandom = etk::fs::getTemporaryRandomPath();
	etk::Path path1 = pathRandom / "eee1.txt";
	etk::Path path2 = pathRandom / "eee2.mov";
	EXPECT_EQ(etk::fs::exist(path1), false);
	EXPECT_EQ(etk::fs::exist(path2), false);
	EXPECT_EQ(etk::fs::touch(path1), true);
	EXPECT_EQ(etk::fs::exist(path1), true);
	EXPECT_EQ(etk::fs::exist(path2), false);
	EXPECT_EQ(etk::fs::move(path1, path2), true);
	EXPECT_EQ(etk::fs::exist(path1), false);
	EXPECT_EQ(etk::fs::exist(path2), true);
	EXPECT_EQ(etk::fs::removeDirectories(pathRandom), true);
	EXPECT_EQ(etk::fs::exist(pathRandom), false);
}
*/