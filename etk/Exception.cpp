/**
 * @author Edouard DUPIN
 * @copyright 2017, Edouard DUPIN, all right reserved
 * @license MPL-2 (see license file)
 */
#include <etk/Exception.hpp>
#include <etk/String.hpp>

etk::Exception::Exception():
  m_type("UNKNOW") {
	
}

etk::Exception::Exception(const char* _type, const etk::String& _what):
  m_type(_type),
  m_what(_what) {
	
}

etk::Exception::Exception(const etk::String& _what):
  m_type("ETK_EXCEPTION"),
  m_what(_what) {
	
}

const char* etk::Exception::which() const {
	return m_type;
}

const etk::String etk::Exception::what() const {
	return m_what;
}

const char* etk::Exception::file() const {
	return m_file;
}

size_t etk::Exception::line() const {
	return m_line;
}

const char* etk::Exception::function() const {
	return m_function;
}

etk::Exception& etk::Exception::setFile(const char* _value) {
	m_file = _value;
	return *this;
}

etk::Exception& etk::Exception::setLine(size_t _value) {
	m_line = _value;
	return *this;
}

etk::Exception& etk::Exception::setFunction(const char* _value) {
	m_function = _value;
	return *this;
}

etk::String etk::Exception::toString() const {
	etk::String out = "exception{";
	out += m_type;
	out += ":";
	out += m_what;
	if (m_function != null) {
		out += " on ";
		out += m_function;
	}
	if (m_file != null) {
		out += " in ";
		out += m_file;
		out += ":";
		out += m_line;
	}
	out += "}";
	return out;
}
