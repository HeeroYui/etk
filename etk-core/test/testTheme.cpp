/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */

#include <etest/etest.hpp>
#include <test-debug/debug.hpp>
#include <etk/theme/theme.hpp>

TEST(TestTheme, init_uninit) {
	etk::theme::init();
	etk::theme::setName("AAA", "aaa");
	EXPECT_EQ(etk::theme::getNameDefault("AAA"), etk::Path("default"));
	EXPECT_EQ(etk::theme::getName("AAA"), etk::Path("aaa"));
	etk::theme::unInit();
	EXPECT_EQ(etk::theme::getNameDefault("AAA"), etk::Path("default"));
	EXPECT_EQ(etk::theme::getName("AAA"), etk::Path());
}

TEST(TestTheme, set) {
	etk::theme::init();
	etk::theme::setNameDefault("AAA", etk::Path("aaa"));
	EXPECT_EQ(etk::theme::getNameDefault("AAA"), etk::Path("aaa"));
	EXPECT_EQ(etk::theme::getName("AAA"), etk::Path());
	etk::theme::unInit();
	EXPECT_EQ(etk::theme::getNameDefault("AAA"), etk::Path("default"));
	EXPECT_EQ(etk::theme::getName("AAA"), etk::Path());
}

TEST(TestTheme, set2) {
	etk::theme::init();
	etk::theme::setNameDefault("AAA", etk::Path("aaa"));
	etk::theme::setName("AAA", etk::Path("bbb"));
	EXPECT_EQ(etk::theme::getNameDefault("AAA"), etk::Path("aaa"));
	EXPECT_EQ(etk::theme::getName("AAA"), etk::Path("bbb"));
	etk::theme::unInit();
}
