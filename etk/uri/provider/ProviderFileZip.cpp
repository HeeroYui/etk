/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#include <etk/uri/provider/ProviderFileZip.hpp>
#include <etk/debug.hpp>
#include <etk/io/ZipFile.hpp>

void etk::uri::provider::ProviderFileZip::loadZipFile(const etk::Uri& _zipFile) {
	m_archive = etk::Archive::load(_zipFile);
	TK_ASSERT(m_archive != null, "Error loading APK ...  '" << _zipFile << "'");
	#ifdef DEBUG
		//Just for debug, print APK contents
		m_archive->display();
	#endif
}

etk::uri::provider::ProviderFileZip::ProviderFileZip(const etk::Uri& _zipFile) {
	loadZipFile(_zipFile);
}

etk::uri::provider::ProviderFileZip::ProviderFileZip(const etk::Uri& _zipFile, const etk::Path& _offset) :
  m_offset(_offset) {
	loadZipFile(_zipFile);
}

ememory::SharedPtr<etk::io::Interface> etk::uri::provider::ProviderFileZip::create(const etk::Uri& _uri) {
	if (m_offset.isEmpty() == true) {
		return ememory::makeShared<etk::io::ZipFile>(_uri.getPath(), m_archive);
	}
	return ememory::makeShared<etk::io::ZipFile>(m_offset / _uri.getPath(), m_archive);
}

bool etk::uri::provider::ProviderFileZip::exist(const etk::Uri& _uri) {
	if (m_offset.isEmpty() == true) {
		return m_archive->exist(_uri.getPath());
	}
	return m_archive->exist(m_offset / _uri.getPath());
}

etk::Vector<etk::Uri> etk::uri::provider::ProviderFileZip::list(const etk::Uri& _uri) {
	etk::Vector<etk::Path> tmp;
	etk::Vector<etk::Uri> out;
	if (m_offset.isEmpty() == true) {
		tmp = m_archive->list(_uri.getPath());
		for (auto& elem: tmp) {
			etk::Uri newUri = _uri;
			newUri.setPath(elem);
			out.pushBack(newUri);
		}
		return out;
	}
	tmp = m_archive->list(m_offset / _uri.getPath());
	int32_t offset = m_offset.getString().size()+1;
	for (auto& elem: tmp) {
		etk::Uri newUri = _uri;
		newUri.setPath(elem.getString().extract(offset));
		out.pushBack(newUri);
	}
	return out;
}
