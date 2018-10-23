/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/uri/Uri.hpp>
#include <etk/io/Interface.hpp>
#include <ememory/SharedPtr.hpp>



namespace etk {
	namespace uri {
		namespace provider {
			class Interface : public ememory::EnableSharedFromThis<Interface> {
				public:
					/**
					 * @brief Virtualize detructor:
					 */
					virtual ~Interface() = default;
				public:
					virtual ememory::SharedPtr<etk::io::Interface> create(const etk::Uri& _uri) = 0;
					/**
					 * @brief Check if an URI really exist.
					 * @param[in] _uri Uri to check.
					 * @return true if exist, false ortherwise
					 */
					virtual bool exist(const etk::Uri& _uri) = 0;
					/**
					 * @brief Check if the path is a directory.
					 * @param[in] _uri Uri to check.
					 * @return true This is a directory.
					 * @return false This is something else...
					 */
					virtual bool isDirectory(const etk::Uri& _uri) = 0;
					/**
					 * @brief Check if the path is a file (regular).
					 * @param[in] _uri Uri to check.
					 * @return true This is a file.
					 * @return false This is something else...
					 */
					virtual bool isFile(const etk::Uri& _uri) = 0;
					/**
					 * @brief check if the path is a symbolink link.
					 * @param[in] _uri Uri to check.
					 * @return true This is a synbolic link.
					 * @return false This is something else...
					 */
					virtual bool isSymLink(const etk::Uri& _uri) = 0;
					/**
					 * @brief Get the File size
					 * @param[in] _uri URI of the file
					 * @return the requested size
					 */
					virtual uint64_t fileSize(const etk::Uri& _uri);
					virtual etk::Vector<etk::Uri> list(const etk::Uri& _uri) = 0;
					virtual etk::Vector<etk::Uri> listRecursive(const etk::Uri& _uri) = 0;
					/**
					 * @brief Check if an URI Can be moved.
					 * @param[in] _uri Uri to check.
					 * @return true if it is possible, false ortherwise
					 */
					virtual bool canMove() { return false; }
					/**
					 * @brief Move an element for a source to a destination.
					 * @param[in] _uriSource Source Uri.
					 * @param[in] _uriDestination Destination Uri.
					 * @return true if moved, false ortherwise
					 */
					virtual bool move(const etk::Uri& _uriSource, const etk::Uri& _uriDestination) { return false; }
					/**
					 * @brief Check if an URI Can be copy.
					 * @param[in] _uri Uri to check.
					 * @return true if it is possible, false ortherwise
					 */
					virtual bool canCopy() { return false; }
					/**
					 * @brief Copy an element for a source to a destination.
					 * @param[in] _uriSource Source Uri.
					 * @param[in] _uriDestination Destination Uri.
					 * @return true if copied, false ortherwise
					 */
					virtual bool copy(const etk::Uri& _uriSource, const etk::Uri& _uriDestination) { return false; }
					/**
					 * @brief Check if an URI Can be removed.
					 * @param[in] _uri Uri to check.
					 * @return true if it is possible, false ortherwise
					 */
					virtual bool canRemove() { return false; }
					/**
					 * @brief Remove an element.
					 * @param[in] _uri Uri to remove.
					 * @return true if removed, false ortherwise
					 */
					virtual bool remove(const etk::Uri& _uri) { return false; }
			};
		}
	}
}
