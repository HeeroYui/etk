/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/types.hpp>

#pragma once

namespace etk {
	namespace fileSystem {
		void copy(const etk::Path& _path1, const etk::Path& _path2);
		void copyDirectory(const etk::Path& _path1, const etk::Path& _path2, bool _recursive = true);
		void copyFile(const etk::Path& _path1, const etk::Path& _path2);
		
		void move(const etk::Path& _path1, const etk::Path& _path2);
		void moveDirectory(const etk::Path& _path1, const etk::Path& _path2);
		void moveFile(const etk::Path& _path1, const etk::Path& _path2);
		
		void remove(const etk::Path& _path1, const etk::Path& _path2);
		void removeDirectory(const etk::Path& _path1, const etk::Path& _path2);
		void removeFile(const etk::Path& _path1, const etk::Path& _path2);
		
		bool exit(const etk::Path& _path);
		uint_t fileSize(const etk::Path& _path);
		
		bool isDirectory(const etk::Path& _path);
		bool isFile(const etk::Path& _path);
		bool isSymLink(const etk::Path& _path);
		
		etk::filesystem::Permissions getPermission(const etk::Path& _path);
		
		etk::String getRelativeString(const etk::Path& _path);
		etk::String getDecoratedString(const etk::Path& _path);
		etk::String getAbsoluteString(const etk::Path& _path);
		
		etk::String getMimeType(const etk::Path& _path);
		
		etk::Path getTemporaryPath();
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

