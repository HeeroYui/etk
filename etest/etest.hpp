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
		return "nullptr";
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
			bool getError() const;
			void testResult(bool _result,
			                const etk::String& _test1Value,
			                const etk::String& _test1,
			                const etk::String& _test2Value,
			                const etk::String& _test2,
			                uint32_t _line);
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
	uint32_t TEST_CLASS_NAME(groupName, localName)::registerElement = etest::registerTest(new TEST_CLASS_NAME(groupName, localName)); \
	\
	void TEST_CLASS_NAME(groupName, localName)::run()


// This all is to be compatible with the gtest API (in main lines).

#define RUN_ALL_TESTS etest::runAllTest

#define EXPECT_EQ(element, result) \
	do { \
		bool ETEST_VARIABLE_TMP_res = (element == result); \
		if (etest::g_currentTest == nullptr) { \
			ETEST_CRITICAL("Not in a test"); \
		} else { \
			etest::g_currentTest->testResult(ETEST_VARIABLE_TMP_res, \
			                                 etest::exportResultToString(element), \
			                                 #element, \
			                                 etest::exportResultToString(result), \
			                                 #result, \
			                                 __LINE__); \
		} \
	} while (false)

#define EXPECT_NE(element, result) \
	do { \
		bool ETEST_VARIABLE_TMP_res = (element != result); \
		if (etest::g_currentTest == nullptr) { \
			ETEST_CRITICAL("Not in a test"); \
		} else { \
			etest::g_currentTest->testResult(ETEST_VARIABLE_TMP_res, \
			                                 etest::exportResultToString(element), \
			                                 #element, \
			                                 etest::exportResultToString(result), \
			                                 #result, \
			                                 __LINE__); \
		} \
	} while (false)

#define EXPECT_FLOAT_EQ(element, result) \
	do { \
		float ETEST_VARIABLE_TMP_res2 = (element) - (result); \
		bool ETEST_VARIABLE_TMP_res = false; \
		if (ETEST_VARIABLE_TMP_res2 < 0.00001f && ETEST_VARIABLE_TMP_res2 > -0.00001f) { \
			ETEST_VARIABLE_TMP_res = true; \
		} \
		if (etest::g_currentTest == nullptr) { \
			ETEST_CRITICAL("Not in a test"); \
		} else { \
			etest::g_currentTest->testResult(ETEST_VARIABLE_TMP_res, \
			                                 etest::exportResultToString(element), \
			                                 #element, \
			                                 etest::exportResultToString(result), \
			                                 #result, \
			                                 __LINE__); \
		} \
	} while (false)



