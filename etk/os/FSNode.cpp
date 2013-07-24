/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */


#include <etk/types.h>
#include <etk/DebugInternal.h>
#include <etk/os/FSNode.h>
#include <unistd.h>
#include <stdlib.h>
#include <etk/tool.h>
#include <etk/Vector.h>
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



static etk::UString SimplifyPathAbstractPath(etk::UString input)
{
	int32_t findStartPos = input.FindForward('/') + 1;
	int32_t findPos = input.FindForward('/', findStartPos);
	//TK_DEBUG("Siplify : \"" << input << "\"");
	int32_t preventBadCode = 0;
	while (findPos!=-1)
	{
		//TK_DEBUG("      string=\"" << input << "\"");
		//TK_DEBUG("      '/' @" << findPos);
		if (input.Size()<findPos+1) {
			// no more element ...
			break;
		}
		if(    input[findPos+1] == '/'
		    || (    input[findPos+1] == '.'
		         && input.Size()==findPos+2 )) {
			// cleane the element path
			input.Remove(findPos+1, 1);
			//TK_DEBUG("      Remove // string=\"" << input << "\"");
		} else {
			if (input.Size()<findPos+2) {
				// no more element ...
				break;
			}
			if(    input[findPos+1] == '.'
			    && input[findPos+2] == '.') {
				// cleane the element path
				input.Remove(findStartPos, findPos+3 - findStartPos );
				//TK_DEBUG("      Remove xxx/.. string=\"" << input << "\"");
			} else if(    input[findPos+1] == '.'
			           && input[findPos+2] == '/') {
				// cleane the element path
				input.Remove(findPos+1, 2);
				//TK_DEBUG("      Remove ./ string=\"" << input << "\"");
			} else {
				findStartPos = findPos+1;
			}
		}
		findPos = input.FindForward('/', findStartPos);
		preventBadCode++;
		if (preventBadCode>5000) {
			TK_CRITICAL("ERROR when getting the small path ... this is loop prevention...");
			break;
		}
	}
	/*
	#ifndef __TARGET_OS__Windows
		// for the target that supported the Realpath system :
		char buf[MAX_FILE_NAME];
		memset(buf, 0, MAX_FILE_NAME);
		char * ok = realpath(input.c_str(), buf);
		if (!ok) {
			TK_ERROR("Error to get the real path");
			input = "/";
		} else {
			input = buf;
		}
	#endif
	*/
	//TK_DEBUG("   ==> \"" << input << "\"");
	return input;
}



// zip file of the apk file for Android ==> set to zip file apk access
static etk::UString s_fileAPK = "";
static etk::UString baseApplName = "ewolNoName";
static etk::UString baseRunPath = "/";
#if defined(__TARGET_OS__Android)
	static etk::UString baseFolderHome     = "/sdcard/";                 // home folder
	static etk::UString baseFolderData     = "assets/";                  // program Data
	static etk::UString baseFolderDataUser = "/sdcard/.tmp/userData/";   // Data specific user (local modification)
	static etk::UString baseFolderCache    = "/sdcard/.tmp/cache/";      // Temporary data (can be removed the next time)
#elif defined(__TARGET_OS__Windows)
	static etk::UString baseFolderHome     = "c:/test";                  // home folder
	static etk::UString baseFolderData     = "c:/test/share/";           // program Data
	static etk::UString baseFolderDataUser = "c:/test/userData/";        // Data specific user (local modification)
	static etk::UString baseFolderCache    = "c:/Windows/Temp/ewol/";    // Temporary data (can be removed the next time)
#else
	static etk::UString baseFolderHome     = "~";                  // home folder
	static etk::UString baseFolderData     = "share/";             // program Data
	static etk::UString baseFolderDataUser = "~/.tmp/userData/";   // Data specific user (local modification)
	static etk::UString baseFolderCache    = "~/.tmp/cache/";      // Temporary data (can be removed the next time)
#endif


#ifdef __TARGET_OS__Android
	static etk::Archive* s_APKArchive = NULL;
	static void loadAPK(etk::UString& apkPath)
	{
		TK_DEBUG("Loading APK \"" << apkPath << "\"");
		s_APKArchive = etk::Archive::Load(apkPath);
		TK_ASSERT(s_APKArchive != NULL, "Error loading APK ...  \"" << apkPath << "\"");
		//Just for debug, print APK contents
		s_APKArchive->Display();
	}
#endif

// for specific device contraint : 
void etk::SetBaseFolderData(const char * folder)
{
	#ifdef __TARGET_OS__Android
		baseFolderData = "assets/";
		s_fileAPK = folder;
		loadAPK(s_fileAPK);
	#else
		TK_WARNING("Not Availlable Outside Android");
	#endif
}

void etk::SetBaseFolderDataUser(const char * folder)
{
	#ifdef __TARGET_OS__Android
		baseFolderDataUser = folder;
	#else
		TK_WARNING("Not Availlable Outside Android");
	#endif
}

void etk::SetBaseFolderCache(const char * folder)
{
	#ifdef __TARGET_OS__Android
		baseFolderCache = folder;
	#else
		TK_WARNING("Not Availlable Outside Android");
	#endif
}

etk::UString l_argZero="";
void etk::SetArgZero(const etk::UString& val)
{
	l_argZero = val;
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
etk::UString GetApplicationPath(void)
{
	etk::UString binaryName = "no-name";
	char binaryCompleatePath[FILENAME_MAX];
	memset(binaryCompleatePath, 0, FILENAME_MAX);
	#ifdef __TARGET_OS__Windows
		GetModuleFileName(NULL, binaryCompleatePath, FILENAME_MAX);
		if (0==strlen(binaryCompleatePath)) {
			TK_CRITICAL("Can not get the binary position in the tree ==> this is really bad ...");
		} else {
			binaryName = binaryCompleatePath;
		}
	#else
		// check it to prevent test mode in local folder ...
		// Generic Linux system
		readlink("/proc/self/exe", binaryCompleatePath, FILENAME_MAX);
		if(0!=strlen(binaryCompleatePath)) {
			binaryName = binaryCompleatePath;
			return binaryName;
		}
		// generic FreeBSD system
		memset(binaryCompleatePath, 0, FILENAME_MAX);
		readlink("/proc/curproc/file", binaryCompleatePath, FILENAME_MAX);
		if(0!=strlen(binaryCompleatePath)) {
			binaryName = binaryCompleatePath;
			return binaryName;
		}
		// generic Solaris system 
		memset(binaryCompleatePath, 0, FILENAME_MAX);
		readlink("/proc/self/path/a.out", binaryCompleatePath, FILENAME_MAX);
		if(0!=strlen(binaryCompleatePath)) {
			binaryName = binaryCompleatePath;
			return binaryName;
		}
		// now we are in a really bad case ...
		if (l_argZero.Size() == 0) {
			TK_CRITICAL("Can not get the binary position in the tree ==> this is really bad ... arg 0 is as bad as other ...");
			return binaryName;
		}
		TK_VERBOSE("Parse arg0 = '" << l_argZero << "' start with '/' ???");
		if (l_argZero.StartWith("/")==true) {
			binaryName = l_argZero;
			return SimplifyPathAbstractPath(binaryName);
		}
		TK_VERBOSE("Parse arg0 = '" << l_argZero << "' try add PWD");
		char * basicPathPWD = getenv("PWD");
		if (NULL != basicPathPWD) {
			etk::UString testCompleatePath = basicPathPWD;
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
				return SimplifyPathAbstractPath(binaryName);
			}
		}
		char * basicPathPATH = getenv("PATH");
		if (NULL != basicPathPWD) {
			// TODO : bad case ...
		}
		// and now we will really in a bad mood ...
	#endif
	TK_INFO("Binary name : " << binaryName);
	return binaryName;
}

void etk::InitDefaultFolder(const char * applName)
{
	baseApplName = applName;
	char cCurrentPath[FILENAME_MAX];
	
	char * basicPath = getenv("HOME");
	if (NULL == basicPath) {
		TK_ERROR("ERROR while trying to get the path of the home folder");
		#if defined(__TARGET_OS__Windows)
			baseFolderHome = "c:/";
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
		etk::UString binaryPath = GetApplicationPath();
		binaryPath.Replace('\\', '/');
		int32_t pos = binaryPath.FindBack('/');
		etk::UString binaryName = binaryPath.Extract(pos);
		binaryPath.Remove(pos, binaryName.Size());
		TK_INFO("Bianry name : '" << binaryPath << "' && '" << binaryName << "'" );
		#ifdef __TARGET_OS__Windows
			baseFolderData = binaryPath;
			baseFolderData += "/data/";
			
			baseFolderDataUser  = binaryPath;
			baseFolderDataUser += "/user/";
			
			baseFolderCache  = binaryPath;
			baseFolderCache += "/tmp/";
		#else
			// if element is installed :
			baseFolderData = "/usr/share";
			baseFolderData += binaryName;
			baseFolderData += "/";
			
			etk::UString theoricInstalledName = "/usr/bin";
			theoricInstalledName += binaryName;
			TK_VERBOSE(" position : '" << binaryPath << "' installed position : '" << theoricInstalledName << "'");
			if (binaryPath != theoricInstalledName) {
				TK_INFO(" base path is not correct try to find it : (must only appear in test and not when installed) base name : '" << binaryPath << "'");
				// remove bin/applName
				baseFolderData = binaryPath;
				#ifdef __TARGET_OS__MacOs
					baseFolderData += "/../../Resources/";
				#else
					baseFolderData += "/../../share";
					baseFolderData += binaryName;
					baseFolderData += "/";
				#endif
				baseFolderData = SimplifyPathAbstractPath(baseFolderData);
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

etk::UString etk::GetUserHomeFolder(void)
{
	return baseFolderHome;
}

etk::UString etk::GetUserRunFolder(void)
{
	return baseRunPath;
}


#ifdef __TARGET_OS__Android
bool etk::FSNode::LoadDataZip(void)
{
	if (NULL == s_APKArchive) {
		return false;
	}
	if (NULL != m_zipContent) {
		return true;
	}
	m_zipContent = &s_APKArchive->GetContent(m_systemFileName);
	if (NULL != m_zipContent) {
		return true;
	}
	return false;
}
#endif



static int32_t FSNODE_LOCAL_mkdir(const char *path, mode_t mode)
{
	struct stat st;
	int32_t status = 0;
	if (stat(path, &st) != 0) {
		/* Directory does not exist. EEXIST for race condition */
		#ifdef __TARGET_OS__Windows
		if(0!=mkdir(path)
		#else
		if(0!=mkdir(path, mode)
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

static int32_t FSNODE_LOCAL_mkPath(const char *path, mode_t mode)
{
	char *pp;
	char *sp;
	int status;
	char *copypath = strdup(path);
	if (NULL==copypath) {
		return -1;
	}
	status = 0;
	pp = copypath;
	while (status == 0 && (sp = strchr(pp, '/')) != 0) {
		if (sp != pp) {
			/* Neither root nor double slash in path */
			*sp = '\0';
			status = FSNODE_LOCAL_mkdir(copypath, mode);
			*sp = '/';
		}
		pp = sp + 1;
	}
	if (status == 0) {
		status = FSNODE_LOCAL_mkdir(path, mode);
	}
	free(copypath);
	return (status);
}





#undef __class__
#define __class__	"FSNode"

etk::FSNode::FSNode(const etk::UString& nodeName) :
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
	PrivateSetName(nodeName);
}


etk::FSNode::~FSNode(void)
{
	if(    NULL != m_PointerFile
	#ifdef __TARGET_OS__Android
	    || NULL != m_zipContent
	#endif
	  ) {
		TK_ERROR("Missing to close the file : \"" << *this << "\"");
		FileClose();
	}
}


void etk::FSNode::SortElementList(etk::Vector<etk::FSNode *> &list)
{
	etk::Vector<etk::FSNode *> tmpList = list;
	list.Clear();
	for(int32_t iii=0; iii<tmpList.Size(); iii++) {
		if (NULL != tmpList[iii]) {
			int32_t findPos = 0;
			for(int32_t jjj=0; jjj<list.Size(); jjj++) {
				//EWOL_DEBUG("compare : \""<<*tmpList[iii] << "\" and \"" << *m_listDirectory[jjj] << "\"");
				if (list[jjj]!=NULL) {
					if (tmpList[iii]->GetNameFile() > list[jjj]->GetNameFile()) {
						findPos = jjj+1;
					}
				}
			}
			//EWOL_DEBUG("position="<<findPos);
			list.Insert(findPos, tmpList[iii]);
		}
	}
}

void etk::FSNode::PrivateSetName(const etk::UString& newName)
{
	if(    NULL != m_PointerFile
	#ifdef __TARGET_OS__Android
	    || NULL != m_zipContent
	#endif
	  ) {
		TK_ERROR("Missing to close the file : \"" << *this << "\"");
		FileClose();
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
	TK_DBG_MODE("1 : Set Name :              \"" << newName << "\"");
	
	// generate destination name in case of the input error
	etk::UString destFilename;
	if (newName.Size() == 0) {
		// if no name ==> go to the root Folder
		destFilename = "ROOT:";
	} else {
		destFilename = newName;
	}
	
	bool isRootFolder = false;
	#ifdef __TARGET_OS__Windows
		for (char iii='a' ; iii<='z' ; iii++) {
			char tmpVal[10];
			char tmpValMaj[10];
			sprintf(tmpVal, "%c:/", iii);
			sprintf(tmpValMaj, "%c:/", iii+'A'-'a');
			if(    true == destFilename.StartWith(tmpVal)
			    || true == destFilename.StartWith(tmpValMaj)) {
				isRootFolder = true;
				break;
			}
		}
	#else
		isRootFolder = destFilename.StartWith("/");
	#endif
	if (true == destFilename.StartWith(baseFolderHome) ) {
		TK_DBG_MODE("    ==> detect home");
		destFilename.Remove(0, baseFolderHome.Size());
		m_type = etk::FSN_TYPE_HOME;
	} else if(true == isRootFolder) {
		TK_DBG_MODE("    ==> detect root");
		#ifdef __TARGET_OS__Windows
			destFilename.Remove(0, 3);
		#else
			destFilename.Remove(0, 1);
		#endif
		m_type = etk::FSN_TYPE_DIRECT;
	} else if(    true == destFilename.StartWith("ROOT:")
	           || true == destFilename.StartWith("root:") ) {
		TK_DBG_MODE("    ==> detect root 2 ");
		destFilename.Remove(0, 5);
		m_type = etk::FSN_TYPE_DIRECT;
		if(true == destFilename.StartWith("~")) {
			destFilename.Remove(0, 1);
			m_type = etk::FSN_TYPE_HOME;
		}
	} else if(    true == destFilename.StartWith("DIRECT:")
	           || true == destFilename.StartWith("direct:") ) {
		TK_DBG_MODE("    ==> detect direct");
		destFilename.Remove(0, 7);
		m_type = etk::FSN_TYPE_DIRECT;
		if(true == destFilename.StartWith("~")) {
			destFilename.Remove(0, 1);
			m_type = etk::FSN_TYPE_HOME;
		}
	} else if(    true == destFilename.StartWith("DATA:")
	           || true == destFilename.StartWith("data:") ) {
		TK_DBG_MODE("    ==> detect data");
		destFilename.Remove(0, 5);
		m_type = etk::FSN_TYPE_DATA;
	} else if(    true == destFilename.StartWith("USERDATA:")
	           || true == destFilename.StartWith("userdata:") ) {
		TK_DBG_MODE("    ==> detect User-data");
		destFilename.Remove(0, 9);
		m_type = etk::FSN_TYPE_USER_DATA;
	} else if(    true == destFilename.StartWith("CACHE:")
	           || true == destFilename.StartWith("cache:") ) {
		TK_DBG_MODE("    ==> detect Cach");
		destFilename.Remove(0, 6);
		m_type = etk::FSN_TYPE_CACHE;
	} else if(    true == destFilename.StartWith("THEME:")
	           || true == destFilename.StartWith("theme:") ) {
		TK_DBG_MODE("    ==> detect theme");
		destFilename.Remove(0, 6);
		m_type = etk::FSN_TYPE_THEME;
	} else if(true == destFilename.StartWith("~")) {
		TK_DBG_MODE("    ==> detect home 2");
		destFilename.Remove(0, 1);
		m_type = etk::FSN_TYPE_HOME;
	} else if(    true == destFilename.StartWith("HOME:")
	           || true == destFilename.StartWith("home:") ) {
		TK_DBG_MODE("    ==> detect home 3");
		destFilename.Remove(0, 5);
		m_type = etk::FSN_TYPE_HOME;
		if(true == destFilename.StartWith("~")) {
			destFilename.Remove(0, 1);
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
		etk::UString tmpName = etk::GetUserRunFolder() + "/" + destFilename;
		destFilename = tmpName;
		m_type = etk::FSN_TYPE_DIRECT;
		
	}
	m_userFileName = destFilename;
	TK_DBG_MODE("3 : parse done :            [" << m_type << "]->\"" << m_userFileName << "\"");
	
	// Now we reduce the path with all un-needed ../ and other thinks ...
	// TODO : Do it whith link and the other sub thinks ...
	m_userFileName = SimplifyPathAbstractPath(m_userFileName);
	TK_DBG_MODE("4 : Path simplification :   [" << m_type << "]->\"" << m_userFileName << "\"");
	
	// Now we generate the real FS path:
	GenerateFileSystemPath();
	TK_DBG_MODE("5 : file System Real name : \"" << m_systemFileName << "\"");
	
	// now we get all the right if the file existed:
	UpdateFileSystemProperty();
	TK_DBG_MODE("6 : type :                  [" << m_typeNode << "]  right :" << m_rights);
}


bool DirectCheckFile(etk::UString tmpFileNameDirect, bool checkInAPKIfNeeded=false)
{
	#ifdef __TARGET_OS__Android
	if (true == checkInAPKIfNeeded) {
		if(    NULL != s_APKArchive
		    && true == s_APKArchive->Exist(tmpFileNameDirect) ) {
			return true;
		}
		return false;
	}
	#endif
	// tmpStat Buffer :
	struct stat statProperty;
	if (-1 == stat(tmpFileNameDirect.c_str(), &statProperty)) {
		return false;
	}
	return true;
}

// Now we generate the real FS path:
void etk::FSNode::GenerateFileSystemPath(void)
{
	switch (m_type)
	{
		default:
		case etk::FSN_TYPE_UNKNOW:
			m_systemFileName = baseFolderHome;
			break;
		case etk::FSN_TYPE_DIRECT:
			m_systemFileName = "/";
			break;
		case etk::FSN_TYPE_RELATIF:
			{
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
			}
			break;
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
				//etk::UString myCompleateName=baseFolderData + "/theme/";
				etk::UString themeName("");
				etk::UString basicName(m_userFileName);
				int32_t firstPos = m_userFileName.FindForward(':');
				if (-1 != firstPos) {
					// we find a theme name : We extracted it :
					themeName = m_userFileName.Extract(0, firstPos);
					basicName = m_userFileName.Extract(firstPos+1);
				}
				TK_DBG_MODE(" THEME party : \"" << themeName << "\" => \"" << basicName << "\"");
				themeName = etk::theme::GetName(themeName);
				TK_DBG_MODE("      ==> theme Folder \"" << themeName << "\"");
				// search the corect folder : 
				if (themeName == "") {
					TK_WARNING("no theme name detected : set it to \"default\"");
				} else if (themeName != "default") {
					// Selected theme :
					// check in the user data :
					m_systemFileName = baseFolderDataUser + "theme/" + themeName + "/" + basicName;
					if (true==DirectCheckFile(m_systemFileName)) {
						return;
					}
					// check in the Appl data :
					m_systemFileName = baseFolderData + "theme/" + themeName + "/" + basicName;
					if (true==DirectCheckFile(m_systemFileName, true)) {
						m_type = etk::FSN_TYPE_THEME_DATA;
						return;
					}
				}
				themeName = "default";
				// default theme :
				// check in the user data :
				m_systemFileName = baseFolderDataUser + "theme/" + themeName + "/" + basicName;
				if (true==DirectCheckFile(m_systemFileName)) {
					return;
				}
				// check in the Appl data : In every case we return this one ...
				m_systemFileName = baseFolderData + "theme/" + themeName + "/" + basicName;
				if (true==DirectCheckFile(m_systemFileName, true)) {
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
void etk::FSNode::UpdateFileSystemProperty(void)
{
	// clean general properties : 
	m_rights.Clear();
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
		etk::UString folderName="/";
		if (true==m_systemFileName.EndWith(folderName)) {
			folderName = m_systemFileName;
		} else {
			folderName = m_systemFileName + "/";
		}
		// note : Zip does not support other think than file ...
		m_typeNode=FSN_FILE;
		m_rights.SetUserReadable(true);
		// TODO : Set the time of the file (time program compilation)
		// TODO : Set the USER ID in the group and the user Id ...
		TK_DBG_MODE("File existed ... in APK : '" << m_systemFileName << "'");
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

bool etk::FSNode::SetRight(etk::FSNodeRight newRight)
{
	// TODO : ...
	TK_ERROR("Can not set the new rights ...");
	return false;
}

void etk::FSNode::SetName(const etk::UString& newName)
{
	PrivateSetName(newName);
}

etk::UString etk::FSNode::GetNameFolder(void) const
{
	int32_t lastPos = m_systemFileName.FindBack('/');
	if (-1 != lastPos) {
		return m_systemFileName.Extract(0, lastPos);
	}
	return "";
}
etk::UString etk::FSNode::GetFileSystemName(void) const
{
	return m_systemFileName;
}

etk::UString etk::FSNode::GetName(void) const
{
	etk::UString output;
	switch (m_type)
	{
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


etk::UString etk::FSNode::GetNameFile(void) const
{
	int32_t lastPos = m_systemFileName.FindBack('/');
	if (-1 != lastPos) {
		return m_systemFileName.Extract(lastPos+1);
	}
	return "";
}

etk::UString etk::FSNode::GetRelativeFolder(void) const
{
	etk::UString tmppp = GetName();
	TK_DBG_MODE("get REF folder : " << tmppp );
	switch (m_typeNode)
	{
		case etk::FSN_UNKNOW:
		case etk::FSN_FOLDER:
		case etk::FSN_LINK:
			if (tmppp.EndWith("/") == true) {
				TK_DBG_MODE("     ==> : " << tmppp );
				return tmppp;
			} else {
				etk::UString tmpVal = tmppp;
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
	int32_t lastPos = tmppp.FindBack('/');
	if (-1 != lastPos) {
		TK_DBG_MODE("     ==> : " << tmppp.Extract(0, lastPos+1) );
		return tmppp.Extract(0, lastPos+1);
	}
	lastPos = tmppp.FindBack(':');
	if (-1 != lastPos) {
		TK_DBG_MODE("     ==> : " << tmppp.Extract(0, lastPos+1) );
		return tmppp.Extract(0, lastPos+1);
	}
	TK_DBG_MODE("     ==> : \"\"" );
	return "";
}


bool etk::FSNode::Touch(void)
{
	TK_DEBUG("Touch FILE : " << GetName());
	//just open in write an close ==> this will update the time
	if (false==FileOpenAppend()) {
		return false;
	}
	bool ret = FileClose();
	// update internal time and properties ...
	UpdateFileSystemProperty();
	return ret;
}

bool etk::FSNode::Move(const etk::UString& path)
{
	etk::FSNode tmpDst(path);
	if (tmpDst.Exist()==true) {
		tmpDst.Remove();
	}
	TK_DEBUG("Move : \"" << GetFileSystemName() << "\" ==> \"" << tmpDst.GetFileSystemName() << "\"");
	int32_t res = rename(GetFileSystemName().c_str(), tmpDst.GetFileSystemName().c_str());
	if (res!=0) {
		return false;
	} else {
		return true;
	}
}

bool etk::FSNode::Remove(void)
{
	if (GetNodeType()==etk::FSN_FOLDER) {
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
	UpdateFileSystemProperty();
	return true;
}

uint64_t etk::FSNode::TimeCreated(void) const
{
	return m_timeCreate;
}

etk::UString etk::FSNode::TimeCreatedString(void) const
{
	time_t tmpVal = (int32_t)m_timeCreate;
	etk::UString tmpTime = ctime(&tmpVal);
	if (tmpTime[tmpTime.Size()-1] == '\n') {
		tmpTime.Remove(tmpTime.Size()-1, 1);
	}
	return tmpTime;
}

uint64_t etk::FSNode::TimeModified(void) const
{
	return m_timeModify;
}

etk::UString etk::FSNode::TimeModifiedString(void) const
{
	time_t tmpVal = (int32_t)m_timeModify;
	etk::UString tmpTime = ctime(&tmpVal);
	if (tmpTime[tmpTime.Size()-1] == '\n') {
		tmpTime.Remove(tmpTime.Size()-1, 1);
	}
	return tmpTime;
}

uint64_t etk::FSNode::TimeAccessed(void) const
{
	return m_timeAccess;
}

etk::UString etk::FSNode::TimeAccessedString(void) const
{
	time_t tmpVal = (int32_t)m_timeAccess;
	etk::UString tmpTime = ctime(&tmpVal);
	if (tmpTime[tmpTime.Size()-1] == '\n') {
		tmpTime.Remove(tmpTime.Size()-1, 1);
	}
	return tmpTime;
}

/*
	Operator :
*/
const etk::FSNode& etk::FSNode::operator=  (const etk::FSNode &obj )
{
	if( this != &obj ) // avoid copy to itself
	{
		if(    NULL != m_PointerFile
		#ifdef __TARGET_OS__Android
		    || NULL != m_zipContent
		#endif
		   ) {
			TK_ERROR("Missing close the file : " << *this);
			FileClose();
			m_PointerFile = NULL;
		}
		#ifdef __TARGET_OS__Android
			m_zipContent = NULL;
			m_zipReadingOffset = 0;
		#endif
		etk::UString tmppp = obj.GetName();
		PrivateSetName(tmppp);
	}
	return *this;
}
bool etk::FSNode::operator== (const etk::FSNode &obj ) const
{
	if( this != &obj ) {
		if(    obj.m_userFileName == m_userFileName
		    && obj.m_systemFileName == m_systemFileName
		    && obj.m_type == m_type ) {
			return true;
		} else {
			return false;
		}
		return true;
	}
	return true;
}

bool etk::FSNode::operator!= (const etk::FSNode &obj ) const
{
	return !(*this == obj);
}

etk::CCout& etk::operator <<(etk::CCout &os, const etk::FSNode &obj)
{
	os << "[" << obj.m_type << "]->\"" << obj.m_userFileName << "\"";
	return os;
}

etk::CCout& etk::operator <<(etk::CCout &os, const etk::FSNType_te &obj)
{
	switch (obj)
	{
		case etk::FSN_TYPE_UNKNOW:
			os << "FSN_TYPE_UNKNOW";
			break;
		case etk::FSN_TYPE_DIRECT:
			os << "FSN_TYPE_DIRECT";
			break;
		case etk::FSN_TYPE_RELATIF:
			os << "FSN_TYPE_RELATIF";
			break;
		case etk::FSN_TYPE_HOME:
			os << "FSN_TYPE_HOME";
			break;
		case etk::FSN_TYPE_DATA:
			os << "FSN_TYPE_DATA";
			break;
		case etk::FSN_TYPE_USER_DATA:
			os << "FSN_TYPE_USER_DATA";
			break;
		case etk::FSN_TYPE_CACHE:
			os << "FSN_TYPE_CACHE";
			break;
		case etk::FSN_TYPE_THEME:
			os << "FSN_TYPE_THEME";
			break;
		case etk::FSN_TYPE_THEME_DATA:
			os << "FSN_TYPE_THEME(DATA)";
			break;
		default:
			os << "FSN_TYPE_????";
			break;
	}
	return os;
}

etk::CCout& etk::operator <<(etk::CCout &os, const etk::typeNode_te &obj)
{
	switch (obj)
	{
		case etk::FSN_UNKNOW:
			os << "FSN_UNKNOW";
			break;
		case etk::FSN_BLOCK:
			os << "FSN_BLOCK";
			break;
		case etk::FSN_CHARACTER:
			os << "FSN_CHARACTER";
			break;
		case etk::FSN_FOLDER:
			os << "FSN_FOLDER";
			break;
		case etk::FSN_FIFO:
			os << "FSN_FIFO";
			break;
		case etk::FSN_LINK:
			os << "FSN_LINK";
			break;
		case etk::FSN_FILE:
			os << "FSN_FILE";
			break;
		case etk::FSN_SOCKET:
			os << "FSN_SOCKET";
			break;
		default:
			os << "FSN_????";
			break;
	}
	return os;
}

/*
	Folder specific :
*/
int64_t etk::FSNode::FolderCount(void)
{
	int64_t counter=0;
	DIR *dir = NULL;
	struct dirent *ent = NULL;
	dir = opendir(m_systemFileName.c_str());
	if (dir != NULL) {
		// for each element in the drectory...
		while ((ent = readdir(dir)) != NULL) {
			etk::UString tmpName(ent->d_name);
			if(    tmpName=="." 
			    || tmpName==".." ) {
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
etk::Vector<etk::FSNode *> etk::FSNode::FolderGetSubList(bool showHidenFile, bool getFolderAndOther, bool getFile, bool temporaryFile)
{
	etk::Vector<etk::FSNode*> tmpp;
	if (m_typeNode != etk::FSN_FOLDER ) {
		return tmpp;
	}
	
	// regenerate the next list :
	etk::FSNode * tmpEmement;
	DIR *dir = NULL;
	struct dirent *ent = NULL;
	dir = opendir(m_systemFileName.c_str());
	if (dir != NULL) {
		// for each element in the drectory...
		while ((ent = readdir(dir)) != NULL) {
			etk::UString tmpName(ent->d_name);
			TK_VERBOSE(" search in folder\"" << tmpName << "\"");
			if(    tmpName=="." 
			    || tmpName==".." ) {
				// do nothing ...
				continue;
			}
			if(    false == tmpName.StartWith(".")
			    || true == showHidenFile) {
				tmpEmement = new etk::FSNode(GetRelativeFolder()+tmpName);
				if (NULL == tmpEmement) {
					TK_ERROR("allocation error ... of ewol::FSNode");
					continue;
				}
				if(tmpEmement->GetNodeType() == etk::FSN_FILE) {
					if (true == getFile) {
						tmpp.PushBack(tmpEmement);
					} else {
						delete(tmpEmement);
						tmpEmement = NULL;
					}
				} else if (getFolderAndOther) {
					tmpp.PushBack(tmpEmement);
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
	SortElementList(tmpp);
	
	return tmpp;
}
etk::FSNode etk::FSNode::FolderGetParent(void)
{
	etk::FSNode tmpp;
	return tmpp;
}

void etk::FSNode::FolderGetRecursiveFiles(etk::Vector<etk::UString>& output, bool recursiveEnable)
{
	#ifdef __TARGET_OS__Android
	if(    m_type == etk::FSN_TYPE_DATA
	    || m_type == etk::FSN_TYPE_THEME_DATA) {
		etk::UString assetsName = "assets/";
		etk::UString FolderName = GetNameFolder();
		if (s_APKArchive==NULL) {
			return;
		}
		for (int iii=0; iii<s_APKArchive->Size(); iii++) {
			etk::UString filename = s_APKArchive->GetName(iii);
			if (filename.StartWith(FolderName) == true) {
				etk::UString tmpString;
				if(m_type == etk::FSN_TYPE_DATA) {
					tmpString = "DATA:";
				} else {
					tmpString = "THEME:";
				}
				if (true == filename.StartWith(assetsName)) {
					filename.Remove(0,assetsName.Size());
				}
				tmpString += filename;
				output.PushBack(tmpString);
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
			etk::UString tmpName(ent->d_name);
			if(    tmpName=="." 
			    || tmpName==".." ) {
				// do nothing ...
				continue;
			}
			//TK_DEBUG(" find : " << ent->d_name << " ==> " << (GetRelativeFolder()+tmpName));
			tmpEmement = new etk::FSNode(GetRelativeFolder()+tmpName);
			if (NULL != tmpEmement) {
				if(tmpEmement->GetNodeType() == etk::FSN_FILE) {
					etk::UString tmpVal = tmpEmement->GetName();
					output.PushBack(tmpVal);
				}
				if(tmpEmement->GetNodeType() == etk::FSN_FOLDER) {
					if (true==recursiveEnable) {
						tmpEmement->FolderGetRecursiveFiles(output);
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

/*
	File Specific :
*/
bool etk::FSNode::FileHasExtention(void)
{
	int32_t lastPos = m_userFileName.FindBack('.');
	if(    -1 != lastPos                       // not find the .
	    && 0  != lastPos                       // Find a . at the fist position .jdlskjdfklj ==> hiden file
	    && m_userFileName.Size() != lastPos ) // Remove file ended with .
	{
		return true;
	} else {
		return false;
	}
}

etk::UString etk::FSNode::FileGetExtention(void)
{
	etk::UString tmpExt = "";
	int32_t lastPos = m_userFileName.FindBack('.');
	if(    -1 != lastPos                       // not find the .
	    && 0  != lastPos                       // Find a . at the fist position .jdlskjdfklj ==> hiden file
	    && m_userFileName.Size() != lastPos ) // Remove file ended with .
	{
		// Get the FileName
		tmpExt = m_userFileName.Extract(lastPos+1);
	}
	return tmpExt;
}

uint64_t etk::FSNode::FileSize(void)
{
	if (etk::FSN_FILE != m_typeNode) {
		TK_ERROR("Request size of a non file node : " << m_typeNode);
		return 0;
	}
	#ifdef __TARGET_OS__Android
	if(    etk::FSN_TYPE_DATA == m_type
	    || etk::FSN_TYPE_THEME_DATA == m_type) {
		if (true == LoadDataZip()) {
			return m_zipContent->GetTheoricSize();
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
	TK_INFO(" file size : " << (int64_t)statProperty.st_size << " bytes");
	if ((uint64_t)statProperty.st_size<=0) {
		return 0;
	}
	return (uint64_t)statProperty.st_size;
}


bool etk::FSNode::FileOpenRead(void)
{
	#ifdef __TARGET_OS__Android
	if(    etk::FSN_TYPE_DATA == m_type
	    || etk::FSN_TYPE_THEME_DATA == m_type) {
		return LoadDataZip();
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
bool etk::FSNode::FileOpenWrite(void)
{
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
	FSNODE_LOCAL_mkPath(GetNameFolder().c_str() , 0777);
	TK_VERBOSE(" write file : " << m_systemFileName);
	m_PointerFile=fopen(m_systemFileName.c_str(),"wb");
	if(NULL == m_PointerFile) {
		TK_ERROR("Can not find the file " << *this);
		return false;
	}
	return true;
}
bool etk::FSNode::FileOpenAppend(void)
{
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
	FSNODE_LOCAL_mkPath(GetNameFolder().c_str() , 0777);
	
	TK_VERBOSE(" append file : " << m_systemFileName);
	
	m_PointerFile=fopen(m_systemFileName.c_str(),"ab");
	if(NULL == m_PointerFile) {
		TK_ERROR("Can not find the file " << *this);
		return false;
	}
	return true;
}
bool etk::FSNode::FileClose(void)
{
	#ifdef __TARGET_OS__Android
	if(    etk::FSN_TYPE_DATA == m_type
	    || etk::FSN_TYPE_THEME_DATA == m_type) {
		if (NULL == m_zipContent) {
			TK_CRITICAL("File Already closed : " << *this);
			return false;
		}
		m_zipContent = NULL;
		m_zipReadingOffset = 0;
		return true;
	}
	#endif
	if (NULL == m_PointerFile) {
		TK_CRITICAL("File Already closed : " << *this);
		return false;
	}
	fclose(m_PointerFile);
	m_PointerFile = NULL;
	return true;
}
char* etk::FSNode::FileGets(char * elementLine, int64_t maxData)
{
	memset(elementLine, 0, maxData);
	#ifdef __TARGET_OS__Android
	char * element = elementLine;
	int64_t outSize = 0;
	if(    etk::FSN_TYPE_DATA == m_type
	    || etk::FSN_TYPE_THEME_DATA == m_type) {//char * tmpData = internalDataFiles[iii].data + m_readingOffset;
		if (NULL == m_zipContent) {
			element[0] = '\0';
			return NULL;
		}
		if (m_zipReadingOffset>m_zipContent->Size()) {
			element[0] = '\0';
			return NULL;
		}
		while (((char*)m_zipContent->Data())[m_zipReadingOffset] != '\0') {
			if(    ((char*)m_zipContent->Data())[m_zipReadingOffset] == '\n'
			    || ((char*)m_zipContent->Data())[m_zipReadingOffset] == '\r')
			{
				*element = ((char*)m_zipContent->Data())[m_zipReadingOffset];
				element++;
				m_zipReadingOffset++;
				*element = '\0';
				return elementLine;
			}
			*element = ((char*)m_zipContent->Data())[m_zipReadingOffset];
			element++;
			m_zipReadingOffset++;
			if (m_zipReadingOffset>m_zipContent->Size()) {
				*element = '\0';
				return elementLine;
			}
			// check maxData Size ...
			if (outSize>=maxData-1) {
				*element = '\0';
				return elementLine;
			}
			outSize++;
		}
		if (outSize==0) {
			return NULL;
		} else {
			// send last line
			return elementLine;
		}
	}
	#endif
	return fgets(elementLine, maxData, m_PointerFile);
}
int64_t etk::FSNode::FileRead(void * data, int64_t blockSize, int64_t nbBlock)
{
	#ifdef __TARGET_OS__Android
	if(    etk::FSN_TYPE_DATA == m_type
	    || etk::FSN_TYPE_THEME_DATA == m_type) {
		if (NULL == m_zipContent) {
			((char*)data)[0] = '\0';
			return 0;
		}
		int32_t dataToRead = blockSize * nbBlock;
		if (dataToRead + m_zipReadingOffset > m_zipContent->Size()) {
			nbBlock = ((m_zipContent->Size() - m_zipReadingOffset) / blockSize);
			dataToRead = blockSize * nbBlock;
		}
		memcpy(data, &((char*)m_zipContent->Data())[m_zipReadingOffset], dataToRead);
		m_zipReadingOffset += dataToRead;
		return nbBlock;
	}
	#endif
	return fread(data, blockSize, nbBlock, m_PointerFile);
}
int64_t etk::FSNode::FileWrite(void * data, int64_t blockSize, int64_t nbBlock)
{
	#ifdef __TARGET_OS__Android
	if(    etk::FSN_TYPE_DATA == m_type
	    || etk::FSN_TYPE_THEME_DATA == m_type) {
		TK_CRITICAL("Can not write on data inside APK : " << *this);
		return 0;
	}
	#endif
	return fwrite(data, blockSize, nbBlock, m_PointerFile);
}
bool etk::FSNode::FileSeek(long int offset, etk::seekNode_te origin)
{
	#ifdef __TARGET_OS__Android
	if(    etk::FSN_TYPE_DATA == m_type
	    || etk::FSN_TYPE_THEME_DATA == m_type) {
		if (NULL == m_zipContent) {
			return false;
		}
		int32_t positionEnd = 0;
		switch(origin) {
			case etk::FSN_SEEK_END:
				positionEnd = m_zipContent->Size();
				break;
			case etk::FSN_SEEK_CURRENT:
				positionEnd = m_zipReadingOffset;
				break;
			default:
				positionEnd = 0;
				break;
		}
		positionEnd += offset;
		if (positionEnd < 0) {
			positionEnd = 0;
		} else if (positionEnd > m_zipContent->Size()) {
			positionEnd = m_zipContent->Size();
		}
		m_zipReadingOffset = positionEnd;
		return true;
	}
	#endif
	int originFS = 0;
	switch(origin) {
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
	fseek(m_PointerFile, offset, originFS);
	if(ferror(m_PointerFile)) {
		return false;
	} else {
		return true;
	}
}

void etk::FSNode::FileFlush(void)
{
	#ifdef __TARGET_OS__Android
	if(    etk::FSN_TYPE_DATA == m_type
	    || etk::FSN_TYPE_THEME_DATA == m_type) {
		return;
	}
	#endif
	if (NULL != m_PointerFile) {
		fflush(m_PointerFile);
	}
}




// TODO : Add an INIT to reset all allocated parameter :

class tmpThemeElement
{
	public:
		etk::UString refName;
		etk::UString folderName;
};

static etk::Vector<tmpThemeElement*> g_listTheme;

// set the Folder of a subset of a theme ...
void etk::theme::SetName(etk::UString refName, etk::UString folderName)
{
	for(int32_t iii=0; iii<g_listTheme.Size(); iii++) {
		if (NULL != g_listTheme[iii]) {
			if (g_listTheme[iii]->refName==refName) {
				g_listTheme[iii]->folderName = folderName;
				// action done
				return;
			}
		}
	}
	// we did not find it ...
	tmpThemeElement* tmpp = new tmpThemeElement();
	if (NULL==tmpp) {
		TK_ERROR("pb to add a reference theme");
		return;
	}
	tmpp->refName = refName;
	tmpp->folderName = folderName;
	g_listTheme.PushBack(tmpp);
}

// get the folder from a Reference theme
etk::UString etk::theme::GetName(etk::UString refName)
{
	for(int32_t iii=0; iii<g_listTheme.Size(); iii++) {
		if (NULL != g_listTheme[iii]) {
			if (g_listTheme[iii]->refName==refName) {
				return g_listTheme[iii]->folderName;
			}
		}
	}
	// We did not find the theme
	return refName;
}

// get the list of all the theme folder availlable in the user Home/appl
etk::Vector<etk::UString> etk::theme::List(void)
{
	etk::Vector<etk::UString> tmpp;
	return tmpp;
	// TODO :
}


/* --------------------------------------------------------------------------
 * 
 *  Simple direct wrapper on the FileSystem node access :
 * 
 * -------------------------------------------------------------------------- */
bool etk::FSNodeRemove(const etk::UString& path)
{
	etk::FSNode tmpNode(path);
	if (false==tmpNode.Exist()) {
		return false;
	}
	return tmpNode.Remove();
}

int64_t etk::FSNodeGetCount(const etk::UString& path)
{
	etk::FSNode tmpNode(path);
	if (false==tmpNode.Exist()) {
		return -1;
	}
	return tmpNode.FolderCount();
}

bool etk::FSNodeCreate(const etk::UString& path, etk::FSNodeRight right, etk::typeNode_te type)
{
	// TODO :
	return false;
}

bool etk::FSNodeExist(const etk::UString& path)
{
	etk::FSNode tmpNode(path);
	return tmpNode.Exist();
}

bool etk::FSNodeMove(const etk::UString& path1, const etk::UString& path2)
{
	etk::FSNode tmpNode(path1);
	if (false==tmpNode.Exist()) {
		TK_DEBUG("try to move un existant file \"" << path1 << "\"");
		return false;
	}
	// no check error in every case
	(void)etk::FSNodeRemove(path2);
	//move the node
	return tmpNode.Move(path2);
}

etk::FSNodeRight etk::FSNodeGetRight(const etk::UString& path)
{
	etk::FSNode tmpNode(path);
	return tmpNode.GetRight();
}

etk::typeNode_te etk::FSNodeGetType(const etk::UString& path)
{
	etk::FSNode tmpNode(path);
	return tmpNode.GetNodeType();
}

uint64_t etk::FSNodeGetTimeCreated(const etk::UString& path)
{
	etk::FSNode tmpNode(path);
	return tmpNode.TimeCreated();
}

uint64_t etk::FSNodeGetTimeModified(const etk::UString& path)
{
	etk::FSNode tmpNode(path);
	return tmpNode.TimeModified();
}

uint64_t etk::FSNodeGetTimeAccessed(const etk::UString& path)
{
	etk::FSNode tmpNode(path);
	return tmpNode.TimeAccessed();
}

bool etk::FSNodeTouch(const etk::UString& path)
{
	etk::FSNode tmpNode(path);
	return tmpNode.Touch();
}

bool etk::FSNodeEcho(const etk::UString& path, const etk::UString& dataTowrite)
{
	etk::FSNode tmpNode(path);
	if (false==tmpNode.Exist()) {
		return false;
	}
	if (FSN_FOLDER==tmpNode.GetNodeType()) {
		return false;
	}
	if (false==tmpNode.FileOpenWrite()) {
		return false;
	}
	// convert in UTF8 :
	etk::Char tmpChar = dataTowrite.c_str();
	int32_t nbChar = strlen(tmpChar);
	if (nbChar != tmpNode.FileWrite(tmpChar, 1, nbChar)) {
		tmpNode.FileClose();
		return false;
	}
	return tmpNode.FileClose();
}

bool etk::FSNodeEchoAdd(const etk::UString& path, const etk::UString& dataTowrite)
{
	etk::FSNode tmpNode(path);
	if (false==tmpNode.Exist()) {
		return false;
	}
	if (FSN_FOLDER==tmpNode.GetNodeType()) {
		return false;
	}
	if (false==tmpNode.FileOpenAppend()) {
		return false;
	}
	// convert in UTF8 :
	etk::Char tmpChar = dataTowrite.c_str();
	int32_t nbChar = strlen(tmpChar);
	if (nbChar != tmpNode.FileWrite(tmpChar, 1, nbChar)) {
		tmpNode.FileClose();
		return false;
	}
	return tmpNode.FileClose();
}

void etk::FSNodeHistory(const etk::UString& _path, int32_t _historyCount)
{
	// step 1 : Move the file to prevent writing error
	//Get the first oldest save :
	for (int32_t iii=_historyCount-1; iii>0 ; iii--) {
		if (true==etk::FSNodeExist(_path+"-"+iii) ) {
			etk::FSNodeMove(_path+"-"+iii,_path+"-"+(iii+1));
		}
	}
	if (true==etk::FSNodeExist(_path) ) {
		etk::FSNodeMove(_path,_path+"-1");
	}
}
