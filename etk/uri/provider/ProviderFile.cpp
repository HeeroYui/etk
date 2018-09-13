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
