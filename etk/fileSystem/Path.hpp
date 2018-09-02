/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/fileSystem/Type.hpp>
#include <etk/String.hpp>

namespace etk {
	/**
	 * @brief representation of a path in the filesystem (the generic store data with / separators, for windows we store the Drive with a /c/ or /x/.
	 * You can get the OS specific filename with the function: @ref getOsPath();
	 */
	class Path {
		private:
			etk::String m_data; //!< Raw data of the path.
		public:
			ETK_CONSTRUCTOR_MOVE_DEFAULT(Path);
			ETK_CONSTRUCTOR_COPY_DEFAULT(Path);
			/**
			 * @brief Default contructor.
			 */
			Path();
			/**
			 * @brief Contructor with basic path.
			 * @param[in] _value Element basic path
			 */
			Path(const etk::String& _value);
			/**
			 * @brief Get the absolute path
			 * @return string like /home/userXXX/aaa/bbb/### or /c/userXXX/aaa/bbb/###
			 */
			etk::String getString() const;
			/**
			 * @brief Get the absolute path
			 * @return string like /home/userXXX/aaa/bbb/### or /c/userXXX/aaa/bbb/###
			 */
			etk::String getStringWindows() const;
			/**
			 * @brief Get the relative path.
			 * @return string like ../../aaa/bbb/###
			 */
			etk::String getRelative() const;
			/**
			 * @brief Get the absolute path
			 * @return string like /home/userXXX/aaa/bbb/### or c:\userXXX\aaa\bbb\###
			 */
			etk::String getNative() const;
			/**
			 * @brief Check if the path is relative or not.
			 * @return true The path is relative.
			 * @return false The path is not relative.
			 */
			bool isRelative() const;
			/**
			 * @brief Check if the path is absolute or not.
			 * @return true The path is absolute.
			 * @return false The path is not absolute.
			 */
			bool isAbsolute() const;
			/**
			 * @brief remove the last child element of the path.
			 */
			void parent();
			/**
			 * @brief Get the path of the parent.
			 * @return Parent path.
			 */
			etk::Path getParent() const;
			/**
			 * @brief Check if the 2 Path are identical.
			 * @param[in] _obj Path to compare.
			 * @return true : same path, false otherwise.
			 */
			bool operator== (const etk::Path &_obj) const;
			/**
			 * @brief Check if the 2 Path are different.
			 * @param[in] _obj Path to compare.
			 * @return false : same path, true otherwise.
			 */
			bool operator!= (const etk::Path &_obj) const;
			/**
			 * @brief Add a subfolder on the current path.
			 * @param[in] _element sub folder or file to add.
			 * @return false : same path, true otherwise.
			 */
			Path operator/ (const etk::String & _element) const;
			//! @preivious
			Path& operator/= (const etk::String & _element);
			//! @preivious
			Path operator/ (const etk::Path & _element) const;
			//! @preivious
			Path& operator/= (const etk::Path & _element);
			/**
			 * @brief Add a subfolder on the current path.
			 * @param[in] _element sub folder or file to add.
			 * @return false : same path, true otherwise.
			 */
			Path operator+ (const etk::String & _element) const;
			//! @preivious
			Path& operator+= (const etk::String & _element);
			//! @preivious
			Path operator+ (const etk::Path & _element) const;
			//! @preivious
			Path& operator+= (const etk::Path & _element);
	};
	//! @not_in_doc
	etk::Stream& operator <<(etk::Stream &_os, const etk::Path &_obj);
}
