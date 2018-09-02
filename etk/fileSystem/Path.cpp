/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#include <etk/fileSystem/Path.hpp>
#include <etk/log.hpp>

#include <etk/typeInfo.hpp>
ETK_DECLARE_TYPE(etk::Path);

//#define TK_DBG_MODE TK_VERBOSE
#define TK_DBG_MODE TK_WARNING

static etk::Pair<etk::fileSystem::Type, etk::String> parsePath(etk::String _path) {
	// Reset ALL DATA :
	m_data = "";
	m_type = etk::fileSystem::Type::Unknow;
	TK_DBG_MODE("1 : Set Name :              \"" << _path << "\"");
	#ifdef __TARGET_OS__Windows
		_path.replace("\\", "/");
		for (char iii='a' ; iii<='z' ; iii++) {
			char tmpVal[10];
			char tmpDest[10];
			sprintf(tmpVal, "%c:/", iii);
			sprintf(tmpDest, "/%c/", iii);
			if(etk::start_with(_path, tmpVal) == true) {
				_path.replace(tmpVal, tmpDest);
				break;
			}
		}
		for (char iii='A' ; iii<='Z' ; iii++) {
			char tmpVal[10];
			char tmpDest[10];
			sprintf(tmpVal, "%c:/", iii);
			sprintf(tmpDest, "/%c/", iii+'a'-'A');
			if(etk::start_with(_path, tmpVal) == true) {
				_path.replace(tmpVal, tmpDest);
				break;
			}
		}
	#endif
	// generate destination name in case of the input error
	if (_path.size() == 0) {
		// if no name ==> go to the root Folder
		_path = "ROOT:";
	}
	if (_path[0] == '/') {
		TK_DBG_MODE("    ==> detect root");
		_path.erase(0, 1);
		m_type = etk::fileSystem::Type::Direct;
	} else if (start_with(_path, "ROOT:", false) == true) {
		TK_DBG_MODE("    ==> detect root 2 ");
		_path.erase(0, 5);
		m_type = etk::fileSystem::Type::Direct;
		if(start_with(_path, "~") == true) {
			_path.erase(0, 1);
			m_type = etk::fileSystem::Type::Home;
		}
	} else if (start_with(_path, "DIRECT:", false) == true) {
		TK_DBG_MODE("    ==> detect direct");
		_path.erase(0, 7);
		m_type = etk::fileSystem::Type::Direct;
		if(start_with(_path, "~") == true) {
			_path.erase(0, 1);
			m_type = etk::fileSystem::Type::Home;
		}
	} else if (start_with(_path, "DATA:", false) == true) {
		TK_DBG_MODE("    ==> detect data");
		_path.erase(0, 5);
		m_type = etk::fileSystem::Type::Data;
	} else if (start_with(_path, "USERDATA:", false) == true) {
		TK_DBG_MODE("    ==> detect User-data");
		_path.erase(0, 9);
		m_type = etk::fileSystem::Type::UserData;
	} else if (start_with(_path, "CACHE:", false) == true) {
		TK_DBG_MODE("    ==> detect Cache");
		_path.erase(0, 6);
		m_type = etk::fileSystem::Type::Cache;
	} else if (start_with(_path, "THEME:", false) == true) {
		TK_DBG_MODE("    ==> detect theme");
		_path.erase(0, 6);
		m_type = etk::fileSystem::Type::Theme;
	} else if (start_with(_path, "./") == true) {
		TK_DBG_MODE("    ==> detect relatif 1");
		_path.erase(0, 2);
		while (_path.size()>0 && _path[0] == '/') {
			_path.erase(0, 1);
		}
		m_type = etk::FSNType_relatif;
	} else if (start_with(_path, "REL:", false) == true) {
		TK_DBG_MODE("    ==> detect relatif 2");
		_path.erase(0, 4);
		while (_path.size()>0 && _path[0] == '/') {
			_path.erase(0, 1);
		}
		m_type = etk::FSNType_relatif;
	} else if (start_with(_path, baseRunPath) == true) {
		TK_DBG_MODE("    ==> detect relatif 3 (run path=" << baseRunPath << ")");
		_path.erase(0, baseRunPath.size());
		while (_path.size()>0 && _path[0] == '/') {
			_path.erase(0, 1);
		}
		m_type = etk::FSNType_relatif;
	} else if ((    baseRunPath != baseRunPathInHome
	             && (    start_with(_path, "~" + baseRunPathInHome) == true
	                  || start_with(_path, "HOME:" + baseRunPathInHome, false) == true ) ) ) {
		TK_DBG_MODE("    ==> detect relatif 4");
		if (start_with(_path, "~" + baseRunPathInHome) == true) {
			_path.erase(0, 1);
		} else {
			_path.erase(0, 5);
		}
		_path.erase(0, baseRunPathInHome.size());
		while (_path.size()>0 && _path[0] == '/') {
			_path.erase(0, 1);
		}
		m_type = etk::FSNType_relatif;
	} else if (start_with(_path, "~")) {
		TK_DBG_MODE("    ==> detect home 2");
		_path.erase(0, 1);
		m_type = etk::fileSystem::Type::Home;
	} else if (start_with(_path, "HOME:", false) == true ) {
		TK_DBG_MODE("    ==> detect home 3");
		_path.erase(0, 5);
		m_type = etk::fileSystem::Type::Home;
		if(start_with(_path, "~") == true) {
			_path.erase(0, 1);
		}
	} else if (start_with(_path, baseFolderHome) == true) {
		TK_DBG_MODE("    ==> detect home");
		_path.erase(0, baseFolderHome.size());
		m_type = etk::fileSystem::Type::Home;
	} else {
		TK_DBG_MODE("    ==> detect other");
		// nothing to remove
		//Other type is Relative : 
		m_type = etk::FSNType_relatif;
	}
	m_data = _path;
	TK_DBG_MODE("3 : parse done :            [" << m_type << "]->\"" << m_data << "\"");
	
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

etk::Path::Path(fileSystem::Type _type, const etk::String& _value) {
	
}

etk::String etk::Path::getString() const {
	
}

etk::String etk::Path::getRelative() const {
	
}

etk::String etk::Path::getDecorated() const {
	
}

etk::String etk::Path::getNative() const {
	
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

