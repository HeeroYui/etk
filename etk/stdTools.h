/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ETK_STD_TOOLS_H__
#define __ETK_STD_TOOLS_H__

#include <etk/debug.h>
#include <vector>
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>

namespace u32char {
	extern const char32_t Null; //!< '\0' 
	extern const char32_t Return; //!< '\n' 
	extern const char32_t CarrierReturn; //!< '\r' CR
	extern const char32_t Tabulation; //!< '\t' TAB
	extern const char32_t Suppress; //!< BS (SUPPRESS)
	extern const char32_t Delete; //!< DEL
	extern const char32_t Space; //!< ' ' SPACE
	extern const char32_t Escape; //!< ESC Escape
	/**
	 * @brief check if the current element is white or not : '\t' '\n' '\r' ' '
	 * @return tue if it is white char
	 */
	bool isWhiteChar(char32_t _val);
	bool isSpecialChar(char32_t _val);
	/**
	 * @brief check if the curent element is number or not
	 * @return tue if it is a number char
	 */
	bool isInteger(char32_t _val);
	int32_t toInt(char32_t _val);
	
	char32_t changeOrder(char32_t _val);
	int8_t convertUtf8(char32_t _val, char _output[5]);
};

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
	
	char32_t convertChar32(const char* _input);
};

namespace etk {
	#ifdef __TARGET_OS__MacOs
		typedef std::basic_string<char32_t> u32string;
	#endif
	
	
	// these declaration is to prevent some under template declaration of unknown type
	template <class TYPE> std::string to_string(const TYPE& _variable);
	template <class TYPE> std::u32string to_string(const TYPE& _variable);
	
	
	template<class TYPE, int size=0> std::string to_string_format(TYPE t, std::ios_base & (*f)(std::ios_base&)) {
		std::ostringstream oss;
		if (size==0) {
			oss << f << t;
		} else {
			oss << std::setw(size) << std::setfill('0') << f << t;
		}
		return oss.str();
	}
	template<class TYPE, int size=0> std::u32string to_u32string_format(TYPE t, std::ios_base & (*f)(std::ios_base&)) {
		std::ostringstream oss;
		if (size==0) {
			oss << f << t;
		} else {
			oss << std::setw(size) << std::setfill('0') << f << t;
		}
		return std::to_u32string(oss.str());
	}
	
	// these declaration is to prevent some under template declaration of unknown type
	template <class TYPE> bool from_string(TYPE& _variableRet, const std::string& _value);
	template <class TYPE> bool from_string(TYPE& _variableRet, const std::u32string& _value);
	
	double string_to_double(const std::string& _str);
	double string_to_dbouble(const std::u32string& _str);
	
	float string_to_float(const std::string& _str);
	float string_to_float(const std::u32string& _str);
	
	int string_to_int32_t(const std::string& _str, int _base = 10);
	int string_to_i(const std::u32string& _str, int _base = 10);
	
	long string_to_l(const std::string& _str, int _base = 10);
	//! @previous
	long string_to_l(const std::u32string& _str, int _base = 10);
	
	long double string_to_ld(const std::string& _str);
	//! @previous
	long double string_to_ld(const std::u32string& _str);
	
	long long string_to_ll(const std::string& _str, int _base = 10);
	//! @previous
	long long string_to_ll(const std::u32string& _str, int _base = 10);
	
	unsigned long stoul(const std::string& _str, int _base = 10);
	//! @previous
	unsigned long stoul(const std::u32string& _str, int _base = 10);
	
	unsigned long long stoull(const std::string& _str, int _base = 10);
	//! @previous
	unsigned long long stoull(const std::u32string& _str, int _base = 10);
	
	bool stob(const std::string& _str);
	//! @previous
	bool stob(const std::u32string& _str);
	std::string tolower(std::string _obj);
	//! @previous
	std::u32string tolower(std::u32string _obj);
	std::string toupper(std::string _obj);
	//! @previous
	std::u32string toupper(std::u32string _obj);
	
	bool compare_no_case(const std::string& _obj, const std::string& _val);
	//! @previous
	bool compare_no_case(const std::u32string& _obj, const std::u32string& _val);
	
	bool end_with(const std::string& _obj, const std::string& _val, bool _caseSensitive = true);
	//! @previous
	bool end_with(const std::u32string& _obj, const std::u32string& _val, bool _caseSensitive = true);
	
	bool start_with(const std::string& _obj, const std::string& _val, bool _caseSensitive = true);
	//! @previous
	bool start_with(const std::u32string& _obj, const std::u32string& _val, bool _caseSensitive = true);
	
	std::string replace(const std::string& _obj, char _val, char _replace);
	//! @previous
	std::u32string replace(const std::u32string& _obj, char32_t _val, char32_t _replace);
	
	std::string extract_line(const std::string& _obj, int32_t _pos);
	//! @previous
	std::u32string extract_line(const std::u32string& _obj, int32_t _pos);
	
	std::vector<std::string> split(const std::string& _input, char _val);
	//! @previous
	std::vector<std::u32string> split(const std::u32string& _input, char32_t _val);
	
	void sort(std::vector<std::u32string *>& _list);
	//! @previous
	void sort(std::vector<std::string *>& _list);
};

namespace std {
	template <class TYPE> const TYPE& avg(const TYPE& a, const TYPE& b, const TYPE& c) {
		return std::min(std::max(a,b),c);
	}
};

namespace etk {
	std::ostream& operator <<(std::ostream& _os, const std::string& _obj);
	std::ostream& operator <<(std::ostream& _os, const std::vector<std::string>& _obj);
	std::ostream& operator <<(std::ostream& _os, const std::u32string& _obj);
	std::ostream& operator <<(std::ostream& _os, const std::vector<std::u32string>& _obj);
};

int32_t strlen(const char32_t * _data);

#endif

