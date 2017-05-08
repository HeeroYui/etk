/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */

#include <gtest/gtest.h>
#include <ememory/memory.hpp>
#include <test-debug/debug.hpp>
#define NAME "Shared_ptr"

class Example : public ememory::EnableSharedFromThis<Example> {
	protected:
		int32_t m_id;
	public:
		Example() {
			static int32_t mid = 0;
			m_id = mid++;
			std::cout << "create Example [" << m_id << "]" << std::endl;
		}
		~Example() {
			std::cout << "Remove Example [" << m_id << "]" << std::endl;
		}
};



TEST(TestSTDSharedPtr, testBaseLocal) {
	Example();
}

TEST(TestSTDSharedPtr, testBaseShared) {
	ememory::SharedPtr<Example> tmp = ememory::makeShared<Example>();
}


TEST(TestSTDSharedPtr, testBaseSharedDouble) {
	ememory::SharedPtr<Example> tmp = ememory::makeShared<Example>();
	ememory::SharedPtr<Example> tmp2 = tmp;
}
/*
TEST(TestSTDSharedPtr, testBaseSharedDirectAndShared) {
	Example tmp;
	ememory::SharedPtr<Example> tmp2 = ememory::makeShared<tmp>;
}
*/