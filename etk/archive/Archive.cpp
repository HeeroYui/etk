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

const etk::Archive::Content& etk::Archive::getContent(const std::string& _key) const {
	static const etk::Archive::Content g_error;
	if (m_content.exist(_key)==false) {
		TK_ERROR("File does not exist : " << _key);
		return g_error;
	}
	return m_content[_key];
}

void etk::Archive::display(void)
{
	for (int32_t iii=0; iii<m_content.size(); iii++) {
		int32_t size = m_content.getValue(iii).getTheoricSize();
		int32_t sizeR = m_content.getValue(iii).size();
		TK_INFO(" element : " << m_content.getKey(iii) << " size=" << size << " allocated=" << sizeR);
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
	if (m_content.exist(_key)==false) {
		TK_ERROR("Try open an unexistant file : '" << _key << "'");
		return;
	}
	if (m_content[_key].getNumberOfRef()==-1) {
		loadFile(m_content.getId(_key));
		m_content[_key].increaseRef();
	}
	m_content[_key].increaseRef();
}

void etk::Archive::close(const std::string& _key) {
	if (m_content.exist(_key)==false) {
		TK_ERROR("Try close an unexistant file : '" << _key << "'");
		return;
	}
	if (m_content[_key].getNumberOfRef()==0){
		TK_ERROR("Try close one more time the file : '" << _key << "'");
	} else {
		m_content[_key].decreaseRef();
	}
}
