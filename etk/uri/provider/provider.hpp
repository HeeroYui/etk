/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/fs/Type.hpp>
#include <etk/String.hpp>
#include <etk/Map.hpp>
#include <etk/uri/Query.hpp>
#include <etk/fs/Path.hpp>
#include <etk/io/Interface.hpp>
#include <etk/uri/provider/Interface.hpp>
#include <ememory/SharedPtr.hpp>
#include <ememory/memory.hpp>

namespace etk {
	namespace uri {
		namespace provider {
			/**
			 * @brief Add a IO interface provider ==> permit to have simple whangable backend interface.
			 * @param[in] _scheme URI scheme specific interface (like 'http' for 'http://' or 'RAW' for no scheme or "data" for 'data://')
			 * @param[in] _interface Provider interface
			 */
			void add(const etk::String& _scheme, ememory::SharedPtr<etk::uri::provider::Interface> _interface);
			/**
			 * @brief Add a IO interface provider ==> permit to have simple whangable backend interface.
			 * @param[in] _scheme URI scheme specific interface
			 */
			void remove(const etk::String& _scheme);
			/**
			 * @brief Check if a provider exist.
			 * @param[in] _scheme URI scheme specific interface
			 * @return true The provider is availlable
			 */
			bool exist(const etk::String& _scheme);
			/**
			 * @brief Clear all providers
			 */
			void clear();
			/**
			 * @brief Get an IO interface with a specific URI
			 * @param[in] _uri Data interface requested
			 * @return The interface requested.
			 */
			ememory::SharedPtr<etk::io::Interface> get(const etk::Uri& _uri);
			/**
			 * @brief Get an URI provider
			 * @param[in] _scheme type of provider
			 * @return The interface requested.
			 */
			ememory::SharedPtr<etk::uri::provider::Interface> getProvider(const etk::String& _scheme);
			/**
			 * @brief Initialize uri provider
			 */
			void init();
			/**
			 * @brief Un-Initialize uri provider
			 */
			void unInit();
		}
	}
}
