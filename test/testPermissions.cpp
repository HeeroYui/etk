/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */

#include <etest/etest.hpp>
#include <test-debug/debug.hpp>
#include <etk/fileSystem/Permissions.hpp>

TEST(TestPermission, defaultContructor) {
	etk::fileSystem::Permissions permission;
	EXPECT_EQ(permission.isUserReadable(), false);
	EXPECT_EQ(permission.isUserWritable(), false);
	EXPECT_EQ(permission.isUserRunable(), false);
	EXPECT_EQ(permission.isGroupReadable(), false);
	EXPECT_EQ(permission.isGroupWritable(), false);
	EXPECT_EQ(permission.isGroupRunable(), false);
	EXPECT_EQ(permission.isOtherReadable(), false);
	EXPECT_EQ(permission.isOtherWritable(), false);
	EXPECT_EQ(permission.isOtherRunable(), false);
	EXPECT_EQ(permission.getRight(), "---------");
}


TEST(TestPermission, fullright) {
	etk::fileSystem::Permissions permission(0777);
	EXPECT_EQ(permission.isUserReadable(), true);
	EXPECT_EQ(permission.isUserWritable(), true);
	EXPECT_EQ(permission.isUserRunable(), true);
	EXPECT_EQ(permission.isGroupReadable(), true);
	EXPECT_EQ(permission.isGroupWritable(), true);
	EXPECT_EQ(permission.isGroupRunable(), true);
	EXPECT_EQ(permission.isOtherReadable(), true);
	EXPECT_EQ(permission.isOtherWritable(), true);
	EXPECT_EQ(permission.isOtherRunable(), true);
	EXPECT_EQ(permission.getRight(), "rwxrwxrwx");
}


TEST(TestPermission, user) {
	etk::fileSystem::Permissions permission(0700);
	EXPECT_EQ(permission.isUserReadable(), true);
	EXPECT_EQ(permission.isUserWritable(), true);
	EXPECT_EQ(permission.isUserRunable(), true);
	EXPECT_EQ(permission.isGroupReadable(), false);
	EXPECT_EQ(permission.isGroupWritable(), false);
	EXPECT_EQ(permission.isGroupRunable(), false);
	EXPECT_EQ(permission.isOtherReadable(), false);
	EXPECT_EQ(permission.isOtherWritable(), false);
	EXPECT_EQ(permission.isOtherRunable(), false);
	EXPECT_EQ(permission.getRight(), "rwx------");
}


TEST(TestPermission, group) {
	etk::fileSystem::Permissions permission(0070);
	EXPECT_EQ(permission.isUserReadable(), false);
	EXPECT_EQ(permission.isUserWritable(), false);
	EXPECT_EQ(permission.isUserRunable(), false);
	EXPECT_EQ(permission.isGroupReadable(), true);
	EXPECT_EQ(permission.isGroupWritable(), true);
	EXPECT_EQ(permission.isGroupRunable(), true);
	EXPECT_EQ(permission.isOtherReadable(), false);
	EXPECT_EQ(permission.isOtherWritable(), false);
	EXPECT_EQ(permission.isOtherRunable(), false);
	EXPECT_EQ(permission.getRight(), "---rwx---");
}


TEST(TestPermission, other) {
	etk::fileSystem::Permissions permission(0007);
	EXPECT_EQ(permission.isUserReadable(), false);
	EXPECT_EQ(permission.isUserWritable(), false);
	EXPECT_EQ(permission.isUserRunable(), false);
	EXPECT_EQ(permission.isGroupReadable(), false);
	EXPECT_EQ(permission.isGroupWritable(), false);
	EXPECT_EQ(permission.isGroupRunable(), false);
	EXPECT_EQ(permission.isOtherReadable(), true);
	EXPECT_EQ(permission.isOtherWritable(), true);
	EXPECT_EQ(permission.isOtherRunable(), true);
	EXPECT_EQ(permission.getRight(), "------rwx");
}

