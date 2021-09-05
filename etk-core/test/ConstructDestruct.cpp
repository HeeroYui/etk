#include <test-debug/debug.hpp>
#include "ConstructDestruct.hpp"

static int32_t isDestroy = 0;

test::ConstructDestruct::ConstructDestruct(uint32_t _addValue):
  m_addValue(_addValue) {
	isDestroy += m_addValue;
	TEST_DEBUG("Create class " << m_addValue << " isDestroy=" << isDestroy);
}

test::ConstructDestruct::ConstructDestruct(test::ConstructDestruct&& _obj):
  m_addValue(_obj.m_addValue) {
	_obj.m_addValue = 0;
	TEST_DEBUG("move contruction " << m_addValue << " isDestroy=" << isDestroy);
}

test::ConstructDestruct::ConstructDestruct(const test::ConstructDestruct& _obj):
  m_addValue(_obj.m_addValue) {
	isDestroy += m_addValue;
	TEST_DEBUG("copy contruction " << m_addValue << " isDestroy=" << isDestroy);
}

test::ConstructDestruct::~ConstructDestruct() {
	if (m_addValue == 0) {
		TEST_DEBUG("Remove class (after move)" << " isDestroy=" << isDestroy);
		return;
	}
	isDestroy -= m_addValue;
	TEST_DEBUG("Remove Class " << m_addValue << " isDestroy=" << isDestroy);
}

test::ConstructDestruct& test::ConstructDestruct::operator= (test::ConstructDestruct&& _obj) {
	TEST_DEBUG("move operator " << m_addValue << " isDestroy=" << isDestroy);
	if (this != &_obj) {
		etk::swap(m_addValue, _obj.m_addValue);
	}
	return *this;
}

test::ConstructDestruct& test::ConstructDestruct::operator= (const test::ConstructDestruct& _obj) {
	TEST_DEBUG("opr operator " << m_addValue << " isDestroy=" << isDestroy);
	if (this != &_obj) {
		m_addValue = _obj.m_addValue;
		isDestroy += m_addValue;
	}
	return *this;
}

int32_t test::getIsDestroy() {
	return isDestroy;
}

void test::resetIsDestroy() {
	isDestroy = 0;
}

