/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#include <etk/theme/ProviderTheme.hpp>
#include <etk/io/File.hpp>
#include <etk/path/fileSystem.hpp>
#include <etk/debug.hpp>
#include <etk/uri/uri.hpp>

etk::theme::ProviderTheme::ProviderTheme() {
	
}

etk::theme::ProviderTheme::ProviderTheme(const etk::Path& _offset, const etk::Path& _offsetDefault) :
  m_offset(_offset),
  m_offsetDefault(_offsetDefault) {
	
}

ememory::SharedPtr<etk::io::Interface> etk::theme::ProviderTheme::create(const etk::Uri& _uri) {
	etk::Uri uri = _uri;
	uri.setScheme("DATA");
	TK_WARNING("Create URI file IO " << _uri);
	if (m_offset.isEmpty() == true) {
		TK_WARNING("    check " << uri);
		if (etk::uri::exist(uri) == true) {
			TK_WARNING("        ==> find");
			return etk::uri::get(uri);
		}
	} else {
		uri.setPath(m_offset / _uri.getPath());
		TK_WARNING("    check " << uri);
		if (etk::uri::exist(uri) == true) {
			TK_WARNING("        ==> find");
			return etk::uri::get(uri);
		}
	}
	if (    m_offsetDefault.isEmpty() == false
	     && m_offsetDefault != "theme") {
		etk::Uri uri2 = uri;
		uri2.setPath(m_offsetDefault / _uri.getPath());
		TK_WARNING("    check " << uri2);
		if (etk::uri::exist(uri2) == true) {
			TK_WARNING("        ==> find");
			return etk::uri::get(uri2);
		}
	}
	TK_WARNING("    ** Find nothing ...");
	return etk::uri::get(uri);
}

bool etk::theme::ProviderTheme::exist(const etk::Uri& _uri) {
	etk::Uri uri = _uri;
	uri.setScheme("DATA");
	TK_WARNING("Exist URI file IO " << _uri);
	if (m_offset.isEmpty() == true) {
		TK_WARNING("    check " << uri);
		if (etk::uri::exist(uri) == true) {
			TK_WARNING("        ==> true");
			return true;
		}
	} else {
		uri.setPath(m_offset / _uri.getPath());
		TK_WARNING("    check " << uri);
		if (etk::uri::exist(uri) == true) {
			TK_WARNING("        ==> true");
			return true;
		}
	}
	if (    m_offsetDefault.isEmpty() == false
	     && m_offsetDefault != "theme") {
		etk::Uri uri2 = uri;
		uri2.setPath(m_offsetDefault / _uri.getPath());
		TK_WARNING("    check " << uri2);
		if (etk::uri::exist(uri2) == true) {
			TK_WARNING("        ==> true");
			return true;
		}
	}
	TK_WARNING("    ** Find nothing ...");
	return false;
}

bool etk::theme::ProviderTheme::isDirectory(const etk::Uri& _uri) {
	// TODO:
	throw "kjkjkj";
}

bool etk::theme::ProviderTheme::isFile(const etk::Uri& _uri) {
	// TODO:
	throw "kjkjkj";
}

bool etk::theme::ProviderTheme::isSymLink(const etk::Uri& _uri) {
	// TODO:
	throw "kjkjkj";
}

etk::Vector<etk::Uri> etk::theme::ProviderTheme::list(const etk::Uri& _uri) {
	etk::Uri uri = _uri;
	uri.setScheme("DATA");
	etk::Vector<etk::Uri> directList;
	if (m_offset.isEmpty() == true) {
		directList = etk::uri::list(uri);
	} else {
		uri.setPath(m_offset / _uri.getPath());
		directList = etk::uri::list(uri);
	}
	etk::Vector<etk::Uri> defaultList;
	if (    m_offsetDefault.isEmpty() == false
	     && m_offsetDefault != "theme") {
		uri.setPath(m_offsetDefault / _uri.getPath());
		defaultList = etk::uri::list(uri);
	}
	for (auto& it: defaultList) {
		it.setScheme(_uri.getScheme());
	}
	for (auto& it: directList) {
		it.setScheme(_uri.getScheme());
	}
	if (defaultList.size() == 0) {
		return directList;
	}
	if (directList.size() == 0) {
		return defaultList;
	}
	for (auto& it: defaultList) {
		if (etk::isIn(it, directList) == false) {
			directList.pushBack(it);
		}
	}
	return directList;
}

etk::Vector<etk::Uri> etk::theme::ProviderTheme::listRecursive(const etk::Uri& _uri) {
	etk::Uri uri = _uri;
	uri.setScheme("DATA");
	etk::Vector<etk::Uri> directList;
	if (m_offset.isEmpty() == true) {
		directList = etk::uri::listRecursive(uri);
	} else {
		uri.setPath(m_offset / _uri.getPath());
		directList = etk::uri::listRecursive(uri);
	}
	etk::Vector<etk::Uri> defaultList;
	if (    m_offsetDefault.isEmpty() == false
	     && m_offsetDefault != "theme") {
		uri.setPath(m_offsetDefault / _uri.getPath());
		defaultList = etk::uri::listRecursive(uri);
	}
	for (auto& it: defaultList) {
		it.setScheme(_uri.getScheme());
	}
	for (auto& it: directList) {
		it.setScheme(_uri.getScheme());
	}
	if (defaultList.size() == 0) {
		return directList;
	}
	if (directList.size() == 0) {
		return defaultList;
	}
	for (auto& it: defaultList) {
		if (etk::isIn(it, directList) == false) {
			directList.pushBack(it);
		}
	}
	return directList;
}

