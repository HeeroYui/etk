/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */

#include <etest/etest.hpp>

#include <etk/Map.hpp>
#include <test-debug/debug.hpp>
#define NAME "Map"

TEST(TestEtkMap, Creation) {
	etk::Map<uint32_t, etk::String> testData(0,true);
	EXPECT_EQ(testData.size(), 0);
}

TEST(TestEtkMap, add_ordered) {
	etk::Map<uint32_t, etk::String> testData(0,true);
	EXPECT_EQ(testData.size(), 0);
	testData.add(2, "a 2");
	TEST_INFO("--------------------");
	for (size_t iii=0; iii<testData.size(); ++iii) {
		TEST_INFO("    " << iii << " " << testData.getKey(iii));
	}
	testData.add(19, "b 19");
	TEST_INFO("--------------------");
	for (size_t iii=0; iii<testData.size(); ++iii) {
		TEST_INFO("    " << iii << " " << testData.getKey(iii));
	}
	testData.add(1, "c 1");
	TEST_INFO("--------------------");
	for (size_t iii=0; iii<testData.size(); ++iii) {
		TEST_INFO("    " << iii << " " << testData.getKey(iii));
	}
	testData.add(5, "d 5");
	TEST_INFO("--------------------");
	for (size_t iii=0; iii<testData.size(); ++iii) {
		TEST_INFO("    " << iii << " " << testData.getKey(iii));
	}
	testData.add(66, "e 66");
	TEST_INFO("--------------------");
	for (size_t iii=0; iii<testData.size(); ++iii) {
		TEST_INFO("    " << iii << " " << testData.getKey(iii));
	}
	EXPECT_EQ(testData.size(), 5);
	EXPECT_EQ(testData[1], "c 1");
	EXPECT_EQ(testData.getValue(0), "c 1");
}
