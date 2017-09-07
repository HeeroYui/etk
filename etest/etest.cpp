/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etest/etest.hpp>
#include <etest/debug.hpp>
#include <etk/Vector.hpp>
#include <elog/elog.hpp>
#include <echrono/Steady.hpp>
#include <echrono/Duration.hpp>

static int32_t nbTimeInit = 0;

static etk::Vector<etest::GenericTest*>& getListOfTest() {
	static etk::Vector<etest::GenericTest*> s_listOfData;
	return s_listOfData;
}
static etk::String filterGroup;
static etk::String filterTest;


void etest::unInit() {
	if (nbTimeInit > 1) {
		nbTimeInit--;
		// not the time to un-init
		return;
	}
	nbTimeInit--;
	if (nbTimeInit < 0) {
		ETEST_ERROR("ETEST system un-init More un-init than init ...");
		nbTimeInit = 0;
		return;
	}
	ETEST_INFO("ETEST system un-init (BEGIN)");
	ETEST_INFO("ETEST system un-init (END)");
	elog::unInit();
}

static etk::Vector<etk::String> getListGroupSpecific(const etk::Vector<etest::GenericTest*>& _value) {
	etk::Vector<etk::String> listGroup;
	for (auto &it: _value) {
		if (etk::isIn(it->getTestGroup(), listGroup) == true) {
			continue;
		}
		listGroup.pushBack(it->getTestGroup());
	}
	return listGroup;
}

static etk::Vector<etk::String> getListGroup() {
	return getListGroupSpecific(getListOfTest());
}

static etk::Vector<etest::GenericTest*> getListFiltered() {
	if (filterGroup == "") {
		return getListOfTest();
	}
	etk::Vector<etest::GenericTest*> out;
	for (auto &it: getListOfTest()) {
		if (it->getTestGroup() != filterGroup) {
			continue;
		}
		if (filterTest == "") {
			out.pushBack(it);
			continue;
		}
		if (filterTest == it->getTestName()) {
			out.pushBack(it);
			continue;
		}
	}
	return out;
}

static void listAllTest() {
	ETEST_ERROR("We have " << getListOfTest().size() << " tests:");
	etk::Vector<etk::String> listGroup = getListGroup();
	for (auto &itGroup: listGroup) {
		ETEST_PRINT("Group: " << itGroup);
		for (auto &it: getListOfTest()) {
			if (it->getTestGroup() == itGroup) {
				ETEST_PRINT("     - " << itGroup << "." << it->getTestName());
			}
		}
	}
}

void etest::init(int32_t _argc, const char** _argv) {
	if (nbTimeInit > 0) {
		nbTimeInit++;
		// already init
		return;
	}
	nbTimeInit++;
	elog::init(_argc, _argv);
	ETEST_INFO("ETEST system init (BEGIN) ");
	for (int32_t iii=0; iii<_argc ; ++iii) {
		etk::String data = _argv[iii];
		ETEST_PRINT("Parameter : " << data << "  " << data.startWith("--etest-filter="));
		if (    data == "-h"
		     || data == "--help") {
			ETEST_PRINT("etest - help : ");
			if (_argc >= 1) {
				ETEST_PRINT("    " << _argv[0] << " [options]");
				ETEST_PRINT("        --etest-list          List all test names");
				ETEST_PRINT("        --etest-filter=XXX    filter group or test: XXX or WWW.yyy");
			}
			ETEST_PRINT("        -h/--help: this help");
		} else if (data == "--etest-list") {
			listAllTest();
			exit(0);
		} else if (data.startWith("--etest-filter=") == true) {
			etk::String filter = &data[15];
			ETEST_PRINT("        Filter: " << filter);
			ETEST_ERROR("plop:" << filter);
			etk::Vector<etk::String> tmp = filter.split(".");
			if (tmp.size() == 1) {
				// Filter only the groups
				filterGroup = filter;
			} else if (tmp.size() == 2) {
				filterGroup = tmp[0];
				filterTest = tmp[1];
			} else {
				ETEST_CRITICAL("Can not parse the argument : '" << data << "' ==> more than 1 '.'");
			}
		} else if (data.startWith("--etest") == true) {
			ETEST_ERROR("Can not parse the argument : '" << data << "'");
		}
	}
	ETEST_INFO("ETEST system init (END)");
}

etest::GenericTest::GenericTest(const char* _file,
                                uint32_t _line,
                                const char* _testGroup,
                                const char* _testName):
  m_file(_file),
  m_line(_line),
  m_testGroup(_testGroup),
  m_testName(_testName) {
	
}

const etk::String& etest::GenericTest::getFileName() const {
	return m_file;
}

uint32_t etest::GenericTest::getFileLine() const {
	return m_line;
}

const etk::String& etest::GenericTest::getTestGroup() const {
	return m_testGroup;
}

const etk::String& etest::GenericTest::getTestName() const {
	return m_testName;
}

bool etest::GenericTest::getError() const {
	return m_haveError;
}

void etest::GenericTest::testResult(bool _result,
                                    const etk::String& _test1Value,
                                    const etk::String& _test1,
                                    const etk::String& _test2Value,
                                    const etk::String& _test2,
                                    uint32_t _line) {
	if (_result == true) {
		return;
	}
	ETEST_ERROR("Detect an error: " << m_file << ":" << _line << ":");
	ETEST_ERROR("    have: " << _test1 << " = " << _test1Value);
	ETEST_ERROR("    expect: " << _test2 << " = " << _test2Value);
	m_haveError = true;
}

void etest::GenericTest::clearLocal() {
	m_haveError = false;
}
etest::GenericTest* etest::g_currentTest = nullptr;

int32_t etest::runAllTest() {
	int32_t errorCount = 0;
	etk::Vector<etest::GenericTest*> runList = getListFiltered();
	etk::Vector<etk::String> listGroup = getListGroupSpecific(runList);
	ETEST_PRINT("[==========] Running " << runList.size() << " tests from " << listGroup.size() << " test group.");
	echrono::Steady tic = echrono::Steady::now();
	for (auto &itGroup: listGroup) {
		int32_t count = 0;
		for (auto &it: getListOfTest()) {
			if (it->getTestGroup() == itGroup) {
				count++;
			}
		}
		ETEST_PRINT("[++++++++++] " << count << " test from " << itGroup << ":");
		echrono::Steady ticGroup = echrono::Steady::now();
		for (auto &it: getListOfTest()) {
			if (it->getTestGroup() != itGroup) {
				continue;
			}
			ETEST_PRINT("[ RUN      ] " << itGroup << "." << it->getTestName());
			it->clearLocal();
			g_currentTest = it;
			echrono::Steady ticTest = echrono::Steady::now();
			it->run();
			echrono::Steady tocTest = echrono::Steady::now();
			g_currentTest = nullptr;
			if (it->getError() == true) {
				ETEST_PRINT("[     FAIL ] " << itGroup << "." << it->getTestName() << " (" << (tocTest - ticTest) << ")");
				errorCount++;
			} else {
				ETEST_PRINT("[       OK ] " << itGroup << "." << it->getTestName() << " (" << (tocTest - ticTest) << ")");
			}
		}
		echrono::Steady tocGroup = echrono::Steady::now();
		ETEST_PRINT("[++++++++++] " << count << " test from " << itGroup << " (" << (tocGroup - ticGroup) << ")");
	}
	echrono::Steady toc = echrono::Steady::now();
	ETEST_PRINT("[==========] All done in " << (toc - tic));
	if (errorCount != 0) {
		ETEST_PRINT("[== FAIL ==] Have " << errorCount << " test fail");
	}
	return -errorCount;
}

uint32_t etest::registerTest(etest::GenericTest* _element) {
	if (_element == nullptr) {
		return -1;
	}
	getListOfTest().pushBack(_element);
	return getListOfTest().size()-1;
}
/*
  7h55'30 [P] elog | Log in file: '/tmp/elog_etk-test.log'
[==========] Running 13 tests from 4 test cases.
[----------] Global test environment set-up.
[----------] 1 test from TestEtkColor
[ RUN      ] TestEtkColor.RGBA8
[       OK ] TestEtkColor.RGBA8 (0 ms)
[----------] 1 test from TestEtkColor (0 ms total)
[----------] 1 test from TestEtkFSNode
[ RUN      ] TestEtkFSNode.checkType
[       OK ] TestEtkFSNode.checkType (1 ms)
[----------] 1 test from TestEtkFSNode (1 ms total)
[----------] 8 tests from TestEtkHash
[ RUN      ] TestEtkHash.Creation
[       OK ] TestEtkHash.Creation (0 ms)
[ RUN      ] TestEtkHash.AddElement
[       OK ] TestEtkHash.AddElement (0 ms)
[ RUN      ] TestEtkHash.OverWriteElement
[       OK ] TestEtkHash.OverWriteElement (0 ms)
[ RUN      ] TestEtkHash.RemoveElement
[       OK ] TestEtkHash.RemoveElement (0 ms)
[ RUN      ] TestEtkHash.ExistElement
[       OK ] TestEtkHash.ExistElement (0 ms)
[ RUN      ] TestEtkHash.clear
[       OK ] TestEtkHash.clear (0 ms)
[ RUN      ] TestEtkHash.getKey
[       OK ] TestEtkHash.getKey (0 ms)
[ RUN      ] TestEtkHash.getKeys
[       OK ] TestEtkHash.getKeys (0 ms)
[----------] 8 tests from TestEtkHash (0 ms total)
[----------] 3 tests from TestSTDSharedPtr
[ RUN      ] TestSTDSharedPtr.testBaseLocal
create Example [0]
Remove Example [0]
[       OK ] TestSTDSharedPtr.testBaseLocal (0 ms)
[ RUN      ] TestSTDSharedPtr.testBaseShared
create Example [1]
Remove Example [1]
[       OK ] TestSTDSharedPtr.testBaseShared (0 ms)
[ RUN      ] TestSTDSharedPtr.testBaseSharedDouble
create Example [2]
Remove Example [2]
[       OK ] TestSTDSharedPtr.testBaseSharedDouble (0 ms)
[----------] 3 tests from TestSTDSharedPtr (0 ms total)
[----------] Global test environment tear-down
[==========] 13 tests from 4 test cases ran. (2 ms total)
[  PASSED  ] 13 tests.
*/

