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
		 * @brief query Interface management.
		 */
		class Query {
			private:
				etk::Map<etk::String, etk::String> m_data; //!< query data
			public:
				ETK_CONSTRUCTOR_MOVE_DEFAULT(Query);
				ETK_CONSTRUCTOR_COPY_DEFAULT(Query);
				/**
				 * @brief Default contructor.
				 */
				Query();
				/**
				 * @brief Set with a specific query string
				 * @param[in] _value query data
				 */
				Query(const etk::String& _value);
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
				 * @brief Get the Not encoded query (for debug only).
				 * @return encoded data.
				 */
				etk::String getNotEncoded() const;
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
				/**
				 * @brief clear data
				 */
				void clear();
				/**
				 * @brief check if the querry is empty
				 * @return true The querry have no data. false Otherwise
				 */
				bool isEmpty() const;
				/**
				 * @brief Check if the 2 Query are identical.
				 * @param[in] _obj Query to compare.
				 * @return true : same Query, false otherwise.
				 */
				bool operator== (const etk::uri::Query& _obj) const;
				/**
				 * @brief Check if the 2 Query are different.
				 * @param[in] _obj Query to compare.
				 * @return false : same query, true otherwise.
				 */
				bool operator!= (const etk::uri::Query& _obj) const;
				/**
				 * @brief check if this elemnt is greater than the other.
				 * @param[in] _obj Query to compare.
				 * @return true : less Query, false otherwise.
				 */
				bool operator< (const etk::uri::Query& _obj) const;
				/**
				 * @brief Check if this elemnt is greater than the other.
				 * @param[in] _obj Query to compare.
				 * @return false : Greater Query, true otherwise.
				 */
				bool operator> (const etk::uri::Query& _obj) const;
		};
	}
	//! @not_in_doc
	etk::Stream& operator <<(etk::Stream& _os, const etk::uri::Query& _obj);
}

