/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
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
#include <etk/stdTools.h>
#include <string>

#undef __class__
#define __class__	"etktest"

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

	etk::Color<uint8_t, 4> colorRGBA8__("#520F6544");
	etk::Color<uint16_t, 4> colorRGBA16__("rgba[U16](0x52, 0x0F, 0x65, 0x44)");
	etk::Color<uint32_t, 4> colorRGBA32__("rgba[U32](0x52,0x0F, 0x65, 0x44)");
	etk::Color<float, 4> colorRGBAF__("rgba[FLOAT](0.1,0.2,0.8,1.0)");
	etk::Color<uint8_t, 3> colorRGB8__("rgba[U8](0x52,0x0F, 0x65)");
	etk::Color<uint16_t, 3> colorRGB16__("rgba[U16](0x52,0x0F, 0x65)");
	etk::Color<uint32_t, 3> colorRGB32__("rgba[U32](0x52,0x0F, 0x65)");
	etk::Color<float, 3> colorRGBF__("rgba[FLOAT](0.1,0.2, 0.8)");
	/*
	etk::Color<uint8_t, 1> colorMono8__("mono[U8](0x52)");
	etk::Color<uint16_t, 1> colorMono16__("mono[U16](0x52)");
	etk::Color<uint32_t, 1> colorMono32__("mono[U32](0x52)");
	etk::Color<float, 1> colorMonoF__("mono[FLOAT](5200.22)");
	etk::Color<double, 1> colorMonoD__("mono[DOUBLE](520000.22)");
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
}


int main(int argc, const char *argv[]) {
	// the only one init for etk:
	etk::log::setLevel(etk::log::logLevelVerbose);
	etk::setArgZero(argv[0]);
	etk::initDefaultFolder("ewolApplNoName");
	
	testHash();
	//testFSNode();
	//testDimension();
	//testArchive();
	testColor();
	return 0;
}

