/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */


#include <etk/Pair.hpp>
#include <etk/Vector.hpp>
#include <test-debug/debug.hpp>
#include <etest/etest.hpp>

TEST(TestVector, constructor) {
	// Test contructor value
	etk::Vector<float> test;
	EXPECT_EQ(test.size(), 0);
}

TEST(TestVector, constructor_2) {
	// Test contructor value
	etk::Vector<float> test(3.9f, 33.0f,55.8f);
	EXPECT_EQ(test.size(), 3);
	EXPECT_EQ(test[0], 3.9f);
	EXPECT_EQ(test[1], 33.0f);
	EXPECT_EQ(test[2], 55.8f);
}

TEST(TestVector, resize) {
	// Test contructor value
	etk::Vector<float> test;
	test.resize(3);
	EXPECT_EQ(test.size(), 3);
}
TEST(TestVector, empty) {
	// Test contructor value
	etk::Vector<float> test;
	EXPECT_EQ(test.empty(), true);
	test.pushBack(2);
	EXPECT_EQ(test.empty(), false);
}

TEST(TestVector, pushBack) {
	// Test contructor value
	etk::Vector<float> test;
	EXPECT_EQ(test.size(), 0);
	test.pushBack(2);
	EXPECT_EQ(test.size(), 1);
	EXPECT_EQ(test[0], 2);
	test.pushBack(4);
	EXPECT_EQ(test.size(), 2);
	EXPECT_EQ(test[0], 2);
	EXPECT_EQ(test[1], 4);
	test.pushBack(8);
	EXPECT_EQ(test.size(), 3);
	EXPECT_EQ(test[0], 2);
	EXPECT_EQ(test[1], 4);
	EXPECT_EQ(test[2], 8);
	test.popBack();
	EXPECT_EQ(test.size(), 2);
	EXPECT_EQ(test[0], 2);
	EXPECT_EQ(test[1], 4);
}

TEST(TestVector, pushFront) {
	// Test contructor value
	etk::Vector<float> test;
	EXPECT_EQ(test.size(), 0);
	test.pushBack(2);
	EXPECT_EQ(test.size(), 1);
	EXPECT_EQ(test[0], 2);
	test.pushBack(4);
	EXPECT_EQ(test.size(), 2);
	EXPECT_EQ(test[0], 2);
	EXPECT_EQ(test[1], 4);
	test.pushFront(8);
	EXPECT_EQ(test.size(), 3);
	EXPECT_EQ(test[0], 8);
	EXPECT_EQ(test[1], 2);
	EXPECT_EQ(test[2], 4);
	test.pushFront(55);
	EXPECT_EQ(test.size(), 4);
	EXPECT_EQ(test[0], 55);
	EXPECT_EQ(test[1], 8);
	EXPECT_EQ(test[2], 2);
	EXPECT_EQ(test[3], 4);
}

TEST(TestVector, insert) {
	// Test contructor value
	etk::Vector<float> test;
	EXPECT_EQ(test.size(), 0);
	test.pushBack(2);
	EXPECT_EQ(test.size(), 1);
	EXPECT_EQ(test[0], 2);
	test.pushBack(4);
	EXPECT_EQ(test.size(), 2);
	EXPECT_EQ(test[0], 2);
	EXPECT_EQ(test[1], 4);
	test.pushFront(8);
	EXPECT_EQ(test.size(), 3);
	EXPECT_EQ(test[0], 8);
	EXPECT_EQ(test[1], 2);
	EXPECT_EQ(test[2], 4);
	test.pushFront(55);
	EXPECT_EQ(test.size(), 4);
	EXPECT_EQ(test[0], 55);
	EXPECT_EQ(test[1], 8);
	EXPECT_EQ(test[2], 2);
	EXPECT_EQ(test[3], 4);
}

TEST(TestVector, back) {
	// Test contructor value
	etk::Vector<float> test;
	EXPECT_EQ(test.size(), 0);
	test.pushBack(2);
	test.pushBack(4);
	test.pushBack(8);
	EXPECT_EQ(test.size(), 3);
	EXPECT_EQ(test[0], 2);
	EXPECT_EQ(test[1], 4);
	EXPECT_EQ(test[2], 8);
	EXPECT_EQ(test.back(), 8);
}

TEST(TestVector, popBack) {
	// Test contructor value
	etk::Vector<float> test;
	EXPECT_EQ(test.size(), 0);
	test.pushBack(2);
	test.pushBack(4);
	test.pushBack(8);
	EXPECT_EQ(test.size(), 3);
	EXPECT_EQ(test[0], 2);
	EXPECT_EQ(test[1], 4);
	EXPECT_EQ(test[2], 8);
	test.popBack();
	EXPECT_EQ(test.size(), 2);
	EXPECT_EQ(test[0], 2);
	EXPECT_EQ(test[1], 4);
}

TEST(TestVector, front) {
	// Test contructor value
	etk::Vector<float> test;
	EXPECT_EQ(test.size(), 0);
	test.pushBack(2);
	test.pushBack(4);
	test.pushBack(8);
	EXPECT_EQ(test.size(), 3);
	EXPECT_EQ(test[0], 2);
	EXPECT_EQ(test[1], 4);
	EXPECT_EQ(test[2], 8);
	EXPECT_EQ(test.front(), 2);
}

TEST(TestVector, popFront) {
	// Test contructor value
	etk::Vector<float> test;
	EXPECT_EQ(test.size(), 0);
	test.pushBack(2);
	test.pushBack(4);
	test.pushBack(8);
	EXPECT_EQ(test.size(), 3);
	EXPECT_EQ(test[0], 2);
	EXPECT_EQ(test[1], 4);
	EXPECT_EQ(test[2], 8);
	test.popFront();
	EXPECT_EQ(test.size(), 2);
	EXPECT_EQ(test[0], 4);
	EXPECT_EQ(test[1], 8);
}


TEST(TestVector, initializationList_1) {
	// Test contructor value
	etk::Vector<int> test = {1, 5, 6, 8};
	EXPECT_EQ(test.size(), 4);
	EXPECT_EQ(test[0], 1);
	EXPECT_EQ(test[1], 5);
	EXPECT_EQ(test[2], 6);
	EXPECT_EQ(test[3], 8);
}

TEST(TestVector, initializationList_2) {
	// Test contructor value
	etk::Vector<int> test(1, 5, 6, 8);
	EXPECT_EQ(test.size(), 4);
	EXPECT_EQ(test[0], 1);
	EXPECT_EQ(test[1], 5);
	EXPECT_EQ(test[2], 6);
	EXPECT_EQ(test[3], 8);
}



static uint32_t isDestroy = 0;

class testContructDestruct {
	private:
		uint32_t m_addValue;
	public:
		testContructDestruct(uint32_t _addValue):
		  m_addValue(_addValue) {
			isDestroy += m_addValue;
			TEST_DEBUG("Create class " << m_addValue);
		}
		testContructDestruct(testContructDestruct&& _obj):
		  m_addValue(_obj.m_addValue) {
			_obj.m_addValue = 0;
			TEST_DEBUG("move contruction " << m_addValue);
		}
		virtual ~testContructDestruct() {
			if (m_addValue == 0) {
				TEST_DEBUG("Remove class (after move)");
				return;
			}
			TEST_DEBUG("Remove Class " << m_addValue);
			isDestroy -= m_addValue;
		}
		testContructDestruct& operator= (testContructDestruct&& _obj) {
			TEST_DEBUG("move operator " << m_addValue);
			if (this != &_obj) {
				etk::swap(m_addValue, _obj.m_addValue);
			}
			return *this;
		}
};

TEST(TestVector, destroyElementAtTheCorectMoment) {
	isDestroy = 0;
	{
		etk::Vector<testContructDestruct> list;
		list.pushBack(testContructDestruct(55));
		EXPECT_EQ(list.size(), 1);
		EXPECT_EQ(isDestroy, 55);
		auto it = list.erase(list.begin());
		EXPECT_EQ(isDestroy, 0);
		EXPECT_EQ(list.size(), 0);
		EXPECT_EQ(it, list.end());
	}
	EXPECT_EQ(isDestroy, 0);
}

TEST(TestVector, destroyElementAtTheCorectMoment_2) {
	isDestroy = 0;
	{
		etk::Vector<testContructDestruct> list;
		list.pushBack(testContructDestruct(4));
		list.pushBack(testContructDestruct(30));
		list.pushBack(testContructDestruct(1000));
		list.pushBack(testContructDestruct(200));
		EXPECT_EQ(list.size(), 4);
		EXPECT_EQ(isDestroy, 1234);
		auto it = list.erase(list.begin());
		EXPECT_EQ(list.size(), 3);
		EXPECT_EQ(isDestroy, 1230);
		it = list.erase(list.begin()+1);
		EXPECT_EQ(isDestroy, 230);
		EXPECT_EQ(list.size(), 2);
	}
	EXPECT_EQ(isDestroy, 0);
}

TEST(TestVector, allocateElementAtTheCorectMoment) {
	isDestroy = 0;
	{
		etk::Vector<testContructDestruct> list;
		list.reserve(10);
		EXPECT_EQ(list.size(), 0);
		EXPECT_EQ(isDestroy, 0);
	}
	EXPECT_EQ(isDestroy, 0);
}
