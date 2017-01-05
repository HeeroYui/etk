/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */

#include <gtest/gtest.h>
#undef NAME
#define NAME "FSNode"

TEST(TestEtkFSNode, checkType) {
	std::string fileName("USERDATA:myFileTest.txt");
	etk::FSNode myNodeTest1(fileName);
	EXPECT_EQ(myNodeTest1.getNameFile(), "myFileTest.txt");
	EXPECT_EQ(myNodeTest1.exist(), false);
	/*
	TEST_INFO("      GetNameFolder()      ='" << myNodeTest1.getNameFolder() << "'");
	TEST_INFO("      GetName()            ='" << myNodeTest1.getName() << "'");
	TEST_INFO("      GetNameFile()        ='" << myNodeTest1.getNameFile() << "'");
	TEST_INFO("      GetRelativeFolder()  ='" << myNodeTest1.getRelativeFolder() << "'");
	TEST_INFO("      getFileSystemName()  ='" << myNodeTest1.getFileSystemName() << "'");
	TEST_INFO("      exist                =" << myNodeTest1.exist());
	*/
}

void testFSNode() {
	TEST_INFO("==> Start test of FSNode");
	std::string fileName("USERDATA:myFileTest.txt");
	etk::FSNode myNodeTest1(fileName);
	TEST_INFO("********************************************");
	TEST_INFO("** Filename=\"" << fileName << "\"");
	TEST_INFO("********************************************");
	TEST_INFO("      GetNameFolder()      ='" << myNodeTest1.getNameFolder() << "'");
	TEST_INFO("      GetName()            ='" << myNodeTest1.getName() << "'");
	TEST_INFO("      GetNameFile()        ='" << myNodeTest1.getNameFile() << "'");
	TEST_INFO("      GetRelativeFolder()  ='" << myNodeTest1.getRelativeFolder() << "'");
	TEST_INFO("      getFileSystemName()  ='" << myNodeTest1.getFileSystemName() << "'");
	TEST_INFO("      exist                =" << myNodeTest1.exist());
	if (true==myNodeTest1.exist()) {
		TEST_ERROR(" ==> remove the file ==> bad for the test");
	} else {
		TEST_INFO("      Display time when file does not exist :");
		TEST_INFO("          TimeCreatedString()  ='" << myNodeTest1.timeCreatedString() << "'");
		TEST_INFO("          TimeModifiedString() ='" << myNodeTest1.timeModifiedString() << "'");
		TEST_INFO("          TimeAccessedString() ='" << myNodeTest1.timeAccessedString() << "'");
	}
	myNodeTest1.touch();
	if (false==myNodeTest1.exist()) {
		TEST_ERROR(" ==> Error, can not create the file ....");
	} else {
		TEST_INFO("      Display time when file does exist :");
		TEST_INFO("          TimeCreatedString()  ='" << myNodeTest1.timeCreatedString() << "'");
		TEST_INFO("          TimeModifiedString() ='" << myNodeTest1.timeModifiedString() << "'");
		TEST_INFO("          TimeAccessedString() ='" << myNodeTest1.timeAccessedString() << "'");
	}
	etk::FSNode myNodeTest2(fileName);
	TEST_INFO("********************************************");
	TEST_INFO("** Filename2=\"" << myNodeTest2<< "\"");
	TEST_INFO("********************************************");
	TEST_INFO("      GetNameFolder()      ='" << myNodeTest2.getNameFolder() << "'");
	TEST_INFO("      GetName()            ='" << myNodeTest2.getName() << "'");
	TEST_INFO("      GetNameFile()        ='" << myNodeTest2.getNameFile() << "'");
	TEST_INFO("      GetRelativeFolder()  ='" << myNodeTest2.getRelativeFolder() << "'");
	TEST_INFO("      getFileSystemName()  ='" << myNodeTest2.getFileSystemName() << "'");
	TEST_INFO("      exist                =" << myNodeTest2.exist());
	if (false==myNodeTest1.exist()) {
		TEST_ERROR(" ==> Error, can not create the file ....");
	} else {
		TEST_INFO("      Display time when file does exist :");
		TEST_INFO("          TimeCreatedString()  ='" << myNodeTest2.timeCreatedString() << "'");
		TEST_INFO("          TimeModifiedString() ='" << myNodeTest2.timeModifiedString() << "'");
		TEST_INFO("          TimeAccessedString() ='" << myNodeTest2.timeAccessedString() << "'");
	}
	// Try remove the file : 
	myNodeTest1.remove();
	if (true==myNodeTest1.exist()) {
		TEST_ERROR(" ==> The file might be removed ==> but it is not the case ...");
	} else {
		TEST_INFO(" ==> The file is removed");
	}
	TEST_INFO("********************************************");
	TEST_INFO("==> Stop test of FSNode");
}