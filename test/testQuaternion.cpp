/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <gtest/gtest.h>
#include <etk/math/Quaternion.hpp>
#include <test-debug/debug.hpp>

#define NAME "etk::Quaternion"

TEST(TestQuaternion, constructor) {
	etk::Quaternion test0(1,2,3,4);
	EXPECT_FLOAT_EQ(test0.x(), 1.0);
	EXPECT_FLOAT_EQ(test0.y(), 2.0);
	EXPECT_FLOAT_EQ(test0.z(), 3.0);
	EXPECT_FLOAT_EQ(test0.w(), 4.0);
	etk::Quaternion test1(4, vec3(1,2,3));
	EXPECT_FLOAT_EQ(test1.x(), 1.0);
	EXPECT_FLOAT_EQ(test1.y(), 2.0);
	EXPECT_FLOAT_EQ(test1.z(), 3.0);
	EXPECT_FLOAT_EQ(test1.w(), 4.0);
	etk::Quaternion test2;
	EXPECT_FLOAT_EQ(test2.x(), 0.0);
	EXPECT_FLOAT_EQ(test2.y(), 0.0);
	EXPECT_FLOAT_EQ(test2.z(), 0.0);
	EXPECT_FLOAT_EQ(test2.w(), 0.0);
	etk::Quaternion test3(test0);
	EXPECT_FLOAT_EQ(test3.x(), 1.0);
	EXPECT_FLOAT_EQ(test3.y(), 2.0);
	EXPECT_FLOAT_EQ(test3.z(), 3.0);
	EXPECT_FLOAT_EQ(test3.w(), 4.0);
	etk::Quaternion test4 = test0;
	EXPECT_FLOAT_EQ(test4.x(), 1.0);
	EXPECT_FLOAT_EQ(test4.y(), 2.0);
	EXPECT_FLOAT_EQ(test4.z(), 3.0);
	EXPECT_FLOAT_EQ(test4.w(), 4.0);
	test2 = test0;
	EXPECT_FLOAT_EQ(test2.x(), 1.0);
	EXPECT_FLOAT_EQ(test2.y(), 2.0);
	EXPECT_FLOAT_EQ(test2.z(), 3.0);
	EXPECT_FLOAT_EQ(test2.w(), 4.0);
}

TEST(TestQuaternion, constructorMatrix) {
	etk::Quaternion test1(0.18257423, 0.3651484, 0.54772264, 0.73029673);
	etk::Quaternion test2(test1.getMatrix());
	EXPECT_FLOAT_EQ(test2.x(), 0.18257423);
	EXPECT_FLOAT_EQ(test2.y(), 0.3651484);
	EXPECT_FLOAT_EQ(test2.z(), 0.54772264);
	EXPECT_FLOAT_EQ(test2.w(), 0.73029673);
}

TEST(TestQuaternion, constructorEuler) {
	etk::Quaternion test0(vec3(M_PI*0.5f, 0, 0));
	etk::Quaternion test01(std::sin(M_PI*0.25f), 0, 0, std::cos(M_PI*0.25f));
	test01.normalize();
	EXPECT_FLOAT_EQ(test0.x(), test01.x());
	EXPECT_FLOAT_EQ(test0.y(), test01.y());
	EXPECT_FLOAT_EQ(test0.z(), test01.z());
	EXPECT_FLOAT_EQ(test0.w(), test01.w());
	
	etk::Quaternion test1(vec3(0, M_PI*0.5f, 0));
	etk::Quaternion test11(0, std::sin(M_PI*0.25f), 0, std::cos(M_PI*0.25f));
	test11.normalize();
	EXPECT_FLOAT_EQ(test1.x(), test11.x());
	EXPECT_FLOAT_EQ(test1.y(), test11.y());
	EXPECT_FLOAT_EQ(test1.z(), test11.z());
	EXPECT_FLOAT_EQ(test1.w(), test11.w());
	
	etk::Quaternion test2(vec3(0, 0, M_PI*0.5f));
	etk::Quaternion test21(0, 0, std::sin(M_PI*0.25f), std::cos(M_PI*0.25f));
	test21.normalize();
	EXPECT_FLOAT_EQ(test2.x(), test21.x());
	EXPECT_FLOAT_EQ(test2.y(), test21.y());
	EXPECT_FLOAT_EQ(test2.z(), test21.z());
	EXPECT_FLOAT_EQ(test2.w(), test21.w());
}

TEST(TestQuaternion, normalize) {
	etk::Quaternion test1(5, 3, 8, 2);
	etk::Quaternion test2 = test1.normalized();
	// check if other quaternion does not change
	EXPECT_FLOAT_EQ(test1.x(), 5.0);
	EXPECT_FLOAT_EQ(test1.y(), 3.0);
	EXPECT_FLOAT_EQ(test1.z(), 8.0);
	EXPECT_FLOAT_EQ(test1.w(), 2.0);
	EXPECT_FLOAT_EQ(test2.x(), 0.4950738);
	EXPECT_FLOAT_EQ(test2.y(), 0.29704428);
	EXPECT_FLOAT_EQ(test2.z(), 0.79211807);
	EXPECT_FLOAT_EQ(test2.w(), 0.19802952);
	test1.normalize();
	EXPECT_FLOAT_EQ(test1.x(), 0.4950738);
	EXPECT_FLOAT_EQ(test1.y(), 0.29704428);
	EXPECT_FLOAT_EQ(test1.z(), 0.79211807);
	EXPECT_FLOAT_EQ(test1.w(), 0.19802952);
}

TEST(TestQuaternion, length) {
	etk::Quaternion test1(5, 3, 8, 2);
	EXPECT_FLOAT_EQ(test1.length2(), 102.0);
	EXPECT_FLOAT_EQ(test1.length(), 10.099504);
	EXPECT_FLOAT_EQ(test1.normalized().length(), 1.0);
}

TEST(TestQuaternion, set) {
	etk::Quaternion test1(5, 3, 8, 2);
	test1.setValue(12, 15, 22, 13);
	EXPECT_FLOAT_EQ(test1.x(), 12.0);
	EXPECT_FLOAT_EQ(test1.y(), 15.0);
	EXPECT_FLOAT_EQ(test1.z(), 22.0);
	EXPECT_FLOAT_EQ(test1.w(), 13.0);
	test1.setZero();
	EXPECT_FLOAT_EQ(test1.x(), 0.0);
	EXPECT_FLOAT_EQ(test1.y(), 0.0);
	EXPECT_FLOAT_EQ(test1.z(), 0.0);
	EXPECT_FLOAT_EQ(test1.w(), 0.0);
	test1.setIdentity();
	EXPECT_FLOAT_EQ(test1.x(), 0.0);
	EXPECT_FLOAT_EQ(test1.y(), 0.0);
	EXPECT_FLOAT_EQ(test1.z(), 0.0);
	EXPECT_FLOAT_EQ(test1.w(), 1.0);
	test1 = etk::Quaternion::zero();
	EXPECT_FLOAT_EQ(test1.x(), 0.0);
	EXPECT_FLOAT_EQ(test1.y(), 0.0);
	EXPECT_FLOAT_EQ(test1.z(), 0.0);
	EXPECT_FLOAT_EQ(test1.w(), 0.0);
	test1 = etk::Quaternion::identity();
	EXPECT_FLOAT_EQ(test1.x(), 0.0);
	EXPECT_FLOAT_EQ(test1.y(), 0.0);
	EXPECT_FLOAT_EQ(test1.z(), 0.0);
	EXPECT_FLOAT_EQ(test1.w(), 1.0);
}

TEST(TestQuaternion, getVector) {
	etk::Quaternion test1(5, 3, 8, 2);
	vec3 test2 = test1.getVectorV();
	EXPECT_FLOAT_EQ(test2.x(), 5.0);
	EXPECT_FLOAT_EQ(test2.y(), 3.0);
	EXPECT_FLOAT_EQ(test2.z(), 8.0);
}

TEST(TestQuaternion, conjugate) {
	etk::Quaternion test1(5, 3, 8, 2);
	etk::Quaternion test2 = test1.getConjugate();
	// check if other quaternion does not change
	EXPECT_FLOAT_EQ(test1.x(), 5.0);
	EXPECT_FLOAT_EQ(test1.y(), 3.0);
	EXPECT_FLOAT_EQ(test1.z(), 8.0);
	EXPECT_FLOAT_EQ(test1.w(), 2.0);
	EXPECT_FLOAT_EQ(test2.x(), -5.0);
	EXPECT_FLOAT_EQ(test2.y(), -3.0);
	EXPECT_FLOAT_EQ(test2.z(), -8.0);
	EXPECT_FLOAT_EQ(test2.w(), 2.0);
	test1.conjugate();
	EXPECT_FLOAT_EQ(test1.x(), -5.0);
	EXPECT_FLOAT_EQ(test1.y(), -3.0);
	EXPECT_FLOAT_EQ(test1.z(), -8.0);
	EXPECT_FLOAT_EQ(test1.w(), 2.0);
}
