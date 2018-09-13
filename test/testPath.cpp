/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */

#include <etest/etest.hpp>
#include <test-debug/debug.hpp>
#include <etk/path/Path.hpp>
#include <etk/path/fileSystem.hpp>

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
	EXPECT_EQ(path.getString(), "/k");
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
	path = "/home/plouf/plaf/./././pluf/plouc/../../../mioch/narn////miasm/../";
	EXPECT_EQ(path.getString(), "/home/plouf/mioch/narn");
	path = "../../hello";
	EXPECT_EQ(path.getString(), "../../hello");
}

TEST(TestPath, fileName) {
	etk::Path path("/home/plouf.pdf");
	EXPECT_EQ(path.getFileName(), "plouf.pdf");
	path = "plouf.pdf";
	EXPECT_EQ(path.getFileName(), "plouf.pdf");
	path = "/hello/plouf";
	EXPECT_EQ(path.getFileName(), "plouf");
	path = "/plouf";
	EXPECT_EQ(path.getFileName(), "plouf");
	path = "/";
	EXPECT_EQ(path.getFileName(), "");
}

TEST(TestPath, extention) {
	etk::Path path("/home/plouf.pdf");
	EXPECT_EQ(path.getExtention(), "pdf");
	path = "plouf.ma-super-extention";
	EXPECT_EQ(path.getExtention(), "ma-super-extention");
	path = "/home/plouf";
	EXPECT_EQ(path.getExtention(), "");
	path = "/ho.me/plouf";
	EXPECT_EQ(path.getExtention(), "");
	path = "/ho.me/.plouf";
	EXPECT_EQ(path.getExtention(), "");
	path = ".plouf";
	EXPECT_EQ(path.getExtention(), "");
	path = ".plouf.hello.pdf";
	EXPECT_EQ(path.getExtention(), "pdf");
}

TEST(TestPath, parent) {
	etk::Path path("/home/plouf.pdf");
	EXPECT_EQ(path.getParent(), "/home/");
	path = "/home/plouf/plaf/plop";
	EXPECT_EQ(path.getParent(), "/home/plouf/plaf");
	path.parent();
	EXPECT_EQ(path.getString(), "/home/plouf/plaf");
	path = "/";
	EXPECT_EQ(path.getParent(), "/");
}

TEST(TestPath, getRelative) {
	etk::Path path("plouf.pdf");
	EXPECT_EQ(path.getRelative(), "plouf.pdf");
	path = "/ici/plouf.pdf";
	etk::String test;
	auto elements = etk::path::getExecutionPath().getString().split('/');
	for (size_t iii=0; iii<elements.size(); ++iii) {
		if (elements[iii].size() == 0) {
			continue;
		}
		test += "../";
	}
	test += "ici/plouf.pdf";
	EXPECT_EQ(path.getRelative(), test);
}

TEST(TestPath, getAbsolute) {
	etk::Path path("plouf.pdf");
	EXPECT_EQ(path.getAbsolute(), (etk::path::getExecutionPath() / "plouf.pdf").getString());
	path = "/plouf.pdf";
	EXPECT_EQ(path.getAbsolute(), "/plouf.pdf");
}

TEST(TestPath, GetHomePath) {
	etk::String basicPath = getenv("HOME");
	etk::Path path("~");
	EXPECT_EQ(path.getString(), basicPath);
	basicPath += "/plouf.php";
	path = "~/plouf.php";
	EXPECT_EQ(path.getString(), basicPath);
}