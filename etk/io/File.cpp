/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL-2 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/io/Interface.hpp>

etk::io::File::File() {
	// nothing to do.
}
etk::io::File::File(const etk::Path& _path):
  m_path(_path) {
	
}
bool etk::io::File::open(etk::io::OpenMode _mode) {
	if (m_pointer != null) {
		TK_CRITICAL("File Already open : " << *this);
		return true;
	}
	TK_VERBOSE(" Read file : " << m_path);
	switch (_mode) {
		case etk::io::OpenMode::Read:
			m_pointer = fopen(m_path.c_str(),"rb");
			break;
		case etk::io::OpenMode::Write:
			m_pointer = fopen(m_path.c_str(),"wb");
			break;
		case etk::io::OpenMode::Append:
			m_pointer = fopen(m_path.c_str(),"ab");
			break;
	}
	if(m_pointer == null) {
		TK_ERROR("Can not open the file " << m_path );
		return false;
	}
	return true;
}

bool etk::io::File::isOpen() {
	return m_pointer != null;
}

bool etk::io::File::close() {
	if (m_pointer == null) {
		TK_CRITICAL("File Already closed : " << *this);
		return false;
	}
	fclose(m_pointer);
	m_pointer = null;
	return true;
}

uint64_t etk::io::File::size() {
	return etk::fileSystem::fileSize(m_path);
}

char* etk::io::File::gets(char* _elementLine, int64_t _maxData) {
	return fgets(_elementLine, _maxData, m_pointer);
}

char etk::io::File::get() {
	char data='\0';
	if (read(&data, 1, 1)!=1) {
		return '\0';
	}
	return data;
}

bool etk::io::File::gets(etk::String& _output) {
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

bool etk::io::File::put(char _input) {
	if (fileWrite(&_input, 1, 1) == 1) {
		return true;
	}
	return false;
}

bool etk::io::File::puts(const etk::String& _input) {
	if (fileWrite((void*)_input.c_str(), 1, _input.size()) == (int64_t)_input.size()) {
		return true;
	}
	return false;
}

bool etk::io::File::seek(uint64_t _offset, enum etk::io::SeekMode _origin) {
	int originFS = 0;
	switch(_origin) {
		case etk::seekNode_end:
			originFS = SEEK_END;
			break;
		case etk::seekNode_current:
			originFS = SEEK_CUR;
			break;
		default:
			originFS = 0;
			break;
	}
	fseek(m_pointer, _offset, originFS);
	if(ferror(m_pointer)) {
		return false;
	}
	return true;
}

void etk::io::File::flush() {
	if (m_pointer != null) {
		fflush(m_pointer);
	}
}

void etk::io::File::tell() {
	if (m_pointer != null) {
		ftell(m_pointer);
	}
}

int64_t etk::io::File::read(void* _data, int64_t _blockSize, int64_t _nbBlock) {
	if (m_pointer == null) {
		TK_ERROR("Can not read in a file that is not open : " << *this);
		return 0;
	}
	return fread(_data, _blockSize, _nbBlock, m_pointer);
}

int64_t etk::io::File::write(const void* _data, int64_t _blockSize, int64_t _nbBlock) {
	if (m_pointer == null) {
		TK_ERROR("Can not write in a file that is not open : " << *this);
		return 0;
	}
	return fwrite(_data, _blockSize, _nbBlock, m_pointer);
}
