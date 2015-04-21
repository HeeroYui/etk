/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ETK_ARCHIVE_ZIP_H__
#define __ETK_ARCHIVE_ZIP_H__

#include <etk/archive/Archive.h>
#ifdef ETK_BUILD_MINIZIP
	extern "C" {
		#include <minizip/unzip.h>
	}
	namespace etk {
		namespace archive {
			class Zip : public etk::Archive {
				private:
					unzFile m_ctx; //!< mini zip context
					unz_global_info m_info; //!< global information of the Zip
				public:
					Zip(const std::string& _fileName);
					virtual ~Zip();
				protected: // herited functions :
					virtual void loadFile(const std::map<std::string, ArchiveContent>::iterator& it);
			};
		};
	};

#endif

#endif

