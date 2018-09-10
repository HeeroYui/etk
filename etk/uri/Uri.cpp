/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/uri/Uri.hpp>
#include <etk/debug.hpp>

etk::Uri::Uri() {
	
}

etk::Uri::Uri(const etk::String& _value) {
	set(_value);
}

etk::Uri::Uri(const etk::Path& _value) {
	m_path = _value;
}

etk::Uri::Uri(const char * _value) {
	set(_value);
}

etk::Stream& etk::operator <<(etk::Stream& _os, const etk::Uri& _obj) {
	_os << _obj.get();
	return _os;
}

void etk::Uri::set(const char * _value) {
	set(etk::String(_value));
}

void etk::Uri::clear() {
	m_scheme.clear();
	m_user.clear();
	m_password.clear();
	m_server.clear();
	m_port = 0;
	m_path.clear();
	m_query.clear();
	m_fragment.clear();
}

bool etk::Uri::isEmpty() const {
	return    m_scheme.isEmpty() == true
	       && m_user.isEmpty() == true
	       && m_password.isEmpty() == true
	       && m_server.isEmpty() == true
	       && m_port == 0
	       && m_path.isEmpty() == true
	       && m_query.isEmpty() == true
	       && m_fragment.isEmpty() == true;
}
bool etk::Uri::operator== (const etk::Uri& _obj) const {
	return    m_scheme == _obj.m_scheme
	       && m_user == _obj.m_user
	       && m_password == _obj.m_password
	       && m_server == _obj.m_server
	       && m_port == _obj.m_port
	       && m_path == _obj.m_path
	       && m_query == _obj.m_query
	       && m_fragment == _obj.m_fragment;
}

bool etk::Uri::operator!= (const etk::Uri& _obj) const {
	return    m_scheme != _obj.m_scheme
	       || m_user != _obj.m_user
	       || m_password != _obj.m_password
	       || m_server != _obj.m_server
	       || m_port != _obj.m_port
	       || m_path != _obj.m_path
	       || m_query != _obj.m_query
	       || m_fragment != _obj.m_fragment;
}
bool etk::Uri::operator< (const etk::Uri& _obj) const {
	return    m_scheme < _obj.m_scheme
	       && m_user < _obj.m_user
	       && m_password < _obj.m_password
	       && m_server < _obj.m_server
	       && m_port < _obj.m_port
	       && m_path < _obj.m_path
	       && m_query < _obj.m_query
	       && m_fragment < _obj.m_fragment;
}
bool etk::Uri::operator> (const etk::Uri& _obj) const {
	return    m_scheme > _obj.m_scheme
	       && m_user > _obj.m_user
	       && m_password > _obj.m_password
	       && m_server > _obj.m_server
	       && m_port > _obj.m_port
	       && m_path > _obj.m_path
	       && m_query > _obj.m_query
	       && m_fragment > _obj.m_fragment;
}

void etk::Uri::set(etk::String _value) {
	TK_VERBOSE("parse: '" << _value << "'");
	size_t pos = _value.find("://");
	if (pos != etk::String::npos) {
		// find scheme
		m_scheme = _value.extract(0, pos);
		_value = _value.extract(pos+3, etk::String::npos);
		TK_VERBOSE("find scheme : '" << m_scheme << "'     ==||==     '" << _value << "'");
	}
	pos = _value.rfind('#');
	if (pos != etk::String::npos) {
		// find scheme
		m_fragment = _value.extract(pos+1, etk::String::npos);
		_value = _value.extract(0, pos);
		TK_VERBOSE("find fragment: '" << m_fragment << "'     ==||==     '" << _value << "'");
	}
	pos = _value.rfind('?');
	if (pos != etk::String::npos) {
		// find query
		m_query.setEncoded(_value.extract(pos+1, etk::String::npos));
		_value = _value.extract(0, pos);
		TK_VERBOSE("find query: '" << m_query << "'     ==||==     '" << _value << "'");
	}
	pos = _value.find('/');
	if (pos != etk::String::npos) {
		// find path
		m_path = _value.extract(pos+1, etk::String::npos);
		_value = _value.extract(0, pos);
		TK_VERBOSE("find scheme : '" << m_path << "'     ==||==     '" << _value << "'");
	}
	pos = _value.find('@');
	if (pos != etk::String::npos) {
		TK_VERBOSE("find server With name");
		// find server with user
		etk::String userInfo = _value.extract(0, pos);
		size_t pos_2 = userInfo.find(':');
		if (pos_2 != etk::String::npos) {
			// find password:
			m_user = userInfo.extract(0, pos_2);
			m_password = userInfo.extract(pos_2+1, etk::String::npos);
		} else {
			m_user=userInfo;
			m_password="";
		}
		_value = _value.extract(pos+1, etk::String::npos);
		TK_VERBOSE("find user / pass : '" << m_user << "' / '" << m_password << "'     ==||==     '" << _value << "'");
	}
	pos = _value.find(':');
	if (pos != etk::String::npos) {
		m_server = _value.extract(0, pos);
		m_port = string_to_uint16_t(_value.extract(pos+1, etk::String::npos));
	} else {
		m_server = _value;
		m_port = 0;
	}
	TK_VERBOSE("find server / port : '" << m_server << "' / '" << m_port << "'");
}

etk::String etk::Uri::get() const {
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
	if(m_query.isEmpty() == false) {
		out += "?";
		out += m_query.getEncoded();
	}
	if(m_fragment != "") {
		out += "#";
		out += m_fragment;
	}
	return out;
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
