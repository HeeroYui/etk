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
		TK_ERROR("Extention not managed '" << _fileName << "' Supported extention : .zip");
	}
	return output;
}
ememory::SharedPtr<etk::Archive> etk::Archive::load(const etk::Uri& _uri) {
	ememory::SharedPtr<etk::Archive> output;
	etk::String extention = _uri.getPath().getExtention().toLower();
	// select the corect Loader :
	if(    extention == "zip"
	    || extention == ".apk") {
		output = ememory::makeShared<etk::archive::Zip>(_uri);
		if (output == null) {
			TK_ERROR("An error occured when load archive : " << _uri);
		}
	} else {
		TK_ERROR("Extention not managed '" << _uri << "' Supported extention : .zip");
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

etk::Vector<etk::Path> etk::Archive::list(const etk::Path& _path) {
	etk::Vector<etk::Path> out;
	etk::String base = _path.getString();
	for (auto& it: m_content) {
		etk::String name = it.first.getString();
		if (name.size() < base.size()) {
			continue;
		}
		if (etk::start_with(name, base) == true) {
			// element or subElement...
			if (it.first.getParent() == _path) {
				out.pushBack(it.first);
				continue;
			}
			etk::String back = name.extract(base.size());
			if (    back.size() == 0
			     || back[0] != '/') {
				continue;
			}
			back.erase(back.begin());
			size_t pos = back.find('/');
			if (pos == etk::String::npos) {
				continue;
			}
			etk::String value = back.extract(0, pos);
			etk::Path tmpppp = etk::Path(base) / value;
			if (etk::isIn(tmpppp, out) == false) {
				out.pushBack(tmpppp);
			}
		}
	}
	return out;
}

#endif
