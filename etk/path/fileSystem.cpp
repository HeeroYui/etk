/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#include <etk/path/fileSystem.hpp>
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
	#include <fcntl.h> /* Definition of AT_* constants */
}
#include <unistd.h>
#include <stdlib.h>

#include <etk/tool.hpp>
#include <etk/io/File.hpp>
#include <etk/io/SeekMode.hpp>

bool etk::path::copy(const etk::Path& _path1, const etk::Path& _path2) {
	TK_TODO("Not Implemented COPY of File : " << _path1 << " => " << _path2);
	return false;
}

bool etk::path::copyDirectory(const etk::Path& _path1, const etk::Path& _path2, bool _recursive) {
	TK_TODO("Not Implemented COPY of Directory : " << _path1 << " => " << _path2);
	return false;
}

bool etk::path::copyFile(const etk::Path& _path1, const etk::Path& _path2) {
	TK_TODO("Not Implemented COPY of File : " << _path1 << " => " << _path2);
	return false;
}


bool etk::path::move(const etk::Path& _path1, const etk::Path& _path2) {
	etk::Path path1 = _path1.getAbsolute();
	etk::Path path2 = _path2.getAbsolute();
	TK_VERBOSE("Move : \"" << path1 << "\" ==> \"" << path2 << "\"");
	if (etk::path::exist(path2) == true) {
		removes(path2);
	}
	// create path to be sure it exist ...
	etk::path::makeDirectories(path2.getParent());
	int32_t res = ::rename(path1.getNative().c_str(), path2.getNative().c_str());
	if (res != 0) {
		TK_ERROR("Can not move the file: '" << path1 << "' ==> '" << path2 << "' errno" << errno << " (" << strerror(errno) << ")");
		return false;
	}
	return true;
}

bool etk::path::moveDirectory(const etk::Path& _path1, const etk::Path& _path2) {
	return etk::path::move(_path1, _path2);
}

bool etk::path::moveFile(const etk::Path& _path1, const etk::Path& _path2) {
	return etk::path::move(_path1, _path2);
}

namespace detail {
	bool removeDirectories(const etk::Path& _path, bool _recursive);
	bool removes(const etk::Path& _path, bool _recursive) {
		etk::Path path = _path.getAbsolute();
		TK_VERBOSE("remove: " << path);
		if (etk::path::isDirectory(path) == true) {
			return detail::removeDirectories(path, _recursive);
		}
		return etk::path::removeFile(path);
	}
	bool removeDirectories(const etk::Path& _path, bool _recursive) {
		etk::Path path = _path.getAbsolute();
		TK_VERBOSE("remove Directory: " << path);
		if (_recursive == true) {
			etk::Vector<etk::Path> elements = etk::path::list(path);
			for (auto& it : elements) {
				detail::removes(it, _recursive);
			}
		}
		if ( 0 != ::rmdir(path.getNative().c_str()) ) {
			if (ENOTEMPTY == errno) {
				TK_ERROR("The Directory is not empty...");
			}
			return false;
		}
		return true;
	}
}

bool etk::path::remove(const etk::Path& _path) {
	return detail::removes(_path, false);
}

bool etk::path::removes(const etk::Path& _path) {
	return detail::removes(_path, true);
}

bool etk::path::removeDirectory(const etk::Path& _path) {
	return detail::removeDirectories(_path, false);
}

bool etk::path::removeDirectories(const etk::Path& _path) {
	return detail::removeDirectories(_path, true);
}

bool etk::path::removeFile(const etk::Path& _path) {
	etk::Path path = _path.getAbsolute();
	TK_VERBOSE("remove File: " << path);
	if (0 != unlink(path.getNative().c_str()) ) {
		return false;
	}
	return true;
}

bool etk::path::makeDirectory(const etk::Path& _path, etk::path::Permissions _permission) {
	etk::Path path = _path.getAbsolute();
	TK_VERBOSE("Make directory : " << path << " perm: " << _permission);
	if (etk::path::exist(path) == true) {
		return true;
	}
	#ifdef __TARGET_OS__Windows
		if (::mkdir(path.getNative().c_str()) != 0
		     && errno != EEXIST) {
			return false;
		}
	#else
		mode_t mode = _permission.getRightValue();
		if (    ::mkdir(path.getNative().c_str(), mode) != 0
		     && errno != EEXIST ) {
			return false;
		}
	#endif
	return true;
}

bool etk::path::makeDirectories(const etk::Path& _path, etk::path::Permissions _permission) {
	etk::Path path = _path.getAbsolute();
	TK_VERBOSE("Make dirrectories: " << path << " perm: " << _permission);
	if (etk::path::exist(path) == true) {
		return true;
	}
	auto elements = path.getNative().split('/');
	etk::Path pathToCreate;
	if (elements[0].size() == 0) {
		elements.popFront();
		pathToCreate = etk::Path("/");
	}
	for (auto& it: elements) {
		pathToCreate /= it;
		if (etk::path::makeDirectory(pathToCreate, _permission) == false) {
			return false;
		}
	}
	return true;
}

bool etk::path::touch(const etk::Path& _path) {
	TK_VERBOSE("Touch FILE : " << _path);
	if (etk::path::exist(_path) == true ) {
		int rc = utimensat(0,
		                   _path.getAbsoluteNative().c_str(),
		                   NULL,
		                   AT_SYMLINK_NOFOLLOW);
		if (rc) {
			return false;
		}
		return true;
	}
	// Write the file with nothing inside...
	etk::io::File file{_path};
	if (file.open(etk::io::OpenMode::Write) == false) {
		return false;
	}
	return file.close();
}

bool etk::path::exist(const etk::Path& _path) {
	if (::access( _path.getNative().c_str(), F_OK ) != -1 ) {
		return true;
	}
	return false;
}

uint64_t etk::path::fileSize(const etk::Path& _path) {
	// Note : this is a proper methode to get the file size for Big files ... otherwithe the size is limited at 2^31 bytes
	// tmpStat Buffer :
	struct stat statProperty;
	if (stat(_path.getNative().c_str(), &statProperty) == -1) {
		//Normal case when the file does not exist ... ==> the it was in unknow mode ...
		return 0;
	}
	TK_VERBOSE(" file size : " << (int64_t)statProperty.st_size << " bytes");
	if ((uint64_t)statProperty.st_size <= 0) {
		return 0;
	}
	return (uint64_t)statProperty.st_size;
}


bool etk::path::isDirectory(const etk::Path& _path) {
	struct stat st;
	int32_t status = 0;
	if (stat(_path.getNative().c_str(), &st) != 0) {
		return false;
	} else if (!S_ISDIR(st.st_mode)) {
		return false;
	}
	return true;
}

bool etk::path::isFile(const etk::Path& _path) {
	struct stat st;
	int32_t status = 0;
	if (stat(_path.getNative().c_str(), &st) != 0) {
		return false;
	} else if (!S_ISREG(st.st_mode)) {
		return false;
	}
	return true;
}

bool etk::path::isSymLink(const etk::Path& _path) {
	struct stat st;
	int32_t status = 0;
	if (stat(_path.getNative().c_str(), &st) != 0) {
		return false;
	} else if (!S_ISLNK(st.st_mode)) {
		return false;
	}
	return true;
}

bool etk::path::haveChild(const etk::Path& _path) {
	if (isDirectory(_path) == false) {
		return false;
	}
	// TODO: do it better. it work, but is slow ...
	return list(_path).size() != 0;
}


etk::path::Permissions etk::path::getPermission(const etk::Path& _path) {
	etk::path::Permissions permissions;
	// tmpStat Buffer :
	struct stat statProperty;
	if (-1 == stat(_path.getNative().c_str(), &statProperty)) {
		//Normal case when the file does not exist ... ==> the it was in unknow mode ...
		return permissions;
	}
	permissions = statProperty.st_mode;
	return permissions;
}


etk::String etk::path::getRelativeString(const etk::Path& _path) {
	return _path.getRelative();
}

etk::String etk::path::getAbsoluteString(const etk::Path& _path) {
	return _path.getAbsolute();
}

etk::String etk::path::getNativeString(const etk::Path& _path) {
	return _path.getNative();
}

/*
etk::String etk::path::getMimeType(const etk::Path& _path) {
	return "*";
}
*/

etk::Path etk::path::getTemporaryPath() {
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
		etk::Path val;
		do {
			val = etk::path::getTemporaryPath() / _patern + etk::random::generateString(16);
		} while (etk::path::exist(val) == true);
		return val;
	}
}

etk::Path etk::path::getTemporaryProcessPath() {
	static etk::Path out = detail::getTemporaryProcessPath("etk.process.");
	return out;
}

etk::Path etk::path::getTemporaryRandomPath() {
	return detail::getTemporaryProcessPath("etk.random.");
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

etk::Path etk::path::getHomePath() {
	return etk::Path(getHomePathString());
}

etk::Path etk::path::getExecutionPath() {
	static etk::Path g_path;
	if (g_path.getNative() != "") {
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

etk::Path etk::path::realPath(const etk::Path& _path) {
	#if ! defined(__TARGET_OS__Windows)
		char buf[8192];
		memset(buf, 0, 8192);
		char *res = realpath(_path.getNative().c_str(), buf);
		if (res) {
			return etk::Path{buf};
		}
	#endif
	return _path;
}

etk::Path etk::path::getBinaryPath() {
	static etk::Path out;
	if ( out.getNative() == "" ) {
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
			if (etk::path::exist("/proc/self/exe") == true) {
				out = etk::path::realPath("/proc/self/exe");
			} else if (etk::path::exist("/proc/curproc/file") == true) {
				out = etk::path::realPath("/proc/curproc/file");
			} else if (etk::path::exist("/proc/curproc/exe") == true) {
				out = etk::path::realPath("/proc/curproc/exe");
			}
		#endif
	}
	return out;
}

etk::String etk::path::getBinaryName() {
	return getBinaryPath().getFileName();
}

etk::Path etk::path::getDataPath() {
	#if defined(__TARGET_OS__Web)
		return "zz_generic_zz";
	#elif defined(__TARGET_OS__Android)
		return "assets";
	#elif defined(__TARGET_OS__Linux)
		etk::Path dataPath =  etk::Path("/usr/share") / getBinaryName();
		etk::Path theoricInstalledName = etk::Path("/usr/bin") / getBinaryName();
		TK_DEBUG(" position : '" << getBinaryPath() << "' installed position : '" << theoricInstalledName << "'");
		if (getBinaryPath() != theoricInstalledName) {
			dataPath = getBinaryPath().getParent() / ".." / "share" / getBinaryName();
		}
		return dataPath;
	#elif defined(__TARGET_OS__Windows)
		return getBinaryPath().getParent() / "data";
	#elif defined(__TARGET_OS__MacOs)
		return getBinaryPath().getParent() / ".." / "Resources" / getBinaryName();
	#elif defined(__TARGET_OS__IOs)
		return getBinaryPath().getParent() / "share" / getBinaryName();
	#endif
	return "NO_DATA_PATH";
}

uint64_t etk::path::getCreateTime(const etk::Path& _path) {
	struct stat statProperty;
	if (-1 == stat(_path.getNative().c_str(), &statProperty)) {
		return 0;
	}
	return statProperty.st_ctime;
}

uint64_t etk::path::getModifyTime(const etk::Path& _path) {
	struct stat statProperty;
	if (-1 == stat(_path.getNative().c_str(), &statProperty)) {
		return 0;
	}
	return statProperty.st_mtime;
}

uint64_t etk::path::getAccessTime(const etk::Path& _path) {
	struct stat statProperty;
	if (-1 == stat(_path.getNative().c_str(), &statProperty)) {
		return 0;
	}
	return statProperty.st_atime;
}

uint32_t etk::path::getIdOwner(const etk::Path& _path) {
	struct stat statProperty;
	if (-1 == stat(_path.getNative().c_str(), &statProperty)) {
		return 0;
	}
	return statProperty.st_uid;
}

uint32_t etk::path::getIdGroup(const etk::Path& _path) {
	struct stat statProperty;
	if (-1 == stat(_path.getNative().c_str(), &statProperty)) {
		return 0;
	}
	return statProperty.st_gid;
}

etk::Vector<etk::Path> etk::path::list(const etk::Path& _path, uint32_t _flags) {
	etk::Vector<etk::Path> out;
	if (etk::path::isDirectory(_path) == false) {
		return out;
	}
	DIR *dir = null;
	struct dirent *ent = null;
	TK_VERBOSE("List path: " << _path << " with flags: " << _flags);
	TK_VERBOSE("    native=" << _path.getNative());
	dir = opendir(_path.getNative().c_str());
	if (dir != null) {
		// for each element in the drectory...
		while ((ent = readdir(dir)) != null) {
			if(    strcmp(ent->d_name, ".") == 0
			    || strcmp(ent->d_name, "..") == 0
			    || strlen(ent->d_name) == 0) {
				// do nothing ...
				continue;
			}
			TK_VERBOSE("        find=" << ent->d_name);
			etk::Path tmpPath = _path / ent->d_name;
			if (_flags == etk::path::LIST_ALL) {
				out.pushBack(tmpPath);
				continue;
			}
			// Hidden file
			if (    ent->d_name[0] == '.'
			     && (_flags & etk::path::LIST_HIDDEN) == 0) {
				TK_VERBOSE("            ==> hidden");
				continue;
			}
			// FOLDER
			if (etk::path::isDirectory(tmpPath) == true) {
				if ((_flags & etk::path::LIST_FOLDER) != 0) {
					TK_VERBOSE("            ==> directory (add)");
					out.pushBack(tmpPath);
				} else {
					TK_VERBOSE("            ==> directory");
				}
				continue;
			}
			// OTHER ==> clasify as file ==> 99.9999% of usage
			if ((_flags & etk::path::LIST_FILE) != 0) {
				TK_VERBOSE("            ==> file (add)");
				out.pushBack(tmpPath);
			}
		}
		closedir(dir);
	} else {
		TK_ERROR("could not open directory : '" << _path << "'");
	}
	return out;
}


etk::Vector<etk::Path> etk::path::listRecursive(const etk::Path& _path, uint32_t _flags) {
	etk::Vector<etk::Path> out;
	if (etk::path::isDirectory(_path) == false) {
		return out;
	}
	DIR *dir = null;
	struct dirent *ent = null;
	dir = opendir(_path.getNative().c_str());
	if (dir != null) {
		// for each element in the drectory...
		while ((ent = readdir(dir)) != null) {
			if(    strcmp(ent->d_name, ".") == 0
			    || strcmp(ent->d_name, "..") == 0) {
				// do nothing ...
				continue;
			}
			etk::Path tmpPath = _path / ent->d_name;
			if (_flags == etk::path::LIST_ALL) {
				out.pushBack(tmpPath);
				if (etk::path::isDirectory(tmpPath) == true) {
					for (auto& it: etk::path::listRecursive(tmpPath, _flags)) {
						out.pushBack(it);
					}
				}
				continue;
			}
			// Hidden file
			if (    ent->d_name[0] == '.'
			     || (_flags & etk::path::LIST_HIDDEN) == 0) {
				continue;
			}
			// FOLDER
			if (etk::path::isDirectory(tmpPath) == true) {
				if ((_flags & etk::path::LIST_FOLDER) != 0) {
					out.pushBack(tmpPath);
				}
				if (etk::path::isDirectory(tmpPath) == true) {
					for (auto& it: etk::path::listRecursive(tmpPath, _flags)) {
						out.pushBack(it);
					}
				}
				continue;
			}
			// OTHER ==> clasify as file ==> 99.9999% of usage
			if ((_flags & etk::path::LIST_FILE) != 0) {
				out.pushBack(tmpPath);
			}
		}
		closedir(dir);
	} else {
		TK_ERROR("could not open directory : '" << _path << "'");
	}
	return out;
}

