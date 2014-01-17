/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */


#include <etk/types.h>
#include <etk/os/FSNode.h>
#include <unistd.h>
#include <stdlib.h>
#include <etk/tool.h>
#include <etk/Hash.h>
#ifdef __TARGET_OS__Windows
	#include "windows.h"
#endif
extern "C" {
	// file browsing ...
	#include <dirent.h>
	#include <sys/stat.h>
	#include <errno.h>
}


#ifdef __TARGET_OS__Windows
	// For ctime 
	#include <time.h>
#endif


#define TK_DBG_MODE TK_VERBOSE
//#define TK_DBG_MODE TK_DEBUG



std::string etk::simplifyPath(std::string _input) {
	// step 1 : for windows change \ in /:
	TK_DBG_MODE("Siplify(1) : \"" << _input << "\"");
	size_t currentPos = 0;
	if (_input.size() == 0) {
		return _input;
	}
	while(currentPos < _input.size()) {
		if (_input[currentPos] == '\\') {
			_input[currentPos] = '/';
		}
		currentPos++;
		continue;
	}
	// step 2 : remove all '//'
	TK_DBG_MODE("Siplify(2) : \"" << _input << "\"");
	currentPos = 0;
	if (_input.size() <= 1) {
		return _input;
	}
	while(currentPos < _input.size()-1) {
		if (    _input[currentPos] != '/'
		     || _input[currentPos+1] != '/') {
			currentPos++;
			continue;
		}
		_input.erase(currentPos, 1);
	}
	// step 3 : remove all '/./'
	TK_DBG_MODE("Siplify(3) : \"" << _input << "\"");
	currentPos = 0;
	if (_input.size() <= 1) {
		return _input;
	}
	while(currentPos < _input.size()-2) {
		if (    _input[currentPos] != '/'
		     || _input[currentPos+1] != '.'
		     || _input[currentPos+2] != '/') {
			currentPos++;
			continue;
		}
		_input.erase(currentPos, 2);
	}
	// step 4 remove xxx/..
	TK_DBG_MODE("Siplify(4) : \"" << _input << "\"");
	size_t lastSlashPos = std::string::npos;
	currentPos = 0;
	if (_input.size() <= 2) {
		return _input;
	}
	while(currentPos < _input.size()-2) {
		if (    _input[currentPos] != '/'
		     || _input[currentPos+1] != '.'
		     || _input[currentPos+2] != '.') {
			if (_input[currentPos] == '/') {
				lastSlashPos = currentPos;
			}
			currentPos++;
			continue;
		}
		if (lastSlashPos == std::string::npos) {
			currentPos++;
			continue;
		}
		_input.erase(lastSlashPos, currentPos+2-lastSlashPos+1);
		TK_DEBUG("update : \"" << _input << "\"");
		lastSlashPos = std::string::npos;
		currentPos = 0;
	}
	TK_DBG_MODE("Siplify(5) : \"" << _input << "\"");
	return _input;
}



// zip file of the apk file for Android ==> set to zip file apk access
static std::string s_fileAPK = "";
static std::string baseApplName = "ewolNoName";
static std::string baseRunPath = "/";
#if defined(__TARGET_OS__Android)
	static std::string baseFolderHome     = "/sdcard/";                 // home folder
	static std::string baseFolderData     = "assets/";                  // program Data
	static std::string baseFolderDataUser = "/sdcard/.tmp/userData/";   // Data specific user (local modification)
	static std::string baseFolderCache    = "/sdcard/.tmp/cache/";      // Temporary data (can be removed the next time)
#elif defined(__TARGET_OS__Windows)
	static std::string baseFolderHome     = "c:/test";                  // home folder
	static std::string baseFolderData     = "c:/test/share/";           // program Data
	static std::string baseFolderDataUser = "c:/test/userData/";        // Data specific user (local modification)
	static std::string baseFolderCache    = "c:/Windows/Temp/ewol/";    // Temporary data (can be removed the next time)
#else
	static std::string baseFolderHome     = "~";                  // home folder
	static std::string baseFolderData     = "share/";             // program Data
	static std::string baseFolderDataUser = "~/.tmp/userData/";   // Data specific user (local modification)
	static std::string baseFolderCache    = "~/.tmp/cache/";      // Temporary data (can be removed the next time)
#endif


#ifdef __TARGET_OS__Android
	static etk::Archive* s_APKArchive = NULL;
	static void loadAPK(std::string& _apkPath)
	{
		TK_DEBUG("Loading APK \"" << _apkPath << "\"");
		s_APKArchive = etk::Archive::load(_apkPath);
		TK_ASSERT(s_APKArchive != NULL, "Error loading APK ...  \"" << _apkPath << "\"");
		//Just for debug, print APK contents
		s_APKArchive->display();
	}
#endif

// for specific device contraint : 
void etk::setBaseFolderData(const char* _folder)
{
	#ifdef __TARGET_OS__Android
		baseFolderData = "assets/";
		s_fileAPK = _folder;
		loadAPK(s_fileAPK);
	#else
		TK_WARNING("Not Availlable Outside Android");
	#endif
}

void etk::setBaseFolderDataUser(const char* _folder)
{
	#ifdef __TARGET_OS__Android
		baseFolderDataUser = _folder;
	#else
		TK_WARNING("Not Availlable Outside Android");
	#endif
}

void etk::setBaseFolderCache(const char* _folder)
{
	#ifdef __TARGET_OS__Android
		baseFolderCache = _folder;
	#else
		TK_WARNING("Not Availlable Outside Android");
	#endif
}

std::string l_argZero = "";
void etk::setArgZero(const std::string& _val) {
	l_argZero = _val;
}
/*
	On Unixes with /proc really straight and realiable way is to:
		readlink("/proc/self/exe", buf, bufsize) (Linux)
		readlink("/proc/curproc/file", buf, bufsize) (FreeBSD)
		readlink("/proc/self/path/a.out", buf, bufsize) (Solaris)
	On Unixes without /proc (i.e. if above fails):
		If argv[0] starts with "/" (absolute path) this is the path.
		Otherwise if argv[0] contains "/" (relative path) append it to cwd (assuming it hasn't been changed yet).
		Otherwise search directories in $PATH for executable argv[0].
	Afterwards it may be reasonable to check whether the executable isn't actually a symlink. If it is resolve it relative to the symlink directory.
	This step is not necessary in /proc method (at least for Linux). There the proc symlink points directly to executable.
	Note that it is up to the calling process to set argv[0] correctly. It is right most of the times however there are occasions when the calling process cannot be trusted (ex. setuid executable).
	On Windows: use GetModuleFileName(NULL, buf, bufsize)
*/
std::string getApplicationPath(void) {
	std::string binaryName = "no-name";
	char binaryCompleatePath[FILENAME_MAX];
	memset(binaryCompleatePath, 0, FILENAME_MAX);
	#ifdef __TARGET_OS__Windows
		getModuleFileName(NULL, binaryCompleatePath, FILENAME_MAX);
		if (0==strlen(binaryCompleatePath)) {
			TK_CRITICAL("Can not get the binary position in the tree ==> this is really bad ...");
		} else {
			binaryName = binaryCompleatePath;
		}
	#else
		// check it to prevent test mode in local folder ...
		// Generic Linux system
		readlink("/proc/self/exe", binaryCompleatePath, FILENAME_MAX);
		if(strlen(binaryCompleatePath) != 0) {
			binaryName = binaryCompleatePath;
			return binaryName;
		}
		// generic FreeBSD system
		memset(binaryCompleatePath, 0, FILENAME_MAX);
		readlink("/proc/curproc/file", binaryCompleatePath, FILENAME_MAX);
		if(strlen(binaryCompleatePath) != 0) {
			binaryName = binaryCompleatePath;
			return binaryName;
		}
		// generic Solaris system 
		memset(binaryCompleatePath, 0, FILENAME_MAX);
		readlink("/proc/self/path/a.out", binaryCompleatePath, FILENAME_MAX);
		if(strlen(binaryCompleatePath) != 0) {
			binaryName = binaryCompleatePath;
			return binaryName;
		}
		// now we are in a really bad case ...
		if (l_argZero.size() == 0) {
			TK_CRITICAL("Can not get the binary position in the tree ==> this is really bad ... arg 0 is as bad as other ...");
			return binaryName;
		}
		TK_VERBOSE("Parse arg0 = '" << l_argZero << "' start with '/' ???");
		if (l_argZero[0] == '/') {
			binaryName = l_argZero;
			return etk::simplifyPath(binaryName);
		}
		TK_VERBOSE("Parse arg0 = '" << l_argZero << "' try add PWD");
		char * basicPathPWD = getenv("PWD");
		if (NULL != basicPathPWD) {
			std::string testCompleatePath = basicPathPWD;
			testCompleatePath += "/";
			testCompleatePath += l_argZero;
			// check if the element existed : 
			TK_VERBOSE("test path: '" << testCompleatePath << "'");
			memset(binaryCompleatePath, 0, FILENAME_MAX);
			struct stat statProperty;
			if (-1 != stat(testCompleatePath.c_str(), &statProperty)) {
				//Normal case when the file does not exist ... ==> the it was in unknow mode ...
				binaryName = testCompleatePath;
				TK_VERBOSE("find real name = '" << binaryName << "'");
				return etk::simplifyPath(binaryName);
			}
		}
		//char * basicPathPATH = getenv("PATH");
		//if (NULL != basicPathPWD) {
			// TODO : bad case ...
		//}
		// and now we will really in a bad mood ...
	#endif
	TK_INFO("Binary name : " << binaryName);
	return binaryName;
}
std::u32string getUApplicationPath(void) {
	return to_u32string(getApplicationPath());
}

void etk::initDefaultFolder(const char* _applName) {
	baseApplName = _applName;
	char cCurrentPath[FILENAME_MAX];
	
	char * basicPath = getenv("HOME");
	if (NULL == basicPath) {
		TK_WARNING("ERROR while trying to get the path of the home folder");
		#if defined(__TARGET_OS__Windows)
			baseFolderHome = "c:/";
		#elif defined(__TARGET_OS__Android)
			baseFolderHome = "/sdcard";
		#else
			baseFolderHome = "~";
		#endif
	} else {
		baseFolderHome = basicPath;
	}
	if (!getcwd(cCurrentPath, FILENAME_MAX)) {
		baseRunPath = ".";
	} else {
		cCurrentPath[FILENAME_MAX - 1] = '\0';
		if (cCurrentPath[0] == '/') {
			baseRunPath = cCurrentPath+1;
		} else {
			baseRunPath = cCurrentPath;
		}
	}
	TK_DBG_MODE("Find Basic running PATH : \"" << baseRunPath << "\"");
	
	#ifndef __TARGET_OS__Android
		std::string binaryPath = getApplicationPath();
		binaryPath = replace(binaryPath, '\\', '/');
		size_t pos = binaryPath.rfind('/');
		std::string binaryName(binaryPath, pos);
		binaryPath.erase(binaryPath.begin() + pos, binaryPath.end());
		TK_INFO("Bianry name : '" << binaryPath << "' && '" << binaryName << "'" );
		#ifdef __TARGET_OS__Windows
			baseFolderData  = binaryPath;
			baseFolderData += "/data/";
			
			baseFolderDataUser  = binaryPath;
			baseFolderDataUser += "/user/";
			
			baseFolderCache  = binaryPath;
			baseFolderCache += "/tmp/";
		#else
			// if element is installed :
			baseFolderData  = "/usr/share";
			baseFolderData += binaryName;
			baseFolderData += "/";
			
			std::string theoricInstalledName = "/usr/bin";
			theoricInstalledName += binaryName;
			TK_VERBOSE(" position : '" << binaryPath << "' installed position : '" << theoricInstalledName << "'");
			if (binaryPath != theoricInstalledName) {
				TK_INFO(" base path is not correct try to find it : (must only appear in test and not when installed) base name : '" << binaryPath << "'");
				// remove bin/applName
				baseFolderData = binaryPath;
				#ifdef __TARGET_OS__MacOs
					baseFolderData += "/../Resources/";
				#else
					baseFolderData += "/../share";
					baseFolderData += binaryName;
					baseFolderData += "/";
				#endif
				baseFolderData = simplifyPath(baseFolderData);
			}
			baseFolderDataUser  = baseFolderHome;
			baseFolderDataUser += "/.local/share/";
			baseFolderDataUser += binaryName;
			baseFolderDataUser += "/";
			
			baseFolderCache  = "/tmp/";
			baseFolderCache += binaryName;
			baseFolderCache += "/";
		#endif
	#endif
	TK_INFO("baseFolderHome     : '" << baseFolderHome << "'");
	TK_INFO("baseFolderData     : '" << baseFolderData << "'");
	TK_INFO("baseFolderDataUser : '" << baseFolderDataUser << "'");
	TK_INFO("baseFolderCache    : '" << baseFolderCache << "'");
}

std::string etk::getUserHomeFolder(void) {
	return baseFolderHome;
}
std::u32string etk::getUUserHomeFolder(void) {
	return to_u32string(baseFolderHome);
}

std::string etk::getUserRunFolder(void) {
	return baseRunPath;
}
std::u32string etk::getUUserRunFolder(void) {
	return to_u32string(baseRunPath);
}


#ifdef __TARGET_OS__Android
bool etk::FSNode::loadDataZip(void)
{
	if (NULL == s_APKArchive) {
		return false;
	}
	if (NULL != m_zipContent) {
		return true;
	}
	if (false == s_APKArchive->exist(m_systemFileName)) {
		return false;
	}
	m_zipContent = &s_APKArchive->getContent(m_systemFileName);
	if (NULL != m_zipContent) {
		return true;
	}
	return false;
}
#endif



static int32_t FSNODE_LOCAL_mkdir(const char* _path, mode_t _mode) {
	struct stat st;
	int32_t status = 0;
	if (stat(_path, &st) != 0) {
		/* Directory does not exist. EEXIST for race condition */
		#ifdef __TARGET_OS__Windows
		if(0!=mkdir(_path)
		#else
		if(0!=mkdir(_path, _mode)
		#endif
		    && errno != EEXIST) {
			status = -1;
		}
	} else if (!S_ISDIR(st.st_mode)) {
		errno = ENOTDIR;
		status = -1;
	}
	
	return(status);
}

static int32_t FSNODE_LOCAL_mkPath(const char* _path, mode_t _mode) {
	char *pp;
	char *sp;
	int status;
	char *copypath = strdup(_path);
	if (NULL==copypath) {
		return -1;
	}
	status = 0;
	pp = copypath;
	while (status == 0 && (sp = strchr(pp, '/')) != 0) {
		if (sp != pp) {
			/* Neither root nor double slash in path */
			*sp = '\0';
			status = FSNODE_LOCAL_mkdir(copypath, _mode);
			*sp = '/';
		}
		pp = sp + 1;
	}
	if (status == 0) {
		status = FSNODE_LOCAL_mkdir(_path, _mode);
	}
	free(copypath);
	return (status);
}





#undef __class__
#define __class__ "FSNode"

etk::FSNode::FSNode(const std::string& _nodeName) :
  m_userFileName(""),
  m_type(etk::FSN_TYPE_UNKNOW),
  m_typeNode(etk::FSN_UNKNOW),
  m_PointerFile(NULL),
  m_timeCreate(0),
  m_timeModify(0),
  m_timeAccess(0)
#ifdef __TARGET_OS__Android
    , m_zipContent(NULL),
    m_zipReadingOffset(-1)
#endif
{
	privateSetName(_nodeName);
}

etk::FSNode::FSNode(const std::u32string& _nodeName) :
  m_userFileName(""),
  m_type(etk::FSN_TYPE_UNKNOW),
  m_typeNode(etk::FSN_UNKNOW),
  m_PointerFile(NULL),
  m_timeCreate(0),
  m_timeModify(0),
  m_timeAccess(0)
#ifdef __TARGET_OS__Android
    , m_zipContent(NULL),
    m_zipReadingOffset(-1)
#endif
{
	privateSetName(_nodeName);
}


etk::FSNode::~FSNode(void) {
	if(    NULL != m_PointerFile
	#ifdef __TARGET_OS__Android
	    || NULL != m_zipContent
	#endif
	  ) {
		TK_ERROR("Missing to close the file : \"" << *this << "\"");
		fileClose();
	}
}


void etk::FSNode::sortElementList(std::vector<etk::FSNode *>& _list) {
	std::vector<etk::FSNode *> tmpList = _list;
	_list.clear();
	for(size_t iii=0; iii<tmpList.size(); iii++) {
		if (NULL != tmpList[iii]) {
			size_t findPos = 0;
			for(size_t jjj=0; jjj<_list.size(); jjj++) {
				//EWOL_DEBUG("compare : \""<<*tmpList[iii] << "\" and \"" << *m_listDirectory[jjj] << "\"");
				if (_list[jjj]!=NULL) {
					// TODO : Do something better : this methode is a litthe hard!!!
					if (std::toupper(tmpList[iii]->getNameFile()) > std::toupper(_list[jjj]->getNameFile())) {
						findPos = jjj+1;
					}
				}
			}
			//EWOL_DEBUG("position="<<findPos);
			_list.insert(_list.begin() + findPos, tmpList[iii]);
		}
	}
}

void etk::FSNode::privateSetName(const std::string& _newName) {
	if(    NULL != m_PointerFile
	#ifdef __TARGET_OS__Android
	    || NULL != m_zipContent
	#endif
	  ) {
		TK_ERROR("Missing to close the file : \"" << *this << "\"");
		fileClose();
	}
	// set right at NULL ...
	m_rights = 0;
	
	#ifdef __TARGET_OS__Android
		m_zipContent = NULL;
		m_zipReadingOffset = 0;
	#endif
	// Reset ALL DATA :
	m_userFileName = "";
	m_type = etk::FSN_TYPE_UNKNOW;
	TK_DBG_MODE("1 : Set Name :              \"" << _newName << "\"");
	
	// generate destination name in case of the input error
	std::string destFilename;
	if (_newName.size() == 0) {
		// if no name ==> go to the root Folder
		destFilename = "ROOT:";
	} else {
		destFilename = _newName;
	}
	
	bool isRootFolder = false;
	#ifdef __TARGET_OS__Windows
		for (char iii='a' ; iii<='z' ; iii++) {
			char tmpVal[10];
			char tmpValMaj[10];
			sprintf(tmpVal, "%c:/", iii);
			sprintf(tmpValMaj, "%c:/", iii+'A'-'a');
			if(    true == destFilename.startWith(tmpVal)
			    || true == destFilename.startWith(tmpValMaj)) {
				isRootFolder = true;
				break;
			}
		}
	#else
		isRootFolder = destFilename[0] == '/';
	#endif
	if (true == start_with(destFilename, baseFolderHome) ) {
		TK_DBG_MODE("    ==> detect home");
		destFilename.erase(0, baseFolderHome.size());
		m_type = etk::FSN_TYPE_HOME;
	} else if(true == isRootFolder) {
		TK_DBG_MODE("    ==> detect root");
		#ifdef __TARGET_OS__Windows
			destFilename.erase(0, 3);
		#else
			destFilename.erase(0, 1);
		#endif
		m_type = etk::FSN_TYPE_DIRECT;
	} else if(    true == start_with(destFilename, "ROOT:")
	           || true == start_with(destFilename, "root:") ) {
		TK_DBG_MODE("    ==> detect root 2 ");
		destFilename.erase(0, 5);
		m_type = etk::FSN_TYPE_DIRECT;
		if(true == start_with(destFilename, "~")) {
			destFilename.erase(0, 1);
			m_type = etk::FSN_TYPE_HOME;
		}
	} else if(    true == start_with(destFilename, "DIRECT:")
	           || true == start_with(destFilename, "direct:") ) {
		TK_DBG_MODE("    ==> detect direct");
		destFilename.erase(0, 7);
		m_type = etk::FSN_TYPE_DIRECT;
		if(true == start_with(destFilename, "~")) {
			destFilename.erase(0, 1);
			m_type = etk::FSN_TYPE_HOME;
		}
	} else if(    true == start_with(destFilename, "DATA:")
	           || true == start_with(destFilename, "data:") ) {
		TK_DBG_MODE("    ==> detect data");
		destFilename.erase(0, 5);
		m_type = etk::FSN_TYPE_DATA;
	} else if(    true == start_with(destFilename, "USERDATA:")
	           || true == start_with(destFilename, "userdata:") ) {
		TK_DBG_MODE("    ==> detect User-data");
		destFilename.erase(0, 9);
		m_type = etk::FSN_TYPE_USER_DATA;
	} else if(    true == start_with(destFilename, "CACHE:")
	           || true == start_with(destFilename, "cache:") ) {
		TK_DBG_MODE("    ==> detect Cach");
		destFilename.erase(0, 6);
		m_type = etk::FSN_TYPE_CACHE;
	} else if(    true == start_with(destFilename, "THEME:")
	           || true == start_with(destFilename, "theme:") ) {
		TK_DBG_MODE("    ==> detect theme");
		destFilename.erase(0, 6);
		m_type = etk::FSN_TYPE_THEME;
	} else if(true == start_with(destFilename, "~")) {
		TK_DBG_MODE("    ==> detect home 2");
		destFilename.erase(0, 1);
		m_type = etk::FSN_TYPE_HOME;
	} else if(    true == start_with(destFilename, "HOME:")
	           || true == start_with(destFilename, "home:") ) {
		TK_DBG_MODE("    ==> detect home 3");
		destFilename.erase(0, 5);
		m_type = etk::FSN_TYPE_HOME;
		if(true == start_with(destFilename, "~")) {
			destFilename.erase(0, 1);
		}
	} /*else if(true == destFilename.StartWith(baseRunPath)) {
		destFilename.Remove(0, baseRunPath.Size());
		m_type = etk::FSN_TYPE_RELATIF;
	} */else {
		TK_DBG_MODE("    ==> detect other");
		// nothing to remove
		//Other type is Relative : 
		m_type = etk::FSN_TYPE_RELATIF;
		
		// we force to have the correct name : (can generate many problem otherwise ...
		std::string tmpName = etk::getUserRunFolder() + "/" + destFilename;
		destFilename = tmpName;
		m_type = etk::FSN_TYPE_DIRECT;
		
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
void etk::FSNode::privateSetName(const std::u32string& _newName) {
	privateSetName(std::to_string(_newName));
}

bool directCheckFile(std::string _tmpFileNameDirect, bool _checkInAPKIfNeeded = false) {
	#ifdef __TARGET_OS__Android
	if (true == _checkInAPKIfNeeded) {
		if(    NULL != s_APKArchive
		    && true == s_APKArchive->exist(_tmpFileNameDirect) ) {
			return true;
		}
		return false;
	}
	#endif
	// tmpStat Buffer :
	struct stat statProperty;
	if (-1 == stat(_tmpFileNameDirect.c_str(), &statProperty)) {
		return false;
	}
	return true;
}
bool directCheckFile(std::u32string _tmpFileNameDirect, bool _checkInAPKIfNeeded = false) {
	return directCheckFile(std::to_string(_tmpFileNameDirect));
}
// Now we generate the real FS path:
void etk::FSNode::generateFileSystemPath(void) {
	switch (m_type) {
		default:
		case etk::FSN_TYPE_UNKNOW:
			m_systemFileName = baseFolderHome;
			break;
		case etk::FSN_TYPE_DIRECT:
			m_systemFileName = "/";
			break;
		case etk::FSN_TYPE_RELATIF: {
				// Get the command came from the running of the program : 
				char cCurrentPath[FILENAME_MAX];
				if (!getcwd(cCurrentPath, FILENAME_MAX)) {
					TK_WARNING("Can not get the curent path");
					cCurrentPath[0] = '/';
					cCurrentPath[1] = '\0';
				}
				cCurrentPath[FILENAME_MAX - 1] = '\0';
				m_systemFileName = cCurrentPath;
				m_systemFileName += "/";
			break;
		}
		case etk::FSN_TYPE_HOME:
			m_systemFileName = baseFolderHome;
			break;
		case etk::FSN_TYPE_DATA:
			m_systemFileName = baseFolderData;
			break;
		case etk::FSN_TYPE_USER_DATA:
			m_systemFileName = baseFolderDataUser;
			break;
		case etk::FSN_TYPE_CACHE:
			m_systemFileName = baseFolderCache;
			break;
		case etk::FSN_TYPE_THEME:
		case etk::FSN_TYPE_THEME_DATA:
			{
				//std::u32string myCompleateName=baseFolderData + "/theme/";
				std::string themeName("");
				std::string basicName(m_userFileName);
				size_t firstPos = m_userFileName.find(':');
				if (firstPos != std::string::npos) {
					// we find a theme name : We extracted it :
					themeName = std::string(m_userFileName, 0, firstPos);
					basicName = std::string(m_userFileName, firstPos+1);
				}
				TK_DBG_MODE(" THEME party : \"" << themeName << "\" => \"" << basicName << "\"");
				themeName = etk::theme::getName(themeName);
				std::string themeNameDefault = etk::theme::getNameDefault(themeName);
				TK_DBG_MODE("      ==> theme Folder \"" << themeName << "\"");
				// search the corect folder : 
				if (themeName == "") {
					TK_WARNING("no theme name detected : set it to '" << themeNameDefault << "'");
				} else if (themeName != themeNameDefault) {
					// Selected theme :
					// check in the user data :
					m_systemFileName = simplifyPath(baseFolderDataUser + "theme/" + themeName + "/" + basicName);
					if (directCheckFile(m_systemFileName) == true) {
						return;
					}
					// check in the Appl data :
					m_systemFileName = simplifyPath(baseFolderData + "theme/" + themeName + "/" + basicName);
					if (directCheckFile(m_systemFileName, true) == true) {
						m_type = etk::FSN_TYPE_THEME_DATA;
						return;
					}
				}
				// default theme :
				// check in the user data :
				m_systemFileName = simplifyPath(baseFolderDataUser + "theme/" + themeNameDefault + "/" + basicName);
				if (true==directCheckFile(m_systemFileName)) {
					return;
				}
				// check in the Appl data : In every case we return this one ...
				m_systemFileName = simplifyPath(baseFolderData + "theme/" + themeNameDefault + "/" + basicName);
				if (true==directCheckFile(m_systemFileName, true)) {
					m_type = etk::FSN_TYPE_THEME_DATA;
					return;
				}
				m_type = etk::FSN_TYPE_UNKNOW;
				return;
			}
			break;
	}
	m_systemFileName += m_userFileName;
}


// now we get all the right if the file existed:
void etk::FSNode::updateFileSystemProperty(void) {
	// clean general properties : 
	m_rights.clear();
	m_timeCreate = 0;
	m_timeModify = 0;
	m_timeAccess = 0;
	m_idOwner = 0;
	m_idGroup = 0;
	// File type is not knowns ...
	m_typeNode=FSN_UNKNOW;
	
	#ifdef __TARGET_OS__Android
	if(    m_type == etk::FSN_TYPE_DATA
	    || m_type == etk::FSN_TYPE_THEME_DATA) {
		// ----------------------------------------
		// = Check if it was a folder :           =
		// ----------------------------------------
		std::string folderName = "/";
		if (true == end_with(m_systemFileName, folderName)) {
			folderName = m_systemFileName;
		} else {
			folderName = m_systemFileName + "/";
		}
		// note : Zip does not support other think than file ...
		if (s_APKArchive == NULL) {
			TK_ERROR("NOT Find the File in APK : '" << m_systemFileName << "'");
			return;
		}
		if (s_APKArchive->exist(m_systemFileName) == true) {
			m_typeNode=FSN_FILE;
			m_rights.setUserReadable(true);
			TK_DBG_MODE("Find a File in APK : '" << m_systemFileName << "'");
			return;
		}
		// TODO : Set the time of the file (time program compilation)
		// TODO : Set the USER ID in the group and the user Id ...
		if (m_systemFileName[m_systemFileName.size()-1] == '/') {
			//Might be a folder ==> check if it existed in the start files ...
			for (int iii=0; iii<s_APKArchive->size(); iii++) {
				std::string filename = s_APKArchive->getName(iii);
				if (start_with(filename, m_systemFileName) == true) {
					m_typeNode=etk::FSN_FOLDER;
					m_rights.setUserReadable(true);
					m_rights.setUserRunable(true);
					TK_DBG_MODE("Find a Folder in APK : '" << m_systemFileName << "'");
					return;
				}
			}
		}
		TK_WARNING("File existed ??? in APK : '" << m_systemFileName << "'");
		return;
	}
	#endif
	// tmpStat Buffer :
	struct stat statProperty;
	if (-1 == stat(m_systemFileName.c_str(), &statProperty)) {
		//Normal case when the file does not exist ... ==> the it was in unknow mode ...
		return;
	}
	
	switch (statProperty.st_mode & S_IFMT) {
		case S_IFBLK:  m_typeNode=etk::FSN_BLOCK;     break;
		case S_IFCHR:  m_typeNode=etk::FSN_CHARACTER; break;
		case S_IFDIR:  m_typeNode=etk::FSN_FOLDER;    break;
		case S_IFIFO:  m_typeNode=etk::FSN_FIFO;      break;
		#ifndef __TARGET_OS__Windows
		case S_IFLNK:  m_typeNode=etk::FSN_LINK;      break;
		#endif
		case S_IFREG:  m_typeNode=etk::FSN_FILE;      break;
		#ifndef __TARGET_OS__Windows
		case S_IFSOCK: m_typeNode=etk::FSN_SOCKET;    break;
		#endif
		default:       m_typeNode=etk::FSN_UNKNOW;    break;
	}
	// Right
	m_rights = statProperty.st_mode;
	m_idOwner = (int32_t) statProperty.st_uid;
	m_idGroup = (int32_t) statProperty.st_gid;
	m_timeCreate = statProperty.st_ctime;
	m_timeModify = statProperty.st_mtime;
	m_timeAccess = statProperty.st_atime;
	
	return;
}

bool etk::FSNode::setRight(etk::FSNodeRight _newRight) {
	// TODO : ...
	TK_ERROR("Can not set the new rights ...");
	return false;
}

void etk::FSNode::setName(const std::string& _newName) {
	privateSetName(_newName);
}
void etk::FSNode::setName(const std::u32string& _newName) {
	privateSetName(_newName);
}

std::string etk::FSNode::getNameFolder(void) const {
	size_t lastPos = m_systemFileName.rfind('/');
	if (lastPos != std::string::npos) {
		return std::string(m_systemFileName, 0, lastPos);
	}
	return "";
}
std::u32string etk::FSNode::getUNameFolder(void) const {
	return to_u32string(getNameFolder());
}

std::string etk::FSNode::getFileSystemName(void) const {
	return m_systemFileName;
}
std::u32string etk::FSNode::getUFileSystemName(void) const {
	return to_u32string(getFileSystemName());
}

std::string etk::FSNode::getName(void) const {
	std::string output;
	switch (m_type) {
		default:
		case etk::FSN_TYPE_UNKNOW:
			output = "HOME:";
			break;
		case etk::FSN_TYPE_DIRECT:
			output = "/";
			break;
		case etk::FSN_TYPE_RELATIF:
			output = "";
			break;
		case etk::FSN_TYPE_HOME:
			output = "~";
			break;
		case etk::FSN_TYPE_DATA:
			output = "DATA:";
			break;
		case etk::FSN_TYPE_USER_DATA:
			output = "USERDATA:";
			break;
		case etk::FSN_TYPE_CACHE:
			output = "CACHE:";
			break;
		case etk::FSN_TYPE_THEME:
		case etk::FSN_TYPE_THEME_DATA:
			output = "THEME:";
			break;
	}
	output += m_userFileName;
	return output;
}
std::u32string etk::FSNode::getUName(void) const {
	return to_u32string(getName());
}

std::string etk::FSNode::getNameFile(void) const {
	size_t lastPos = m_systemFileName.rfind('/');
	if (lastPos != std::string::npos) {
		return std::string(m_systemFileName, lastPos+1);
	}
	return "";
}
std::u32string etk::FSNode::getUNameFile(void) const {
	return to_u32string(getNameFile());
}

std::string etk::FSNode::getRelativeFolder(void) const {
	std::string tmppp = getName();
	TK_DBG_MODE("get REF folder : " << tmppp );
	switch (m_typeNode) {
		case etk::FSN_UNKNOW:
		case etk::FSN_FOLDER:
		case etk::FSN_LINK:
		if (tmppp[tmppp.size()-1] == '/') {
				TK_DBG_MODE("     ==> : " << tmppp );
				return tmppp;
			} else {
				std::string tmpVal = tmppp;
				tmpVal += "/";
				TK_DBG_MODE("     ==> : " << tmppp );
				return tmpVal;
			}
			break;
		case etk::FSN_BLOCK:
		case etk::FSN_CHARACTER:
		case etk::FSN_FIFO:
		case etk::FSN_FILE:
		case etk::FSN_SOCKET:
		default:
			break;
	}
	size_t lastPos = tmppp.rfind('/');
	if (lastPos != std::string::npos) {
		TK_DBG_MODE("     ==> : " << std::string(tmppp, 0, lastPos+1) );
		return std::string(tmppp, 0, lastPos+1);
	}
	lastPos = tmppp.rfind(':');
	if (lastPos != std::string::npos) {
		TK_DBG_MODE("     ==> : " << std::string(tmppp, 0, lastPos+1) );
		return std::string(tmppp, 0, lastPos+1);
	}
	TK_DBG_MODE("     ==> : \"\"" );
	return "";
}
std::u32string etk::FSNode::getURelativeFolder(void) const {
	return to_u32string(getRelativeFolder());
}


bool etk::FSNode::touch(void) {
	TK_DEBUG("Touch FILE : " << getName());
	//just open in write an close ==> this will update the time
	if (fileOpenAppend() == false) {
		return false;
	}
	bool ret = fileClose();
	// update internal time and properties ...
	updateFileSystemProperty();
	return ret;
}

bool etk::FSNode::move(const std::string& _path) {
	etk::FSNode tmpDst(_path);
	if (tmpDst.exist()==true) {
		tmpDst.remove();
	}
	TK_DEBUG("Move : \"" << getFileSystemName() << "\" ==> \"" << tmpDst.getFileSystemName() << "\"");
	int32_t res = rename(getFileSystemName().c_str(), tmpDst.getFileSystemName().c_str());
	if (res!=0) {
		return false;
	} else {
		return true;
	}
}
bool etk::FSNode::move(const std::u32string& _path) {
	return move(std::to_string(_path));
}

bool etk::FSNode::remove(void) {
	if (getNodeType()==etk::FSN_FOLDER) {
		// remove the folder
		if( 0!=rmdir(m_systemFileName.c_str()) ) {
			if (ENOTEMPTY == errno) {
				TK_ERROR("The Directory is not empty...");
			}
			return false;
		}
	} else {
		if( 0!=unlink(m_systemFileName.c_str()) ) {
			return false;
		}
	}
	// update internal time and properties ...
	updateFileSystemProperty();
	return true;
}

uint64_t etk::FSNode::timeCreated(void) const {
	return m_timeCreate;
}

std::string etk::FSNode::timeCreatedString(void) const {
	time_t tmpVal = (int32_t)m_timeCreate;
	std::string tmpTime = ctime(&tmpVal);
	if (tmpTime[tmpTime.size()-1] == '\n') {
		tmpTime.erase(tmpTime.end()-1);
	}
	return tmpTime;
}
std::u32string etk::FSNode::timeUCreatedString(void) const {
	return to_u32string(timeCreatedString());
}

uint64_t etk::FSNode::timeModified(void) const {
	return m_timeModify;
}

std::string etk::FSNode::timeModifiedString(void) const {
	time_t tmpVal = (int32_t)m_timeModify;
	std::string tmpTime = ctime(&tmpVal);
	if (tmpTime[tmpTime.size()-1] == '\n') {
		tmpTime.erase(tmpTime.end()-1);
	}
	return tmpTime;
}
std::u32string etk::FSNode::timeUModifiedString(void) const {
	return to_u32string(timeModifiedString());
}

uint64_t etk::FSNode::timeAccessed(void) const {
	return m_timeAccess;
}

std::string etk::FSNode::timeAccessedString(void) const {
	time_t tmpVal = (int32_t)m_timeAccess;
	std::string tmpTime = ctime(&tmpVal);
	if (tmpTime[tmpTime.size()-1] == '\n') {
		tmpTime.erase(tmpTime.end()-1);
	}
	return tmpTime;
}
std::u32string etk::FSNode::timeUAccessedString(void) const {
	return to_u32string(timeAccessedString());
}
/*
	Operator :
*/
const etk::FSNode& etk::FSNode::operator=  (const etk::FSNode &_obj ) {
	// avoid copy to itself
	if( this == &_obj ) {
		return *this;
	}
	if(    NULL != m_PointerFile
	#ifdef __TARGET_OS__Android
	    || NULL != m_zipContent
	#endif
	   ) {
		TK_ERROR("Missing close the file : " << *this);
		fileClose();
		m_PointerFile = NULL;
	}
	#ifdef __TARGET_OS__Android
		m_zipContent = NULL;
		m_zipReadingOffset = 0;
	#endif
	std::string tmppp = _obj.getName();
	privateSetName(tmppp);
	return *this;
}
bool etk::FSNode::operator== (const etk::FSNode& _obj ) const {
	if( this == &_obj ) {
		return true;
	}
	if(    _obj.m_userFileName == m_userFileName
	    && _obj.m_systemFileName == m_systemFileName
	    && _obj.m_type == m_type ) {
		return true;
	} else {
		return false;
	}
	return true;
}

bool etk::FSNode::operator!= (const etk::FSNode& _obj ) const {
	return !(*this == _obj);
}

etk::CCout& etk::operator <<(etk::CCout &_os, const etk::FSNode &_obj) {
	_os << "[" << _obj.m_type << "]->\"" << _obj.m_userFileName << "\"";
	return _os;
}

etk::CCout& etk::operator <<(etk::CCout &_os, const enum etk::FSNType &_obj) {
	switch (_obj)
	{
		case etk::FSN_TYPE_UNKNOW:
			_os << "FSN_TYPE_UNKNOW";
			break;
		case etk::FSN_TYPE_DIRECT:
			_os << "FSN_TYPE_DIRECT";
			break;
		case etk::FSN_TYPE_RELATIF:
			_os << "FSN_TYPE_RELATIF";
			break;
		case etk::FSN_TYPE_HOME:
			_os << "FSN_TYPE_HOME";
			break;
		case etk::FSN_TYPE_DATA:
			_os << "FSN_TYPE_DATA";
			break;
		case etk::FSN_TYPE_USER_DATA:
			_os << "FSN_TYPE_USER_DATA";
			break;
		case etk::FSN_TYPE_CACHE:
			_os << "FSN_TYPE_CACHE";
			break;
		case etk::FSN_TYPE_THEME:
			_os << "FSN_TYPE_THEME";
			break;
		case etk::FSN_TYPE_THEME_DATA:
			_os << "FSN_TYPE_THEME(DATA)";
			break;
		default:
			_os << "FSN_TYPE_????";
			break;
	}
	return _os;
}

etk::CCout& etk::operator <<(etk::CCout &_os, const enum etk::typeNode &_obj) {
	switch (_obj) {
		case etk::FSN_UNKNOW:
			_os << "FSN_UNKNOW";
			break;
		case etk::FSN_BLOCK:
			_os << "FSN_BLOCK";
			break;
		case etk::FSN_CHARACTER:
			_os << "FSN_CHARACTER";
			break;
		case etk::FSN_FOLDER:
			_os << "FSN_FOLDER";
			break;
		case etk::FSN_FIFO:
			_os << "FSN_FIFO";
			break;
		case etk::FSN_LINK:
			_os << "FSN_LINK";
			break;
		case etk::FSN_FILE:
			_os << "FSN_FILE";
			break;
		case etk::FSN_SOCKET:
			_os << "FSN_SOCKET";
			break;
		default:
			_os << "FSN_????";
			break;
	}
	return _os;
}

/*
	Folder specific :
*/
int64_t etk::FSNode::folderCount(void) {
	int64_t counter=0;
	DIR *dir = NULL;
	struct dirent *ent = NULL;
	dir = opendir(m_systemFileName.c_str());
	if (dir != NULL) {
		// for each element in the drectory...
		while ((ent = readdir(dir)) != NULL) {
			std::string tmpName(ent->d_name);
			if(    tmpName == "." 
			    || tmpName == ".." ) {
				// do nothing ...
				continue;
			}
			// just increment counter :
			counter++;
		}
		closedir(dir);
	} else {
		TK_ERROR("could not open directory : \"" << *this << "\"");
	}
	return counter;
}

std::vector<etk::FSNode *> etk::FSNode::folderGetSubList(bool _showHidenFile, bool _getFolderAndOther, bool _getFile, bool _temporaryFile) {
	std::vector<etk::FSNode*> tmpp;
	// regenerate the next list :
	etk::FSNode * tmpEmement = NULL;
	if (m_typeNode != etk::FSN_FOLDER ) {
		return tmpp;
	}
	#ifdef __TARGET_OS__Android
	if(    m_type == etk::FSN_TYPE_DATA
	    || m_type == etk::FSN_TYPE_THEME_DATA) {
		std::vector<std::string> listAdded;
		std::string assetsName = "assets/";
		std::string FolderName = getNameFolder();
		if (s_APKArchive==NULL) {
			return tmpp;
		}
		for (int iii=0; iii<s_APKArchive->size(); iii++) {
			std::string filename = s_APKArchive->getName(iii);
			if (start_with(filename, FolderName) == true) {
				std::string tmpString(filename, FolderName.size()+1);
				size_t pos = tmpString.find('/');
				if (pos != std::string::npos) {
					// a simple folder :
					tmpString = std::string(tmpString, 0, pos+1);
				}
				tmpString = getName() + tmpString;
				bool findIt = false;
				for (size_t jjj = 0; jjj < listAdded.size(); ++jjj) {
					if (listAdded[jjj] == tmpString) {
						findIt = true;
						break;
					}
				}
				if (findIt == false) {
					listAdded.push_back(tmpString);
					tmpEmement = new etk::FSNode(tmpString);
					if (NULL == tmpEmement) {
						TK_ERROR("allocation error ... of ewol::FSNode");
						continue;
					}
					TK_VERBOSE("find element : '" << tmpString << "' --> " << *tmpEmement);
					tmpp.push_back(tmpEmement);
					tmpEmement = NULL;
				}
			}
		}
		return tmpp;
	}
	#endif
	DIR *dir = NULL;
	struct dirent *ent = NULL;
	dir = opendir(m_systemFileName.c_str());
	if (dir != NULL) {
		// for each element in the drectory...
		while ((ent = readdir(dir)) != NULL) {
			std::string tmpName(ent->d_name);
			TK_VERBOSE(" search in folder\"" << tmpName << "\"");
			if(    tmpName == "." 
			    || tmpName == ".." ) {
				// do nothing ...
				continue;
			}
			if(    false == start_with(tmpName, ".")
			    || true == _showHidenFile) {
				tmpEmement = new etk::FSNode(getRelativeFolder()+tmpName);
				if (NULL == tmpEmement) {
					TK_ERROR("allocation error ... of ewol::FSNode");
					continue;
				}
				if(tmpEmement->getNodeType() == etk::FSN_FILE) {
					if (true == _getFile) {
						tmpp.push_back(tmpEmement);
					} else {
						delete(tmpEmement);
						tmpEmement = NULL;
					}
				} else if (_getFolderAndOther) {
					tmpp.push_back(tmpEmement);
				} else {
					delete(tmpEmement);
					tmpEmement = NULL;
				}
			}
		}
		closedir(dir);
	} else {
		TK_ERROR("could not open directory : \"" << *this << "\"");
	}
	
	// reorder the files
	sortElementList(tmpp);
	
	return tmpp;
}

etk::FSNode etk::FSNode::folderGetParent(void) {
	etk::FSNode tmpp;
	return tmpp;
}

void etk::FSNode::folderGetRecursiveFiles(std::vector<std::string>& _output, bool _recursiveEnable) {
	#ifdef __TARGET_OS__Android
	if(    m_type == etk::FSN_TYPE_DATA
	    || m_type == etk::FSN_TYPE_THEME_DATA) {
		std::string assetsName = "assets/";
		std::string FolderName = getNameFolder();
		if (s_APKArchive==NULL) {
			return;
		}
		for (int iii=0; iii<s_APKArchive->size(); iii++) {
			std::string filename = s_APKArchive->getName(iii);
			if (start_with(filename, FolderName) == true) {
				std::string tmpString;
				if(m_type == etk::FSN_TYPE_DATA) {
					tmpString = "DATA:";
				} else {
					tmpString = "THEME:";
				}
				if (start_with(filename, assetsName) == true) {
					filename.erase(0,assetsName.size());
				}
				tmpString += filename;
				_output.push_back(tmpString);
			}
		}
		return;
	}
	#endif
	// regenerate the next list :
	etk::FSNode * tmpEmement;
	DIR *dir = NULL;
	struct dirent *ent = NULL;
	dir = opendir(m_systemFileName.c_str());
	//TK_DEBUG(" ** open Folder : " << m_systemFileName );
	if (dir != NULL) {
		// for each element in the drectory...
		while ((ent = readdir(dir)) != NULL) {
			std::string tmpName(ent->d_name);
			if(    tmpName == "." 
			    || tmpName == ".." ) {
				// do nothing ...
				continue;
			}
			//TK_DEBUG(" find : " << ent->d_name << " ==> " << (GetRelativeFolder()+tmpName));
			tmpEmement = new etk::FSNode(getRelativeFolder()+tmpName);
			if (NULL != tmpEmement) {
				if(tmpEmement->getNodeType() == etk::FSN_FILE) {
					std::string tmpVal = tmpEmement->getName();
					_output.push_back(tmpVal);
				}
				if(tmpEmement->getNodeType() == etk::FSN_FOLDER) {
					if (true==_recursiveEnable) {
						tmpEmement->folderGetRecursiveFiles(_output, _recursiveEnable);
					}
				}
				delete(tmpEmement);
				tmpEmement = NULL;
			} else {
				TK_ERROR("allocation error ... of ewol::FSNode");
				continue;
			}
		}
		closedir(dir);
	} else {
		TK_ERROR("could not open directory : \"" << *this << "\"");
	}
	return;
}
void etk::FSNode::folderGetRecursiveFiles(std::vector<std::u32string>& _output, bool _recursiveEnable) {
	_output.clear();
	std::vector<std::string> tmpVal;
	folderGetRecursiveFiles(tmpVal, _recursiveEnable);
	for (size_t iii=0; iii<tmpVal.size(); ++iii) {
		_output.push_back(to_u32string(tmpVal[iii]));
	}
}

/*
	File Specific :
*/
bool etk::FSNode::fileHasExtention(void) {
	size_t lastPos = m_userFileName.rfind('.');
	if(    lastPos != std::string::npos // Find a . at the fist position .jdlskjdfklj ==> hiden file
	    && m_userFileName.size() != lastPos ) { // Remove file ended with .
		return true;
	} else {
		return false;
	}
}

std::string etk::FSNode::fileGetExtention(void) {
	size_t lastPos = m_userFileName.rfind('.');
	if(    lastPos != std::string::npos // Find a . at the fist position .jdlskjdfklj ==> hiden file
	    && m_userFileName.size() != lastPos ) { // Remove file ended with .
		// Get the FileName
		return std::string(m_userFileName, lastPos+1);
	}
	return "";
}
std::u32string etk::FSNode::fileUGetExtention(void) {
	return to_u32string(fileGetExtention());
}

uint64_t etk::FSNode::fileSize(void) {
	if (etk::FSN_FILE != m_typeNode) {
		TK_ERROR("Request size of a non file node : " << m_typeNode);
		return 0;
	}
	#ifdef __TARGET_OS__Android
	if(    etk::FSN_TYPE_DATA == m_type
	    || etk::FSN_TYPE_THEME_DATA == m_type) {
		if (true == loadDataZip()) {
			return m_zipContent->getTheoricSize();
		}
		return 0;
	}
	#endif
	// Note : this is a proper methode to get the file size for Big files ... otherwithe the size is limited at 2^31 bytes
	// tmpStat Buffer :
	struct stat statProperty;
	if (-1 == stat(m_systemFileName.c_str(), &statProperty)) {
		//Normal case when the file does not exist ... ==> the it was in unknow mode ...
		TK_ERROR("mlkmlkmlkmlkmlkmlk");
		return 0;
	}
	TK_VERBOSE(" file size : " << (int64_t)statProperty.st_size << " bytes");
	if ((uint64_t)statProperty.st_size<=0) {
		return 0;
	}
	return (uint64_t)statProperty.st_size;
}


bool etk::FSNode::fileOpenRead(void) {
	#ifdef __TARGET_OS__Android
	if(    etk::FSN_TYPE_DATA == m_type
	    || etk::FSN_TYPE_THEME_DATA == m_type) {
		if (false==loadDataZip()) {
			return false;
		}
		s_APKArchive->open(m_systemFileName);
		return m_zipContent->getTheoricSize() == m_zipContent->size();
	}
	#endif
	if (NULL != m_PointerFile) {
		TK_CRITICAL("File Already open : " << *this);
		return true;
	}
	TK_VERBOSE(" Read file : " << m_systemFileName);
	m_PointerFile=fopen(m_systemFileName.c_str(),"rb");
	if(NULL == m_PointerFile) {
		TK_ERROR("Can not find the file " << *this );
		return false;
	}
	return true;
}
bool etk::FSNode::fileOpenWrite(void) {
	#ifdef __TARGET_OS__Android
	if(    etk::FSN_TYPE_DATA == m_type
	    || etk::FSN_TYPE_THEME_DATA == m_type) {
		return false;
	}
	#endif
	if (NULL != m_PointerFile) {
		TK_CRITICAL("File Already open : " << *this);
		return true;
	}
	FSNODE_LOCAL_mkPath(getNameFolder().c_str() , 0777);
	TK_VERBOSE(" write file : " << m_systemFileName);
	m_PointerFile=fopen(m_systemFileName.c_str(),"wb");
	if(NULL == m_PointerFile) {
		TK_ERROR("Can not find the file " << *this);
		return false;
	}
	return true;
}

bool etk::FSNode::fileOpenAppend(void) {
	#ifdef __TARGET_OS__Android
	if(    etk::FSN_TYPE_DATA == m_type
	    || etk::FSN_TYPE_THEME_DATA == m_type) {
		return false;
	}
	#endif
	if (NULL != m_PointerFile) {
		TK_CRITICAL("File Already open : " << *this);
		return true;
	}
	FSNODE_LOCAL_mkPath(getNameFolder().c_str() , 0777);
	
	TK_VERBOSE(" append file : " << m_systemFileName);
	
	m_PointerFile=fopen(m_systemFileName.c_str(),"ab");
	if(NULL == m_PointerFile) {
		TK_ERROR("Can not find the file " << *this);
		return false;
	}
	return true;
}

bool etk::FSNode::fileClose(void) {
	#ifdef __TARGET_OS__Android
	if(    etk::FSN_TYPE_DATA == m_type
	    || etk::FSN_TYPE_THEME_DATA == m_type) {
		if (m_zipContent == NULL) {
			TK_CRITICAL("File Already closed : " << *this);
			return false;
		}
		s_APKArchive->close(m_systemFileName);
		m_zipContent = NULL;
		m_zipReadingOffset = 0;
		return true;
	}
	#endif
	if (m_PointerFile == NULL) {
		TK_CRITICAL("File Already closed : " << *this);
		return false;
	}
	fclose(m_PointerFile);
	m_PointerFile = NULL;
	return true;
}

char* etk::FSNode::fileGets(char* _elementLine, int64_t _maxData) {
	memset(_elementLine, 0, _maxData);
	#ifdef __TARGET_OS__Android
	char * element = _elementLine;
	int64_t outSize = 0;
	if(    m_type == etk::FSN_TYPE_DATA
	    || m_type == etk::FSN_TYPE_THEME_DATA) {//char * tmpData = internalDataFiles[iii].data + m_readingOffset;
		if (m_zipContent == NULL) {
			element[0] = '\0';
			return NULL;
		}
		if (m_zipReadingOffset >= m_zipContent->size()) {
			element[0] = '\0';
			return NULL;
		}
		while (((char*)m_zipContent->data())[m_zipReadingOffset] != '\0') {
			if(    ((char*)m_zipContent->data())[m_zipReadingOffset] == '\n'
			    || ((char*)m_zipContent->data())[m_zipReadingOffset] == '\r') {
				*element = ((char*)m_zipContent->data())[m_zipReadingOffset];
				element++;
				m_zipReadingOffset++;
				*element = '\0';
				return _elementLine;
			}
			*element = ((char*)m_zipContent->data())[m_zipReadingOffset];
			element++;
			m_zipReadingOffset++;
			if (m_zipReadingOffset>=m_zipContent->size()) {
				*element = '\0';
				return _elementLine;
			}
			// check maxData Size ...
			if (outSize>=_maxData-1) {
				*element = '\0';
				return _elementLine;
			}
			outSize++;
		}
		if (outSize==0) {
			return NULL;
		} else {
			// send last line
			return _elementLine;
		}
	}
	#endif
	return fgets(_elementLine, _maxData, m_PointerFile);
}

char etk::FSNode::fileGet(void) {
	char data='\0';
	if (fileRead(&data, 1, 1)!=1) {
		return '\0';
	}
	return data;
}

int64_t etk::FSNode::fileRead(void* _data, int64_t _blockSize, int64_t _nbBlock) {
	#ifdef __TARGET_OS__Android
	if(    m_type == etk::FSN_TYPE_DATA
	    || m_type == etk::FSN_TYPE_THEME_DATA) {
		if (m_zipContent == NULL) {
			((char*)_data)[0] = '\0';
			return 0;
		}
		int32_t dataToRead = _blockSize * _nbBlock;
		if (dataToRead + m_zipReadingOffset > m_zipContent->size()) {
			_nbBlock = ((m_zipContent->size() - m_zipReadingOffset) / _blockSize);
			dataToRead = _blockSize * _nbBlock;
		}
		memcpy(_data, &((char*)m_zipContent->data())[m_zipReadingOffset], dataToRead);
		m_zipReadingOffset += dataToRead;
		return _nbBlock;
	}
	#endif
	return fread(_data, _blockSize, _nbBlock, m_PointerFile);
}

int64_t etk::FSNode::fileWrite(void * _data, int64_t _blockSize, int64_t _nbBlock) {
	#ifdef __TARGET_OS__Android
	if(    m_type == etk::FSN_TYPE_DATA
	    || m_type == etk::FSN_TYPE_THEME_DATA) {
		TK_CRITICAL("Can not write on data inside APK : " << *this);
		return 0;
	}
	#endif
	return fwrite(_data, _blockSize, _nbBlock, m_PointerFile);
}
bool etk::FSNode::fileSeek(long int _offset, enum etk::seekNode _origin)
{
	#ifdef __TARGET_OS__Android
	if(    m_type == etk::FSN_TYPE_DATA
	    || m_type == etk::FSN_TYPE_THEME_DATA) {
		if (NULL == m_zipContent) {
			return false;
		}
		int32_t positionEnd = 0;
		switch(_origin) {
			case etk::FSN_SEEK_END:
				positionEnd = m_zipContent->size();
				break;
			case etk::FSN_SEEK_CURRENT:
				positionEnd = m_zipReadingOffset;
				break;
			default:
				positionEnd = 0;
				break;
		}
		positionEnd += _offset;
		if (positionEnd < 0) {
			positionEnd = 0;
		} else if (positionEnd > m_zipContent->size()) {
			positionEnd = m_zipContent->size();
		}
		m_zipReadingOffset = positionEnd;
		return true;
	}
	#endif
	int originFS = 0;
	switch(_origin) {
		case etk::FSN_SEEK_END:
			originFS = SEEK_END;
			break;
		case etk::FSN_SEEK_CURRENT:
			originFS = SEEK_CUR;
			break;
		default:
			originFS = 0;
			break;
	}
	fseek(m_PointerFile, _offset, originFS);
	if(ferror(m_PointerFile)) {
		return false;
	} else {
		return true;
	}
}

void etk::FSNode::fileFlush(void) {
	#ifdef __TARGET_OS__Android
	if(    m_type == etk::FSN_TYPE_DATA
	    || m_type == etk::FSN_TYPE_THEME_DATA) {
		return;
	}
	#endif
	if (m_PointerFile != NULL) {
		fflush(m_PointerFile);
	}
}


// TODO : Add an INIT to reset all allocated parameter :
static etk::Hash<std::string> g_listTheme;

void etk::theme::setName(const std::string& _refName, const std::string& _folderName) {
	g_listTheme.set(_refName, _folderName);
}
void etk::theme::setName(const std::u32string& _refName, const std::u32string& _folderName) {
	setName(std::to_string(_refName), std::to_string(_folderName));
}

std::string etk::theme::getName(const std::string& _refName) {
	if (g_listTheme.exist(_refName) == true) {
		return g_listTheme[_refName];
	}
	return _refName;
}
std::u32string etk::theme::getName(const std::u32string& _refName) {
	return to_u32string(getName(std::to_string(_refName)));
}

// get the list of all the theme folder availlable in the user Home/appl
std::vector<std::string> etk::theme::list(void) {
	std::vector<std::string> tmpp;
	return tmpp;
	// TODO :
}
std::vector<std::u32string> etk::theme::listU(void) {
	std::vector<std::u32string> tmpp;
	return tmpp;
	// TODO :
}

static etk::Hash<std::string> g_listThemeDefault;
void etk::theme::setNameDefault(const std::string& _refName, const std::string& _folderName) {
	g_listThemeDefault.set(_refName, _folderName);
}
void etk::theme::setNameDefault(const std::u32string& _refName, const std::u32string& _folderName) {
	setNameDefault(std::to_string(_refName), std::to_string(_folderName));
}
std::string etk::theme::getNameDefault(const std::string& _refName) {
	if (g_listThemeDefault.exist(_refName) == true) {
		return g_listThemeDefault[_refName];
	}
	return "default";
}
std::u32string etk::theme::getNameDefault(const std::u32string& _refName) {
	return to_u32string(getNameDefault(std::to_string(_refName)));
}



/* --------------------------------------------------------------------------
 * 
 *  Simple direct wrapper on the FileSystem node access :
 * 
 * -------------------------------------------------------------------------- */
bool etk::FSNodeRemove(const std::string& _path) {
	etk::FSNode tmpNode(_path);
	if (false==tmpNode.exist()) {
		return false;
	}
	return tmpNode.remove();
}
bool etk::FSNodeRemove(const std::u32string& _path) {
	return FSNodeRemove(std::to_string(_path));
}

int64_t etk::FSNodeGetCount(const std::string& _path) {
	etk::FSNode tmpNode(_path);
	if (false==tmpNode.exist()) {
		return -1;
	}
	return tmpNode.folderCount();
}
int64_t etk::FSNodeGetCount(const std::u32string& _path) {
	return FSNodeGetCount(std::to_string(_path));
}

bool etk::FSNodeCreate(const std::string& _path, etk::FSNodeRight _right, enum etk::typeNode _type) {
	// TODO :
	return false;
}
bool etk::FSNodeCreate(const std::u32string& _path, etk::FSNodeRight _right, enum etk::typeNode _type) {
	return FSNodeCreate(std::to_string(_path), _right, _type);
}

bool etk::FSNodeExist(const std::string& _path) {
	etk::FSNode tmpNode(_path);
	return tmpNode.exist();
}
bool etk::FSNodeExist(const std::u32string& _path) {
	return FSNodeExist(std::to_string(_path));
}

bool etk::FSNodeMove(const std::string& _path1, const std::string& _path2) {
	etk::FSNode tmpNode(_path1);
	if (false==tmpNode.exist()) {
		TK_DEBUG("try to move un existant file \"" << _path1 << "\"");
		return false;
	}
	// no check error in every case
	(void)etk::FSNodeRemove(_path2);
	//move the node
	return tmpNode.move(_path2);
}
bool etk::FSNodeMove(const std::u32string& _path1, const std::u32string& _path2) {
	return FSNodeMove(std::to_string(_path1), std::to_string(_path2));
}

etk::FSNodeRight etk::FSNodeGetRight(const std::string& _path) {
	etk::FSNode tmpNode(_path);
	return tmpNode.getRight();
}
etk::FSNodeRight etk::FSNodeGetRight(const std::u32string& _path) {
	return FSNodeGetRight(std::to_string(_path));
}

enum etk::typeNode etk::FSNodeGetType(const std::string& _path) {
	etk::FSNode tmpNode(_path);
	return tmpNode.getNodeType();
}
enum etk::typeNode etk::FSNodeGetType(const std::u32string& _path) {
	return FSNodeGetType(std::to_string(_path));
}

uint64_t etk::FSNodeGetTimeCreated(const std::string& _path) {
	etk::FSNode tmpNode(_path);
	return tmpNode.timeCreated();
}
uint64_t etk::FSNodeGetTimeCreated(const std::u32string& _path) {
	return FSNodeGetTimeCreated(std::to_string(_path));
}

uint64_t etk::FSNodeGetTimeModified(const std::string& _path) {
	etk::FSNode tmpNode(_path);
	return tmpNode.timeModified();
}
uint64_t etk::FSNodeGetTimeModified(const std::u32string& _path) {
	return FSNodeGetTimeModified(std::to_string(_path));
}

uint64_t etk::FSNodeGetTimeAccessed(const std::string& _path) {
	etk::FSNode tmpNode(_path);
	return tmpNode.timeAccessed();
}
uint64_t etk::FSNodeGetTimeAccessed(const std::u32string& _path) {
	return FSNodeGetTimeAccessed(std::to_string(_path));
}

bool etk::FSNodeTouch(const std::string& _path) {
	etk::FSNode tmpNode(_path);
	return tmpNode.touch();
}
bool etk::FSNodeTouch(const std::u32string& _path) {
	return FSNodeTouch(std::to_string(_path));
}

bool etk::FSNodeEcho(const std::string& _path, const std::string& _dataTowrite) {
	etk::FSNode tmpNode(_path);
	if (false==tmpNode.exist()) {
		return false;
	}
	if (FSN_FOLDER==tmpNode.getNodeType()) {
		return false;
	}
	if (false==tmpNode.fileOpenWrite()) {
		return false;
	}
	// convert in UTF8 :
	if ((int64_t)_dataTowrite.size() != tmpNode.fileWrite((char*)_dataTowrite.c_str(), 1, _dataTowrite.size())) {
		tmpNode.fileClose();
		return false;
	}
	return tmpNode.fileClose();
}
bool etk::FSNodeEcho(const std::u32string& _path, const std::u32string& _dataTowrite) {
	return FSNodeEcho(std::to_string(_path), std::to_string(_dataTowrite));
}

bool etk::FSNodeEchoAdd(const std::string& _path, const std::string& _dataTowrite) {
	etk::FSNode tmpNode(_path);
	if (false==tmpNode.exist()) {
		return false;
	}
	if (FSN_FOLDER==tmpNode.getNodeType()) {
		return false;
	}
	if (false==tmpNode.fileOpenAppend()) {
		return false;
	}
	// convert in UTF8 :
	if ((int64_t)_dataTowrite.size() != tmpNode.fileWrite((char*)_dataTowrite.c_str(), 1, _dataTowrite.size())) {
		tmpNode.fileClose();
		return false;
	}
	return tmpNode.fileClose();
}
bool etk::FSNodeEchoAdd(const std::u32string& _path, const std::u32string& _dataTowrite) {
	return FSNodeEchoAdd(std::to_string(_path), std::to_string(_dataTowrite));
}

void etk::FSNodeHistory(const std::string& _path, int32_t _historyCount) {
	// step 1 : Move the file to prevent writing error
	//Get the first oldest save :
	for (int32_t iii=_historyCount-1; iii>0 ; iii--) {
		if (true==etk::FSNodeExist(_path + "-" + std::to_string(iii)) ) {
			etk::FSNodeMove(_path + "-" + std::to_string(iii), _path + "-" + std::to_string(iii+1));
		}
	}
	if (true==etk::FSNodeExist(_path) ) {
		etk::FSNodeMove(_path, _path + "-1");
	}
}
void etk::FSNodeHistory(const std::u32string& _path, int32_t _historyCount) {
	return FSNodeHistory(std::to_string(_path), _historyCount);
}
