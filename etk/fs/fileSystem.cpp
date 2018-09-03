/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#include <etk/fs/fileSystem.hpp>
#include <etk/debug.hpp>

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
#include <unistd.h>
#include <stdlib.h>

#include <etk/io/File.hpp>
#include <etk/io/SeekMode.hpp>

namespace etk {
	static int32_t mkdir(const char* _path, mode_t _mode) {
		struct stat st;
		int32_t status = 0;
		if (stat(_path, &st) != 0) {
			/* Directory does not exist. EEXIST for race condition */
			#ifdef __TARGET_OS__Windows
				if(0!=::mkdir(_path)
			#else
				if(0!=::mkdir(_path, _mode)
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
	static int32_t mkPath(const char* _path, mode_t _mode) {
		char *pp;
		char *sp;
		int status;
		char *copypath = strdup(_path);
		if (copypath == null) {
			return -1;
		}
		status = 0;
		pp = copypath;
		while (status == 0 && (sp = strchr(pp, '/')) != 0) {
			if (sp != pp) {
				/* Neither root nor double slash in path */
				*sp = '\0';
				status = etk::mkdir(copypath, _mode);
				*sp = '/';
			}
			pp = sp + 1;
		}
		if (status == 0) {
			status = etk::mkdir(_path, _mode);
		}
		free(copypath);
		return (status);
	}
}

bool etk::fs::copy(const etk::Path& _path1, const etk::Path& _path2) {
	return false;
}

bool etk::fs::copyDirectory(const etk::Path& _path1, const etk::Path& _path2, bool _recursive) {
	return false;
}

bool etk::fs::copyFile(const etk::Path& _path1, const etk::Path& _path2) {
	return false;
}


bool etk::fs::move(const etk::Path& _path1, const etk::Path& _path2) {
	if (etk::fs::exist(_path2) == true) {
		remove(_path2);
	}
	TK_DEBUG("Move : \"" << _path1 << "\" ==> \"" << _path2 << "\"");
	// create path to be sure it exist ...
	TK_VERBOSE("create path: '" << _path2.getParent() << "'");
	etk::mkPath(_path2.getParent().getString().c_str() , 0755);
	int32_t res = ::rename(_path1.getString().c_str(), _path2.getString().c_str());
	if (res!=0) {
		TK_ERROR("Can not move the file: '" << _path1 << "' ==> '" << _path2 << "'");
		return false;
	}
	return true;
}

bool etk::fs::moveDirectory(const etk::Path& _path1, const etk::Path& _path2) {
	return false;
}

bool etk::fs::moveFile(const etk::Path& _path1, const etk::Path& _path2) {
	return false;
}


bool etk::fs::remove(const etk::Path& _path) {
	if (etk::fs::isDirectory(_path) == true) {
		return etk::fs::removeDirectory(_path);
	}
	return etk::fs::removeFile(_path);
}

bool etk::fs::removeDirectory(const etk::Path& _path) {
	if( 0 != ::rmdir(_path.getString().c_str()) ) {
		if (ENOTEMPTY == errno) {
			TK_ERROR("The Directory is not empty...");
		}
		return false;
	}
	return true;
}

bool etk::fs::removeFile(const etk::Path& _path) {
	if (0 != unlink(_path.getString().c_str()) ) {
		return false;
	}
	return true;
}

bool etk::fs::touch(const etk::Path& _path) {
	TK_DEBUG("Touch FILE : " << _path);
	//just open in write an close ==> this will update the time
	etk::io::File file{_path};
	if (file.open(etk::io::OpenMode::Append) == false) {
		return false;
	}
	return file.close();
}

bool etk::fs::exist(const etk::Path& _path) {
	struct stat st;
	int32_t status = 0;
	if (stat(_path.getString().c_str(), &st) != 0) {
		return false;
	}
	return true;
}

uint64_t etk::fs::fileSize(const etk::Path& _path) {
	// Note : this is a proper methode to get the file size for Big files ... otherwithe the size is limited at 2^31 bytes
	// tmpStat Buffer :
	struct stat statProperty;
	if (stat(_path.getString().c_str(), &statProperty) == -1) {
		//Normal case when the file does not exist ... ==> the it was in unknow mode ...
		return 0;
	}
	TK_VERBOSE(" file size : " << (int64_t)statProperty.st_size << " bytes");
	if ((uint64_t)statProperty.st_size <= 0) {
		return 0;
	}
	return (uint64_t)statProperty.st_size;
}


bool etk::fs::isDirectory(const etk::Path& _path) {
	struct stat st;
	int32_t status = 0;
	if (stat(_path.getString().c_str(), &st) != 0) {
		return false;
	} else if (!S_ISDIR(st.st_mode)) {
		return false;
	}
	return true;
}

bool etk::fs::isFile(const etk::Path& _path) {
	struct stat st;
	int32_t status = 0;
	if (stat(_path.getString().c_str(), &st) != 0) {
		return false;
	} else if (!S_ISREG(st.st_mode)) {
		return false;
	}
	return true;
}

bool etk::fs::isSymLink(const etk::Path& _path) {
	struct stat st;
	int32_t status = 0;
	if (stat(_path.getString().c_str(), &st) != 0) {
		return false;
	} else if (!S_ISLNK(st.st_mode)) {
		return false;
	}
	return true;
}


etk::fs::Permissions etk::fs::getPermission(const etk::Path& _path) {
	etk::fs::Permissions permissions;
	// tmpStat Buffer :
	struct stat statProperty;
	if (-1 == stat(_path.getString().c_str(), &statProperty)) {
		//Normal case when the file does not exist ... ==> the it was in unknow mode ...
		return permissions;
	}
	permissions = statProperty.st_mode;
	return permissions;
}


etk::String etk::fs::getRelativeString(const etk::Path& _path) {
	return _path.getRelative();
}

etk::String etk::fs::getAbsoluteString(const etk::Path& _path) {
	return _path.getAbsolute();
}

etk::String etk::fs::getSystemString(const etk::Path& _path) {
	return _path.getNative();
}

etk::String etk::fs::getMimeType(const etk::Path& _path) {
	return "*";
}

etk::Path etk::fs::getTemporaryPath() {
	return etk::Path{"/tmp/"};
}

etk::String etk::fs::getHomePathString() {
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

etk::Path etk::fs::getHomePath() {
	return etk::Path(etk::fs::getHomePathString());
}

etk::Path etk::fs::getExecutionPath() {
	static etk::Path g_path;
	if (g_path.getString() != "") {
		return g_path;
	}
	char cCurrentPath[FILENAME_MAX];
	if (!getcwd(cCurrentPath, FILENAME_MAX)) {
		g_path = ".";
	} else {
		cCurrentPath[FILENAME_MAX - 1] = '\0';
		if (cCurrentPath[0] == '/') {
			g_path = cCurrentPath;
		} else {
			g_path = etk::String("/") + cCurrentPath;
		}
	}
	return g_path;
}

etk::Path etk::fs::getBinaryPath() {
	
}

etk::Path etk::fs::getDataPath() {
	
}


uint64_t etk::fs::getCreateTime(const etk::Path& _path) {
	
}

uint64_t etk::fs::getModifyTime(const etk::Path& _path) {
	
}

uint64_t etk::fs::getAccessTime(const etk::Path& _path) {
	
}

uint32_t etk::fs::getIdOwner(const etk::Path& _path) {
	
}

uint32_t etk::fs::getIdGroup(const etk::Path& _path) {
	
}


