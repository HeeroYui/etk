/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <gtest/gtest.h>
#include <etk/String.hpp>
#include <test-debug/debug.hpp>

#define NAME "etk:String"

TEST(TestString, constructor) {
	// Test contructor value
	etk::String test0;
	EXPECT_FLOAT_EQ(test0.size(), 0);
	EXPECT_FLOAT_EQ(test0.c_str()[0], '\0');
	
	etk::String test1("hello");
	EXPECT_FLOAT_EQ(test1.size(), 5);
	EXPECT_FLOAT_EQ(test1.c_str()[0], 'h');
	EXPECT_FLOAT_EQ(test1.c_str()[1], 'e');
	EXPECT_FLOAT_EQ(test1.c_str()[2], 'l');
	EXPECT_FLOAT_EQ(test1.c_str()[3], 'l');
	EXPECT_FLOAT_EQ(test1.c_str()[4], 'o');
	EXPECT_FLOAT_EQ(test1.c_str()[5], '\0');
	
	etk::String test2(test1);
	EXPECT_FLOAT_EQ(test2.size(), 5);
	EXPECT_FLOAT_EQ(test2.c_str()[0], 'h');
	EXPECT_FLOAT_EQ(test2.c_str()[1], 'e');
	EXPECT_FLOAT_EQ(test2.c_str()[2], 'l');
	EXPECT_FLOAT_EQ(test2.c_str()[3], 'l');
	EXPECT_FLOAT_EQ(test2.c_str()[4], 'o');
	EXPECT_FLOAT_EQ(test2.c_str()[5], '\0');
	
	etk::String test3(test1, 2);
	EXPECT_FLOAT_EQ(test3.size(), 3);
	EXPECT_FLOAT_EQ(test3.c_str()[0], 'l');
	EXPECT_FLOAT_EQ(test3.c_str()[1], 'l');
	EXPECT_FLOAT_EQ(test3.c_str()[2], 'o');
	EXPECT_FLOAT_EQ(test3.c_str()[3], '\0');
	
	etk::String test4(test1, 1, 3);
	EXPECT_FLOAT_EQ(test4.size(), 3);
	EXPECT_FLOAT_EQ(test4.c_str()[0], 'e');
	EXPECT_FLOAT_EQ(test4.c_str()[1], 'l');
	EXPECT_FLOAT_EQ(test4.c_str()[2], 'l');
	EXPECT_FLOAT_EQ(test4.c_str()[3], '\0');
	
}

TEST(TestString, equality) {
	etk::String test2("hello");
	etk::String test4("maeau");
	
	test4 = 'c';
	EXPECT_FLOAT_EQ(test4.size(), 1);
	EXPECT_FLOAT_EQ(test4.c_str()[0], 'c');
	EXPECT_FLOAT_EQ(test4.c_str()[1], '\0');
	
	test4 = "prout";
	EXPECT_FLOAT_EQ(test4.size(), 5);
	EXPECT_FLOAT_EQ(test4.c_str()[0], 'p');
	EXPECT_FLOAT_EQ(test4.c_str()[1], 'r');
	EXPECT_FLOAT_EQ(test4.c_str()[2], 'o');
	EXPECT_FLOAT_EQ(test4.c_str()[3], 'u');
	EXPECT_FLOAT_EQ(test4.c_str()[4], 't');
	EXPECT_FLOAT_EQ(test4.c_str()[5], '\0');
	
	test4 = test2;
	EXPECT_FLOAT_EQ(test4.size(), 5);
	EXPECT_FLOAT_EQ(test4.c_str()[0], 'h');
	EXPECT_FLOAT_EQ(test4.c_str()[1], 'e');
	EXPECT_FLOAT_EQ(test4.c_str()[2], 'l');
	EXPECT_FLOAT_EQ(test4.c_str()[3], 'l');
	EXPECT_FLOAT_EQ(test4.c_str()[4], 'o');
	EXPECT_FLOAT_EQ(test4.c_str()[5], '\0');
}

TEST(TestString, swap) {
	etk::String test2("hello");
	etk::String test4 = "plo";
	test4.swap(test2);
	EXPECT_FLOAT_EQ(test4.size(), 5);
	EXPECT_FLOAT_EQ(test4.c_str()[0], 'h');
	EXPECT_FLOAT_EQ(test4.c_str()[1], 'e');
	EXPECT_FLOAT_EQ(test4.c_str()[2], 'l');
	EXPECT_FLOAT_EQ(test4.c_str()[3], 'l');
	EXPECT_FLOAT_EQ(test4.c_str()[4], 'o');
	EXPECT_FLOAT_EQ(test4.c_str()[5], '\0');
	EXPECT_FLOAT_EQ(test2.size(), 3);
	EXPECT_FLOAT_EQ(test2.c_str()[0], 'p');
	EXPECT_FLOAT_EQ(test2.c_str()[1], 'l');
	EXPECT_FLOAT_EQ(test2.c_str()[2], 'o');
	EXPECT_FLOAT_EQ(test2.c_str()[3], '\0');
	
}

TEST(TestString, equalityComparison) {
	etk::String test1("hello");
	etk::String test2("hello2");
	EXPECT_FLOAT_EQ(test1 == test2, false);
	EXPECT_FLOAT_EQ(test1 != test2, true);
	
	test1 = "hello2";
	EXPECT_FLOAT_EQ(test1 != test2, false);
	EXPECT_FLOAT_EQ(test1 == test2, true);
}


TEST(TestString, resize) {
	etk::String test1("hello");
	test1.resize(0);
	EXPECT_FLOAT_EQ(test1.size(), 0);
	test1.resize(3);
	EXPECT_FLOAT_EQ(test1.size(), 3);
	EXPECT_FLOAT_EQ(test1.c_str()[0], '\0');
	EXPECT_FLOAT_EQ(test1.c_str()[1], '\0');
	EXPECT_FLOAT_EQ(test1.c_str()[2], '\0');
	EXPECT_FLOAT_EQ(test1.c_str()[3], '\0');
	test1.resize(2, 'g');
	EXPECT_FLOAT_EQ(test1.size(), 2);
	EXPECT_FLOAT_EQ(test1.c_str()[0], '\0');
	EXPECT_FLOAT_EQ(test1.c_str()[1], '\0');
	test1.resize(5, 'g');
	EXPECT_FLOAT_EQ(test1.size(), 5);
	EXPECT_FLOAT_EQ(test1.c_str()[0], '\0');
	EXPECT_FLOAT_EQ(test1.c_str()[1], '\0');
	EXPECT_FLOAT_EQ(test1.c_str()[2], 'g');
	EXPECT_FLOAT_EQ(test1.c_str()[3], 'g');
	EXPECT_FLOAT_EQ(test1.c_str()[4], 'g');
	EXPECT_FLOAT_EQ(test1.c_str()[5], '\0');
}


TEST(TestString, add) {
	etk::String test1("h");
	test1 += 'r';
	EXPECT_FLOAT_EQ(test1.size(), 2);
	EXPECT_FLOAT_EQ(test1.c_str()[0], 'h');
	EXPECT_FLOAT_EQ(test1.c_str()[1], 'r');
	EXPECT_FLOAT_EQ(test1.c_str()[2], '\0');
	test1 += "kg";
	EXPECT_FLOAT_EQ(test1.size(), 4);
	EXPECT_FLOAT_EQ(test1.c_str()[0], 'h');
	EXPECT_FLOAT_EQ(test1.c_str()[1], 'r');
	EXPECT_FLOAT_EQ(test1.c_str()[2], 'k');
	EXPECT_FLOAT_EQ(test1.c_str()[3], 'g');
	EXPECT_FLOAT_EQ(test1.c_str()[4], '\0');
	test1 += etk::String("Ui");
	EXPECT_FLOAT_EQ(test1.size(), 6);
	EXPECT_FLOAT_EQ(test1.c_str()[0], 'h');
	EXPECT_FLOAT_EQ(test1.c_str()[1], 'r');
	EXPECT_FLOAT_EQ(test1.c_str()[2], 'k');
	EXPECT_FLOAT_EQ(test1.c_str()[3], 'g');
	EXPECT_FLOAT_EQ(test1.c_str()[4], 'U');
	EXPECT_FLOAT_EQ(test1.c_str()[5], 'i');
	EXPECT_FLOAT_EQ(test1.c_str()[6], '\0');
}

TEST(TestString, insert) {
	etk::String test1("hrkgUi");
	test1.insert(0, 'F');
	EXPECT_FLOAT_EQ(test1.size(), 7);
	EXPECT_FLOAT_EQ(test1.c_str()[0], 'F');
	EXPECT_FLOAT_EQ(test1.c_str()[1], 'h');
	EXPECT_FLOAT_EQ(test1.c_str()[2], 'r');
	EXPECT_FLOAT_EQ(test1.c_str()[3], 'k');
	EXPECT_FLOAT_EQ(test1.c_str()[4], 'g');
	EXPECT_FLOAT_EQ(test1.c_str()[5], 'U');
	EXPECT_FLOAT_EQ(test1.c_str()[6], 'i');
	EXPECT_FLOAT_EQ(test1.c_str()[7], '\0');
	test1.insert(7, 'Z');
	EXPECT_FLOAT_EQ(test1.size(), 8);
	EXPECT_FLOAT_EQ(test1.c_str()[0], 'F');
	EXPECT_FLOAT_EQ(test1.c_str()[1], 'h');
	EXPECT_FLOAT_EQ(test1.c_str()[2], 'r');
	EXPECT_FLOAT_EQ(test1.c_str()[3], 'k');
	EXPECT_FLOAT_EQ(test1.c_str()[4], 'g');
	EXPECT_FLOAT_EQ(test1.c_str()[5], 'U');
	EXPECT_FLOAT_EQ(test1.c_str()[6], 'i');
	EXPECT_FLOAT_EQ(test1.c_str()[7], 'Z');
	EXPECT_FLOAT_EQ(test1.c_str()[8], '\0');
	test1.insert(2, 'H');
	EXPECT_FLOAT_EQ(test1.size(), 9);
	EXPECT_FLOAT_EQ(test1.c_str()[0], 'F');
	EXPECT_FLOAT_EQ(test1.c_str()[1], 'h');
	EXPECT_FLOAT_EQ(test1.c_str()[2], 'H');
	EXPECT_FLOAT_EQ(test1.c_str()[3], 'r');
	EXPECT_FLOAT_EQ(test1.c_str()[4], 'k');
	EXPECT_FLOAT_EQ(test1.c_str()[5], 'g');
	EXPECT_FLOAT_EQ(test1.c_str()[6], 'U');
	EXPECT_FLOAT_EQ(test1.c_str()[7], 'i');
	EXPECT_FLOAT_EQ(test1.c_str()[8], 'Z');
	EXPECT_FLOAT_EQ(test1.c_str()[9], '\0');
}

TEST(TestString, eraseLen) {
	etk::String test1("hrkgUi");
	test1.erase(0, 3);
	EXPECT_FLOAT_EQ(test1.size(), 3);
	EXPECT_FLOAT_EQ(test1.c_str()[0], 'g');
	EXPECT_FLOAT_EQ(test1.c_str()[1], 'U');
	EXPECT_FLOAT_EQ(test1.c_str()[2], 'i');
	EXPECT_FLOAT_EQ(test1.c_str()[3], '\0');
	test1.erase(1, 1);
	EXPECT_FLOAT_EQ(test1.size(), 2);
	EXPECT_FLOAT_EQ(test1.c_str()[0], 'g');
	EXPECT_FLOAT_EQ(test1.c_str()[1], 'i');
	EXPECT_FLOAT_EQ(test1.c_str()[2], '\0');
	test1.erase(1, 100);
	EXPECT_FLOAT_EQ(test1.size(), 1);
	EXPECT_FLOAT_EQ(test1.c_str()[0], 'g');
	EXPECT_FLOAT_EQ(test1.c_str()[1], '\0');
}

TEST(TestString, additionExtern) {
	etk::String test1 = "aa" + etk::String("he") + 't';
	EXPECT_FLOAT_EQ(test1.size(), 5);
	EXPECT_FLOAT_EQ(test1.c_str()[0], 'a');
	EXPECT_FLOAT_EQ(test1.c_str()[1], 'a');
	EXPECT_FLOAT_EQ(test1.c_str()[2], 'h');
	EXPECT_FLOAT_EQ(test1.c_str()[3], 'e');
	EXPECT_FLOAT_EQ(test1.c_str()[4], 't');
	EXPECT_FLOAT_EQ(test1.c_str()[5], '\0');
}
