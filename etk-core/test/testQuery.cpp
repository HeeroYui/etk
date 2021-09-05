/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */

#include <etest/etest.hpp>
#include <test-debug/debug.hpp>
#include <etk/uri/Query.hpp>

TEST(TestQuery, defaultContructor) {
	etk::uri::Query query;
	EXPECT_EQ(query.getEncoded(), "");
}