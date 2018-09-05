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
#elif defined(__TARGET_OS__MacOs) || defined(__TARGET_OS__IOs)
	#include <cstring>
	#include <mach-o/dyld.h>
#endif

extern "C" {
	// file browsing ...
	#include <dirent.h>
	#include <sys/stat.h>
	#include <errno.h>
	#include <string.h>
}
#include <unistd.h>
#include <stdlib.h>

#include <etk/io/File.hpp>
#include <etk/io/SeekMode.hpp>

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
	etk::fs::makeDirectories(_path2.getParent());
	int32_t res = ::rename(_path1.getString().c_str(), _path2.getString().c_str());
	if (res!=0) {
		TK_ERROR("Can not move the file: '" << _path1 << "' ==> '" << _path2 << "'");
		return false;
	}
	return true;
}

bool etk::fs::moveDirectory(const etk::Path& _path1, const etk::Path& _path2) {
	return etk::fs::move(_path1, _path2);
}

bool etk::fs::moveFile(const etk::Path& _path1, const etk::Path& _path2) {
	return etk::fs::move(_path1, _path2);
}

namespace detail {
	bool removeDirectories(const etk::Path& _path, bool _recursive);
	bool removes(const etk::Path& _path, bool _recursive) {
		TK_VERBOSE("remove: " << _path);
		if (etk::fs::isDirectory(_path) == true) {
			return detail::removeDirectories(_path, _recursive);
		}
		return etk::fs::removeFile(_path);
	}
	bool removeDirectories(const etk::Path& _path, bool _recursive) {
		TK_VERBOSE("remove Directory: " << _path);
		if (_recursive == true) {
			etk::Vector<etk::Path> elements = etk::fs::list(_path);
			for (auto& it : elements) {
				detail::removes(it, _recursive);
			}
		}
		if ( 0 != ::rmdir(_path.getString().c_str()) ) {
			if (ENOTEMPTY == errno) {
				TK_ERROR("The Directory is not empty...");
			}
			return false;
		}
		return true;
	}
}

bool etk::fs::remove(const etk::Path& _path) {
	return detail::removes(_path, false);
}

bool etk::fs::removes(const etk::Path& _path) {
	return detail::removes(_path, true);
}

bool etk::fs::removeDirectory(const etk::Path& _path) {
	return detail::removeDirectories(_path, false);
}

bool etk::fs::removeDirectories(const etk::Path& _path) {
	return detail::removeDirectories(_path, true);
}

bool etk::fs::removeFile(const etk::Path& _path) {
	TK_VERBOSE("remove File: " << _path);
	if (0 != unlink(_path.getString().c_str()) ) {
		return false;
	}
	return true;
}

bool etk::fs::makeDirectory(const etk::Path& _path, etk::fs::Permissions _permission) {
	TK_VERBOSE("Make directory : " << _path << " perm: " << _permission);
	if (etk::fs::exist(_path) == true) {
		return true;
	}
	#ifdef __TARGET_OS__Windows
		if (::mkdir(_path.getString().c_str()) != 0
		     && errno != EEXIST) {
			return false;
		}
	#else
		mode_t mode = _permission.getRightValue();
		if (    ::mkdir(_path.getString().c_str(), mode) != 0
		     && errno != EEXIST ) {
			return false;
		}
	#endif
	return true;
}

bool etk::fs::makeDirectories(const etk::Path& _path, etk::fs::Permissions _permission) {
	TK_VERBOSE("Make dirrectories: " << _path << " perm: " << _permission);
	if (etk::fs::exist(_path) == true) {
		return true;
	}
	auto elements = _path.getString().split('/');
	etk::Path pathToCreate;
	if (elements[0].size() == 0) {
		elements.popFront();
		pathToCreate = etk::Path("/");
	}
	for (auto& it: elements) {
		pathToCreate /= it;
		if (etk::fs::makeDirectory(pathToCreate, _permission) == false) {
			return false;
		}
	}
	return true;
}

bool etk::fs::touch(const etk::Path& _path) {
	TK_DEBUG("Touch FILE : " << _path);
	if (etk::fs::exist(_path) == true ) {
		//just open in write an close ==> this will update the time
		etk::io::File file{_path};
		if (file.open(etk::io::OpenMode::Append) == false) {
			return false;
		}
		return file.close();
	}
	// Write the file with nothing inside...
	etk::io::File file{_path};
	if (file.open(etk::io::OpenMode::Write) == false) {
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

etk::String etk::fs::getNativeString(const etk::Path& _path) {
	return _path.getNative();
}

/*
etk::String etk::fs::getMimeType(const etk::Path& _path) {
	return "*";
}
*/

etk::Path etk::fs::getTemporaryPath() {
	static char const *folder = null;
	if (folder == null) {
		#ifdef __TARGET_OS__Windows
			folder = GetTempPath();
		#else
			folder = getenv("TMPDIR");
			if (folder == 0) {
				folder = getenv("TMP");
			}
			if (folder == 0) {
				folder = getenv("TEMP");
			}
			if (folder == 0) {
				folder = getenv("TEMPDIR");
			}
			#ifdef __TARGET_OS__Android
				if (folder == 0) {
					folder = "/data/local/tmp";
				}
			#else
				if (folder == 0) {
					folder = "/tmp";
				}
			#endif
		#endif
	}
	return etk::Path{folder};
}

namespace detail {
	etk::Path getTemporaryProcessPath(const etk::String& _patern) {
		char tmpName[1024];
		strcpy(tmpName, _patern.c_str());
		mktemp(tmpName);
		return etk::fs::getTemporaryPath() / tmpName;
	}
}

etk::Path etk::fs::getTemporaryProcessPath() {
	static etk::Path out = detail::getTemporaryProcessPath("etk.process.XXXXXX");
	return out;
}

etk::Path etk::fs::getTemporaryRandomPath() {
	return detail::getTemporaryProcessPath("etk.random.XXXXXX");
}

static etk::String getHomePathString() {
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
	return etk::Path(getHomePathString());
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

etk::Path etk::fs::realPath(const etk::Path& _path) {
	#if ! defined(__TARGET_OS__Windows)
		char buf[8192];
		memset(buf, 0, 8192);
		char *res = realpath(_path.getString().c_str(), buf);
		if (res) {
			return etk::Path{buf};
		}
	#endif
	return _path;
}

etk::Path etk::fs::getBinaryPath() {
	static etk::Path out;
	if ( out.getString() == "" ) {
		#if defined(__TARGET_OS__Windows) || defined(__TARGET_OS__MacOs) || defined(__TARGET_OS__IOs)
			etk::String tmpValue;
			tmpValue.resize(4096);
			do {
				uint_t size = tmpValue.size();
				#if defined(__TARGET_OS__Windows)
					uint_t len = GetModuleFileName(NULL, &tmpValue[0], size);
					if (len < tmpValue.size()) {
						tmpValue.resize(len);
						break;
					}
				#else
					uint_t size = tmpValue.size();
					if (_NSGetExecutablePath(&tmpValue[0], &size) == 0) {
						tmpValue.resize(strlen(&tmpValue[0]));
						break;
					}
				#endif
				tmpValue.resize(tmpValue.size() * 2);
			} while (tmpValue.size() < 65536);
			out = tmpValue;
		#else
			if (etk::fs::exist("/proc/self/exe") == true) {
				out = etk::fs::realPath("/proc/self/exe");
			} else if (etk::fs::exist("/proc/curproc/file") == true) {
				out = etk::fs::realPath("/proc/curproc/file");
			} else if (etk::fs::exist("/proc/curproc/exe") == true) {
				out = etk::fs::realPath("/proc/curproc/exe");
			}
		#endif
	}
	return out;
}

etk::Path etk::fs::getBinaryName() {
	return getBinaryPath().getFileName();
}
#if 0
etk::Path etk::fs::getDataPath() {
	
}
#endif
uint64_t etk::fs::getCreateTime(const etk::Path& _path) {
	struct stat statProperty;
	if (-1 == stat(_path.getString().c_str(), &statProperty)) {
		return 0;
	}
	return statProperty.st_ctime;
}

uint64_t etk::fs::getModifyTime(const etk::Path& _path) {
	struct stat statProperty;
	if (-1 == stat(_path.getString().c_str(), &statProperty)) {
		return 0;
	}
	return statProperty.st_mtime;
}

uint64_t etk::fs::getAccessTime(const etk::Path& _path) {
	struct stat statProperty;
	if (-1 == stat(_path.getString().c_str(), &statProperty)) {
		return 0;
	}
	return statProperty.st_atime;
}

uint32_t etk::fs::getIdOwner(const etk::Path& _path) {
	struct stat statProperty;
	if (-1 == stat(_path.getString().c_str(), &statProperty)) {
		return 0;
	}
	return statProperty.st_uid;
}

uint32_t etk::fs::getIdGroup(const etk::Path& _path) {
	struct stat statProperty;
	if (-1 == stat(_path.getString().c_str(), &statProperty)) {
		return 0;
	}
	return statProperty.st_gid;
}

etk::Vector<etk::Path> etk::fs::list(const etk::Path& _path) {
	etk::Vector<etk::Path> out;
	if (etk::fs::isDirectory(_path) == false) {
		return out;
	}
	DIR *dir = null;
	struct dirent *ent = null;
	dir = opendir(_path.getString().c_str());
	if (dir != null) {
		// for each element in the drectory...
		while ((ent = readdir(dir)) != null) {
			if(    strcmp(ent->d_name, ".") == 0
			    || strcmp(ent->d_name, "..") == 0) {
				// do nothing ...
				continue;
			}
			out.pushBack(_path / ent->d_name);
		}
		closedir(dir);
	} else {
		TK_ERROR("could not open directory : '" << _path << "'");
	}
	return out;
}

