/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>

#include <etk/String.hpp>
#include <etk/Map.hpp>
#include <etk/uri/Query.hpp>
#include <etk/path/Path.hpp>
#include <etk/uri/Uri.hpp>
#include <etk/uri/provider/provider.hpp>

namespace etk {
	namespace uri {
		/**
		 * @brief Check if an URI really exist.
		 * @param[in] _uri Uri to check.
		 * @return true if exist, false ortherwise
		 */
		bool exist(const etk::Uri& _uri);
		/**
		 * @brief Check if the path is a directory.
		 * @param[in] _uri Uri to check.
		 * @return true This is a directory.
		 * @return false This is something else...
		 */
		bool isDirectory(const etk::Uri& _uri);
		/**
		 * @brief Check if the path is a file (regular).
		 * @param[in] _uri Uri to check.
		 * @return true This is a file.
		 * @return false This is something else...
		 */
		bool isFile(const etk::Uri& _uri);
		/**
		 * @brief check if the path is a symbolink link.
		 * @param[in] _uri Uri to check.
		 * @return true This is a synbolic link.
		 * @return false This is something else...
		 */
		bool isSymLink(const etk::Uri& _uri);
		/**
		 * @brief Get the list of sub-element in the Uri
		 * @param[in] _uri Uri requested as parent.
		 * @return list of sub-uri
		 */
		etk::Vector<etk::Uri> list(const etk::Uri& _uri);
		/**
		 * @brief Get the list of sub-element in the Uri reursively
		 * @param[in] _uri Uri requested as parent.
		 * @return list of sub-uri
		 */
		etk::Vector<etk::Uri> listRecursive(const etk::Uri& _uri);
		/**
		 * @brief Get an IO interface with a specific URI
		 * @param[in] _uri Data interface requested
		 * @return The interface requested.
		 */
		ememory::SharedPtr<etk::io::Interface> get(const etk::Uri& _uri);
		/**
		 * @brief Check if an URI Can be moved.
		 * @param[in] _uri Uri to check.
		 * @return true if it is possible, false ortherwise
		 */
		bool canMove(const etk::Uri& _uri);
		/**
		 * @brief Move an element for a source to a destination.
		 * @param[in] _uriSource Source Uri.
		 * @param[in] _uriDestination Destination Uri.
		 * @return true if moved, false ortherwise
		 */
		bool move(const etk::Uri& _uriSource, const etk::Uri& _uriDestination);
		/**
		 * @brief Write all a string in a uri (if possible)
		 * @param[in] _uri Uri destination.
		 * @param[in] _data Data to write.
		 * @return true All data are write, false otherwise.
		 */
		bool writeAll(const etk::Uri& _uri, const etk::String& _data);
		/**
		 * @brief Read all a string in a uri (if possible)
		 * @param[in] _uri Uri destination.
		 * @param[out] _data Data readed.
		 * @return true All data are read, false otherwise.
		 */
		bool readAll(const etk::Uri& _uri, etk::String& _data);
	}
}
