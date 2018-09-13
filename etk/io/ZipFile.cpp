/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL-2 (see license file)
 */
#include <etk/types.hpp>
#include <etk/io/ZipFile.hpp>
#include <etk/debug.hpp>

etk::io::ZipFile::ZipFile(ememory::SharedPtr<etk::Archive> _archive):
  m_archive(_archive) {
	// nothing to do.
}
etk::io::ZipFile::ZipFile(const etk::Path& _path, ememory::SharedPtr<etk::Archive> _archive):
  m_path(_path),
  m_archive(_archive) {
	
}

bool etk::io::ZipFile::open(etk::io::OpenMode _mode) {
	if (m_content != null) {
		TK_CRITICAL("File Already open: " << m_path);
		return true;
	}
	if (m_archive == null) {
		return false;
	}
	TK_VERBOSE(" Read file : " << m_path);
	switch (_mode) {
		case etk::io::OpenMode::Read:
			if (m_archive->exist(m_path) == false) {
				return false;
			}
			m_content = m_archive->getContent(m_path);
			if (m_content == null) {
				return false;
			}
			m_archive->open(m_path);
			return true;
		case etk::io::OpenMode::Write:
			return false;
		case etk::io::OpenMode::Append:
			return false;
	}
	return false;
}

bool etk::io::ZipFile::isOpen() {
	if (m_content != null) {
		return true;
	}
	return false;
}

bool etk::io::ZipFile::close() {
	if (m_content == null) {
		TK_CRITICAL("File Already closed : " << m_path);
		return false;
	}
	m_archive->close(m_path);
	m_content = null;
	m_offset = 0;
	return true;
}

uint64_t etk::io::ZipFile::size() {
	if (m_content == null) {
		TK_CRITICAL("Can not access to the size: " << m_path);
		return false;
	}
	return m_content->getTheoricSize();
}


bool etk::io::ZipFile::seek(uint64_t _offset, enum etk::io::SeekMode _origin) {
	if (m_content == null) {
		return false;
	}
	int32_t positionEnd = 0;
	switch(_origin) {
		case etk::io::SeekMode::End:
			positionEnd = m_content->size();
			break;
		case etk::io::SeekMode::Current:
			positionEnd = m_offset;
			break;
		default:
			positionEnd = 0;
			break;
	}
	positionEnd += _offset;
	if (positionEnd < 0) {
		positionEnd = 0;
	} else if (positionEnd > m_content->size()) {
		positionEnd = m_content->size();
	}
	m_offset = positionEnd;
	return true;
}

void etk::io::ZipFile::flush() {
	// nothing to do.
}

int64_t etk::io::ZipFile::tell() {
	if (m_content == null) {
		return 0;
	}
	return m_offset;
}

int64_t etk::io::ZipFile::read(void* _data, int64_t _blockSize, int64_t _nbBlock) {
	if (m_content == null) {
		((char*)_data)[0] = '\0';
		return 0;
	}
	int32_t dataToRead = _blockSize * _nbBlock;
	if (dataToRead + m_offset > m_content->size()) {
		_nbBlock = ((m_content->size() - m_offset) / _blockSize);
		dataToRead = _blockSize * _nbBlock;
	}
	memcpy(_data, &((char*)m_content->data())[m_offset], dataToRead);
	m_offset += dataToRead;
	return _nbBlock;
}

int64_t etk::io::ZipFile::write(const void* _data, int64_t _blockSize, int64_t _nbBlock) {
	TK_CRITICAL("Can not write on data inside APK : " << m_path);
	return 0;
}

