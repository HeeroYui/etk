/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL-2 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/debug.hpp>
#include <etk/Vector.hpp>

namespace etk {
	template<class ETK_ITERATOR_TYPE>
	size_t distance(const ETK_ITERATOR_TYPE& _start, const ETK_ITERATOR_TYPE& _stop) {
		size_t out = 0;
		ETK_ITERATOR_TYPE tmp = _start;
		while (tmp != _stop) {
			out++;
			++tmp;
		}
		return out;
	}
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
					char operator* () const {
						TK_ASSERT(m_current < m_string->size(), "out of range");
						return m_string->get(m_current);
					}
					/**
					 * @brief Get reference on the current Element
					 * @return the reference on the current Element 
					 */
					char& operator* () {
						TK_ASSERT(m_current < m_string->size(), "out of range");
						return m_string->get(m_current);
					}
					/*****************************************************
					 *    == operator
					 *****************************************************/
					bool operator== (const Iterator& _obj) const {
						// check if it was the same pointer
						if( this == &_obj ) {
							return true;
						}
						if (m_current != _obj.m_current) {
							return false;
						}
						if (m_string != _obj.m_string) {
							return false;
						}
						return true;
					}
					/*****************************************************
					 *    != operator
					 *****************************************************/
					bool operator!= (const Iterator& _obj) const {
						// check if it was the same pointer
						if( this == &_obj ) {
							return false;
						}
						if (m_current != _obj.m_current) {
							return true;
						}
						if (m_string != _obj.m_string) {
							return true;
						}
						return false;
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
			etk::Vector<char> m_data; //!< pointer on the current data (contain all time 1 element '\0')
		public:
			static const size_t npos = size_t(-1);
			/**
			 * @brief Create an empty string
			 */
			String():
			  m_data() {
				m_data.resize(1, '\0');
			}
			/**
			 * @brief Copy constructor (copy all data)
			 * @param[in] _obj String that might be copy
			 */
			String(const etk::String& _obj) {
				m_data = _obj.m_data;
			}
			/**
			 * @brief Partial copy constructor (copy all needed data)
			 * @param[in] _obj String that might be copy (part of it)
			 * @param[in] _pos Start position to copy data
			 * @param[in] _size Number of element to copy in the string
			 */
			String(const etk::String& _obj, size_t _pos, size_t _size = etk::String::npos) {
				if (_pos + _size >= _obj.size()) {
					_size = etk::String::npos;
				}
				if (_size != etk::String::npos) {
					resize(_size);
					for (size_t iii=0; iii<_size; ++iii) {
						m_data[iii] = _obj.m_data[_pos+iii];
					}
					return;
				}
				resize(_obj.size()-_pos);
				for (size_t iii=0; iii<_obj.size()-_pos; ++iii) {
					m_data[iii] = _obj.m_data[_pos+iii];
				}
			}
			/**
			 * @brief Copy the null-terminated C string.
			 * @param[in] _obj C string that might be copy (end by '\0')
			 */
			String(const char* _obj) {
				if (_obj == nullptr) {
					resize(0);
					return;
				}
				uint32_t size = strlen(_obj);
				resize(size);
				for (size_t iii=0; iii<size; ++iii) {
					m_data[iii] = _obj[iii];
				}
			}
			/**
			 * @brief Partial copy of the null-terminated C string.
			 * @param[in] _obj String that might be copyC string that might be copy (end by '\0')
			 * @param[in] _size Number of element to copy.
			 */
			String(const char* _obj, size_t _size) {
				if (    _obj == nullptr
				     || _size == 0) {
					resize(0);
					return;
				}
				uint32_t size = strlen(_obj);
				if (_size < size) {
					size = _size;
				}
				resize(size);
				for (size_t iii=0; iii<size; ++iii) {
					m_data[iii] = _obj[iii];
				}
			}
			/**
			 * @brief Fills the string with _size consecutive copies of character _val.
			 * @param[in] _size Number of element in the string
			 * @param[in] _val Value to set in the string
			 */
			String(size_t _size, char _val) {
				resize(_size);
				for (size_t iii=0; iii<_size; ++iii) {
					m_data[iii] = _val;
				}
			}
			/**
			 * @brief Copy all element betewwen the 2 iterator of the new string.
			 * @param[in] _start Start iterator of adding value.
			 * @param[in] _stop Start iterator of adding value.
			 */
			String(Iterator _start, Iterator _stop) {
				size_t size = etk::distance(_start, _stop);
				resize(size);
				Iterator it = begin();
				while (_start != _stop) {
					*it++ = *_start++;
				}
			}
			
			/**
			 * @brief Move constructor
			 * @param[in] _obj String that might be move inside
			 */
			String(String&& _obj) noexcept {
				m_data = std::move(_obj.m_data);
			}
			/**
			 * @brief Set constructor
			 * @param[in] _value Char element to set in the string
			 */
			String(char _value) {
				resize(1);
				m_data[0] = _value;
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
			String& operator=(const etk::String& _obj) {
				if (this != &_obj) {
					m_data = _obj.m_data;
				}
				// Return the current pointer
				return *this;
			}
			/**
			 * @brief Re-copy operator
			 * @param[in] _obj C string terminated with '\0'
			 * @return reference on the current re-copy string
			 */
			String& operator=(const char* _obj) {
				clear();
				if (_obj == nullptr) {
					return *this;
				}
				size_t numberElement = strlen(_obj);
				resize(numberElement);
				for (size_t iii=0; iii<numberElement; ++iii) {
					m_data[iii] = _obj[iii];
				}
				// Return the current pointer
				return *this;
			}
			/**
			 * @brief Re-copy operator
			 * @param[in] _value Char value to set in the string
			 * @return reference on the current re-copy string
			 */
			String& operator=(char _value) {
				resize(1);
				m_data[0] = _value;
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
				resize(size()+_obj.size());
				for (size_t iii=0; iii<_obj.size(); ++iii) {
					m_data[idElement+iii] = _obj[iii];
				}
				// Return the current pointer
				return *this;
			}
			/**
			 * @brief Add at the Last position of the String
			 * @param[in] _obj C string terminated with '\0'
			 */
			String& operator+= (const char* _obj) {
				if (_obj == nullptr) {
					return *this;
				}
				size_t numberElement = strlen(_obj);
				size_t idElement = size();
				resize(size() + numberElement);
				for (size_t iii=0; iii<numberElement; ++iii) {
					m_data[idElement+iii] = _obj[iii];
				}
				// Return the current pointer
				return *this;
			}
			/**
			 * @brief Add at the Last position of the String
			 * @param[in] _value Simple character to add.
			 */
			String& operator+= (char _value) {
				pushBack(_value);
				// Return the current pointer
				return *this;
			}
			/**
			 * @brief Get the number of element in the string
			 * @return The number requested
			 */
			size_t size() const {
				return m_data.size() - 1; // remove '\0'
			}
			/**
			 * @brief Get a current element in the string
			 * @param[in] _pos Desired position read
			 * @return Reference on the Element
			 */
			char& get(size_t _pos) {
				return m_data[_pos];
			}
			/**
			 * @brief Get an copy Element an a special position
			 * @param[in] _pos Position in the string that might be get [0..Size()]
			 * @return An reference on the copy of selected element
			 */
			char& operator[] (size_t _pos) {
				return m_data[_pos];
			}
			/**
			 * @brief Get an Element an a special position
			 * @param[in] _pos Position in the string that might be get [0..Size()]
			 * @return An reference on the selected element
			 */
			const char operator[] (size_t _pos) const {
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
				size_t idElement = size();
				resize(size()+1);
				if (idElement < size()) {
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
				size_t idElement = size();
				resize(size()+_nbElement);
				if (idElement > size()) {
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
				if(size()>0) {
					resize(size()-1);
				}
			}
			/**
			 * @brief Remove all element in the current string
			 */
			void clear() {
				resize(0);
			}
			/**
			 * @brief Insert N element in the String.
			 * @param[in] _pos Position to add the elements.
			 * @param[in] _item Pointer on a table of the elements to add.
			 * @param[in] _nbElement Number of element to add in the String
			 */
			void insert(size_t _pos, const char* _item, size_t _nbElement) {
				if (_pos>size()) {
					TK_WARNING(" can not insert Element at this position : " << _pos << " > " << size() << " add it at the end ... ");
					pushBack(_item, _nbElement);
					return;
				}
				size_t idElement = size();
				// Request resize of the current buffer
				resize(size()+_nbElement);
				if (idElement>=size()) {
					TK_ERROR("Resize does not work correctly ... not added item");
					return;
				}
				// move current data (after the position)
				size_t sizeToMove = (idElement - _pos);
				if ( 0 < sizeToMove) {
					for (size_t iii=1; iii<=sizeToMove; iii++) {
						m_data[size()-iii] = m_data[idElement-iii];
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
			void erase(size_t _pos, size_t _nbElement=1) {
				if (_pos>size()) {
					TK_ERROR(" can not Erase Len Element at this position : " << _pos << " > " << size());
					return;
				}
				if (_pos+_nbElement>size()) {
					_nbElement = size() - _pos;
				}
				size_t idElement = size();
				// move current data
				size_t sizeToMove = (idElement - (_pos+_nbElement));
				if ( 0 < sizeToMove) {
					for (size_t iii=0; iii<sizeToMove; iii++) {
						m_data[_pos+iii] = m_data[_pos+_nbElement+iii];
					}
				}
				// Request resize of the current buffer
				resize(size() - _nbElement);
			}
			/**
			 * @brief Remove N elements
			 * @param[in] _pos Position to remove the data
			 * @param[in] _posEnd Last position number
			 */
			void eraseRange(size_t _pos, size_t _posEnd) {
				if (_pos>size()) {
					TK_ERROR(" can not Erase Element at this position : " << _pos << " > " << size());
					return;
				}
				if (_posEnd > size()) {
					_posEnd = size();
				}
				size_t nbElement = size() - _pos;
				size_t tmpSize = size();
				// move current data
				size_t sizeToMove = (tmpSize - (_pos+nbElement));
				if ( 0 < sizeToMove) {
					for (size_t iii=0; iii<sizeToMove; iii++) {
						m_data[_pos+iii] = m_data[_pos+nbElement+iii];
					}
				}
				// Request resize of the current buffer
				resize(size()-nbElement);
			}
			/**
			 * @brief extract data between two point : 
			 * @param[in] _posStart start position to extract data
			 * @param[in] _posEnd End position to extract data
			 * @return the extracted string
			 */
			etk::String extract(size_t _posStart = 0, size_t _posEnd=etk::String::npos) const {
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
				return Iterator(this, _pos);
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
			/**
			 * @brief Change the current size of the string
			 * @param[in] _newSize New requested size of element in the string
			 * @param[in] _value Value to set at the new element
			 */
			void resize(size_t _newSize, char _value = '\0') {
				size_t oldSize = m_data.size();
				m_data[m_data.size()-1] = _value;
				m_data.resize(_newSize + 1, _value);
				// in all case ==> we have the last element that is '\0'
				m_data[_newSize] = '\0';
			}
			/*****************************************************
			 *    == operator
			 *****************************************************/
			bool operator== (const String& _obj) const {
				// check if it was the same pointer
				if( this == &_obj ) {
					return true;
				}
				// first step : check the size ...
				if (m_data.size() != _obj.m_data.size()) {
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
				if (m_data.size() != _obj.m_data.size()) {
					return true;
				}
				for (size_t iii=0; iii<m_data.size(); ++iii) {
					if (m_data[iii] != _obj.m_data[iii]) {
						return true;
					}
				}
				return false;
			}
			/**
			 * @brief Template that permit to convert string in everythings you want
			 * @param[in] ETK_STRING_TYPE Template type of the convertion output
			 */
			template <class ETK_STRING_TYPE>
			ETK_STRING_TYPE to();
	};
	String operator+ (const String& _left, const String& _right) {
		String tmp = _left;
		tmp += _right;
		return tmp;
	}
	String operator+ (const String& _left, const char* _right) {
		String tmp = _left;
		tmp += _right;
		return tmp;
	}
	String operator+ (const char* _left, const String& _right) {
		String tmp = _left;
		tmp += _right;
		return tmp;
	}
	String operator+ (const String& _left, char _right) {
		String tmp = _left;
		tmp.pushBack(_right);
		return tmp;
	}
	String operator+ (char _left, const String& _right) {
		String tmp = _left;
		tmp += _right;
		return tmp;
	}
	/**
	 * @brief Template to declare conversion from anything in etk::String
	 * @param[in] _variable Variable to convert
	 * @return String of the value
	 */
	template <class TYPE>
	etk::String toString(const TYPE& _variable);
	/**
	 * @brief Template to declare conversion from std::vector<anything> in etk::String
	 * @param[in] _list Variable to convert
	 * @return String of the value: {...,...,...}
	 */
	template <class TYPE>
	etk::String toString(const std::vector<TYPE>& _list) {
		etk::String out = "{";
		for (size_t iii=0; iii<_list.size(); ++iii) {
			if (iii!=0) {
				out += ";";
			}
			out+= etk::toString(_list[iii]);
		}
		out += "}";
		return out;
	}
	
	
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const etk::String& _obj);
	
	
		/**
	 * @brief Template to declare conversion from string to anything
	 * @param[out] _variableRet Output value
	 * @param[in] _value input property
	 * @return true if the can be converted.
	 */
	template <class TYPE>
	bool from_string(TYPE& _variableRet, const etk::String& _value);
	
	etk::String tolower(etk::String _obj);
	etk::String toupper(etk::String _obj);
	bool compare_no_case(const etk::String& _obj, const etk::String& _val);
	bool end_with(const etk::String& _obj, const etk::String& _val, bool _caseSensitive = true);
	bool start_with(const etk::String& _obj, const etk::String& _val, bool _caseSensitive = true);
	etk::String replace(const etk::String& _obj, char _val, char _replace);
	etk::String replace(const etk::String& _obj, const etk::String& _val, const etk::String& _replace);
	etk::String extract_line(const etk::String& _obj, int32_t _pos);
	etk::Vector<etk::String> split(const etk::String& _input, char _val);
	etk::Vector<etk::String> split(const etk::String& _input, etk::String _val);
	void sort(etk::Vector<etk::String *>& _list);
}
