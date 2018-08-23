/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */


#include <etk/utf8.hpp>
#include <test-debug/debug.hpp>
#include <etest/etest.hpp>
#include "ConstructDestruct.hpp"

TEST(TestUTF8, full) {
	// Test contructor value
	for (uint32_t jjj=0; jjj<0XFF; ++jjj) {
		TEST_PRINT("range : " << jjj << " / " << 0XFF );
		for (uint32_t iii=0; iii<0XFFFFFF; ++iii) {
			char32_t inputValue = iii;
			char output[7];
			u32char::convertUtf8(inputValue, output);
			char32_t outputValue = utf8::convertChar32(output);
			EXPECT_EQ(inputValue, outputValue);
		}
	}
}