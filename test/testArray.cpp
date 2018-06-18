/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */


#include <etk/Pair.hpp>
#include <etk/Array.hpp>
#include <test-debug/debug.hpp>
#include <etest/etest.hpp>

TEST(TestArray, constructor) {
	// Test contructor value
	etk::Array<float, 20> test;
	EXPECT_EQ(test.size(), 0);
}

TEST(TestArray, constructor_2) {
	// Test contructor value
	etk::Array<float, 20> test(3.9f, 33.0f,55.8f);
	EXPECT_EQ(test.size(), 3);
	EXPECT_EQ(test[0], 3.9f);
	EXPECT_EQ(test[1], 33.0f);
	EXPECT_EQ(test[2], 55.8f);
}

TEST(TestArray, resize) {
	// Test contructor value
	etk::Array<float, 20> test;
	test.resize(3);
	EXPECT_EQ(test.size(), 3);
}
TEST(TestArray, empty) {
	// Test contructor value
	etk::Array<float, 20> test;
	EXPECT_EQ(test.empty(), true);
	test.pushBack(2);
	EXPECT_EQ(test.empty(), false);
}

TEST(TestArray, pushBack) {
	// Test contructor value
	etk::Array<float, 20> test;
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

TEST(TestArray, pushFront) {
	// Test contructor value
	etk::Array<float, 20> test;
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

TEST(TestArray, insert) {
	// Test contructor value
	etk::Array<float, 20> test;
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

TEST(TestArray, back) {
	// Test contructor value
	etk::Array<float, 20> test;
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

TEST(TestArray, popBack) {
	// Test contructor value
	etk::Array<float, 20> test;
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

TEST(TestArray, front) {
	// Test contructor value
	etk::Array<float, 20> test;
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

TEST(TestArray, popFront) {
	// Test contructor value
	etk::Array<float, 20> test;
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


TEST(TestArray, initializationList_1) {
	// Test contructor value
	etk::Array<int, 20> test = {1, 5, 6, 8};
	EXPECT_EQ(test.size(), 4);
	EXPECT_EQ(test[0], 1);
	EXPECT_EQ(test[1], 5);
	EXPECT_EQ(test[2], 6);
	EXPECT_EQ(test[3], 8);
}

TEST(TestArray, initializationList_2) {
	// Test contructor value
	etk::Array<int, 20> test(1, 5, 6, 8);
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

TEST(TestArray, destroyElementAtTheCorectMoment) {
	isDestroy = 0;
	{
		etk::Array<testContructDestruct, 20> list;
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

TEST(TestArray, destroyElementAtTheCorectMoment_2) {
	isDestroy = 0;
	{
		etk::Array<testContructDestruct, 20> list;
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

TEST(TestArray, allocateElementAtTheCorectMoment) {
	isDestroy = 0;
	{
		etk::Array<testContructDestruct, 20> list;
		list.reserve(10);
		EXPECT_EQ(list.size(), 0);
		EXPECT_EQ(isDestroy, 0);
	}
	EXPECT_EQ(isDestroy, 0);
}
/*
TEST(TestArray, allocateBench) {
	while (1) {
		etk::Array<uint8_t, 20> list;
		//list.reserve(1024*1024);
		for (size_t iii=0; iii < 1024*1024; ++iii) {
			list.pushBack(66);
		}
		EXPECT_EQ(list.size(), 1024*1024);
	}
}
*/


