/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/archive/Zip.h>
#include <etk/types.h>

etk::archive::Zip::Zip(const std::string& _fileName) :
  etk::Archive(_fileName),
  m_ctx(NULL) {
	/* Open the zip file */
	m_ctx = unzOpen(m_fileName.c_str());
	if(!m_ctx) {
		TK_ERROR("Unable to open the zip file '" << m_fileName << "'");
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
		if(unzGetCurrentFileInfo(m_ctx, &tmpFileInfo, tmpFileName, FILENAME_MAX, NULL, 0, NULL, 0) != UNZ_OK) {
			TK_ERROR("Could not read file info from the zip file '" << m_fileName << "'");
			return;
		}
		if(tmpFileName[strlen(tmpFileName) - 1] == '/' ) {
			// find directory ...
		} else {
			m_content.insert(std::pair<std::string, etk::Archive::Content>(tmpFileName, etk::Archive::Content(tmpFileInfo.uncompressed_size)));
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

etk::archive::Zip::~Zip(void) {
	if (m_ctx!= NULL) {
		unzClose(m_ctx);
		m_ctx = NULL;
	};
}

void etk::archive::Zip::loadFile(const std::map<std::string, Content>::iterator& it) {
	TK_VERBOSE("Real load file : '" << it->first << "'");
	
	unzGoToFirstFile(m_ctx);
	
	// Store all the file in the standard structure
	for(uint32_t iii=0; iii<m_info.number_entry; iii++) {
		char tmpFileName[FILENAME_MAX];
		unz_file_info tmpFileInfo;
		/* Get info about current file. */
		if(unzGetCurrentFileInfo(m_ctx, &tmpFileInfo, tmpFileName, FILENAME_MAX, NULL, 0, NULL, 0) != UNZ_OK) {
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
			if(NULL == data) {
				TK_ERROR("Allocation error...");
				return;
			}
			/* read the file */
			do {
				error = unzReadCurrentFile(m_ctx, data, it->second.getTheoricSize());
				if ( error < 0 ) {
					TK_ERROR("Could not read file '" << tmpFileName << "' into the zip file '" << m_fileName << "': " <<  error);
					unzCloseCurrentFile(m_ctx);
					return;
				}
			} while ( error > 0 );
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
