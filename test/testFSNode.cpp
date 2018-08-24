/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */

#include <etest/etest.hpp>
#include <test-debug/debug.hpp>
#include <etk/os/FSNode.hpp>
#define NAME "FSNode"

TEST(TestEtkFSNode, checkHomePath) {
	etk::String homePath = etk::FSNodeGetHomePath();
	EXPECT_EQ(homePath, "/home/heero");
	etk::FSNode myNodeTest1("HOME:filePresent.txt");
	EXPECT_EQ(myNodeTest1.getNameFile(), "filePresent.txt");
	EXPECT_EQ(myNodeTest1.getFileSystemName(), homePath + "/filePresent.txt");
	EXPECT_EQ(myNodeTest1.getNameFolder(), "/home/heero");
	etk::FSNode myNodeTest2("HOME:/filePresent.txt");
	EXPECT_EQ(myNodeTest2.getNameFile(), "filePresent.txt");
	EXPECT_EQ(myNodeTest2.getFileSystemName(), homePath + "/filePresent.txt");
	EXPECT_EQ(myNodeTest2.getNameFolder(), "/home/heero");
	etk::FSNode myNodeTest3("~/filePresent.txt");
	EXPECT_EQ(myNodeTest3.getNameFile(), "filePresent.txt");
	EXPECT_EQ(myNodeTest3.getFileSystemName(), homePath + "/filePresent.txt");
	EXPECT_EQ(myNodeTest3.getNameFolder(), "/home/heero");
}



TEST(TestEtkFSNode, checkDATAFilePresent) {
	etk::String fileName("DATA:filePresent.txt");
	etk::FSNode myNodeTest1(fileName);
	EXPECT_EQ(myNodeTest1.getNameFile(), "filePresent.txt");
	EXPECT_EQ(myNodeTest1.exist(), true);
	bool ret = myNodeTest1.fileOpenRead();
	EXPECT_EQ(ret, true);
	etk::String data;
	ret = myNodeTest1.fileGets(data);
	EXPECT_EQ(ret, true);
	EXPECT_EQ(data, "plop");
	ret = myNodeTest1.fileClose();
	EXPECT_EQ(ret, true);
}

TEST(TestEtkFSNode, checkDATAFileEmpty) {
	etk::String fileName("DATA:fileEmpty.txt");
	etk::FSNode myNodeTest1(fileName);
	EXPECT_EQ(myNodeTest1.getNameFile(), "fileEmpty.txt");
	EXPECT_EQ(myNodeTest1.exist(), true);
	bool ret = myNodeTest1.fileOpenRead();
	EXPECT_EQ(ret, true);
	etk::String data;
	ret = myNodeTest1.fileGets(data);
	EXPECT_EQ(ret, false);
	EXPECT_EQ(data, "");
	ret = myNodeTest1.fileClose();
	EXPECT_EQ(ret, true);
}

TEST(TestEtkFSNode, checkDATAFileNotPresent) {
	etk::String fileName("DATA:fileNotPresent.txt");
	etk::FSNode myNodeTest1(fileName);
	EXPECT_EQ(myNodeTest1.getNameFile(), "fileNotPresent.txt");
	EXPECT_EQ(myNodeTest1.exist(), false);
}


TEST(TestEtkFSNode, checkType) {
	etk::String fileName("USERDATA:myFileTest.txt");
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
	etk::String fileName("USERDATA:myFileTest.txt");
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