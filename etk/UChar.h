/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_UNI_CHAR_H__
#define __ETK_UNI_CHAR_H__

namespace etk {
	//in the unicode section we have : [E000..F8FF]   private area ==> we will store element in this area:
	// internal define to permit to have all needed system
	enum regExpPrivateSection {
		REGEXP_OPCODE_PTHESE_IN=0xE000,	/* ( */
		REGEXP_OPCODE_PTHESE_OUT,/* ) */
		REGEXP_OPCODE_BRACKET_IN,/* [ */
		REGEXP_OPCODE_BRACKET_OUT,/* ] */
		REGEXP_OPCODE_BRACE_IN,/* { */
		REGEXP_OPCODE_BRACE_OUT,/* } */
		REGEXP_OPCODE_TO,/* - */
		REGEXP_OPCODE_STAR,/* * */
		REGEXP_OPCODE_DOT,/* . */
		REGEXP_OPCODE_QUESTION,/* ? */
		REGEXP_OPCODE_PLUS,/* + */
		REGEXP_OPCODE_PIPE,/* | */
		REGEXP_OPCODE_START_OF_LINE,/* ^  this is also NOT, but not manage */
		REGEXP_OPCODE_END_OF_LINE,/* $ */
		REGEXP_OPCODE_DIGIT,/* \d */
		REGEXP_OPCODE_DIGIT_NOT,/* \D */
		REGEXP_OPCODE_LETTER,/* \l */
		REGEXP_OPCODE_LETTER_NOT,/* \L */
		REGEXP_OPCODE_SPACE,/* \s */
		REGEXP_OPCODE_SPACE_NOT,/* \S */
		REGEXP_OPCODE_WORD,/* \w */
		REGEXP_OPCODE_WORD_NOT,/* \W */
		REGEXP_OPCODE_NO_CHAR,/* \@ */
		REGEXP_OPCODE_ERROR, // not used
	};
	
	class UChar {
		public: // classic unicar code :
			static const UChar Null; //!< '\0' 
			static const UChar Return; //!< '\n' 
			static const UChar CarrierReturn; //!< '\r' CR
			static const UChar Tabulation; //!< '\t' TAB
			static const UChar Suppress; //!< BS (SUPPRESS)
			static const UChar Delete; //!< DEL
			static const UChar Space; //!< ' ' SPACE
			static const UChar Escape; //!< ESC Escape
		private:
			uint32_t m_value;
		public:
			// note : No preset at this element to prevent unneded set
			UChar(void) {
				
			};
			UChar(const etk::UChar& _obj) :
			  m_value(_obj.m_value) {
				
			};
			UChar(const char _obj) :
			  m_value((uint32_t)_obj){
				
			};
			UChar(const enum regExpPrivateSection _obj) :
			  m_value((uint32_t)_obj) {
				
			};
			~UChar(void) {}
			
			/*****************************************************
			 *    = assigment
			 *****************************************************/
			const etk::UChar& operator= (const etk::UChar& _obj ) {
				m_value = _obj.m_value;
				return *this;
			};
			/*****************************************************
			 *    == operator
			 *****************************************************/
			bool operator== (const etk::UChar& _obj) const {
				return m_value == _obj.m_value;
			};
			bool compareNoCase(const etk::UChar& _obj) const;
			/*****************************************************
			 *    != operator
			 *****************************************************/
			bool operator!= (const etk::UChar& _obj) const {
				return m_value != _obj.m_value;
			};
			/*****************************************************
			 *    > < >= <= operator
			 *****************************************************/
			bool operator> (const etk::UChar& _obj) const {
				return m_value > _obj.m_value;
			};
			bool operator>= (const etk::UChar& _obj) const {
				return m_value >= _obj.m_value;
			};
			bool operator< (const etk::UChar& _obj) const {
				return m_value < _obj.m_value;
			};
			bool operator<= (const etk::UChar& _obj) const {
				return m_value <= _obj.m_value;
			};
			/*****************************************************
			 *    += operator
			 *****************************************************/
			const etk::UChar& operator+= (const etk::UChar& _obj) {
				m_value += _obj.m_value;
				return *this;
			};
			/*****************************************************
			 *    + operator
			 *****************************************************/
			etk::UChar operator+ (const etk::UChar& _obj) const {
				etk::UChar tmp = *this;
				tmp += _obj;
				return tmp;
			};
			/*****************************************************
			 *    -= operator
			 *****************************************************/
			const etk::UChar& operator-= (const etk::UChar& _obj) {
				if (_obj.m_value >= m_value) {
					m_value = 0;
				} else {
					m_value -= _obj.m_value;
				}
				return *this;
			};
			/*****************************************************
			 *    - operator
			 *****************************************************/
			etk::UChar operator- (const etk::UChar& _obj) const {
				etk::UChar tmp = *this;
				tmp -= _obj;
				return tmp;
			};
			/*****************************************************
			 *    () operator
			 *****************************************************/
			//operator uint32_t() const { return m_value; };
			/**
			 * @brief check if the curent element is white or not : '\t' '\n' '\r' ' '
			 * @return tue if it is white char
			 */
			bool isWhiteChar(void) const;
			bool isSpecialChar(void) const;
			/**
			 * @brief check if the curent element is number or not
			 * @return tue if it is a number char
			 */
			bool isInteger(void) const;
			int32_t toInt32(void) const;
			
			void lower(void);
			UChar toLower(void) const;
			void upper(void);
			UChar toUpper(void) const;
			
			UChar changeOrder(void) const;
			
			uint32_t get(void) const { return m_value; };
			void set(uint32_t _val) { m_value = _val; };
			
			uint32_t getUtf8(void) const;
			int8_t getUtf8(char _output[5]) const;
			//etk::Vector<int8_t> GetUtf8(void) const;
			int8_t setUtf8(const char* _input);
		public:
			/**
			 * @brief Get the size of an utf8 char with his first char.
			 * @param[in] _input Char to parse
			 * @return number of char needed
			 */
			static int8_t theoricUTF8Len(const char _input);
			/**
			 * @brief When parsing a string in a reverse mode, we need to know if we get the first char
			 * @param[in] _input Char to parse.
			 * @return true if it was the first char.
			 */
			static bool theoricUTF8First(const char _input);
	};
};

#endif

