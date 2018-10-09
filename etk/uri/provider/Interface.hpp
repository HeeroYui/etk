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
					virtual etk::Vector<etk::Uri> list(const etk::Uri& _uri) = 0;
					virtual etk::Vector<etk::Uri> listRecursive(const etk::Uri& _uri) = 0;
					virtual bool canMove() { return false; }
					virtual bool move(const etk::Uri& _uriSource, const etk::Uri& _uriDestination) { return false; }
			};
		}
	}
}
