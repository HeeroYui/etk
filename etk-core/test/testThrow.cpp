/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etest/etest.hpp>
#include <etk/Exception.hpp>
#include <test-debug/debug.hpp>
#include "ConstructDestruct.hpp"

TEST(TestThrow, exception_base) {
	// Test contructor value
	try {
		throw etk::Exception("plop");
	} catch (etk::Exception ex) {
		EXPECT_EQ(true, true);
		return;
	}
	EXPECT_EQ(false, true);
}


TEST(TestThrow, invalidArgument) {
	// Test contructor value
	try {
		throw etk::exception::InvalidArgument("plop");
	} catch (etk::exception::InvalidArgument ex) {
		EXPECT_EQ(true, true);
		return;
	} catch (etk::Exception ex) {
		EXPECT_EQ(true, false);
		return;
	}
	EXPECT_EQ(false, true);
}

static void tmpThrow() {
	throw etk::exception::InvalidArgument("plop");
}

TEST(TestThrow, invalidArgument_etest) {
	// Test contructor value
	EXPECT_THROW(tmpThrow(), etk::exception::InvalidArgument);
}

static void tmpThrow2() {
	ETK_THROW_EXCEPTION(etk::exception::InvalidArgument("plop"));
}

TEST(TestThrow, invalidArgument_etest2) {
	// Test contructor value
	EXPECT_THROW(tmpThrow2(), etk::exception::InvalidArgument);
}
