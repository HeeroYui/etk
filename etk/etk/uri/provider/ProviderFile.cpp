/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#include <etk/uri/provider/ProviderFile.hpp>
#include <etk/io/File.hpp>
#include <etk/path/fileSystem.hpp>
#include <etk/debug.hpp>

etk::uri::provider::ProviderFile::ProviderFile() {
	
}

etk::uri::provider::ProviderFile::ProviderFile(const etk::Path& _offset) :
  m_offset(_offset) {
	
}

ememory::SharedPtr<etk::io::Interface> etk::uri::provider::ProviderFile::create(const etk::Uri& _uri) {
	if (m_offset.isEmpty() == true) {
		return ememory::makeShared<etk::io::File>(_uri.getPath());
	}
	return ememory::makeShared<etk::io::File>(m_offset / _uri.getPath());
}

bool etk::uri::provider::ProviderFile::exist(const etk::Uri& _uri) {
	if (m_offset.isEmpty() == true) {
		return etk::path::exist(_uri.getPath());
	}
	return etk::path::exist(m_offset / _uri.getPath());
}

bool etk::uri::provider::ProviderFile::isDirectory(const etk::Uri& _uri) {
	if (m_offset.isEmpty() == true) {
		return etk::path::isDirectory(_uri.getPath());
	}
	return etk::path::isDirectory(m_offset / _uri.getPath());
}

bool etk::uri::provider::ProviderFile::isFile(const etk::Uri& _uri) {
	if (m_offset.isEmpty() == true) {
		return etk::path::isFile(_uri.getPath());
	}
	return etk::path::isFile(m_offset / _uri.getPath());
}

bool etk::uri::provider::ProviderFile::isSymLink(const etk::Uri& _uri) {
	if (m_offset.isEmpty() == true) {
		return etk::path::isSymLink(_uri.getPath());
	}
	return etk::path::isSymLink(m_offset / _uri.getPath());
}

etk::Vector<etk::Uri> etk::uri::provider::ProviderFile::list(const etk::Uri& _uri) {
	etk::Vector<etk::Path> tmp;
	etk::Vector<etk::Uri> out;
	if (m_offset.isEmpty() == true) {
		tmp = etk::path::list(_uri.getPath());
		for (auto& elem: tmp) {
			etk::Uri newUri = _uri;
			newUri.setPath(elem);
			out.pushBack(newUri);
		}
		return out;
	}
	TK_VERBOSE("list path: " << m_offset / _uri.getPath());
	tmp = etk::path::list(m_offset / _uri.getPath());
	int32_t offset = m_offset.getString().size()+1;
	for (auto& elem: tmp) {
		etk::Uri newUri = _uri;
		newUri.setPath(elem.getString().extract(offset));
		out.pushBack(newUri);
	}
	return out;
}

etk::Vector<etk::Uri> etk::uri::provider::ProviderFile::listRecursive(const etk::Uri& _uri) {
	etk::Vector<etk::Path> tmp;
	etk::Vector<etk::Uri> out;
	if (m_offset.isEmpty() == true) {
		tmp = etk::path::listRecursive(_uri.getPath());
		for (auto& elem: tmp) {
			etk::Uri newUri = _uri;
			newUri.setPath(elem);
			out.pushBack(newUri);
		}
		return out;
	}
	TK_VERBOSE("list path: " << m_offset / _uri.getPath());
	tmp = etk::path::listRecursive(m_offset / _uri.getPath());
	int32_t offset = m_offset.getString().size()+1;
	for (auto& elem: tmp) {
		etk::Uri newUri = _uri;
		newUri.setPath(elem.getString().extract(offset));
		out.pushBack(newUri);
	}
	return out;
}

bool etk::uri::provider::ProviderFile::canMove() {
	return true;
}

bool etk::uri::provider::ProviderFile::move(const etk::Uri& _uriSource, const etk::Uri& _uriDestination) {
	etk::Path pathSource =_uriSource.getPath();
	if (m_offset.isEmpty() == false) {
		pathSource = m_offset / _uriSource.getPath();
	}
	etk::Path pathDestination =_uriDestination.getPath();
	if (m_offset.isEmpty() == false) {
		pathDestination = m_offset / _uriDestination.getPath();
	}
	return etk::path::move(pathSource, pathDestination);
}

bool etk::uri::provider::ProviderFile::canCopy() {
	return true;
}

bool etk::uri::provider::ProviderFile::copy(const etk::Uri& _uriSource, const etk::Uri& _uriDestination) {
	etk::Path pathSource =_uriSource.getPath();
	if (m_offset.isEmpty() == false) {
		pathSource = m_offset / _uriSource.getPath();
	}
	etk::Path pathDestination =_uriDestination.getPath();
	if (m_offset.isEmpty() == false) {
		pathDestination = m_offset / _uriDestination.getPath();
	}
	return etk::path::copy(pathSource, pathDestination);
}

bool etk::uri::provider::ProviderFile::canRemove() {
	return true;
}

bool etk::uri::provider::ProviderFile::remove(const etk::Uri& _uri) {
	etk::Path pathSource =_uri.getPath();
	if (m_offset.isEmpty() == false) {
		pathSource = m_offset / _uri.getPath();
	}
	return etk::path::remove(pathSource);
}
