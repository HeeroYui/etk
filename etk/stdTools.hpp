/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
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
	 * @param[in] _val Value to interprete
	 * @return true if it is white char
	 * @return false otherwise
	 */
	bool isWhiteChar(char32_t _val);
	/**
	 * @brief check if the current element is NOT [a-zA-Z0-9]
	 * @param[in] _val Value to interprete
	 * @return true Not in the previous list
	 * @return false otherwise
	 */
	bool isSpecialChar(char32_t _val);
	/**
	 * @brief check if the curent element is number or not [0-9]
	 * @param[in] _val Value to interprete
	 * @return true if it is a number char
	 * @return false otherwise
	 */
	bool isInteger(char32_t _val);
	/**
	 * @brief Convert char32_t in an interfer
	 * @param[in] _val Value to interprete
	 * @return The parsed Value or ...
	 */
	int32_t toInt(char32_t _val);
	/**
	 * @brief Change order of the value to have an order of display with A->Z and after a->z and after 0->9 and after all the rest ....
	 * @param[in] _val Value in unicode
	 * @return A value usable in interfer only ... to check order...
	 */
	char32_t changeOrder(char32_t _val);
	/**
	 * @brief Conver unicode in UTF8 value
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
	int8_t theoricLen(const char _input);
	/**
	 * @brief When parsing a string in a reverse mode, we need to know if we get the first char
	 * @param[in] _input Char to parse.
	 * @return true if it was the first char.
	 */
	bool theoricFirst(const char _input);
	/**
	 * @brief Convert a char* in a unicode value
	 * @param[in] _input pointer on a string C (utf-8) to convert
	 * @return Converted Value
	 */
	char32_t convertChar32(const char* _input);
	#if __CPP_VERSION__ >= 2011
		std::u32string convertUnicode(const std::string& _input);
	#endif
	/**
	 * @brief Iterator on a simple std::string that contain utf8 value
	 */
	class iterator {
		private:
			char32_t m_value; //!< store vlue to prevent multiple calcule of getting the data
			std::string* m_data; //!< Pointer on the current Buffer
			int64_t m_current; //!< curent Id in the Buffer
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
			 * @brief Asignation operator.
			 * @param[in] _obj The Iterator that might be copy
			 * @return reference on the curent Iterator
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
			 * @return Reference on the current iterator incremented
			 */
			iterator& operator++ ();
			/**
			 * @brief Decremental operator
			 * @return Reference on the current iterator decremented
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
			 * @brief egality iterator
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
			 * @brief egality iterator
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
				iterator tmpp(*this);
				for (int64_t iii=0; iii<_val; ++iii) {
					++tmpp;
				}
				return tmpp;
			};
			/**
			 * @copydoc utf8::iterator::operator+ (const int64_t)
			 */
			iterator operator+ (const int32_t _val) const {
				iterator tmpp(*this);
				for (int64_t iii=0; iii<_val; ++iii) {
					++tmpp;
				}
				return tmpp;
			};
			/**
			 * @copydoc utf8::iterator::operator+ (const int64_t)
			 */
			iterator operator+ (const size_t _val) const {
				iterator tmpp(*this);
				for (int64_t iii=0; iii<(int64_t)_val; ++iii) {
					++tmpp;
				}
				return tmpp;
			};
			/**
			 * @brief move the element position
			 * @param[in] _val Value to remove on the Iterator
			 * @return a new iterator.
			 */
			iterator operator- (const int64_t _val) const {
				iterator tmpp(*this);
				for (int64_t iii=0; iii<_val; ++iii) {
					--tmpp;
				}
				return tmpp;
			};
			/**
			 * @copydoc utf8::iterator::operator- (const int64_t)
			 */
			iterator operator- (const int32_t _val) const {
				iterator tmpp(*this);
				for (int64_t iii=0; iii<_val; ++iii) {
					--tmpp;
				}
				return tmpp;
			};
			/**
			 * @copydoc utf8::iterator::operator- (const int64_t)
			 */
			iterator operator- (const size_t _val) const {
				iterator tmpp(*this);
				for (int64_t iii=0; iii<(int64_t)_val; ++iii) {
					--tmpp;
				}
				return tmpp;
			};
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

namespace std {
	#if (defined(__TARGET_OS__MacOs) || defined(__TARGET_OS__Windows))
		using u32string = std::basic_string<char32_t>;
	#endif
	#if (defined(__TARGET_OS__Android))
		//! @not_in_doc
		std::string to_string(int _val);
		//! @not_in_doc
		std::string to_string(long _val);
		//! @not_in_doc
		std::string to_string(long long _val);
		//! @not_in_doc
		std::string to_string(unsigned _val);
		//! @not_in_doc
		std::string to_string(unsigned long _val);
		//! @not_in_doc
		std::string to_string(unsigned long long _val);
		//! @not_in_doc
		std::string to_string(float _val);
		//! @not_in_doc
		std::string to_string(double _val);
		//! @not_in_doc
		std::string to_string(long double _val);
		//! @not_in_doc
		double stod(const std::string& _str, size_t* _idx = 0);
		//! @not_in_doc
		float stof(const std::string& _str, size_t* _idx = 0);
		//! @not_in_doc
		int stoi(const std::string& _str, size_t* _idx = 0, int _base = 10);
		//! @not_in_doc
		long stol(const std::string& _str, size_t* _idx = 0, int _base = 10);
		//! @not_in_doc
		long double stold(const std::string& _str, size_t* _idx = 0);
		//! @not_in_doc
		long long stoll(const std::string& _str, size_t* _idx = 0, int _base = 10);
		//! @not_in_doc
		unsigned long stoul(const std::string& _str, size_t* _idx = 0, int _base = 10);
		//! @not_in_doc
		unsigned long long stoull(const std::string& _str, size_t* _idx = 0, int _base = 10);
	#endif
};
namespace etk {
	// these declaration is to prevent some under template declaration of unknown type
	/**
	 * @brief Template to declare convertion from anything in std::string
	 * @param[in] _variable Variable to convert
	 * @return String of the value
	 */
	template <class TYPE>
	std::string to_string(const TYPE& _variable);
	/**
	 * @brief Template to declare convertion from std::vector<anything> in std::string
	 * @param[in] _list Variable to convert
	 * @return String of the value: {...,...,...}
	 */
	template <class TYPE>
	std::string to_string(const std::vector<TYPE>& _list) {
		std::string out = "{";
		for (size_t iii=0; iii<_list.size(); ++iii) {
			if (iii!=0) {
				out += ";";
			}
			out+= etk::to_string(_list[iii]);
		}
		out += "}";
		return out;
	}
	#if __CPP_VERSION__ >= 2011
		template <class TYPE>
		std::u32string to_u32string(const TYPE& _variable);
	#endif
	// these declaration is to prevent some under template declaration of unknown type
	/**
	 * @brief Template to declare convertion from string to anything
	 * @param[out] _variableRet Output value
	 * @param[in] _value input property
	 * @return true if the can be converted.
	 */
	template <class TYPE>
	bool from_string(TYPE& _variableRet, const std::string& _value);
	#if __CPP_VERSION__ >= 2011
		template <class TYPE>
		bool from_string(TYPE& _variableRet, const std::u32string& _value);
	#endif
	
	// TODO : Change this in : 
	// TODO :     template <typename TYPE> TYPE string_to<TYPE>(const std::u32string& _value); ==> check exceptions ...
	//! @not_in_doc
	long double string_to_long_double(const std::string& _str);
	#if __CPP_VERSION__ >= 2011
		long double string_to_long_double(const std::u32string& _str);
	#endif
	//! @not_in_doc
	double string_to_double(const std::string& _str);
	#if __CPP_VERSION__ >= 2011
		double string_to_double(const std::u32string& _str);
	#endif
	//! @not_in_doc
	float string_to_float(const std::string& _str);
	#if __CPP_VERSION__ >= 2011
		float string_to_float(const std::u32string& _str);
	#endif
	//! @not_in_doc
	int8_t string_to_int8_t(const std::string& _str, int _base = 10);
	#if __CPP_VERSION__ >= 2011
		int8_t string_to_int8_t(const std::u32string& _str, int _base = 10);
	#endif
	//! @not_in_doc
	int16_t string_to_int16_t(const std::string& _str, int _base = 10);
	#if __CPP_VERSION__ >= 2011
		int16_t string_to_int16_t(const std::u32string& _str, int _base = 10);
	#endif
	//! @not_in_doc
	int32_t string_to_int32_t(const std::string& _str, int _base = 10);
	#if __CPP_VERSION__ >= 2011
		int32_t string_to_int32_t(const std::u32string& _str, int _base = 10);
	#endif
	//! @not_in_doc
	int64_t string_to_int64_t(const std::string& _str, int _base = 10);
	#if __CPP_VERSION__ >= 2011
		int64_t string_to_int64_t(const std::u32string& _str, int _base = 10);
	#endif
	//! @not_in_doc
	uint8_t string_to_uint8_t(const std::string& _str, int _base = 10);
	#if __CPP_VERSION__ >= 2011
		uint8_t string_to_uint8_t(const std::u32string& _str, int _base = 10);
	#endif
	//! @not_in_doc
	uint16_t string_to_uint16_t(const std::string& _str, int _base = 10);
	#if __CPP_VERSION__ >= 2011
		uint16_t string_to_uint16_t(const std::u32string& _str, int _base = 10);
	#endif
	//! @not_in_doc
	uint32_t string_to_uint32_t(const std::string& _str, int _base = 10);
	#if __CPP_VERSION__ >= 2011
		uint32_t string_to_uint32_t(const std::u32string& _str, int _base = 10);
	#endif
	//! @not_in_doc
	uint64_t string_to_uint64_t(const std::string& _str, int _base = 10);
	#if __CPP_VERSION__ >= 2011
		uint64_t string_to_uint64_t(const std::u32string& _str, int _base = 10);
	#endif
	//! @not_in_doc
	bool string_to_bool(const std::string& _str);
	#if __CPP_VERSION__ >= 2011
		bool string_to_bool(const std::u32string& _str);
	#endif
	//! @not_in_doc
	std::string tolower(std::string _obj);
	#if __CPP_VERSION__ >= 2011
		//! @previous
		std::u32string tolower(std::u32string _obj);
	#endif
	//! @not_in_doc
	std::string toupper(std::string _obj);
	#if __CPP_VERSION__ >= 2011
		//! @previous
		std::u32string toupper(std::u32string _obj);
	#endif
	//! @not_in_doc
	bool compare_no_case(const std::string& _obj, const std::string& _val);
	#if __CPP_VERSION__ >= 2011
		//! @previous
		bool compare_no_case(const std::u32string& _obj, const std::u32string& _val);
	#endif
	//! @not_in_doc
	bool end_with(const std::string& _obj, const std::string& _val, bool _caseSensitive = true);
	#if __CPP_VERSION__ >= 2011
		//! @previous
		bool end_with(const std::u32string& _obj, const std::u32string& _val, bool _caseSensitive = true);
	#endif
	//! @not_in_doc
	bool start_with(const std::string& _obj, const std::string& _val, bool _caseSensitive = true);
	#if __CPP_VERSION__ >= 2011
		//! @previous
		bool start_with(const std::u32string& _obj, const std::u32string& _val, bool _caseSensitive = true);
	#endif
	//! @not_in_doc
	std::string replace(const std::string& _obj, char _val, char _replace);
	#if __CPP_VERSION__ >= 2011
		//! @previous
		std::u32string replace(const std::u32string& _obj, char32_t _val, char32_t _replace);
	#endif
	//! @not_in_doc
	std::string extract_line(const std::string& _obj, int32_t _pos);
	#if __CPP_VERSION__ >= 2011
		//! @previous
		std::u32string extract_line(const std::u32string& _obj, int32_t _pos);
	#endif
	//! @not_in_doc
	std::vector<std::string> split(const std::string& _input, char _val);
	#if __CPP_VERSION__ >= 2011
		//! @previous
		std::vector<std::u32string> split(const std::u32string& _input, char32_t _val);
	#endif
	//! @not_in_doc
	std::vector<std::string> split(const std::string& _input, std::string _val);
	//! @not_in_doc
	void sort(std::vector<std::string *>& _list);
	#if __CPP_VERSION__ >= 2011
		//! @previous
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
	/**
	 * @brief in std, we have min, max but not avg ==> it is missing... the Defineing avg template.
	 * @param[in] _min Minimum value of the range
	 * @param[in] _val The value that we want a min/max
	 * @param[in] _max Maximum value of the range
	 * @return Value that min/max applied
	 */
	template <class TYPE> const TYPE& avg(const TYPE& _min, const TYPE& _val, const TYPE& _max) {
		return std::min(std::max(_min,_val),_max);
	}
};

namespace etk {
	/**
	 * @brief in std, we have min, max but not avg ==> it is missing... the Defineing avg template.
	 * @param[in] _min Minimum value of the range
	 * @param[in] _val The value that we want a min/max
	 * @param[in] _max Maximum value of the range
	 * @return Value that min/max applied
	 */
	template <class TYPE> const TYPE& avg(const TYPE& _min, const TYPE& _val, const TYPE& _max) {
		return std::min(std::max(_min,_val),_max);
	}
};

namespace std {
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const std::string& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const std::vector<std::string>& _obj);
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
 * @brief Claculate the size of a string (unicode)
 * @param[in] _data Data to parse to find the end of string
 * @return the Number of char32_t befor the '\\0' value
 */
int32_t strlen(const char32_t* _data);

#if (defined(__TARGET_OS__Windows))
	#define M_PI 3.14159265358979323846
#endif

