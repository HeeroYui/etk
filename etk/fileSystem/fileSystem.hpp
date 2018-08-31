/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/types.hpp>

#pragma once

namespace etk {
	namespace fileSystem {
		/**
		 * @brief Copy a path to an other (if possible...)
		 * @param[in] _path1 Path source.
		 * @param[in] _path2 Path destination.
		 */
		void copy(const etk::Path& _path1, const etk::Path& _path2);
		/**
		 * @brief Copy a FOLDER path to an other (if possible...)
		 * @param[in] _path1 Path source.
		 * @param[in] _path2 Path destination.
		 */
		void copyDirectory(const etk::Path& _path1, const etk::Path& _path2, bool _recursive = true);
		/**
		 * @brief Copy a FILE path to an other (if possible...)
		 * @param[in] _path1 Path source.
		 * @param[in] _path2 Path destination.
		 */
		void copyFile(const etk::Path& _path1, const etk::Path& _path2);
		
		/**
		 * @brief Move a path to an other (if possible...)
		 * @param[in] _path1 Path source.
		 * @param[in] _path2 Path destination.
		 */
		void move(const etk::Path& _path1, const etk::Path& _path2);
		/**
		 * @brief Move a FOLDER path to an other (if possible...)
		 * @param[in] _path1 Path source.
		 * @param[in] _path2 Path destination.
		 */
		void moveDirectory(const etk::Path& _path1, const etk::Path& _path2);
		/**
		 * @brief Move a FILE path to an other (if possible...)
		 * @param[in] _path1 Path source.
		 * @param[in] _path2 Path destination.
		 */
		void moveFile(const etk::Path& _path1, const etk::Path& _path2);
		
		/**
		 * @brief Remove a path (if possible...)
		 * @param[in] _path Path to remove.
		 */
		void remove(const etk::Path& _path);
		/**
		 * @brief Remove a FOLDER path (if possible...)
		 * @param[in] _path Path to remove.
		 */
		void removeDirectory(const etk::Path& _path);
		/**
		 * @brief Remove a FILE path (if possible...)
		 * @param[in] _path Path to remove.
		 */
		void removeFile(const etk::Path& _path);
		
		/**
		 * @brief Check if the path exist
		 * @param[in] _path1 Path source.
		 * @param[in] _path2 Path destination.
		 */
		bool exit(const etk::Path& _path);
		uint64_t fileSize(const etk::Path& _path);
		
		bool isDirectory(const etk::Path& _path);
		bool isFile(const etk::Path& _path);
		bool isSymLink(const etk::Path& _path);
		
		etk::filesystem::Permissions getPermission(const etk::Path& _path);
		
		etk::String getRelativeString(const etk::Path& _path);
		etk::String getDecoratedString(const etk::Path& _path);
		etk::String getAbsoluteString(const etk::Path& _path);
		etk::String getSystemString(const etk::Path& _path);
		
		etk::String getMimeType(const etk::Path& _path);
		
		etk::Path getTemporaryPath();
		etk::String getHomePathString();
		etk::Path getHomePath();
		etk::Path getExecutionPath();
		etk::Path getBinaryPath();
		etk::Path getDataPath();
		
		uint64_t getCreateTime(const etk::Path& _path);
		uint64_t getModifyTime(const etk::Path& _path);
		uint64_t getAccessTime(const etk::Path& _path);
		uint32_t getIdOwner(const etk::Path& _path);
		uint32_t getIdGroup(const etk::Path& _path);
	}
}

