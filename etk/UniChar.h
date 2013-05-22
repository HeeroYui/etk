/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_UNI_CHAR_H__
#define __ETK_UNI_CHAR_H__

namespace etk
{
	
	//in the unicode section we have : [E000..F8FF]   private area ==> we will store element in this area:
	// internal define to permit to have all needed system
	typedef enum {
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
	} regExpPrivateSection_te;
	
	class UniChar
	{
		private:
			uint32_t m_value;
		public:
			// note : No preset at this element to prevent unneded set
			UniChar(void) { };
			UniChar(const etk::UniChar& _obj) :
				m_value(_obj.m_value)
			{ };
			UniChar(const char _obj) :
				m_value((uint32_t)_obj)
			{ };
			UniChar(const regExpPrivateSection_te _obj) :
				m_value((uint32_t)_obj)
			{ };
			~UniChar(void) {}
			
			/*****************************************************
			 *    = assigment
			 *****************************************************/
			const etk::UniChar& operator= (const etk::UniChar& _obj )
			{
				m_value = _obj.m_value;
				return *this;
			};
			/*****************************************************
			 *    == operator
			 *****************************************************/
			bool operator== (const etk::UniChar& _obj) const
			{
				return m_value == _obj.m_value;
			};
			bool CompareNoCase(const etk::UniChar& _obj) const;
			/*****************************************************
			 *    != operator
			 *****************************************************/
			bool operator!= (const etk::UniChar& _obj) const
			{
				return m_value != _obj.m_value;
			};
			/*****************************************************
			 *    > < >= <= operator
			 *****************************************************/
			bool operator> (const etk::UniChar& _obj) const
			{
				return m_value > _obj.m_value;
			};
			bool operator>= (const etk::UniChar& _obj) const
			{
				return m_value >= _obj.m_value;
			};
			bool operator< (const etk::UniChar& _obj) const
			{
				return m_value < _obj.m_value;
			};
			bool operator<= (const etk::UniChar& _obj) const
			{
				return m_value <= _obj.m_value;
			};
			/*****************************************************
			 *    += operator
			 *****************************************************/
			const etk::UniChar& operator+= (const etk::UniChar& _obj)
			{
				m_value += _obj.m_value;
				return *this;
			};
			/*****************************************************
			 *    + operator
			 *****************************************************/
			etk::UniChar operator+ (const etk::UniChar& _obj) const
			{
				etk::UniChar tmp = *this;
				tmp += _obj;
				return tmp;
			};
			/*****************************************************
			 *    -= operator
			 *****************************************************/
			const etk::UniChar& operator-= (const etk::UniChar& _obj)
			{
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
			etk::UniChar operator- (const etk::UniChar& _obj) const
			{
				etk::UniChar tmp = *this;
				tmp -= _obj;
				return tmp;
			};
			/*****************************************************
			 *    () operator
			 *****************************************************/
			//operator uint32_t() const { return m_value; };
			
			bool IsInteger(void) const;
			int32_t ToInt32(void) const;
			
			void Lower(void);
			UniChar ToLower(void) const;
			void Upper(void);
			UniChar ToUpper(void) const;
			
			UniChar ChangeOrder(void) const;
			
			uint32_t Get(void) const { return m_value; };
			void Set(uint32_t _val) { m_value = _val; };
			
			uint32_t GetUtf8(void) const;
			int8_t GetUtf8(char _output[5]) const;
			void SetUtf8(const char* _input);
	};
};

typedef etk::UniChar uniChar_t;

#endif

