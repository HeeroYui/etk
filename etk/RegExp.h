/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __TK_REG_EXP_H__
#define __TK_REG_EXP_H__

#include <etk/types.h>
#include <etk/DebugInternal.h>
#include <etk/UString.h>
#include <etk/Vector.h>


#define TK_REG_EXP_DBG_MODE TK_VERBOSE
//#define TK_REG_EXP_DBG_MODE TK_DEBUG

namespace etk {

/*
normal mode :
	(...)				sub element is separate with |
	\d					Digits									[0-9]
	\D					NOT a digit								[^0-9]
	\l					Letters									[a-zA-Z]
	\L					NOT a Letter							[^a-zA-Z]
	\s					Whitespace								[ \t\n\r\f\v]
	\S					NOT Whitespace							[^ \t\n\r\f\v]
	\w					"Word" character						[a-zA-Z0-9_]
	\W					NOT a "Word" character					[^a-zA-Z0-9_]
	\@					at the start or the end					not in the parsing of element ==> check if \w is not present   (other regExp will be <> ...)
	[anjdi] or [a-gt-j]	range
	.					dot										[^\x00-\x08\x0A-\x1F\x7F]
==> TODO :
	$					End / Start of line of line 			==> ce sera un truc suplémentaire comme le \@
	^in the []			invertion of the range element

multiplicity :
	*     ==> {0, 2147483647}
	?     ==> {0, 1}
	+     ==> {1, 2147483647}
	{x}   ==> {x, x}
	{x,y} ==> {x, y}
*/

typedef struct {
	bool haveBackSlash;
	char inputValue;
	char newValue;
	etk::regExpPrivateSection_te specialChar;
}convertionTable_ts;

extern const convertionTable_ts constConvertionTable[];
extern const esize_t constConvertionTableSize;

void DisplayElem(const etk::Vector<etk::UniChar>& _data, esize_t _start=0, esize_t _stop=0x7FFFFFFF);
char * levelSpace(uint32_t _level);
esize_t GetLenOfPTheseElem(const etk::Vector<etk::UniChar>& _data, esize_t _startPos);
esize_t GetLenOfPThese(const etk::Vector<etk::UniChar>& _data, esize_t _startPos);
esize_t GetLenOfBracket(const etk::Vector<etk::UniChar>& _data, esize_t _startPos);
esize_t GetLenOfBrace(const etk::Vector<etk::UniChar>& _data, esize_t _startPos);
esize_t GetLenOfNormal(const etk::Vector<etk::UniChar>& _data, esize_t _startPos);
bool ParseBrace(const etk::Vector<etk::UniChar>& _data, uint32_t& _min, uint32_t& _max);


#undef __class__
#define __class__	"etk::RegExpNode"

/**
 *	@brief Node Elements for every-one
 */
template<class CLASS_TYPE> class RegExpNode
{
	protected :
		uint32_t m_multipleMin; //!< minimum repetition (included)
		uint32_t m_multipleMax; //!< maximum repetition (included)
		// Data Section ... (can have no data...)
		etk::Vector<etk::UniChar> m_RegExpData; //!< data to parse and compare in some case ...
	public :
		/**
		 * @brief Constructor
		 */
		RegExpNode(void) :
			m_multipleMin(1),
			m_multipleMax(1)
		{ };
		
		/**
		 * @brief Destructor
		 */
		virtual ~RegExpNode(void) { };
		
		/**
		 * @brief Generate the regular expression with the current "converted string"
		 * @param[in] _data Property of the regexp
		 * @return the number of element used
		 */
		virtual int32_t Generate(const etk::Vector<etk::UniChar>& _data)
		{
			return 0;
		};
		
		/**
		 * @brief Parse the current node
		 * @param[in] _data Data to parse (start pointer / or class that have access with operator[] )
		 * @param[in] _currentPos Current parsing position.
		 * @param[in] _lenMax Maximum position to parse the data (can be not hte end of the data due to the fact sometime we want to parse sub section).
		 * @param[in] _findLen number of element parssed
		 * @return true : Find something
		 * @return false : Find nothing
		 */
		virtual bool Parse(const CLASS_TYPE& _data, esize_t _currentPos, esize_t _lenMax, esize_t& _findLen)=0;
		/**
		 * @brief Display the current node properties
		 * @param[in] level of the node
		 */
		virtual void Display(uint32_t _level)
		{
			TK_INFO("Find NODE : " << levelSpace(_level) << "@???@ {" << GetMultMin() << "," << GetMultMax() << "}  subdata="; DisplayElem(m_RegExpData););
		};
		/**
		 * @brief Set the multiplicity of this Node.
		 * @param[in] _min The minimum appear time.
		 * @param[in] _max The maximum appear time.
		 */
		void SetMult(uint32_t _min, uint32_t _max)
		{
			m_multipleMin = etk_max(_min, 0);
			m_multipleMax = etk_max(_max, 1);
		}
	protected:
		/**
		 * @brief Get the minimum multiplicity.
		 * @return The minimum appear availlable.
		 */
		uint32_t GetMultMin(void) const { return m_multipleMin; };
		/**
		 * @brief Get the maximum multiplicity.
		 * @return The maximum appear availlable.
		 */
		uint32_t GetMultMax(void) const { return m_multipleMax; };
};

#undef __class__
#define __class__	"etk::RegExpNodeValue"

template<class CLASS_TYPE> class RegExpNodeValue : public RegExpNode<CLASS_TYPE>
{
	protected :
		// SubNodes :
		etk::Vector<etk::UniChar> m_data;
	public :
		
		/**
		 * @brief Constructor
		 */
		RegExpNodeValue(void) { };
		
		/**
		 * @brief Destructor
		 */
		~RegExpNodeValue(void) { };
		
		int32_t Generate(const etk::Vector<etk::UniChar>& _data)
		{
			RegExpNode<CLASS_TYPE>::m_RegExpData = _data;
			TK_REG_EXP_DBG_MODE("Request Parse \"Value\" data="; DisplayElem(RegExpNode<CLASS_TYPE>::m_RegExpData););
			m_data.Clear();
			for (int32_t i=0; i<RegExpNode<CLASS_TYPE>::m_RegExpData.Size(); i++) {
				m_data.PushBack(RegExpNode<CLASS_TYPE>::m_RegExpData[i]);
			}
			return _data.Size();
		};
		
		virtual bool Parse(const CLASS_TYPE& _data, esize_t _currentPos, esize_t _lenMax, esize_t& _findLen)
		{
			_findLen = 0;
			TK_REG_EXP_DBG_MODE("Parse node : Value{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			if (0==m_data.Size()) {
				TK_ERROR("No data inside type elemTypeValue");
				return false;
			}
			TK_REG_EXP_DBG_MODE("check element value : '" << m_data[0] << "'");
			bool tmpFind = true;
			uint32_t jjj;
			for (jjj=0; jjj<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind == true; jjj++) {
				uint32_t ofset = 0;
				esize_t kkk;
				for (kkk=0; _findLen+kkk<_lenMax && kkk < m_data.Size(); kkk++) {
					if (m_data[kkk] != _data[_currentPos+_findLen+kkk]) {
						tmpFind=false;
						break;
					}
					ofset++;
				}
				if (kkk != m_data.Size()) {
					// parsing not ended ...
					tmpFind=false;
				}
				// Update local ofset of data
				if (true == tmpFind) {
					_findLen += ofset;
				}
			}
			if(		jjj>=RegExpNode<CLASS_TYPE>::m_multipleMin
				&&	jjj<=RegExpNode<CLASS_TYPE>::m_multipleMax
				&&	_findLen>0	)
			{
				TK_REG_EXP_DBG_MODE("find " << _findLen);
				return true;
			} else if( 0 == RegExpNode<CLASS_TYPE>::m_multipleMin ) {
				TK_REG_EXP_DBG_MODE("find size=0");
				return true;
			}
			return false;
		};
		
		void Display(uint32_t _level)
		{
			TK_INFO("Find NODE : " << levelSpace(_level) << "@Value@ {" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}  subdata="; DisplayElem(RegExpNode<CLASS_TYPE>::m_RegExpData); etk::cout<< " data: "; DisplayElem(m_data); );
		};
};
#undef __class__
#define __class__	"etk::RegExpNodeBracket"

template<class CLASS_TYPE> class RegExpNodeBracket : public RegExpNode<CLASS_TYPE>
{
	protected :
		// SubNodes :
		etk::Vector<etk::UniChar> m_data;
	public :
		
		/**
		 * @brief Constructor
		 */
		RegExpNodeBracket(void) { };
		
		/**
		 * @brief Destructor
		 */
		~RegExpNodeBracket(void) { };
		
		int32_t Generate(const etk::Vector<etk::UniChar>& _data)
		{
			RegExpNode<CLASS_TYPE>::m_RegExpData = _data;
			TK_REG_EXP_DBG_MODE("Request Parse [...] data="; DisplayElem(_data););
			m_data.Clear();
			
			etk::UniChar lastElement = 'a';
			bool multipleElement = false;
			//
			for (int32_t kkk=0; kkk<RegExpNode<CLASS_TYPE>::m_RegExpData.Size(); kkk++) {
				if (RegExpNode<CLASS_TYPE>::m_RegExpData[kkk] == REGEXP_OPCODE_TO && multipleElement == true) {
					TK_ERROR("Can not have 2 consecutive - in [...]");
					return 0;
				} else if (multipleElement == true) {
					etk::UniChar jjj='\0';
					for (jjj=lastElement+1; jjj <= RegExpNode<CLASS_TYPE>::m_RegExpData[kkk]; jjj+=1) {
						m_data.PushBack(jjj);
					}
					multipleElement = false;
				} else if(RegExpNode<CLASS_TYPE>::m_RegExpData[kkk] == REGEXP_OPCODE_TO) {
					multipleElement = true;
				} else {
					lastElement = RegExpNode<CLASS_TYPE>::m_RegExpData[kkk];
					m_data.PushBack(lastElement);
				}
			}
			// check size ...
			if (m_data.Size() == 0) {
				TK_ERROR("No data inside [...] ");
				return 0;
			}
			return _data.Size();
		};
		
		virtual bool Parse(const CLASS_TYPE& _data, esize_t _currentPos, esize_t _lenMax, esize_t& _findLen)
		{
			_findLen = 0;
			TK_REG_EXP_DBG_MODE("Parse node : [...]{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			if (0==m_data.Size()) {
				TK_ERROR("No data inside type elemTypeValue");
				return false;
			}
			TK_REG_EXP_DBG_MODE("one of element value List : "; DisplayElem(m_data););
			bool tmpFind = true;
			uint32_t jjj=0;
			for (jjj=0; jjj<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind ==true && jjj < _lenMax; jjj++) {
				tmpFind=false;
				for (esize_t iii=0; iii<m_data.Size(); iii++) {
					if (m_data[iii] == _data[_currentPos+jjj]) {
						_findLen += 1;
						tmpFind=true;
						break;
					}
				}
			}
			if(		jjj>=RegExpNode<CLASS_TYPE>::m_multipleMin
				&&	jjj<=RegExpNode<CLASS_TYPE>::m_multipleMax
				&&	_findLen>0	)
			{
				TK_REG_EXP_DBG_MODE("find " << _findLen);
				return true;
			} else if( 0 == RegExpNode<CLASS_TYPE>::m_multipleMin ) {
				TK_REG_EXP_DBG_MODE("find size=0");
				return true;
			}
			return false;
		};
		
		void Display(uint32_t _level)
		{
			TK_INFO("Find NODE : " << levelSpace(_level) << "@[...]@ {" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}  subdata="; DisplayElem(RegExpNode<CLASS_TYPE>::m_RegExpData); etk::cout<< " data: "; DisplayElem(m_data); );
		};
};
#undef __class__
#define __class__	"etk::RegExpNodeDigit"

template<class CLASS_TYPE> class RegExpNodeDigit : public RegExpNode<CLASS_TYPE>
{
	public :
		/**
		 * @brief Constructor
		 */
		RegExpNodeDigit(void) { };
		
		/**
		 * @brief Destructor
		 */
		~RegExpNodeDigit(void) { };
		
		virtual bool Parse(const CLASS_TYPE& _data, esize_t _currentPos, esize_t _lenMax, esize_t& _findLen)
		{
			_findLen = 0;
			TK_REG_EXP_DBG_MODE("Parse node : Digit{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "} : "<< _data[_currentPos] << " lenMax=" << _lenMax);
			bool tmpFind = true;
			uint32_t jjj;
			for (jjj=0; jjj<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind ==true && jjj < _lenMax; jjj++) {
				etk::UniChar tmpVal = _data[_currentPos+jjj];
				TK_REG_EXP_DBG_MODE("compare : " << tmpVal);
				if(    tmpVal >= '0'
				    && tmpVal <= '9')
				{
					TK_REG_EXP_DBG_MODE("find ++");
					_findLen += 1;
				} else {
					tmpFind=false;
				}
			}
			if(		jjj>=RegExpNode<CLASS_TYPE>::m_multipleMin
				&&	jjj<=RegExpNode<CLASS_TYPE>::m_multipleMax
				&&	_findLen>0	)
			{
				TK_REG_EXP_DBG_MODE("find " << _findLen);
				return true;
			} else if( 0 == RegExpNode<CLASS_TYPE>::m_multipleMin ) {
				TK_REG_EXP_DBG_MODE("find size=0");
				return true;
			}
			return false;
		};
		
		void Display(uint32_t _level)
		{
			TK_INFO("Find NODE : " << levelSpace(_level) << "@Digit@ {" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}  subdata="; DisplayElem(RegExpNode<CLASS_TYPE>::m_RegExpData););
		};
};
#undef __class__
#define __class__ "etk::RegExpNodeDigitNot"

template<class CLASS_TYPE> class RegExpNodeDigitNot : public RegExpNode<CLASS_TYPE>
{
	public :
		/**
		 * @brief Constructor
		 */
		RegExpNodeDigitNot(void) { };
		
		/**
		 * @brief Destructor
		 */
		~RegExpNodeDigitNot(void) { };
		
		virtual bool Parse(const CLASS_TYPE& _data, esize_t _currentPos, esize_t _lenMax, esize_t& _findLen)
		{
			_findLen = 0;
			TK_REG_EXP_DBG_MODE("Parse node : DigitNot{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			bool tmpFind = true;
			uint32_t jjj;
			for (jjj=0; jjj<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind ==true && jjj < _lenMax; jjj++) {
				etk::UniChar tmpVal = _data[_currentPos+jjj];
				if(    tmpVal < '0'
				    || tmpVal > '9') {
					_findLen += 1;
				} else {
					tmpFind=false;
				}
			}
			if(    jjj>=RegExpNode<CLASS_TYPE>::m_multipleMin
			    && jjj<=RegExpNode<CLASS_TYPE>::m_multipleMax
			    && _findLen>0 ) {
				TK_REG_EXP_DBG_MODE("find " << _findLen);
				return true;
			} else if( 0 == RegExpNode<CLASS_TYPE>::m_multipleMin ) {
				TK_REG_EXP_DBG_MODE("find size=0");
				return true;
			}
			return false;
		};
		
		void Display(uint32_t _level)
		{
			TK_INFO("Find NODE : " << levelSpace(_level) << "@DigitNot@ {" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}  subdata="; DisplayElem(RegExpNode<CLASS_TYPE>::m_RegExpData););
		};
};
#undef __class__
#define __class__	"etk::RegExpNodeLetter"

template<class CLASS_TYPE> class RegExpNodeLetter : public RegExpNode<CLASS_TYPE>
{
	public :
		
		/**
		 * @brief Constructor
		 */
		RegExpNodeLetter(void) { };
		
		/**
		 * @brief Destructor
		 */
		~RegExpNodeLetter(void) { };
		
		virtual bool Parse(const CLASS_TYPE& _data, esize_t _currentPos, esize_t _lenMax, esize_t& _findLen)
		{
			_findLen = 0;
			TK_REG_EXP_DBG_MODE("Parse node : Letter{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			bool tmpFind = true;
			uint32_t jjj;
			for (jjj=0; jjj<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind ==true && jjj < _lenMax; jjj++) {
				etk::UniChar tmpVal = _data[_currentPos+jjj];
				if(    (    tmpVal >= 'a'
				         && tmpVal <= 'z')
				    || (    tmpVal >= 'A'
				         && tmpVal <= 'Z') ) {
					_findLen += 1;
				} else {
					tmpFind=false;
				}
			}
			if(    jjj>=RegExpNode<CLASS_TYPE>::m_multipleMin
			    && jjj<=RegExpNode<CLASS_TYPE>::m_multipleMax
			    && _findLen>0 ) {
				TK_REG_EXP_DBG_MODE("find " << _findLen);
				return true;
			} else if( 0 == RegExpNode<CLASS_TYPE>::m_multipleMin ) {
				TK_REG_EXP_DBG_MODE("find size=0");
				return true;
			}
			return false;
		};
		
		void Display(uint32_t _level)
		{
			TK_INFO("Find NODE : " << levelSpace(_level) << "@Letter@ {" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}  subdata="; DisplayElem(RegExpNode<CLASS_TYPE>::m_RegExpData););
		};
};
#undef __class__
#define __class__	"etk::RegExpNodeLetterNot"

template<class CLASS_TYPE> class RegExpNodeLetterNot : public RegExpNode<CLASS_TYPE>
{
	public :
		
		/**
		 * @brief Constructor
		 */
		RegExpNodeLetterNot(void) { };
		
		/**
		 * @brief Destructor
		 */
		~RegExpNodeLetterNot(void) { };
		
		virtual bool Parse(const CLASS_TYPE& _data, esize_t _currentPos, esize_t _lenMax, esize_t& _findLen)
		{
			_findLen = 0;
			TK_REG_EXP_DBG_MODE("Parse node : LetterNot{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			bool tmpFind = true;
			uint32_t jjj;
			for (jjj=0; jjj<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind ==true && jjj < _lenMax; jjj++) {
				etk::UniChar tmpVal = _data[_currentPos+jjj];
				if(    (    tmpVal < 'a'
				         && tmpVal > 'Z')
				    || tmpVal < 'A'
				    || tmpVal > 'z') {
					_findLen += 1;
				} else {
					tmpFind=false;
				}
			}
			if(    jjj>=RegExpNode<CLASS_TYPE>::m_multipleMin
			    && jjj<=RegExpNode<CLASS_TYPE>::m_multipleMax
			    && _findLen>0 ) {
				TK_REG_EXP_DBG_MODE("find " << _findLen);
				return true;
			} else if( 0 == RegExpNode<CLASS_TYPE>::m_multipleMin ) {
				TK_REG_EXP_DBG_MODE("find size=0");
				return true;
			}
			return false;
		};
		
		void Display(uint32_t _level)
		{
			TK_INFO("Find NODE : " << levelSpace(_level) << "@LetterNot@ {" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}  subdata="; DisplayElem(RegExpNode<CLASS_TYPE>::m_RegExpData););
		};
};
#undef __class__
#define __class__	"etk::RegExpNodeWhiteSpace"

template<class CLASS_TYPE> class RegExpNodeWhiteSpace : public RegExpNode<CLASS_TYPE>
{
	public :
		
		/**
		 * @brief Constructor
		 */
		RegExpNodeWhiteSpace(void) { };
		
		/**
		 * @brief Destructor
		 */
		~RegExpNodeWhiteSpace(void) { };
		
		virtual bool Parse(const CLASS_TYPE& _data, esize_t _currentPos, esize_t _lenMax, esize_t& _findLen)
		{
			_findLen = 0;
			TK_REG_EXP_DBG_MODE("Parse node : Space{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			bool tmpFind = true;
			uint32_t jjj;
			for (jjj=0; jjj<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind ==true && jjj < _lenMax; jjj++) {
				etk::UniChar tmpVal = _data[_currentPos+jjj];
				if(    tmpVal == ' '
				    || tmpVal == '\t'
				    || tmpVal == '\n'
				    || tmpVal == '\r'
				    || tmpVal == '\f'
				    || tmpVal == '\v' ) {
					_findLen += 1;
				} else {
					tmpFind=false;
				}
			}
			if(    jjj>=RegExpNode<CLASS_TYPE>::m_multipleMin
			    && jjj<=RegExpNode<CLASS_TYPE>::m_multipleMax
			    && _findLen>0 ) {
				TK_REG_EXP_DBG_MODE("find " << _findLen);
				return true;
			} else if( 0 == RegExpNode<CLASS_TYPE>::m_multipleMin ) {
				TK_REG_EXP_DBG_MODE("find size=0");
				return true;
			}
			return false;
		};
		
		void Display(uint32_t _level)
		{
			TK_INFO("Find NODE : " << levelSpace(_level) << "@Space@ {" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}  subdata="; DisplayElem(RegExpNode<CLASS_TYPE>::m_RegExpData););
		};
};
#undef __class__
#define __class__	"etk::RegExpNodeWhiteSpaceNot"

template<class CLASS_TYPE> class RegExpNodeWhiteSpaceNot : public RegExpNode<CLASS_TYPE>
{
	public :
		
		/**
		 * @brief Constructor
		 */
		RegExpNodeWhiteSpaceNot(void) { };
		
		/**
		 * @brief Destructor
		 */
		~RegExpNodeWhiteSpaceNot(void) { };
		
		virtual bool Parse(const CLASS_TYPE& _data, esize_t _currentPos, esize_t _lenMax, esize_t& _findLen)
		{
			_findLen = 0;
			TK_REG_EXP_DBG_MODE("Parse node : SpaceNot{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			bool tmpFind = true;
			uint32_t jjj;
			for (jjj=0; jjj<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind ==true && jjj < _lenMax; jjj++) {
				etk::UniChar tmpVal = _data[_currentPos+jjj];
				if(    tmpVal != ' '
				    && tmpVal != '\t'
				    && tmpVal != '\n'
				    && tmpVal != '\r'
				    && tmpVal != '\f'
				    && tmpVal != '\v' ) {
					_findLen += 1;
				} else {
					tmpFind=false;
				}
			}
			if(    jjj>=RegExpNode<CLASS_TYPE>::m_multipleMin
			    && jjj<=RegExpNode<CLASS_TYPE>::m_multipleMax
			    && _findLen>0 ) {
				TK_REG_EXP_DBG_MODE("find " << _findLen);
				return true;
			} else if( 0 == RegExpNode<CLASS_TYPE>::m_multipleMin ) {
				TK_REG_EXP_DBG_MODE("find size=0");
				return true;
			}
			return false;
		};
		
		void Display(uint32_t _level)
		{
			TK_INFO("Find NODE : " << levelSpace(_level) << "@SpaceNot@ {" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}  subdata="; DisplayElem(RegExpNode<CLASS_TYPE>::m_RegExpData););
		};
};
#undef __class__
#define __class__	"etk::RegExpNodeWordChar"

template<class CLASS_TYPE> class RegExpNodeWordChar : public RegExpNode<CLASS_TYPE>
{
	public :
		/**
		 * @brief Constructor
		 */
		RegExpNodeWordChar(void) { };
		
		/**
		 * @brief Destructor
		 */
		~RegExpNodeWordChar(void) { };
		
		virtual bool Parse(const CLASS_TYPE& _data, esize_t _currentPos, esize_t _lenMax, esize_t& _findLen)
		{
			_findLen = 0;
			TK_REG_EXP_DBG_MODE("Parse node : Word{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			bool tmpFind = true;
			uint32_t jjj;
			for (jjj=0; jjj<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind ==true && jjj < _lenMax; jjj++) {
				etk::UniChar tmpVal = _data[_currentPos+jjj];
				if(    (    tmpVal >= 'a'
				         && tmpVal <= 'z' )
				    || (    tmpVal >= 'A'
				         && tmpVal <= 'Z' )
				    || (    tmpVal >= '0'
				         && tmpVal <= '9' ) ) {
					_findLen += 1;
				} else {
					tmpFind=false;
				}
			}
			if(    jjj>=RegExpNode<CLASS_TYPE>::m_multipleMin
			    && jjj<=RegExpNode<CLASS_TYPE>::m_multipleMax
			    && _findLen>0 ) {
				TK_REG_EXP_DBG_MODE("find " << _findLen);
				return true;
			} else if( 0 == RegExpNode<CLASS_TYPE>::m_multipleMin ) {
				TK_REG_EXP_DBG_MODE("find size=0");
				return true;
			}
			return false;
		};
		
		void Display(uint32_t _level)
		{
			TK_INFO("Find NODE : " << levelSpace(_level) << "@Word@ {" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}  subdata="; DisplayElem(RegExpNode<CLASS_TYPE>::m_RegExpData););
		};
};
#undef __class__
#define __class__	"etk::RegExpNodeWordCharNot"

template<class CLASS_TYPE> class RegExpNodeWordCharNot : public RegExpNode<CLASS_TYPE>
{
	public :
		/**
		 * @brief Constructor
		 */
		RegExpNodeWordCharNot(void) { };
		
		/**
		 * @brief Destructor
		 */
		~RegExpNodeWordCharNot(void) { };
		
		virtual bool Parse(const CLASS_TYPE& _data, esize_t _currentPos, esize_t _lenMax, esize_t& _findLen)
		{
			_findLen = 0;
			TK_REG_EXP_DBG_MODE("Parse node : WordNot{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			bool tmpFind = true;
			uint32_t jjj;
			for (jjj=0; jjj<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind ==true && jjj < _lenMax; jjj++) {
				etk::UniChar tmpVal = _data[_currentPos+jjj];
				if(    (    tmpVal < 'A'
				         && tmpVal > '9' )
				    || (    tmpVal < 'a'
				         && tmpVal > 'Z' )
				    || tmpVal < '0'
				    || tmpVal > 'z') {
					_findLen += 1;
				} else {
					tmpFind=false;
				}
			}
			if(    jjj>=RegExpNode<CLASS_TYPE>::m_multipleMin
			    && jjj<=RegExpNode<CLASS_TYPE>::m_multipleMax
			    && _findLen>0 ) {
				TK_REG_EXP_DBG_MODE("find " << _findLen);
				return true;
			} else if( 0 == RegExpNode<CLASS_TYPE>::m_multipleMin ) {
				TK_REG_EXP_DBG_MODE("find size=0");
				return true;
			}
			return false;
		};
		
		void Display(uint32_t _level)
		{
			TK_INFO("Find NODE : " << levelSpace(_level) << "@WordNot@ {" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}  subdata="; DisplayElem(RegExpNode<CLASS_TYPE>::m_RegExpData););
		};
};
#undef __class__
#define __class__	"etk::RegExpNodeDot"

template<class CLASS_TYPE> class RegExpNodeDot : public RegExpNode<CLASS_TYPE>
{
	public :
		
		/**
		 * @brief Constructor
		 */
		RegExpNodeDot(void) { };
		
		/**
		 * @brief Destructor
		 */
		~RegExpNodeDot(void) { };
		
		virtual bool Parse(const CLASS_TYPE& _data, esize_t _currentPos, esize_t _lenMax, esize_t& _findLen)
		{
			_findLen = 0;
			TK_REG_EXP_DBG_MODE("Parse node : '.'{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			// equivalent a : [^\x00-\x08\x0A-\x1F\x7F]
			bool tmpFind = true;
			uint32_t jjj;
			for (jjj=0; jjj<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind ==true && jjj < _lenMax; jjj++) {
				etk::UniChar tmpVal = _data[_currentPos+jjj];
				if(    (    tmpVal > 0x08
				         && tmpVal < 0x0A )
				    || (    tmpVal > 0x1F
				         && tmpVal < 0x7F )
				    || (    tmpVal > 0x7F
				         && tmpVal < 0xFF ) ) {
					_findLen += 1;
				} else {
					tmpFind=false;
				}
			}
			if(    jjj>=RegExpNode<CLASS_TYPE>::m_multipleMin
			    && jjj<=RegExpNode<CLASS_TYPE>::m_multipleMax
			    && _findLen>0 ) {
				TK_REG_EXP_DBG_MODE("find " << _findLen);
				return true;
			} else if( 0 == RegExpNode<CLASS_TYPE>::m_multipleMin ) {
				TK_REG_EXP_DBG_MODE("find size=0");
				return true;
			}
			return false;
		};
		
		void Display(uint32_t _level)
		{
			TK_INFO("Find NODE : " << levelSpace(_level) << "@.@ {" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}  subdata="; DisplayElem(RegExpNode<CLASS_TYPE>::m_RegExpData););
		};
};

#undef __class__
#define __class__	"etk::RegExpNodeSOL"

template<class CLASS_TYPE> class RegExpNodeSOL : public RegExpNode<CLASS_TYPE>
{
	public :
		
		/**
		 * @brief Constructor
		 */
		RegExpNodeSOL(void) { };
		
		/**
		 * @brief Destructor
		 */
		~RegExpNodeSOL(void) { };
		
		virtual bool Parse(const CLASS_TYPE& _data, esize_t _currentPos, esize_t _lenMax, esize_t& _findLen)
		{
			_findLen = 0;
			// TODO : ...
			TK_INFO("Parse node : SOL{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			return false;
		};
		
		void Display(uint32_t _level)
		{
			TK_INFO("Find NODE : " << levelSpace(_level) << "@SOL@ {" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}  subdata="; DisplayElem(RegExpNode<CLASS_TYPE>::m_RegExpData););
		};
};

#undef __class__
#define __class__	"etk::RegExpNodeEOL"

template<class CLASS_TYPE> class RegExpNodeEOL : public RegExpNode<CLASS_TYPE>
{
	public :
		/**
		 * @brief Constructor
		 */
		RegExpNodeEOL(void) { };
		
		/**
		 * @brief Destructor
		 */
		~RegExpNodeEOL(void) { };
		
		virtual bool Parse(const CLASS_TYPE& _data, esize_t _currentPos, esize_t _lenMax, esize_t& _findLen)
		{
			_findLen = 0;
			// TODO : ...
			TK_INFO("Parse node : EOL{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			return false;
		};
		
		void Display(uint32_t _level)
		{
			TK_INFO("Find NODE : " << levelSpace(_level) << "@EOL@ {" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}  subdata="; DisplayElem(RegExpNode<CLASS_TYPE>::m_RegExpData););
		};
};

typedef struct {
	int32_t start;
	int32_t stop;
}elementPos_ts;

#undef __class__
#define __class__	"etk::RegExpNodePTheseElem"

template<class CLASS_TYPE> class RegExpNodePThese;

template<class CLASS_TYPE> class RegExpNodePTheseElem : public RegExpNode<CLASS_TYPE>
{
	protected :
		// SubNodes :
		etk::Vector<RegExpNode<CLASS_TYPE>*> m_subNode;
	public :
		/**
		 * @brief Constructor
		 */
		RegExpNodePTheseElem(void) { };
		
		/**
		 * @brief Destructor
		 */
		~RegExpNodePTheseElem(void) { };
		
		int32_t Generate(const etk::Vector<etk::UniChar>& _data)
		{
			RegExpNode<CLASS_TYPE>::m_RegExpData = _data;
			TK_REG_EXP_DBG_MODE("Request Parse (elem) data="; DisplayElem(RegExpNode<CLASS_TYPE>::m_RegExpData););
			esize_t pos = 0;
			esize_t elementSize = 0;
			etk::Vector<etk::UniChar> tmpData;
			while (pos < RegExpNode<CLASS_TYPE>::m_RegExpData.Size()) {
				tmpData.Clear();
				switch (RegExpNode<CLASS_TYPE>::m_RegExpData[pos].Get()) {
					case REGEXP_OPCODE_PTHESE_IN:
						{
							elementSize=GetLenOfPThese(RegExpNode<CLASS_TYPE>::m_RegExpData, pos);
							for (esize_t kkk=pos+1; kkk<pos+elementSize+1; kkk++) {
								tmpData.PushBack(RegExpNode<CLASS_TYPE>::m_RegExpData[kkk]);
							}
							RegExpNodePThese<CLASS_TYPE> * myElem = new RegExpNodePThese<CLASS_TYPE>();
							(void)myElem->Generate(tmpData);
							// add to the subnode list : 
							m_subNode.PushBack(myElem);
							// move current position ...
							pos += elementSize+1;
						}
						break;
					case REGEXP_OPCODE_PTHESE_OUT:
						TK_ERROR("Impossible case :  ')' " << pos);
						return false;
					case REGEXP_OPCODE_BRACKET_IN:
						{
							elementSize=GetLenOfBracket(RegExpNode<CLASS_TYPE>::m_RegExpData, pos);
							for (esize_t kkk=pos+1; kkk<pos+elementSize+1; kkk++) {
								tmpData.PushBack(RegExpNode<CLASS_TYPE>::m_RegExpData[kkk]);
							}
							RegExpNodeBracket<CLASS_TYPE> * myElem = new RegExpNodeBracket<CLASS_TYPE>();
							(void)myElem->Generate(tmpData);
							// add to the subnode list : 
							m_subNode.PushBack(myElem);
							// move current position ...
							pos += elementSize+1;
						}
						break;
					case REGEXP_OPCODE_BRACKET_OUT:
						TK_ERROR("Impossible case :  ']' " << pos);
						return false;
					case REGEXP_OPCODE_BRACE_IN:
						{
							elementSize=GetLenOfBrace(RegExpNode<CLASS_TYPE>::m_RegExpData, pos);
							for (esize_t kkk=pos+1; kkk<pos+elementSize+1; kkk++) {
								tmpData.PushBack(RegExpNode<CLASS_TYPE>::m_RegExpData[kkk]);
							}
							uint32_t min = 0;
							uint32_t max = 0;
							if (false == ParseBrace(tmpData, min, max)) {
								return false;
							}
							SetMultiplicityOnLastNode(min, max);
							pos += elementSize+1;
						}
						break;
					case REGEXP_OPCODE_BRACE_OUT:
						TK_ERROR("Impossible case :  '}' " << pos);
						return false;
					case REGEXP_OPCODE_TO:
						TK_ERROR("Impossible case :  '-' " << pos);
						return false;
					case REGEXP_OPCODE_STAR:
						SetMultiplicityOnLastNode(0, 0x7FFFFFFF);
						break;
					case REGEXP_OPCODE_QUESTION:
						SetMultiplicityOnLastNode(0, 1);
						break;
					case REGEXP_OPCODE_PLUS:
						SetMultiplicityOnLastNode(1, 0x7FFFFFFF);
						break;
					case REGEXP_OPCODE_PIPE:
						TK_ERROR("Impossible case :  '|' " << pos);
						return false;
					case REGEXP_OPCODE_DOT:
						m_subNode.PushBack(new RegExpNodeDot<CLASS_TYPE>());
						break;
					case REGEXP_OPCODE_START_OF_LINE:
						m_subNode.PushBack(new RegExpNodeSOL<CLASS_TYPE>());
						break;
					case REGEXP_OPCODE_END_OF_LINE:
						m_subNode.PushBack(new RegExpNodeEOL<CLASS_TYPE>());
						break;
					case REGEXP_OPCODE_DIGIT:
						m_subNode.PushBack(new RegExpNodeDigit<CLASS_TYPE>());
						break;
					case REGEXP_OPCODE_DIGIT_NOT:
						m_subNode.PushBack(new RegExpNodeDigitNot<CLASS_TYPE>());
						break;
					case REGEXP_OPCODE_LETTER:
						m_subNode.PushBack(new RegExpNodeLetter<CLASS_TYPE>());
						break;
					case REGEXP_OPCODE_LETTER_NOT:
						m_subNode.PushBack(new RegExpNodeLetterNot<CLASS_TYPE>());
						break;
					case REGEXP_OPCODE_SPACE:
						m_subNode.PushBack(new RegExpNodeWhiteSpace<CLASS_TYPE>());
						break;
					case REGEXP_OPCODE_SPACE_NOT:
						m_subNode.PushBack(new RegExpNodeWhiteSpaceNot<CLASS_TYPE>());
						break;
					case REGEXP_OPCODE_WORD:
						m_subNode.PushBack(new RegExpNodeWordChar<CLASS_TYPE>());
						break;
					case REGEXP_OPCODE_WORD_NOT:
						m_subNode.PushBack(new RegExpNodeWordCharNot<CLASS_TYPE>());
						break;
					
					default:
						{
							elementSize=GetLenOfNormal(RegExpNode<CLASS_TYPE>::m_RegExpData, pos);
							for (esize_t kkk=pos; kkk<pos+elementSize; kkk++) {
								tmpData.PushBack(RegExpNode<CLASS_TYPE>::m_RegExpData[kkk]);
							}
							RegExpNodeValue<CLASS_TYPE> * myElem = new RegExpNodeValue<CLASS_TYPE>();
							(void)myElem->Generate(tmpData);
							// add to the subnode list : 
							m_subNode.PushBack(myElem);
							// move current position ...
							pos += elementSize-1;
						}
						break;
				}
				pos++;
			}
			return _data.Size();
		};
		
		virtual bool Parse(const CLASS_TYPE& _data, esize_t _currentPos, esize_t _lenMax, esize_t& _findLen)
		{
			_findLen = 0;
			TK_REG_EXP_DBG_MODE("Parse node : (Elem){" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			// NOTE 1 : Must done only one time in EVERY case ...
			// NOTE 2 : All element inside must be OK
			if (0 == m_subNode.Size()) {
				return false;
			}
			esize_t tmpCurrentPos = _currentPos;
			for (esize_t iii=0; iii<m_subNode.Size(); iii++) {
				esize_t tmpFindLen;
				if (false == m_subNode[iii]->Parse(_data, tmpCurrentPos, _lenMax, tmpFindLen)) {
					_findLen = 0;
					return false;
				} else {
					tmpCurrentPos += tmpFindLen;
				}
			}
			if (tmpCurrentPos<_currentPos) {
				_findLen = 0;
			} else {
				_findLen = tmpCurrentPos - _currentPos;
			}
			return true;
		};
		
		void Display(uint32_t _level)
		{
			TK_INFO("Find NODE : " << levelSpace(_level) << "@(Elem)@ {" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}  subdata="; DisplayElem(RegExpNode<CLASS_TYPE>::m_RegExpData););
			for(esize_t iii=0; iii<m_subNode.Size(); iii++) {
				m_subNode[iii]->Display(_level+1);
			}
		};
	private :
		/**
		 * @brief Set the number of repeate time on a the last node in the list ...
		 * @param[in] _min Minimum of the multiplicity
		 * @param[in] _max Maximum of the multiplicity
		 * @return true if we find the node, false otherwise
		 */
		bool SetMultiplicityOnLastNode(uint32_t _min, uint32_t _max)
		{
			if (0==m_subNode.Size()) {
				TK_ERROR("Set multiplicity on an inexistant element ....");
				return false;
			}
			RegExpNode<CLASS_TYPE> * myNode = m_subNode[m_subNode.Size()-1];
			if (NULL==myNode) {
				TK_ERROR("INTERNAL error ==> node not generated");
				return false;
			}
			myNode->SetMult(_min, _max);
			return true;
		}
};

#undef __class__
#define __class__	"etk::RegExpNodePThese"

template<class CLASS_TYPE> class RegExpNodePThese : public RegExpNode<CLASS_TYPE>
{
	protected :
		etk::Vector<RegExpNode<CLASS_TYPE>*> m_subNode; //!< Subnode list 
	public :
		/**
		 * @brief Constructor
		 */
		RegExpNodePThese(void)
		{
			
		};
		
		/**
		 * @brief Destructor
		 */
		~RegExpNodePThese(void)
		{
			
		};
		
		int32_t Generate(const etk::Vector<etk::UniChar>& _data)
		{
			RegExpNode<CLASS_TYPE>::m_RegExpData = _data;
			TK_REG_EXP_DBG_MODE("Request Parse (...) data="; DisplayElem(RegExpNode<CLASS_TYPE>::m_RegExpData););
			//Find all the '|' in the string (and at the good level ...) 
			int32_t pos = 0;
			int32_t elementSize = GetLenOfPTheseElem(RegExpNode<CLASS_TYPE>::m_RegExpData, pos);
			// generate all the "elemTypePTheseElem" of the Node
			while (elementSize>0) {
				// geerate output deta ...
				etk::Vector<etk::UniChar> tmpData;
				for (esize_t kkk=pos; kkk<pos+elementSize; kkk++) {
					tmpData.PushBack(RegExpNode<CLASS_TYPE>::m_RegExpData[kkk]);
				}
				RegExpNodePTheseElem<CLASS_TYPE> * myElem = new RegExpNodePTheseElem<CLASS_TYPE>();
				(void)myElem->Generate(tmpData);
				// add to the subnode list : 
				m_subNode.PushBack(myElem);
				pos += elementSize+1;
				TK_REG_EXP_DBG_MODE("plop="; DisplayElem(_data, pos, pos+1););
				elementSize = GetLenOfPTheseElem(RegExpNode<CLASS_TYPE>::m_RegExpData, pos);
				TK_REG_EXP_DBG_MODE("find " << elementSize << " elements");
			}
			if (0 == pos && 0 == elementSize) {
				TK_ERROR("No data in the (...) element at " << pos);
				return false;
			}
			return _data.Size();
		};
		
		virtual bool Parse(const CLASS_TYPE& _data, esize_t _currentPos, esize_t _lenMax, esize_t& _findLen)
		{
			_findLen = 0;
			TK_REG_EXP_DBG_MODE("Parse node : (...){" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			if (0 == m_subNode.Size()) {
				return false;
			}
			bool tmpFind = true;
			uint32_t jjj;
			for (jjj=0; jjj<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind == true ; jjj++) {
				tmpFind = false;
				for (esize_t iii=0; iii<m_subNode.Size(); iii++) {
					esize_t tmpFindLen;
					if (true == m_subNode[iii]->Parse(_data, _currentPos+_findLen, _lenMax, tmpFindLen)) {
						_findLen += tmpFindLen;
						tmpFind = true;
					}
				}
			}
			if(		jjj>=RegExpNode<CLASS_TYPE>::m_multipleMin
				&&	jjj<=RegExpNode<CLASS_TYPE>::m_multipleMax
				&&	_findLen>0	)
			{
				TK_REG_EXP_DBG_MODE("find " << _findLen);
				return true;
			} else if( 0 == RegExpNode<CLASS_TYPE>::m_multipleMin ) {
				TK_REG_EXP_DBG_MODE("find size=0");
				return true;
			}
			return false;
		};
		
		void Display(uint32_t _level)
		{
			if (-1 == _level) {
				TK_INFO("regExp :"; DisplayElem(RegExpNode<CLASS_TYPE>::m_RegExpData););
			} else {
				TK_INFO("Find NODE : " << levelSpace(_level) << "@(...)@ {" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}  subdata="; DisplayElem(RegExpNode<CLASS_TYPE>::m_RegExpData););
				for(int32_t i=0; i<m_subNode.Size(); i++) {
					m_subNode[i]->Display(_level+1);
				}
			}
		};
};
#undef __class__
#define __class__	"etk::RegExp"

// Regular expression manager
template<class CLASS_TYPE> class RegExp
{
	private:
		etk::UString m_expressionRequested; //!< Regular expression parsed ...
		elementPos_ts m_areaFind; //!< position around selection
		RegExpNodePThese<CLASS_TYPE> m_exprRootNode; //!< The tree where data is set
		bool m_isOk; //!< Known if we can process with this regExp
		bool m_notBeginWithChar; //!< The regular expression must not have previously a char [a-zA-Z0-9_]
		bool m_notEndWithChar; //!< The regular expression must not have after the end a char [a-zA-Z0-9_]
	public:
		// create the regular expression
		
		/**
		 * @brief Constructor
		 * @param[in,out] _exp Regular expression to parse
		 */
		RegExp(const etk::UString &_exp="") :
			m_expressionRequested(""),
			m_isOk(false),
			m_notBeginWithChar(false),
			m_notEndWithChar(false)
		{
			m_areaFind.start=0;
			m_areaFind.stop=0;
			if (_exp.Size() != 0) {
				SetRegExp(_exp);
			}
		};
		
		/**
		 * @brief Destructor
		 */
		~RegExp(void)
		{
			m_isOk = false;
		};
		
		/**
		 * @brief Set a new regular expression matching
		 * @param[in] _regexp the new expression to search
		 */
		void SetRegExp(const etk::UString &_regexp)
		{
			m_expressionRequested = _regexp;
			etk::Vector<etk::UniChar> tmpExp;
			
			TK_REG_EXP_DBG_MODE("---------------------------------------------------------------------");
			TK_REG_EXP_DBG_MODE("Parse RegExp : (" << _regexp << ")" );
			m_isOk = false;
			m_areaFind.start=0;
			m_areaFind.stop=0;
			m_notBeginWithChar = false;
			m_notEndWithChar = false;
			
			// change in the regular Opcode ==> replace \x with the corect element ... x if needed
			int32_t countBraceIn = 0;
			int32_t countBraceOut = 0;
			int32_t countPTheseIn = 0;
			int32_t countPTheseOut = 0;
			int32_t countBracketIn = 0;
			int32_t countBracketOut = 0;
			for (esize_t iii=0; iii<_regexp.Size(); iii++) {
				if (_regexp[iii] == '\\') {
					if(iii+1>=_regexp.Size()) {
						TK_ERROR("Dangerous parse of the element pos " << iii << " \\ with nothing after");
						// TODO : Generate Exeption ...
						return;
					}
					esize_t jjj;
					// Find the element in the list...
					for (jjj=0; jjj<constConvertionTableSize; jjj++) {
						if(		true == constConvertionTable[jjj].haveBackSlash 
							&&	_regexp[iii+1] == constConvertionTable[jjj].inputValue)
						{
							if (constConvertionTable[jjj].newValue==0) {
								tmpExp.PushBack(constConvertionTable[jjj].specialChar);
							} else {
								tmpExp.PushBack(constConvertionTable[jjj].newValue);
							}
							break;
						}
					}
					// check error : 
					if (jjj==constConvertionTableSize) {
						TK_ERROR("Dangerous parse of the \\ " << _regexp[iii+1] << " at element " << iii);
						// TODO : Generate Exeption ...
						return;
					}
					// less one char in the regular expression ...
					iii++;
				} else {
					if (_regexp[iii] == '(') {
						countPTheseIn++;
					} else if (_regexp[iii] == ')') {
						countPTheseOut++;
					} else if (_regexp[iii] == '[') {
						countBracketIn++;
					} else if (_regexp[iii] == ']') {
						countBracketOut++;
					} else if (_regexp[iii] == '{') {
						countBraceIn++;
					} else if (_regexp[iii] == '}') {
						countBraceOut++;
					}
					esize_t jjj;
					// find the element in the list...
					for (jjj=0; jjj<constConvertionTableSize; jjj++) {
						if(		false == constConvertionTable[jjj].haveBackSlash 
							&&	_regexp[iii] == constConvertionTable[jjj].inputValue)
						{
							if (constConvertionTable[jjj].newValue==0) {
								tmpExp.PushBack(constConvertionTable[jjj].specialChar);
							} else {
								tmpExp.PushBack(constConvertionTable[jjj].newValue);
							}
							break;
						}
					}
					// not find : normal element
					if (jjj==constConvertionTableSize) {
						//TK_REG_EXP_DBG_MODE("parse : '" << _regexp[iii] << "'" );
						tmpExp.PushBack(_regexp[iii]);
					}
				}
			}
			
			// count the number of '(' and ')'
			if (countPTheseIn != countPTheseOut ) {
				TK_ERROR("Error in the number of '('=" << countPTheseIn << " and ')'=" << countPTheseOut << " elements");
				return;
			}
			// count the number of '{' and '}'
			if (countBraceIn != countBraceOut ) {
				TK_ERROR("Error in the number of '{'=" << countBraceIn << " and '}'=" << countBraceOut << " elements");
				return;
			}
			// count the number of '[' and ']'
			if (countBracketIn != countBracketOut ) {
				TK_ERROR("Error in the number of '['=" << countBracketIn << " and ']'=" << countBracketOut << " elements");
				return;
			}
			// need to check if all () [] and {} is well set ...
			if (false == CheckGoodPosition(tmpExp) ) {
				return;
			}
			
			TK_REG_EXP_DBG_MODE("Main element :"; DisplayElem(tmpExp); );
			if(		tmpExp.Size()>0
				&&	tmpExp[0] == REGEXP_OPCODE_NO_CHAR)
			{
				//TK_DEBUG("=> must not begin with char");
				m_notBeginWithChar = true;
				// remove element
				tmpExp.Erase(0);
			}
			if(		tmpExp.Size()>0
				&&	tmpExp[tmpExp.Size()-1] == REGEXP_OPCODE_NO_CHAR)
			{
				//TK_DEBUG("=> must not end with char");
				m_notEndWithChar = true;
				// remove element
				tmpExp.Erase(tmpExp.Size()-1);
			}
			
			if (tmpExp.Size() != m_exprRootNode.Generate(tmpExp) ) {
				return;
			}
			// TODO : optimize node here ...
			//Display();
		
			// all OK ... play again 
			m_isOk = true;
		};
		
		/**
		 * @brief Get the regular expression string
		 * @return the string representing the RegExp
		 */
		const etk::UString& GetRegExp(void) const
		{
			return m_expressionRequested;
		};
		
		/**
		 * @brief Get the status if the regular expression parsing
		 * @return true : the regExp is correctly parsed
		 * @return false : an error occcured (check log ...)
		 */
		bool GetStatus(void)
		{
			return m_isOk;
		};
		// process the regular expression
		
		/**
		 * @brief process the seach of the regular expression in a defined class type
		 * @param[in] _SearchIn table of element to seach in
		 * @param[in] _startPos start position to search
		 * @param[in] _endPos end position to search
		 * @param[in] _escapeChar special char that remove other char real type
		 * @return true : find something, false otherwise
		 */
		bool Process( const CLASS_TYPE& _SearchIn,
		              esize_t _startPos,
		              esize_t _endPos,
		              etk::UniChar _escapeChar=0)
		{
			if (false == m_isOk) {
				return false;
			}
			esize_t buflen = _SearchIn.Size();
			if (_endPos > buflen) {
				_endPos = buflen;
			}
			if (_startPos > _endPos) {
				return false;
			}
			for (esize_t iii=_startPos; iii<_endPos; iii++) {
				esize_t findLen=0;
				esize_t maxlen = _endPos-iii;
				if (true == m_notBeginWithChar) {
					if (iii>0) {
						etk::UniChar tmpVal = _SearchIn[iii-1];
						if(    (    tmpVal >= 'a'
						         && tmpVal <= 'z' )
						    || (    tmpVal >= 'A'
						         && tmpVal <= 'Z' )
						    || (    tmpVal >= '0'
						         && tmpVal <= '9' )
						    || (    tmpVal == '_' ) ) {
							// go on the next char ...
							continue;
						}
					}
				}
				if (true == m_exprRootNode.Parse(_SearchIn, iii, maxlen, findLen)) {
					if(		_escapeChar != 0
						&&	iii>0)
					{
						if (_escapeChar == _SearchIn[iii-1]) {
							//==> detected escape char ==> try find again ...
							continue;
						}
					}
					// Check end :
					if (true == m_notEndWithChar) {
						if (iii+findLen < _SearchIn.Size() ) {
							etk::UniChar tmpVal = _SearchIn[iii+findLen];
							if(    (    tmpVal >= 'a'
							         && tmpVal <= 'z' )
							    || (    tmpVal >= 'A'
							         && tmpVal <= 'Z' )
							    || (    tmpVal >= '0'
							         && tmpVal <= '9' )
							    || (    tmpVal == '_' ) ) {
								// go on the next char ...
								continue;
							}
						}
					}
					m_areaFind.start = iii;
					m_areaFind.stop  = iii + findLen;
					/*
					if (iii == 812) {
						std::cout << std::endl;
						for(int32_t k=startPos; k<endPos; k++){
							std::cout << SearchIn[k];
						}
						std::cout << std::endl;
					}
					TK_DEBUG("Find RegExp at position : " << i << " startpos=" << startPos << " endPos=" << endPos << " with size :" << findLen << " type : "; );
					m_exprRootNode.Display(-1);
					TK_DEBUG("---------------------------------------------------");
					*/
					return true;
				}
			}
			return false;
		};
		
		bool ProcessOneElement( const CLASS_TYPE& _SearchIn,
		                        esize_t _startPos,
		                        esize_t _endPos,
		                        etk::UniChar _escapeChar=0)
		{
			if (false == m_isOk) {
				return false;
			}
			esize_t buflen = _SearchIn.Size();
			if (_endPos > buflen) {
				_endPos = buflen;
			}
			if (_startPos > _endPos) {
				return false;
			}
			esize_t findLen=0;
			esize_t maxlen = _endPos-_startPos;
			if (true == m_notBeginWithChar) {
				if (_startPos>0) {
					etk::UniChar tmpVal = _SearchIn[_startPos-1];
					if(    (    tmpVal >= 'a'
					         && tmpVal <= 'z' )
					    || (    tmpVal >= 'A'
					         && tmpVal <= 'Z' )
					    || (    tmpVal >= '0'
					         && tmpVal <= '9' )
					    || (    tmpVal == '_' ) ) {
						// go on the next char ...
						return false;
					}
				}
			}
			if (true == m_exprRootNode.Parse(_SearchIn, _startPos, maxlen, findLen)) {
				if(		_escapeChar != 0
					&&	_startPos>0)
				{
					if (_escapeChar == _SearchIn[_startPos-1]) {
						//==> detected escape char ==> try find again ...
						return false;
					}
				}
				// Check end :
				if (true == m_notEndWithChar) {
					if (_startPos+findLen < _SearchIn.Size() ) {
						etk::UniChar tmpVal = _SearchIn[_startPos+findLen];
						if(    (    tmpVal >= 'a'
						         && tmpVal <= 'z' )
						    || (    tmpVal >= 'A'
						         && tmpVal <= 'Z' )
						    || (    tmpVal >= '0'
						         && tmpVal <= '9' )
						    || (    tmpVal == '_' ) ) {
							// go on the next char ...
							return false;
						}
					}
				}
				m_areaFind.start = _startPos;
				m_areaFind.stop  = _startPos + findLen;
				return true;
			}
			return false;
		};
		
		
		/**
		 * @brief Get the expression start position detected
		 * @return position of the start regExp
		 */
		int32_t	Start(void) { return m_areaFind.start; };
		
		/**
		 * @brief Get the expression stop position detected
		 * @return position of the stop regExp
		 */
		int32_t	Stop(void) { return m_areaFind.stop; };
		
		/**
		 * @brief Display the reg Exp
		 */
		void Display(void)
		{
			m_exprRootNode.Display(0);
		};
	private:
		/**
		 * @brief
		 * @param[in,out] 
		 * @return
		 */
		bool CheckGoodPosition(const etk::Vector<etk::UniChar>& _tmpExp, esize_t& _pos)
		{
			etk::UniChar curentCode = _tmpExp[_pos];
			etk::UniChar endCode = REGEXP_OPCODE_PTHESE_OUT;
			const char *input = "(...)";
			if (curentCode == REGEXP_OPCODE_BRACKET_IN) {
				endCode = REGEXP_OPCODE_BRACKET_OUT;
				input = "[...]";
			} else if (curentCode == REGEXP_OPCODE_BRACE_IN){
				endCode = REGEXP_OPCODE_BRACE_OUT;
				input = "{x,x}";
			}
			_pos++;
			if (_pos >= _tmpExp.Size()) {
				TK_ERROR("ended with: ( or { or [ ... not permited");
				return false;
			}
			//TK_DEBUG(" ==> Find ELEMENT : ([{");
			// case dependent : 
			if(		curentCode == REGEXP_OPCODE_BRACKET_IN
				||	curentCode == REGEXP_OPCODE_BRACE_IN) {
				while(_pos<_tmpExp.Size()) {
					//TK_DEBUG("check : " << tmpExp[pos]);
					// if we find the end : 
					if (endCode == _tmpExp[_pos]) {
						return true;
					} else {
						// otherwise, we check the error in the element ...
						char *find = NULL;
						switch (_tmpExp[_pos].Get())
						{
							case REGEXP_OPCODE_PTHESE_IN:		find = (char*)"(";			break;
							case REGEXP_OPCODE_BRACKET_IN:		find = (char*)"[";			break;
							case REGEXP_OPCODE_BRACE_IN:		find = (char*)"{";			break;
							case REGEXP_OPCODE_PTHESE_OUT:		find = (char*)")";			break;
							case REGEXP_OPCODE_BRACKET_OUT:		find = (char*)"]";			break;
							case REGEXP_OPCODE_BRACE_OUT:		find = (char*)"}";			break;
							case REGEXP_OPCODE_STAR:			find = (char*)"*";			break;
							case REGEXP_OPCODE_DOT:				find = (char*)".";			break;
							case REGEXP_OPCODE_QUESTION:		find = (char*)"?";			break;
							case REGEXP_OPCODE_PLUS:			find = (char*)"+";			break;
							case REGEXP_OPCODE_PIPE:			find = (char*)"|";			break;
							case REGEXP_OPCODE_START_OF_LINE:	find = (char*)"^";			break;
							case REGEXP_OPCODE_END_OF_LINE:		find = (char*)"$";			break;
							case REGEXP_OPCODE_DIGIT:			find = (char*)"\\d";		break;
							case REGEXP_OPCODE_DIGIT_NOT:		find = (char*)"\\D";		break;
							case REGEXP_OPCODE_LETTER:			find = (char*)"\\l";		break;
							case REGEXP_OPCODE_LETTER_NOT:		find = (char*)"\\L";		break;
							case REGEXP_OPCODE_SPACE:			find = (char*)"\\s";		break;
							case REGEXP_OPCODE_SPACE_NOT:		find = (char*)"\\S";		break;
							case REGEXP_OPCODE_WORD:			find = (char*)"\\w";		break;
							case REGEXP_OPCODE_WORD_NOT:		find = (char*)"\\W";		break;
							case REGEXP_OPCODE_NO_CHAR:			find = (char*)"\\@";		break;
							default:														break;
						}
						if (NULL != find) {
							(void)input;
							TK_ERROR("can not have : '" << find << "' inside " << input << " element");
							return false;
						}
					}
					_pos++;
				}
			} else {
				while(_pos< _tmpExp.Size()) {
					if (endCode == _tmpExp[_pos]) {
						// find the last element
						return true;
					} else if (	_tmpExp[_pos] == REGEXP_OPCODE_BRACE_OUT) {
						TK_ERROR("find } inside a (...) without start {");
						return false;
					} else if (	_tmpExp[_pos] == REGEXP_OPCODE_BRACKET_OUT) {
						TK_ERROR("find ] inside a (...) without start [");
						return false;
					} else {
						if(    _tmpExp[_pos] == REGEXP_OPCODE_PTHESE_IN
						    || _tmpExp[_pos] == REGEXP_OPCODE_BRACKET_IN
						    || _tmpExp[_pos] == REGEXP_OPCODE_BRACE_IN ) {
							if (false==CheckGoodPosition(_tmpExp, _pos) ) {
								return false;
							}
						}
					}
					_pos++;
				}
			}
			
			// we did not find the cloder . ...
			if (endCode == REGEXP_OPCODE_BRACKET_OUT) {
				TK_ERROR("Missing ']' at the end");
			}
			if (endCode == REGEXP_OPCODE_BRACE_OUT) {
				TK_ERROR("Missing '}' at the end");
			}
			if (endCode == REGEXP_OPCODE_PTHESE_OUT) {
				TK_ERROR("Missing ')' at the end");
			}
			return false;
		};
		
		/**
		 * @brief
		 * @param[in,out] 
		 * @return
		 */
		bool CheckGoodPosition(const etk::Vector<etk::UniChar>& _tmpExp)
		{
			esize_t pos = 0;
			while (pos < _tmpExp.Size()) {
				//TK_DEBUG("check : " << tmpExp[pos]);
				if(    _tmpExp[pos] == REGEXP_OPCODE_PTHESE_IN
				    || _tmpExp[pos] == REGEXP_OPCODE_BRACKET_IN
				    || _tmpExp[pos] == REGEXP_OPCODE_BRACE_IN)
				{
					// attention the i position change inside the finction...
					if (false==CheckGoodPosition(_tmpExp, pos) ) {
						TK_ERROR("Error at position : " << pos+1 );
						return false;
					} else {
						//TK_DEBUG(" <== Find ELEMENT : ]})");
					}
				} else if(_tmpExp[pos] == REGEXP_OPCODE_PTHESE_OUT) {
					TK_ERROR("can find ')' with no start : ')'");
					return false;
				} else if(_tmpExp[pos] == REGEXP_OPCODE_BRACKET_OUT) {
					TK_ERROR("can find ']' with no start : '['");
					return false;
				} else if(_tmpExp[pos] == REGEXP_OPCODE_BRACE_OUT) {
					TK_ERROR("can find '}' with no start : '{'");
					return false;
				}
				pos++;
			}
			return true;
		};


};

}; // end of etk namespace

#undef __class__
#define __class__	(NULL)

#endif
