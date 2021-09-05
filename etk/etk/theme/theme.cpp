/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#include <etk/types.hpp>
#include <etk/theme/theme.hpp>
#include <etk/theme/ProviderTheme.hpp>
#include <etk/Map.hpp>
#include <etk/debug.hpp>
#include <etk/uri/uri.hpp>


static etk::Map<etk::String, etk::Path>& getTheme() {
	static etk::Map<etk::String, etk::Path> g_listTheme;
	return g_listTheme;
}

static etk::Map<etk::String, etk::Path>& getThemeDefault() {
	static etk::Map<etk::String, etk::Path> g_listThemeDefault;
	return g_listThemeDefault;
}

static void updateProvider(const etk::String& _refName) {
	etk::Path base = etk::theme::getName(_refName);
	etk::Path baseDefault = etk::theme::getNameDefault(_refName);
	if (base.isEmpty() == true) {
		etk::uri::provider::add("THEME_" + _refName, ememory::makeShared<etk::theme::ProviderTheme>(etk::Path("theme") / baseDefault, etk::Path("theme") / base));
	} else {
		etk::uri::provider::add("THEME_" + _refName, ememory::makeShared<etk::theme::ProviderTheme>(etk::Path("theme") / base, etk::Path("theme") / baseDefault));
	}
}

void etk::theme::init() {
	
}

void etk::theme::unInit() {
	getTheme().clear();
	getThemeDefault().clear();
}

void etk::theme::setName(const etk::String& _refName, const etk::Path& _folderName) {
	TK_WARNING("Change theme : '" << _refName << "' : '" << _folderName << "'");
	getTheme().set(_refName, _folderName);
	updateProvider(_refName);
}

etk::Path etk::theme::getName(const etk::String& _refName) {
	auto it = getTheme().find(_refName);
	if (it != getTheme().end()) {
		return it->second;
	}
	return "";
}

// get the list of all the theme folder availlable in the user Home/appl
etk::Vector<etk::String> etk::theme::list() {
	etk::Vector<etk::String> keys;
	for (auto &it : getTheme()) {
		keys.pushBack(it.first);
	}
	return keys;
}

void etk::theme::setNameDefault(const etk::String& _refName, const etk::Path& _folderName) {
	getThemeDefault().set(_refName, _folderName);
	updateProvider(_refName);
}

etk::Path etk::theme::getNameDefault(const etk::String& _refName) {
	auto it = getThemeDefault().find(_refName);
	if (it != getThemeDefault().end()) {
		return it->second;
	}
	return "default";
}
