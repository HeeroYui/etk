/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */

#include <etest/etest.hpp>
#include <test-debug/debug.hpp>
#include <etk/uri/Uri.hpp>
#include <etk/uri/provider/provider.hpp>
#include <etk/uri/provider/ProviderFile.hpp>
#include <etk/uri/provider/ProviderFileZip.hpp>
#include <etk/fs/fileSystem.hpp>



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
	};
}


TEST(TestUriProvider, checkPlouf) {
	etk::uri::provider::clear();
	s_plouf = 0;
	EXPECT_EQ(etk::uri::provider::exist(""), true);
	EXPECT_EQ(etk::uri::provider::exist("RAW"), true);
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
	etk::uri::provider::get("PLOUF_1:///qsdfqsdfqsdfqsdf.txt");
	EXPECT_EQ(s_plouf, 5555);
	etk::uri::provider::get("PLOUF_2:///qsdfqsdfqsdfqsdf.txt");
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
	"DATA:///filePresent.txt",
	"DATA:///fileEmpty.txt",
	"DATA:///data",
	"DATA:///data_sample.zip",
};

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
	array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int_t partition (etk::Vector<etk::Uri>& _data, int _low, int _high) {
	int_t iii = (_low - 1);  // Index of smaller element
	for (int_t jjj = _low; jjj < _high; ++jjj) {
		// If current element is smaller than or equal to pivot
		if (_data[jjj] < _data[_high]) {
			iii++;	// increment index of smaller element
			etk::swap(_data[iii], _data[jjj]);
		}
	}
	etk::swap(_data[iii + 1], _data[_high]);
	return (iii + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(etk::Vector<etk::Uri>& _data, int _low, int _high) {
	if (_low >= _high) {
		return;
	}
	// pi is partitioning index, arr[p] is now at right place
	int_t pi = partition(_data, _low, _high);
	// Separately sort elements before partition and after partition
	quickSort(_data, _low, pi - 1);
	quickSort(_data, pi + 1, _high);
}

TEST(TestUriProvider, checkDirectAccess) {
	etk::uri::provider::clear();
	TEST_VERBOSE("data path: " << etk::fs::getDataPath());
	etk::uri::provider::add("DATA", ememory::makeShared<etk::uri::provider::ProviderFile>(etk::fs::getDataPath()));
	EXPECT_EQ(etk::uri::provider::exist("DATA"), true);
	ememory::SharedPtr<etk::uri::provider::Interface> provider = etk::uri::provider::getProvider("DATA");
	EXPECT_NE(provider, null);
	etk::Uri searchBase("DATA:///");
	auto elems = provider->list(searchBase);
	TEST_WARNING("List DATA path: (A)");
	for (auto& it: elems) {
		TEST_WARNING("     " << it);
	}
	elems.sort(0, elems.size(), [] (const etk::Uri& _left, const etk::Uri& _right) {
	    	TEST_WARNING("compare " << _left << " " << (_left < _right?"<":">=") << " " << _right);
	    	
	    	return _left < _right;
	    });
	TEST_WARNING("List DATA path: (B)");
	for (auto& it: elems) {
		TEST_WARNING("     " << it);
	}
	quickSort(elems, 0, elems.size()-1);
	TEST_WARNING("List DATA path: (C)");
	for (auto& it: elems) {
		TEST_WARNING("     " << it);
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
	TEST_VERBOSE("data path: " << etk::fs::getDataPath());
	etk::uri::provider::add("DATA", ememory::makeShared<etk::uri::provider::ProviderFile>(etk::fs::getDataPath()));
	EXPECT_EQ(etk::uri::provider::exist("DATA"), true);
	ememory::SharedPtr<etk::uri::provider::Interface> provider = etk::uri::provider::getProvider("DATA");
	EXPECT_NE(provider, null);
	etk::Uri searchBase("DATA:///data");
	
	auto elems = provider->list(searchBase);
	TEST_WARNING("List DATA path: (A)");
	for (auto& it: elems) {
		TEST_WARNING("     " << it);
	}
	elems.sort(0, elems.size(), [] (const etk::Uri& _left, const etk::Uri& _right) {
	    	return _left < _right;
	    });
	TEST_WARNING("List DATA path: (B)");
	for (auto& it: elems) {
		TEST_WARNING("     " << it);
	}
	EXPECT_EQ(elems, listDirect2);
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
	TEST_VERBOSE("data path: " << etk::fs::getDataPath());
	etk::uri::provider::add("DATA", ememory::makeShared<etk::uri::provider::ProviderFileZip>(etk::fs::getDataPath() / "data_sample.zip", "data"));
	EXPECT_EQ(etk::uri::provider::exist("DATA"), true);
	ememory::SharedPtr<etk::uri::provider::Interface> provider = etk::uri::provider::getProvider("DATA");
	EXPECT_NE(provider, null);
	TEST_WARNING("List DATA path:");
	etk::Uri searchBase("DATA://");
	auto elems = provider->list(searchBase);
	for (auto& it: elems) {
		TEST_WARNING("     " << it);
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
	TEST_VERBOSE("data path: " << etk::fs::getDataPath());
	etk::uri::provider::add("DATA", ememory::makeShared<etk::uri::provider::ProviderFileZip>(etk::fs::getDataPath() / "data_sample.zip", "data"));
	EXPECT_EQ(etk::uri::provider::exist("DATA"), true);
	ememory::SharedPtr<etk::uri::provider::Interface> provider = etk::uri::provider::getProvider("DATA");
	EXPECT_NE(provider, null);
	TEST_WARNING("List DATA path:");
	etk::Uri searchBase("DATA:///dir_B");
	auto elems = provider->list(searchBase);
	for (auto& it: elems) {
		TEST_WARNING("     " << it);
	}
	EXPECT_EQ(elems, listZip2);
}

