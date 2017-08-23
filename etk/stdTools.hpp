/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/String.hpp>
#include <etk/Vector.hpp>
#include <vector>
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <chrono>

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
		std::string convertToUtf8(const std::u32string& _input);
	#endif
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
	#if __CPP_VERSION__ >= 2011
		std::u32string convertUnicode(const etk::String& _input);
	#endif
	/**
	 * @brief Iterator on a simple std::string that contain utf8 value
	 */
	class iterator {
		private:
			char32_t m_value; //!< store value to prevent multiple calculation of getting the data
			std::string* m_data; //!< Pointer on the current Buffer
			int64_t m_current; //!< current Id in the Buffer
		public:
			/**
			 * @brief Basic constructor that is not link on a string
			 */
			iterator():
			  m_value(u32char::Null),
			  m_data(nullptr),
			  m_current(0) {
				// nothing to do ...
			};
			/**
			 * @brief Basic begin constructor link at the start of the string
			 * @param[in] _str reference on the string to inspect.
			 */
			iterator(std::string& _str) :
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
			iterator(std::string& _str, const std::string::iterator& _pos) :
			  m_value(u32char::Null),
			  m_data(&_str),
			  m_current(0) {
				if (m_data != nullptr) {
					m_current = std::distance(m_data->begin(), _pos);
				}
			};
			/**
			 * @brief Basic position constructor link at the _pos position of the string
			 * @param[in] _str reference on the string to inspect.
			 * @param[in] _pos Position on the string (in AINSI value).
			 */
			iterator(std::string& _str, size_t _pos) :
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
			iterator(std::string* _str, const std::string::iterator& _pos) :
			  m_value(u32char::Null),
			  m_data(_str),
			  m_current(0) {
				if (m_data != nullptr) {
					m_current = std::distance(m_data->begin(), _pos);
				}
			};
			/**
			 * @brief Basic position constructor link at the _pos position of the string
			 * @param[in] _str Pointer on the string to inspect.
			 * @param[in] _pos Position on the string (in AINSI value).
			 */
			iterator(std::string* _str, size_t _pos) :
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
			iterator(const iterator& _obj):
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
			iterator& operator=(const iterator & _obj) {
				m_current = _obj.m_current;
				m_data = _obj.m_data;
				m_value = u32char::Null;
				return *this;
			};
			/**
			 * @brief Basic destructor
			 */
			virtual ~iterator() {
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
			 * @return Reference on the current iterator increment
			 */
			iterator& operator++ ();
			/**
			 * @brief Decremental operator
			 * @return Reference on the current iterator decrement
			 */
			iterator& operator-- ();
			/**
			 * @brief Incremental operator
			 * @return Reference on a new iterator and increment the other one
			 */
			iterator operator++ (int32_t) {
				iterator it(*this);
				++(*this);
				return it;
			};
			/**
			 * @brief Decremental operator
			 * @return Reference on a new iterator and decrement the other one
			 */
			iterator operator-- (int32_t) {
				iterator it(*this);
				--(*this);
				return it;
			};
			/**
			 * @brief equality iterator
			 * @param[in] _obj Iterator to compare
			 * @return true if the iterator is identical pos
			 */
			bool operator== (const iterator& _obj) const {
				if (    m_current == _obj.m_current
				     && m_data == _obj.m_data) {
					return true;
				}
				return false;
			};
			/**
			 * @brief equality iterator
			 * @param[in] _obj Iterator to compare
			 * @return true if the iterator is identical pos
			 */
			bool operator!= (const iterator& _obj) const {
				if (    m_current != _obj.m_current
				     || m_data != _obj.m_data) {
					return true;
				}
				return false;
			};
			/**
			 * @brief <= iterator
			 * @param[in] _obj Iterator to compare
			 * @return true if the iterator is identical pos
			 */
			bool operator<= (const iterator& _obj) const {
				if (m_data != _obj.m_data) {
					return false;
				}
				if (m_current <= _obj.m_current) {
					return true;
				}
				return false;
			};
			/**
			 * @brief >= iterator
			 * @param[in] _obj Iterator to compare
			 * @return true if the iterator is identical pos
			 */
			bool operator>= (const iterator& _obj) const {
				if (m_data != _obj.m_data) {
					return false;
				}
				if (m_current >= _obj.m_current) {
					return true;
				}
				return false;
			};
			/**
			 * @brief < iterator
			 * @param[in] _obj Iterator to compare
			 * @return true if the iterator is identical pos
			 */
			bool operator< (const iterator& _obj) const {
				if (m_data != _obj.m_data) {
					return false;
				}
				if (m_current < _obj.m_current) {
					return true;
				}
				return false;
			};
			/**
			 * @brief > iterator
			 * @param[in] _obj Iterator to compare
			 * @return true if the iterator is identical pos
			 */
			bool operator> (const iterator& _obj) const {
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
			 * @return a new iterator.
			 */
			iterator operator+ (const int64_t _val) const {
				iterator tmp(*this);
				for (int64_t iii=0; iii<_val; ++iii) {
					++tmp;
				}
				return tmp;
			};
			/**
			 * @copydoc utf8::iterator::operator+ (const int64_t)
			 */
			iterator operator+ (const int32_t _val) const {
				iterator tmp(*this);
				for (int64_t iii=0; iii<_val; ++iii) {
					++tmp;
				}
				return tmp;
			}
			/**
			 * @copydoc utf8::iterator::operator+ (const int64_t)
			 */
			iterator operator+ (const size_t _val) const {
				iterator tmp(*this);
				for (int64_t iii=0; iii<(int64_t)_val; ++iii) {
					++tmp;
				}
				return tmp;
			}
			/**
			 * @brief move the element position
			 * @param[in] _val Value to remove on the Iterator
			 * @return a new iterator.
			 */
			iterator operator- (const int64_t _val) const {
				iterator tmp(*this);
				for (int64_t iii=0; iii<_val; ++iii) {
					--tmp;
				}
				return tmp;
			}
			/**
			 * @copydoc utf8::iterator::operator- (const int64_t)
			 */
			iterator operator- (const int32_t _val) const {
				iterator tmp(*this);
				for (int64_t iii=0; iii<_val; ++iii) {
					--tmp;
				}
				return tmp;
			}
			/**
			 * @copydoc utf8::iterator::operator- (const int64_t)
			 */
			iterator operator- (const size_t _val) const {
				iterator tmp(*this);
				for (int64_t iii=0; iii<(int64_t)_val; ++iii) {
					--tmp;
				}
				return tmp;
			}
			/*
			iterator begin() const {
				return iterator(m_data);
			}
			iterator end() const {
				return --iterator(m_data, m_data.end());
			}
			*/
	};
};

namespace etk {
	// these declaration is to prevent some under template declaration of unknown type

	#if __CPP_VERSION__ >= 2011
		template <class TYPE>
		std::u32string to_u32string(const TYPE& _variable);
		template <class TYPE>
		bool from_string(TYPE& _variableRet, const std::u32string& _value);
		long double string_to_long_double(const std::u32string& _str);
		double string_to_double(const std::u32string& _str);
		float string_to_float(const std::u32string& _str);
		int8_t string_to_int8_t(const std::u32string& _str, int _base = 10);
		int16_t string_to_int16_t(const std::u32string& _str, int _base = 10);
		int32_t string_to_int32_t(const std::u32string& _str, int _base = 10);
		int64_t string_to_int64_t(const std::u32string& _str, int _base = 10);
		uint8_t string_to_uint8_t(const std::u32string& _str, int _base = 10);
		uint16_t string_to_uint16_t(const std::u32string& _str, int _base = 10);
		uint32_t string_to_uint32_t(const std::u32string& _str, int _base = 10);
		uint64_t string_to_uint64_t(const std::u32string& _str, int _base = 10);
		bool string_to_bool(const std::u32string& _str);
		std::u32string tolower(std::u32string _obj);
		std::u32string toupper(std::u32string _obj);
		bool compare_no_case(const std::u32string& _obj, const std::u32string& _val);
		bool end_with(const std::u32string& _obj, const std::u32string& _val, bool _caseSensitive = true);
		bool start_with(const std::u32string& _obj, const std::u32string& _val, bool _caseSensitive = true);
		std::u32string replace(const std::u32string& _obj, char32_t _val, char32_t _replace);
		std::u32string extract_line(const std::u32string& _obj, int32_t _pos);
		std::vector<std::u32string> split(const std::u32string& _input, char32_t _val);
		void sort(std::vector<std::u32string *>& _list);
	#endif
	//! @not_in_doc
	template<typename T, typename T2>
	bool isIn(const T& _val, const std::vector<T2>& _list) {
		for (size_t iii=0; iii<_list.size(); ++iii) {
			if (_list[iii] == _val) {
				return true;
			}
		}
		return false;
	}
};



namespace std {
	#if __CPP_VERSION__ >= 2011
		//! @not_in_doc
		std::ostream& operator <<(std::ostream& _os, const std::u32string& _obj);
		//! @not_in_doc
		std::ostream& operator <<(std::ostream& _os, const std::vector<std::u32string>& _obj);
	#endif
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const std::vector<float>& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const std::vector<double>& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const std::vector<int64_t>& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const std::vector<uint64_t>& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const std::vector<int32_t>& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const std::vector<uint32_t>& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const std::vector<int16_t>& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const std::vector<uint16_t>& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const std::vector<int8_t>& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const std::vector<uint8_t>& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const std::chrono::system_clock::time_point& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const std::chrono::steady_clock::time_point& _obj);
}

/**
 * @brief Calculate the size of a string (unicode)
 * @param[in] _data Data to parse to find the end of string
 * @return The Number of char32_t before the '\\0' value
 */
int32_t strlen(const char32_t* _data);

#if (defined(__TARGET_OS__Windows))
	#define M_PI 3.14159265358979323846
#endif


