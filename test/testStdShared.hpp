/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <gtest/gtest.h>
#include <memory>
#undef NAME
#define NAME "Shared_ptr"

class Example : public std::enable_shared_from_this<Example> {
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
	std::shared_ptr<Example> tmp = std::make_shared<Example>();
}


TEST(TestSTDSharedPtr, testBaseSharedDouble) {
	std::shared_ptr<Example> tmp = std::make_shared<Example>();
	std::shared_ptr<Example> tmp2 = tmp;
}
/*
TEST(TestSTDSharedPtr, testBaseSharedDirectAndShared) {
	Example tmp;
	std::shared_ptr<Example> tmp2 = std::make_shared<tmp>;
}
*/