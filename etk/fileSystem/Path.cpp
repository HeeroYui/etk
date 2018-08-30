/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#include <etk/fileSystem/Path.hpp>


static etk::Pair<etk::fileSystem::Type, etk::String> parsePath(etk::String _path) {
	m_libSearch = "";
	if (    _path.size() > 0
	     && _path[0] == '{') {
		// special case: Reference of searching in subLib folder ==> library use-case
		size_t firstPos = _path.find('}');
		if (firstPos != etk::String::npos) {
			// we find a theme name : We extracted it :
			m_libSearch = etk::String(_path, 1, firstPos-1);
			_path = etk::String(_path, firstPos+1);
		} else {
			TK_ERROR("start a path name with '{' without '}' : " << _path);
			// remove in case the {
			_path = etk::String(_path, 1);
		}
	}
	
	#ifdef HAVE_ZIP_DATA
		m_zipContent = null;
		m_zipReadingOffset = 0;
	#endif
	// Reset ALL DATA :
	m_userFileName = "";
	m_type = etk::FSNType_unknow;
	TK_DBG_MODE("1 : Set Name :              \"" << _path << "\"");
	
	// generate destination name in case of the input error
	etk::String destFilename;
	if (_path.size() == 0) {
		// if no name ==> go to the root Folder
		destFilename = "ROOT:";
	} else {
		destFilename = _path;
	}
	
	bool isRootFolder = false;
	#ifdef __TARGET_OS__Windows
		for (char iii='a' ; iii<='z' ; iii++) {
			char tmpVal[10];
			char tmpValMaj[10];
			sprintf(tmpVal, "%c:/", iii);
			sprintf(tmpValMaj, "%c:/", iii+'A'-'a');
			if(    etk::start_with(destFilename, tmpVal) == true
			    || etk::start_with(destFilename, tmpValMaj) == true) {
				isRootFolder = true;
				break;
			}
		}
	#else
		isRootFolder = destFilename[0] == '/';
	#endif
	if(    start_with(destFilename, "ROOT:") == true
	    || start_with(destFilename, "root:") == true ) {
		TK_DBG_MODE("    ==> detect root 2 ");
		destFilename.erase(0, 5);
		m_type = etk::FSNType_direct;
		if(start_with(destFilename, "~") == true) {
			destFilename.erase(0, 1);
			m_type = etk::FSNType_home;
		}
	} else if(    start_with(destFilename, "DIRECT:") == true
	           || start_with(destFilename, "direct:") == true ) {
		TK_DBG_MODE("    ==> detect direct");
		destFilename.erase(0, 7);
		m_type = etk::FSNType_direct;
		if(start_with(destFilename, "~") == true) {
			destFilename.erase(0, 1);
			m_type = etk::FSNType_home;
		}
	} else if(    start_with(destFilename, "DATA:") == true
	           || start_with(destFilename, "data:") == true ) {
		TK_DBG_MODE("    ==> detect data");
		destFilename.erase(0, 5);
		m_type = etk::FSNType_data;
	} else if(    start_with(destFilename, "USERDATA:") == true
	           || start_with(destFilename, "userdata:") == true ) {
		TK_DBG_MODE("    ==> detect User-data");
		destFilename.erase(0, 9);
		m_type = etk::FSNType_userData;
	} else if(    start_with(destFilename, "CACHE:") == true
	           || start_with(destFilename, "cache:") == true ) {
		TK_DBG_MODE("    ==> detect Cache");
		destFilename.erase(0, 6);
		m_type = etk::FSNType_cache;
	} else if(    start_with(destFilename, "THEME:") == true
	           || start_with(destFilename, "theme:") == true ) {
		TK_DBG_MODE("    ==> detect theme");
		destFilename.erase(0, 6);
		m_type = etk::FSNType_theme;
	} else if(start_with(destFilename, "./") == true) {
		TK_DBG_MODE("    ==> detect relatif 1");
		destFilename.erase(0, 2);
		while (destFilename.size()>0 && destFilename[0] == '/') {
			destFilename.erase(0, 1);
		}
		m_type = etk::FSNType_relatif;
	} else if(    start_with(destFilename, "REL:") == true
	           || start_with(destFilename, "rel:") == true ) {
		TK_DBG_MODE("    ==> detect relatif 2");
		destFilename.erase(0, 4);
		while (destFilename.size()>0 && destFilename[0] == '/') {
			destFilename.erase(0, 1);
		}
		m_type = etk::FSNType_relatif;
	} else if(start_with(destFilename, baseRunPath) == true) {
		TK_DBG_MODE("    ==> detect relatif 3 (run path=" << baseRunPath << ")");
		destFilename.erase(0, baseRunPath.size());
		while (destFilename.size()>0 && destFilename[0] == '/') {
			destFilename.erase(0, 1);
		}
		m_type = etk::FSNType_relatif;
	} else if ((    baseRunPath != baseRunPathInHome
	             && (    start_with(destFilename, "~" + baseRunPathInHome) == true
	                  || start_with(destFilename, "HOME:" + baseRunPathInHome) == true
	                  || start_with(destFilename, "home:" + baseRunPathInHome) == true ) ) ) {
		TK_DBG_MODE("    ==> detect relatif 4");
		if (start_with(destFilename, "~" + baseRunPathInHome) == true) {
			destFilename.erase(0, 1);
		} else {
			destFilename.erase(0, 5);
		}
		destFilename.erase(0, baseRunPathInHome.size());
		while (destFilename.size()>0 && destFilename[0] == '/') {
			destFilename.erase(0, 1);
		}
		m_type = etk::FSNType_relatif;
	} else if(start_with(destFilename, "~")) {
		TK_DBG_MODE("    ==> detect home 2");
		destFilename.erase(0, 1);
		m_type = etk::FSNType_home;
	} else if(    start_with(destFilename, "HOME:") == true
	           || start_with(destFilename, "home:") == true ) {
		TK_DBG_MODE("    ==> detect home 3");
		destFilename.erase(0, 5);
		m_type = etk::FSNType_home;
		if(start_with(destFilename, "~") == true) {
			destFilename.erase(0, 1);
		}
	} else if (start_with(destFilename, baseFolderHome) == true) {
		TK_DBG_MODE("    ==> detect home");
		destFilename.erase(0, baseFolderHome.size());
		m_type = etk::FSNType_home;
	} else if(isRootFolder == true) {
		TK_DBG_MODE("    ==> detect root");
		#ifdef __TARGET_OS__Windows
			destFilename.erase(0, 3);
		#else
			destFilename.erase(0, 1);
		#endif
		m_type = etk::FSNType_direct;
	} else {
		TK_DBG_MODE("    ==> detect other");
		// nothing to remove
		//Other type is Relative : 
		m_type = etk::FSNType_relatif;
	}
	m_userFileName = destFilename;
	TK_DBG_MODE("3 : parse done :            [" << m_type << "]->\"" << m_userFileName << "\"");
	
	// Now we reduce the path with all un-needed ../ and other thinks ...
	// TODO : Do it whith link and the other sub thinks ...
	m_userFileName = simplifyPath(m_userFileName);
	TK_DBG_MODE("4 : Path simplification :   [" << m_type << "]->\"" << m_userFileName << "\"");
	
	// Now we generate the real FS path:
	generateFileSystemPath();
	TK_DBG_MODE("5 : file System Real name : \"" << m_systemFileName << "\"");
	
	// now we get all the right if the file existed:
	updateFileSystemProperty();
	TK_DBG_MODE("6 : type :                  [" << m_typeNode << "]  right :" << m_rights);
}



etk::Path::Path(const etk::String& _value) {
	m_type = 
	m_data = 
}

bool etk::Path::operator== (const etk::Path &_obj) const {
	return    m_type == _obj.m_type
	       && m_data == _obj.m_data;
}

bool etk::Path::operator!= (const etk::Path &_obj) const {
	return    m_type != _obj.m_type
	       || m_data != _obj.m_data;
}

etk::Path etk::Path::operator/ (const etk::String & _element) const {
	etk::Path tmp = *this;
	tmp /= _element;
	return tmp;
}

etk::Path& etk::Path::operator/= (const etk::String & _element) {
	if (_element.size() == 0) {
		return *this;
	}
	m_data += "/" + _element;
	return *this;
}

etk::Path etk::Path::operator+ (const etk::String & _element) const {
	etk::Path tmp = *this;
	tmp += _element;
	return tmp;
}

etk::Path& etk::Path::operator+= (const etk::String & _element) {
	if (_element.size() == 0) {
		return *this;
	}
	m_data += _element;
	return *this;
}

