/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#include <etk/fileSystem/Path.hpp>
#include <etk/debug.hpp>
#include <etk/Exception.hpp>

#include <etk/typeInfo.hpp>
ETK_DECLARE_TYPE(etk::Path);

//#define TK_DBG_MODE TK_VERBOSE
#define TK_DBG_MODE TK_WARNING


static etk::String simplifyPath(etk::String _input) {
	// step 1 : for windows change \ in /:
	TK_DEBUG("Simplify(1) : '" << _input << "'");
	size_t currentPos = 0;
	if (_input.size() == 0) {
		return _input;
	}
	while(currentPos < _input.size()) {
		if (_input[currentPos] == '\\') {
			_input[currentPos] = '/';
		}
		currentPos++;
		continue;
	}
	// step 2 : remove all '//'
	TK_DBG_MODE("Simplify(2) : '" << _input << "'");
	currentPos = 0;
	if (_input.size() <= 1) {
		return _input;
	}
	while(currentPos < _input.size()-1) {
		if (    _input[currentPos] != '/'
		     || _input[currentPos+1] != '/') {
			currentPos++;
			continue;
		}
		_input.erase(currentPos, 1);
	}
	// step 3 : remove all '/./'
	TK_DBG_MODE("Simplify(3) : '" << _input << "'");
	currentPos = 0;
	if (_input.size() <= 1) {
		return _input;
	}
	while(    currentPos < _input.size()-2
	       && _input.size() > 2) {
		if (    _input[currentPos] != '/'
		     || _input[currentPos+1] != '.'
		     || _input[currentPos+2] != '/') {
			currentPos++;
			continue;
		}
		_input.erase(currentPos, 2);
	}
	if (end_with(_input, "/.") == true) {
		_input.erase(_input.size()-1, 1);
	}
	// step 4 remove xxx/..
	TK_DBG_MODE("Simplify(4) : '" << _input << "'");
	size_t lastSlashPos = etk::String::npos;
	currentPos = 0;
	while(    currentPos < _input.size()-2
	       && _input.size() > 2) {
		if (    _input[currentPos] != '/'
		     || _input[currentPos+1] != '.'
		     || _input[currentPos+2] != '.') {
			if (_input[currentPos] == '/') {
				lastSlashPos = currentPos;
			}
			currentPos++;
			continue;
		}
		if (lastSlashPos == etk::String::npos) {
			currentPos++;
			continue;
		}
		_input.erase(lastSlashPos, currentPos+2-lastSlashPos+1);
		TK_DEBUG("update : '" << _input << "'");
		lastSlashPos = etk::String::npos;
		currentPos = 0;
	}
	TK_DBG_MODE("Simplify(5) : '" << _input << "'");
	if (_input.size() == 0) {
		_input = "/";
	}
	#ifdef __TARGET_OS__Windows
		etk::String base;
		base += _input[0];
		base += ":";
		if (    _input == base + "/../"
		     || _input == base + "/.."
		     || _input == base + "/./"
		     || _input == base + "/."
		     || _input == "/") {
			_input = base + "/";
		}
	#else
		if (    _input == "/../"
		     || _input == "/.."
		     || _input == "/./"
		     || _input == "/.") {
			_input = "/";
		}
	#endif
	TK_DEBUG("Simplify(end) : '" << _input << "'");
	return _input;
}


static etk::String parsePath(etk::String _path) {
	etk::String out = _path;
	TK_DBG_MODE("1 : Set Name :              '" << out << "'");
	// Replace all time to prevent Windows user error when port on Unix
	out.replace("\\", "/");
	if (    out.size() > 3
	     && out[1] == ':'
	     && out[2] == '/') {
		#ifndef __TARGET_OS__Windows
			TK_WARNING("Path name have a windows form: '" << _path << "' c:/ but not a windwos platform");
		#endif
		if (    out[0] >= 'A'
		     && out[0] <= 'Z') {
			out[1] = out[0] + 'a' - 'A';
		} else {
			out[1] = out[0];
		}
		out[0] = '/';
	}
	out = simplifyPath(out);
	TK_DBG_MODE("3 : parse done :            '" << _path << "' ==>\"" << out << "\"");
	return out;
}


etk::Path::Path(const etk::String& _value) {
	m_data = parsePath(_value);
}

etk::String etk::Path::getString() const {
	return m_data;
}

etk::String etk::Path::getStringWindows() const {
	etk::String out = m_data;
	out.replace("/", "\\");
	if (    out.size() > 3
	     && out[0] == '/'
	     && out[2] == '/') {
		out[0] = out[1];
		out[0] = ':';
	}
	return out;
}

etk::String etk::Path::getRelative() const {
	// TODO : plouf ...
	return "todo";
}

etk::String etk::Path::getNative() const {
	#ifdef __TARGET_OS__Windows
		return getStringWindows();
	#else
		return getString();
	#endif
}

bool etk::Path::isRelative() const {
	if (    m_data.size() >= 1
	     && m_data[0] != '/') {
		return true;
	}
	return false;
}

bool etk::Path::isAbsolute() const {
	if (    m_data.size() >= 1
	     && m_data[0] == '/') {
		return true;
	}
	return false;
}

void etk::Path::parent() {
	size_t pos = m_data.rfind('/');
	if (pos == etk::String::npos) {
		return;
	}
	if (pos == 0) {
		// Last root element ==> do nothing.
		return;
	}
	m_data = m_data.extract(0, pos);
}

etk::Path etk::Path::getParent() const {
	etk::Path out = *this;
	out.parent();
	return out;
}

bool etk::Path::operator== (const etk::Path &_obj) const {
	return m_data == _obj.m_data;
}

bool etk::Path::operator!= (const etk::Path &_obj) const {
	return m_data != _obj.m_data;
}

etk::Path etk::Path::operator/ (const etk::String & _element) const {
	etk::Path tmp = *this;
	tmp /= _element;
	return tmp;
}

etk::Path etk::Path::operator/ (const etk::Path & _path) const {
	etk::Path tmp = *this;
	tmp /= _path;
	return tmp;
}

etk::Path& etk::Path::operator/= (const etk::String & _element) {
	if (_element.size() == 0) {
		return *this;
	}
	if (_element[0] == '/') {
		ETK_THROW_EXCEPTION(etk::exception::InvalidArgument("add path that is absolute"));
	}
	m_data += '/' + _element;
	m_data = simplifyPath(m_data);
	return *this;
}

etk::Path& etk::Path::operator/= (const etk::Path & _path) {
	if (_path.m_data.size() == 0) {
		return *this;
	}
	if (_path.m_data[0] == '/') {
		ETK_THROW_EXCEPTION(etk::exception::InvalidArgument("add path that is absolute"));
	}
	m_data += '/' + _path.m_data;
	m_data = simplifyPath(m_data);
	return *this;
}

etk::Path etk::Path::operator+ (const etk::String & _element) const {
	etk::Path tmp = *this;
	tmp += _element;
	return tmp;
}

etk::Path& etk::Path::operator+= (const etk::String & _element) {
	if (_element.size() == 0) {
		return *this;
	}
	m_data += _element;
	m_data = simplifyPath(m_data);
	return *this;
}

etk::Stream& etk::operator <<(etk::Stream &_os, const etk::Path &_obj) {
	_os << _obj.getString();
	return _os;
}

