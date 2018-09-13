/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL-2 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/io/Interface.hpp>
#include <etk/path/Path.hpp>
#include <ememory/SharedPtr.hpp>
#include <etk/archive/Archive.hpp>

namespace etk {
	namespace io {
		/**
		 * @brief System file interface.
		 */
		class ZipFile: public etk::io::Interface {
			private:
				etk::Path m_path; //!< Path to access in this interface
				ememory::SharedPtr<etk::Archive> m_archive; //!< Archive interface
				ememory::SharedPtr<etk::ArchiveContent> m_content; //!< Data in the archive file
				int32_t m_offset;
			public:
				ZipFile(ememory::SharedPtr<etk::Archive> _archive);
				ZipFile(const etk::Path& _path, ememory::SharedPtr<etk::Archive> _archive);
				ETK_CONSTRUCTOR_COPY_DELETE(ZipFile);
				ETK_CONSTRUCTOR_MOVE_DEFAULT(ZipFile);
			public:
				bool open(etk::io::OpenMode _mode) override;
				bool isOpen() override;
				bool close() override;
				uint64_t size() override;
				bool seek(uint64_t _offset, enum etk::io::SeekMode _origin) override;
				int64_t tell() override;
				void flush() override;
				int64_t read(void* _data, int64_t _blockSize, int64_t _nbBlock) override;
				int64_t write(const void* _data, int64_t _blockSize, int64_t _nbBlock) override;
		};
	}
}