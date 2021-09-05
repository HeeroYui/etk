/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#include <etk/uri/provider/provider.hpp>
#include <etk/uri/provider/ProviderFile.hpp>
#include <etk/Map.hpp>
#include <etk/io/File.hpp>
#include <etk/debug.hpp>

namespace etk {
	namespace uri {
		namespace provider {
			etk::Map<etk::String, ememory::SharedPtr<etk::uri::provider::Interface>>& getProviders();
			etk::Map<etk::String, ememory::SharedPtr<etk::uri::provider::Interface>>& getProviders() {
				static etk::Map<etk::String, ememory::SharedPtr<etk::uri::provider::Interface>> g_data;
				return g_data;
			}
		}
	}
}

static void displayProviders() {
	TK_INFO("List all datat provider:");
	for (auto& it: etk::uri::provider::getProviders()) {
		TK_INFO("    - " << it.first);
	}
}

void etk::uri::provider::add(const etk::String& _scheme, ememory::SharedPtr<etk::uri::provider::Interface> _interface) {
	etk::String scheme = _scheme;
	if (scheme.empty() == true) {
		scheme = "FILE";
	}
	etk::uri::provider::getProviders().set(scheme, _interface);
	displayProviders();
}

void etk::uri::provider::clear() {
	etk::uri::provider::getProviders().clear();
	etk::uri::provider::add("", ememory::makeShared<etk::uri::provider::ProviderFile>());
	displayProviders();
}

void etk::uri::provider::remove(const etk::String& _scheme) {
	etk::uri::provider::getProviders().erase(_scheme);
	displayProviders();
}

bool etk::uri::provider::exist(const etk::String& _scheme) {
	etk::String scheme = _scheme;
	if (scheme.empty() == true) {
		scheme = "FILE";
	}
	return etk::uri::provider::getProviders().exist(scheme);
}

ememory::SharedPtr<etk::uri::provider::Interface> etk::uri::provider::getProvider(const etk::String& _scheme) {
	etk::String scheme = _scheme;
	if (scheme.empty() == true) {
		scheme = "FILE";
	}
	if (etk::uri::provider::getProviders().exist(scheme) == false) {
		return null;
	}
	return etk::uri::provider::getProviders()[scheme];
}

void etk::uri::provider::init() {
	etk::uri::provider::clear();
}

void etk::uri::provider::unInit() {
	etk::uri::provider::getProviders().clear();
}

