/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */

#include <etest/etest.hpp>

#include <etk/Set.hpp>
#include <test-debug/debug.hpp>

TEST(TestEtkSet, Creation) {
	etk::Set<uint32_t> testData;
	EXPECT_EQ(testData.size(), 0);
}

TEST(TestEtkSet, addGoodOrder) {
	etk::Set<uint32_t> testData;
	EXPECT_EQ(testData.size(), 0);
	testData.add(2);
	testData.add(9);
	testData.add(1);
	testData.add(6);
	EXPECT_EQ(testData.size(), 4);
	EXPECT_EQ(testData[0], 1);
	EXPECT_EQ(testData[1], 2);
	EXPECT_EQ(testData[2], 6);
	EXPECT_EQ(testData[3], 9);
}

TEST(TestEtkSet, addMultiple) {
	etk::Set<uint32_t> testData;
	EXPECT_EQ(testData.size(), 0);
	testData.add(2);
	testData.add(9);
	testData.add(9);
	testData.add(2);
	EXPECT_EQ(testData.size(), 2);
	EXPECT_EQ(testData[0], 2);
	EXPECT_EQ(testData[1], 9);
}

TEST(TestEtkSet, initializationList) {
	etk::Set<int> testData = {7,2,3,3,1,99};
	EXPECT_EQ(testData.size(), 5);
	EXPECT_EQ(testData[0], 1);
	EXPECT_EQ(testData[1], 2);
	EXPECT_EQ(testData[2], 3);
	EXPECT_EQ(testData[3], 7);
	EXPECT_EQ(testData[4], 99);
}

TEST(TestEtkSet, find) {
	etk::Set<int> testData = {1,2,3,66,74623};
	EXPECT_EQ(testData.size(), 5);
	auto it = testData.find(66);
	EXPECT_EQ(it, testData.begin() + 3);
	it = testData.find(99);
	EXPECT_EQ(it, testData.end());
}

TEST(TestEtkSet, erase) {
	etk::Set<int> testData = {1,3,4,2,0,7};
	EXPECT_EQ(testData.size(), 6);
	auto it = testData.erase(testData.begin() + 4);
	EXPECT_EQ(testData.size(), 5);
	EXPECT_EQ(testData[0], 0);
	EXPECT_EQ(testData[1], 1);
	EXPECT_EQ(testData[2], 2);
	EXPECT_EQ(testData[3], 3);
	EXPECT_EQ(testData[4], 7);
}

TEST(TestEtkSet, withStringClass) {
	etk::Set<etk::String> testData;
	EXPECT_EQ(testData.size(), 0);
	testData.add("2");
	testData.add("9");
	testData.add("9");
	testData.add("4");
	EXPECT_EQ(testData.size(), 3);
	EXPECT_EQ(testData[0], "2");
	EXPECT_EQ(testData[1], "4");
	EXPECT_EQ(testData[2], "9");
}

bool comp(const uint32_t& _left, const uint32_t& _right ) { return _left>_right; };

TEST(TestEtkSet, creationComparatorReverse) {
	etk::Set<uint32_t> testData;
	//auto comp = [](const uint32_t& _left, const uint32_t& _right ) { return _left>_right; };
	testData.setComparator(&comp);
	EXPECT_EQ(testData.size(), 0);
	testData.add(2);
	testData.add(9);
	testData.add(1);
	testData.add(6);
	EXPECT_EQ(testData.size(), 4);
	EXPECT_EQ(testData[0], 9);
	EXPECT_EQ(testData[1], 6);
	EXPECT_EQ(testData[2], 2);
	EXPECT_EQ(testData[3], 1);
}
