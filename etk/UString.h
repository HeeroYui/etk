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
	/*
	std::u32string to_string(int _val);
	std::u32string to_string(long _val);
	std::u32string to_string(long long _val);
	std::u32string to_string(unsigned _val);
	std::u32string to_string(unsigned long _val);
	std::u32string to_string(unsigned long long _val);
	std::u32string to_string(float _val);
	std::u32string to_string(double _val);
	std::u32string to_string(long double _val);
	*/
	//typedef std::u32string  UString;
	#if 0
	class UString {
		public:
			enum printMode {
				printModeBinary,
				printModeOctal,
				printModeDecimal,
				printModeHexadecimal,
				printModeString,
			};
		private :
			std::vector<char32_t> m_data; //!< internal data is stored in the Unicode properties ...
		public:
			// Constructeurs
			UString(void);
			// destructor : 
			~UString(void) { };
			// recopy operator :
			UString(const std::string& _obj);
			
			// single element adding
			UString(const bool _inputData, enum printMode _mode=printModeString, bool _preset=false);
			UString(char32_t _inputData);
			UString(const char* _data, enum unicode::charset _inputCharset);
			UString(const float _inputData);
			UString(const double _inputData);
			UString(const int8_t& _inputData, enum printMode _mode=printModeDecimal, bool _preset=false, int32_t _leadingZero=0) {
				set((int64_t)_inputData, _mode, _preset, _leadingZero);
			};
			UString(const int16_t& _inputData, enum printMode _mode=printModeDecimal, bool _preset=false, int32_t _leadingZero=0) {
				set((int64_t)_inputData, _mode, _preset, _leadingZero);
			};
			UString(const int32_t& _inputData, enum printMode _mode=printModeDecimal, bool _preset=false, int32_t _leadingZero=0) {
				set((int64_t)_inputData, _mode, _preset, _leadingZero);
			};
			UString(const int64_t& _inputData, enum printMode _mode=printModeDecimal, bool _preset=false, int32_t _leadingZero=0) {
				set(_inputData, _mode, _preset, _leadingZero);
			};
			UString(const uint8_t& _inputData, enum printMode _mode=printModeDecimal, bool _preset=false, int32_t _leadingZero=0) {
				set((uint64_t)_inputData, _mode, _preset, _leadingZero);
			};
			UString(const uint16_t& _inputData, enum printMode _mode=printModeDecimal, bool _preset=false, int32_t _leadingZero=0) {
				set((uint64_t)_inputData, _mode, _preset, _leadingZero);
			};
			UString(const uint32_t& _inputData, enum printMode _mode=printModeDecimal, bool _preset=false, int32_t _leadingZero=0) {
				set((uint64_t)_inputData, _mode, _preset, _leadingZero);
			};
			UString(const uint64_t& _inputData, enum printMode _mode=printModeDecimal, bool _preset=false, int32_t _leadingZero=0) {
				set(_inputData, _mode, _preset, _leadingZero);
			};
			// multiple element add
			UString(const char32_t* _inputData, int32_t _len = -1);
			UString(const char* _inputData, int32_t _len = -1);
			UString(const std::vector<char>& _inputData);
			UString(const std::vector<int8_t>& _inputData);
			UString(const std::vector<char32_t>& _inputData);
			// generic setter
			void set(const char32_t* _inputData, int32_t _len=-1);
			void set(const char*      _inputData, int32_t _len=-1);
			void set(const std::vector<char>& _inputData);
			void set(const std::vector<int8_t>& _inputData);
			void set(const std::vector<char32_t>& _inputData);
		private:
			void setNumber(bool _negative, const uint64_t& _inputData, enum printMode _mode, bool _preset, int32_t _leadingZero);
		public:
			void set(const int64_t& _inputData, enum printMode _mode=printModeDecimal, bool _preset=false, int32_t _leadingZero=0);
			void set(const uint64_t& _inputData, enum printMode _mode=printModeDecimal, bool _preset=false, int32_t _leadingZero=0);
			
			/*****************************************************
			 *    = assigment
			 *****************************************************/
			const std::string& operator= (const std::string& _obj );
			/*****************************************************
			 *    == operator
			 *****************************************************/
			bool operator== (const std::string& _obj) const;
			bool compareNoCase(const std::string& _obj) const;
			/*****************************************************
			 *    != operator
			 *****************************************************/
			bool operator!= (const std::string& _obj) const;
			/*****************************************************
			 *    > < >= <= operator
			 *****************************************************/
			bool operator>  (const std::string& _obj) const;
			bool operator>= (const std::string& _obj) const;
			bool operator<  (const std::string& _obj) const;
			bool operator<= (const std::string& _obj) const;
			/*****************************************************
			 *    += operator
			 *****************************************************/
			const std::string& operator+= (const std::string& _obj);
			//const std::string& operator+= (char32_t _obj);
			/*****************************************************
			 *    + operator
			 *****************************************************/
			std::string operator+ (const std::string &_obj) const;
			/*****************************************************
			 *    << operator
			 *****************************************************/
			/*
			const std::string& operator <<= (const char input);
			const std::string& operator <<= (const int input);
			const std::string& operator <<= (const unsigned int input);
			*/
			/*****************************************************
			 *    >> operator
			 *****************************************************/
			
			/*****************************************************
			 *    Cout << operator
			 *****************************************************/
			friend etk::CCout& operator <<( etk::CCout& _os,const std::string& _obj);
			/*****************************************************
			 *    [] operator
			 *****************************************************/
			char32_t operator[] (esize_t _pos) const {
				return m_data[_pos];
			}
			char32_t operator[] (esize_t _pos) {
				return m_data[_pos];
			}
			
			/*****************************************************
			 *    toolbox
			 *****************************************************/
			// Start With ...
			bool startWith(const std::string& _data, bool _caseSensitive=true) const ;
			// End With ...
			bool endWith(const std::string& _data, bool _caseSensitive=true) const ;
			// Find element
			int32_t findForward(const char32_t _data, int32_t _startPos=0) const;
			int32_t findBack(const char32_t _data, int32_t _startPos=0x7FFFFFFF) const;
			
			bool isEmpty(void) const;
			int32_t size(void) const;
			
			/*****************************************************
			 *    Generic modification function
			 *****************************************************/
			void add(int32_t _currentID, const char* _inputData);
			void add(int32_t _currentID, const char32_t* _inputData);
			void add(int32_t _currentID, const char32_t  _inputData);
			void remove(int32_t _currentID, int32_t _len = 1);
			void clear(void);
			void append(char32_t _inputData);
			
			/**
			 * @brief Split a string in multiple separate by a specific char
			 * @param[in] _val Separate value of the string
			 * @return The list of all sthe string splited.
			 */
			std::vector<std::string> split(char32_t _val);
			/**
			 * @brief Replace a char with an other
			 * @param[in] _out element to replace.
			 * @param[in] _in Element to set.
			 */
			void replace(char32_t _out, char32_t _in);
			
			std::vector<char32_t> getVector(void);
			char32_t* pointer(void) { return &m_data[0]; };
			
			etk::Char c_str(void) const;
			
			void lower(void);
			std::string toLower(void) const;
			void upper(void);
			std::string toUpper(void) const;
			
			/**
			 * @brief transform tab in \t and '\r' in \r
			 * @return the new string
			 */
			//std::string WrapHidenChar(void) const;
			
			// Sting operation :
			std::string extract(int32_t _posStart=0, int32_t _posEnd=0x7FFFFFFF) const;
			std::string extractLine(int32_t _pos=0) const;
			/**
			 * @brief Transform the current string in an int64_t
			 * @return the requested int
			 */
			int64_t toInt64(void) const;
			/**
			 * @brief Transform the current string in an int32_t (if the number is higher, then it is limited at the int32_t max)
			 * @return the requested int
			 */
			int32_t toInt32(void) const;
			/**
			 * @brief Transform the current string in an int16_t (if the number is higher, then it is limited at the int16_t max)
			 * @return the requested int
			 */
			int16_t toInt16(void) const;
			/**
			 * @brief Transform the current string in an int8_t (if the number is higher, then it is limited at the int8_t max)
			 * @return the requested int
			 */
			int8_t toInt8(void) const;
			/**
			 * @brief Transform the current string in an uint64_t
			 * @return the requested int
			 */
			uint64_t toUInt64(void) const;
			/**
			 * @brief Transform the current string in an uint32_t (if the number is higher, then it is limited at the uint32_t max)
			 * @return the requested int
			 */
			uint32_t toUInt32(void) const;
			/**
			 * @brief Transform the current string in an uint16_t (if the number is higher, then it is limited at the uint16_t max)
			 * @return the requested int
			 */
			uint16_t toUInt16(void) const;
			/**
			 * @brief Transform the current string in an uint8_t (if the number is higher, then it is limited at the uint8_t max)
			 * @return the requested int
			 */
			uint8_t toUInt8(void) const;
			/**
			 * @brief Transform the current string in a double
			 * @return the requested double
			 */
			double toDouble(void) const;
			/**
			 * @brief Transform the current string in a float
			 * @return the requested float
			 */
			float toFloat(void) const;
			/**
			 * @brief Transform the current string in a boolean
			 * @return the requested bool
			 */
			bool toBool(void) const;
	};
	#endif

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

std::u32string to_u32string(int _val);
std::u32string to_u32string(long _val);
std::u32string to_u32string(long long _val);
std::u32string to_u32string(unsigned _val);
std::u32string to_u32string(unsigned long _val);
std::u32string to_u32string(unsigned long long _val);
std::u32string to_u32string(float _val);
std::u32string to_u32string(double _val);
std::u32string to_u32string(long double _val);

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

bool end_with(const std::string& _obj, const std::string& _val, bool _caseSensitive = false);
bool end_with(const std::u32string& _obj, const std::u32string& _val, bool _caseSensitive = false);
bool start_with(const std::string& _obj, const std::string& _val, bool _caseSensitive = false);
bool start_with(const std::u32string& _obj, const std::u32string& _val, bool _caseSensitive = false);

bool compare_no_case(const std::u32string& _obj, const std::u32string& _val);
bool compare_no_case(const std::string& _obj, const std::string& _val);

std::u32string replace(const std::u32string& _obj, char32_t _val, char32_t _replace);
std::string replace(const std::string& _obj, char _val, char _replace);

int32_t strlen(const char32_t * _data);

std::string extract_line(const std::string& _obj, int32_t _pos);
std::u32string extract_line(const std::u32string& _obj, int32_t _pos);

std::vector<std::string> string_split(const std::string& _input, char _val);

#endif

