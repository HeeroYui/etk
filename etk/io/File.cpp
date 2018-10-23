/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL-2 (see license file)
 */
#include <etk/types.hpp>
#include <etk/io/File.hpp>
#include <etk/debug.hpp>
#include <etk/path/fileSystem.hpp>
#include <sys/stat.h>
extern "C" {
	#include <errno.h>
}

etk::io::File::File() {
	// nothing to do.
}

etk::io::File::File(const etk::Path& _path):
  m_path(_path) {
	
}

etk::io::File::~File() {
	if (m_pointer != null) {
		TK_ERROR("Missing to close the file : '" << m_path << "'S");
		close();
	}
}

bool etk::io::File::open(etk::io::OpenMode _mode) {
	if (m_pointer != null) {
		TK_CRITICAL("File Already open : " << m_path);
		return true;
	}
	TK_VERBOSE(" Read file : " << m_path);
	switch (_mode) {
		case etk::io::OpenMode::Read:
			m_pointer = fopen(m_path.getNative().c_str(), "rb");
			break;
		case etk::io::OpenMode::Write:
			if (etk::path::isDirectory(m_path.getParent().getNative()) == false) {
				etk::path::makeDirectories(m_path.getParent().getNative());
			}
			m_pointer = fopen(m_path.getNative().c_str(), "wb");
			break;
		case etk::io::OpenMode::Append:
			m_pointer = fopen(m_path.getNative().c_str(), "ab");
			break;
	}
	if(m_pointer == null) {
		TK_WARNING("Can not open the file '" << m_path.getNative() << "' mode: " << _mode << " errno" << errno << " (" << strerror(errno) << ")");
		return false;
	}
	return true;
}

bool etk::io::File::isOpen() {
	return m_pointer != null;
}

bool etk::io::File::close() {
	if (m_pointer == null) {
		TK_CRITICAL("File Already closed : " << m_path);
		return false;
	}
	fclose(m_pointer);
	m_pointer = null;
	return true;
}

uint64_t etk::io::File::size() {
	return etk::path::fileSize(m_path);
}

bool etk::io::File::seek(uint64_t _offset, enum etk::io::SeekMode _origin) {
	int originFS = 0;
	switch(_origin) {
		case etk::io::SeekMode::End:
			originFS = SEEK_END;
			break;
		case etk::io::SeekMode::Current:
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

int64_t etk::io::File::tell() {
	if (m_pointer != null) {
		return ftell(m_pointer);
	}
	return 0;
}

int64_t etk::io::File::read(void* _data, int64_t _blockSize, int64_t _nbBlock) {
	if (m_pointer == null) {
		TK_ERROR("Can not read in a file that is not open : " << m_path);
		return 0;
	}
	return fread(_data, _blockSize, _nbBlock, m_pointer);
}

int64_t etk::io::File::write(const void* _data, int64_t _blockSize, int64_t _nbBlock) {
	if (m_pointer == null) {
		TK_ERROR("Can not write in a file that is not open : " << m_path);
		return 0;
	}
	return fwrite(_data, _blockSize, _nbBlock, m_pointer);
}

