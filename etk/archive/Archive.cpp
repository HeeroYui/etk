/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#ifdef ETK_BUILD_MINIZIP

#include <etk/archive/Archive.hpp>
#include <etk/archive/Zip.hpp>
#include <etk/debug.hpp>

static const etk::ArchiveContent g_error;


const etk::String& etk::Archive::getName(size_t _id) const {
	std::unique_lock<std::mutex> lock(m_mutex);
	size_t id = 0;
	for (auto &it : m_content) {
		if (id == _id) {
			return it.getKey();
		}
		++id;
	}
	static const etk::String error("");
	return error;
}

const etk::ArchiveContent& etk::Archive::getContent(size_t _id) const {
	std::unique_lock<std::mutex> lock(m_mutex);
	size_t id = 0;
	for (auto &it : m_content) {
		if (id == _id) {
			return it.getValue();
		}
		++id;
	}
	return g_error;
}

const etk::ArchiveContent& etk::Archive::getContent(const etk::String& _key) const {
	std::unique_lock<std::mutex> lock(m_mutex);
	auto it = m_content.find(_key);
	if (it == m_content.end()) {
		return g_error;
	}
	return it->getValue();
}


bool etk::Archive::exist(const etk::String& _key) const {
	std::unique_lock<std::mutex> lock(m_mutex);
	return m_content.find(_key) != m_content.end();
}

void etk::Archive::display() {
	std::unique_lock<std::mutex> lock(m_mutex);
	for (auto &it : m_content) {
		int32_t size = it.getValue().getTheoricSize();
		int32_t sizeR = it.getValue().size();
		TK_INFO(" element : " << it.getKey() << " size=" << size << " allocated=" << sizeR);
	}
}

etk::Archive* etk::Archive::load(const etk::String& _fileName) {
	etk::Archive* output=nullptr;
	etk::String tmpName = _fileName.toLower();
	// select the corect Loader :
	if(    tmpName.endWith(".zip") == true
	    || tmpName.endWith(".apk") == true ) {
		output = new etk::archive::Zip(_fileName);
		if (output == nullptr) {
			TK_ERROR("An error occured when load archive : " << _fileName);
		}
	} else {
		TK_ERROR("Extention not managed " << _fileName << " Sopported extention : .zip");
	}
	return output;
}

etk::Archive* etk::Archive::loadPackage(const etk::String& _fileName) {
	etk::Archive* output=nullptr;
	FILE* file = fopen(_fileName.c_str(), "rb");
	if (file == nullptr) {
		TK_ERROR("Can not open file : '" << _fileName);
		return nullptr;
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
		return nullptr;
	}
	fclose(file);
	file = nullptr;
	output = new etk::archive::Zip(_fileName, position);
	if (nullptr==output) {
		TK_ERROR("An error occured when load archive : " << _fileName);
	}
	return output;
}


void etk::Archive::open(const etk::String& _key) {
	std::unique_lock<std::mutex> lock(m_mutex);
	auto it = m_content.find(_key);
	if (it == m_content.end()) {
		TK_ERROR("Try open an unexistant file : '" << _key << "'");
		return;
	}
	if (it->getValue().getNumberOfRef()==-1) {
		loadFile(it);
		it->getValue().increaseRef();
	}
	it->getValue().increaseRef();
}

void etk::Archive::close(const etk::String& _key) {
	std::unique_lock<std::mutex> lock(m_mutex);
	auto it = m_content.find(_key);
	if (it == m_content.end()) {
		TK_ERROR("Try close an unexistant file : '" << _key << "'");
		return;
	}
	if (it->getValue().getNumberOfRef()==0){
		TK_ERROR("Try close one more time the file : '" << _key << "'");
	} else {
		it->getValue().decreaseRef();
	}
}

#endif