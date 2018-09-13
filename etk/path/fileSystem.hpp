/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>

#include <etk/path/Path.hpp>
#include <etk/path/Permissions.hpp>

namespace etk {
	namespace path {
		/**
		 * @brief Copy a path to an other (if possible...)
		 * @param[in] _path1 Path source.
		 * @param[in] _path2 Path destination.
		 * @return true Operation succeed.
		 * @return false Operation Failed.
		 */
		bool copy(const etk::Path& _path1, const etk::Path& _path2);
		/**
		 * @brief Copy a FOLDER path to an other (if possible...)
		 * @param[in] _path1 Path source.
		 * @param[in] _path2 Path destination.
		 * @return true Operation succeed.
		 * @return false Operation Failed.
		 */
		bool copyDirectory(const etk::Path& _path1, const etk::Path& _path2, bool _recursive = true);
		/**
		 * @brief Copy a FILE path to an other (if possible...)
		 * @param[in] _path1 Path source.
		 * @param[in] _path2 Path destination.
		 * @return true Operation succeed.
		 * @return false Operation Failed.
		 */
		bool copyFile(const etk::Path& _path1, const etk::Path& _path2);
		
		/**
		 * @brief Move a path to an other (if possible...)
		 * @param[in] _path1 Path source.
		 * @param[in] _path2 Path destination.
		 * @return true Operation succeed.
		 * @return false Operation Failed.
		 */
		bool move(const etk::Path& _path1, const etk::Path& _path2);
		/**
		 * @brief Move a FOLDER path to an other (if possible...)
		 * @param[in] _path1 Path source.
		 * @param[in] _path2 Path destination.
		 * @return true Operation succeed.
		 * @return false Operation Failed.
		 */
		bool moveDirectory(const etk::Path& _path1, const etk::Path& _path2);
		/**
		 * @brief Move a FILE path to an other (if possible...)
		 * @param[in] _path1 Path source.
		 * @param[in] _path2 Path destination.
		 * @return true Operation succeed.
		 * @return false Operation Failed.
		 */
		bool moveFile(const etk::Path& _path1, const etk::Path& _path2);
		/**
		 * @brief Remove a path (if possible...)
		 * @param[in] _path Path to remove.
		 * @return true Operation succeed.
		 * @return false Operation Failed.
		 */
		bool remove(const etk::Path& _path);
		/**
		 * @brief Remove a path recursively
		 * @param[in] _path Path to remove.
		 * @return true Operation succeed.
		 * @return false Operation Failed.
		 */
		bool removes(const etk::Path& _path);
		/**
		 * @brief Remove a FOLDER path (if possible...)
		 * @param[in] _path Path to remove.
		 * @return true Operation succeed.
		 * @return false Operation Failed.
		 */
		bool removeDirectory(const etk::Path& _path);
		/**
		 * @brief Remove a FOLDER path (with all his sub files
		 * @param[in] _path Path to remove.
		 * @return true Operation succeed.
		 * @return false Operation Failed.
		 */
		bool removeDirectories(const etk::Path& _path);
		/**
		 * @brief Remove a FILE path (if possible...)
		 * @param[in] _path Path to remove.
		 * @return true Operation succeed.
		 * @return false Operation Failed.
		 */
		bool removeFile(const etk::Path& _path);
		/**
		 * @brief Make a directory (last one only)
		 * @param[in] _path Path to create.
		 * @param[in] _permission Permission of creating directory.
		 * @return true Operation succeed.
		 * @return false Operation Failed.
		 */
		bool makeDirectory(const etk::Path& _path, etk::path::Permissions _permission = etk::path::Permissions::genericFolder);
		/**
		 * @brief Make a directory (With all parents if needed)
		 * @param[in] _path Path to create.
		 * @param[in] _permission Permission of creating directories.
		 * @return true Operation succeed.
		 * @return false Operation Failed.
		 */
		bool makeDirectories(const etk::Path& _path, etk::path::Permissions _permission = etk::path::Permissions::genericFolder);
		/**
		 * @brief update the Time of the file with the current time
		 * @param[in] _path Path to touch.
		 * @return true : action done
		 * @return false : action not done
		 */
		bool touch(const etk::Path& _path);
		/**
		 * @brief Check if the path exist
		 * @param[in] _path1 Path source.
		 * @param[in] _path2 Path destination.
		 */
		bool exist(const etk::Path& _path);
		/**
		 * @brief Get the File size
		 * @return the requested size
		 */
		uint64_t fileSize(const etk::Path& _path);
		/**
		 * @brief Check if the path is a directory.
		 * @param[in] _path Path of the requested information/
		 * @return true This is a directory.
		 * @return false This is something else...
		 */
		bool isDirectory(const etk::Path& _path);
		/**
		 * @brief Check if the path is a file (regular).
		 * @param[in] _path Path of the requested information.
		 * @return true This is a file.
		 * @return false This is something else...
		 */
		bool isFile(const etk::Path& _path);
		/**
		 * @brief check if the path is a symbolink link.
		 * @param[in] _path Path of the requested information.
		 * @return true This is a synbolic link.
		 * @return false This is something else...
		 */
		bool isSymLink(const etk::Path& _path);
		/**
		 * @brief Get the relative string of the path.
		 * @param[in] _path Path to transform.
		 * @return Well formated string of the path.
		 */
		etk::String getRelativeString(const etk::Path& _path);
		/**
		 * @brief Get the absolute string of the path.
		 * @param[in] _path Path to transform.
		 * @return Well formated string of the path.
		 */
		etk::String getAbsoluteString(const etk::Path& _path);
		/**
		 * @brief Get the native string of the path. (c:\xxx\xxx for windows and /YYY/vvv for unix)
		 * @param[in] _path Path to transform.
		 * @return Well formated string of the path.
		 */
		etk::String getNativeString(const etk::Path& _path);
		
		#if 0
			/**
			 * @brief Get the mime type of the file
			 * @param[in] _path Path of the requested information
			 * @return Mime file type "XXX_GROUP_XXX/YYY_ELEMENT_YYY"
			 */
			etk::String getMimeType(const etk::Path& _path);
		#endif
		/**
		 * @brief Get the realPath of a defined path.
		 * @param[in] Path that we want to have real value.
		 * @return the real path of the _path.
		 */
		etk::Path realPath(const etk::Path& _path);
		/**
		 * @brief Get a temporary path that can be write as you want.
		 * @return A system path.
		 */
		etk::Path getTemporaryPath();
		/**
		 * @brief Get a temporary path random and unique for all the process axecution.
		 * @return A system path with gegerated string.
		 */
		etk::Path getTemporaryProcessPath();
		/**
		 * @brief Get a temporary path random at each call of the application.
		 * @return A system path with gegerated string.
		 */
		etk::Path getTemporaryRandomPath();
		/**
		 * @brief Get user home directory.
		 */
		etk::Path getHomePath();
		/**
		 * @brief Get the Currect execution path.
		 * @return Path where the program is lunch.
		 */
		etk::Path getExecutionPath();
		/**
		 * @brief Current binary name.
		 * @return executable name.
		 */
		etk::String getBinaryName();
		/**
		 * @brief Full banary name (with root path).
		 * @return the binary absolute path.
		 */
		etk::Path getBinaryPath();
		/**
		 * @brief Get the data path of the application.
		 * @return the root path of the data for this application.
		 */
		etk::Path getDataPath();
		/**
		 * @brief Get the creation time of the path.
		 * @param[in] _path Path of the requested information.
		 * @return time since epoch.
		 */
		uint64_t getCreateTime(const etk::Path& _path);
		/**
		 * @brief Get the tast modification time of the path.
		 * @param[in] _path Path of the requested information.
		 * @return time since epoch.
		 */
		uint64_t getModifyTime(const etk::Path& _path);
		/**
		 * @brief Get the last access time of the path.
		 * @param[in] _path Path of the requested information.
		 * @return time since epoch.
		 */
		uint64_t getAccessTime(const etk::Path& _path);
		/**
		 * @brief Get the Id of the file owner.
		 * @param[in] _path Path of the requested information.
		 * @return system user ID.
		 */
		uint32_t getIdOwner(const etk::Path& _path);
		/**
		 * @brief Get the Id of the file group.
		 * @param[in] _path Path of the requested information.
		 * @return system group ID.
		 */
		uint32_t getIdGroup(const etk::Path& _path);
		/**
		 * @brief Get the permission of a specific Path.
		 * @param[in] _path Path of the requested information.
		 * @return Generic permission class.
		 */
		etk::path::Permissions getPermission(const etk::Path& _path);
		/**
		 * @brief List the content of a specific path.
		 * @param[in] Path to parse.
		 * @return the full list of path in the _path.
		 */
		etk::Vector<etk::Path> list(const etk::Path& _path);
	}
}

