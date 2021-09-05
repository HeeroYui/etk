/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */

#include <etest/etest.hpp>
#include <test-debug/debug.hpp>
#include <etk/path/fileSystem.hpp>

TEST(TestFileSystem, checkHomePath) {
	etk::String basicPath = getenv("HOME");
	EXPECT_EQ(etk::path::getHomePath(), basicPath);
}

TEST(TestFileSystem, checkTmpPath) {
	EXPECT_EQ(etk::path::getTemporaryPath(), "/tmp");
}

TEST(TestFileSystem, getBinaryName) {
	EXPECT_EQ(etk::path::getBinaryName(), "etk-test");
}

TEST(TestFileSystem, getBinaryPath) {
	EXPECT_EQ(etk::path::getBinaryPath().getString().split('/').size() > 2, true);
}

TEST(TestFileSystem, randomProcessPath) {
	etk::Path path1 = etk::path::getTemporaryProcessPath();
	etk::Path path2 = etk::path::getTemporaryProcessPath();
	EXPECT_EQ(path1,path2);
}

TEST(TestFileSystem, randomPath) {
	etk::Path path1 = etk::path::getTemporaryRandomPath();
	etk::Path path2 = etk::path::getTemporaryRandomPath();
	EXPECT_NE(path1,path2);
}

TEST(TestFileSystem, create_and_remove_directory_relative) {
	etk::Path path = "hello";
	EXPECT_EQ(etk::path::exist(path), false);
	EXPECT_EQ(etk::path::makeDirectory(path), true);
	EXPECT_EQ(etk::path::exist(path), true);
	EXPECT_EQ(etk::path::makeDirectory(path), true);
	EXPECT_EQ(etk::path::removeDirectory(path), true);
	EXPECT_EQ(etk::path::exist(path), false);
}

TEST(TestFileSystem, createDirectory_relative_error) {
	etk::Path path = "hello/sdfsdf";
	EXPECT_EQ(etk::path::exist(path), false);
	EXPECT_EQ(etk::path::makeDirectory(path), false);
	EXPECT_EQ(etk::path::exist(path), false);
}

TEST(TestFileSystem, create_and_remove_directories) {
	etk::Path pathRandom = etk::path::getTemporaryRandomPath();
	etk::Path path = pathRandom / "eee" / "kjlk" / "kjhkjh";
	TEST_DEBUG("path tmp: " << path);
	EXPECT_EQ(etk::path::exist(path), false);
	EXPECT_EQ(etk::path::makeDirectories(path), true);
	EXPECT_EQ(etk::path::exist(path), true);
	EXPECT_EQ(etk::path::removeDirectories(pathRandom), true);
	EXPECT_EQ(etk::path::exist(pathRandom), false);
	EXPECT_EQ(etk::path::exist(path), false);
}

TEST(TestFileSystem, create_and_remove_directories_error) {
	etk::Path pathRandom = etk::path::getTemporaryRandomPath();
	etk::Path path = etk::Path("home") / "eee" / "kjlk" / "kjhkjh";
	TEST_DEBUG("path tmp: " << path);
	EXPECT_EQ(etk::path::exist(path), false);
	EXPECT_EQ(etk::path::makeDirectories(path), false);
	EXPECT_EQ(etk::path::exist(path), false);
}
/*
TEST(TestFileSystem, move_directory) {
	etk::Path pathRandom = etk::path::getTemporaryRandomPath();
	etk::Path path1 = pathRandom / "eee1";
	etk::Path path2 = pathRandom / "eee2";
	etk::Path offset = etk::Path("kjlk") / "kjhkjh";
	EXPECT_EQ(etk::path::exist(path1), false);
	EXPECT_EQ(etk::path::exist(path2), false);
	EXPECT_EQ(etk::path::exist(path1 / offset), false);
	EXPECT_EQ(etk::path::exist(path2 / offset), false);
	EXPECT_EQ(etk::path::makeDirectories(path1 / offset), true);
	EXPECT_EQ(etk::path::exist(path1), true);
	EXPECT_EQ(etk::path::exist(path2), false);
	EXPECT_EQ(etk::path::exist(path1 / offset), true);
	EXPECT_EQ(etk::path::exist(path2 / offset), false);
	EXPECT_EQ(etk::path::move(path1, path2), true);
	EXPECT_EQ(etk::path::exist(path1), false);
	EXPECT_EQ(etk::path::exist(path2), true);
	EXPECT_EQ(etk::path::exist(path1 / offset), false);
	EXPECT_EQ(etk::path::exist(path2 / offset), true);
	EXPECT_EQ(etk::path::removeDirectories(pathRandom), true);
	EXPECT_EQ(etk::path::exist(pathRandom), false);
}
*/
#include <unistd.h>

TEST(TestFileSystem, touch) {
	etk::Path pathRandom = etk::path::getTemporaryRandomPath();
	etk::Path path = pathRandom / "eee" / "kjlk" / "kjhkjh.txt";
	TEST_DEBUG("path tmp: " << path);
	EXPECT_EQ(etk::path::exist(path), false);
	// Touch a file in a unexisting path
	EXPECT_EQ(etk::path::touch(path), false);
	EXPECT_EQ(etk::path::makeDirectories(path.getParent()), true);
	EXPECT_EQ(etk::path::exist(path), false);
	// Touch a file in an existing path
	EXPECT_EQ(etk::path::touch(path), true);
	EXPECT_EQ(etk::path::exist(path), true);
	uint64_t touch1 = etk::path::getModifyTime(path);
	
	usleep(1000000);
	// Tich a file already existing
	EXPECT_EQ(etk::path::touch(path), true);
	EXPECT_EQ(etk::path::exist(path), true);
	uint64_t touch2 = etk::path::getModifyTime(path);
	EXPECT_NE(touch1, touch2);
	EXPECT_EQ(etk::path::removeDirectories(pathRandom), true);
	EXPECT_EQ(etk::path::exist(pathRandom), false);
	EXPECT_EQ(etk::path::exist(path), false);
}

TEST(TestFileSystem, move_file) {
	etk::Path pathRandom = etk::path::getTemporaryRandomPath();
	etk::Path path1 = pathRandom / "eee1.txt";
	etk::Path path2 = pathRandom / "eee2.mov";
	EXPECT_EQ(etk::path::exist(path1), false);
	EXPECT_EQ(etk::path::exist(path2), false);
	EXPECT_EQ(etk::path::makeDirectories(pathRandom), true);
	EXPECT_EQ(etk::path::touch(path1), true);
	EXPECT_EQ(etk::path::exist(path1), true);
	EXPECT_EQ(etk::path::exist(path2), false);
	EXPECT_EQ(etk::path::move(path1, path2), true);
	EXPECT_EQ(etk::path::exist(path1), false);
	EXPECT_EQ(etk::path::exist(path2), true);
	/*
	EXPECT_EQ(etk::path::removeDirectories(pathRandom), true);
	EXPECT_EQ(etk::path::exist(pathRandom), false);
	*/
}
