/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL-2 (see license file)
 */
#pragma once

#include <etk/types.hpp>
//#include <etk/debug.hpp>
#include <etk/Vector.hpp>


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
					Iterator operator++ (int) {
						Iterator it(*this);
						++(*this);
						return it;
					}
					/**
					 * @brief Decremental operator
					 * @return Reference on a new iterator and decrement the other one
					 */
					Iterator operator-- (int) {
						Iterator it(*this);
						--(*this);
						return it;
					}
					
					Iterator& operator-= (size_t _offset) {
						m_current -= _offset;
						return *this;
					}
					Iterator operator- (size_t _offset) const {
						Iterator tmp(*this);
						tmp -= _offset;
						return tmp;
					}
					Iterator& operator-= (int _offset) {
						m_current -= _offset;
						return *this;
					}
					Iterator operator- (int _offset) const {
						Iterator tmp(*this);
						tmp -= _offset;
						return tmp;
					}
					Iterator& operator+= (size_t _offset) {
						m_current += _offset;
						return *this;
					}
					Iterator operator+ (size_t _offset) const {
						Iterator tmp(*this);
						tmp += _offset;
						return tmp;
					}
					Iterator& operator+= (int _offset) {
						m_current += _offset;
						return *this;
					}
					Iterator operator+ (int _offset) const {
						Iterator tmp(*this);
						tmp += _offset;
						return tmp;
					}
					/**
					 * @brief Get reference on the current Element
					 * @return the reference on the current Element 
					 */
					char operator* () const {
						//TK_ASSERT(m_current < m_string->size(), "out of range");
						return m_string->get(m_current);
					}
					/**
					 * @brief Get reference on the current Element
					 * @return the reference on the current Element 
					 */
					char& operator* () {
						//TK_ASSERT(m_current < m_string->size(), "out of range");
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
					Iterator(const String* _obj, int32_t _pos):
					  m_current(_pos),
					  m_string(const_cast<String*>(_obj)) {
						// nothing to do ...
					}
					size_t getCurrent() const {
						return m_current;
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
			String();
			/**
			 * @brief Copy constructor (copy all data)
			 * @param[in] _obj String that might be copy
			 */
			String(const etk::String& _obj);
			/**
			 * @brief Partial copy constructor (copy all needed data)
			 * @param[in] _obj String that might be copy (part of it)
			 * @param[in] _pos Start position to copy data
			 * @param[in] _size Number of element to copy in the string
			 */
			String(const etk::String& _obj, size_t _pos, size_t _size = etk::String::npos);
			/**
			 * @brief Copy the null-terminated C string.
			 * @param[in] _obj C string that might be copy (end by '\0')
			 */
			String(const char* _obj);
			// TODO : remove this when ready
			//////// String(const std::string _obj);
			/**
			 * @brief Partial copy of the null-terminated C string.
			 * @param[in] _obj String that might be copyC string that might be copy (end by '\0')
			 * @param[in] _size Number of element to copy.
			 */
			String(const char* _obj, size_t _size);
			/**
			 * @brief Fills the string with _size consecutive copies of character _val.
			 * @param[in] _size Number of element in the string
			 * @param[in] _val Value to set in the string
			 */
			String(size_t _size, char _val);
			/**
			 * @brief Copy all element betewwen the 2 iterator of the new string.
			 * @param[in] _start Start iterator of adding value.
			 * @param[in] _stop Start iterator of adding value.
			 */
			String(Iterator _start, Iterator _stop);
			/**
			 * @brief Move constructor
			 * @param[in] _obj String that might be move inside
			 */
			String(String&& _obj) noexcept;
			/**
			 * @brief Set constructor
			 * @param[in] _value Char element to set in the string
			 */
			String(char _value);
			/**
			 * @brief Destructor of the current Class
			 */
			~String();
			/**
			 * @brief Swap the data of 2 Strings
			 * @param[in] _obj second string to swap data.
			 */
			void swap(etk::String& _obj);
			/**
			 * @brief Re-copy operator
			 * @param[in] _obj String that might be copy
			 * @return reference on the current re-copy string
			 */
			String& operator=(const etk::String& _obj);
			/**
			 * @brief Re-copy operator
			 * @param[in] _obj C string terminated with '\0'
			 * @return reference on the current re-copy string
			 */
			String& operator=(const char* _obj);
			/**
			 * @brief Re-copy operator
			 * @param[in] _value Char value to set in the string
			 * @return reference on the current re-copy string
			 */
			String& operator=(char _value);
			/**
			 * @brief Add at the Last position of the String
			 * @param[in] _obj Element to add at the end of string
			 */
			String& operator+= (const etk::String& _obj);
			/**
			 * @brief Add at the Last position of the String
			 * @param[in] _obj C string terminated with '\0'
			 */
			String& operator+= (const char* _obj);
			/**
			 * @brief Add at the Last position of the String
			 * @param[in] _value Simple character to add.
			 */
			String& operator+= (char _value);
			/**
			 * @brief Get the number of element in the string
			 * @return The number requested
			 */
			size_t size() const;
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
			const char& operator[] (size_t _pos) const {
				return m_data[_pos];
			}
			/**
			 * @brief Add at the First position of the String
			 * @param[in] _item Element to add at the end of string
			 */
			void pushFront(char _item);
			/**
			 * @brief Add at the Last position of the String
			 * @param[in] _item Pointer on a list of Element to add at the start of string
			 * @param[in] _nbElement Number of element to add.
			 */
			void pushFront(const char * _item, size_t _nbElement);
			/**
			 * @brief Add at the Last position of the String
			 * @param[in] _item Element to add at the end of string
			 */
			void pushBack(const char _item);
			/**
			 * @brief Add at the Last position of the String
			 * @param[in] _item Pointer on a list of Element to add at the end of string
			 * @param[in] _nbElement Number of element to add.
			 */
			void pushBack(const char* _item, size_t _nbElement);
			/**
			 * @brief Remove the last element of the string
			 */
			void popBack();
			/**
			 * @brief Remove all element in the current string
			 */
			void clear();
			/**
			 * @brief Insert N element in the String.
			 * @param[in] _pos Position to add the elements.
			 * @param[in] _item Pointer on a table of the elements to add.
			 * @param[in] _nbElement Number of element to add in the String
			 */
			void insert(size_t _pos, const char* _item, size_t _nbElement);
			//! @previous
			void insert(const Iterator& _pos, const char* _item, size_t _nbElement) {
				insert(_pos.getCurrent(), _item, _nbElement);
			};
			/**
			 * @brief Insert one element in the String at a specific position
			 * @param[in] _pos Position to add the elements.
			 * @param[in] _item Element to add.
			 */
			void insert(size_t _pos, const char _item);
			//! @previous
			void insert(const Iterator& _pos, const char _item) {
				insert(_pos.getCurrent(), _item);
			}
			/**
			 * @brief Insert one element in the String at a specific position
			 * @param[in] _pos Position to add the elements.
			 * @param[in] _item Element to add.
			 */
			void insert(size_t _pos, const String& _value);
			//! @previous
			void insert(const Iterator& _pos, const String& _value) {
				insert(_pos.getCurrent(), _value);
			}
			/**
			 * @brief Remove N element
			 * @param[in] _pos Position to remove the data
			 * @param[in] _nbElement number of element to remove
			 */
			void erase(size_t _pos, size_t _nbElement=1);
			//! @previous
			void erase(const Iterator& _pos) {
				erase(_pos.getCurrent(), 1);
			}
			/**
			 * @brief Remove N elements
			 * @param[in] _start Position to remove the data
			 * @param[in] _stop Last position number
			 */
			void eraseRange(size_t _start, size_t _stop);
			//! @previous
			void erase(const Iterator& _start, const Iterator& _stop) {
				eraseRange(_start.getCurrent(), _stop.getCurrent());
			}
			/**
			 * @brief extract data between two point : 
			 * @param[in] _posStart start position to extract data
			 * @param[in] _posEnd End position to extract data
			 * @return the extracted string
			 */
			etk::String extract(size_t _posStart = 0, size_t _posEnd=etk::String::npos) const;
			//! @previous
			etk::String extract(const Iterator& _start, const Iterator& _stop) const {
				return extract(_start.getCurrent(), _stop.getCurrent());
			}
			/**
			 * @brief Get the pointer on the data
			 * @return pointer on the "C" string
			 */
			const char* c_str() const;
			/**
			 * @brief Get an iterator an an specific position
			 * @param[in] _pos Requested position of the iterator in the string
			 * @return The Iterator
			 */
			Iterator position(size_t _pos);
			//! @previous
			const Iterator position(size_t _pos) const;
			/**
			 * @brief Get an Iterator on the start position of the String
			 * @return The Iterator
			 */
			Iterator begin();
			//! @previous
			const Iterator begin() const;
			/**
			 * @brief Get an Iterator on the end position of the String
			 * @return The Iterator
			 */
			Iterator end();
			//! @previous
			const Iterator end() const;
			/**
			 * @brief Change the current size of the string
			 * @param[in] _newSize New requested size of element in the string
			 * @param[in] _value Value to set at the new element
			 */
			void resize(size_t _newSize, char _value = '\0');
			void append(Iterator _start, Iterator _stop);
			/*****************************************************
			 *    == operator
			 *****************************************************/
			bool operator== (const String& _obj) const;
			/*****************************************************
			 *    != operator
			 *****************************************************/
			bool operator!= (const String& _obj) const;
			size_t find(char _value, size_t _pos=0) const;
			size_t find(const etk::String& _value, size_t _pos=0) const;
			size_t rfind(char _value, size_t _pos=etk::String::npos) const;
			size_t rfind(const etk::String& _value, size_t _pos=etk::String::npos) const;
			etk::String& replace(size_t _pos, size_t _len, char _replace);
			etk::String& replace(size_t _pos, size_t _len, const etk::String& _replace);
			etk::String& replace(char _val, char _replace);
			etk::String& replace(const etk::String& _val, const etk::String& _replace);
			etk::String getLine(int32_t _pos) const;
			etk::String toLower() const;
			etk::String& lower();
			etk::String toUpper() const;
			etk::String& upper();
			bool compare(const etk::String& _val, bool _caseSensitive = true) const;
			bool endWith(const etk::String& _val, bool _caseSensitive = true) const;
			bool startWith(const etk::String& _val, bool _caseSensitive = true) const;
			etk::Vector<etk::String> split(char _val) const;
			etk::Vector<etk::String> split(etk::String _val) const;
			/**
			 * @brief Template that permit to convert string in everythings you want
			 * @param[in] ETK_STRING_TYPE Template type of the convertion output
			 */
			template <class ETK_STRING_TYPE>
			ETK_STRING_TYPE to() const;
	};
	char toLower(char _value);
	char toUpper(char _value);
	bool operator> (const String& _left, const String& _right);
	bool operator>= (const String& _left, const String& _right);
	bool operator< (const String& _left, const String& _right);
	bool operator<= (const String& _left, const String& _right);
	String operator+ (const String& _left, const String& _right);
	String operator+ (const String& _left, const char* _right);
	String operator+ (const char* _left, const String& _right);
	String operator+ (const String& _left, char _right);
	String operator+ (char _left, const String& _right);
	
	inline bool operator== (const char* _left, const String& _right) {
		return _right == _left;
	}
	inline bool operator!= (const char* _left, const String& _right) {
		return _right != _left;
	}
	inline bool operator> (const char* _left, const String& _right) {
		return _right > _left;
	}
	inline bool operator>= (const char* _left, const String& _right) {
		return _right >= _left;
	}
	inline bool operator< (const char* _left, const String& _right) {
		return _right < _left;
	}
	inline bool operator<= (const char* _left, const String& _right) {
		return _right <= _left;
	}
	/**
	 * @brief Template to declare conversion from anything in etk::String
	 * @param[in] _variable Variable to convert
	 * @return String of the value
	 */
	template <class TYPE>
	etk::String toString(const TYPE& _variable);
	//! @not_in_doc
	etk::Stream& operator <<(etk::Stream& _os, const etk::String& _obj);
	/**
	 * @brief Template to declare conversion from string to anything
	 * @param[out] _variableRet Output value
	 * @param[in] _value input property
	 * @return true if the can be converted.
	 */
	template <class TYPE>
	bool from_string(TYPE& _variableRet, const etk::String& _value);
	void sort(etk::Vector<etk::String *>& _list);
	void sort(etk::Vector<etk::String>& _list);
	
	// TODO: DEPRECATED function:
	long double string_to_long_double(const etk::String& _obj);
	double string_to_double(const etk::String& _obj);
	float string_to_float(const etk::String& _obj);
	int8_t string_to_int8_t(const etk::String& _obj);
	int16_t string_to_int16_t(const etk::String& _obj);
	int32_t string_to_int32_t(const etk::String& _obj);
	int64_t string_to_int64_t(const etk::String& _obj);
	uint8_t string_to_uint8_t(const etk::String& _obj);
	uint16_t string_to_uint16_t(const etk::String& _obj);
	uint32_t string_to_uint32_t(const etk::String& _obj);
	uint64_t string_to_uint64_t(const etk::String& _obj);
	bool string_to_bool(const etk::String& _obj);
	etk::String tolower(etk::String _obj);
	etk::String toupper(etk::String _obj);
	bool compare_no_case(const etk::String& _obj, const etk::String& _val);
	bool end_with(const etk::String& _obj, const etk::String& _val, bool _caseSensitive = true);
	bool start_with(const etk::String& _obj, const etk::String& _val, bool _caseSensitive = true);
	etk::String replace(const etk::String& _obj, char _val, char _replace);
	etk::String extract_line(const etk::String& _obj, int32_t _pos);
	etk::Vector<etk::String> split(const etk::String& _obj, char _val);
	
	
	/**
	 * @brief Template to declare conversion from etk::Vector<anything> in etk::String
	 * @param[in] _list Variable to convert
	 * @return String of the value: {...,...,...}
	 */
	template <class TYPE>
	etk::String toString(const etk::Vector<TYPE>& _list) {
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
}
