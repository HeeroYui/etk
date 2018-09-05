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

namespace etk {
	namespace uri {
		/**
		 * @brief Querry Interface management.
		 */
		class Query {
			private:
				etk::Map<etk::String, etk::String> m_query; //!< Querry data
			public:
				ETK_CONSTRUCTOR_MOVE_DEFAULT(Query);
				ETK_CONSTRUCTOR_COPY_DEFAULT(Query);
				/**
				 * @brief Default contructor.
				 */
				Querry();
				/**
				 * @brief Set with a specific querry string
				 * @param[in] _value querry data
				 */
				Querry(const etk::String& _value);
				/**
				 * @brief Set the encoded query.
				 * @param[in] _value encoded data.
				 */
				void setEncoded(const etk::String& _value);
				/**
				 * @brief Get the encoded query.
				 * @return encoded data.
				 */
				etk::String getEncoded() const;
				/**
				 * @brief Set an element of the query.
				 * @param[in] _key Key of the query.
				 * @param[in] _value Associated data.
				 */
				void set(const etk::String& _key, const etk::String& _value);
				/**
				 * @brief Check if the key exist.
				 * @param[in] _key Key of the query.
				 * @return true Key exist.
				 * @return false Unknown key.
				 */
				bool exist(const etk::String& _key);
				/**
				 * @brief erase a specific key.
				 * @param[in] _key Key of the query.
				 */
				void erase(const etk::String& _key);
				/**
				 * @brief Get value of a query element.
				 * @param[in] _key Key of the query.
				 * @return associated data.
				 */
				etk::String get(const etk::String& _key);
		};
	}
}

