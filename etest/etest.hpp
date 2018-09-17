/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/String.hpp>
#include <etest/debug.hpp>

#define TEST_CLASS_NAME(groupName, localName) \
	groupName##_##localName##_test

/*
template <typename T>
class hasEtkStreamExporter {
	typedef char one;
	typedef long two;
	//template <typename C> static one test( decltype(T::toString()) );
	template <typename C> static one test( decltype(&etk::operator<<(etk::Stream&,const T&)) );
	template <typename C> static two test(...);
public:
	enum { value = sizeof(test<T>(0)) == sizeof(char) };
};
*/

template <typename T>
class hasMemberToString {
	typedef char one;
	typedef long two;
	template <typename C> static one test( decltype(T::toString()) );
	template <typename C> static two test(...);
public:
	enum { value = sizeof(test<T>(0)) == sizeof(char) };
};

template<typename T>
struct hasEtkStreamExporter {
	typedef char yes[1];
	typedef char no[2];
	template<typename U> static yes& test( U& );
	template<typename U> static no& test(...);
	
	static etk::Stream &s;
	static T const &t;
	
	static bool const value = sizeof( test( s << t ) ) == sizeof( yes ); // line 48
};

namespace has_insertion_operator_impl {
  typedef char no;
  typedef char yes[2];

  struct any_t {
    template<typename T> any_t( T const& );
  };

  no operator<<( etk::Stream&, any_t const& );

  yes& test( etk::Stream& );
  no test( no );

  template<typename T>
  struct has_insertion_operator {
    static etk::Stream &s;
    static T const &t;
    static bool const value = sizeof( test(s << t) ) == sizeof( yes );
  };
}

template<typename T>
struct has_insertion_operator :
  has_insertion_operator_impl::has_insertion_operator<T> {
};

namespace etest {
	template<class ETEST_TYPE,
	         typename etk::EnableIf<etk::IsSame<ETEST_TYPE,etk::NullPtr>::value, int>::type = 0 >
	etk::String exportResultToString(const ETEST_TYPE& _element) {
		return "null";
	}
	template<class ETEST_TYPE,
	         typename etk::EnableIf<    !etk::IsSame<ETEST_TYPE,etk::NullPtr>::value
	                                 && has_insertion_operator<ETEST_TYPE>::value, int>::type = 0 >
	etk::String exportResultToString(const ETEST_TYPE& _element) {
		etk::Stream tmp;
		tmp << _element;
		return tmp.str();
	}
	template<class ETEST_TYPE,
	         typename etk::EnableIf<    !etk::IsSame<ETEST_TYPE,etk::NullPtr>::value
	                                 && !has_insertion_operator<ETEST_TYPE>::value, int>::type = 0 >
	etk::String exportResultToString(const ETEST_TYPE& _element) {
		return "---";
	}
	class GenericTest {
		private:
			etk::String m_file;
			uint32_t m_line;
			etk::String m_testGroup;
			etk::String m_testName;
			bool m_haveError;
		protected:
			uint32_t m_numberCheck;
			uint32_t m_numberCheckFail;
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
			/**
			 * @brief Get if an error occured during the test
			 * @return true an error occured, false otherwise
			 */
			bool getError() const;
			/**
			 * @brief Get the number of check done in the test
			 * @return simple count of test done
			 */
			uint32_t getNumberCheck() const;
			/**
			 * @brief Get the number of check done in the test
			 * @return simple count of test done with error
			 */
			uint32_t getNumberCheckError() const;
			void addCheck() {
				m_numberCheck++;
			}
			void testResult(bool _result,
			                const etk::String& _test1Value,
			                const etk::String& _test1,
			                const etk::String& _test2Value,
			                const etk::String& _test2,
			                uint32_t _line);
			void testCatchThrow(const etk::Exception& exeption, uint32_t _line);
			void testCatchThrow(uint32_t _line);
			void clearLocal();
			virtual void run() = 0;
	};
	void unInit();
	void init(int32_t _argc, const char *_argv[]);
	int32_t runAllTest();
	uint32_t registerTest(etest::GenericTest* _element);
	extern GenericTest* g_currentTest;
}

#define TEST(groupName,localName) \
	class TEST_CLASS_NAME(groupName, localName) : public etest::GenericTest { \
		protected: \
			static uint32_t registerElement; \
		public: \
			TEST_CLASS_NAME(groupName, localName)(): \
			  etest::GenericTest(__FILE__, __LINE__, #groupName, #localName) { \
				 \
			} \
			void run() override; \
	}; \
	\
	uint32_t TEST_CLASS_NAME(groupName, localName)::registerElement = etest::registerTest(\
		etk::memory::allocatorNewFull<TEST_CLASS_NAME(groupName, localName)>("etest_test_class", null, __LINE__, __FILE__)); \
	\
	void TEST_CLASS_NAME(groupName, localName)::run()


// This all is to be compatible with the gtest API (in main lines).

#define RUN_ALL_TESTS etest::runAllTest

#define EXPECT_EQ(element, result) \
	do { \
		try { \
			etest::g_currentTest->addCheck(); \
			ETEST_DEBUG("    [ SUB-RUN  ] EXPECT_EQ(" << #element << ", " << #result << ");"); \
			auto ETEST_VARIABLE_TMP_element = (element); \
			auto ETEST_VARIABLE_TMP_result = (result); \
			bool ETEST_VARIABLE_TMP_res = (ETEST_VARIABLE_TMP_element == ETEST_VARIABLE_TMP_result); \
			if (etest::g_currentTest == null) { \
				ETEST_CRITICAL("Not in a test"); \
			} else { \
				etest::g_currentTest->testResult(ETEST_VARIABLE_TMP_res, \
				                                 etest::exportResultToString(ETEST_VARIABLE_TMP_element), \
				                                 #element, \
				                                 etest::exportResultToString(ETEST_VARIABLE_TMP_result), \
				                                 #result, \
				                                 __LINE__); \
			} \
			ETEST_DEBUG("    [ SUB-DONE ]"); \
		} catch ( etk::Exception e ) { \
			etest::g_currentTest->testCatchThrow(e, __LINE__); \
		} catch ( ... ) {\
			etest::g_currentTest->testCatchThrow(__LINE__); \
		} \
	} while (false)

#define EXPECT_NE(element, result) \
	do { \
		try { \
			etest::g_currentTest->addCheck(); \
			ETEST_DEBUG("    [ SUB-RUN  ] EXPECT_NE(" << #element << ", " << #result << ");"); \
			auto ETEST_VARIABLE_TMP_element = (element); \
			auto ETEST_VARIABLE_TMP_result = (result); \
			bool ETEST_VARIABLE_TMP_res = (ETEST_VARIABLE_TMP_element != ETEST_VARIABLE_TMP_result); \
			if (etest::g_currentTest == null) { \
				ETEST_CRITICAL("Not in a test"); \
			} else { \
				etest::g_currentTest->testResult(ETEST_VARIABLE_TMP_res, \
				                                 etest::exportResultToString(ETEST_VARIABLE_TMP_element), \
				                                 #element, \
				                                 etest::exportResultToString(ETEST_VARIABLE_TMP_result), \
				                                 #result, \
				                                 __LINE__); \
			} \
			ETEST_DEBUG("    [ SUB-DONE ]"); \
		} catch ( etk::Exception e ) { \
			etest::g_currentTest->testCatchThrow(e, __LINE__); \
		} catch ( ... ) {\
			etest::g_currentTest->testCatchThrow(__LINE__); \
		} \
	} while (false)

#define ASSERT_NE(element, result) \
	do { \
		try { \
			etest::g_currentTest->addCheck(); \
			ETEST_DEBUG("    [ SUB-RUN  ] ASSERT_NE(" << #element << ", " << #result << ");"); \
			auto ETEST_VARIABLE_TMP_element = (element); \
			auto ETEST_VARIABLE_TMP_result = (result); \
			bool ETEST_VARIABLE_TMP_res = (ETEST_VARIABLE_TMP_element != ETEST_VARIABLE_TMP_result); \
			if (etest::g_currentTest == null) { \
				ETEST_CRITICAL("Not in a test"); \
			} else { \
				etest::g_currentTest->testResult(ETEST_VARIABLE_TMP_res, \
				                                 etest::exportResultToString(ETEST_VARIABLE_TMP_element), \
				                                 #element, \
				                                 etest::exportResultToString(ETEST_VARIABLE_TMP_result), \
				                                 #result, \
				                                 __LINE__); \
			} \
			ETEST_DEBUG("    [ SUB-DONE ]"); \
			if (ETEST_VARIABLE_TMP_res == true) { \
				return; \
			} \
		} catch ( etk::Exception e ) { \
			etest::g_currentTest->testCatchThrow(e, __LINE__); \
		} catch ( ... ) {\
			etest::g_currentTest->testCatchThrow(__LINE__); \
		} \
	} while (false)

#define EXPECT_FLOAT_EQ_DELTA(element, result, delta) \
	do { \
		try { \
			etest::g_currentTest->addCheck(); \
			ETEST_DEBUG("    [ SUB-RUN  ] EXPECT_FLOAT_EQ(" << #element << ", " << #result << ");"); \
			auto ETEST_VARIABLE_TMP_element = (element); \
			auto ETEST_VARIABLE_TMP_result = (result); \
			float ETEST_VARIABLE_TMP_res2 = (ETEST_VARIABLE_TMP_element - ETEST_VARIABLE_TMP_result); \
			bool ETEST_VARIABLE_TMP_res = false; \
			if (ETEST_VARIABLE_TMP_res2 < delta && ETEST_VARIABLE_TMP_res2 > -delta) { \
				ETEST_VARIABLE_TMP_res = true; \
			} \
			if (etest::g_currentTest == null) { \
				ETEST_CRITICAL("Not in a test"); \
			} else { \
				etest::g_currentTest->testResult(ETEST_VARIABLE_TMP_res, \
				                                 etest::exportResultToString(ETEST_VARIABLE_TMP_element), \
				                                 #element, \
				                                 etest::exportResultToString(ETEST_VARIABLE_TMP_result), \
				                                 #result, \
				                                 __LINE__); \
			} \
			ETEST_DEBUG("    [ SUB-DONE ]"); \
		} catch ( etk::Exception e ) { \
			etest::g_currentTest->testCatchThrow(e, __LINE__); \
		} catch ( ... ) {\
			etest::g_currentTest->testCatchThrow(__LINE__); \
		} \
	} while (false)

#define EXPECT_FLOAT_EQ(element, result) \
	EXPECT_FLOAT_EQ_DELTA(element, result, 0.00001f)


#define EXPECT_THROW(element, typeThrow) \
	do { \
		try { \
			etest::g_currentTest->addCheck(); \
			ETEST_DEBUG("    [ SUB-RUN  ] EXPECT_THROW(" << #element << ", " << #typeThrow << ");"); \
			element; \
			if (etest::g_currentTest == null) { \
				ETEST_CRITICAL("Not in a test"); \
			} else { \
				etest::g_currentTest->testResult(false, \
				                                 "", \
				                                 #element, \
				                                 "--- Not throw ---", \
				                                 #typeThrow, \
				                                 __LINE__); \
			} \
			ETEST_DEBUG("    [ SUB-DONE ]"); \
		} catch ( typeThrow e ) { \
			/*Normale Case ...*/ \
			if (etest::g_currentTest == null) { \
				ETEST_CRITICAL("Not in a test"); \
			} else { \
				etest::g_currentTest->testResult(true, \
				                                 "", \
				                                 #element, \
				                                 "--- Have Throw ---", \
				                                 #typeThrow, \
				                                 __LINE__); \
			} \
			ETEST_DEBUG("    [ SUB-DONE ]"); \
		} catch ( etk::Exception e ) { \
			etest::g_currentTest->testCatchThrow(e, __LINE__); \
		} catch ( ... ) {\
			etest::g_currentTest->testCatchThrow(__LINE__); \
		} \
	} while (false)

