/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#ifdef ETK_BUILD_MINIZIP

#include <etk/types.h>

#pragma once

#include <map>
#include <mutex>
#include <memory>

namespace etk {
	/**
	 * @brief Element of the archive (with associated data)
	 */
	class ArchiveContent {
		private:
			int32_t m_link; //!< number of element open on this file
		public:
			/**
			 * @brief Increment the number of user of this resource (permit to keep data alive)
			 */
			void increaseRef() {
				m_link++;
			}
			/**
			 * @brief Release reference on this data
			 */
			void decreaseRef() {
				m_link--;
			}
			/**
			 * @brief Get the number of user link with this reference
			 * @return Count of user connected
			 */
			int32_t getNumberOfRef() const {
				return m_link;
			}
		private:
			int32_t m_theoricSize; //!< Size set by the zip file (theoric ==> the data has not been read)
		public:
			/**
			 * @brief Get the size of the element (size set by Zip file (not read))
			 * @return the size in Byte of the file
			 */
			int32_t getTheoricSize() const {
				return m_theoricSize;
			}
		private:
			std::vector<char> m_data; //!< Data read from the zip file (if m_data.size() != m_theoricSize the data is not read)
		public:
			/**
			 * @brief Basic constructor of an element
			 * @param[in] _basicSize Size of the zip element
			 */
			ArchiveContent(int32_t _basicSize=0) :
			  m_link(-1),
			  m_theoricSize(_basicSize) {
				
			}
			/**
			 * @brief Get the size of the Data loaded
			 * @return number of Byte loaded.
			 */
			int32_t size() const {
				return m_data.size();
			}
			/**
			 * @brief Get the pointer on the data read from the zip file
			 * @return void pointer on the data.
			 */
			void* data() const {
				return (void*)&m_data[0];
			}
			/**
			 * @brief Get the Data Vector on the file.
			 * @return Vector on the data.
			 */
			std::vector<char>& getDataVector() {
				return m_data;
			}
	};
	/**
	 * @brief Access on a zip data file
	 */
	class Archive {
		private:
			mutable std::mutex m_mutex; //!< access mutex (mini-zip does not support multiple access)
		public:
			/**
			 * @brief Contructor of the archive element
			 * @param[in] _fileName Zip file name (or .apk for android)
			 */
			Archive(const std::string& _fileName) :
			  m_fileName(_fileName) {
				
			};
			/**
			 * @brief Generic Destructor of the archive element
			 */
			virtual ~Archive() = default;
		protected:
			std::string m_fileName; //!< File name when it came from an file
		public:
			/**
			 * @brief Get the current file name.
			 * @return the requested file name.
			 */
			const std::string& getFileName() {
				return m_fileName;
			};
		protected:
			std::map<std::string, ArchiveContent> m_content; //!< list of element of the zip file
		public:
			/**
			 * @brief Get the number of elements
			 * @return nb files in the archive
			 */
			int32_t size() const {
				return m_content.size();
			};
			/**
			 * @brief Get the File name of the ID
			 * @param[in] _id id of the element (must be < Size())
			 * @return FileName of the requested id
			 */
			const std::string& getName(size_t _id) const;
			/**
			 * @brief Get the File name of the ID
			 * @param[in] _id id of the element (must be < Size())
			 * @return the archive content
			 */
			const ArchiveContent& getContent(size_t _id) const;
			/**
			 * @brief Get the File name of the ID
			 * @param[in] _key name of the file
			 * @return FileName of the requested id
			 */
			const ArchiveContent& getContent(const std::string& _key) const;
			/**
			 * @brief Check if a file exist
			 * @param[in] _key Name of the file
			 * @return true if the file is present
			 */
			bool exist(const std::string& _key) const;
			/**
			 * @brief Load the specific file in the memory
			 * @param[in] _key Name of the file
			 */
			void open(const std::string& _key);
			/**
			 * @brief Un-Load the specific file from the memory
			 * @param[in] _key Name of the file
			 */
			void close(const std::string& _key);
			/**
			 * @brief Display all Element in the archive
			 */
			void display();
		protected:
			/**
			 * @brief Request the load in memory of the concerned file.
			 * @param[in] _it Iterator on the element.
			 */
			virtual void loadFile(const std::map<std::string, ArchiveContent>::iterator& _it) { };
		public:
			/**
			 * @brief Load an Achive with a specific name.
			 * @param[in] _fileName File name of the specific archive.
			 * @return A pointer an the specified archive, the user might delete it.
			 */
			static Archive* load(const std::string& _fileName);
			/**
			 * @brief Load an Achive with a specific name in package mode ==> this mean the data is associated with the basic binary.
			 * @param[in] _fileName File name of the specific archive.
			 * @return A pointer an the specified archive, the user might delete it.
			 */
			static Archive* loadPackage(const std::string& _fileName);
	};
}
#endif
