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
		private :
			etk::Vector<uniChar_t> m_data; //!< internal data is stored in the Unicode properties ...
		public:
			// Constructeurs
			UString(void);
			UString(const uniChar_t*  inputData, int32_t len = -1);
			UString(const char*       inputData, int32_t len = -1);
			void Set(const uniChar_t* inputData, int32_t len=-1);
			void Set(const char*      inputData, int32_t len=-1);
			// basic convertion integer en string
			UString(const bool _inputData);
			UString(const char _inputData);
			UString(int inputData, const char* mode="%d");
			UString(unsigned int inputData, const char* mode="%d");
			UString(const float inputData);
			UString(const double inputData);
			UString(const etk::UString &etkS);
			//UString(const uniChar_t inputData);
			// destructor : 
			~UString(void);
			
			/*****************************************************
			 *    = assigment
			 *****************************************************/
			const etk::UString& operator= (const etk::UString& etkS );
			const etk::UString& operator= (etk::Vector<char> inputData);
			const etk::UString& operator= (etk::Vector<int8_t> inputData);
			const etk::UString& operator= (etk::Vector<uniChar_t> inputData);
			/*****************************************************
			 *    == operator
			 *****************************************************/
			bool operator== (const etk::UString& etkS) const;
			bool CompareNoCase(const etk::UString& etkS) const;
			/*****************************************************
			 *    != operator
			 *****************************************************/
			bool operator!= (const etk::UString& etkS) const;
			/*****************************************************
			 *    > < >= <= operator
			 *****************************************************/
			bool operator>  (const etk::UString& etkS) const;
			bool operator>= (const etk::UString& etkS) const;
			bool operator<  (const etk::UString& etkS) const;
			bool operator<= (const etk::UString& etkS) const;
			/*****************************************************
			 *    += operator
			 *****************************************************/
			const etk::UString& operator+= (const etk::UString &etkS);
			/*****************************************************
			 *    + operator
			 *****************************************************/
			etk::UString operator+ (const etk::UString &etkS) const;
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
			friend etk::CCout& operator <<( etk::CCout &os,const etk::UString &obj);
			/*****************************************************
			 *    [] operator
			 *****************************************************/
			const uniChar_t& operator[] (int32_t pos) const {
				return m_data[pos];
			}
			uniChar_t& operator[] (int32_t pos) {
				return m_data[pos];
			}
			
			/*****************************************************
			 *    toolbox
			 *****************************************************/
			// Start With ...
			bool StartWith(const etk::UString& data, bool caseSensitive=true) const ;
			// End With ...
			bool EndWith(const etk::UString& data, bool caseSensitive=true) const ;
			// Find element
			int32_t FindForward(const char data, int32_t startPos=0) const;
			int32_t FindForward(const uniChar_t data, int32_t startPos=0) const;
			int32_t FindBack(const char data, int32_t startPos=0x7FFFFFFF) const;
			int32_t FindBack(const uniChar_t data, int32_t startPos=0x7FFFFFFF) const;
			
			bool IsEmpty(void) const;
			int32_t Size(void) const;
			
			/*****************************************************
			 *    Generic modification function
			 *****************************************************/
			void Add(int32_t currentID, const char* inputData);
			void Add(int32_t currentID, const uniChar_t* inputData);
			void Add(int32_t currentID, const uniChar_t  inputData);
			void Remove(int32_t currentID, int32_t len);
			void Clear(void);
			
			etk::Vector<uniChar_t> GetVector(void);
			uniChar_t* pointer(void) { return &m_data[0]; };
			
			etk::Char c_str(void) const;
			
			// Sting operation :
			etk::UString Extract(int32_t posStart=0, int32_t posEnd=0x7FFFFFFF) const;
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

	etk::CCout& operator <<(etk::CCout &os, const etk::UString &obj);

}

int32_t strlen(const uniChar_t * data);



#endif

