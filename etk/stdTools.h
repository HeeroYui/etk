/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_STD_TOOLS_H__
#define __ETK_STD_TOOLS_H__

#include <etk/debug.h>
#include <vector>
#include <sstream>
#include <iostream>
#include <string>

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

namespace std {
	#ifdef __TARGET_OS__MacOs
		typedef std::basic_string<char32_t> u32string;
	#endif
	std::string to_string(const std::u32string& _obj);
	//! @previous
	std::string to_string(bool _val);
	#if (defined(__TARGET_OS__Android) || defined(__TARGET_OS__MacOs))
		//! @previous
		std::string to_string(int _val);
		//! @previous
		std::string to_string(long _val);
		//! @previous
		std::string to_string(long long _val);
		//! @previous
		std::string to_string(unsigned _val);
		//! @previous
		std::string to_string(unsigned long _val);
		//! @previous
		std::string to_string(unsigned long long _val);
		//! @previous
		std::string to_string(float _val);
		//! @previous
		std::string to_string(double _val);
		//! @previous
		std::string to_string(long double _val);
	#endif
	std::u32string to_u32string(const char* _obj);
	//! @previous
	std::u32string to_u32string(const std::string& _obj);
	//! @previous
	std::u32string to_u32string(bool _val);
	//! @previous
	std::u32string to_u32string(int _val);
	//! @previous
	std::u32string to_u32string(long _val);
	//! @previous
	std::u32string to_u32string(long long _val);
	//! @previous
	std::u32string to_u32string(unsigned _val);
	//! @previous
	std::u32string to_u32string(unsigned long _val);
	//! @previous
	std::u32string to_u32string(unsigned long long _val);
	//! @previous
	std::u32string to_u32string(float _val);
	//! @previous
	std::u32string to_u32string(double _val);
	//! @previous
	std::u32string to_u32string(long double _val);
	
	template<class T> std::string to_string(T t, std::ios_base & (*f)(std::ios_base&)) {
		std::ostringstream oss;
		oss << f << t;
		return oss.str();
	}
	template<class T> std::u32string to_u32string(T t, std::ios_base & (*f)(std::ios_base&)) {
		std::ostringstream oss;
		oss << f << t;
		return std::to_u32string(oss.str());
	}
	
	
	#if (defined(__TARGET_OS__Android) || defined(__TARGET_OS__MacOs))
		double stod(const std::string& _str, size_t* _idx = 0);
	#endif
	//! @previous
	double stod(const std::u32string& _str, size_t* _idx = 0);
	
	#if (defined(__TARGET_OS__Android) || defined(__TARGET_OS__MacOs))
		float stof(const std::string& _str, size_t* _idx = 0);
	#endif
	//! @previous
	float stof(const std::u32string& _str, size_t* _idx = 0);
	
	#if (defined(__TARGET_OS__Android) || defined(__TARGET_OS__MacOs))
		int stoi(const std::string& _str, size_t* _idx = 0, int _base = 10);
	#endif
	//! @previous
	int stoi(const std::u32string& _str, size_t* _idx = 0, int _base = 10);
	
	#if (defined(__TARGET_OS__Android) || defined(__TARGET_OS__MacOs))
		long stol(const std::string& _str, size_t* _idx = 0, int _base = 10);
	#endif
	//! @previous
	long stol(const std::u32string& _str, size_t* _idx = 0, int _base = 10);
	
	#if (defined(__TARGET_OS__Android) || defined(__TARGET_OS__MacOs))
		long double stold(const std::string& _str, size_t* _idx = 0);
	#endif
	//! @previous
	long double stold(const std::u32string& _str, size_t* _idx = 0);
	
	#if (defined(__TARGET_OS__Android) || defined(__TARGET_OS__MacOs))
		long long stoll(const std::string& _str, size_t* _idx = 0, int _base = 10);
	#endif
	//! @previous
	long long stoll(const std::u32string& _str, size_t* _idx = 0, int _base = 10);
	
	#if (defined(__TARGET_OS__Android) || defined(__TARGET_OS__MacOs))
		unsigned long stoul(const std::string& _str, size_t* _idx = 0, int _base = 10);
	#endif
	//! @previous
	unsigned long stoul(const std::u32string& _str, size_t* _idx = 0, int _base = 10);
	
	#if (defined(__TARGET_OS__Android) || defined(__TARGET_OS__MacOs))
		unsigned long long stoull(const std::string& _str, size_t* _idx = 0, int _base = 10);
	#endif
	//! @previous
	unsigned long long stoull(const std::u32string& _str, size_t* _idx = 0, int _base = 10);
	
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
namespace etk {
etk::CCout& operator <<(etk::CCout& _os, const std::string& _obj);
etk::CCout& operator <<(etk::CCout& _os, const std::vector<std::string>& _obj);
etk::CCout& operator <<(etk::CCout& _os, const std::u32string& _obj);
etk::CCout& operator <<(etk::CCout& _os, const std::vector<std::u32string>& _obj);
};

int32_t strlen(const char32_t * _data);


#endif

