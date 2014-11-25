/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <gtest/gtest.h>
#undef NAME
#define NAME "FSNode"

#undef __class__
#define __class__	"etktest"

TEST(TestEtkFSNode, checkType) {
	std::string fileName("USERDATA:myFileTest.txt");
	etk::FSNode myNodeTest1(fileName);
	EXPECT_EQ(myNodeTest1.getNameFile(), "myFileTest.txt");
	EXPECT_EQ(myNodeTest1.exist(), false);
	/*
	TK_INFO("      GetNameFolder()      ='" << myNodeTest1.getNameFolder() << "'");
	TK_INFO("      GetName()            ='" << myNodeTest1.getName() << "'");
	TK_INFO("      GetNameFile()        ='" << myNodeTest1.getNameFile() << "'");
	TK_INFO("      GetRelativeFolder()  ='" << myNodeTest1.getRelativeFolder() << "'");
	TK_INFO("      getFileSystemName()  ='" << myNodeTest1.getFileSystemName() << "'");
	TK_INFO("      exist                =" << myNodeTest1.exist());
	*/
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