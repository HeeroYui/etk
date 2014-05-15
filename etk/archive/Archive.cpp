/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/archive/Archive.h>
#include <etk/archive/Zip.h>
#include <etk/debug.h>

static const etk::Archive::Content g_error;


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

const etk::Archive::Content& etk::Archive::getContent(size_t _id) const {
	size_t id = 0;
	for (auto &it : m_content) {
		if (id == _id) {
			return it.second;
		}
		++id;
	}
	return g_error;
}

const etk::Archive::Content& etk::Archive::getContent(const std::string& _key) const {
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
	etk::Archive* output=NULL;
	std::string tmpName = std::tolower(_fileName);
	// select the corect Loader :
	if(    true == end_with(tmpName, ".zip") 
	    || true == end_with(tmpName, ".apk")  ) {
		output = new etk::archive::Zip(_fileName);
		if (NULL==output) {
			TK_ERROR("An error occured when load archive : " << _fileName);
		}
	} else {
		TK_ERROR("Extention not managed " << _fileName << " Sopported extention : .zip");
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
