/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */

#include <gtest/gtest.h>

#include <etk/Map.hpp>
#include <test-debug/debug.hpp>
#define NAME "MAP_unorderer"

TEST(TestEtkMap_unordered, Creation) {
	etk::Map<etk::String, etk::String> testData(0,false);
	EXPECT_EQ(testData.size(), 0);
}

TEST(TestEtkMap_unordered, AddElement) {
	etk::Map<etk::String, etk::String> testData(0,false);
	testData.add("TEST", "testData");
	testData.add("TEST2", "22222222222222222");
	testData.add("TEST4", "4444444444444444444");
	testData.add("TEST3", "3333333333");
	testData.add("TEST1", "11111111111");
	testData.add("TEST55", "555555555555555((((5555");
	EXPECT_EQ(testData.size(), 6);
	EXPECT_EQ(testData["TEST"], "testData");
	EXPECT_EQ(testData["TEST3"], "3333333333");
}

TEST(TestEtkMap_unordered, OverWriteElement) {
	etk::Map<etk::String, etk::String> testData(0,false);
	testData.add("TEST", "testData");
	testData.add("TEST2", "22222222222222222");
	testData.add("TEST4", "4444444444444444444");
	testData.add("TEST3", "3333333333");
	testData.add("TEST1", "11111111111");
	testData.add("TEST55", "555555555555555((((5555");
	EXPECT_EQ(testData.size(), 6);
	testData.add("TEST", "testData22");
	EXPECT_EQ(testData.size(), 6);
	EXPECT_EQ(testData["TEST"], "testData22");
}

TEST(TestEtkMap_unordered, RemoveElement) {
	etk::Map<etk::String, etk::String> testData(0,false);
	testData.add("TEST", "testData");
	testData.add("TEST2", "22222222222222222");
	testData.add("TEST4", "4444444444444444444");
	testData.add("TEST3", "3333333333");
	testData.add("TEST1", "11111111111");
	testData.add("TEST55", "555555555555555((((5555");
	EXPECT_EQ(testData.size(), 6);
	testData.erase("TEST1");
	EXPECT_EQ(testData.size(), 5);
}

TEST(TestEtkMap_unordered, ExistElement) {
	etk::Map<etk::String, etk::String> testData(0,false);
	testData.add("TEST", "testData");
	testData.add("TEST2", "22222222222222222");
	EXPECT_EQ(testData.exist("TEST"), true);
	EXPECT_EQ(testData.exist("Tlskdfjgmsqlkdfjgmlqskdfg"), false);
}

TEST(TestEtkMap_unordered, clear) {
	etk::Map<etk::String, etk::String> testData(0,false);
	testData.add("TEST", "1");
	testData.add("TEST2", "2");
	EXPECT_EQ(testData.size(), 2);
	testData.clear();
	EXPECT_EQ(testData.size(), 0);
}

TEST(TestEtkMap_unordered, getKey) {
	etk::Map<etk::String, etk::String> testData(0,false);
	testData.add("TEST", "1");
	testData.add("TEST2", "2");
	testData.add("TEST3", "3");
	EXPECT_EQ(testData.getKey(1), "TEST2");
}

TEST(TestEtkMap_unordered, getKeys) {
	etk::Map<etk::String, etk::String> testData(0,false);
	testData.add("TEST", "1");
	testData.add("TEST2", "2");
	testData.add("TEST3", "3");
	etk::Vector<etk::String> list = testData.getKeys();
	EXPECT_EQ(list.size(), 3);
	EXPECT_EQ(list[0], "TEST");
	EXPECT_EQ(list[1], "TEST2");
	EXPECT_EQ(list[2], "TEST3");
}
