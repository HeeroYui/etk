/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */

#include <gtest/gtest.h>
#include <etk/math/Vector3D.hpp>
#include <etk/math/Matrix3.hpp>
#include <test-debug/debug.hpp>

#define NAME "etk::Matrix3"

TEST(TestMatrix3x3, constructor) {
	// Test contructor value
	etk::Matrix3 test1(99.0);
	EXPECT_FLOAT_EQ(test1.m_mat[0], 99.0);
	EXPECT_FLOAT_EQ(test1.m_mat[1], 99.0);
	EXPECT_FLOAT_EQ(test1.m_mat[2], 99.0);
	EXPECT_FLOAT_EQ(test1.m_mat[3], 99.0);
	EXPECT_FLOAT_EQ(test1.m_mat[4], 99.0);
	EXPECT_FLOAT_EQ(test1.m_mat[5], 99.0);
	EXPECT_FLOAT_EQ(test1.m_mat[6], 99.0);
	EXPECT_FLOAT_EQ(test1.m_mat[7], 99.0);
	EXPECT_FLOAT_EQ(test1.m_mat[8], 99.0);
	etk::Matrix3 test2(11,22,33,44,55,66,77,88,99);
	EXPECT_FLOAT_EQ(test2.m_mat[0], 11.0);
	EXPECT_FLOAT_EQ(test2.m_mat[1], 22.0);
	EXPECT_FLOAT_EQ(test2.m_mat[2], 33.0);
	EXPECT_FLOAT_EQ(test2.m_mat[3], 44.0);
	EXPECT_FLOAT_EQ(test2.m_mat[4], 55.0);
	EXPECT_FLOAT_EQ(test2.m_mat[5], 66.0);
	EXPECT_FLOAT_EQ(test2.m_mat[6], 77.0);
	EXPECT_FLOAT_EQ(test2.m_mat[7], 88.0);
	EXPECT_FLOAT_EQ(test2.m_mat[8], 99.0);
	etk::Matrix3 test3(test2);
	EXPECT_FLOAT_EQ(test3.m_mat[0], 11.0);
	EXPECT_FLOAT_EQ(test3.m_mat[1], 22.0);
	EXPECT_FLOAT_EQ(test3.m_mat[2], 33.0);
	EXPECT_FLOAT_EQ(test3.m_mat[3], 44.0);
	EXPECT_FLOAT_EQ(test3.m_mat[4], 55.0);
	EXPECT_FLOAT_EQ(test3.m_mat[5], 66.0);
	EXPECT_FLOAT_EQ(test3.m_mat[6], 77.0);
	EXPECT_FLOAT_EQ(test3.m_mat[7], 88.0);
	EXPECT_FLOAT_EQ(test3.m_mat[8], 99.0);
	etk::Matrix3 test4 = test1;
	EXPECT_FLOAT_EQ(test4.m_mat[0], 99.0);
	EXPECT_FLOAT_EQ(test4.m_mat[1], 99.0);
	EXPECT_FLOAT_EQ(test4.m_mat[2], 99.0);
	EXPECT_FLOAT_EQ(test4.m_mat[3], 99.0);
	EXPECT_FLOAT_EQ(test4.m_mat[4], 99.0);
	EXPECT_FLOAT_EQ(test4.m_mat[5], 99.0);
	EXPECT_FLOAT_EQ(test4.m_mat[6], 99.0);
	EXPECT_FLOAT_EQ(test4.m_mat[7], 99.0);
	EXPECT_FLOAT_EQ(test4.m_mat[8], 99.0);
	test1 = test3;
	EXPECT_FLOAT_EQ(test1.m_mat[0], 11.0);
	EXPECT_FLOAT_EQ(test1.m_mat[1], 22.0);
	EXPECT_FLOAT_EQ(test1.m_mat[2], 33.0);
	EXPECT_FLOAT_EQ(test1.m_mat[3], 44.0);
	EXPECT_FLOAT_EQ(test1.m_mat[4], 55.0);
	EXPECT_FLOAT_EQ(test1.m_mat[5], 66.0);
	EXPECT_FLOAT_EQ(test1.m_mat[6], 77.0);
	EXPECT_FLOAT_EQ(test1.m_mat[7], 88.0);
	EXPECT_FLOAT_EQ(test1.m_mat[8], 99.0);
}

TEST(TestMatrix3x3, equity) {
	etk::Matrix3 test1(99,32,56,92,56,32,45,12,54);
	etk::Matrix3 test2(11,22,33,44,55,66,77,88,99);
	etk::Matrix3 test3(11,22,33,44,55,66,77,88,99);
	EXPECT_EQ(test1 == test2, false);
	EXPECT_EQ(test1 != test2, true);
	EXPECT_EQ(test3 == test2, true);
	EXPECT_EQ(test3 != test2, false);
}

TEST(TestMatrix3x3, set) {
	etk::Matrix3 test;
	test.setValue(22, 54, 45, 985, 54, 87, 98, 6532, -8652);
	EXPECT_FLOAT_EQ(test.m_mat[0], 22.0);
	EXPECT_FLOAT_EQ(test.m_mat[1], 54.0);
	EXPECT_FLOAT_EQ(test.m_mat[2], 45.0);
	EXPECT_FLOAT_EQ(test.m_mat[3], 985.0);
	EXPECT_FLOAT_EQ(test.m_mat[4], 54.0);
	EXPECT_FLOAT_EQ(test.m_mat[5], 87.0);
	EXPECT_FLOAT_EQ(test.m_mat[6], 98.0);
	EXPECT_FLOAT_EQ(test.m_mat[7], 6532.0);
	EXPECT_FLOAT_EQ(test.m_mat[8], -8652.0);
	test.setZero();
	EXPECT_FLOAT_EQ(test.m_mat[0], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[1], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[2], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[3], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[4], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[5], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[6], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[7], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[8], 0.0);
	test.setIdentity();
	EXPECT_FLOAT_EQ(test.m_mat[0], 1.0);
	EXPECT_FLOAT_EQ(test.m_mat[1], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[2], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[3], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[4], 1.0);
	EXPECT_FLOAT_EQ(test.m_mat[5], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[6], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[7], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[8], 1.0);
	test = etk::Matrix3::zero();
	EXPECT_FLOAT_EQ(test.m_mat[0], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[1], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[2], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[3], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[4], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[5], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[6], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[7], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[8], 0.0);
	test = etk::Matrix3::identity();
	EXPECT_FLOAT_EQ(test.m_mat[0], 1.0);
	EXPECT_FLOAT_EQ(test.m_mat[1], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[2], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[3], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[4], 1.0);
	EXPECT_FLOAT_EQ(test.m_mat[5], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[6], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[7], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[8], 1.0);
}

TEST(TestMatrix3x3, getRowColomn) {
	etk::Matrix3 test(11, 22, 33, 44, 55, 66, 77, 88, 99);
	EXPECT_FLOAT_EQ(test.getColumn(0).x(), 11.0);
	EXPECT_FLOAT_EQ(test.getColumn(0).y(), 44.0);
	EXPECT_FLOAT_EQ(test.getColumn(0).z(), 77.0);
	EXPECT_FLOAT_EQ(test.getColumn(1).x(), 22.0);
	EXPECT_FLOAT_EQ(test.getColumn(1).y(), 55.0);
	EXPECT_FLOAT_EQ(test.getColumn(1).z(), 88.0);
	EXPECT_FLOAT_EQ(test.getColumn(2).x(), 33.0);
	EXPECT_FLOAT_EQ(test.getColumn(2).y(), 66.0);
	EXPECT_FLOAT_EQ(test.getColumn(2).z(), 99.0);
	EXPECT_FLOAT_EQ(test.getColumn(999).x(), 33.0);
	EXPECT_FLOAT_EQ(test.getColumn(999).y(), 66.0);
	EXPECT_FLOAT_EQ(test.getColumn(999).z(), 99.0);
	EXPECT_FLOAT_EQ(test.getRow(0).x(), 11.0);
	EXPECT_FLOAT_EQ(test.getRow(0).y(), 22.0);
	EXPECT_FLOAT_EQ(test.getRow(0).z(), 33.0);
	EXPECT_FLOAT_EQ(test.getRow(1).x(), 44.0);
	EXPECT_FLOAT_EQ(test.getRow(1).y(), 55.0);
	EXPECT_FLOAT_EQ(test.getRow(1).z(), 66.0);
	EXPECT_FLOAT_EQ(test.getRow(2).x(), 77.0);
	EXPECT_FLOAT_EQ(test.getRow(2).y(), 88.0);
	EXPECT_FLOAT_EQ(test.getRow(2).z(), 99.0);
	EXPECT_FLOAT_EQ(test.getRow(999).x(), 77.0);
	EXPECT_FLOAT_EQ(test.getRow(999).y(), 88.0);
	EXPECT_FLOAT_EQ(test.getRow(999).z(), 99.0);
}

TEST(TestMatrix3x3, transpose) {
	etk::Matrix3 test(11, 22, 33, 44, 55, 66, 77, 88, 99);
	etk::Matrix3 test2 = test.getTranspose();
	EXPECT_FLOAT_EQ(test2.m_mat[0], 11.0);
	EXPECT_FLOAT_EQ(test2.m_mat[1], 44.0);
	EXPECT_FLOAT_EQ(test2.m_mat[2], 77.0);
	EXPECT_FLOAT_EQ(test2.m_mat[3], 22.0);
	EXPECT_FLOAT_EQ(test2.m_mat[4], 55.0);
	EXPECT_FLOAT_EQ(test2.m_mat[5], 88.0);
	EXPECT_FLOAT_EQ(test2.m_mat[6], 33.0);
	EXPECT_FLOAT_EQ(test2.m_mat[7], 66.0);
	EXPECT_FLOAT_EQ(test2.m_mat[8], 99.0);
	// check if original matrix is not transposed
	EXPECT_FLOAT_EQ(test.m_mat[0], 11.0);
	EXPECT_FLOAT_EQ(test.m_mat[1], 22.0);
	EXPECT_FLOAT_EQ(test.m_mat[2], 33.0);
	EXPECT_FLOAT_EQ(test.m_mat[3], 44.0);
	EXPECT_FLOAT_EQ(test.m_mat[4], 55.0);
	EXPECT_FLOAT_EQ(test.m_mat[5], 66.0);
	EXPECT_FLOAT_EQ(test.m_mat[6], 77.0);
	EXPECT_FLOAT_EQ(test.m_mat[7], 88.0);
	EXPECT_FLOAT_EQ(test.m_mat[8], 99.0);
	test.transpose();
	EXPECT_FLOAT_EQ(test.m_mat[0], 11.0);
	EXPECT_FLOAT_EQ(test.m_mat[1], 44.0);
	EXPECT_FLOAT_EQ(test.m_mat[2], 77.0);
	EXPECT_FLOAT_EQ(test.m_mat[3], 22.0);
	EXPECT_FLOAT_EQ(test.m_mat[4], 55.0);
	EXPECT_FLOAT_EQ(test.m_mat[5], 88.0);
	EXPECT_FLOAT_EQ(test.m_mat[6], 33.0);
	EXPECT_FLOAT_EQ(test.m_mat[7], 66.0);
	EXPECT_FLOAT_EQ(test.m_mat[8], 99.0);
}

TEST(TestMatrix3x3, determinant) {
	etk::Matrix3 test(11, -6, 6, 4, -5, 1, 8, -9, -6);
	EXPECT_FLOAT_EQ(test.determinant(), 261.0);
	EXPECT_FLOAT_EQ(etk::Matrix3::identity().determinant(), 1.0);
}

TEST(TestMatrix3x3, trace) {
	etk::Matrix3 test(11, 22, 33, 44, 55, 66, 77, 88, 99);
	EXPECT_FLOAT_EQ(test.getTrace(), 165.0);
}

TEST(TestMatrix3x3, inverse) {
	etk::Matrix3 test(1, -4, 3, -6, 5, 6, 7, 8, 9);
	etk::Matrix3 test2 = test.getInverse();
	// check if original matrix is not inversed
	EXPECT_FLOAT_EQ(test.m_mat[0], 1.0);
	EXPECT_FLOAT_EQ(test.m_mat[1], -4.0);
	EXPECT_FLOAT_EQ(test.m_mat[2], 3.0);
	EXPECT_FLOAT_EQ(test.m_mat[3], -6.0);
	EXPECT_FLOAT_EQ(test.m_mat[4], 5.0);
	EXPECT_FLOAT_EQ(test.m_mat[5], 6.0);
	EXPECT_FLOAT_EQ(test.m_mat[6], 7.0);
	EXPECT_FLOAT_EQ(test.m_mat[7], 8.0);
	EXPECT_FLOAT_EQ(test.m_mat[8], 9.0);
	EXPECT_FLOAT_EQ(test2.m_mat[0], 0.0047169812);
	EXPECT_FLOAT_EQ(test2.m_mat[1], -0.094339617);
	EXPECT_FLOAT_EQ(test2.m_mat[2], 0.061320752);
	EXPECT_FLOAT_EQ(test2.m_mat[3], -0.1509434);
	EXPECT_FLOAT_EQ(test2.m_mat[4], 0.018867925);
	EXPECT_FLOAT_EQ(test2.m_mat[5], 0.03773585);
	EXPECT_FLOAT_EQ(test2.m_mat[6], 0.13050313);
	EXPECT_FLOAT_EQ(test2.m_mat[7], 0.056603771);
	EXPECT_FLOAT_EQ(test2.m_mat[8], 0.029874213);
	test.inverse();
	EXPECT_FLOAT_EQ(test.m_mat[0], 0.0047169812);
	EXPECT_FLOAT_EQ(test.m_mat[1], -0.094339617);
	EXPECT_FLOAT_EQ(test.m_mat[2], 0.061320752);
	EXPECT_FLOAT_EQ(test.m_mat[3], -0.1509434);
	EXPECT_FLOAT_EQ(test.m_mat[4], 0.018867925);
	EXPECT_FLOAT_EQ(test.m_mat[5], 0.03773585);
	EXPECT_FLOAT_EQ(test.m_mat[6], 0.13050313);
	EXPECT_FLOAT_EQ(test.m_mat[7], 0.056603771);
	EXPECT_FLOAT_EQ(test.m_mat[8], 0.029874213);
}

TEST(TestMatrix3x3, absolute) {
	etk::Matrix3 test(-1, -2, -3, -4, -5, -6, -7, -8, -9);
	etk::Matrix3 test2 = test.getAbsolute();
	// check if original matrix is not inversed
	EXPECT_FLOAT_EQ(test.m_mat[0], -1.0);
	EXPECT_FLOAT_EQ(test.m_mat[1], -2.0);
	EXPECT_FLOAT_EQ(test.m_mat[2], -3.0);
	EXPECT_FLOAT_EQ(test.m_mat[3], -4.0);
	EXPECT_FLOAT_EQ(test.m_mat[4], -5.0);
	EXPECT_FLOAT_EQ(test.m_mat[5], -6.0);
	EXPECT_FLOAT_EQ(test.m_mat[6], -7.0);
	EXPECT_FLOAT_EQ(test.m_mat[7], -8.0);
	EXPECT_FLOAT_EQ(test.m_mat[8], -9.0);
	EXPECT_FLOAT_EQ(test2.m_mat[0], 1.0);
	EXPECT_FLOAT_EQ(test2.m_mat[1], 2.0);
	EXPECT_FLOAT_EQ(test2.m_mat[2], 3.0);
	EXPECT_FLOAT_EQ(test2.m_mat[3], 4.0);
	EXPECT_FLOAT_EQ(test2.m_mat[4], 5.0);
	EXPECT_FLOAT_EQ(test2.m_mat[5], 6.0);
	EXPECT_FLOAT_EQ(test2.m_mat[6], 7.0);
	EXPECT_FLOAT_EQ(test2.m_mat[7], 8.0);
	EXPECT_FLOAT_EQ(test2.m_mat[8], 9.0);
	test.absolute();
	EXPECT_FLOAT_EQ(test.m_mat[0], 1.0);
	EXPECT_FLOAT_EQ(test.m_mat[1], 2.0);
	EXPECT_FLOAT_EQ(test.m_mat[2], 3.0);
	EXPECT_FLOAT_EQ(test.m_mat[3], 4.0);
	EXPECT_FLOAT_EQ(test.m_mat[4], 5.0);
	EXPECT_FLOAT_EQ(test.m_mat[5], 6.0);
	EXPECT_FLOAT_EQ(test.m_mat[6], 7.0);
	EXPECT_FLOAT_EQ(test.m_mat[7], 8.0);
	EXPECT_FLOAT_EQ(test.m_mat[8], 9.0);
}

TEST(TestMatrix3x3, operatorAddition) {
	etk::Matrix3 test1(-1, -2, -3, -4, -5, -6, -7, -8, -9);
	etk::Matrix3 test2(1, 2, 3, 4, 5, 6, 7, 8, 9);
	etk::Matrix3 test3 = test1 + test2;
	// check no change
	EXPECT_FLOAT_EQ(test1.m_mat[0], -1.0);
	EXPECT_FLOAT_EQ(test1.m_mat[1], -2.0);
	EXPECT_FLOAT_EQ(test1.m_mat[2], -3.0);
	EXPECT_FLOAT_EQ(test1.m_mat[3], -4.0);
	EXPECT_FLOAT_EQ(test1.m_mat[4], -5.0);
	EXPECT_FLOAT_EQ(test1.m_mat[5], -6.0);
	EXPECT_FLOAT_EQ(test1.m_mat[6], -7.0);
	EXPECT_FLOAT_EQ(test1.m_mat[7], -8.0);
	EXPECT_FLOAT_EQ(test1.m_mat[8], -9.0);
	EXPECT_FLOAT_EQ(test2.m_mat[0], 1.0);
	EXPECT_FLOAT_EQ(test2.m_mat[1], 2.0);
	EXPECT_FLOAT_EQ(test2.m_mat[2], 3.0);
	EXPECT_FLOAT_EQ(test2.m_mat[3], 4.0);
	EXPECT_FLOAT_EQ(test2.m_mat[4], 5.0);
	EXPECT_FLOAT_EQ(test2.m_mat[5], 6.0);
	EXPECT_FLOAT_EQ(test2.m_mat[6], 7.0);
	EXPECT_FLOAT_EQ(test2.m_mat[7], 8.0);
	EXPECT_FLOAT_EQ(test2.m_mat[8], 9.0);
	EXPECT_FLOAT_EQ(test3.m_mat[0], 0.0);
	EXPECT_FLOAT_EQ(test3.m_mat[1], 0.0);
	EXPECT_FLOAT_EQ(test3.m_mat[2], 0.0);
	EXPECT_FLOAT_EQ(test3.m_mat[3], 0.0);
	EXPECT_FLOAT_EQ(test3.m_mat[4], 0.0);
	EXPECT_FLOAT_EQ(test3.m_mat[5], 0.0);
	EXPECT_FLOAT_EQ(test3.m_mat[6], 0.0);
	EXPECT_FLOAT_EQ(test3.m_mat[7], 0.0);
	EXPECT_FLOAT_EQ(test3.m_mat[8], 0.0);
	test1 += test2;
	EXPECT_FLOAT_EQ(test1.m_mat[0], 0.0);
	EXPECT_FLOAT_EQ(test1.m_mat[1], 0.0);
	EXPECT_FLOAT_EQ(test1.m_mat[2], 0.0);
	EXPECT_FLOAT_EQ(test1.m_mat[3], 0.0);
	EXPECT_FLOAT_EQ(test1.m_mat[4], 0.0);
	EXPECT_FLOAT_EQ(test1.m_mat[5], 0.0);
	EXPECT_FLOAT_EQ(test1.m_mat[6], 0.0);
	EXPECT_FLOAT_EQ(test1.m_mat[7], 0.0);
	EXPECT_FLOAT_EQ(test1.m_mat[8], 0.0);
}

TEST(TestMatrix3x3, operatorSubstraction) {
	etk::Matrix3 test1(-1, -2, -3, -4, -5, -6, -7, -8, -9);
	etk::Matrix3 test2(1, 2, 3, 4, 5, 6, 7, 8, 9);
	etk::Matrix3 test3 = test1 - test2;
	// check no change
	EXPECT_FLOAT_EQ(test1.m_mat[0], -1.0);
	EXPECT_FLOAT_EQ(test1.m_mat[1], -2.0);
	EXPECT_FLOAT_EQ(test1.m_mat[2], -3.0);
	EXPECT_FLOAT_EQ(test1.m_mat[3], -4.0);
	EXPECT_FLOAT_EQ(test1.m_mat[4], -5.0);
	EXPECT_FLOAT_EQ(test1.m_mat[5], -6.0);
	EXPECT_FLOAT_EQ(test1.m_mat[6], -7.0);
	EXPECT_FLOAT_EQ(test1.m_mat[7], -8.0);
	EXPECT_FLOAT_EQ(test1.m_mat[8], -9.0);
	EXPECT_FLOAT_EQ(test2.m_mat[0], 1.0);
	EXPECT_FLOAT_EQ(test2.m_mat[1], 2.0);
	EXPECT_FLOAT_EQ(test2.m_mat[2], 3.0);
	EXPECT_FLOAT_EQ(test2.m_mat[3], 4.0);
	EXPECT_FLOAT_EQ(test2.m_mat[4], 5.0);
	EXPECT_FLOAT_EQ(test2.m_mat[5], 6.0);
	EXPECT_FLOAT_EQ(test2.m_mat[6], 7.0);
	EXPECT_FLOAT_EQ(test2.m_mat[7], 8.0);
	EXPECT_FLOAT_EQ(test2.m_mat[8], 9.0);
	EXPECT_FLOAT_EQ(test3.m_mat[0], -2.0);
	EXPECT_FLOAT_EQ(test3.m_mat[1], -4.0);
	EXPECT_FLOAT_EQ(test3.m_mat[2], -6.0);
	EXPECT_FLOAT_EQ(test3.m_mat[3], -8.0);
	EXPECT_FLOAT_EQ(test3.m_mat[4], -10.0);
	EXPECT_FLOAT_EQ(test3.m_mat[5], -12.0);
	EXPECT_FLOAT_EQ(test3.m_mat[6], -14.0);
	EXPECT_FLOAT_EQ(test3.m_mat[7], -16.0);
	EXPECT_FLOAT_EQ(test3.m_mat[8], -18.0);
	test1 -= test2;
	EXPECT_FLOAT_EQ(test1.m_mat[0], -2.0);
	EXPECT_FLOAT_EQ(test1.m_mat[1], -4.0);
	EXPECT_FLOAT_EQ(test1.m_mat[2], -6.0);
	EXPECT_FLOAT_EQ(test1.m_mat[3], -8.0);
	EXPECT_FLOAT_EQ(test1.m_mat[4], -10.0);
	EXPECT_FLOAT_EQ(test1.m_mat[5], -12.0);
	EXPECT_FLOAT_EQ(test1.m_mat[6], -14.0);
	EXPECT_FLOAT_EQ(test1.m_mat[7], -16.0);
	EXPECT_FLOAT_EQ(test1.m_mat[8], -18.0);
}

TEST(TestMatrix3x3, operatorNegation) {
	etk::Matrix3 test1(-1, -2, -3, -4, -5, -6, -7, -8, -9);
	etk::Matrix3 test2 = -test1;
	// check no change
	EXPECT_FLOAT_EQ(test1.m_mat[0], -1.0);
	EXPECT_FLOAT_EQ(test1.m_mat[1], -2.0);
	EXPECT_FLOAT_EQ(test1.m_mat[2], -3.0);
	EXPECT_FLOAT_EQ(test1.m_mat[3], -4.0);
	EXPECT_FLOAT_EQ(test1.m_mat[4], -5.0);
	EXPECT_FLOAT_EQ(test1.m_mat[5], -6.0);
	EXPECT_FLOAT_EQ(test1.m_mat[6], -7.0);
	EXPECT_FLOAT_EQ(test1.m_mat[7], -8.0);
	EXPECT_FLOAT_EQ(test1.m_mat[8], -9.0);
	EXPECT_FLOAT_EQ(test2.m_mat[0], 1.0);
	EXPECT_FLOAT_EQ(test2.m_mat[1], 2.0);
	EXPECT_FLOAT_EQ(test2.m_mat[2], 3.0);
	EXPECT_FLOAT_EQ(test2.m_mat[3], 4.0);
	EXPECT_FLOAT_EQ(test2.m_mat[4], 5.0);
	EXPECT_FLOAT_EQ(test2.m_mat[5], 6.0);
	EXPECT_FLOAT_EQ(test2.m_mat[6], 7.0);
	EXPECT_FLOAT_EQ(test2.m_mat[7], 8.0);
	EXPECT_FLOAT_EQ(test2.m_mat[8], 9.0);
}

TEST(TestMatrix3x3, operatorMultiplicationMatrix) {
	etk::Matrix3 test1(-1, -2, -3, -4, -5, -6, -7, -8, -9);
	etk::Matrix3 test2(1, 2, 3, 4, 5, 6, 7, 8, 9);
	etk::Matrix3 test3 = test1 * test2;
	EXPECT_FLOAT_EQ(test1.m_mat[0], -1.0);
	EXPECT_FLOAT_EQ(test1.m_mat[1], -2.0);
	EXPECT_FLOAT_EQ(test1.m_mat[2], -3.0);
	EXPECT_FLOAT_EQ(test1.m_mat[3], -4.0);
	EXPECT_FLOAT_EQ(test1.m_mat[4], -5.0);
	EXPECT_FLOAT_EQ(test1.m_mat[5], -6.0);
	EXPECT_FLOAT_EQ(test1.m_mat[6], -7.0);
	EXPECT_FLOAT_EQ(test1.m_mat[7], -8.0);
	EXPECT_FLOAT_EQ(test1.m_mat[8], -9.0);
	EXPECT_FLOAT_EQ(test2.m_mat[0], 1.0);
	EXPECT_FLOAT_EQ(test2.m_mat[1], 2.0);
	EXPECT_FLOAT_EQ(test2.m_mat[2], 3.0);
	EXPECT_FLOAT_EQ(test2.m_mat[3], 4.0);
	EXPECT_FLOAT_EQ(test2.m_mat[4], 5.0);
	EXPECT_FLOAT_EQ(test2.m_mat[5], 6.0);
	EXPECT_FLOAT_EQ(test2.m_mat[6], 7.0);
	EXPECT_FLOAT_EQ(test2.m_mat[7], 8.0);
	EXPECT_FLOAT_EQ(test2.m_mat[8], 9.0);
	EXPECT_FLOAT_EQ(test3.m_mat[0], -30);
	EXPECT_FLOAT_EQ(test3.m_mat[1], -36);
	EXPECT_FLOAT_EQ(test3.m_mat[2], -42);
	EXPECT_FLOAT_EQ(test3.m_mat[3], -66);
	EXPECT_FLOAT_EQ(test3.m_mat[4], -81);
	EXPECT_FLOAT_EQ(test3.m_mat[5], -96);
	EXPECT_FLOAT_EQ(test3.m_mat[6], -102);
	EXPECT_FLOAT_EQ(test3.m_mat[7], -126);
	EXPECT_FLOAT_EQ(test3.m_mat[8], -150);
	test1 *= test2;
	EXPECT_FLOAT_EQ(test1.m_mat[0], -30);
	EXPECT_FLOAT_EQ(test1.m_mat[1], -36);
	EXPECT_FLOAT_EQ(test1.m_mat[2], -42);
	EXPECT_FLOAT_EQ(test1.m_mat[3], -66);
	EXPECT_FLOAT_EQ(test1.m_mat[4], -81);
	EXPECT_FLOAT_EQ(test1.m_mat[5], -96);
	EXPECT_FLOAT_EQ(test1.m_mat[6], -102);
	EXPECT_FLOAT_EQ(test1.m_mat[7], -126);
	EXPECT_FLOAT_EQ(test1.m_mat[8], -150);
}

TEST(TestMatrix3x3, operatorMultiplicationVector) {
	etk::Matrix3 test1(1, 2, 3, 4, 5, 6, 7, 8, 9);
	vec3 result = test1 * vec3(1,2,3);
	EXPECT_FLOAT_EQ(result.x(), 14.0);
	EXPECT_FLOAT_EQ(result.y(), 32.0);
	EXPECT_FLOAT_EQ(result.z(), 50.0);
}

