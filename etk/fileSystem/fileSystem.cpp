/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#include <etk/fileSystem/fileSystem.hpp>
#include <etk/log.hpp>

#ifdef __TARGET_OS__Windows
	#include <tchar.h>
	#include <windows.h>
#endif

extern "C" {
	// file browsing ...
	#include <dirent.h>
	#include <sys/stat.h>
	#include <errno.h>
}

void etk::fileSystem::copy(const etk::Path& _path1, const etk::Path& _path2) {
	
}

void etk::fileSystem::copyDirectory(const etk::Path& _path1, const etk::Path& _path2, bool _recursive) {
	
}

void etk::fileSystem::copyFile(const etk::Path& _path1, const etk::Path& _path2) {
	
}


void etk::fileSystem::move(const etk::Path& _path1, const etk::Path& _path2) {
	
}

void etk::fileSystem::moveDirectory(const etk::Path& _path1, const etk::Path& _path2) {
	
}

void etk::fileSystem::moveFile(const etk::Path& _path1, const etk::Path& _path2) {
	
}


void etk::fileSystem::remove(const etk::Path& _path) {
	
}

void etk::fileSystem::removeDirectory(const etk::Path& _path) {
	
}

void etk::fileSystem::removeFile(const etk::Path& _path) {
	
}


bool etk::fileSystem::exit(const etk::Path& _path) {
	struct stat st;
	int32_t status = 0;
	if (stat(_path.get().c_str(), &st) != 0) {
		return false;
	}
	return true;
}

uint64_t etk::fileSystem::fileSize(const etk::Path& _path) {
	// Note : this is a proper methode to get the file size for Big files ... otherwithe the size is limited at 2^31 bytes
	// tmpStat Buffer :
	struct stat statProperty;
	if (stat(_path.get().c_str(), &statProperty) == -1) {
		//Normal case when the file does not exist ... ==> the it was in unknow mode ...
		return 0;
	}
	TK_VERBOSE(" file size : " << (int64_t)statProperty.st_size << " bytes");
	if ((uint64_t)statProperty.st_size <= 0) {
		return 0;
	}
	return (uint64_t)statProperty.st_size;
}


bool etk::fileSystem::isDirectory(const etk::Path& _path) {
	struct stat st;
	int32_t status = 0;
	if (stat(_path.get().c_str(), &st) != 0) {
		return false;
	} else if (!S_ISDIR(st.st_mode)) {
		return false;
	}
	return true;
}

bool etk::fileSystem::isFile(const etk::Path& _path) {
	struct stat st;
	int32_t status = 0;
	if (stat(_path.get().c_str(), &st) != 0) {
		return false;
	} else if (!S_ISREG(st.st_mode)) {
		return false;
	}
	return true;
}

bool etk::fileSystem::isSymLink(const etk::Path& _path) {
	struct stat st;
	int32_t status = 0;
	if (stat(_path.get().c_str(), &st) != 0) {
		return false;
	} else if (!S_ISLNK(st.st_mode)) {
		return false;
	}
	return true;
}


etk::filesystem::Permissions etk::fileSystem::getPermission(const etk::Path& _path) {
	etk::filesystem::Permissions permissions;
	// tmpStat Buffer :
	struct stat statProperty;
	if (-1 == stat(m_systemFileName.c_str(), &statProperty)) {
		//Normal case when the file does not exist ... ==> the it was in unknow mode ...
		return permissions;
	}
	permissions = statProperty.st_mode;
	return permissions;
}


etk::String etk::fileSystem::getRelativeString(const etk::Path& _path) {
	return _path.getRelative();
}

etk::String etk::fileSystem::getDecoratedString(const etk::Path& _path) {
	return _path.getDecorated();
}

etk::String etk::fileSystem::getAbsoluteString(const etk::Path& _path) {
	return _path.get();
}

etk::String etk::fileSystem::getSystemString(const etk::Path& _path) {
	return _path.getNative();
}


etk::String etk::fileSystem::getMimeType(const etk::Path& _path) {
	
}


etk::Path etk::fileSystem::getTemporaryPath() {
	
}


static bool initHomeFolder() {
	static bool isInit = false;
	if (isInit == false) {
		TK_DBG_MODE("Real Ini Home folder:");
		char * basicPath = getenv("HOME");
		if (basicPath == null) {
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
		TK_DBG_MODE("    home=:" << baseFolderHome);
		isInit = true;
	}
	return isInit;
}

etk::String etk::fileSystem::getHomePathString() {
	static bool isInit = false;
	static etk::String data = "";
	if (isInit == false) {
		char * basicPath = getenv("HOME");
		if (basicPath == null) {
			TK_WARNING("ERROR while trying to get the path of the home folder");
			#if defined(__TARGET_OS__Windows)
				data = "c:/";
			#elif defined(__TARGET_OS__Android)
				data = "/sdcard";
			#else
				data = "~";
			#endif
		} else {
			data = basicPath;
		}
		isInit = true;
	}
	return data;
}
etk::Path etk::fileSystem::getHomePath() {
	return etk::Path(etk::fileSystem::Type::Home, "");
}

etk::Path etk::fileSystem::getExecutionPath() {
	
}

etk::Path etk::fileSystem::getBinaryPath() {
	
}

etk::Path etk::fileSystem::getDataPath() {
	
}


uint64_t etk::fileSystem::getCreateTime(const etk::Path& _path) {
	
}

uint64_t etk::fileSystem::getModifyTime(const etk::Path& _path) {
	
}

uint64_t etk::fileSystem::getAccessTime(const etk::Path& _path) {
	
}

uint32_t etk::fileSystem::getIdOwner(const etk::Path& _path) {
	
}

uint32_t etk::fileSystem::getIdGroup(const etk::Path& _path) {
	
}


