/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etest/etest.hpp>
#include <etk/math/Vector3D.hpp>
#include <test-debug/debug.hpp>
#include "ConstructDestruct.hpp"

#define NAME "etk:Vector3D<float>"

TEST(TestVector3D_f, constructor) {
	// Test contructor value
	vec3 test0(0,0,0);
	EXPECT_FLOAT_EQ(test0.x(), 0.0);
	EXPECT_FLOAT_EQ(test0.y(), 0.0);
	EXPECT_FLOAT_EQ(test0.z(), 0.0);
	vec3 vect1(4,5,8);
	EXPECT_FLOAT_EQ(vect1.x(), 4.0);
	EXPECT_FLOAT_EQ(vect1.y(), 5.0);
	EXPECT_FLOAT_EQ(vect1.z(), 8.0);
	vec3 vect2(vect1);
	EXPECT_FLOAT_EQ(vect2.x(), 4.0);
	EXPECT_FLOAT_EQ(vect2.y(), 5.0);
	EXPECT_FLOAT_EQ(vect2.z(), 8.0);
	vec3 vect3 = vect1;
	EXPECT_FLOAT_EQ(vect3.x(), 4.0);
	EXPECT_FLOAT_EQ(vect3.y(), 5.0);
	EXPECT_FLOAT_EQ(vect3.z(), 8.0);
	test0 = vect2;
	EXPECT_FLOAT_EQ(test0.x(), 4.0);
	EXPECT_FLOAT_EQ(test0.y(), 5.0);
	EXPECT_FLOAT_EQ(test0.z(), 8.0);
}

TEST(TestVector3D_f, equity) {
	vec3 test1(99,32,56);
	vec3 test2(11,22,33);
	vec3 test3(11,22,33);
	EXPECT_EQ(test1 == test2, false);
	EXPECT_EQ(test1 != test2, true);
	EXPECT_EQ(test3 == test2, true);
	EXPECT_EQ(test3 != test2, false);
}

TEST(TestVector3D_f, set) {
	// Test contructor value
	vec3 test1(0,0,0);
	EXPECT_FLOAT_EQ(test1.x(), 0.0);
	EXPECT_FLOAT_EQ(test1.y(), 0.0);
	EXPECT_FLOAT_EQ(test1.z(), 0.0);
	test1.setValue(1,2,3);
	EXPECT_FLOAT_EQ(test1.x(), 1.0);
	EXPECT_FLOAT_EQ(test1.y(), 2.0);
	EXPECT_FLOAT_EQ(test1.z(), 3.0);
}

TEST(TestVector3D_f, setSetZero) {
	// Test contructor value
	vec3 test1(4,5,6);
	EXPECT_FLOAT_EQ(test1.x(), 4.0);
	EXPECT_FLOAT_EQ(test1.y(), 5.0);
	EXPECT_FLOAT_EQ(test1.z(), 6.0);
	test1.setZero();
	EXPECT_FLOAT_EQ(test1.x(), 0.0);
	EXPECT_FLOAT_EQ(test1.y(), 0.0);
	EXPECT_FLOAT_EQ(test1.z(), 0.0);
}


TEST(TestVector3D_f, length) {
	// Test contructor value
	vec3 test1(0,0,0);
	EXPECT_FLOAT_EQ(test1.length(), 0.0);
	EXPECT_FLOAT_EQ(test1.length2(), 0.0);
	test1.setValue(2,0,0);
	EXPECT_FLOAT_EQ(test1.length(), 2.0);
	test1.setValue(0,3,0);
	EXPECT_FLOAT_EQ(test1.length(), 3.0);
	test1.setValue(0,0,4);
	EXPECT_FLOAT_EQ(test1.length(), 4.0);
	test1.setValue(3,4,5);
	EXPECT_FLOAT_EQ(test1.length2(), 50.0);
}

TEST(TestVector3D_f, normalize) {
	vec3 test1(11,22,33);
	vec3 test2 = test1.normalized();
	EXPECT_FLOAT_EQ(test1.x(), 11.0);
	EXPECT_FLOAT_EQ(test1.y(), 22.0);
	EXPECT_FLOAT_EQ(test1.z(), 33.0);
	EXPECT_FLOAT_EQ(test2.x(), 0.26726124);
	EXPECT_FLOAT_EQ(test2.y(), 0.53452247);
	EXPECT_FLOAT_EQ(test2.z(), 0.80178374);
	test1.normalize();
	EXPECT_FLOAT_EQ(test1.x(), 0.26726124);
	EXPECT_FLOAT_EQ(test1.y(), 0.53452247);
	EXPECT_FLOAT_EQ(test1.z(), 0.80178374);
}

TEST(TestVector3D_f, dot) {
	vec3 test1(11,0,0);
	vec3 test2(0,88,66);
	EXPECT_FLOAT_EQ(test1.dot(test1), 121.0);
	EXPECT_FLOAT_EQ(test1.dot(test2), 0.0);
	test1.setValue(2,3,5);
	test2.setValue(9,7,6);
	EXPECT_FLOAT_EQ(test1.dot(test2), 69.0); // ????
}

TEST(TestVector3D_f, cross) {
	vec3 test1(0,0,0);
	vec3 test2(-55,88,66);
	EXPECT_EQ(test1.cross(test1), vec3(0,0,0));
	EXPECT_EQ(test2.cross(test2), vec3(0,0,0));
	test1.setValue(1,0,0);
	test2.setValue(0,1,0);
	EXPECT_EQ(test1.cross(test2), vec3(0,0,1));
	test2.setValue(0,0,1);
	EXPECT_EQ(test1.cross(test2), vec3(0,-1,0));
	test1.setValue(0,1,0);
	EXPECT_EQ(test1.cross(test2), vec3(1,0,0));
	test1.setValue(8,9,-10);
	test2.setValue(2,-3,5);
	EXPECT_EQ(test1.cross(test2), vec3(15,-60,-42));
}
