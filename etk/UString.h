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
			etk::Vector<etk::UniChar> m_data; //!< internal data is stored in the Unicode properties ...
		public:
			// Constructeurs
			UString(void);
			// destructor : 
			~UString(void) { };
			// recopy operator :
			UString(const etk::UString& _obj);
			
			// single element adding
			UString(const bool _inputData, printMode_te _mode=printModeString, bool _preset=false);
			UString(const etk::UniChar& _inputData);
			UString(const char* _data, unicode::charset_te _inputCharset);
			UString(const float _inputData);
			UString(const double _inputData);
			UString(const int8_t& _inputData, printMode_te _mode=printModeDecimal, bool _preset=false, int32_t _leadingZero=0)   { Set((int64_t)_inputData, _mode, _preset, _leadingZero); };
			UString(const int16_t& _inputData, printMode_te _mode=printModeDecimal, bool _preset=false, int32_t _leadingZero=0)  { Set((int64_t)_inputData, _mode, _preset, _leadingZero); };
			UString(const int32_t& _inputData, printMode_te _mode=printModeDecimal, bool _preset=false, int32_t _leadingZero=0)  { Set((int64_t)_inputData, _mode, _preset, _leadingZero); };
			UString(const int64_t& _inputData, printMode_te _mode=printModeDecimal, bool _preset=false, int32_t _leadingZero=0)  { Set(_inputData, _mode, _preset, _leadingZero); };
			UString(const uint8_t& _inputData, printMode_te _mode=printModeDecimal, bool _preset=false, int32_t _leadingZero=0)  { Set((uint64_t)_inputData, _mode, _preset, _leadingZero); };
			UString(const uint16_t& _inputData, printMode_te _mode=printModeDecimal, bool _preset=false, int32_t _leadingZero=0) { Set((uint64_t)_inputData, _mode, _preset, _leadingZero); };
			UString(const uint32_t& _inputData, printMode_te _mode=printModeDecimal, bool _preset=false, int32_t _leadingZero=0) { Set((uint64_t)_inputData, _mode, _preset, _leadingZero); };
			UString(const uint64_t& _inputData, printMode_te _mode=printModeDecimal, bool _preset=false, int32_t _leadingZero=0) { Set(_inputData, _mode, _preset, _leadingZero); };
			// multiple element add
			UString(const etk::UniChar* _inputData, int32_t _len = -1);
			UString(const char* _inputData, int32_t _len = -1);
			UString(const etk::Vector<char>& _inputData);
			UString(const etk::Vector<int8_t>& _inputData);
			UString(const etk::Vector<etk::UniChar>& _inputData);
			// generic setter
			void Set(const etk::UniChar* _inputData, int32_t _len=-1);
			void Set(const char*      _inputData, int32_t _len=-1);
			void Set(const etk::Vector<char>& _inputData);
			void Set(const etk::Vector<int8_t>& _inputData);
			void Set(const etk::Vector<etk::UniChar>& _inputData);
		private:
			void SetNumber(bool _negative, const uint64_t& _inputData, etk::UString::printMode_te _mode, bool _preset, int32_t _leadingZero);
		public:
			void Set(const int64_t& _inputData, printMode_te _mode=printModeDecimal, bool _preset=false, int32_t _leadingZero=0);
			void Set(const uint64_t& _inputData, printMode_te _mode=printModeDecimal, bool _preset=false, int32_t _leadingZero=0);
			
			/*****************************************************
			 *    = assigment
			 *****************************************************/
			const etk::UString& operator= (const etk::UString& _obj );
			/*****************************************************
			 *    == operator
			 *****************************************************/
			bool operator== (const etk::UString& _obj) const;
			bool CompareNoCase(const etk::UString& _obj) const;
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
			//const etk::UString& operator+= (const etk::UniChar& _obj);
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
			const etk::UniChar& operator[] (int32_t _pos) const {
				return m_data[_pos];
			}
			etk::UniChar& operator[] (int32_t _pos) {
				return m_data[_pos];
			}
			
			/*****************************************************
			 *    toolbox
			 *****************************************************/
			// Start With ...
			bool StartWith(const etk::UString& _data, bool _caseSensitive=true) const ;
			// End With ...
			bool EndWith(const etk::UString& _data, bool _caseSensitive=true) const ;
			// Find element
			int32_t FindForward(const etk::UniChar _data, int32_t _startPos=0) const;
			int32_t FindBack(const etk::UniChar _data, int32_t _startPos=0x7FFFFFFF) const;
			
			bool IsEmpty(void) const;
			int32_t Size(void) const;
			
			/*****************************************************
			 *    Generic modification function
			 *****************************************************/
			void Add(int32_t _currentID, const char* _inputData);
			void Add(int32_t _currentID, const etk::UniChar* _inputData);
			void Add(int32_t _currentID, const etk::UniChar  _inputData);
			void Remove(int32_t _currentID, int32_t _len);
			void Clear(void);
			void Append(const etk::UniChar& _inputData);
			
			/**
			 * @brief Split a string in multiple separate by a specific char
			 * @param[in] _val Separate value of the string
			 * @return The list of all sthe string splited.
			 */
			etk::Vector<etk::UString> Split(const etk::UniChar& _val);
			
			etk::Vector<etk::UniChar> GetVector(void);
			etk::UniChar* pointer(void) { return &m_data[0]; };
			
			etk::Char c_str(void) const;
			
			void Lower(void);
			etk::UString ToLower(void) const;
			void Upper(void);
			etk::UString ToUpper(void) const;
			
			/**
			 * @brief transform tab in \t and '\r' in \r
			 * @return the new string
			 */
			//etk::UString WrapHidenChar(void) const;
			
			// Sting operation :
			etk::UString Extract(int32_t _posStart=0, int32_t _posEnd=0x7FFFFFFF) const;
			/**
			 * @brief Transform the current string in an int64_t
			 * @return the requested int
			 */
			int64_t ToInt64(void) const;
			/**
			 * @brief Transform the current string in an int32_t (if the number is higher, then it is limited at the int32_t max)
			 * @return the requested int
			 */
			int32_t ToInt32(void) const;
			/**
			 * @brief Transform the current string in an int16_t (if the number is higher, then it is limited at the int16_t max)
			 * @return the requested int
			 */
			int16_t ToInt16(void) const;
			/**
			 * @brief Transform the current string in an int8_t (if the number is higher, then it is limited at the int8_t max)
			 * @return the requested int
			 */
			int8_t ToInt8(void) const;
			/**
			 * @brief Transform the current string in an uint64_t
			 * @return the requested int
			 */
			uint64_t ToUInt64(void) const;
			/**
			 * @brief Transform the current string in an uint32_t (if the number is higher, then it is limited at the uint32_t max)
			 * @return the requested int
			 */
			uint32_t ToUInt32(void) const;
			/**
			 * @brief Transform the current string in an uint16_t (if the number is higher, then it is limited at the uint16_t max)
			 * @return the requested int
			 */
			uint16_t ToUInt16(void) const;
			/**
			 * @brief Transform the current string in an uint8_t (if the number is higher, then it is limited at the uint8_t max)
			 * @return the requested int
			 */
			uint8_t ToUInt8(void) const;
			/**
			 * @brief Transform the current string in a double
			 * @return the requested double
			 */
			double ToDouble(void) const;
			/**
			 * @brief Transform the current string in a float
			 * @return the requested float
			 */
			float ToFloat(void) const;
			/**
			 * @brief Transform the current string in a boolean
			 * @return the requested bool
			 */
			bool ToBool(void) const;
	};

	etk::CCout& operator <<(etk::CCout& _os, const etk::UString& _obj);
	etk::CCout& operator <<(etk::CCout& _os, const etk::Vector<etk::UString>& _obj);

}

int32_t strlen(const etk::UniChar * _data);



#endif

