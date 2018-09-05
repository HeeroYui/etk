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
			uint16_t m_port; //!< Port of the server
			etk::Path m_path; //!< Path data
			etk::uri::Query m_query; //!< querry interface
			etk::String m_fragment; //!< fragment data
		public:
			ETK_CONSTRUCTOR_MOVE_DEFAULT(Uri);
			ETK_CONSTRUCTOR_COPY_DEFAULT(Uri);
			/**
			 * @brief Default contructor.
			 */
etk::Uri::Uri() {
	
}

etk::Uri::Uri(const etk::String& _value) {
	set(_value);
}

etk::Uri::Uri(const char * _value) {
	set(_value);
}

void etk::Uri::set(const etk::String& _value) {
	
}

void etk::Uri::set(const char * _value) {
	set(etk::String(_value));
}

etk::String etk::Uri::get() {
	etk::String out;
	if (m_scheme != "") {
		out += m_scheme;
		out += "://";
	}
	if (m_server != "") {
		if (m_user != "") {
			out += m_user;
			if (m_password != "") {
				out += ":";
				out += m_password;
			}
			out += "@";
		}
		out += m_server;
		if (m_port != 0) {
			out += ":";
			out += etk::toString(m_port);
		}
	}
	if(m_path != "") {
		out += "/";
		out += m_path.getString();
	}
	if(m_query.size() != 0) {
		out += "?";
		out += m_query.getEncoded();
	}
	if(m_fragment != "") {
		out += "#";
		out += m_fragment;
	}
}

const etk::String& etk::Uri::getScheme() const {
	return m_scheme;
}

void etk::Uri::setScheme(const etk::String& _value) {
	m_scheme = _value;
}

const etk::String& etk::Uri::getUser() const {
	return m_user;
}

void etk::Uri::setUser(const etk::String& _value) {
	m_user = _value;
}

const etk::String& etk::Uri::getPassword() const {
	return m_password;
}

void etk::Uri::setPassword(const etk::String& _value) {
	m_password = _value;
}

const etk::String& etk::Uri::getServer() const {
	return m_server;
}

void etk::Uri::setServer(const etk::String& _value) {
	m_server = _value;
}

uint16_t etk::Uri::getPort() const {
	return m_port;
}

void etk::Uri::setPort(uint16_t _value) {
	m_port = _value;
}

const etk::Path& etk::Uri::getPath() const {
	return m_path;
}

void etk::Uri::setPath(const etk::Path& _value) {
	m_path = _value;
}

const etk::uri::Query& etk::Uri::getQuery() const {
	return m_query;
}

void etk::Uri::setQuery(const etk::uri::Query& _value) {
	m_query = _value;
}

const etk::String& etk::Uri::getFragment() const {
	return m_fragment;
}

void etk::Uri::setFragment(const etk::String& _value) {
	m_fragment = _value;
}
