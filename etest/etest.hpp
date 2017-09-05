/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/String.hpp>

#define TEST_CLASS_NAME(groupName, localName) \
	groupName##_##localName##_test

namespace etest {
	class GenericTest {
		private:
			etk::String m_file;
			uint32_t m_line;
			etk::String m_testGroup;
			etk::String m_testName;
		public:
			GenericTest(const char* _file,
			            uint32_t _line,
			            const char* _testGroup,
			            const char* _testName);
			virtual ~GenericTest() = default;
			const etk::String& getFileName() const;
			uint32_t getFileLine() const;
			const etk::String& getTestGroup() const;
			const etk::String& getTestName() const;
			void testEqual(bool _result, const char* _test1, const char* _test2);
			void testNotEqual(bool _result, const char* _test1, const char* _test2);
			void clearLocal() {};
			virtual void run() = 0;
			
			template<class ETEST_TYPE, class ETEST_TYPE_2>
			void expectEq(const ETEST_TYPE& _element, const ETEST_TYPE_2& _result, const char* _elementChar, const char* _resultChar) {
				bool res = (_element == _result);
				testEqual(res, _elementChar, _resultChar);
			}
	};
	void unInit();
	void init(int32_t _argc, const char *_argv[]);
	int32_t runAllTest();
	uint32_t registerTest(etest::GenericTest* _element);
}

#define TEST(groupName,localName) \
	class TEST_CLASS_NAME(groupName, localName) : public etest::GenericTest { \
		protected: \
			static uint32_t registerElement; \
		public: \
			TEST_CLASS_NAME(groupName, localName)() : \
			  etest::GenericTest(__FILE__, __LINE__, #groupName, #localName) { \
				 \
			} \
			void run() override; \
	}; \
	\
	uint32_t TEST_CLASS_NAME(groupName, localName)::registerElement = etest::registerTest(new TEST_CLASS_NAME(groupName, localName)); \
	\
	void TEST_CLASS_NAME(groupName, localName)::run()

#define RUN_ALL_TESTS etest::runAllTest

#if 0
#define EXPECT_EQ(element, result) \
	do { \
		bool res = (element) == (result); \
		testEqual(res, "##element##", "##result##"); \
	} while (false)
#else
#define EXPECT_EQ(element, result) \
	do { \
		expectEq(element, result, "##element##", "##result##"); \
	} while (false)
#endif
#define EXPECT_NE(element, result) \
	do { \
		bool res = (element) != (result); \
		testNotEqual(res, "##element##", "##result##"); \
	} while (false)


#define EXPECT_FLOAT_EQ(element, result) \
	do { \
		float res2 = (element) - (result); \
		bool res = false; \
		if (res2 < 0.00001f && res2 > -0.00001f) { \
			res = true; \
		} \
		testEqual(res, "##element##", "##result##"); \
	} while (false)



