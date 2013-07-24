/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_ARCHIVE_H__
#define __ETK_ARCHIVE_H__

#include <etk/UString.h>
#include <etk/Vector.h>
#include <etk/Hach.h>

namespace etk
{
	class Archive
	{
		public:
			class Content
			{
				private:
					int32_t m_link; //!< number of element open on this file
				public:
					void IncreaseRef(void) { m_link++; };
					void DecreaseRef(void) { m_link--; };
					int32_t GetNumberOfRef(void) const { return m_link; };
				private:
					esize_t m_theoricSize; //!< number of element open on this file
				public:
					esize_t GetTheoricSize(void) const { return m_theoricSize; };
				private:
					etk::Vector<char> m_data;
				public:
					Content(esize_t _basicSize=0) : m_link(-1), m_theoricSize(_basicSize) { };
					esize_t Size(void) const { return m_data.Size(); };
					void* Data(void) const { return (void*)&m_data[0]; };
					etk::Vector<char>& GetDataVector(void) { return m_data; };
			};
		public:
			Archive(const etk::UString& _fileName) : m_fileName(_fileName) { };
			virtual ~Archive(void) { };
		protected:
			etk::UString m_fileName; //!< File name when it came from an file
		public:
			/**
			 * @brief Get the current file name.
			 * @return the requested file name.
			 */
			const etk::UString& GetFileName(void) { return m_fileName; };
		protected:
			etk::Hash<Content> m_content;
		public:
			/**
			 * @brief Get the number of elements
			 * @return nb files in the archive
			 */
			esize_t Size(void) const { return m_content.Size(); };
			/**
			 * @brief Get the File name of the ID
			 * @param[in] _id id of the element (must be < Size())
			 * @return FileName of the requested id
			 */
			const etk::UString& GetName(esize_t _id) const { return m_content.GetKey(_id); };
			/**
			 * @brief Get the File name of the ID
			 * @param[in] _id id of the element (must be < Size())
			 * @return the archive content
			 */
			const Content& GetContent(esize_t _id) const { return m_content.GetValue(_id); };
			/**
			 * @brief Get the File name of the ID
			 * @param[in] _key name of the file
			 * @return FileName of the requested id
			 */
			const Content& GetContent(const etk::UString& _key) const;
			/**
			 * @brief Check if a file exist
			 * @param[in] _key Name of the file
			 * @return true if the file is present
			 */
			bool Exist(const etk::UString& _key) const { return m_content.Exist(_key); };
			/**
			 * @brief Load the specific file in the memory
			 * @param[in] _key Name of the file
			 */
			void Open(const etk::UString& _key);
			/**
			 * @brief Un-Load the specific file from the memory
			 * @param[in] _key Name of the file
			 */
			void Close(const etk::UString& _key);
			/**
			 * @brief Display all Element in the archive
			 */
			void Display(void);
		protected:
			/**
			 * @brief Request the load in memory of the concerned file.
			 * @param[in] _id Id of the file to load.
			 */
			virtual void LoadFile(int32_t _id) { };
		public:
			/**
			 * @brief Load an Achive with a specific name.
			 * @param[in] _fileName File name of the specific archive.
			 * @return A pointer an the specified archive, the user might delete it.
			 */
			static Archive* Load(const etk::UString& _fileName);
			
			/**
			 * @brief Create an Achive with a specific name.
			 * @param[in] _fileName File name of the specific archive.
			 * @return A pointer an the specified archive. it is empty due to the fact of create a new archive file.
			 */
			//Archive* Create(const etk::UString& _fileName);
	};
};
#endif

