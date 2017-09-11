/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */


#include <etk/Pair.hpp>
#include <etk/math/Vector2D.hpp>
#include <test-debug/debug.hpp>
#include <etest/etest.hpp>

TEST(TestVector2D_f, constructor) {
	// Test contructor value
	etk::Vector2D<float> test0(0,0);
	EXPECT_FLOAT_EQ(test0.x(), 0.0);
	EXPECT_FLOAT_EQ(test0.y(), 0.0);
	etk::Vector2D<float> vect1(4,5);
	EXPECT_FLOAT_EQ(vect1.x(), 4.0);
	EXPECT_FLOAT_EQ(vect1.y(), 5.0);
	etk::Vector2D<float> vect2(vect1);
	EXPECT_FLOAT_EQ(vect2.x(), 4.0);
	EXPECT_FLOAT_EQ(vect2.y(), 5.0);
	etk::Vector2D<float> vect3 = vect1;
	EXPECT_FLOAT_EQ(vect3.x(), 4.0);
	EXPECT_FLOAT_EQ(vect3.y(), 5.0);
	test0 = vect2;
	EXPECT_FLOAT_EQ(test0.x(), 4.0);
	EXPECT_FLOAT_EQ(test0.y(), 5.0);
}

TEST(TestVector2D_f, constructorString) {
	etk::Vector2D<float> vect1("(4,-8.5)");
	EXPECT_EQ(vect1, etk::Vector2D<float>(4.0,-8.5));
	etk::Vector2D<float> vect2("-6,5.5");
	EXPECT_FLOAT_EQ(vect2.x(), -6.0);
	EXPECT_FLOAT_EQ(vect2.y(), 5.5);
	etk::Vector2D<float> vect3("256.38");
	EXPECT_FLOAT_EQ(vect3.x(), 256.38);
	EXPECT_FLOAT_EQ(vect3.y(), 256.38);
}

TEST(TestVector2D_f, equity) {
	etk::Vector2D<float> test1(99,32);
	etk::Vector2D<float> test2(11,22);
	etk::Vector2D<float> test3(11,22);
	EXPECT_EQ(test1 == test2, false);
	EXPECT_EQ(test1 != test2, true);
	EXPECT_EQ(test3 == test2, true);
	EXPECT_EQ(test3 != test2, false);
}

TEST(TestVector2D_f, set) {
	// Test contructor value
	etk::Vector2D<float> test1(0,0);
	EXPECT_FLOAT_EQ(test1.x(), 0.0);
	EXPECT_FLOAT_EQ(test1.y(), 0.0);
	test1.setValue(1,2);
	EXPECT_FLOAT_EQ(test1.x(), 1.0);
	EXPECT_FLOAT_EQ(test1.y(), 2.0);
}


TEST(TestVector2D_f, setSetZero) {
	// Test contructor value
	etk::Vector2D<float> test1(4,5);
	EXPECT_EQ(test1, etk::Vector2D<float>(4,5));
	EXPECT_FLOAT_EQ(test1.x(), 4.0);
	EXPECT_FLOAT_EQ(test1.y(), 5.0);
	test1.setZero();
	EXPECT_FLOAT_EQ(test1.x(), 0.0);
	EXPECT_FLOAT_EQ(test1.y(), 0.0);
}


TEST(TestVector2D_f, length) {
	// Test contructor value
	etk::Vector2D<float> test1(0,0);
	EXPECT_FLOAT_EQ(test1.length(), 0.0);
	EXPECT_FLOAT_EQ(test1.length2(), 0.0);
	test1.setValue(2,0);
	EXPECT_FLOAT_EQ(test1.length(), 2.0);
	test1.setValue(0,3);
	EXPECT_FLOAT_EQ(test1.length(), 3.0);
	test1.setValue(3,4);
	EXPECT_FLOAT_EQ(test1.length2(), 25.0);
}

TEST(TestVector2D_f, normalize) {
	etk::Vector2D<float> test1(11,22);
	etk::Vector2D<float> test2 = test1.normalized();
	EXPECT_FLOAT_EQ(test1.x(), 11.0);
	EXPECT_FLOAT_EQ(test1.y(), 22.0);
	EXPECT_FLOAT_EQ(test2.x(), 0.44721359);
	EXPECT_FLOAT_EQ(test2.y(), 0.89442718);
	test1.normalize();
	EXPECT_FLOAT_EQ(test1.x(), 0.44721359);
	EXPECT_FLOAT_EQ(test1.y(), 0.89442718);
}

TEST(TestVector2D_f, dot) {
	etk::Vector2D<float> test1(11,0);
	etk::Vector2D<float> test2(0,88);
	EXPECT_FLOAT_EQ(test1.dot(test1), 121.0);
	EXPECT_FLOAT_EQ(test1.dot(test2), 0.0);
	test1.setValue(2,3);
	test2.setValue(9,7);
	EXPECT_FLOAT_EQ(test1.dot(test2), 39.0);
}
