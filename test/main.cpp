/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/types.h>
#include <etk/debug.h>
#include <vector>
#include <string>
#include <etk/Hash.h>
#include <etk/os/FSNode.h>
#include <etk/archive/Archive.h>
#include <etk/log.h>
#include <etk/Color.h>
#include <etk/RegExp.h>

#undef __class__
#define __class__	"etktest"

void testVector() {
	
}

void testUChar() {
	
}

void testHash() {
	TK_INFO("==> Start test of Hach table");
	etk::Hash<std::string> testData;
	testData.add("TEST", "testData");
	testData.add("TEST", "testData333");
	testData.add("TEST2", "22222222222222222");
	testData.add("TEST4", "4444444444444444444");
	testData.add("TEST3", "3333333333");
	testData.add("TEST1", "11111111111");
	testData.add("TEST55", "555555555555555((((5555");
	TK_INFO(" count =" << testData.size());
	for (int32_t iii=0; iii< testData.size(); iii++) {
		TK_INFO(" id=" << iii << " key='" << testData.getKey(iii) << "' val='" << testData.getValue(iii) << "'");
	}
	TK_INFO(" direct acces at the key  key='TEST4' val='" << testData["TEST4"] << "'");
	TK_INFO("==> End test of Hach table");
}

void testFSNode() {
	TK_INFO("==> Start test of FSNode");
	std::string fileName("USERDATA:myFileTest.txt");
	etk::FSNode myNodeTest1(fileName);
	TK_INFO("********************************************");
	TK_INFO("** Filename=\"" << fileName << "\"");
	TK_INFO("********************************************");
	TK_INFO("      GetNameFolder()      ='" << myNodeTest1.getNameFolder() << "'");
	TK_INFO("      GetName()            ='" << myNodeTest1.getName() << "'");
	TK_INFO("      GetNameFile()        ='" << myNodeTest1.getNameFile() << "'");
	TK_INFO("      GetRelativeFolder()  ='" << myNodeTest1.getRelativeFolder() << "'");
	TK_INFO("      getFileSystemName()  ='" << myNodeTest1.getFileSystemName() << "'");
	TK_INFO("      exist                =" << myNodeTest1.exist());
	if (true==myNodeTest1.exist()) {
		TK_ERROR(" ==> remove the file ==> bad for the test");
	} else {
		TK_INFO("      Display time when file does not exist :");
		TK_INFO("          TimeCreatedString()  ='" << myNodeTest1.timeCreatedString() << "'");
		TK_INFO("          TimeModifiedString() ='" << myNodeTest1.timeModifiedString() << "'");
		TK_INFO("          TimeAccessedString() ='" << myNodeTest1.timeAccessedString() << "'");
	}
	myNodeTest1.touch();
	if (false==myNodeTest1.exist()) {
		TK_ERROR(" ==> Error, can not create the file ....");
	} else {
		TK_INFO("      Display time when file does exist :");
		TK_INFO("          TimeCreatedString()  ='" << myNodeTest1.timeCreatedString() << "'");
		TK_INFO("          TimeModifiedString() ='" << myNodeTest1.timeModifiedString() << "'");
		TK_INFO("          TimeAccessedString() ='" << myNodeTest1.timeAccessedString() << "'");
	}
	etk::FSNode myNodeTest2(fileName);
	TK_INFO("********************************************");
	TK_INFO("** Filename2=\"" << myNodeTest2<< "\"");
	TK_INFO("********************************************");
	TK_INFO("      GetNameFolder()      ='" << myNodeTest2.getNameFolder() << "'");
	TK_INFO("      GetName()            ='" << myNodeTest2.getName() << "'");
	TK_INFO("      GetNameFile()        ='" << myNodeTest2.getNameFile() << "'");
	TK_INFO("      GetRelativeFolder()  ='" << myNodeTest2.getRelativeFolder() << "'");
	TK_INFO("      getFileSystemName()  ='" << myNodeTest2.getFileSystemName() << "'");
	TK_INFO("      exist                =" << myNodeTest2.exist());
	if (false==myNodeTest1.exist()) {
		TK_ERROR(" ==> Error, can not create the file ....");
	} else {
		TK_INFO("      Display time when file does exist :");
		TK_INFO("          TimeCreatedString()  ='" << myNodeTest2.timeCreatedString() << "'");
		TK_INFO("          TimeModifiedString() ='" << myNodeTest2.timeModifiedString() << "'");
		TK_INFO("          TimeAccessedString() ='" << myNodeTest2.timeAccessedString() << "'");
	}
	// Try remove the file : 
	myNodeTest1.remove();
	if (true==myNodeTest1.exist()) {
		TK_ERROR(" ==> The file might be removed ==> but it is not the case ...");
	} else {
		TK_INFO(" ==> The file is removed");
	}
	TK_INFO("********************************************");
	TK_INFO("==> Stop test of FSNode");
}


void testArchive() {
	TK_INFO("==> Start test of archive");
	etk::Archive* tmpArchive = etk::Archive::load("testzip.zip");
	tmpArchive->display();
	
	TK_INFO("==> End test of archive");
}

/*
void testDimension() {
	TK_INFO("==> test of Dimension (START)");
	
	ewol::Dimension myDimention(vec2(5,5), ewol::Dimension::Centimeter);
	TK_INFO("    set dimension at : " << myDimention);
	TK_INFO("    set dimension at : " << myDimention.GetCentimeter() << " cm");
	TK_INFO("    set dimension at : " << myDimention.GetMillimeter() << " mm");
	TK_INFO("    set dimension at : " << myDimention.GetKilometer() << " km");
	TK_INFO("    set dimension at : " << myDimention.GetMeter() << " m");
	TK_INFO("    set dimension at : " << myDimention.GetInch() << " Inch");
	TK_INFO("    set dimension at : " << myDimention.GetFoot() << " ft");
	TK_INFO("    set dimension at : " << myDimention.GetPourcent() << " %");
	TK_INFO("    set dimension at : " << myDimention.GetPixel() << " px");
	
	TK_INFO("==> test of Dimension (STOP)");
	exit(0);
}
*/

void testColor() {
	TK_INFO("==> test of COLOR (START)");
	
	etk::Color<uint8_t, 4> colorRGBA8(0x52,0x0F, 0x65, 0x44);
	etk::Color<uint16_t, 4> colorRGBA16(0x52,0x0F, 0x65, 0x44);
	etk::Color<uint32_t, 4> colorRGBA32(0x52,0x0F, 0x65, 0x44);
	etk::Color<float, 4> colorRGBAF(0.1,0.2, 0.8, 1.0);
	etk::Color<uint8_t, 3> colorRGB8(0x52,0x0F, 0x65);
	etk::Color<uint16_t, 3> colorRGB16(0x52,0x0F, 0x65);
	etk::Color<uint32_t, 3> colorRGB32(0x52,0x0F, 0x65);
	etk::Color<float, 3> colorRGBF(0.1,0.2, 0.8);
	etk::Color<uint8_t, 1> colorMono8(0x52);
	etk::Color<uint16_t, 1> colorMono16(0x52);
	etk::Color<uint32_t, 1> colorMono32(0x52);
	etk::Color<float, 1> colorMonoF(5200.22);
	etk::Color<double, 1> colorMonoD(520000.22);
	/*
	etk::Color<uint8_t, 4> colorRGBA8__("#520F6544");
	etk::Color<uint16_t, 4> colorRGBA16__("rgba(0x52, 0x0F, 0x65, 0x44)");
	etk::Color<uint32_t, 4> colorRGBA32__("rgba(0x52,0x0F, 0x65, 0x44)");
	etk::Color<float, 4> colorRGBAF__("rgba(0.1,0.2, 0.8, 1.0)");
	etk::Color<uint8_t, 3> colorRGB8__("rgba(0x52,0x0F, 0x65)");
	etk::Color<uint16_t, 3> colorRGB16__("rgba(0x52,0x0F, 0x65)");
	etk::Color<uint32_t, 3> colorRGB32__("rgba(0x52,0x0F, 0x65)");
	etk::Color<float, 3> colorRGBF__("rgba(0.1,0.2, 0.8)");
	etk::Color<uint8_t, 1> colorMono8__("mono(0x52)");
	etk::Color<uint16_t, 1> colorMono16__("mono(0x52)");
	etk::Color<uint32_t, 1> colorMono32__("mono(0x52)");
	etk::Color<float, 1> colorMonoF__("mono(5200.22)");
	etk::Color<double, 1> colorMonoD__("mono(520000.22)");
	*/
	etk::Color<float, 4> colorRGBAf__(colorRGBA8);
	etk::Color<uint32_t, 2> colorXX332__(colorRGBA8);
	
	TK_INFO("Create a color : RGBA 8 : " << colorRGBA8);
	TK_INFO("Create a color : RGBA 8 : " << colorRGBAf__ << " (converted)");
	TK_INFO("Create a color : XX 32 : " << colorXX332__ << " (converted)");
	TK_INFO("Create a color : RGBA 16 : " << colorRGBA16);
	TK_INFO("Create a color : RGBA 32 : " << colorRGBA32);
	TK_INFO("Create a color : RGBA float : " << colorRGBAF);
	TK_INFO("Create a color : RGB 8 : " << colorRGB8);
	TK_INFO("Create a color : RGB 16 : " << colorRGB16);
	TK_INFO("Create a color : RGB 32 : " << colorRGB32);
	TK_INFO("Create a color : RGB float : " << colorRGBF);
	TK_INFO("Create a color : MONO 8 : " << colorMono8);
	TK_INFO("Create a color : MONO 16 : " << colorMono16);
	TK_INFO("Create a color : MONO 32 : " << colorMono32);
	TK_INFO("Create a color : MONO float : " << colorMonoF);
	TK_INFO("Create a color : MONO double : " << colorMonoD);
	
	TK_INFO("==> test of Color (STOP)");
	exit(0);
}

void testRegExpSingle(const std::string& _expression, const std::string& _search) {
	etk::RegExp<std::string> expression(_expression);
	TK_INFO("Parse RegEx: " << expression.getRegExDecorated());
	TK_INFO("         IN: " << etk::regexp::autoStr(_search));
	if (expression.parse(_search, 0, _search.size()) == true) {
		TK_INFO("    match [" << expression.start() << ".." << expression.stop() << "] ");
		TK_INFO("        ==> '" << etk::regexp::autoStr(std::string(_search, expression.start(), expression.stop() - expression.start())) << "'");
	}
}


void testRegExp() {
	std::string data;
	//std::string data = " a /* plop */ \n int eee = 22; // error value \nint main(void) {\n return 0;\n}\n";
	//std::string data = "alpha /* plop */ test";
	//std::string data = "pp \n // qdfqdfsdf \nde";
	//testRegExpSingle("/\\*.*\\*/", data);
	//testRegExpSingle("//.*$", data);
	//testRegExpSingle("/\\*.*", data);
	//testRegExpSingle("[a-z]", data);
	//std::string data = "  eesd a lzzml plophzzzzzhhhhhrlkmlkml";
	//testRegExpSingle("a.*plop(z{2,3}|h+)+r", data);
	
	//std::string data = "pp \n# plop // qdfqdfsdf \nde";
	//std::string data = "pp \n# plop //\\\n qdfqdfsdf \nde";
	//std::string data = "p#\ne";
	//testRegExpSingle("#(\\\\\\\\|\\\\\\n|.)*$", data);
	//testRegExpSingle("#.*$", data);
	
	//std::string data = "p//TODO:\ndse";
	//std::string data = "p// TODO:\ndse";
	//std::string data = "p// TODO :\ndse";
	//std::string data = "p// TODO 	: sdfgsdfsd \ndse";
	//testRegExpSingle("//[ \\t]*TODO[ \\t]*:.*$", data);
	
	data = "abc  m_def ghi";
	data =  "	protected:\n"
			"		vec2 m_offset; \n";
	//testRegExpSingle("\\@m_[A-Za-z_0-9]*\\@", data);
	
	
	data = " * @param[in] _mode Configuring mode.\n"
	"		 * @param[in] _time Time in second of the annimation display\n"
	"		 */\n"
	"		void setAnnimationTime(enum ";
	data = "virtual vec2 relativePosition(const vec2& _pos);";
	
	//testRegExpSingle("\\@(\\w|_)+[ \\t]*\\(", data);
	
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
	//testRegExpSingle("#(\\\\[\\\\\\n]|.)*$", data);
	
	
	data =  "	'dfgd\\'fg'  \n"
			"	vec2 m_offset; \n";
	testRegExpSingle("'((\\\\[\\\\'])|.)*'", data);

}

int main(int argc, const char *argv[]) {
	// the only one init for etk:
	etk::log::setLevel(etk::log::logLevelVerbose);
	etk::setArgZero(argv[0]);
	etk::initDefaultFolder("ewolApplNoName");
	
	//testVector();
	//testUChar();
	//testUString();
	//testHash();
	//testFSNode();
	//testDimension();
	//testArchive();
	//testColor();
	testRegExp();
	return 0;
}

