/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */


#include <etk/Pair.hpp>
#include <etk/Vector.hpp>
#include <test-debug/debug.hpp>
#include <etest/etest.hpp>

TEST(TestVector, constructor) {
	// Test contructor value
	etk::Vector<float> test;
	EXPECT_EQ(test.size(), 0);
}

TEST(TestVector, constructor_2) {
	// Test contructor value
	etk::Vector<float> test(3);
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

