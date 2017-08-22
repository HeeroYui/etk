/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL-2 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/debug.hpp>

namespace etk {
	/**
	 * @brief string class ...
	 */
	class String {
		public:
			class Iterator {
				private:
					size_t m_current; //!< current Id on the string
					String* m_string; //!< Pointer on the current element of the stringBin
				public:
					/**
					 * @brief Basic iterator constructor with no link with an etk::String
					 */
					Iterator():
					  m_current(0),
					  m_string(nullptr) {
						// nothing to do ...
					}
					/**
					 * @brief Recopy constructor on a specific etk::String.
					 * @param[in] _obj The Iterator that might be copy
					 */
					Iterator(const Iterator & _obj):
					  m_current(_obj.m_current),
					  m_string(_obj.m_string) {
						// nothing to do ...
					}
					/**
					 * @brief Assignation operator.
					 * @param[in] _otherIterator The Iterator that might be copy
					 * @return reference on the current Iterator
					 */
					Iterator& operator=(const Iterator & _otherIterator) {
						m_current = _otherIterator.m_current;
						m_string = _otherIterator.m_string;
						return *this;
					}
					/**
					 * @brief Basic destructor
					 */
					~Iterator() {
						m_current = 0;
						m_string = nullptr;
					}
					/**
					 * @brief basic boolean cast
					 * @return true if the element is present in the etk::String size
					 */
					operator bool () {
						return (m_current < m_string->size());
					}
					/**
					 * @brief Incremental operator
					 * @return Reference on the current iterator increment
					 */
					Iterator& operator++ () {
						if (    m_string != nullptr
						     && m_current < m_string->size() )
						{
							m_current++;
						}
						return *this;
					}
					/**
					 * @brief Decremental operator
					 * @return Reference on the current iterator decrement
					 */
					Iterator& operator-- () {
						if (    m_string != nullptr
						     && m_current > 0) {
							m_current--;
						}
						return *this;
					}
					/**
					 * @brief Incremental operator
					 * @return Reference on a new iterator and increment the other one
					 */
					Iterator operator++ (int32_t) {
						Iterator it(*this);
						++(*this);
						return it;
					}
					/**
					 * @brief Decremental operator
					 * @return Reference on a new iterator and decrement the other one
					 */
					Iterator operator-- (int32_t) {
						Iterator it(*this);
						--(*this);
						return it;
					}
					/**
					 * @brief Get reference on the current Element
					 * @return the reference on the current Element 
					 */
					ETK_VECTOR_TYPE & operator-> () const {
						TK_CHECK_INOUT(m_current < m_string->size());
						return &m_string->get(m_current);
					}
					/**
					 * @brief Get reference on the current Element
					 * @return the reference on the current Element 
					 */
					ETK_VECTOR_TYPE & operator* () const {
						TK_CHECK_INOUT(m_current < m_string->size());
						return m_string->get(m_current);
					}
				private:
					Iterator(String* _obj, int32_t _pos):
					  m_current(_pos),
					  m_string(_obj) {
						// nothing to do ...
					}
					friend class String;
			};
		private:
			std::string<char> m_data; //!< pointer on the current data (contain all time 1 element '\0')
		public:
			/**
			 * @brief Create an empty string
			 * @param[in] _count Minimum request size of the Buffer (allocated at '\0')
			 */
			String(int32_t _count = 0):
			  m_data() {
				m_data.resize(_count, '\0');
			}
			/**
			 * @brief Re-copy constructor (copy all needed data)
			 * @param[in] _obj String that might be copy
			 */
			String(const etk::String& _obj) {
				m_data = _obj.m_data;
			}
			/**
			 * @brief Destructor of the current Class
			 */
			~String() {
				// nothing to do...
			}
			/**
			 * @brief Swap the data of 2 Strings
			 * @param[in] _obj second string to swap data.
			 */
			void swap(etk::String& _obj) {
				// avoid Swap of itself
				if(this != &_obj) {
					m_data.swap(_obj.m_data);
				}
			}
			/**
			 * @brief Re-copy operator
			 * @param[in] _obj String that might be copy
			 * @return reference on the current re-copy string
			 */
			String& operator=(const etk::String & _obj) {
				if (this != &_obj) {
					m_data = _obj.m_data;
				}
				// Return the current pointer
				return *this;
			}
			
			/**
			 * @brief Add at the Last position of the String
			 * @param[in] _obj Element to add at the end of string
			 */
			String& operator+= (const etk::String& _obj) {
				size_t numberElement = _obj.size();
				size_t idElement = size();
				resize(m_data.size()+_obj.size());
				for (size_t iii=0; iii<_obj.size(); ++iii) {
					m_data[idElement+iii] = _obj[iii];
				}
				// Return the current pointer
				return *this;
			}
			/**
			 * @brief Get the number of element in the string
			 * @return The number requested
			 */
			size_t size() const {
				return m_size;
			}
			/**
			 * @brief Resize the string with a basic element
			 * @param[in] _newSize New size of the string
			 */
			void resize(size_t _newSize) {
				size_t idElement = size();
				resize(_newSize);
				if (m_size != _newSize) {
					TK_CRITICAL("error to resize string");
					return;
				}
				if (_newSize > idElement) {
					// initialize data ...
					for(size_t iii=idElement; iii<_newSize; iii++) {
						m_data[iii] = '\0';
					}
				}
			}
			/**
			 * @brief Get a current element in the string
			 * @param[in] _pos Desired position read
			 * @return Reference on the Element
			 */
			char& get(size_t _pos) {
				// NOTE :Do not change log level, this generate error only in debug mode
				return m_data[_pos];
			}
			/**
			 * @brief Get an copy Element an a special position
			 * @param[in] _pos Position in the string that might be get [0..Size()]
			 * @return An reference on the copy of selected element
			 */
			char& operator[] (size_t _pos) {
				return get(_pos);
			}
			/**
			 * @brief Get an Element an a special position
			 * @param[in] _pos Position in the string that might be get [0..Size()]
			 * @return An reference on the selected element
			 */
			const char operator[] (size_t _pos) const {
				// NOTE :Do not change log level, this generate error only in debug mode
				return m_data[_pos];
			}
			/**
			 * @brief Add at the First position of the String
			 * @param[in] _item Element to add at the end of string
			 */
			void pushFront(char _item) {
				insert(0, &_item, 1);
			}
			/**
			 * @brief Add at the Last position of the String
			 * @param[in] _item Pointer on a list of Element to add at the start of string
			 * @param[in] _nbElement Number of element to add.
			 */
			void pushFront(const char * _item, size_t _nbElement) {
				insert(0, _item, _nbElement);
			}
			/**
			 * @brief Add at the Last position of the String
			 * @param[in] _item Element to add at the end of string
			 */
			void pushBack(const char _item) {
				size_t idElement = m_size;
				resize(m_size+1);
				if (idElement < m_size) {
					m_data[idElement] = _item;
				} else {
					TK_ERROR("Resize does not work correctly ... not added item");
				}
			}
			/**
			 * @brief Add at the Last position of the String
			 * @param[in] _item Pointer on a list of Element to add at the end of string
			 * @param[in] _nbElement Number of element to add.
			 */
			void pushBack(const char* _item, size_t _nbElement) {
				if (_item == nullptr) {
					return;
				}
				size_t idElement = m_size;
				resize(m_size+_nbElement);
				if (idElement > m_size) {
					TK_ERROR("Resize does not work correctly ... not added item");
					return;
				}
				for (size_t iii=0; iii<_nbElement; iii++) {
					m_data[idElement+iii] = _item[iii];
				}
			}
			/**
			 * @brief Remove the last element of the string
			 */
			void popBack() {
				if(m_size>0) {
					resize(m_size-1);
				}
			}
			/**
			 * @brief Remove all element in the current string
			 */
			void clear() {
				if(m_size>0) {
					resize(0);
				}
			}
			/**
			 * @brief Insert N element in the String.
			 * @param[in] _pos Position to add the elements.
			 * @param[in] _item Pointer on a table of the elements to add.
			 * @param[in] _nbElement Number of element to add in the String
			 */
			void insert(size_t _pos, const char* _item, size_t _nbElement) {
				if (_pos>m_size) {
					TK_WARNING(" can not insert Element at this position : " << _pos << " > " << m_size << " add it at the end ... ");
					pushBack(_item, _nbElement);
					return;
				}
				size_t idElement = m_size;
				// Request resize of the current buffer
				resize(m_size+_nbElement);
				if (idElement>=m_size) {
					TK_ERROR("Resize does not work correctly ... not added item");
					return;
				}
				// move current data (after the position)
				size_t sizeToMove = (idElement - _pos);
				if ( 0 < sizeToMove) {
					for (size_t iii=1; iii<=sizeToMove; iii++) {
						m_data[m_size-iii] = m_data[idElement-iii];
					}
				}
				// affectation of all input element
				for (size_t iii=0; iii<_nbElement; iii++) {
					m_data[_pos+iii] = _item[iii];
				}
			}
			/**
			 * @brief Insert one element in the String at a specific position
			 * @param[in] _pos Position to add the elements.
			 * @param[in] _item Element to add.
			 */
			void insert(size_t _pos, const char _item) {
				insert(_pos, &_item, 1);
			}
			/**
			 * @brief Remove N element
			 * @param[in] _pos Position to remove the data
			 * @param[in] _nbElement number of element to remove
			 */
			void eraseLen(size_t _pos, size_t _nbElement) {
				if (_pos>m_size) {
					TK_ERROR(" can not Erase Len Element at this position : " << _pos << " > " << m_size);
					return;
				}
				if (_pos+_nbElement>m_size) {
					_nbElement = m_size - _pos;
				}
				size_t idElement = m_size;
				// move current data
				size_t sizeToMove = (idElement - (_pos+_nbElement));
				if ( 0 < sizeToMove) {
					for (size_t iii=0; iii<sizeToMove; iii++) {
						m_data[_pos+iii] = m_data[_pos+_nbElement+iii];
					}
				}
				// Request resize of the current buffer
				resize(m_size-_nbElement);
			}
			/**
			 * @brief Remove one element
			 * @param[in] _pos Position to remove the data
			 */
			inline void erase(size_t _pos) {
				eraseLen(_pos, 1);
			}
			/**
			 * @brief Remove one element
			 * @param[in] _pos Position to remove the data
			 */
			inline void remove(size_t _pos) {
				eraseLen(_pos, 1);
			}
			/**
			 * @brief Remove N elements
			 * @param[in] _pos Position to remove the data
			 * @param[in] _posEnd Last position number
			 */
			void erase(size_t _pos, size_t _posEnd) {
				if (_pos>m_size) {
					TK_ERROR(" can not Erase Element at this position : " << _pos << " > " << m_size);
					return;
				}
				if (_posEnd>m_size) {
					_posEnd = m_size;
				}
				size_t nbElement = m_size - _pos;
				size_t tmpSize = m_size;
				// move current data
				size_t sizeToMove = (tmpSize - (_pos+nbElement));
				if ( 0 < sizeToMove) {
					for (size_t iii=0; iii<sizeToMove; iii++) {
						m_data[_pos+iii] = m_data[_pos+nbElement+iii];
					}
				}
				// Request resize of the current buffer
				resize(m_size-nbElement);
			}
			/**
			 * @brief extract data between two point : 
			 * @param[in] _posStart start position to extract data
			 * @param[in] _posEnd End position to extract data
			 * @return the extracted string
			 */
			etk::String extract(size_t _posStart = 0, size_t _posEnd=0x7FFFFFFF) const {
				etk::String out;
				if (_posStart >= size() ) {
					return out;
				}
				if (_posEnd >= size() ) {
					_posEnd = size();
				}
				out.pushBack(&m_data[_posStart], _posEnd-_posStart);
				return out;
			}
			/**
			 * @brief Get the pointer on the data
			 * @return pointer on the "C" string
			 */
			const char* c_str() const {
				return &m_data[0];
			}
			/**
			 * @brief Get an iterator an an specific position
			 * @param[in] _pos Requested position of the iterator in the string
			 * @return The Iterator
			 */
			Iterator position(size_t _pos) {
				return iterator(this, _pos);
			}
			/**
			 * @brief Get an Iterator on the start position of the String
			 * @return The Iterator
			 */
			Iterator begin() {
				return position(0);
			}
			/**
			 * @brief Get an Iterator on the end position of the String
			 * @return The Iterator
			 */
			Iterator end() {
				return position( size()-1 );
			}
		private:
			/**
			 * @brief Change the current size of the string
			 * @param[in] _newSize New requested size of element in the string
			 */
			void resize(size_t _newSize) {
				size_t oldSize = m_data.size();
				m_data.resize(_newSize + 1);
				// in all case ==> we have the last element that is '\0'
				m_data[_newSize] = '\0';
				// Clear all end data to prevent errors
				for (size_t iii=oldSize; iii<_newSize; ++iii) {
					m_data[iii] = '\0';
				}
			}
		public :
			/*****************************************************
			 *    == operator
			 *****************************************************/
			bool operator== (const String& _obj) const {
				// check if it was the same pointer
				if( this == &_obj ) {
					return true;
				}
				// first step : check the size ...
				if (m_size != _obj.m_size) {
					return false;
				}
				for (size_t iii=0; iii<m_data.size(); ++iii) {
					if (m_data[iii] != _obj.m_data[iii]) {
						return false;
					}
				}
				return true;
			}
			/*****************************************************
			 *    != operator
			 *****************************************************/
			bool operator!= (const String& _obj) const {
				// check if it was the same pointer
				if( this == &_obj ) {
					return false;
				}
				// first step : check the size ...
				if (m_size != _obj.m_size) {
					return true;
				}
				for (size_t iii=0; iii<m_data.size(); ++iii) {
					if (m_data[iii] != _obj.m_data[iii]) {
						return true;
					}
				}
				return false;
			}
	};
}
