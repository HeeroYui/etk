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
	EXPECT_EQ(etk::theme::getDefaultName("AAA"), "");
	EXPECT_EQ(etk::theme::getName("AAA"), "aaa");
	etk::theme::unInit()
	EXPECT_EQ(etk::theme::getDefaultName("AAA"), "");
	EXPECT_EQ(etk::theme::getName("AAA"), "");
}

TEST(TestTheme, set) {
	etk::theme::init();
	etk::theme::setDefaultName("AAA", "aaa");
	EXPECT_EQ(etk::theme::getDefaultName("AAA"), "aaa");
	EXPECT_EQ(etk::theme::getName("AAA"), "aaa");
	etk::theme::unInit()
	EXPECT_EQ(etk::theme::getDefaultName("AAA"), "");
	EXPECT_EQ(etk::theme::getName("AAA"), "");
}

TEST(TestTheme, set2) {
	etk::theme::init();
	etk::theme::setDefaultName("AAA", "aaa");
	etk::theme::setName("AAA", "bbb");
	EXPECT_EQ(etk::theme::getDefaultName("AAA"), "aaa");
	EXPECT_EQ(etk::theme::getName("AAA"), "bbb");
	etk::theme::unInit()
}
