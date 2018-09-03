/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#ifdef ETK_BUILD_MINIZIP

#include <etk/archive/Archive.hpp>
#include <etk/archive/Zip.hpp>
#include <etk/debug.hpp>
#include <etk/typeInfo.hpp>

ETK_DECLARE_TYPE(etk::Archive);

etk::Path etk::Archive::getName(size_t _id) const {
	ethread::UniqueLock lock(m_mutex);
	size_t id = 0;
	for (auto &it : m_content) {
		if (id == _id) {
			return it.first;
		}
		++id;
	}
	return "";
}

ememory::SharedPtr<etk::ArchiveContent> etk::Archive::getContent(size_t _id) const {
	ethread::UniqueLock lock(m_mutex);
	size_t id = 0;
	for (auto &it : m_content) {
		if (id == _id) {
			return it.second;
		}
		++id;
	}
	return null;
}

ememory::SharedPtr<etk::ArchiveContent> etk::Archive::getContent(const etk::Path& _key) const {
	ethread::UniqueLock lock(m_mutex);
	auto it = m_content.find(_key);
	if (it == m_content.end()) {
		return null;
	}
	return it->second;
}


bool etk::Archive::exist(const etk::Path& _key) const {
	ethread::UniqueLock lock(m_mutex);
	return m_content.find(_key) != m_content.end();
}

void etk::Archive::display() {
	ethread::UniqueLock lock(m_mutex);
	for (auto &it : m_content) {
		int32_t size = it.second->getTheoricSize();
		int32_t sizeR = it.second->size();
		TK_INFO(" element : " << it.first << " size=" << size << " allocated=" << sizeR);
	}
}

ememory::SharedPtr<etk::Archive> etk::Archive::load(const etk::Path& _fileName) {
	ememory::SharedPtr<etk::Archive> output;
	etk::String extention = _fileName.getExtention().toLower();
	// select the corect Loader :
	if(    extention == "zip"
	    || extention == ".apk") {
		output = ememory::makeShared<etk::archive::Zip>(_fileName);
		if (output == null) {
			TK_ERROR("An error occured when load archive : " << _fileName);
		}
	} else {
		TK_ERROR("Extention not managed " << _fileName << " Sopported extention : .zip");
	}
	return output;
}

ememory::SharedPtr<etk::Archive> etk::Archive::loadPackage(const etk::Path& _fileName) {
	ememory::SharedPtr<etk::Archive> output;
	FILE* file = fopen(_fileName.getNative().c_str(), "rb");
	if (file == null) {
		TK_ERROR("Can not open file : '" << _fileName);
		return null;
	}
	// move to end - 16 bytes:
	fseek(file, -8, SEEK_END);
	// get the basic binary size
	uint64_t position = 0;
	fread(&position, 1, sizeof(uint64_t), file);
	TK_ERROR("position = " << position);
	// move to the position
	fseek(file, position, SEEK_SET);
	char plop[1024];
	fread(plop, 1, 16, file);
	plop[16] = '\0';
	// check if we have the mark: "***START DATA***" ==> if not ==> error
	if (etk::String(plop) != "***START DATA***") {
		TK_ERROR("Error in the tag file : '" << plop << "'");
		fclose(file);
		return null;
	}
	fclose(file);
	file = null;
	output = ememory::makeShared<etk::archive::Zip>(_fileName, position);
	if (output == null) {
		TK_ERROR("An error occured when load archive : " << _fileName);
	}
	return output;
}


void etk::Archive::open(const etk::Path& _key) {
	ethread::UniqueLock lock(m_mutex);
	auto it = m_content.find(_key);
	if (it == m_content.end()) {
		TK_ERROR("Try open an unexistant file : '" << _key << "'");
		return;
	}
	if (it->second->getNumberOfRef()==-1) {
		loadFile(it);
		it->second->increaseRef();
	}
	it->second->increaseRef();
}

void etk::Archive::close(const etk::Path& _key) {
	ethread::UniqueLock lock(m_mutex);
	auto it = m_content.find(_key);
	if (it == m_content.end()) {
		TK_ERROR("Try close an unexistant file : '" << _key << "'");
		return;
	}
	if (it->second->getNumberOfRef()==0){
		TK_ERROR("Try close one more time the file : '" << _key << "'");
	} else {
		it->second->decreaseRef();
	}
}

#endif