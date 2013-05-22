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
			UString(const uniChar_t _inputData);
			UString(const float _inputData);
			UString(const double _inputData);
			UString(const int8_t& _inputData, printMode_te _mode=printModeDecimal, bool _preset=false)   { Set((int64_t)_inputData, _mode, _preset); };
			UString(const int16_t& _inputData, printMode_te _mode=printModeDecimal, bool _preset=false)  { Set((int64_t)_inputData, _mode, _preset); };
			UString(const int32_t& _inputData, printMode_te _mode=printModeDecimal, bool _preset=false)  { Set((int64_t)_inputData, _mode, _preset); };
			UString(const int64_t& _inputData, printMode_te _mode=printModeDecimal, bool _preset=false)  { Set(_inputData, _mode, _preset); };
			UString(const uint8_t& _inputData, printMode_te _mode=printModeDecimal, bool _preset=false)  { Set((uint64_t)_inputData, _mode, _preset); };
			UString(const uint16_t& _inputData, printMode_te _mode=printModeDecimal, bool _preset=false) { Set((uint64_t)_inputData, _mode, _preset); };
			UString(const uint32_t& _inputData, printMode_te _mode=printModeDecimal, bool _preset=false) { Set((uint64_t)_inputData, _mode, _preset); };
			UString(const uint64_t& _inputData, printMode_te _mode=printModeDecimal, bool _preset=false) { Set(_inputData, _mode, _preset); };
			// multiple element add
			UString(const uniChar_t* _inputData, int32_t _len = -1);
			UString(const char* _inputData, int32_t _len = -1);
			UString(const etk::Vector<char>& _inputData);
			UString(const etk::Vector<int8_t>& _inputData);
			UString(const etk::Vector<uniChar_t>& _inputData);
			// generic setter
			void Set(const uniChar_t* _inputData, int32_t _len=-1);
			void Set(const char*      _inputData, int32_t _len=-1);
			void Set(const etk::Vector<char>& _inputData);
			void Set(const etk::Vector<int8_t>& _inputData);
			void Set(const etk::Vector<uniChar_t>& _inputData);
		private:
			void SetNumber(bool _negative, const uint64_t& _inputData, etk::UString::printMode_te _mode, bool _preset);
		public:
			void Set(const int64_t& _inputData, printMode_te _mode=printModeDecimal, bool _preset=false);
			void Set(const uint64_t& _inputData, printMode_te _mode=printModeDecimal, bool _preset=false);
			
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
			const etk::UString& operator+= (const etk::UString &_obj);
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
			int32_t FindForward(const uniChar_t _data, int32_t _startPos=0) const;
			int32_t FindBack(const uniChar_t _data, int32_t _startPos=0x7FFFFFFF) const;
			
			bool IsEmpty(void) const;
			int32_t Size(void) const;
			
			/*****************************************************
			 *    Generic modification function
			 *****************************************************/
			void Add(int32_t _currentID, const char* _inputData);
			void Add(int32_t _currentID, const uniChar_t* _inputData);
			void Add(int32_t _currentID, const uniChar_t  _inputData);
			void Remove(int32_t _currentID, int32_t _len);
			void Clear(void);
			
			etk::Vector<etk::UniChar> GetVector(void);
			uniChar_t* pointer(void) { return &m_data[0]; };
			
			etk::Char c_str(void) const;
			
			void Lower(void);
			etk::UString ToLower(void) const;
			void Upper(void);
			etk::UString ToUpper(void) const;
			
			
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

}

int32_t strlen(const uniChar_t * _data);



#endif

