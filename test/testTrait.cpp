/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etest/etest.hpp>
#include <etk/Color.hpp>
#include <test-debug/debug.hpp>
#define NAME "Color"

TEST(typeTrait, RemoveConstVolatile_1) {
	typedef std::remove_cv<const int>::type type1;
	EXPECT_EQ(etk::IsSame<int, type1>::value, true);
}
TEST(typeTrait, RemoveConstVolatile_2) {
	typedef std::remove_cv<volatile int>::type type1;
	EXPECT_EQ(etk::IsSame<int, type1>::value, true);
}
TEST(typeTrait, RemoveConstVolatile_3) {
	typedef std::remove_cv<const volatile int>::type type1;
	EXPECT_EQ(etk::IsSame<int, type1>::value, true);
}
TEST(typeTrait, RemoveConstVolatile_4) {
	typedef std::remove_cv<const volatile int*>::type type1;
	EXPECT_EQ(etk::IsSame<const volatile int*, type1>::value, true);
}
TEST(typeTrait, RemoveConstVolatile_5) {
	typedef std::remove_cv<int* const volatile>::type type1;
	EXPECT_EQ(etk::IsSame<int*, type1>::value, true);
}

TEST(typeTrait, IsVoid_1) {
	EXPECT_EQ(etk::IsVoid<void>::value, true);
}
TEST(typeTrait, IsVoid_2) {
	EXPECT_EQ(etk::IsVoid<int>::value, false);
}

class A {};

class B : A {};

class C {};

TEST(typeTrait, IsBaseOf_1) {
	EXPECT_EQ(etk::IsBaseOf<A, B>::value, true);
}

TEST(typeTrait, IsBaseOf_2) {
	EXPECT_EQ(etk::IsBaseOf<B, A>::value, false);
}

TEST(typeTrait, IsBaseOf_3) {
	EXPECT_EQ(etk::IsBaseOf<C, B>::value, false);
}

TEST(typeTrait, IsBaseOf_4) {
	EXPECT_EQ(etk::IsBaseOf<C, C>::value, true);
}


TEST(typeTrait, IsSame_1) {
	EXPECT_EQ(etk::IsSame<int, int32_t>::value, true);
}
TEST(typeTrait, IsSame_2) {
	EXPECT_EQ(etk::IsSame<int, int64_t>::value, false);
}
TEST(typeTrait, IsSame_3) {
	EXPECT_EQ(etk::IsSame<float, int32_t>::value, false);
}


TEST(typeTrait, IsSame_4) {
	EXPECT_EQ(etk::IsSame<int, int>::value, true);
}
TEST(typeTrait, IsSame_5) {
	EXPECT_EQ(etk::IsSame<int, unsigned int>::value, false);
}
TEST(typeTrait, IsSame_6) {
	EXPECT_EQ(etk::IsSame<int, signed int>::value, true);
}


TEST(typeTrait, IsSame_7) {
	EXPECT_EQ(etk::IsSame<char, char>::value, true);
}
TEST(typeTrait, IsSame_8) {
	EXPECT_EQ(etk::IsSame<char, unsigned char>::value, false);
}
TEST(typeTrait, IsSame_9) {
	EXPECT_EQ(etk::IsSame<char, signed char>::value, false);
}



struct K_A {};

class K_B {};

enum class K_C {};

TEST(typeTrait, IsClass_1) {
	EXPECT_EQ(etk::IsClass<K_A>::value, true);
}
TEST(typeTrait, IsClass_2) {
	EXPECT_EQ(etk::IsClass<K_B>::value, true);
}
TEST(typeTrait, IsClass_3) {
	EXPECT_EQ(etk::IsClass<K_C>::value, false);
}
TEST(typeTrait, IsClass_4) {
	EXPECT_EQ(etk::IsClass<int>::value, false);
}













#include <iostream>
#include <type_traits>

struct J_A {};

typedef union {
    int a;
    float b;
} J_B;

struct J_C {
    J_B d;
};

TEST(typeTrait, IsUnion_1) {
	EXPECT_EQ(etk::IsUnion<K_A>::value, false);
}
TEST(typeTrait, IsUnion_2) {
	EXPECT_EQ(etk::IsUnion<K_B>::value, true);
}
TEST(typeTrait, IsUnion_3) {
	EXPECT_EQ(etk::IsUnion<K_C>::value, false);
}
TEST(typeTrait, IsUnion_4) {
	EXPECT_EQ(etk::IsUnion<int>::value, false);
}


