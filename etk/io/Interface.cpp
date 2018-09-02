/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL-2 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/io/Interface.hpp>


char etk::io::Interface::get() {
	char data='\0';
	if (read(&data, 1, 1)!=1) {
		return '\0';
	}
	return data;
}

bool etk::io::Interface::gets(etk::String& _output) {
	_output.clear();
	char tmp = get();
	while (    tmp != '\0'
	        && tmp != '\n') {
		_output += tmp;
		tmp = get();
	}
	if (tmp == '\0') {
		return false;
	}
	return true;
}

bool etk::io::Interface::put(char _input) {
	if (fileWrite(&_input, 1, 1) == 1) {
		return true;
	}
	return false;
}

bool etk::io::Interface::puts(const etk::String& _input) {
	if (fileWrite((void*)_input.c_str(), 1, _input.size()) == (int64_t)_input.size()) {
		return true;
	}
	return false;
}
