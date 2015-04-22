/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#ifdef ETK_BUILD_MINIZIP

#include <etk/archive/Archive.h>
#include <etk/archive/Zip.h>
#include <etk/debug.h>

static const etk::ArchiveContent g_error;


const std::string& etk::Archive::getName(size_t _id) const {
	size_t id = 0;
	for (auto &it : m_content) {
		if (id == _id) {
			return it.first;
		}
		++id;
	}
	static const std::string error("");
	return error;
}

const etk::ArchiveContent& etk::Archive::getContent(size_t _id) const {
	size_t id = 0;
	for (auto &it : m_content) {
		if (id == _id) {
			return it.second;
		}
		++id;
	}
	return g_error;
}

const etk::ArchiveContent& etk::Archive::getContent(const std::string& _key) const {
	auto it = m_content.find(_key);
	if (it == m_content.end()) {
		return g_error;
	}
	return it->second;
}


bool etk::Archive::exist(const std::string& _key) const {
	return m_content.find(_key) != m_content.end();
}

void etk::Archive::display()
{
	for (auto &it : m_content) {
		int32_t size = it.second.getTheoricSize();
		int32_t sizeR = it.second.size();
		TK_INFO(" element : " << it.first << " size=" << size << " allocated=" << sizeR);
	}
}

etk::Archive* etk::Archive::load(const std::string& _fileName) {
	etk::Archive* output=nullptr;
	std::string tmpName = etk::tolower(_fileName);
	// select the corect Loader :
	if(    true == end_with(tmpName, ".zip") 
	    || true == end_with(tmpName, ".apk")  ) {
		output = new etk::archive::Zip(_fileName);
		if (nullptr==output) {
			TK_ERROR("An error occured when load archive : " << _fileName);
		}
	} else {
		TK_ERROR("Extention not managed " << _fileName << " Sopported extention : .zip");
	}
	return output;
}

etk::Archive* etk::Archive::loadPackage(const std::string& _fileName) {
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
	if (std::string(plop) != "***START DATA***") {
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


void etk::Archive::open(const std::string& _key) {
	auto it = m_content.find(_key);
	if (it == m_content.end()) {
		TK_ERROR("Try open an unexistant file : '" << _key << "'");
		return;
	}
	if (it->second.getNumberOfRef()==-1) {
		loadFile(it);
		it->second.increaseRef();
	}
	it->second.increaseRef();
}

void etk::Archive::close(const std::string& _key) {
	auto it = m_content.find(_key);
	if (it == m_content.end()) {
		TK_ERROR("Try close an unexistant file : '" << _key << "'");
		return;
	}
	if (it->second.getNumberOfRef()==0){
		TK_ERROR("Try close one more time the file : '" << _key << "'");
	} else {
		it->second.decreaseRef();
	}
}

#endif