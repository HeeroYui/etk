/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/archive/Archive.hpp>
#ifdef ETK_BUILD_MINIZIP
	extern "C" {
		#include <minizip/unzip.h>
	}
	namespace etk {
		/**
		 * @brief Zip file acces are set in a archive namespace
		 */
		namespace archive {
			/**
			 * @brief Zip acces interface (wrapper)
			 */
			class Zip : public etk::Archive {
				private:
					unzFile m_ctx; //!< mini zip context
					unz_global_info m_info; //!< global information of the Zip
				public:
					/**
					 * @brief constructor of a zip file access
					 * @param[in] _fileName File to parse (.zip / .apk)
					 * @param[in] _offset Offset in the file where to start the parsing of the "zip"
					 */
					Zip(const etk::Path& _fileName, uint64_t _offset = 0LL);
					/**
					 * @brief basic destructor
					 */
					virtual ~Zip();
				protected:
					void loadFile(const etk::Map<etk::Path, ememory::SharedPtr<ArchiveContent>>::Iterator& _it) override;
			};
		}
	}

#endif


