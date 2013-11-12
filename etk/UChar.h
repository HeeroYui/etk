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
	namespace UChar {
		extern const char32_t Null; //!< '\0' 
		extern const char32_t Return; //!< '\n' 
		extern const char32_t CarrierReturn; //!< '\r' CR
		extern const char32_t Tabulation; //!< '\t' TAB
		extern const char32_t Suppress; //!< BS (SUPPRESS)
		extern const char32_t Delete; //!< DEL
		extern const char32_t Space; //!< ' ' SPACE
		extern const char32_t Escape; //!< ESC Escape
	};
	#if 0
	class UChar : public char32_t{
		public: // classic unicar code :
			static const UChar Null; //!< '\0' 
			static const UChar Return; //!< '\n' 
			static const UChar CarrierReturn; //!< '\r' CR
			static const UChar Tabulation; //!< '\t' TAB
			static const UChar Suppress; //!< BS (SUPPRESS)
			static const UChar Delete; //!< DEL
			static const UChar Space; //!< ' ' SPACE
			static const UChar Escape; //!< ESC Escape
	};
			
			uint32_t get(void) const { return m_value; };
			void set(uint32_t _val) { m_value = _val; };
			
			uint32_t getUtf8(void) const;
			int8_t getUtf8(char _output[5]) const;
			//std::vector<int8_t> GetUtf8(void) const;
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
	#endif
	/**
	 * @brief check if the curent element is white or not : '\t' '\n' '\r' ' '
	 * @return tue if it is white char
	 */
	bool isWhiteChar(char32_t _val);
	bool isSpecialChar(char32_t _val);
	/**
	 * @brief check if the curent element is number or not
	 * @return tue if it is a number char
	 */
	bool isInteger(char32_t _val);
	int32_t toInt32(char32_t _val);
	
	char32_t toLower(char32_t _val);
	char32_t toUpper(char32_t _val);
	bool compareNoCase(char32_t _val1, char32_t _val2);
	char32_t changeOrder(char32_t _val);
	
	int8_t getUtf8(char32_t _val, char _output[5]);
	char32_t setUtf8(const char* _input);
	// TODO : Not needed : tolower(int ...)
	char32_t toLower(char32_t _val);
	char32_t toUpper(char32_t _val);
};

#endif

