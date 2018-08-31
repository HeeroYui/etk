/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/fileSystem/Type.hpp>

namespace etk {
	/**
	 * @brief representation of a path in the filesystem (the generic store data with / separators, for windows we store the Drive with a /c/ or /x/.
	 * You can get the OS specific filename with the function: @ref getOsPath();
	 */
	class Path {
		private:
			fileSystem::Type m_type; //!< the Type of data requested by the User.
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
			 * @brief Contructor with basic path.
			 * @param[in] _type type of path
			 * @param[in] _value offset in the path
			 */
			Path(fileSystem::Type _type, const etk::String& _value);
			/**
			 * @brief Get the absolute path
			 * @return string like /home/userXXX/aaa/bbb/*** or /c/userXXX/aaa/bbb/***
			 */
			etk::String get() const;
			/**
			 * @brief Get the relative path.
			 * @return string like ../../aaa/bbb/***
			 */
			etk::String getRelative() const;
			/**
			 * @brief Get the Decorated path.
			 * @return string like DATA:aaa/bbb/***
			 */
			etk::String getDecorated() const;
			/**
			 * @brief Get the absolute path
			 * @return string like /home/userXXX/aaa/bbb/*** or c:\userXXX\aaa\bbb\***
			 */
			etk::String getNative() const;
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
			Path& operator=/ (const etk::String & _element);
			/**
			 * @brief Add a subfolder on the current path.
			 * @param[in] _element sub folder or file to add.
			 * @return false : same path, true otherwise.
			 */
			Path operator+ (const etk::String & _element) const;
			//! @preivious
			Path& operator+= (const etk::String & _element);
			
			
	};
}

