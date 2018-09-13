/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL-2 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/io/Interface.hpp>
#include <etk/io/File.hpp>
#include <etk/path/Path.hpp>

namespace etk {
	namespace io {
		/**
		 * @brief System file interface.
		 */
		class File: public etk::io::Interface {
			private:
				etk::Path m_path; //!< Path to access in this interface
				FILE * m_pointer = null; //!< Generic file accesss.
			public:
				File();
				File(const etk::Path& _path);
				~File();
				ETK_CONSTRUCTOR_COPY_DELETE(File);
				ETK_CONSTRUCTOR_MOVE_DEFAULT(File);
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