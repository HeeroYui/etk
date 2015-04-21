/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#ifdef ETK_BUILD_MINIZIP

#include <etk/types.h>

#ifndef __ETK_ARCHIVE_H__
#define __ETK_ARCHIVE_H__

#include <map>

namespace etk {
	class ArchiveContent {
		private:
			int32_t m_link; //!< number of element open on this file
		public:
			void increaseRef() {
				m_link++;
			};
			void decreaseRef() {
				m_link--;
			};
			int32_t getNumberOfRef() const {
				return m_link;
			};
		private:
			int32_t m_theoricSize; //!< number of element open on this file
		public:
			int32_t getTheoricSize() const {
				return m_theoricSize;
			};
		private:
			std::vector<char> m_data;
		public:
			ArchiveContent(int32_t _basicSize=0) :
			  m_link(-1),
			  m_theoricSize(_basicSize) { };
			int32_t size() const {
				return m_data.size();
			};
			void* data() const {
				return (void*)&m_data[0];
			};
			std::vector<char>& getDataVector() {
				return m_data;
			};
	};
	class Archive {
		public:
			Archive(const std::string& _fileName) :
			  m_fileName(_fileName) {
				
			};
			virtual ~Archive() { };
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
			std::map<std::string, ArchiveContent> m_content;
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
			 * @param[in] _id Id of the file to load.
			 */
			virtual void loadFile(const std::map<std::string, ArchiveContent>::iterator& it) { };
		public:
			/**
			 * @brief Load an Achive with a specific name.
			 * @param[in] _fileName File name of the specific archive.
			 * @return A pointer an the specified archive, the user might delete it.
			 */
			static Archive* load(const std::string& _fileName);
			
			/**
			 * @brief Create an Achive with a specific name.
			 * @param[in] _fileName File name of the specific archive.
			 * @return A pointer an the specified archive. it is empty due to the fact of create a new archive file.
			 */
			//Archive* create(const std::u32string& _fileName);
	};
};
#endif

#endif