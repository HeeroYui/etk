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
	etk::Function<void(int)> f_display = null;
	EXPECT_EQ(f_display, null);
}

TEST(TestFunction, setAFreeFunction) {
	globalValue = 0;
	// Test contructor value
	etk::Function<void(int32_t)> f_display = print_num;
	EXPECT_NE(f_display, null);
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
	EXPECT_NE(f_display, null);
}

TEST(TestFunction, callAlLambda) {
	globalValue = 0;
	// Test contructor value
	etk::Function<void()> f_display = []() { print_num(42); };
	f_display();
	EXPECT_EQ(globalValue, 42 + 1000);
}

class testObject {
	private:
		uint32_t m_id;
	public:
		testObject(int32_t iii) {
			m_id = iii;
			TEST_DEBUG("Call testObject Contructor " << m_id);
		}
		~testObject() {
			TEST_DEBUG("Call testObject Destructor " << m_id);
		}
		void operator() (int32_t iii) {
			globalValue = m_id + iii;
		}
};

/*
TEST(TestFunction, setCallableObject) {
	globalValue = 0;
	// Test contructor value
	testObject tmp(100000);
	etk::Function<void(int32_t)> f_display = tmp;
	EXPECT_NE(f_display, null);
}

TEST(TestFunction, callCallableObject) {
	globalValue = 0;
	// Test contructor value
	testObject tmp(550000);
	etk::Function<void(int32_t)> f_display = tmp;
	f_display(43);
	EXPECT_EQ(globalValue, 43 + 550000);
}
*/
etk::Function<void(int32_t)> createTmpFunction(uint32_t _value) {
	return [=](int32_t _data) { globalValue = _value + _data;};
}

TEST(TestFunction, setLambdaOnStack) {
	globalValue = 0;
	etk::Function<void(int32_t)> f_display = createTmpFunction(87000);
	EXPECT_NE(f_display, null);
}

TEST(TestFunction, callLambdaOnStack) {
	globalValue = 0;
	etk::Function<void(int32_t)> f_display = createTmpFunction(88000);
	f_display(44);
	EXPECT_EQ(globalValue, 44 + 88000);
}

/*
TEST(TestFunction, setAMemberFunction) {
	globalValue = 0;
	// Test contructor value
	etk::Function<void(const Foo&, int)> f_display = &Foo::print_add;
	EXPECT_NE(f_display, null);
}
TEST(TestFunction, callAMemberFunction) {
	globalValue = 0;
	// Test contructor value
	etk::Function<void(const Foo&, int)> f_display = &Foo::print_add;
	EXPECT_NE(f_display, null);
	Foo foo(70000);
	f_display(foo, 16);
	EXPECT_EQ(globalValue, 16 + 70000);
}
*/

