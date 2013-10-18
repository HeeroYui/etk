/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_USTRING_H__
#define __ETK_USTRING_H__

#include <etk/DebugInternal.h>
#include <etk/Stream.h>
#include <etk/Vector.h>
#include <etk/Char.h>
#include <etk/unicode.h>

namespace etk
{
	class UString
	{
		public:
			typedef enum {
				printModeBinary,
				printModeOctal,
				printModeDecimal,
				printModeHexadecimal,
				printModeString,
			} printMode_te;
		private :
			etk::Vector<etk::UChar> m_data; //!< internal data is stored in the Unicode properties ...
		public:
			// Constructeurs
			UString(void);
			// destructor : 
			~UString(void) { };
			// recopy operator :
			UString(const etk::UString& _obj);
			
			// single element adding
			UString(const bool _inputData, printMode_te _mode=printModeString, bool _preset=false);
			UString(const etk::UChar& _inputData);
			UString(const char* _data, unicode::charset_te _inputCharset);
			UString(const float _inputData);
			UString(const double _inputData);
			UString(const int8_t& _inputData, printMode_te _mode=printModeDecimal, bool _preset=false, int32_t _leadingZero=0) { set((int64_t)_inputData, _mode, _preset, _leadingZero); };
			UString(const int16_t& _inputData, printMode_te _mode=printModeDecimal, bool _preset=false, int32_t _leadingZero=0) { set((int64_t)_inputData, _mode, _preset, _leadingZero); };
			UString(const int32_t& _inputData, printMode_te _mode=printModeDecimal, bool _preset=false, int32_t _leadingZero=0) { set((int64_t)_inputData, _mode, _preset, _leadingZero); };
			UString(const int64_t& _inputData, printMode_te _mode=printModeDecimal, bool _preset=false, int32_t _leadingZero=0) { set(_inputData, _mode, _preset, _leadingZero); };
			UString(const uint8_t& _inputData, printMode_te _mode=printModeDecimal, bool _preset=false, int32_t _leadingZero=0) { set((uint64_t)_inputData, _mode, _preset, _leadingZero); };
			UString(const uint16_t& _inputData, printMode_te _mode=printModeDecimal, bool _preset=false, int32_t _leadingZero=0) { set((uint64_t)_inputData, _mode, _preset, _leadingZero); };
			UString(const uint32_t& _inputData, printMode_te _mode=printModeDecimal, bool _preset=false, int32_t _leadingZero=0) { set((uint64_t)_inputData, _mode, _preset, _leadingZero); };
			UString(const uint64_t& _inputData, printMode_te _mode=printModeDecimal, bool _preset=false, int32_t _leadingZero=0) { set(_inputData, _mode, _preset, _leadingZero); };
			// multiple element add
			UString(const etk::UChar* _inputData, int32_t _len = -1);
			UString(const char* _inputData, int32_t _len = -1);
			UString(const etk::Vector<char>& _inputData);
			UString(const etk::Vector<int8_t>& _inputData);
			UString(const etk::Vector<etk::UChar>& _inputData);
			// generic setter
			void set(const etk::UChar* _inputData, int32_t _len=-1);
			void set(const char*      _inputData, int32_t _len=-1);
			void set(const etk::Vector<char>& _inputData);
			void set(const etk::Vector<int8_t>& _inputData);
			void set(const etk::Vector<etk::UChar>& _inputData);
		private:
			void setNumber(bool _negative, const uint64_t& _inputData, etk::UString::printMode_te _mode, bool _preset, int32_t _leadingZero);
		public:
			void set(const int64_t& _inputData, printMode_te _mode=printModeDecimal, bool _preset=false, int32_t _leadingZero=0);
			void set(const uint64_t& _inputData, printMode_te _mode=printModeDecimal, bool _preset=false, int32_t _leadingZero=0);
			
			/*****************************************************
			 *    = assigment
			 *****************************************************/
			const etk::UString& operator= (const etk::UString& _obj );
			/*****************************************************
			 *    == operator
			 *****************************************************/
			bool operator== (const etk::UString& _obj) const;
			bool compareNoCase(const etk::UString& _obj) const;
			/*****************************************************
			 *    != operator
			 *****************************************************/
			bool operator!= (const etk::UString& _obj) const;
			/*****************************************************
			 *    > < >= <= operator
			 *****************************************************/
			bool operator>  (const etk::UString& _obj) const;
			bool operator>= (const etk::UString& _obj) const;
			bool operator<  (const etk::UString& _obj) const;
			bool operator<= (const etk::UString& _obj) const;
			/*****************************************************
			 *    += operator
			 *****************************************************/
			const etk::UString& operator+= (const etk::UString& _obj);
			//const etk::UString& operator+= (const etk::UChar& _obj);
			/*****************************************************
			 *    + operator
			 *****************************************************/
			etk::UString operator+ (const etk::UString &_obj) const;
			/*****************************************************
			 *    << operator
			 *****************************************************/
			/*
			const etk::UString& operator <<= (const char input);
			const etk::UString& operator <<= (const int input);
			const etk::UString& operator <<= (const unsigned int input);
			*/
			/*****************************************************
			 *    >> operator
			 *****************************************************/
			
			/*****************************************************
			 *    Cout << operator
			 *****************************************************/
			friend etk::CCout& operator <<( etk::CCout& _os,const etk::UString& _obj);
			/*****************************************************
			 *    [] operator
			 *****************************************************/
			const etk::UChar& operator[] (esize_t _pos) const {
				return m_data[_pos];
			}
			etk::UChar& operator[] (esize_t _pos) {
				return m_data[_pos];
			}
			
			/*****************************************************
			 *    toolbox
			 *****************************************************/
			// Start With ...
			bool startWith(const etk::UString& _data, bool _caseSensitive=true) const ;
			// End With ...
			bool endWith(const etk::UString& _data, bool _caseSensitive=true) const ;
			// Find element
			int32_t findForward(const etk::UChar _data, int32_t _startPos=0) const;
			int32_t findBack(const etk::UChar _data, int32_t _startPos=0x7FFFFFFF) const;
			
			bool isEmpty(void) const;
			int32_t size(void) const;
			
			/*****************************************************
			 *    Generic modification function
			 *****************************************************/
			void add(int32_t _currentID, const char* _inputData);
			void add(int32_t _currentID, const etk::UChar* _inputData);
			void add(int32_t _currentID, const etk::UChar  _inputData);
			void remove(int32_t _currentID, int32_t _len);
			void clear(void);
			void append(const etk::UChar& _inputData);
			
			/**
			 * @brief Split a string in multiple separate by a specific char
			 * @param[in] _val Separate value of the string
			 * @return The list of all sthe string splited.
			 */
			etk::Vector<etk::UString> split(const etk::UChar& _val);
			/**
			 * @brief Replace a char with an other
			 * @param[in] _out element to replace.
			 * @param[in] _in Element to set.
			 */
			void replace(const etk::UChar& _out, const etk::UChar& _in);
			
			etk::Vector<etk::UChar> getVector(void);
			etk::UChar* pointer(void) { return &m_data[0]; };
			
			etk::Char c_str(void) const;
			
			void lower(void);
			etk::UString toLower(void) const;
			void upper(void);
			etk::UString toUpper(void) const;
			
			/**
			 * @brief transform tab in \t and '\r' in \r
			 * @return the new string
			 */
			//etk::UString WrapHidenChar(void) const;
			
			// Sting operation :
			etk::UString extract(int32_t _posStart=0, int32_t _posEnd=0x7FFFFFFF) const;
			etk::UString extractLine(int32_t _pos=0) const;
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

	etk::CCout& operator <<(etk::CCout& _os, const etk::UString& _obj);
	etk::CCout& operator <<(etk::CCout& _os, const etk::Vector<etk::UString>& _obj);

}

int32_t strlen(const etk::UChar * _data);



#endif

