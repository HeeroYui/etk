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
	EXPECT_EQ(path.getString(), "");
	EXPECT_EQ(path.isRelative(), true);
	EXPECT_EQ(path.isAbsolute(), false);
}

TEST(TestPath, basic_relatif) {
	etk::Path path("hello");
	EXPECT_EQ(path.getSring(), "hello");
	EXPECT_EQ(path.isRelative(), true);
	EXPECT_EQ(path.isAbsolute(), false);
}

TEST(TestPath, basic_relatif_2) {
	etk::Path path("hello/plouf");
	EXPECT_EQ(path.getSring(), "hello/plouf");
	EXPECT_EQ(path.isRelative(), true);
	EXPECT_EQ(path.isAbsolute(), false);
}

TEST(TestPath, basic_relatif_2_windows) {
	etk::Path path("hello\\plouf");
	EXPECT_EQ(path.getSring(), "hello/plouf");
	EXPECT_EQ(path.isRelative(), true);
	EXPECT_EQ(path.isAbsolute(), false);
}

TEST(TestPath, basic_absolute) {
	etk::Path path("/");
	EXPECT_EQ(path.getSring(), "/");
	EXPECT_EQ(path.getSringWindows(), "\\");
	EXPECT_EQ(path.isRelative(), false);
	EXPECT_EQ(path.isAbsolute(), true);
}

TEST(TestPath, basic_absolute_windows) {
	etk::Path path("k:\\");
	EXPECT_EQ(path.getSring(), "/k/");
	EXPECT_EQ(path.getSringWindows(), "k:\\");
	EXPECT_EQ(path.isRelative(), false);
	EXPECT_EQ(path.isAbsolute(), true);
}

TEST(TestPath, basic_absolute_2) {
	etk::Path path("/home/heero/hello/plouf");
	EXPECT_EQ(path.getSring(), "/home/heero/hello/plouf");
	EXPECT_EQ(path.getSringWindows(), "\\home\\heero\\hello\\plouf");
	EXPECT_EQ(path.isRelative(), false);
	EXPECT_EQ(path.isAbsolute(), true);
}

TEST(TestPath, basic_absolute_2_windows) {
	etk::Path path("G:\\hello\\plouf");
	EXPECT_EQ(path.getSring(), "/g/hello/plouf");
	EXPECT_EQ(path.getSringWindows(), "g:\\hello\\plouf");
	EXPECT_EQ(path.isRelative(), false);
	EXPECT_EQ(path.isAbsolute(), true);
}
