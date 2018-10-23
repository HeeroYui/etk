/**
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL-2 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/io/SeekMode.hpp>
#include <etk/io/OpenMode.hpp>
#include <etk/Vector.hpp>
#include <etk/String.hpp>

namespace etk {
	namespace io {
		/**
		 * @brief string class ...
		 */
		class Interface {
			public:
				/**
				 * @brief Virtualize destructor.
				 */
				virtual ~Interface() = default;
				/**
				 * @brief Open the file in Read mode
				 * @param[in] _mode Mode to open the IO
				 * @return true : action done
				 * @return false : action not done
				 */
				virtual bool open(etk::io::OpenMode _mode) = 0;
				/**
				 * @brief Check if the current file is Open
				 * @return true : File is open in write or in read
				 * @return false : File is NOT open in write or in read
				 */
				virtual bool isOpen() = 0;
				/**
				 * @brief Close the curent file
				 * @return true : action done
				 * @return false : action not done
				 */
				virtual bool close() = 0;
				/**
				 * @brief Get the File size
				 * @return the requested size
				 */
				virtual uint64_t size() = 0;
				/**
				 * @brief Get a unique data in the file
				 * @return the next element in the file.
				 */
				virtual char get();
				/**
				 * @brief Get a compleate line in a text file
				 * @param[out] _output the next element in the file.
				 * @return true The file is not ended.
				 * @return false The file is ended.
				 */
				virtual bool gets(etk::String& _output);
				/**
				 * @brief Write data on the file
				 * @param[in] _input data to write.
				 * @return true Write done corectly.
				 * @return false ErrorOn write.
				 */
				virtual bool put(char _input);
				/**
				 * @brief Write data on the file
				 * @param[in] _input data to write.
				 * @return true Write done corectly.
				 * @return false ErrorOn write.
				 */
				virtual bool puts(const etk::String& _input);
				/**
				 * @brief Move in the file Position
				 * @param[in] _offset Offset to apply at the file
				 * @param[in] _origin Origin  of the position
				 * @return true : action done
				 * @return false : action not done
				 */
				virtual bool seek(uint64_t _offset, enum etk::io::SeekMode _origin) = 0;
				/**
				 * @brief Get the position in the file.
				 * @return the requested position.
				 */
				virtual int64_t tell() = 0;
				/**
				 * @brief Flush the current file
				 */
				virtual void flush() = 0;
				/**
				 * @brief Read data from the file
				 * @param[in,out] _data Pointer on the buffer that might be set the data
				 * @param[in] _blockSize Size of one block of data
				 * @param[in] _nbBlock Number of block needed
				 * @return Number of element read (in block number)
				 */
				virtual int64_t read(void* _data, int64_t _blockSize, int64_t _nbBlock) = 0;
				/**
				 * @brief Write data on the file
				 * @param[in] _data Pointer on the buffer that might be set on the file
				 * @param[in] _blockSize Size of one block of data
				 * @param[in] _nbBlock Number of block needed
				 * @return Number of element written (in block number)
				 */
				virtual int64_t write(const void* _data, int64_t _blockSize, int64_t _nbBlock) = 0;
				/**
				 * @brief Read all element in a file and set it in a generic vector
				 * @return the read vector
				 */
				template<typename T> etk::Vector<T> readAll() {
					etk::Vector<T> value;
					value.resize(size());
					read(&value[0], sizeof(T), size()/sizeof(T));
					return value;
				}
				/**
				 * @brief Read all element in a file and set it in a generic etk::String
				 * @return the read string
				 */
				etk::String readAllString() {
					etk::String value;
					value.resize(size());
					read(&value[0], sizeof(char), size()/sizeof(char));
					return value;
				}
				/**
				 * @brief Write all the vector in a file
				 * @param[in] _value Data to write in the File
				 */
				template<typename T>
				void writeAll(const etk::Vector<T>& _value) {
					write(static_cast<const void*>(&(_value[0])), sizeof(T), _value.size()/sizeof(T));
				}
				/**
				 * @brief Write all the vector in a file
				 * @param[in] _value String data to write in the File
				 * @return true the file is fully correcty write
				 */
				bool writeAll(const etk::String& _value) {
					return int64_t(_value.size()) == write(static_cast<const void*>(&(_value[0])), sizeof(char), _value.size()/sizeof(char));
				}
				/**
				 * @brief Stream write mode
				 * @param[in] _data Stream to write
				 * @return The current FSNode reference to add other stream.
				 * @note not stable API ...
				 */
				etk::io::Interface& operator<< (const etk::Stream& _data);
				//! @copydoc etk::io::Interface::operator<<(const etk::Stringstream&)
				etk::io::Interface& operator<< (const etk::String& _data);
				//! @copydoc etk::io::Interface::operator<<(const etk::Stringstream&)
				etk::io::Interface& operator<< (const char* _data);
				//! @copydoc etk::io::Interface::operator<<(const etk::Stringstream&)
				etk::io::Interface& operator<< (const int32_t _data);
				//! @copydoc etk::io::Interface::operator<<(const etk::Stringstream&)
				etk::io::Interface& operator<< (const uint32_t _data);
				//! @copydoc etk::io::Interface::operator<<(const etk::Stringstream&)
				etk::io::Interface& operator<< (const float _data);
		};
	}
}
