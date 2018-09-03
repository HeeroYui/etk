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
	EXPECT_EQ(path.isRelative(), false);
	EXPECT_EQ(path.isAbsolute(), false);
}

TEST(TestPath, basic_relatif) {
	etk::Path path("hello");
	EXPECT_EQ(path.getString(), "hello");
	EXPECT_EQ(path.isRelative(), true);
	EXPECT_EQ(path.isAbsolute(), false);
}

TEST(TestPath, basic_relatif_2) {
	etk::Path path("hello/plouf");
	EXPECT_EQ(path.getString(), "hello/plouf");
	EXPECT_EQ(path.isRelative(), true);
	EXPECT_EQ(path.isAbsolute(), false);
}

TEST(TestPath, basic_relatif_2_windows) {
	etk::Path path("hello\\plouf");
	EXPECT_EQ(path.getString(), "hello/plouf");
	EXPECT_EQ(path.isRelative(), true);
	EXPECT_EQ(path.isAbsolute(), false);
}

TEST(TestPath, basic_absolute) {
	etk::Path path("/");
	EXPECT_EQ(path.getString(), "/");
	EXPECT_EQ(path.getStringWindows(), "\\");
	EXPECT_EQ(path.isRelative(), false);
	EXPECT_EQ(path.isAbsolute(), true);
}

TEST(TestPath, basic_absolute_windows) {
	etk::Path path("k:\\");
	EXPECT_EQ(path.getString(), "/k/");
	EXPECT_EQ(path.getStringWindows(), "k:\\");
	EXPECT_EQ(path.isRelative(), false);
	EXPECT_EQ(path.isAbsolute(), true);
}

TEST(TestPath, basic_absolute_2) {
	etk::Path path("/home/heero/hello/plouf");
	EXPECT_EQ(path.getString(), "/home/heero/hello/plouf");
	EXPECT_EQ(path.getStringWindows(), "\\home\\heero\\hello\\plouf");
	EXPECT_EQ(path.isRelative(), false);
	EXPECT_EQ(path.isAbsolute(), true);
}

TEST(TestPath, basic_absolute_2_windows) {
	etk::Path path("G:\\hello\\plouf");
	EXPECT_EQ(path.getString(), "/g/hello/plouf");
	EXPECT_EQ(path.getStringWindows(), "g:\\hello\\plouf");
	EXPECT_EQ(path.isRelative(), false);
	EXPECT_EQ(path.isAbsolute(), true);
}

TEST(TestPath, assignation) {
	etk::Path path;
	EXPECT_EQ(path.getString(), "");
	path = "/home/plouf";
	EXPECT_EQ(path.getString(), "/home/plouf");
	path = "rastapopoulos";
	EXPECT_EQ(path.getString(), "rastapopoulos");
	path = etk::Path("/home/plouf");
	EXPECT_EQ(path.getString(), "/home/plouf");
	path = etk::Path("rastapopoulos");
	EXPECT_EQ(path.getString(), "rastapopoulos");
}


TEST(TestPath, simplification) {
	etk::Path path("/home/../plouf");
	EXPECT_EQ(path.getString(), "/plouf");
	path = "/home/plouf/../";
	EXPECT_EQ(path.getString(), "/home");
	path = "/home/plouf/plaf/./././pluf/plouc/../../../mioch/narn/miasm/../";
	EXPECT_EQ(path.getString(), "/home/plouf/mioch/narn");
}
