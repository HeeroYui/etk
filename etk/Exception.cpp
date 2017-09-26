/**
 * @author Edouard DUPIN
 * @copyright 2017, Edouard DUPIN, all right reserved
 * @license MPL-2 (see license file)
 */
#include <etk/Exception.hpp>
#include <etk/String.hpp>

etk::Exception::Exception():
  m_type("UNKNOW"),
  m_what("? ? ?"),
  m_function(nullptr) {
	
}
etk::Exception::Exception(const char* _type, const etk::String& _what, const char* _function):
  m_type(_type),
  m_what(_what),
  m_function(_function) {
	
}

const char* etk::Exception::which() const {
	return m_type;
}

const etk::String etk::Exception::what() const {
	return m_what;
}

const char* etk::Exception::where() const {
	return m_function;
}

etk::String etk::Exception::toString() const {
	etk::String out = "exception{";
	out += m_type;
	out += ":";
	out += m_what;
	if (m_function != nullptr) {
		out += " in ";
		out += m_function;
	}
	out += "}";
	return out;
}
