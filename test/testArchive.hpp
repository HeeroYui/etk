/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */

#include <gtest/gtest.h>
#undef NAME
#define NAME "Archive"

#ifdef ETK_BUILD_MINIZIP

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

#endif
