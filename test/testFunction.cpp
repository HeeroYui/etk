/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */


#include <etk/Pair.hpp>
#include <etk/math/Vector2D.hpp>
#include <test-debug/debug.hpp>
#include <etest/etest.hpp>

static uint32_t globalValue = 0;

struct Foo {
	Foo(int32_t num) : m_num(num) {}
	void print_add(int32_t i) const {
		globalValue = m_num + i;
	}
	int32_t m_num;
};

void print_num(int32_t iii) {
	globalValue = 1000 + iii;
}

TEST(TestFunction, NullFunction) {
	globalValue = 0;
	// Test contructor value
	etk::Function<void(int)> f_display = nullptr;
	EXPECT_EQ(f_display, nullptr);
}

TEST(TestFunction, setAFreeFunction) {
	globalValue = 0;
	// Test contructor value
	etk::Function<void(int32_t)> f_display = print_num;
	EXPECT_NE(f_display, nullptr);
}
TEST(TestFunction, callAFreeFunction) {
	globalValue = 0;
	// Test contructor value
	etk::Function<void(int32_t)> f_display = print_num;
	f_display(235);
	EXPECT_EQ(globalValue, 235 + 1000);
}

TEST(TestFunction, setALambda) {
	globalValue = 0;
	// Test contructor value
	etk::Function<void()> f_display = []() { print_num(642); };;
	EXPECT_NE(f_display, nullptr);
}
TEST(TestFunction, callAlLambda) {
	globalValue = 0;
	// Test contructor value
	etk::Function<void()> f_display = []() { print_num(42); };
	f_display();
	EXPECT_EQ(globalValue, 42 + 1000);
}

TEST(TestFunction, setAMemberFunction) {
	globalValue = 0;
	// Test contructor value
	etk::Function<void(const Foo&, int)> f_display = &Foo::print_add;
	EXPECT_NE(f_display, nullptr);
}
TEST(TestFunction, callAMemberFunction) {
	globalValue = 0;
	// Test contructor value
	etk::Function<void(const Foo&, int)> f_display = &Foo::print_add;
	EXPECT_NE(f_display, nullptr);
	Foo foo(70000);
	f_display(foo, 16);
	EXPECT_EQ(globalValue, 16 + 70000);
}

