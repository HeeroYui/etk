/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <gtest/gtest.h>

#undef NAME
#define NAME "Hash"

#undef __class__
#define __class__	"etktest"

TEST(TestEtkHash, Creation) {
	etk::Hash<std::string> testData;
	EXPECT_EQ(testData.size(), 0);
}

TEST(TestEtkHash, AddElement) {
	etk::Hash<std::string> testData;
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

TEST(TestEtkHash, OverWriteElement) {
	etk::Hash<std::string> testData;
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

TEST(TestEtkHash, RemoveElement) {
	etk::Hash<std::string> testData;
	testData.add("TEST", "testData");
	testData.add("TEST2", "22222222222222222");
	testData.add("TEST4", "4444444444444444444");
	testData.add("TEST3", "3333333333");
	testData.add("TEST1", "11111111111");
	testData.add("TEST55", "555555555555555((((5555");
	EXPECT_EQ(testData.size(), 6);
	testData.remove("TEST1");
	EXPECT_EQ(testData.size(), 5);
}

TEST(TestEtkHash, ExistElement) {
	etk::Hash<std::string> testData;
	testData.add("TEST", "testData");
	testData.add("TEST2", "22222222222222222");
	EXPECT_EQ(testData.exist("TEST"), true);
	EXPECT_EQ(testData.exist("Tlskdfjgmsqlkdfjgmlqskdfg"), false);
}

TEST(TestEtkHash, clear) {
	etk::Hash<std::string> testData;
	testData.add("TEST", "1");
	testData.add("TEST2", "2");
	EXPECT_EQ(testData.size(), 2);
	testData.clear();
	EXPECT_EQ(testData.size(), 0);
}

TEST(TestEtkHash, getKey) {
	etk::Hash<std::string> testData;
	testData.add("TEST", "1");
	testData.add("TEST2", "2");
	testData.add("TEST3", "3");
	EXPECT_EQ(testData.getKey(1), "TEST2");
}

TEST(TestEtkHash, getKeys) {
	etk::Hash<std::string> testData;
	testData.add("TEST", "1");
	testData.add("TEST2", "2");
	testData.add("TEST3", "3");
	std::vector<std::string> list = testData.getKeys();
	EXPECT_EQ(list.size(), 3);
	EXPECT_EQ(list[0], "TEST");
	EXPECT_EQ(list[1], "TEST2");
	EXPECT_EQ(list[2], "TEST3");
}
