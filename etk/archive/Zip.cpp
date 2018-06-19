/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#ifdef ETK_BUILD_MINIZIP

#include <etk/archive/Zip.hpp>
#include <etk/types.hpp>
#include <etk/debug.hpp>
#include <etk/typeInfo.hpp>

ETK_DECLARE_TYPE(etk::archive::Zip);

etk::archive::Zip::Zip(const etk::String& _fileName, uint64_t _offset) :
  etk::Archive(_fileName),
  m_ctx(null) {
	/* Open the zip file */
	m_ctx = unzOpenOffset(m_fileName.c_str(), _offset);
	if(!m_ctx) {
		TK_ERROR("Unable to open the zip file '" << m_fileName << "' offset=" << _offset);
		return;
	}
	/* Get info about the zip file */
	if(unzGetGlobalInfo(m_ctx, &m_info) != UNZ_OK) {
		TK_ERROR("Unable to read the global info related to the '" << m_fileName << "' zip file");
		return;
	}
	
	// Store all the file in the standard structure
	for(uint32_t iii=0; iii<m_info.number_entry; iii++) {
		char tmpFileName[FILENAME_MAX];
		unz_file_info tmpFileInfo;
		/* Get info about current file. */
		if(unzGetCurrentFileInfo(m_ctx, &tmpFileInfo, tmpFileName, FILENAME_MAX, null, 0, null, 0) != UNZ_OK) {
			TK_ERROR("Could not read file info from the zip file '" << m_fileName << "'");
			return;
		}
		if(tmpFileName[strlen(tmpFileName) - 1] == '/' ) {
			// find directory ...
		} else {
			TK_INFO("find file : " << tmpFileName);
			m_content.set(tmpFileName, etk::ArchiveContent(tmpFileInfo.uncompressed_size));
		}
		/* Go the the next entry listed in the zip file. */
		if((iii+1) < m_info.number_entry) {
			if (unzGoToNextFile(m_ctx) != UNZ_OK) {
				TK_ERROR("Could not read next file from the zip file '" << m_fileName << "'");
				return;
			}
		}
	}
}

etk::archive::Zip::~Zip() {
	if (m_ctx!= null) {
		unzClose(m_ctx);
		m_ctx = null;
	};
}

void etk::archive::Zip::loadFile(const etk::Map<etk::String, ArchiveContent>::Iterator& it) {
	TK_VERBOSE("Real load file : '" << it->first << "'");
	
	unzGoToFirstFile(m_ctx);
	
	// Store all the file in the standard structure
	for(uint32_t iii=0; iii<m_info.number_entry; iii++) {
		char tmpFileName[FILENAME_MAX];
		unz_file_info tmpFileInfo;
		/* Get info about current file. */
		if(unzGetCurrentFileInfo(m_ctx, &tmpFileInfo, tmpFileName, FILENAME_MAX, null, 0, null, 0) != UNZ_OK) {
			TK_ERROR("Could not read file info from the zip file '" << m_fileName << "'");
			return;
		}
		if (it->first == tmpFileName ) {
			// Entry is a file, so extract it.
			if(unzOpenCurrentFile(m_ctx) != UNZ_OK) {
				TK_ERROR("Could not open file '" << it->first << "' into the zip file '" << m_fileName << "'");
				return;
			}
			int error = UNZ_OK;
			// request the resize of the data :
			it->second.getDataVector().resize(it->second.getTheoricSize(), 0);
			void* data = it->second.data();
			if(data == null) {
				TK_ERROR("Allocation error...");
				return;
			}
			/* read the file */
			do {
				error = unzReadCurrentFile(m_ctx, data, it->second.getTheoricSize());
				if (error < 0) {
					TK_ERROR("Could not read file '" << tmpFileName << "' into the zip file '" << m_fileName << "': " <<  error);
					unzCloseCurrentFile(m_ctx);
					return;
				}
			} while (error > 0);
			//((char*)data)[m_content.GetValue(_id).GetTheoricSize()] = '\0';
			// stop searching here
			unzCloseCurrentFile(m_ctx);
			return;
		}
		unzCloseCurrentFile(m_ctx);
		
		/* Go the the next entry listed in the zip file. */
		if((iii+1) < m_info.number_entry) {
			if (unzGoToNextFile(m_ctx) != UNZ_OK) {
				TK_ERROR("Could not read next file from the zip file '" << m_fileName << "'");
				return;
			}
		}
	}
}
#endif
