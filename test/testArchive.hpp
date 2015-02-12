/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <gtest/gtest.h>
#undef NAME
#define NAME "Archive"

#undef __class__
#define __class__	"etktest"

TEST(TestEtkArchive, CreationWrong) {
	etk::Archive* tmpArchive = etk::Archive::load("nonExistantFile.zip");
	EXPECT_NE(tmpArchive, nullptr);
}

/*
TEST(TestEtkArchive, Display) {
	etk::Archive* tmpArchive = etk::Archive::load("nonExistantFile.zip");
	ASSERT_NEQ(tmpArchive, nullptr);
	tmpArchive->display();
}
*/