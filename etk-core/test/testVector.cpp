/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */


#include <etk/Pair.hpp>
#include <etk/Vector.hpp>
#include <test-debug/debug.hpp>
#include <etest/etest.hpp>
#include "ConstructDestruct.hpp"

TEST(TestVector, constructor) {
	// Test contructor value
	etk::Vector<float> test;
	EXPECT_EQ(test.size(), 0);
}

TEST(TestVector, constructor_2) {
	// Test contructor value
	etk::Vector<float> test(3.9f, 33.0f,55.8f);
	EXPECT_EQ(test.size(), 3);
	EXPECT_EQ(test[0], 3.9f);
	EXPECT_EQ(test[1], 33.0f);
	EXPECT_EQ(test[2], 55.8f);
}

TEST(TestVector, resize) {
	// Test contructor value
	etk::Vector<float> test;
	test.resize(3);
	EXPECT_EQ(test.size(), 3);
}
TEST(TestVector, empty) {
	// Test contructor value
	etk::Vector<float> test;
	EXPECT_EQ(test.empty(), true);
	test.pushBack(2);
	EXPECT_EQ(test.empty(), false);
}

TEST(TestVector, pushBack) {
	// Test contructor value
	etk::Vector<float> test;
	EXPECT_EQ(test.size(), 0);
	test.pushBack(2);
	EXPECT_EQ(test.size(), 1);
	EXPECT_EQ(test[0], 2);
	test.pushBack(4);
	EXPECT_EQ(test.size(), 2);
	EXPECT_EQ(test[0], 2);
	EXPECT_EQ(test[1], 4);
	test.pushBack(8);
	EXPECT_EQ(test.size(), 3);
	EXPECT_EQ(test[0], 2);
	EXPECT_EQ(test[1], 4);
	EXPECT_EQ(test[2], 8);
	test.popBack();
	EXPECT_EQ(test.size(), 2);
	EXPECT_EQ(test[0], 2);
	EXPECT_EQ(test[1], 4);
}

TEST(TestVector, pushFront) {
	// Test contructor value
	etk::Vector<float> test;
	EXPECT_EQ(test.size(), 0);
	test.pushBack(2);
	EXPECT_EQ(test.size(), 1);
	EXPECT_EQ(test[0], 2);
	test.pushBack(4);
	EXPECT_EQ(test.size(), 2);
	EXPECT_EQ(test[0], 2);
	EXPECT_EQ(test[1], 4);
	test.pushFront(8);
	EXPECT_EQ(test.size(), 3);
	EXPECT_EQ(test[0], 8);
	EXPECT_EQ(test[1], 2);
	EXPECT_EQ(test[2], 4);
	test.pushFront(55);
	EXPECT_EQ(test.size(), 4);
	EXPECT_EQ(test[0], 55);
	EXPECT_EQ(test[1], 8);
	EXPECT_EQ(test[2], 2);
	EXPECT_EQ(test[3], 4);
}

TEST(TestVector, insert) {
	// Test contructor value
	etk::Vector<float> test;
	EXPECT_EQ(test.size(), 0);
	test.pushBack(2);
	EXPECT_EQ(test.size(), 1);
	EXPECT_EQ(test[0], 2);
	test.pushBack(4);
	EXPECT_EQ(test.size(), 2);
	EXPECT_EQ(test[0], 2);
	EXPECT_EQ(test[1], 4);
	test.pushFront(8);
	EXPECT_EQ(test.size(), 3);
	EXPECT_EQ(test[0], 8);
	EXPECT_EQ(test[1], 2);
	EXPECT_EQ(test[2], 4);
	test.pushFront(55);
	EXPECT_EQ(test.size(), 4);
	EXPECT_EQ(test[0], 55);
	EXPECT_EQ(test[1], 8);
	EXPECT_EQ(test[2], 2);
	EXPECT_EQ(test[3], 4);
}

TEST(TestVector, back) {
	// Test contructor value
	etk::Vector<float> test;
	EXPECT_EQ(test.size(), 0);
	test.pushBack(2);
	test.pushBack(4);
	test.pushBack(8);
	EXPECT_EQ(test.size(), 3);
	EXPECT_EQ(test[0], 2);
	EXPECT_EQ(test[1], 4);
	EXPECT_EQ(test[2], 8);
	EXPECT_EQ(test.back(), 8);
}

TEST(TestVector, popBack) {
	// Test contructor value
	etk::Vector<float> test;
	EXPECT_EQ(test.size(), 0);
	test.pushBack(2);
	test.pushBack(4);
	test.pushBack(8);
	EXPECT_EQ(test.size(), 3);
	EXPECT_EQ(test[0], 2);
	EXPECT_EQ(test[1], 4);
	EXPECT_EQ(test[2], 8);
	test.popBack();
	EXPECT_EQ(test.size(), 2);
	EXPECT_EQ(test[0], 2);
	EXPECT_EQ(test[1], 4);
}

TEST(TestVector, front) {
	// Test contructor value
	etk::Vector<float> test;
	EXPECT_EQ(test.size(), 0);
	test.pushBack(2);
	test.pushBack(4);
	test.pushBack(8);
	EXPECT_EQ(test.size(), 3);
	EXPECT_EQ(test[0], 2);
	EXPECT_EQ(test[1], 4);
	EXPECT_EQ(test[2], 8);
	EXPECT_EQ(test.front(), 2);
}

TEST(TestVector, popFront) {
	// Test contructor value
	etk::Vector<float> test;
	EXPECT_EQ(test.size(), 0);
	test.pushBack(2);
	test.pushBack(4);
	test.pushBack(8);
	EXPECT_EQ(test.size(), 3);
	EXPECT_EQ(test[0], 2);
	EXPECT_EQ(test[1], 4);
	EXPECT_EQ(test[2], 8);
	test.popFront();
	EXPECT_EQ(test.size(), 2);
	EXPECT_EQ(test[0], 4);
	EXPECT_EQ(test[1], 8);
}


TEST(TestVector, initializationList_1) {
	// Test contructor value
	etk::Vector<int> test = {1, 5, 6, 8};
	EXPECT_EQ(test.size(), 4);
	EXPECT_EQ(test[0], 1);
	EXPECT_EQ(test[1], 5);
	EXPECT_EQ(test[2], 6);
	EXPECT_EQ(test[3], 8);
}

TEST(TestVector, initializationList_2) {
	// Test contructor value
	etk::Vector<int> test(1, 5, 6, 8);
	EXPECT_EQ(test.size(), 4);
	EXPECT_EQ(test[0], 1);
	EXPECT_EQ(test[1], 5);
	EXPECT_EQ(test[2], 6);
	EXPECT_EQ(test[3], 8);
}


TEST(TestVector, destroyElementAtTheCorectMoment) {
	test::resetIsDestroy();
	{
		etk::Vector<test::ConstructDestruct> list;
		list.pushBack(test::ConstructDestruct(55));
		EXPECT_EQ(list.size(), 1);
		EXPECT_EQ(test::getIsDestroy(), 55);
		auto it = list.erase(list.begin());
		EXPECT_EQ(test::getIsDestroy(), 0);
		EXPECT_EQ(list.size(), 0);
		EXPECT_EQ(it, list.end());
	}
	EXPECT_EQ(test::getIsDestroy(), 0);
}

TEST(TestVector, destroyElementAtTheCorectMoment_2) {
	test::resetIsDestroy();
	{
		etk::Vector<test::ConstructDestruct> list;
		list.pushBack(test::ConstructDestruct(4));
		list.pushBack(test::ConstructDestruct(30));
		list.pushBack(test::ConstructDestruct(1000));
		list.pushBack(test::ConstructDestruct(200));
		EXPECT_EQ(list.size(), 4);
		EXPECT_EQ(test::getIsDestroy(), 1234);
		auto it = list.erase(list.begin());
		EXPECT_EQ(list.size(), 3);
		EXPECT_EQ(test::getIsDestroy(), 1230);
		it = list.erase(list.begin()+1);
		EXPECT_EQ(test::getIsDestroy(), 230);
		EXPECT_EQ(list.size(), 2);
	}
	EXPECT_EQ(test::getIsDestroy(), 0);
}

TEST(TestVector, allocateElementAtTheCorectMoment) {
	test::resetIsDestroy();
	{
		etk::Vector<test::ConstructDestruct> list;
		list.reserve(10);
		EXPECT_EQ(list.size(), 0);
		EXPECT_EQ(test::getIsDestroy(), 0);
	}
	EXPECT_EQ(test::getIsDestroy(), 0);
}
/*
TEST(TestVector, allocateBench) {
	while (1) {
		etk::Vector<uint8_t> list;
		//list.reserve(1024*1024);
		for (size_t iii=0; iii < 1024*1024; ++iii) {
			list.pushBack(66);
		}
		EXPECT_EQ(list.size(), 1024*1024);
	}
}
*/


