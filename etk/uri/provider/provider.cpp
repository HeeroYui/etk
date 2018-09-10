/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#include <etk/uri/provider/provider.hpp>
#include <etk/uri/provider/ProviderFile.hpp>
#include <etk/Map.hpp>
#include <etk/io/File.hpp>

static etk::Map<etk::String, ememory::SharedPtr<etk::uri::provider::Interface>>& getProviders() {
	static etk::Map<etk::String, ememory::SharedPtr<etk::uri::provider::Interface>> g_data;
	return g_data;
}

void etk::uri::provider::add(const etk::String& _scheme, ememory::SharedPtr<etk::uri::provider::Interface> _interface) {
	etk::String scheme = _scheme;
	if (scheme.empty() == true) {
		scheme = "RAW";
	}
	getProviders().set(scheme, _interface);
}

void etk::uri::provider::clear() {
	getProviders().clear();
	etk::uri::provider::add("", ememory::makeShared<etk::uri::provider::ProviderFile>());
}

void etk::uri::provider::remove(const etk::String& _scheme) {
	getProviders().erase(_scheme);
}

bool etk::uri::provider::exist(const etk::String& _scheme) {
	etk::String scheme = _scheme;
	if (scheme.empty() == true) {
		scheme = "RAW";
	}
	return getProviders().exist(scheme);
}

ememory::SharedPtr<etk::io::Interface> etk::uri::provider::get(const etk::Uri& _uri) {
	etk::String scheme = _uri.getScheme();
	if (scheme.empty() == true) {
		scheme = "RAW";
	}
	if (getProviders().exist(scheme) == false) {
		return null;
	}
	return getProviders()[scheme]->create(_uri);
}
ememory::SharedPtr<etk::uri::provider::Interface> etk::uri::provider::getProvider(const etk::String& _scheme) {
	etk::String scheme = _scheme;
	if (scheme.empty() == true) {
		scheme = "RAW";
	}
	if (getProviders().exist(scheme) == false) {
		return null;
	}
	return getProviders()[scheme];
}

void etk::uri::provider::init() {
	etk::uri::provider::clear();
}

void etk::uri::provider::unInit() {
	getProviders().clear();
}
