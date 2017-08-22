/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */

#include <gtest/gtest.h>
#include <etk/RegEx.hpp>
#include <test-debug/debug.hpp>

#define NAME "Hash"

std::pair<int32_t, int32_t> testRegExSingle(const std::string& _expression, const std::string& _search) {
	etk::RegEx<std::string> expression(_expression);
	TK_INFO("Parse RegEx: \"" << expression.getRegExDecorated() << "\"");
	TK_INFO("         IN: \"" << etk::regex::autoStr(_search) << "\"");
	if (expression.parse(_search, 0, _search.size()) == true) {
		TK_INFO("    match [" << expression.start() << ".." << expression.stop() << "] ");
		TK_INFO("        ==> '" << etk::regex::autoStr(std::string(_search, expression.start(), expression.stop() - expression.start())) << "'");
		return std::make_pair(expression.start(), expression.stop());
	}
	TK_INFO("        ==> ---------------");
	return std::make_pair(0,0);
}

static std::string data1 = " a /* plop */ \n int eee = 22; // error value \nint main(void) {\n return 0;\n}\n";
static std::string data2 = "alpha /* plop */ test";
static std::string data3 = "pp \n // qdfqdfsdf \nde";

TEST(TestEtkRegEx, MultipleLineComment ) {
	std::string expression = "/\\*.*\\*/";
	std::pair<int32_t, int32_t> res;
	res = testRegExSingle(expression, data1);
	EXPECT_EQ(res, std::make_pair(3,13));
	res = testRegExSingle(expression, data2);
	EXPECT_EQ(res, std::make_pair(6,16));
	res = testRegExSingle(expression, data3);
	EXPECT_EQ(res, std::make_pair(0,0));
}
TEST(TestEtkRegEx, MultipleEndDollar ) {
	std::string expression = "//.*$";
	std::pair<int32_t, int32_t> res;
	res = testRegExSingle(expression, data1);
	EXPECT_EQ(res, std::make_pair(30,46));
	res = testRegExSingle(expression, data2);
	EXPECT_EQ(res, std::make_pair(0,0));
	res = testRegExSingle(expression, data3);
	EXPECT_EQ(res, std::make_pair(5,19));
}

TEST(TestEtkRegEx, MultipleNoEnd ) {
	std::string expression = "/\\*.*";
	std::pair<int32_t, int32_t> res;
	res = testRegExSingle(expression, data1);
	EXPECT_EQ(res, std::make_pair(3,5));
	res = testRegExSingle(expression, data2);
	EXPECT_EQ(res, std::make_pair(6,8));
	res = testRegExSingle(expression, data3);
	EXPECT_EQ(res, std::make_pair(0,0));
}

TEST(TestEtkRegEx, aToZ ) {
	std::string expression = "[a-z]";
	std::pair<int32_t, int32_t> res;
	res = testRegExSingle(expression, data1);
	EXPECT_EQ(res, std::make_pair(1,2));
	res = testRegExSingle(expression, data2);
	EXPECT_EQ(res, std::make_pair(0,1));
	res = testRegExSingle(expression, data3);
	EXPECT_EQ(res, std::make_pair(0,1));
}

TEST(TestEtkRegEx, complexString ) {
	std::string expression = "a.*plop(z{2,3}|h+)+r";
	std::string dataToParse = "  eesd a lzzml plophzzzzzhhhhhrlkmlkml";
	std::pair<int32_t, int32_t> res;
	res = testRegExSingle(expression, dataToParse);
	EXPECT_EQ(res, std::make_pair(7,31));
}

TEST(TestEtkRegEx, multipleUnderscore ) {
	std::string expression = "\\@\\w+_\\@";
	std::string dataToParse = "  aaa_bbb_ plop_ ";
	std::pair<int32_t, int32_t> res;
	res = testRegExSingle(expression, dataToParse);
	EXPECT_EQ(res, std::make_pair(2,10));
}


TEST(TestEtkRegEx, endError ) {
	std::string expression = "\\@((0(x|X)[0-9a-fA-F]*)|(\\d+\\.?\\d*|\\.\\d+)((e|E)(\\+|\\-)?\\d+)?)(LL|L|l|UL|ul|u|U|F|f)?\\@";
	std::string dataToParse = "(95";
	std::pair<int32_t, int32_t> res;
	res = testRegExSingle(expression, dataToParse);
	EXPECT_EQ(res, std::make_pair(7,31));
}



void testRegEx() {
	std::string data;
	
	//std::string data = "pp \n# plop // qdfqdfsdf \nde";
	//std::string data = "pp \n# plop //\\\n qdfqdfsdf \nde";
	//std::string data = "p#\ne";
	//testRegExSingle("#(\\\\\\\\|\\\\\\n|.)*$", data);
	//testRegExSingle("#.*$", data);
	
	//std::string data = "p//TODO:\ndse";
	//std::string data = "p// TODO:\ndse";
	//std::string data = "p// TODO :\ndse";
	//std::string data = "p// TODO 	: sdfgsdfsd \ndse";
	//testRegExSingle("//[ \\t]*TODO[ \\t]*:.*$", data);
	
	data = "abc  m_def ghi";
	data =  "	protected:\n"
			"		vec2 m_offset; \n";
	//testRegExSingle("\\@m_[A-Za-z_0-9]*\\@", data);
	
	
	data = " * @param[in] _mode Configuring mode.\n"
	"		 * @param[in] _time Time in second of the annimation display\n"
	"		 */\n"
	"		void setAnnimationTime(enum ";
	data = "virtual vec2 relativePosition(const vec2& _pos);";
	
	//testRegExSingle("\\@(\\w|_)+[ \\t]*\\(", data);
	
	data = "include <ewol/Dimensio2n.h>\n"
		"#include <ewol/Dimension.h>\n"
		"'dfgd\'fg'\n"
		"\"dqf\\\"gsdfg\" // \"\n"
		"// TODO : sqdkfjsdldkqfj\n"
		"\n"
		"namespace ewol {\n"
		"	class Widget;\n"
		"	namespace widget {\n"
		"		class Manager;\n"
		"		class Windows;\n"
		"	};\n"
		"};\n"
		"#include <etk/types.h>\n";
	//testRegExSingle("#(\\\\[\\\\\\n]|.)*$", data);
	
	
	data =  "	'dfgd\\'fg'  \n"
			"	vec2 m_offset; \n";
	//testRegExSingle("'((\\\\[\\\\'])|.)*'", data);
	
	
	/*
	data = "ddfgdfgh";
	etk::RegEx<std::string> reg(".*");
	reg.setMaximize(true);
	
	TK_INFO("Parse RegEx : '" << reg.getRegExDecorated() << "'");
	if (reg.parse(data, 0, data.size()) == true) {
	//if (reg.processOneElement(data, 0, data.size()) == true) {
		TK_INFO("    match [" << reg.start() << ".." << reg.stop() << "] ");
		TK_INFO("        ==> '" << std::string(data, reg.start(), reg.stop()-reg.start()) << "'");
	}
	
	data = "plop \"\" sdfsdf s\"swdfsqd sdfgsdfg \" \" sdfsf";
	reg = etk::RegEx<std::string>("\"(\\\\[\\\\\"]|.)*\"");
	reg.setMaximize(false);
	TK_INFO("Parse RegEx : '" << reg.getRegExDecorated() << "'");
	if (reg.parse(data, 0, data.size()) == true) {
	//if (reg.processOneElement(data, 0, data.size()) == true) {
		TK_INFO("    match [" << reg.start() << ".." << reg.stop() << "] ");
		TK_INFO("        ==> '" << std::string(data, reg.start(), reg.stop()-reg.start()) << "'");
	}
	//TODO : good : "(\\+|[0-9])*" ==> really bad : "(+|[0-9])*"
	
	data = "void limit(const vec2& _origin, const vec2& _size);\n";
	reg = etk::RegEx<std::string>("\\@(\\w|_)+[ \\t]*\\(");
	reg.setMaximize(false);
	TK_INFO("Parse RegEx : '" << reg.getRegExDecorated() << "'");
	if (reg.parse(data, 0, data.size()) == true) {
	//if (reg.processOneElement(data, 0, data.size()) == true) {
		TK_INFO("    match [" << reg.start() << ".." << reg.stop() << "] ");
		TK_INFO("        ==> '" << std::string(data, reg.start(), reg.stop()-reg.start()) << "'");
	}
	data = "void limit const vec2& _origin, const vec2& _size);\n";
	if (reg.parse(data, 0, data.size()) == true) {
	//if (reg.processOneElement(data, 0, data.size()) == true) {
		TK_INFO("    match [" << reg.start() << ".." << reg.stop() << "] ");
		TK_INFO("        ==> '" << std::string(data, reg.start(), reg.stop()-reg.start()) << "'");
	}
	*/
}

