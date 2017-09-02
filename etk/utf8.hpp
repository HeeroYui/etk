/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/String.hpp>
#include <etk/Vector.hpp>
#include <etk/stdTools.hpp>

namespace etk {
	class UString;
}

/**
 * @brief Unicode simple wrapper interface
 */
namespace u32char {
	extern const char32_t Null; //!< Value '\\0' 
	extern const char32_t Return; //!< Value '\\n' 
	extern const char32_t CarrierReturn; //!< Value '\\r' CR
	extern const char32_t Tabulation; //!< Value '\\t' TAB
	extern const char32_t Suppress; //!< Value BS (SUPPRESS)
	extern const char32_t Delete; //!< Value DEL
	extern const char32_t Space; //!< Value ' ' SPACE
	extern const char32_t Escape; //!< Value ESC Escape
	/**
	 * @brief check if the current element is white or not : '\\t' '\\n' '\\r' ' '
	 * @param[in] _val Value to interpret
	 * @return true if it is white char
	 * @return false otherwise
	 */
	bool isWhiteChar(char32_t _val);
	/**
	 * @brief check if the current element is NOT [a-zA-Z0-9]
	 * @param[in] _val Value to interpret
	 * @return true Not in the previous list
	 * @return false otherwise
	 */
	bool isSpecialChar(char32_t _val);
	/**
	 * @brief check if the current element is number or not [0-9]
	 * @param[in] _val Value to interpret
	 * @return true if it is a number char
	 * @return false otherwise
	 */
	bool isInteger(char32_t _val);
	/**
	 * @brief Convert char32_t in an integer
	 * @param[in] _val Value to interpret
	 * @return The parsed Value or ...
	 */
	int32_t toInt(char32_t _val);
	/**
	 * @brief Change order of the value to have an order of display with A->Z and after a->z and after 0->9 and after all the rest ....
	 * @param[in] _val Value in unicode
	 * @return A value usable in integer only ... to check order...
	 */
	char32_t changeOrder(char32_t _val);
	/**
	 * @brief Convert unicode in UTF8 value
	 * @param[in] _val Value to convert
	 * @param[out] _output Char data converted
	 * @return Number of char in utf8
	 */
	int8_t convertUtf8(char32_t _val, char _output[5]);
	#if __CPP_VERSION__ >= 2011
		etk::String convertToUtf8(const etk::UString& _input);
	#endif
	char32_t toUpper(char32_t _input);
	char32_t toLower(char32_t _input);
	size_t strlen(const char32_t* _input);
};

/**
 * @brief UTF-8 simple wrapper interface
 */
namespace utf8 {
	/**
	 * @brief Get the size of an utf8 char with his first char.
	 * @param[in] _input Char to parse
	 * @return number of char needed
	 */
	int8_t length(const char _input);
	/**
	 * @brief When parsing a string in a reverse mode, we need to know if we get the first char
	 * @param[in] _input Char to parse.
	 * @return true if it was the first char.
	 */
	bool first(const char _input);
	/**
	 * @brief Convert a char* in a unicode value
	 * @param[in] _input pointer on a string C (utf-8) to convert
	 * @return Converted Value
	 */
	char32_t convertChar32(const char* _input);
	etk::UString convertUnicode(const char* _input);
	etk::UString convertUnicode(const etk::String& _input);
	/**
	 * @brief Iterator on a simple etk::String that contain utf8 value
	 */
	class Iterator {
		private:
			char32_t m_value; //!< store value to prevent multiple calculation of getting the data
			etk::String* m_data; //!< Pointer on the current Buffer
			int64_t m_current; //!< current Id in the Buffer
		public:
			/**
			 * @brief Basic constructor that is not link on a string
			 */
			Iterator():
			  m_value(u32char::Null),
			  m_data(nullptr),
			  m_current(0) {
				// nothing to do ...
			};
			/**
			 * @brief Basic begin constructor link at the start of the string
			 * @param[in] _str reference on the string to inspect.
			 */
			Iterator(etk::String& _str) :
			  m_value(u32char::Null),
			  m_data(&_str),
			  m_current(0) {
				// nothing to do ...
			};
			/**
			 * @brief Basic position constructor link at the _pos position of the string
			 * @param[in] _str reference on the string to inspect.
			 * @param[in] _pos Iterator position on the string.
			 */
			Iterator(etk::String& _str, const etk::String::Iterator& _pos) :
			  m_value(u32char::Null),
			  m_data(&_str),
			  m_current(0) {
				if (m_data != nullptr) {
					m_current = etk::distance(m_data->begin(), _pos);
				}
			};
			/**
			 * @brief Basic position constructor link at the _pos position of the string
			 * @param[in] _str reference on the string to inspect.
			 * @param[in] _pos Position on the string (in AINSI value).
			 */
			Iterator(etk::String& _str, size_t _pos) :
			  m_value(u32char::Null),
			  m_data(&_str),
			  m_current(0) {
				if (m_data != nullptr) {
					if (_pos > m_data->size()) {
						m_current = m_data->size();
					} else {
						m_current = _pos;
					}
				}
			};
			/**
			 * @brief Basic position constructor link at the _pos position of the string
			 * @param[in] _str Pointer on the string to inspect.
			 * @param[in] _pos Iterator position on the string.
			 */
			Iterator(etk::String* _str, const etk::String::Iterator& _pos) :
			  m_value(u32char::Null),
			  m_data(_str),
			  m_current(0) {
				if (m_data != nullptr) {
					m_current = etk::distance(m_data->begin(), _pos);
				}
			};
			/**
			 * @brief Basic position constructor link at the _pos position of the string
			 * @param[in] _str Pointer on the string to inspect.
			 * @param[in] _pos Position on the string (in AINSI value).
			 */
			Iterator(etk::String* _str, size_t _pos) :
			  m_value(u32char::Null),
			  m_data(_str),
			  m_current(0) {
				if (m_data != nullptr) {
					if (_pos > m_data->size()) {
						m_current = m_data->size();
					} else {
						m_current = _pos;
					}
				}
			};
			/**
			 * @brief Recopy constructor.
			 * @param[in] _obj The Iterator that might be copy
			 */
			Iterator(const Iterator& _obj):
			  m_value(u32char::Null),
			  m_data(_obj.m_data),
			  m_current(_obj.m_current) {
				// nothing to do ...
			};
			/**
			 * @brief Assignation operator.
			 * @param[in] _obj The Iterator that might be copy
			 * @return reference on the current Iterator
			 */
			Iterator& operator=(const Iterator & _obj) {
				m_current = _obj.m_current;
				m_data = _obj.m_data;
				m_value = u32char::Null;
				return *this;
			};
			/**
			 * @brief Basic destructor
			 */
			virtual ~Iterator() {
				m_current = 0;
				m_data = nullptr;
				m_value = u32char::Null;
			};
			/**
			 * @brief basic boolean cast
			 * @return true if the element is present in buffer
			 */
			operator size_t () const {
				if (m_data == nullptr) {
					return 0;
				}
				if (m_current < 0) {
					return 0;
				}
				if (m_current > (int64_t)m_data->size()) {
					return m_data->size();
				}
				return (size_t)m_current;
			};
			/**
			 * @brief Incremental operator
			 * @return Reference on the current Iterator increment
			 */
			Iterator& operator++ ();
			/**
			 * @brief Decremental operator
			 * @return Reference on the current Iterator decrement
			 */
			Iterator& operator-- ();
			/**
			 * @brief Incremental operator
			 * @return Reference on a new Iterator and increment the other one
			 */
			Iterator operator++ (int32_t) {
				Iterator it(*this);
				++(*this);
				return it;
			};
			/**
			 * @brief Decremental operator
			 * @return Reference on a new Iterator and decrement the other one
			 */
			Iterator operator-- (int32_t) {
				Iterator it(*this);
				--(*this);
				return it;
			};
			/**
			 * @brief equality Iterator
			 * @param[in] _obj Iterator to compare
			 * @return true if the Iterator is identical pos
			 */
			bool operator== (const Iterator& _obj) const {
				if (    m_current == _obj.m_current
				     && m_data == _obj.m_data) {
					return true;
				}
				return false;
			};
			/**
			 * @brief equality Iterator
			 * @param[in] _obj Iterator to compare
			 * @return true if the Iterator is identical pos
			 */
			bool operator!= (const Iterator& _obj) const {
				if (    m_current != _obj.m_current
				     || m_data != _obj.m_data) {
					return true;
				}
				return false;
			};
			/**
			 * @brief <= Iterator
			 * @param[in] _obj Iterator to compare
			 * @return true if the Iterator is identical pos
			 */
			bool operator<= (const Iterator& _obj) const {
				if (m_data != _obj.m_data) {
					return false;
				}
				if (m_current <= _obj.m_current) {
					return true;
				}
				return false;
			};
			/**
			 * @brief >= Iterator
			 * @param[in] _obj Iterator to compare
			 * @return true if the Iterator is identical pos
			 */
			bool operator>= (const Iterator& _obj) const {
				if (m_data != _obj.m_data) {
					return false;
				}
				if (m_current >= _obj.m_current) {
					return true;
				}
				return false;
			};
			/**
			 * @brief < Iterator
			 * @param[in] _obj Iterator to compare
			 * @return true if the Iterator is identical pos
			 */
			bool operator< (const Iterator& _obj) const {
				if (m_data != _obj.m_data) {
					return false;
				}
				if (m_current < _obj.m_current) {
					return true;
				}
				return false;
			};
			/**
			 * @brief > Iterator
			 * @param[in] _obj Iterator to compare
			 * @return true if the Iterator is identical pos
			 */
			bool operator> (const Iterator& _obj) const {
				if (m_data != _obj.m_data) {
					return false;
				}
				if (m_current > _obj.m_current) {
					return true;
				}
				return false;
			};
			/**
			 * @brief Get the value on the current element
			 * @return The request element value
			 */
			char32_t operator* ();
			/**
			 * @brief Get the position in the buffer
			 * @return The requested position.
			 */
			size_t getPos() const {
				if (m_data == nullptr) {
					return 0;
				}
				if (m_current < 0) {
					return 0;
				}
				if (m_current >= (int64_t)m_data->size()) {
					return m_data->size()-1;
				}
				return (size_t)m_current;
			};
			/**
			 * @brief move the element position
			 * @param[in] _val Value to add on the Iterator
			 * @return a new Iterator.
			 */
			Iterator operator+ (const int64_t _val) const {
				Iterator tmp(*this);
				for (int64_t iii=0; iii<_val; ++iii) {
					++tmp;
				}
				return tmp;
			};
			/**
			 * @copydoc utf8::Iterator::operator+ (const int64_t)
			 */
			Iterator operator+ (const int32_t _val) const {
				Iterator tmp(*this);
				for (int64_t iii=0; iii<_val; ++iii) {
					++tmp;
				}
				return tmp;
			}
			/**
			 * @copydoc utf8::Iterator::operator+ (const int64_t)
			 */
			Iterator operator+ (const size_t _val) const {
				Iterator tmp(*this);
				for (int64_t iii=0; iii<(int64_t)_val; ++iii) {
					++tmp;
				}
				return tmp;
			}
			/**
			 * @brief move the element position
			 * @param[in] _val Value to remove on the Iterator
			 * @return a new Iterator.
			 */
			Iterator operator- (const int64_t _val) const {
				Iterator tmp(*this);
				for (int64_t iii=0; iii<_val; ++iii) {
					--tmp;
				}
				return tmp;
			}
			/**
			 * @copydoc utf8::Iterator::operator- (const int64_t)
			 */
			Iterator operator- (const int32_t _val) const {
				Iterator tmp(*this);
				for (int64_t iii=0; iii<_val; ++iii) {
					--tmp;
				}
				return tmp;
			}
			/**
			 * @copydoc utf8::Iterator::operator- (const int64_t)
			 */
			Iterator operator- (const size_t _val) const {
				Iterator tmp(*this);
				for (int64_t iii=0; iii<(int64_t)_val; ++iii) {
					--tmp;
				}
				return tmp;
			}
			/*
			Iterator begin() const {
				return Iterator(m_data);
			}
			Iterator end() const {
				return --Iterator(m_data, m_data.end());
			}
			*/
	};
}



/**
 * @brief Calculate the size of a string (unicode)
 * @param[in] _data Data to parse to find the end of string
 * @return The Number of char32_t before the '\\0' value
 */
int32_t strlen(const char32_t* _data);
