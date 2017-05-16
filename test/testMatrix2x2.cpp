/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */

#include <gtest/gtest.h>
#include <etk/math/Matrix2x2.hpp>
#include <test-debug/debug.hpp>

#define NAME "etk::Matrix2x2"

TEST(TestMatrix2x2, constructor) {
	// Test contructor value
	etk::Matrix2x2 test1(99.0);
	EXPECT_FLOAT_EQ(test1.m_mat[0], 99.0);
	EXPECT_FLOAT_EQ(test1.m_mat[1], 99.0);
	EXPECT_FLOAT_EQ(test1.m_mat[2], 99.0);
	EXPECT_FLOAT_EQ(test1.m_mat[3], 99.0);
	etk::Matrix2x2 test2(11,22,33,44);
	EXPECT_FLOAT_EQ(test2.m_mat[0], 11.0);
	EXPECT_FLOAT_EQ(test2.m_mat[1], 22.0);
	EXPECT_FLOAT_EQ(test2.m_mat[2], 33.0);
	EXPECT_FLOAT_EQ(test2.m_mat[3], 44.0);
	etk::Matrix2x2 test3(test2);
	EXPECT_FLOAT_EQ(test3.m_mat[0], 11.0);
	EXPECT_FLOAT_EQ(test3.m_mat[1], 22.0);
	EXPECT_FLOAT_EQ(test3.m_mat[2], 33.0);
	EXPECT_FLOAT_EQ(test3.m_mat[3], 44.0);
	etk::Matrix2x2 test4 = test1;
	EXPECT_FLOAT_EQ(test4.m_mat[0], 99.0);
	EXPECT_FLOAT_EQ(test4.m_mat[1], 99.0);
	EXPECT_FLOAT_EQ(test4.m_mat[2], 99.0);
	EXPECT_FLOAT_EQ(test4.m_mat[3], 99.0);
	test1 = test3;
	EXPECT_FLOAT_EQ(test1.m_mat[0], 11.0);
	EXPECT_FLOAT_EQ(test1.m_mat[1], 22.0);
	EXPECT_FLOAT_EQ(test1.m_mat[2], 33.0);
	EXPECT_FLOAT_EQ(test1.m_mat[3], 44.0);
}

TEST(TestMatrix2x2, equity) {
	etk::Matrix2x2 test1(99,32,56,92);
	etk::Matrix2x2 test2(11,22,33,44);
	etk::Matrix2x2 test3(11,22,33,44);
	EXPECT_EQ(test1 == test2, false);
	EXPECT_EQ(test1 != test2, true);
	EXPECT_EQ(test3 == test2, true);
	EXPECT_EQ(test3 != test2, false);
}

TEST(TestMatrix2x2, set) {
	etk::Matrix2x2 test;
	test.setValue(22, 54, 45, 985);
	EXPECT_FLOAT_EQ(test.m_mat[0], 22.0);
	EXPECT_FLOAT_EQ(test.m_mat[1], 54.0);
	EXPECT_FLOAT_EQ(test.m_mat[2], 45.0);
	EXPECT_FLOAT_EQ(test.m_mat[3], 985.0);
	test.setZero();
	EXPECT_FLOAT_EQ(test.m_mat[0], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[1], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[2], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[3], 0.0);
	test.setIdentity();
	EXPECT_FLOAT_EQ(test.m_mat[0], 1.0);
	EXPECT_FLOAT_EQ(test.m_mat[1], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[2], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[3], 1.0);
	test = etk::Matrix2x2::zero();
	EXPECT_FLOAT_EQ(test.m_mat[0], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[1], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[2], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[3], 0.0);
	test = etk::Matrix2x2::identity();
	EXPECT_FLOAT_EQ(test.m_mat[0], 1.0);
	EXPECT_FLOAT_EQ(test.m_mat[1], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[2], 0.0);
	EXPECT_FLOAT_EQ(test.m_mat[3], 1.0);
}

TEST(TestMatrix2x2, getRowColomn) {
	etk::Matrix2x2 test(11, 22, 33, 44);
	EXPECT_FLOAT_EQ(test.getColumn(0).x(), 11.0);
	EXPECT_FLOAT_EQ(test.getColumn(0).y(), 33.0);
	EXPECT_FLOAT_EQ(test.getColumn(1).x(), 22.0);
	EXPECT_FLOAT_EQ(test.getColumn(1).y(), 44.0);
	EXPECT_FLOAT_EQ(test.getColumn(999).x(), 22.0);
	EXPECT_FLOAT_EQ(test.getColumn(999).y(), 44.0);
	EXPECT_FLOAT_EQ(test.getRow(0).x(), 11.0);
	EXPECT_FLOAT_EQ(test.getRow(0).y(), 22.0);
	EXPECT_FLOAT_EQ(test.getRow(1).x(), 33.0);
	EXPECT_FLOAT_EQ(test.getRow(1).y(), 44.0);
	EXPECT_FLOAT_EQ(test.getRow(999).x(), 33.0);
	EXPECT_FLOAT_EQ(test.getRow(999).y(), 44.0);
}

TEST(TestMatrix2x2, transpose) {
	etk::Matrix2x2 test(11, 22, 33, 44);
	etk::Matrix2x2 test2 = test.getTranspose();
	EXPECT_FLOAT_EQ(test2.m_mat[0], 11.0);
	EXPECT_FLOAT_EQ(test2.m_mat[1], 33.0);
	EXPECT_FLOAT_EQ(test2.m_mat[2], 22.0);
	EXPECT_FLOAT_EQ(test2.m_mat[3], 44.0);
	// check if original matrix is not transposed
	EXPECT_FLOAT_EQ(test.m_mat[0], 11.0);
	EXPECT_FLOAT_EQ(test.m_mat[1], 22.0);
	EXPECT_FLOAT_EQ(test.m_mat[2], 33.0);
	EXPECT_FLOAT_EQ(test.m_mat[3], 44.0);
	test.transpose();
	EXPECT_FLOAT_EQ(test.m_mat[0], 11.0);
	EXPECT_FLOAT_EQ(test.m_mat[1], 33.0);
	EXPECT_FLOAT_EQ(test.m_mat[2], 22.0);
	EXPECT_FLOAT_EQ(test.m_mat[3], 44.0);
}

TEST(TestMatrix2x2, determinant) {
	etk::Matrix2x2 test(11, 22, 33, 44);
	EXPECT_FLOAT_EQ(test.determinant(), -242.0);
	EXPECT_FLOAT_EQ(etk::Matrix2x2::identity().determinant(), 1.0);
}

TEST(TestMatrix2x2, trace) {
	etk::Matrix2x2 test(11, 22, 33, 44);
	EXPECT_FLOAT_EQ(test.getTrace(), 55.0);
}

TEST(TestMatrix2x2, inverse) {
	etk::Matrix2x2 test(1, 2, 3, 4);
	etk::Matrix2x2 test2 = test.getInverse();
	// check if original matrix is not inversed
	EXPECT_FLOAT_EQ(test.m_mat[0], 1.0);
	EXPECT_FLOAT_EQ(test.m_mat[1], 2.0);
	EXPECT_FLOAT_EQ(test.m_mat[2], 3.0);
	EXPECT_FLOAT_EQ(test.m_mat[3], 4.0);
	EXPECT_FLOAT_EQ(test2.m_mat[0], -2.0);
	EXPECT_FLOAT_EQ(test2.m_mat[1], 1.0);
	EXPECT_FLOAT_EQ(test2.m_mat[2], 1.5);
	EXPECT_FLOAT_EQ(test2.m_mat[3], -0.5);
	test.inverse();
	EXPECT_FLOAT_EQ(test.m_mat[0], -2.0);
	EXPECT_FLOAT_EQ(test.m_mat[1], 1.0);
	EXPECT_FLOAT_EQ(test.m_mat[2], 1.5);
	EXPECT_FLOAT_EQ(test.m_mat[3], -0.5);
}

TEST(TestMatrix2x2, absolute) {
	etk::Matrix2x2 test(-1, -2, -3, -4);
	etk::Matrix2x2 test2 = test.getAbsolute();
	// check if original matrix is not inversed
	EXPECT_FLOAT_EQ(test.m_mat[0], -1.0);
	EXPECT_FLOAT_EQ(test.m_mat[1], -2.0);
	EXPECT_FLOAT_EQ(test.m_mat[2], -3.0);
	EXPECT_FLOAT_EQ(test.m_mat[3], -4.0);
	EXPECT_FLOAT_EQ(test2.m_mat[0], 1.0);
	EXPECT_FLOAT_EQ(test2.m_mat[1], 2.0);
	EXPECT_FLOAT_EQ(test2.m_mat[2], 3.0);
	EXPECT_FLOAT_EQ(test2.m_mat[3], 4.0);
	test.absolute();
	EXPECT_FLOAT_EQ(test.m_mat[0], 1.0);
	EXPECT_FLOAT_EQ(test.m_mat[1], 2.0);
	EXPECT_FLOAT_EQ(test.m_mat[2], 3.0);
	EXPECT_FLOAT_EQ(test.m_mat[3], 4.0);
}

TEST(TestMatrix2x2, operatorAddition) {
	etk::Matrix2x2 test1(-1, -2, -3, -4);
	etk::Matrix2x2 test2(1, 2, 3, 4);
	etk::Matrix2x2 test3 = test1 + test2;
	// check no change
	EXPECT_FLOAT_EQ(test1.m_mat[0], -1.0);
	EXPECT_FLOAT_EQ(test1.m_mat[1], -2.0);
	EXPECT_FLOAT_EQ(test1.m_mat[2], -3.0);
	EXPECT_FLOAT_EQ(test1.m_mat[3], -4.0);
	EXPECT_FLOAT_EQ(test2.m_mat[0], 1.0);
	EXPECT_FLOAT_EQ(test2.m_mat[1], 2.0);
	EXPECT_FLOAT_EQ(test2.m_mat[2], 3.0);
	EXPECT_FLOAT_EQ(test2.m_mat[3], 4.0);
	EXPECT_FLOAT_EQ(test3.m_mat[0], 0.0);
	EXPECT_FLOAT_EQ(test3.m_mat[1], 0.0);
	EXPECT_FLOAT_EQ(test3.m_mat[2], 0.0);
	EXPECT_FLOAT_EQ(test3.m_mat[3], 0.0);
	
	test1 += test2;
	EXPECT_FLOAT_EQ(test1.m_mat[0], 0.0);
	EXPECT_FLOAT_EQ(test1.m_mat[1], 0.0);
	EXPECT_FLOAT_EQ(test1.m_mat[2], 0.0);
	EXPECT_FLOAT_EQ(test1.m_mat[3], 0.0);
}

TEST(TestMatrix2x2, operatorSubstraction) {
	etk::Matrix2x2 test1(-1, -2, -3, -4);
	etk::Matrix2x2 test2(1, 2, 3, 4);
	etk::Matrix2x2 test3 = test1 - test2;
	// check no change
	EXPECT_FLOAT_EQ(test1.m_mat[0], -1.0);
	EXPECT_FLOAT_EQ(test1.m_mat[1], -2.0);
	EXPECT_FLOAT_EQ(test1.m_mat[2], -3.0);
	EXPECT_FLOAT_EQ(test1.m_mat[3], -4.0);
	EXPECT_FLOAT_EQ(test2.m_mat[0], 1.0);
	EXPECT_FLOAT_EQ(test2.m_mat[1], 2.0);
	EXPECT_FLOAT_EQ(test2.m_mat[2], 3.0);
	EXPECT_FLOAT_EQ(test2.m_mat[3], 4.0);
	EXPECT_FLOAT_EQ(test3.m_mat[0], -2.0);
	EXPECT_FLOAT_EQ(test3.m_mat[1], -4.0);
	EXPECT_FLOAT_EQ(test3.m_mat[2], -6.0);
	EXPECT_FLOAT_EQ(test3.m_mat[3], -8.0);
	test1 -= test2;
	EXPECT_FLOAT_EQ(test1.m_mat[0], -2.0);
	EXPECT_FLOAT_EQ(test1.m_mat[1], -4.0);
	EXPECT_FLOAT_EQ(test1.m_mat[2], -6.0);
	EXPECT_FLOAT_EQ(test1.m_mat[3], -8.0);
}

TEST(TestMatrix2x2, operatorNegation) {
	etk::Matrix2x2 test1(-1, -2, -3, -4);
	etk::Matrix2x2 test2 = -test1;
	EXPECT_FLOAT_EQ(test1.m_mat[0], -1.0);
	EXPECT_FLOAT_EQ(test1.m_mat[1], -2.0);
	EXPECT_FLOAT_EQ(test1.m_mat[2], -3.0);
	EXPECT_FLOAT_EQ(test1.m_mat[3], -4.0);
	EXPECT_FLOAT_EQ(test2.m_mat[0], 1.0);
	EXPECT_FLOAT_EQ(test2.m_mat[1], 2.0);
	EXPECT_FLOAT_EQ(test2.m_mat[2], 3.0);
	EXPECT_FLOAT_EQ(test2.m_mat[3], 4.0);
}

TEST(TestMatrix2x2, operatorMultiplicationMatrix) {
	etk::Matrix2x2 test1(1, 2, 3, 4);
	etk::Matrix2x2 test2(5, 6, 7, 10);
	etk::Matrix2x2 test3 = test1 * test2;
	EXPECT_FLOAT_EQ(test1.m_mat[0], 1.0);
	EXPECT_FLOAT_EQ(test1.m_mat[1], 2.0);
	EXPECT_FLOAT_EQ(test1.m_mat[2], 3.0);
	EXPECT_FLOAT_EQ(test1.m_mat[3], 4.0);
	EXPECT_FLOAT_EQ(test2.m_mat[0], 5.0);
	EXPECT_FLOAT_EQ(test2.m_mat[1], 6.0);
	EXPECT_FLOAT_EQ(test2.m_mat[2], 7.0);
	EXPECT_FLOAT_EQ(test2.m_mat[3], 10.0);
	EXPECT_FLOAT_EQ(test3.m_mat[0], 19.0);
	EXPECT_FLOAT_EQ(test3.m_mat[1], 26.0);
	EXPECT_FLOAT_EQ(test3.m_mat[2], 43.0);
	EXPECT_FLOAT_EQ(test3.m_mat[3], 58.0);
	test1 *= test2;
	EXPECT_FLOAT_EQ(test1.m_mat[0], 19.0);
	EXPECT_FLOAT_EQ(test1.m_mat[1], 26.0);
	EXPECT_FLOAT_EQ(test1.m_mat[2], 43.0);
	EXPECT_FLOAT_EQ(test1.m_mat[3], 58.0);
}

TEST(TestMatrix2x2, operatorMultiplicationVector) {
	etk::Matrix2x2 test1(1, 2, 3, 4);
	vec2 result = test1 * vec2(1,2);
	EXPECT_FLOAT_EQ(result.x(), 5.0);
	EXPECT_FLOAT_EQ(result.y(), 11.0);
}

