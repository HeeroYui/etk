/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_USTRING_H__
#define __ETK_USTRING_H__

#include <etk/debug.h>
#include <string>
#include <vector>
#include <sstream>

namespace etk {

	etk::CCout& operator <<(etk::CCout& _os, const std::string& _obj);
	etk::CCout& operator <<(etk::CCout& _os, const std::vector<std::string>& _obj);
	etk::CCout& operator <<(etk::CCout& _os, const std::u32string& _obj);
	etk::CCout& operator <<(etk::CCout& _os, const std::vector<std::u32string>& _obj);
};

std::string to_u8string(const std::u32string& _obj);
std::u32string to_u32string(const std::string& _obj);
std::u32string to_u32string(const char* _obj);


template<class T> std::string to_string(T t, std::ios_base & (*f)(std::ios_base&)) {
	std::ostringstream oss;
	oss << f << t;
	return oss.str();
}

template<class T> std::u32string to_u32string(T t, std::ios_base & (*f)(std::ios_base&)) {
	std::ostringstream oss;
	oss << f << t;
	return to_u32string(oss.str());
}
namespace std {
	std::string to_string(bool _val);
	#ifdef __TARGET_OS__Android
	
	#endif
}
std::u32string to_u32string(bool _val);
std::u32string to_u32string(int _val);
std::u32string to_u32string(long _val);
std::u32string to_u32string(long long _val);
std::u32string to_u32string(unsigned _val);
std::u32string to_u32string(unsigned long _val);
std::u32string to_u32string(unsigned long long _val);
std::u32string to_u32string(float _val);
std::u32string to_u32string(double _val);
std::u32string to_u32string(long double _val);

namespace std {
	#ifdef __TARGET_OS__Android
	double stod(const std::string& _str, size_t* _idx = 0);
	float stof(const std::string& _str, size_t* _idx = 0);
	int stoi(const std::string& _str, size_t* _idx = 0, int _base = 10);
	long stol(const std::string& _str, size_t* _idx = 0, int _base = 10);
	long double stold(const std::string& _str, size_t* _idx = 0);
	long long stoll(const std::string& _str, size_t* _idx = 0, int _base = 10);
	unsigned long stoul(const std::string& _str, size_t* _idx = 0, int _base = 10);
	unsigned long long stoull(const std::string& _str, size_t* _idx = 0, int _base = 10);
	#endif
}
double stod(const std::u32string& _str, size_t* _idx = 0);
float stof(const std::u32string& _str, size_t* _idx = 0);
int stoi(const std::u32string& _str, size_t* _idx = 0, int _base = 10);
long stol(const std::u32string& _str, size_t* _idx = 0, int _base = 10);
long double stold(const std::u32string& _str, size_t* _idx = 0);
long long stoll(const std::u32string& _str, size_t* _idx = 0, int _base = 10);
unsigned long stoul(const std::u32string& _str, size_t* _idx = 0, int _base = 10);
unsigned long long stoull(const std::u32string& _str, size_t* _idx = 0, int _base = 10);
bool stobool(const std::u32string& _str);
bool stobool(const std::string& _str);


std::u32string to_lower(const std::u32string& _obj);
std::u32string to_upper(const std::u32string& _obj);

std::string to_lower(const std::string& _obj);
std::string to_upper(const std::string& _obj);

bool end_with(const std::string& _obj, const std::string& _val, bool _caseSensitive = true);
bool end_with(const std::u32string& _obj, const std::u32string& _val, bool _caseSensitive = true);
bool start_with(const std::string& _obj, const std::string& _val, bool _caseSensitive = true);
bool start_with(const std::u32string& _obj, const std::u32string& _val, bool _caseSensitive = true);

bool compare_no_case(const std::u32string& _obj, const std::u32string& _val);
bool compare_no_case(const std::string& _obj, const std::string& _val);

std::u32string replace(const std::u32string& _obj, char32_t _val, char32_t _replace);
std::string replace(const std::string& _obj, char _val, char _replace);

int32_t strlen(const char32_t * _data);

std::string extract_line(const std::string& _obj, int32_t _pos);
std::u32string extract_line(const std::u32string& _obj, int32_t _pos);

std::vector<std::string> string_split(const std::string& _input, char _val);

#endif

