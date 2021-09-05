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

TEST(TestUri, defaultContructor) {
	etk::Uri uri;
	EXPECT_EQ(uri.get(), "");
	EXPECT_EQ(uri.getScheme(), "");
	EXPECT_EQ(uri.getUser(), "");
	EXPECT_EQ(uri.getPassword(), "");
	EXPECT_EQ(uri.getServer(), "");
	EXPECT_EQ(uri.getPort(), 0);
	EXPECT_EQ(uri.getPath(), etk::Path(""));
	EXPECT_EQ(uri.getQuery().getEncoded(), "");
	EXPECT_EQ(uri.getFragment(), "");
}

TEST(TestUri, base_1) {
	etk::String value = "__SCHEME__://__USER__:__PASSWORD__@__SERVER__:1234/__PATH__?__QUERY__#__FRAGMENT__";
	etk::Uri uri(value);
	EXPECT_EQ(uri.get(), value);
	EXPECT_EQ(uri.getScheme(), "__SCHEME__");
	EXPECT_EQ(uri.getUser(), "__USER__");
	EXPECT_EQ(uri.getPassword(), "__PASSWORD__");
	EXPECT_EQ(uri.getServer(), "__SERVER__");
	EXPECT_EQ(uri.getPort(), 1234);
	EXPECT_EQ(uri.getPath(), etk::Path("__PATH__"));
	EXPECT_EQ(uri.getQuery().getEncoded(), "__QUERY__");
	EXPECT_EQ(uri.getFragment(), "__FRAGMENT__");
}

TEST(TestUri, base_2) {
	etk::String value = "__SCHEME__://__USER__@__SERVER__:1234/__PATH__?__QUERY__#__FRAGMENT__";
	etk::Uri uri(value);
	EXPECT_EQ(uri.get(), value);
	EXPECT_EQ(uri.getScheme(), "__SCHEME__");
	EXPECT_EQ(uri.getUser(), "__USER__");
	EXPECT_EQ(uri.getPassword(), "");
	EXPECT_EQ(uri.getServer(), "__SERVER__");
	EXPECT_EQ(uri.getPort(), 1234);
	EXPECT_EQ(uri.getPath(), etk::Path("__PATH__"));
	EXPECT_EQ(uri.getQuery().getEncoded(), "__QUERY__");
	EXPECT_EQ(uri.getFragment(), "__FRAGMENT__");
}

TEST(TestUri, base_3) {
	etk::String value = "__SCHEME__://__SERVER__:1234/__PATH__?__QUERY__#__FRAGMENT__";
	etk::Uri uri(value);
	EXPECT_EQ(uri.get(), value);
	EXPECT_EQ(uri.getScheme(), "__SCHEME__");
	EXPECT_EQ(uri.getUser(), "");
	EXPECT_EQ(uri.getPassword(), "");
	EXPECT_EQ(uri.getServer(), "__SERVER__");
	EXPECT_EQ(uri.getPort(), 1234);
	EXPECT_EQ(uri.getPath(), etk::Path("__PATH__"));
	EXPECT_EQ(uri.getQuery().getEncoded(), "__QUERY__");
	EXPECT_EQ(uri.getFragment(), "__FRAGMENT__");
}

TEST(TestUri, base_4) {
	etk::String value = "__SERVER__:1234/__PATH__?__QUERY__#__FRAGMENT__";
	etk::Uri uri(value);
	EXPECT_EQ(uri.get(), value);
	EXPECT_EQ(uri.getScheme(), "");
	EXPECT_EQ(uri.getUser(), "");
	EXPECT_EQ(uri.getPassword(), "");
	EXPECT_EQ(uri.getServer(), "__SERVER__");
	EXPECT_EQ(uri.getPort(), 1234);
	EXPECT_EQ(uri.getPath(), etk::Path("__PATH__"));
	EXPECT_EQ(uri.getQuery().getEncoded(), "__QUERY__");
	EXPECT_EQ(uri.getFragment(), "__FRAGMENT__");
}

TEST(TestUri, base_5) {
	etk::String value = "__SERVER__/__PATH__?__QUERY__#__FRAGMENT__";
	etk::Uri uri(value);
	EXPECT_EQ(uri.get(), value);
	EXPECT_EQ(uri.getScheme(), "");
	EXPECT_EQ(uri.getUser(), "");
	EXPECT_EQ(uri.getPassword(), "");
	EXPECT_EQ(uri.getServer(), "__SERVER__");
	EXPECT_EQ(uri.getPort(), 0);
	EXPECT_EQ(uri.getPath(), etk::Path("__PATH__"));
	EXPECT_EQ(uri.getQuery().getEncoded(), "__QUERY__");
	EXPECT_EQ(uri.getFragment(), "__FRAGMENT__");
}

TEST(TestUri, base_6) {
	etk::String value = "__SERVER__/__PATH__?__QUERY__";
	etk::Uri uri(value);
	EXPECT_EQ(uri.get(), value);
	EXPECT_EQ(uri.getScheme(), "");
	EXPECT_EQ(uri.getUser(), "");
	EXPECT_EQ(uri.getPassword(), "");
	EXPECT_EQ(uri.getServer(), "__SERVER__");
	EXPECT_EQ(uri.getPort(), 0);
	EXPECT_EQ(uri.getPath(), etk::Path("__PATH__"));
	EXPECT_EQ(uri.getQuery().getEncoded(), "__QUERY__");
	EXPECT_EQ(uri.getFragment(), "");
}

TEST(TestUri, base_7) {
	etk::String value = "__SERVER__/__PATH__";
	etk::Uri uri(value);
	EXPECT_EQ(uri.get(), value);
	EXPECT_EQ(uri.getScheme(), "");
	EXPECT_EQ(uri.getUser(), "");
	EXPECT_EQ(uri.getPassword(), "");
	EXPECT_EQ(uri.getServer(), "__SERVER__");
	EXPECT_EQ(uri.getPort(), 0);
	EXPECT_EQ(uri.getPath(), etk::Path("__PATH__"));
	EXPECT_EQ(uri.getQuery().getEncoded(), "");
	EXPECT_EQ(uri.getFragment(), "");
}

TEST(TestUri, base_8) {
	etk::String value = "__SERVER__";
	etk::Uri uri(value);
	EXPECT_EQ(uri.get(), value);
	EXPECT_EQ(uri.getScheme(), "");
	EXPECT_EQ(uri.getUser(), "");
	EXPECT_EQ(uri.getPassword(), "");
	EXPECT_EQ(uri.getServer(), "__SERVER__");
	EXPECT_EQ(uri.getPort(), 0);
	EXPECT_EQ(uri.getPath(), etk::Path(""));
	EXPECT_EQ(uri.getQuery().getEncoded(), "");
	EXPECT_EQ(uri.getFragment(), "");
}


TEST(TestUri, base_9) {
	etk::String value = "__SERVER__:1234";
	etk::Uri uri(value);
	EXPECT_EQ(uri.get(), value);
	EXPECT_EQ(uri.getScheme(), "");
	EXPECT_EQ(uri.getUser(), "");
	EXPECT_EQ(uri.getPassword(), "");
	EXPECT_EQ(uri.getServer(), "__SERVER__");
	EXPECT_EQ(uri.getPort(), 1234);
	EXPECT_EQ(uri.getPath(), etk::Path(""));
	EXPECT_EQ(uri.getQuery().getEncoded(), "");
	EXPECT_EQ(uri.getFragment(), "");
}

TEST(TestUri, base_10) {
	etk::String value = "__SCHEME__:////__PATH__?__QUERY__";
	etk::Uri uri(value);
	EXPECT_EQ(uri.get(), value);
	EXPECT_EQ(uri.getScheme(), "__SCHEME__");
	EXPECT_EQ(uri.getUser(), "");
	EXPECT_EQ(uri.getPassword(), "");
	EXPECT_EQ(uri.getServer(), "");
	EXPECT_EQ(uri.getPort(), 0);
	EXPECT_EQ(uri.getPath(), etk::Path("/__PATH__"));
	EXPECT_EQ(uri.getQuery().getEncoded(), "__QUERY__");
	EXPECT_EQ(uri.getFragment(), "");
}

TEST(TestUri, base_10_2) {
	etk::String value = "__SCHEME__:///__PATH__?__QUERY__";
	etk::Uri uri(value);
	EXPECT_EQ(uri.get(), value);
	EXPECT_EQ(uri.getScheme(), "__SCHEME__");
	EXPECT_EQ(uri.getUser(), "");
	EXPECT_EQ(uri.getPassword(), "");
	EXPECT_EQ(uri.getServer(), "");
	EXPECT_EQ(uri.getPort(), 0);
	EXPECT_EQ(uri.getPath(), etk::Path("__PATH__"));
	EXPECT_EQ(uri.getQuery().getEncoded(), "__QUERY__");
	EXPECT_EQ(uri.getFragment(), "");
}

TEST(TestUri, base_11_1) {
	etk::String value = "//hello/txt";
	etk::Path valuePath = "/hello/txt";
	etk::Uri uri(valuePath);
	EXPECT_EQ(uri.get(), value);
	EXPECT_EQ(uri.getScheme(), "");
	EXPECT_EQ(uri.getUser(), "");
	EXPECT_EQ(uri.getPassword(), "");
	EXPECT_EQ(uri.getServer(), "");
	EXPECT_EQ(uri.getPort(), 0);
	EXPECT_EQ(uri.getPath(), valuePath);
	EXPECT_EQ(uri.getQuery().getEncoded(), "");
	EXPECT_EQ(uri.getFragment(), "");
}

TEST(TestUri, base_11_2) {
	etk::String value = "/hello/txt";
	etk::Path valuePath = "hello/txt";
	etk::Uri uri(valuePath);
	EXPECT_EQ(uri.get(), value);
	EXPECT_EQ(uri.getScheme(), "");
	EXPECT_EQ(uri.getUser(), "");
	EXPECT_EQ(uri.getPassword(), "");
	EXPECT_EQ(uri.getServer(), "");
	EXPECT_EQ(uri.getPort(), 0);
	EXPECT_EQ(uri.getPath(), valuePath);
	EXPECT_EQ(uri.getQuery().getEncoded(), "");
	EXPECT_EQ(uri.getFragment(), "");
}
// "audio://alsa/front?mode=I16"

