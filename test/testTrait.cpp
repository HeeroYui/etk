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
	typedef etk::RemoveConstVolatile<const int>::type type1;
	auto ret = etk::IsSame<int, type1>::value;
	EXPECT_EQ(ret, true);
}
TEST(typeTrait, RemoveConstVolatile_2) {
	typedef etk::RemoveConstVolatile<volatile int>::type type1;
	auto ret = etk::IsSame<int, type1>::value;
	EXPECT_EQ(ret, true);
}
TEST(typeTrait, RemoveConstVolatile_3) {
	typedef etk::RemoveConstVolatile<const volatile int>::type type1;
	auto ret = etk::IsSame<int, type1>::value;
	EXPECT_EQ(ret, true);
}
TEST(typeTrait, RemoveConstVolatile_4) {
	typedef etk::RemoveConstVolatile<const volatile int*>::type type1;
	auto ret = etk::IsSame<const volatile int*, type1>::value;
	EXPECT_EQ(ret, true);
}
TEST(typeTrait, RemoveConstVolatile_5) {
	typedef etk::RemoveConstVolatile<int* const volatile>::type type1;
	auto ret = etk::IsSame<int*, type1>::value;
	EXPECT_EQ(ret, true);
}

TEST(typeTrait, IsVoid_1) {
	auto ret = etk::IsVoid<void>::value;
	EXPECT_EQ(ret, true);
}
TEST(typeTrait, IsVoid_2) {
	auto ret = etk::IsVoid<int>::value;
	EXPECT_EQ(ret, false);
}

class A {};

class B : A {};

class C {};

TEST(typeTrait, IsBaseOf_1) {
	auto ret = etk::IsBaseOf<A, B>::value;
	EXPECT_EQ(ret, true);
}

TEST(typeTrait, IsBaseOf_2) {
	auto ret = etk::IsBaseOf<B, A>::value;
	EXPECT_EQ(ret, false);
}

TEST(typeTrait, IsBaseOf_3) {
	auto ret = etk::IsBaseOf<C, B>::value;
	EXPECT_EQ(ret, false);
}

TEST(typeTrait, IsBaseOf_4) {
	auto ret = etk::IsBaseOf<C, C>::value;
	EXPECT_EQ(ret, true);
}



TEST(typeTrait, isSame_nullptr) {
	typedef etk::NullPtr type1;
	auto ret = etk::IsSame<etk::NullPtr, type1>::value;
	EXPECT_EQ(ret, true);
}
/*
TEST(typeTrait, isSame_nullptr2) {
	typedef etk::NullPtr type1;
	auto ret = etk::IsSame<nullptr, type1>::value;
	EXPECT_EQ(ret, true);
}
*/

TEST(typeTrait, IsSame_1) {
	auto ret = etk::IsSame<int, int32_t>::value;
	EXPECT_EQ(ret, true);
}
TEST(typeTrait, IsSame_2) {
	auto ret = etk::IsSame<int, int64_t>::value;
	EXPECT_EQ(ret, false);
}
TEST(typeTrait, IsSame_3) {
	auto ret = etk::IsSame<float, int32_t>::value;
	EXPECT_EQ(ret, false);
}


TEST(typeTrait, IsSame_4) {
	auto ret = etk::IsSame<int, int>::value;
	EXPECT_EQ(ret, true);
}
TEST(typeTrait, IsSame_5) {
	auto ret = etk::IsSame<int, unsigned int>::value;
	EXPECT_EQ(ret, false);
}
TEST(typeTrait, IsSame_6) {
	auto ret = etk::IsSame<int, signed int>::value;
	EXPECT_EQ(ret, true);
}


TEST(typeTrait, IsSame_7) {
	auto ret = etk::IsSame<char, char>::value;
	EXPECT_EQ(ret, true);
}
TEST(typeTrait, IsSame_8) {
	auto ret = etk::IsSame<char, unsigned char>::value;
	EXPECT_EQ(ret, false);
}
TEST(typeTrait, IsSame_9) {
	auto ret = etk::IsSame<char, signed char>::value;
	EXPECT_EQ(ret, false);
}



struct K_A {};

class K_B {};

enum class K_C {};

TEST(typeTrait, IsClass_1) {
	auto ret = etk::IsClass<K_A>::value;
	EXPECT_EQ(ret, true);
}
TEST(typeTrait, IsClass_2) {
	auto ret = etk::IsClass<K_B>::value;
	EXPECT_EQ(ret, true);
}
TEST(typeTrait, IsClass_3) {
	auto ret = etk::IsClass<K_C>::value;
	EXPECT_EQ(ret, false);
}
TEST(typeTrait, IsClass_4) {
	auto ret = etk::IsClass<int>::value;
	EXPECT_EQ(ret, false);
}





struct J_A {};

typedef union {
    int a;
    float b;
} J_B;

struct J_C {
    J_B d;
};

TEST(typeTrait, IsUnion_1) {
	auto ret = etk::IsUnion<K_A>::value;
	EXPECT_EQ(ret, false);
}
TEST(typeTrait, IsUnion_2) {
	auto ret = etk::IsUnion<K_B>::value;
	EXPECT_EQ(ret, true);
}
TEST(typeTrait, IsUnion_3) {
	auto ret = etk::IsUnion<K_C>::value;
	EXPECT_EQ(ret, false);
}
TEST(typeTrait, IsUnion_4) {
	auto ret = etk::IsUnion<int>::value;
	EXPECT_EQ(ret, false);
}


/*
	TEST_ERROR("plop1: " << (has_insertion_operator<etk::Vector2D<float>>::value));
	bool val = has_insertion_operator<etk::Pair<float,float>>::value;
	TEST_ERROR("plop2: " << val);
	TEST_ERROR("plop3: " << (has_insertion_operator<int32_t>::value));
	//etk::EnableIf<has_insertion_operator<etk::Pair<float,float>>::value, uint32_t>::type plop = 55;
	etk::EnableIf<has_insertion_operator<int32_t>::value, uint32_t>::type plop = 55;
*/

static uint32_t contructCount = 0;

class PlopMove {
	public:
		PlopMove() {
			contructCount ++;
		}
};

void hello(PlopMove _val) {
	contructCount += 1000;
}

TEST(typeMove, move_1) {
	contructCount = 0;
	PlopMove value;
	EXPECT_EQ(contructCount, 1);
	hello(etk::move(value));
	EXPECT_EQ(contructCount, 1001);
}


