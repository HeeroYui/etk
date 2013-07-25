/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/archive/Archive.h>
#include <etk/archive/Zip.h>
#include <etk/DebugInternal.h>

const etk::Archive::Content& etk::Archive::GetContent(const etk::UString& _key) const
{
	static const etk::Archive::Content g_error;
	if (m_content.Exist(_key)==false) {
		TK_ERROR("File does not exist : " << _key);
		return g_error;
	}
	return m_content[_key];
}

void etk::Archive::Display(void)
{
	for (esize_t iii=0; iii<m_content.Size(); iii++) {
		esize_t size = m_content.GetValue(iii).GetTheoricSize();
		esize_t sizeR = m_content.GetValue(iii).Size();
		TK_INFO(" element : " << m_content.GetKey(iii) << " size=" << size << " allocated=" << sizeR);
	}
}

etk::Archive* etk::Archive::Load(const etk::UString& _fileName)
{
	etk::Archive::Archive* output=NULL;
	etk::UString tmpName = _fileName.ToLower();
	// select the corect Loader :
	if(    true == tmpName.EndWith(".zip") 
	    || true == tmpName.EndWith(".apk")  ) {
		output = new etk::archive::Zip(_fileName);
		if (NULL==output) {
			TK_ERROR("An error occured when load archive : " << _fileName);
		}
	} else {
		TK_ERROR("Extention not managed " << _fileName << " Sopported extention : .zip");
	}
	return output;
}


void etk::Archive::Open(const etk::UString& _key)
{
	if (m_content.Exist(_key)==false) {
		TK_ERROR("Try open an unexistant file : '" << _key << "'");
		return;
	}
	if (m_content[_key].GetNumberOfRef()==-1) {
		LoadFile(m_content.GetId(_key));
		m_content[_key].IncreaseRef();
	}
	m_content[_key].IncreaseRef();
}

void etk::Archive::Close(const etk::UString& _key)
{
	if (m_content.Exist(_key)==false) {
		TK_ERROR("Try close an unexistant file : '" << _key << "'");
		return;
	}
	if (m_content[_key].GetNumberOfRef()==0){
		TK_ERROR("Try close one more time the file : '" << _key << "'");
	} else {
		m_content[_key].DecreaseRef();
	}
}
