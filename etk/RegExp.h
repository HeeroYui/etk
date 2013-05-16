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
#include <etk/os/Memory.h>
#include <etk/UString.h>
#include <etk/Vector.h>

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
	bool     haveBackSlash;
	uint32_t inputValue;
	uint32_t newValue;
}convertionTable_ts;

extern const convertionTable_ts constConvertionTable[];
extern const int32_t constConvertionTableSize;

void DisplayElem(const etk::Vector<etk::UniChar>& _data, int32_t _start=0, int32_t _stop=0x7FFFFFFF);
char * levelSpace(int32_t _level);
int32_t GetLenOfPTheseElem(const etk::Vector<etk::UniChar>& _data, int32_t _startPos);
int32_t GetLenOfPThese(const etk::Vector<etk::UniChar>& _data, int32_t _startPos);
int32_t GetLenOfBracket(const etk::Vector<etk::UniChar>& _data, int32_t _startPos);
int32_t GetLenOfBrace(const etk::Vector<etk::UniChar>& _data, int32_t _startPos);
int32_t GetLenOfNormal(const etk::Vector<etk::UniChar>& _data, int32_t _startPos);
bool ParseBrace(const etk::Vector<etk::UniChar>& _data, int32_t& _min, int32_t& _max);


#undef __class__
#define __class__	"etk::RegExpNode"

/**
 *	@brief Node Elements for every-one
 */
template<class CLASS_TYPE> class RegExpNode
{
	protected :
		int32_t m_multipleMin; //!< minimum repetition (included)
		int32_t m_multipleMax; //!< maximum repetition (included)
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
		virtual bool Parse(const CLASS_TYPE& _data, int32_t _currentPos, int32_t _lenMax, int32_t& _findLen)=0;
		/*
		{
			findLen = 0;
			return false;
		};
		*/
		/**
		 * @brief Display the current node properties
		 * @param[in] level of the node
		 */
		virtual void Display(int32_t _level)
		{
			TK_INFO("Find NODE : " << levelSpace(_level) << "@???@ {" << GetMultMin() << "," << GetMultMax() << "}  subdata="; DisplayElem(m_RegExpData););
		};
		/**
		 * @brief Set the multiplicity of this Node.
		 * @param[in] _min The minimum appear time.
		 * @param[in] _max The maximum appear time.
		 */
		void SetMult(int32_t _min, int32_t _max)
		{
			m_multipleMin = etk_max(_min, 0);
			m_multipleMax = etk_max(_max, 1);
		}
	protected:
		/**
		 * @brief Get the minimum multiplicity.
		 * @return The minimum appear availlable.
		 */
		int32_t GetMultMin(void) const { return m_multipleMin; };
		/**
		 * @brief Get the maximum multiplicity.
		 * @return The maximum appear availlable.
		 */
		int32_t GetMultMax(void) const { return m_multipleMax; };
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
			//TK_DEBUG("Request Parse \"Value\" data="; DisplayElem(RegExpNode<CLASS_TYPE>::m_RegExpData););
			m_data.Clear();
			for (int32_t i=0; i<RegExpNode<CLASS_TYPE>::m_RegExpData.Size(); i++) {
				m_data.PushBack(RegExpNode<CLASS_TYPE>::m_RegExpData[i]);
			}
			return _data.Size();
		};
		
		virtual bool Parse(const CLASS_TYPE& _data, int32_t _currentPos, int32_t _lenMax, int32_t& _findLen)
		{
			_findLen = 0;
			//TK_INFO("Parse node : Value{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			if (0==m_data.Size()) {
				TK_ERROR("No data inside type elemTypeValue");
				return false;
			}
			//TK_DEBUG("check element value : '" << m_data[0] << "'");
			bool tmpFind = true;
			int32_t j;
			for (j=0; j<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind == true; j++) {
				int32_t ofset = 0;
				int32_t k;
				for (k=0; _findLen+k<_lenMax && k < m_data.Size(); k++) {
					if (m_data[k] != _data[_currentPos+_findLen+k]) {
						tmpFind=false;
						break;
					}
					ofset++;
				}
				if (k != (int32_t)m_data.Size()) {
					// parsing not ended ...
					tmpFind=false;
				}
				// Update local ofset of data
				if (true == tmpFind) {
					_findLen += ofset;
				}
			}
			if(		j>=RegExpNode<CLASS_TYPE>::m_multipleMin
				&&	j<=RegExpNode<CLASS_TYPE>::m_multipleMax
				&&	_findLen>0	)
			{
				//TK_DEBUG("find " << findLen);
				return true;
			} else if( 0 == RegExpNode<CLASS_TYPE>::m_multipleMin ) {
				//TK_DEBUG("find size=0");
				return true;
			}
			return false;
		};
		
		void Display(int32_t _level)
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
			//TK_DEBUG("Request Parse [...] data="; DisplayElem(RegExpNode<CLASS_TYPE>::m_RegExpData););
			m_data.Clear();
			
			etk::UniChar lastElement = 'a';
			bool multipleElement = false;
			//
			for (int32_t k=0; k<RegExpNode<CLASS_TYPE>::m_RegExpData.Size(); k++) {
				if (RegExpNode<CLASS_TYPE>::m_RegExpData[k] == REGEXP_OPCODE_TO && multipleElement == true) {
					TK_ERROR("Can not have 2 consecutive - in [...]");
					return 0;
				} else if (multipleElement == true) {
					etk::UniChar j='\0';
					for (j=lastElement+1; j <= RegExpNode<CLASS_TYPE>::m_RegExpData[k]; j+=1) {
						m_data.PushBack(j);
					}
					multipleElement = false;
				} else if(RegExpNode<CLASS_TYPE>::m_RegExpData[k] == REGEXP_OPCODE_TO) {
					multipleElement = true;
				} else {
					lastElement = RegExpNode<CLASS_TYPE>::m_RegExpData[k];
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
		
		virtual bool Parse(const CLASS_TYPE& _data, int32_t _currentPos, int32_t _lenMax, int32_t& _findLen)
		{
			_findLen = 0;
			//TK_INFO("Parse node : [...]{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			if (0==m_data.Size()) {
				TK_ERROR("No data inside type elemTypeValue");
				return false;
			}
			//TK_DEBUG("one of element value List : "; DisplayElem(element->m_data););
			bool tmpFind = true;
			int32_t j;
			for (j=0; j<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind ==true && j < _lenMax; j++) {
				int32_t i;
				tmpFind=false;
				for (i=0; i<m_data.Size(); i++) {
					if (_data[_currentPos+j] == m_data[i]) {
						_findLen += 1;
						tmpFind=true;
						break;
					}
				}
			}
			if(		j>=RegExpNode<CLASS_TYPE>::m_multipleMin
				&&	j<=RegExpNode<CLASS_TYPE>::m_multipleMax
				&&	_findLen>0	)
			{
				//TK_DEBUG("find " << findLen);
				return true;
			} else if( 0 == RegExpNode<CLASS_TYPE>::m_multipleMin ) {
				//TK_DEBUG("find size=0");
				return true;
			}
			return false;
		};
		
		void Display(int32_t _level)
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
		
		virtual bool Parse(const CLASS_TYPE& _data, int32_t _currentPos, int32_t _lenMax, int32_t& _findLen)
		{
			_findLen = 0;
			//TK_INFO("Parse node : Digit{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "} : "<< data[currentPos] << " lenMax=" << lenMax);
			bool tmpFind = true;
			int32_t j;
			for (j=0; j<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind ==true && j < _lenMax; j++) {
				etk::UniChar tmpVal = _data[_currentPos+j];
				//TK_DEBUG("compare : " << tmpVal);
				if(    tmpVal >= '0'
				    && tmpVal <= '9')
				{
					//TK_DEBUG("find ++");
					_findLen += 1;
				} else {
					tmpFind=false;
				}
			}
			if(		j>=RegExpNode<CLASS_TYPE>::m_multipleMin
				&&	j<=RegExpNode<CLASS_TYPE>::m_multipleMax
				&&	_findLen>0	)
			{
				//TK_DEBUG("find " << findLen);
				return true;
			} else if( 0 == RegExpNode<CLASS_TYPE>::m_multipleMin ) {
				//TK_DEBUG("find size=0");
				return true;
			}
			return false;
		};
		
		void Display(int32_t _level)
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
		
		virtual bool Parse(const CLASS_TYPE& _data, int32_t _currentPos, int32_t _lenMax, int32_t& _findLen)
		{
			_findLen = 0;
			//TK_INFO("Parse node : DigitNot{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			bool tmpFind = true;
			int32_t j;
			for (j=0; j<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind ==true && j < _lenMax; j++) {
				etk::UniChar tmpVal = _data[_currentPos+j];
				if(    tmpVal < '0'
				    || tmpVal > '9') {
					_findLen += 1;
				} else {
					tmpFind=false;
				}
			}
			if(    j>=RegExpNode<CLASS_TYPE>::m_multipleMin
			    && j<=RegExpNode<CLASS_TYPE>::m_multipleMax
			    && _findLen>0 ) {
				//TK_DEBUG("find " << findLen);
				return true;
			} else if( 0 == RegExpNode<CLASS_TYPE>::m_multipleMin ) {
				//TK_DEBUG("find size=0");
				return true;
			}
			return false;
		};
		
		void Display(int32_t _level)
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
		
		virtual bool Parse(const CLASS_TYPE& _data, int32_t _currentPos, int32_t _lenMax, int32_t& _findLen)
		{
			_findLen = 0;
			//TK_INFO("Parse node : Letter{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			bool tmpFind = true;
			int32_t j;
			for (j=0; j<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind ==true && j < _lenMax; j++) {
				etk::UniChar tmpVal = _data[_currentPos+j];
				if(    (    tmpVal >= 'a'
				         && tmpVal <= 'z')
				    || (    tmpVal >= 'A'
				         && tmpVal <= 'Z') ) {
					_findLen += 1;
				} else {
					tmpFind=false;
				}
			}
			if(    j>=RegExpNode<CLASS_TYPE>::m_multipleMin
			    && j<=RegExpNode<CLASS_TYPE>::m_multipleMax
			    && _findLen>0 ) {
				//TK_DEBUG("find " << findLen);
				return true;
			} else if( 0 == RegExpNode<CLASS_TYPE>::m_multipleMin ) {
				//TK_DEBUG("find size=0");
				return true;
			}
			return false;
		};
		
		void Display(int32_t _level)
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
		
		virtual bool Parse(const CLASS_TYPE& _data, int32_t _currentPos, int32_t _lenMax, int32_t& _findLen)
		{
			_findLen = 0;
			//TK_INFO("Parse node : LetterNot{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			bool tmpFind = true;
			int32_t j;
			for (j=0; j<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind ==true && j < _lenMax; j++) {
				etk::UniChar tmpVal = _data[_currentPos+j];
				if(    (    tmpVal < 'a'
				         && tmpVal > 'Z')
				    || tmpVal < 'A'
				    || tmpVal > 'z') {
					_findLen += 1;
				} else {
					tmpFind=false;
				}
			}
			if(    j>=RegExpNode<CLASS_TYPE>::m_multipleMin
			    && j<=RegExpNode<CLASS_TYPE>::m_multipleMax
			    && _findLen>0 ) {
				//TK_DEBUG("find " << findLen);
				return true;
			} else if( 0 == RegExpNode<CLASS_TYPE>::m_multipleMin ) {
				//TK_DEBUG("find size=0");
				return true;
			}
			return false;
		};
		
		void Display(int32_t _level)
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
		
		virtual bool Parse(const CLASS_TYPE& _data, int32_t _currentPos, int32_t _lenMax, int32_t& _findLen)
		{
			_findLen = 0;
			//TK_INFO("Parse node : Space{" << m_multipleMin << "," << m_multipleMax << "}");
			bool tmpFind = true;
			int32_t j;
			for (j=0; j<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind ==true && j < _lenMax; j++) {
				etk::UniChar tmpVal = _data[_currentPos+j];
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
			if(    j>=RegExpNode<CLASS_TYPE>::m_multipleMin
			    && j<=RegExpNode<CLASS_TYPE>::m_multipleMax
			    && _findLen>0 ) {
				//TK_DEBUG("find " << findLen);
				return true;
			} else if( 0 == RegExpNode<CLASS_TYPE>::m_multipleMin ) {
				//TK_DEBUG("find size=0");
				return true;
			}
			return false;
		};
		
		void Display(int32_t _level)
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
		
		virtual bool Parse(const CLASS_TYPE& _data, int32_t _currentPos, int32_t _lenMax, int32_t& _findLen)
		{
			_findLen = 0;
			//TK_INFO("Parse node : SpaceNot{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			bool tmpFind = true;
			int32_t j;
			for (j=0; j<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind ==true && j < _lenMax; j++) {
				etk::UniChar tmpVal = _data[_currentPos+j];
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
			if(    j>=RegExpNode<CLASS_TYPE>::m_multipleMin
			    && j<=RegExpNode<CLASS_TYPE>::m_multipleMax
			    && _findLen>0 ) {
				//TK_DEBUG("find " << findLen);
				return true;
			} else if( 0 == RegExpNode<CLASS_TYPE>::m_multipleMin ) {
				//TK_DEBUG("find size=0");
				return true;
			}
			return false;
		};
		
		void Display(int32_t _level)
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
		
		virtual bool Parse(const CLASS_TYPE& _data, int32_t _currentPos, int32_t _lenMax, int32_t& _findLen)
		{
			_findLen = 0;
			//TK_INFO("Parse node : Word{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			bool tmpFind = true;
			int32_t j;
			for (j=0; j<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind ==true && j < _lenMax; j++) {
				etk::UniChar tmpVal = _data[_currentPos+j];
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
			if(    j>=RegExpNode<CLASS_TYPE>::m_multipleMin
			    && j<=RegExpNode<CLASS_TYPE>::m_multipleMax
			    && _findLen>0 ) {
				//TK_DEBUG("find " << findLen);
				return true;
			} else if( 0 == RegExpNode<CLASS_TYPE>::m_multipleMin ) {
				//TK_DEBUG("find size=0");
				return true;
			}
			return false;
		};
		
		void Display(int32_t _level)
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
		
		virtual bool Parse(const CLASS_TYPE& _data, int32_t _currentPos, int32_t _lenMax, int32_t& _findLen)
		{
			_findLen = 0;
			//TK_INFO("Parse node : WordNot{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			bool tmpFind = true;
			int32_t j;
			for (j=0; j<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind ==true && j < _lenMax; j++) {
				etk::UniChar tmpVal = _data[_currentPos+j];
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
			if(    j>=RegExpNode<CLASS_TYPE>::m_multipleMin
			    && j<=RegExpNode<CLASS_TYPE>::m_multipleMax
			    && _findLen>0 ) {
				//TK_DEBUG("find " << findLen);
				return true;
			} else if( 0 == RegExpNode<CLASS_TYPE>::m_multipleMin ) {
				//TK_DEBUG("find size=0");
				return true;
			}
			return false;
		};
		
		void Display(int32_t _level)
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
		
		virtual bool Parse(const CLASS_TYPE& _data, int32_t _currentPos, int32_t _lenMax, int32_t& _findLen)
		{
			_findLen = 0;
			//TK_INFO("Parse node : '.'{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			// equivalent a : [^\x00-\x08\x0A-\x1F\x7F]
			bool tmpFind = true;
			int32_t j;
			for (j=0; j<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind ==true && j < _lenMax; j++) {
				etk::UniChar tmpVal = _data[_currentPos+j];
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
			if(    j>=RegExpNode<CLASS_TYPE>::m_multipleMin
			    && j<=RegExpNode<CLASS_TYPE>::m_multipleMax
			    && _findLen>0 ) {
				//TK_DEBUG("find " << findLen);
				return true;
			} else if( 0 == RegExpNode<CLASS_TYPE>::m_multipleMin ) {
				//TK_DEBUG("find size=0");
				return true;
			}
			return false;
		};
		
		void Display(int32_t _level)
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
		
		virtual bool Parse(const CLASS_TYPE& _data, int32_t _currentPos, int32_t _lenMax, int32_t& _findLen)
		{
			_findLen = 0;
			// TODO : ...
			TK_INFO("Parse node : SOL{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			return false;
		};
		
		void Display(int32_t _level)
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
		
		virtual bool Parse(const CLASS_TYPE& _data, int32_t _currentPos, int32_t _lenMax, int32_t& _findLen)
		{
			_findLen = 0;
			// TODO : ...
			TK_INFO("Parse node : EOL{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			return false;
		};
		
		void Display(int32_t _level)
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
			//TK_DEBUG("Request Parse (elem) data="; DisplayElem(RegExpNode<CLASS_TYPE>::m_RegExpData););
			int32_t pos = 0;
			int32_t elementSize = 0;
			etk::Vector<etk::UniChar> tmpData;
			while (pos < RegExpNode<CLASS_TYPE>::m_RegExpData.Size()) {
				tmpData.Clear();
				switch (RegExpNode<CLASS_TYPE>::m_RegExpData[pos].Get()) {
					case REGEXP_OPCODE_PTHESE_IN:
						{
							elementSize=GetLenOfPThese(RegExpNode<CLASS_TYPE>::m_RegExpData, pos);
							for (int32_t k=pos+1; k<pos+elementSize+1; k++) {
								tmpData.PushBack(RegExpNode<CLASS_TYPE>::m_RegExpData[k]);
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
							for (int32_t k=pos+1; k<pos+elementSize+1; k++) {
								tmpData.PushBack(RegExpNode<CLASS_TYPE>::m_RegExpData[k]);
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
							for (int32_t k=pos+1; k<pos+elementSize+1; k++) {
								tmpData.PushBack(RegExpNode<CLASS_TYPE>::m_RegExpData[k]);
							}
							int32_t min = 0;
							int32_t max = 0;
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
							for (int32_t k=pos; k<pos+elementSize; k++) {
								tmpData.PushBack(RegExpNode<CLASS_TYPE>::m_RegExpData[k]);
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
		
		virtual bool Parse(const CLASS_TYPE& _data, int32_t _currentPos, int32_t _lenMax, int32_t& _findLen)
		{
			_findLen = 0;
			//TK_INFO("Parse node : (Elem){" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			// NOTE 1 : Must done only one time in EVERY case ...
			// NOTE 2 : All element inside must be OK
			if (0 == m_subNode.Size()) {
				return false;
			}
			int32_t tmpCurrentPos = _currentPos;
			for (int32_t i=0; i<m_subNode.Size(); i++) {
				int32_t tmpFindLen;
				if (false == m_subNode[i]->Parse(_data, tmpCurrentPos, _lenMax, tmpFindLen)) {
					_findLen = 0;
					return false;
				} else {
					tmpCurrentPos += tmpFindLen;
				}
			}
			_findLen = tmpCurrentPos - _currentPos;
			return true;
		};
		
		void Display(int32_t _level)
		{
			TK_INFO("Find NODE : " << levelSpace(_level) << "@(Elem)@ {" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}  subdata="; DisplayElem(RegExpNode<CLASS_TYPE>::m_RegExpData););
			for(int32_t iii=0; iii<m_subNode.Size(); iii++) {
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
		bool SetMultiplicityOnLastNode(int32_t _min, int32_t _max)
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
			//TK_DEBUG("Request Parse (...) data="; DisplayElem(RegExpNode<CLASS_TYPE>::m_RegExpData););
			//Find all the '|' in the string (and at the good level ...) 
			int32_t pos = 0;
			int32_t elementSize = GetLenOfPTheseElem(RegExpNode<CLASS_TYPE>::m_RegExpData, pos);
			// generate all the "elemTypePTheseElem" of the Node
			while (elementSize>0) {
				// geerate output deta ...
				etk::Vector<etk::UniChar> tmpData;
				for (int32_t k=pos; k<pos+elementSize; k++) {
					tmpData.PushBack(RegExpNode<CLASS_TYPE>::m_RegExpData[k]);
				}
				RegExpNodePTheseElem<CLASS_TYPE> * myElem = new RegExpNodePTheseElem<CLASS_TYPE>();
				(void)myElem->Generate(tmpData);
				// add to the subnode list : 
				m_subNode.PushBack(myElem);
				pos += elementSize+1;
				//TK_DEBUG("plop="; DisplayElem(data, pos, pos+1););
				elementSize = GetLenOfPTheseElem(RegExpNode<CLASS_TYPE>::m_RegExpData, pos);
				//TK_DEBUG("find " << elementSize << " elements");
			}
			if (0 == pos && 0 == elementSize) {
				TK_ERROR("No data in the (...) element at " << pos);
				return false;
			}
			return _data.Size();
		};
		
		virtual bool Parse(const CLASS_TYPE& _data, int32_t _currentPos, int32_t _lenMax, int32_t& _findLen)
		{
			_findLen = 0;
			//TK_INFO("Parse node : (...){" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			if (0 == m_subNode.Size()) {
				return false;
			}
			bool tmpFind = true;
			int32_t j;
			for (j=0; j<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind == true ; j++) {
				tmpFind = false;
				for (int32_t i=0; i<m_subNode.Size(); i++) {
					int32_t tmpFindLen;
					if (true == m_subNode[i]->Parse(_data, _currentPos+_findLen, _lenMax, tmpFindLen)) {
						_findLen += tmpFindLen;
						tmpFind = true;
					}
				}
			}
			if(		j>=RegExpNode<CLASS_TYPE>::m_multipleMin
				&&	j<=RegExpNode<CLASS_TYPE>::m_multipleMax
				&&	_findLen>0	)
			{
				//TK_DEBUG("find " << findLen);
				return true;
			} else if( 0 == RegExpNode<CLASS_TYPE>::m_multipleMin ) {
				//TK_DEBUG("find size=0");
				return true;
			}
			return false;
		};
		
		void Display(int32_t _level)
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
		RegExp(const etk::UString &_exp) :
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
			
			//TK_DEBUG("Parse RegExp : " << expressionRequested.c_str() );
			m_isOk = false;
			m_areaFind.start=0;
			m_areaFind.stop=0;
			m_notBeginWithChar = false;
			m_notEndWithChar = false;
			
			// change in the regular Opcode ==> replace \x with the corect element ... x if needed
			int32_t iii;
			int32_t countBraceIn = 0;
			int32_t countBraceOut = 0;
			int32_t countPTheseIn = 0;
			int32_t countPTheseOut = 0;
			int32_t countBracketIn = 0;
			int32_t countBracketOut = 0;
			for (iii=0; iii<_regexp.Size(); iii++) {
				if (_regexp[iii] == '\\') {
					if(iii+1>=_regexp.Size()) {
						TK_ERROR("Dangerous parse of the element pos " << iii << " \\ with nothing after");
						// TODO : Generate Exeption ...
						return;
					}
					int32_t j;
					// Find the element in the list...
					for (j=0; j<constConvertionTableSize; j++) {
						if(		true == constConvertionTable[j].haveBackSlash 
							&&	_regexp[iii+1] == constConvertionTable[j].inputValue)
						{
							tmpExp.PushBack(constConvertionTable[j].newValue);
							break;
						}
					}
					// check error : 
					if (j==constConvertionTableSize) {
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
					int32_t j;
					// find the element in the list...
					for (j=0; j<constConvertionTableSize; j++) {
						if(		false == constConvertionTable[j].haveBackSlash 
							&&	_regexp[iii] == constConvertionTable[j].inputValue)
						{
							tmpExp.PushBack(constConvertionTable[j].newValue);
							break;
						}
					}
					// not find : normal element
					if (j==constConvertionTableSize) {
						// TODO : It might have an error ...
//						tmpExp.PushBack(_regexp[iii]);
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
			
			//TK_DEBUG("Main element :"; DisplayElem(tmpExp, 0, tmpExp.Size()); );
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
		              int32_t _startPos,
		              int32_t _endPos,
		              char _escapeChar=0)
		{
			if (false == m_isOk) {
				return false;
			}
			int32_t buflen = _SearchIn.Size();
			if (_endPos > buflen) {
				_endPos = buflen;
			}
			if (_startPos > _endPos) {
				return false;
			}
			int32_t i = 0;
			for (i=_startPos; i<_endPos; i++) {
				int32_t findLen=0;
				int32_t maxlen = _endPos-i;
				if (true == m_notBeginWithChar) {
					if (i>0) {
						etk::UniChar tmpVal = _SearchIn[i-1];
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
				if (true == m_exprRootNode.Parse(_SearchIn, i, maxlen, findLen)) {
					if(		_escapeChar != 0
						&&	i>0)
					{
						if ((char)_SearchIn[i-1] == _escapeChar) {
							//==> detected escape char ==> try find again ...
							continue;
						}
					}
					// Check end :
					if (true == m_notEndWithChar) {
						if (i+findLen < _SearchIn.Size() ) {
							etk::UniChar tmpVal = _SearchIn[i+findLen];
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
					m_areaFind.start = i;
					m_areaFind.stop  = i + findLen;
					/*
					if (i == 812) {
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
		                        int32_t _startPos,
		                        int32_t _endPos,
		                        char _escapeChar=0)
		{
			if (false == m_isOk) {
				return false;
			}
			int32_t buflen = _SearchIn.Size();
			if (_endPos > buflen) {
				_endPos = buflen;
			}
			if (_startPos > _endPos) {
				return false;
			}
			int32_t findLen=0;
			int32_t maxlen = _endPos-_startPos;
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
					if (_SearchIn[_startPos-1] == _escapeChar) {
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
		bool CheckGoodPosition(const etk::Vector<etk::UniChar>& _tmpExp, int32_t& _pos)
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
			int32_t pos = 0;
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
