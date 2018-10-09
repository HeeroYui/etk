/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */

#include <etest/etest.hpp>
#include <test-debug/debug.hpp>
#include <etk/uri/uri.hpp>
#include <etk/uri/provider/provider.hpp>
#include <etk/uri/provider/ProviderFile.hpp>
#include <etk/uri/provider/ProviderFileZip.hpp>
#include <etk/path/fileSystem.hpp>
#include <etk/algorithm.hpp>



TEST(TestUriProvider, defaultContructor) {
	etk::uri::provider::clear();
	EXPECT_EQ(etk::uri::provider::exist(""), true);
}

static int32_t s_plouf = 0;

namespace {
	class ProviderTest1 : public etk::uri::provider::Interface {
		public:
			ememory::SharedPtr<etk::io::Interface> create(const etk::Uri& _uri) override {
				s_plouf = 5555;
				return null;
			}
			bool exist(const etk::Uri& _uri) override {
				return false;
			}
			etk::Vector<etk::Uri> list(const etk::Uri& _uri) override {
				etk::Vector<etk::Uri> out;
				return out;
			}
			etk::Vector<etk::Uri> listRecursive(const etk::Uri& _uri) override {
				etk::Vector<etk::Uri> out;
				return out;
			}
	};
	class ProviderTest2 : public etk::uri::provider::Interface {
		public:
			ememory::SharedPtr<etk::io::Interface> create(const etk::Uri& _uri) override {
				s_plouf = 9999;
				return null;
			}
			bool exist(const etk::Uri& _uri) override {
				return false;
			}
			etk::Vector<etk::Uri> list(const etk::Uri& _uri) override {
				etk::Vector<etk::Uri> out;
				return out;
			}
			etk::Vector<etk::Uri> listRecursive(const etk::Uri& _uri) override {
				etk::Vector<etk::Uri> out;
				return out;
			}
	};
}


TEST(TestUriProvider, checkPlouf) {
	etk::uri::provider::clear();
	s_plouf = 0;
	EXPECT_EQ(etk::uri::provider::exist(""), true);
	EXPECT_EQ(etk::uri::provider::exist("FILE"), true);
	EXPECT_EQ(etk::uri::provider::exist("PLOUF_1"), false);
	EXPECT_EQ(etk::uri::provider::exist("PLOUF_2"), false);
	etk::uri::provider::add("PLOUF_1", ememory::makeShared<::ProviderTest1>());
	EXPECT_EQ(etk::uri::provider::exist(""), true);
	EXPECT_EQ(etk::uri::provider::exist("PLOUF_1"), true);
	EXPECT_EQ(etk::uri::provider::exist("PLOUF_2"), false);
	etk::uri::provider::add("PLOUF_2", ememory::makeShared<::ProviderTest2>());
	EXPECT_EQ(etk::uri::provider::exist(""), true);
	EXPECT_EQ(etk::uri::provider::exist("PLOUF_1"), true);
	EXPECT_EQ(etk::uri::provider::exist("PLOUF_2"), true);
	EXPECT_EQ(s_plouf, 0);
	etk::uri::get("PLOUF_1:///qsdfqsdfqsdfqsdf.txt");
	EXPECT_EQ(s_plouf, 5555);
	etk::uri::get("PLOUF_2:///qsdfqsdfqsdfqsdf.txt");
	EXPECT_EQ(s_plouf, 9999);
	etk::uri::provider::remove("PLOUF_1");
	EXPECT_EQ(etk::uri::provider::exist(""), true);
	EXPECT_EQ(etk::uri::provider::exist("PLOUF_1"), false);
	EXPECT_EQ(etk::uri::provider::exist("PLOUF_2"), true);
	etk::uri::provider::remove("PLOUF_2");
	EXPECT_EQ(etk::uri::provider::exist(""), true);
	EXPECT_EQ(etk::uri::provider::exist("PLOUF_1"), false);
	EXPECT_EQ(etk::uri::provider::exist("PLOUF_2"), false);
}

etk::Vector<etk::Uri> listDirect = {
	"DATA:///data",
	"DATA:///data_sample.zip",
	"DATA:///fileEmpty.txt",
	"DATA:///filePresent.txt",
};

bool uriSortCallback(const etk::Uri& _left, const etk::Uri& _right) {
	TEST_VERBOSE("compare " << _left << " " << (_left <= _right?"<=":">") << " " << _right);
	return _left <= _right;
}

TEST(TestUriProvider, checkDirectAccess) {
	etk::uri::provider::clear();
	TEST_VERBOSE("data path: " << etk::path::getDataPath());
	etk::uri::provider::add("DATA", ememory::makeShared<etk::uri::provider::ProviderFile>(etk::path::getDataPath()));
	EXPECT_EQ(etk::uri::provider::exist("DATA"), true);
	ememory::SharedPtr<etk::uri::provider::Interface> provider = etk::uri::provider::getProvider("DATA");
	EXPECT_NE(provider, null);
	etk::Uri searchBase("DATA:///");
	auto elems = provider->list(searchBase);
	TEST_VERBOSE("List DATA path: (A)");
	for (auto& it: elems) {
		TEST_VERBOSE("     " << it);
	}
	etk::algorithm::quickSort(elems, uriSortCallback);
	TEST_VERBOSE("List DATA path: (C)");
	for (auto& it: elems) {
		TEST_VERBOSE("     " << it);
	}
	TEST_VERBOSE("List corect order:");
	for (auto& it: listDirect) {
		TEST_VERBOSE("     " << it);
	}
	EXPECT_EQ(elems, listDirect);
}
etk::Vector<etk::Uri> listDirect2 = {
	"DATA:///data/.file_hidden.txt",
	"DATA:///data/dir_A",
	"DATA:///data/dir_B",
	"DATA:///data/file_1.txt",
	"DATA:///data/file_2.txt",
	"DATA:///data/file_3.txt"
};

TEST(TestUriProvider, checkDirectAccess2) {
	etk::uri::provider::clear();
	TEST_VERBOSE("data path: " << etk::path::getDataPath());
	etk::uri::provider::add("DATA", ememory::makeShared<etk::uri::provider::ProviderFile>(etk::path::getDataPath()));
	EXPECT_EQ(etk::uri::provider::exist("DATA"), true);
	ememory::SharedPtr<etk::uri::provider::Interface> provider = etk::uri::provider::getProvider("DATA");
	EXPECT_NE(provider, null);
	etk::Uri searchBase("DATA:///data");
	
	auto elems = provider->list(searchBase);
	TEST_VERBOSE("List DATA path: (A)");
	for (auto& it: elems) {
		TEST_VERBOSE("     " << it);
	}
	etk::algorithm::quickSort(elems, uriSortCallback);
	TEST_VERBOSE("List DATA path: (B)");
	for (auto& it: elems) {
		TEST_VERBOSE("     " << it);
	}
	EXPECT_EQ(elems, listDirect2);
}

TEST(TestUriProvider, directExistFile) {
	etk::uri::provider::clear();
	TEST_VERBOSE("data path: " << etk::path::getDataPath());
	etk::uri::provider::add("DATA", ememory::makeShared<etk::uri::provider::ProviderFile>(etk::path::getDataPath()));
	EXPECT_EQ(etk::uri::provider::exist("DATA"), true);
	ememory::SharedPtr<etk::uri::provider::Interface> provider = etk::uri::provider::getProvider("DATA");
	EXPECT_NE(provider, null);
	{
		etk::Uri element("DATA:///data/dir_B/file_B_1.txt");
		EXPECT_EQ(provider->exist(element), true);
	}
	{
		etk::Uri element("DATA:///data/dir_B/file_B_1_qsldkjfqlksjd.txt");
		EXPECT_EQ(provider->exist(element), false);
	}
}

TEST(TestUriProvider, directReadFile) {
	etk::uri::provider::clear();
	TEST_VERBOSE("data path: " << etk::path::getDataPath());
	etk::uri::provider::add("DATA", ememory::makeShared<etk::uri::provider::ProviderFile>(etk::path::getDataPath()));
	EXPECT_EQ(etk::uri::provider::exist("DATA"), true);
	etk::Uri element("DATA:///data/dir_B/file_B_1.txt");
	ememory::SharedPtr<etk::io::Interface> ioElement = etk::uri::get(element);
	EXPECT_EQ(ioElement->open(etk::io::OpenMode::Read), true);
	etk::String data = ioElement->readAllString();
	EXPECT_EQ(ioElement->close(), true);
	EXPECT_EQ(data, "file_B_1.txt");
}



etk::Vector<etk::Uri> listZip = {
	"DATA:///.file_hidden.txt",
	"DATA:///dir_A",
	"DATA:///dir_B",
	"DATA:///file_1.txt",
	"DATA:///file_2.txt",
	"DATA:///file_3.txt"
};

TEST(TestUriProvider, checkZipAccess) {
	etk::uri::provider::clear();
	TEST_VERBOSE("data path: " << etk::path::getDataPath());
	etk::uri::provider::add("DATA", ememory::makeShared<etk::uri::provider::ProviderFileZip>(etk::path::getDataPath() / "data_sample.zip", "data"));
	EXPECT_EQ(etk::uri::provider::exist("DATA"), true);
	ememory::SharedPtr<etk::uri::provider::Interface> provider = etk::uri::provider::getProvider("DATA");
	EXPECT_NE(provider, null);
	TEST_VERBOSE("List DATA path:");
	etk::Uri searchBase("DATA:///");
	auto elems = provider->list(searchBase);
	for (auto& it: elems) {
		TEST_VERBOSE("     " << it);
	}
	EXPECT_EQ(elems, listZip);
}


etk::Vector<etk::Uri> listZip2 = {
	"DATA:///dir_B/dir_C",
	"DATA:///dir_B/file_B_1.txt",
	"DATA:///dir_B/file_B_2.txt",
};

TEST(TestUriProvider, checkZipAccess2) {
	etk::uri::provider::clear();
	TEST_VERBOSE("data path: " << etk::path::getDataPath());
	etk::uri::provider::add("DATA", ememory::makeShared<etk::uri::provider::ProviderFileZip>(etk::path::getDataPath() / "data_sample.zip", "data"));
	EXPECT_EQ(etk::uri::provider::exist("DATA"), true);
	ememory::SharedPtr<etk::uri::provider::Interface> provider = etk::uri::provider::getProvider("DATA");
	EXPECT_NE(provider, null);
	TEST_VERBOSE("List DATA path:");
	etk::Uri searchBase("DATA:///dir_B");
	auto elems = provider->list(searchBase);
	for (auto& it: elems) {
		TEST_VERBOSE("     " << it);
	}
	EXPECT_EQ(elems, listZip2);
}


TEST(TestUriProvider, zipExistFile) {
	etk::uri::provider::clear();
	TEST_VERBOSE("data path: " << etk::path::getDataPath());
	etk::uri::provider::add("DATA", ememory::makeShared<etk::uri::provider::ProviderFileZip>(etk::path::getDataPath() / "data_sample.zip", "data"));
	EXPECT_EQ(etk::uri::provider::exist("DATA"), true);
	ememory::SharedPtr<etk::uri::provider::Interface> provider = etk::uri::provider::getProvider("DATA");
	EXPECT_NE(provider, null);
	{
		etk::Uri element("DATA:///dir_B/file_B_1.txt");
		EXPECT_EQ(provider->exist(element), true);
	}
	{
		etk::Uri element("DATA:///dir_B/file_B_1_qsldkjfqlksjd.txt");
		EXPECT_EQ(provider->exist(element), false);
	}
}

TEST(TestUriProvider, zipReadFile) {
	etk::uri::provider::clear();
	TEST_VERBOSE("data path: " << etk::path::getDataPath());
	etk::uri::provider::add("DATA", ememory::makeShared<etk::uri::provider::ProviderFileZip>(etk::path::getDataPath() / "data_sample.zip", "data"));
	EXPECT_EQ(etk::uri::provider::exist("DATA"), true);
	etk::Uri element("DATA:///dir_B/file_B_1.txt");
	ememory::SharedPtr<etk::io::Interface> ioElement = etk::uri::get(element);
	EXPECT_EQ(ioElement->open(etk::io::OpenMode::Read), true);
	etk::String data = ioElement->readAllString();
	EXPECT_EQ(ioElement->close(), true);
	EXPECT_EQ(data, "file_B_1.txt");
}

