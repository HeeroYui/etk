/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#include <etk/types.hpp>
#include <etk/theme/theme.hpp>
#include <etk/Map.hpp>
#include <etk/debug.hpp>


static etk::Map<etk::String, etk::String>& getTheme() {
	static etk::Map<etk::String, etk::String> g_listTheme;
	return g_listTheme;
}

static etk::Map<etk::String, etk::String>& getThemeDefault() {
	static etk::Map<etk::String, etk::String> g_listThemeDefault;
	return g_listThemeDefault;
}

void etk::theme::init() {
	
}

void etk::theme::unInit() {
	getTheme().clear();
	getThemeDefault().clear();
}

void etk::theme::setName(const etk::String& _refName, const etk::String& _folderName) {
	TK_WARNING("Change theme : '" << _refName << "' : '" << _folderName << "'");
	getTheme().set(_refName, _folderName);
}

etk::String etk::theme::getName(const etk::String& _refName) {
	auto it = getTheme().find(_refName);
	if (it != getTheme().end()) {
		return it->second;
	}
	return _refName;
}

// get the list of all the theme folder availlable in the user Home/appl
etk::Vector<etk::String> etk::theme::list() {
	etk::Vector<etk::String> keys;
	for (auto &it : getTheme()) {
		keys.pushBack(it.first);
	}
	return keys;
}

void etk::theme::setNameDefault(const etk::String& _refName, const etk::String& _folderName) {
	auto it = getThemeDefault().find(_refName);
	if (it != getThemeDefault().end()) {
		it->second = _folderName;
		return;
	}
	getThemeDefault().set(_refName, _folderName);
}

etk::String etk::theme::getNameDefault(const etk::String& _refName) {
	auto it = getThemeDefault().find(_refName);
	if (it != getThemeDefault().end()) {
		return it->second;
	}
	return "default";
}
