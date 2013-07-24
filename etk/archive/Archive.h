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
					etk::Vector<char> m_data; // if null ==> this is a folder...
				public:
					Content(esize_t _basicSize=0) : m_data(_basicSize) { };
					esize_t Size(void) const { return m_data.Size(); };
					void* Data(void) { return (void*)m_data.DataPointer(); };
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
			 * @brief Display all Element in the archive
			 */
			void Display(void);
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

