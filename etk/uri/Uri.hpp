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

namespace etk {
	/**
	 * @brief Uniform resource interface manage internal resource and nerwork resource (like URL)
	 * Format is manage like : __SCHEME__://__USER__:__PASSWORD__@__SERVER__:__PORT__/__PATH__?__QUERY__#__FRAGMENT__
	 */
	class Uri {
		private:
			etk::String m_scheme; //!< Sheme of the uri.
			etk::String m_user; //!< user name
			etk::String m_password; //!< password (crypted/hashed)
			etk::String m_server; //!< server name
			uint16_t m_port = 0; //!< Port of the server
			etk::Path m_path; //!< Path data
			etk::uri::Query m_query; //!< query interface
			etk::String m_fragment; //!< fragment data
		public:
			ETK_CONSTRUCTOR_MOVE_DEFAULT(Uri);
			ETK_CONSTRUCTOR_COPY_DEFAULT(Uri);
			/**
			 * @brief Default contructor.
			 */
			Uri();
			/**
			 * @brief Contructor with basic URI.
			 * @param[in] _value Element basic URI
			 */
			Uri(const etk::String& _value);
			/**
			 * @brief Contructor with basic URI with a generic path.
			 * @param[in] _value generic path
			 */
			Uri(const etk::Path& _value);
			/**
			 * @brief Contructor with basic URI.
			 * @param[in] _value Element basic URI
			 */
			Uri(const char * _value);
			/**
			 * @brief Contructor with basic URI.
			 * @param[in] _value Element basic URI
			 */
			void set(etk::String _value);
			/**
			 * @brief Contructor with basic URI.
			 * @param[in] _value Element basic URI
			 */
			void set(const char * _value);
			/**
			 * @brief generate the URI string.
			 * @return the uri correctly encoded
			 */
			etk::String get() const;
			/**
			 * @brief Get the scheme of the URI.
			 * @return Scheme value.
			 */
			const etk::String& getScheme() const;
			/**
			 * @brief Get the scheme of the URI.
			 * @param[in] _value New Scheme value.
			 */
			void setScheme(const etk::String& _value);
			/**
			 * @brief Get the user Name (login).
			 * @return User value.
			 */
			const etk::String& getUser() const;
			/**
			 * @brief Set the user Name (login).
			 * @param[in] _value User value
			 */
			void setUser(const etk::String& _value);
			/**
			 * @brief Get the user password.
			 * @return Password string (crypted/hashed)
			 */
			const etk::String& getPassword() const;
			/**
			 * @brief Set the user password.
			 * @param[in] _value Password string (crypted/hashed).
			 */
			void setPassword(const etk::String& _value);
			/**
			 * @brief Get the server name [HOST].
			 * @return Address of the server.
			 */
			const etk::String& getServer() const;
			/**
			 * @brief Set the server name [HOST].
			 * @param[in] _value address of the server.
			 */
			void setServer(const etk::String& _value);
			/**
			 * @brief Get the server port.
			 * @return port Value (0 disable).
			 */
			uint16_t getPort() const;
			/**
			 * @brief Set the server port.
			 * @param[in] _value new server port (0 disable).
			 */
			void setPort(uint16_t _value);
			/**
			 * @brief Get the path of the URI
			 * @return URI path.
			 */
			const etk::Path& getPath() const;
			/**
			 * @brief Set the path.
			 * @param[in] _value New path value.
			 */
			void setPath(const etk::Path& _value);
			/**
			 * @brief Get the query.
			 * @return query data.
			 */
			const etk::uri::Query& getQuery() const;
			etk::uri::Query& getQuery();
			/**
			 * @brief Set the new query.
			 * @param[in] _value Data.
			 */
			void setQuery(const etk::uri::Query& _value);
			/**
			 * @brief Get the fragment element.
			 * @return frangment string.
			 */
			const etk::String& getFragment() const;
			/**
			 * @brief Set the frangment property.
			 * @param[in] _value New fragment
			 */
			void setFragment(const etk::String& _value);
			/**
			 * @brief Clear the structure.
			 */
			void clear();
			/**
			 * @brief Check if the uri ahave data
			 * @return true The uri is empty
			 * @return famse The uri have some element
			 */
			bool isEmpty() const;
			/**
			 * @brief Check if the 2 Uri are identical.
			 * @param[in] _obj Uri to compare.
			 * @return true : same Uri, false otherwise.
			 */
			bool operator== (const etk::Uri& _obj) const;
			/**
			 * @brief Check if the 2 Uri are different.
			 * @param[in] _obj Uri to compare.
			 * @return false : same Uri, true otherwise.
			 */
			bool operator!= (const etk::Uri& _obj) const;
			/**
			 * @brief check if this elemnt is lower than the other.
			 * @param[in] _obj Uri to compare.
			 * @return true : less Uri, false otherwise.
			 */
			bool operator< (const etk::Uri& _obj) const;
			/**
			 * @brief check if this elemnt is lower or equal than the other.
			 * @param[in] _obj Uri to compare.
			 * @return true : less Uri, false otherwise.
			 */
			bool operator<= (const etk::Uri& _obj) const;
			/**
			 * @brief Check if this elemnt is greater than the other.
			 * @param[in] _obj Uri to compare.
			 * @return false : Greater Uri, true otherwise.
			 */
			bool operator> (const etk::Uri& _obj) const;
			/**
			 * @brief Check if this elemnt is greater or equal than the other.
			 * @param[in] _obj Uri to compare.
			 * @return false : Greater Uri, true otherwise.
			 */
			bool operator>= (const etk::Uri& _obj) const;
			/**
			 * @brief Detail display of this element
			 */
			void display() const;
	};
	//! @not_in_doc
	etk::Stream& operator <<(etk::Stream& _os, const etk::Uri& _obj);
}

