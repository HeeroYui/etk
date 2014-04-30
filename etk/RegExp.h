/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/types.h>

#ifndef __TK_REG_EXP_H__
#define __TK_REG_EXP_H__

#include <etk/debug.h>
#include <etk/stdTools.h>
#include <vector>


#define TK_REG_EXP_DBG_MODE TK_VERBOSE
//#define TK_REG_EXP_DBG_MODE TK_DEBUG

//regular colors
#define ETK_BASH_COLOR_BLACK			"\e[0;30m"
#define ETK_BASH_COLOR_RED				"\e[0;31m"
#define ETK_BASH_COLOR_GREEN			"\e[0;32m"
#define ETK_BASH_COLOR_YELLOW			"\e[0;33m"
#define ETK_BASH_COLOR_BLUE				"\e[0;34m"
#define ETK_BASH_COLOR_MAGENTA			"\e[0;35m"
#define ETK_BASH_COLOR_CYAN				"\e[0;36m"
#define ETK_BASH_COLOR_WHITE			"\e[0;37m"
//emphasized (bolded) colors
#define ETK_BASH_COLOR_BOLD_BLACK		"\e[1;30m"
#define ETK_BASH_COLOR_BOLD_RED			"\e[1;31m"
#define ETK_BASH_COLOR_BOLD_GREEN		"\e[1;32m"
#define ETK_BASH_COLOR_BOLD_YELLOW		"\e[1;33m"
#define ETK_BASH_COLOR_BOLD_BLUE		"\e[1;34m"
#define ETK_BASH_COLOR_BOLD_MAGENTA		"\e[1;35m"
#define ETK_BASH_COLOR_BOLD_CYAN		"\e[1;36m"
#define ETK_BASH_COLOR_BOLD_WHITE		"\e[1;37m"
//background colors
#define ETK_BASH_COLOR_BG_BLACK			"\e[40m"
#define ETK_BASH_COLOR_BG_RED			"\e[41m"
#define ETK_BASH_COLOR_BG_GREEN			"\e[42m"
#define ETK_BASH_COLOR_BG_YELLOW		"\e[43m"
#define ETK_BASH_COLOR_BG_BLUE			"\e[44m"
#define ETK_BASH_COLOR_BG_MAGENTA		"\e[45m"
#define ETK_BASH_COLOR_BG_CYAN			"\e[46m"
#define ETK_BASH_COLOR_BG_WHITE			"\e[47m"
// Return to the normal color setings
#define ETK_BASH_COLOR_NORMAL			"\e[0m"


namespace etk {
//in the unicode section we have : [E000..F8FF]   private area ==> we will store element in this area:
// internal define to permit to have all needed system
enum regExpPrivateSection {
	regexpOpcodePTheseIn=0xE000,	/* ( */
	regexpOpcodePTheseOut,/* ) */
	regexpOpcodeBracketIn,/* [ */
	regexpOpcodeBracketOut,/* ] */
	regexpOpcodeBracetIn,/* { */
	regexpOpcodeBracetOut,/* } */
	regexpOpcodeTo,/* - */
	regexpOpcodeStar,/* * */
	regexpOpcodeDot,/* . */
	regexpOpcodeQuestion,/* ? */
	regexpOpcodePlus,/* + */
	regexpOpcodePipe,/* | */
	regexpOpcodeStartOfLine,/* ^  this is also NOT, but not manage */
	regexpOpcodeEndOfLine,/* $ */
	regexpOpcodeDigit,/* \d */
	regexpOpcodeDigitNot,/* \D */
	regexpOpcodeLetter,/* \l */
	regexpOpcodeLetterNot,/* \L */
	regexpOpcodeSpace,/* \s */
	regexpOpcodeSpaceNot,/* \S */
	regexpOpcodeWord,/* \w */
	regexpOpcodeWordNot,/* \W */
	regexpOpcodeNoChar,/* \@ */
	regexpOpcodeError, // not used
};
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
/**
 * @brief convertion table of every element in a regular expression.
 * @not-in-doc
 */
struct convertionTable {
	bool haveBackSlash;
	char inputValue;
	char newValue;
	enum etk::regExpPrivateSection specialChar;
};

//! @not-in-doc
extern const struct convertionTable constConvertionTable[];
//! @not-in-doc
extern const int64_t constConvertionTableSize;
//! @not-in-doc
std::ostream& displayElem(std::ostream& _os, const std::vector<char32_t>& _data, int64_t _start=0, int64_t _stop=0x7FFFFFFF);
//! @not-in-doc
char * levelSpace(uint32_t _level);
//! @not-in-doc
int64_t getLenOfPTheseElem(const std::vector<char32_t>& _data, int64_t _startPos);
//! @not-in-doc
int64_t getLenOfPThese(const std::vector<char32_t>& _data, int64_t _startPos);
//! @not-in-doc
int64_t getLenOfBracket(const std::vector<char32_t>& _data, int64_t _startPos);
//! @not-in-doc
int64_t getLenOfBrace(const std::vector<char32_t>& _data, int64_t _startPos);
//! @not-in-doc
int64_t getLenOfNormal(const std::vector<char32_t>& _data, int64_t _startPos);
//! @not-in-doc
bool parseBrace(const std::vector<char32_t>& _data, uint32_t& _min, uint32_t& _max);


#undef __class__
#define __class__	"etk::RegExpNode"

/**
 * @brief Node Elements for every-one
 * @not-in-doc
 */
template<class CLASS_TYPE> class RegExpNode {
	protected :
		uint32_t m_multipleMin; //!< minimum repetition (included)
		uint32_t m_multipleMax; //!< maximum repetition (included)
		// Data Section ... (can have no data...)
		std::vector<char32_t> m_RegExpData; //!< data to parse and compare in some case ...
	public :
		/**
		 * @brief Constructor
		 */
		RegExpNode(void) :
		  m_multipleMin(1),
		  m_multipleMax(1) {
			
		};
		/**
		 * @brief Destructor
		 */
		virtual ~RegExpNode(void) { };
		/**
		 * @brief Generate the regular expression with the current "converted string"
		 * @param[in] _data Property of the regexp
		 * @return the number of element used
		 */
		virtual int32_t generate(const std::vector<char32_t>& _data) {
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
		virtual bool parse(const CLASS_TYPE& _data, int64_t _currentPos, int64_t _lenMax, int64_t& _findLen)=0;
		/**
		 * @brief Display the current node properties
		 * @param[in] level of the node
		 */
		virtual void display(uint32_t _level) {
			TK_INFO("Find NODE : " << levelSpace(_level) << "@???@ {" << getMultMin() << "," << getMultMax() << "}  subdata=" /*<< etk::displayElem(m_RegExpData) */);
		};
		/**
		 * @brief Set the multiplicity of this Node.
		 * @param[in] _min The minimum appear time.
		 * @param[in] _max The maximum appear time.
		 */
		void setMult(uint32_t _min, uint32_t _max) {
			m_multipleMin = etk_max(_min, 0);
			m_multipleMax = etk_max(_max, 1);
		}
	protected:
		/**
		 * @brief Get the minimum multiplicity.
		 * @return The minimum appear availlable.
		 */
		uint32_t getMultMin(void) const {
			return m_multipleMin;
		};
		/**
		 * @brief Get the maximum multiplicity.
		 * @return The maximum appear availlable.
		 */
		uint32_t getMultMax(void) const {
			return m_multipleMax;
		};
};

#undef __class__
#define __class__ "etk::RegExpNodeValue"

template<class CLASS_TYPE> class RegExpNodeValue : public etk::RegExpNode<CLASS_TYPE> {
	protected :
		// SubNodes :
		std::vector<char32_t> m_data;
	public :
		
		/**
		 * @brief Constructor
		 */
		RegExpNodeValue(void) { };
		
		/**
		 * @brief Destructor
		 */
		~RegExpNodeValue(void) { };
		
		int32_t generate(const std::vector<char32_t>& _data) {
			RegExpNode<CLASS_TYPE>::m_RegExpData = _data;
			TK_REG_EXP_DBG_MODE("Request Parse \"Value\" data=" /*<< etk::displayElem(RegExpNode<CLASS_TYPE>::m_RegExpData)*/ );
			m_data.clear();
			for (int32_t i=0; i<RegExpNode<CLASS_TYPE>::m_RegExpData.size(); i++) {
				m_data.push_back(RegExpNode<CLASS_TYPE>::m_RegExpData[i]);
			}
			return _data.size();
		};
		
		virtual bool parse(const CLASS_TYPE& _data, int64_t _currentPos, int64_t _lenMax, int64_t& _findLen) {
			_findLen = 0;
			TK_REG_EXP_DBG_MODE("Parse node : Value{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			if (0==m_data.size()) {
				TK_ERROR("No data inside type elemTypeValue");
				return false;
			}
			TK_REG_EXP_DBG_MODE("check element value : '" << m_data[0] << "'");
			bool tmpFind = true;
			uint32_t jjj;
			for (jjj=0; jjj<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind == true; jjj++) {
				uint32_t ofset = 0;
				int64_t kkk;
				for (kkk=0; _findLen+kkk<_lenMax && kkk < m_data.size(); kkk++) {
					if (m_data[kkk] != _data[_currentPos+_findLen+kkk]) {
						tmpFind=false;
						break;
					}
					ofset++;
				}
				if (kkk != m_data.size()) {
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
		
		void display(uint32_t _level) {
			TK_INFO("Find NODE : " << levelSpace(_level) << "@Value@ {"
			        << RegExpNode<CLASS_TYPE>::m_multipleMin << ","
			        << RegExpNode<CLASS_TYPE>::m_multipleMax << "} subdata="
			        /*<< etk::displayElem(RegExpNode<CLASS_TYPE>::m_RegExpData)*/
			        << " data: " /*<< etk::displayElem(m_data)*/ );
		};
};
#undef __class__
#define __class__ "etk::RegExpNodeBracket"

/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class RegExpNodeBracket : public etk::RegExpNode<CLASS_TYPE> {
	protected :
		// SubNodes :
		std::vector<char32_t> m_data;
	public:
		/**
		 * @brief Constructor
		 */
		RegExpNodeBracket(void) { };
		/**
		 * @brief Destructor
		 */
		~RegExpNodeBracket(void) { };
		int32_t generate(const std::vector<char32_t>& _data) {
			RegExpNode<CLASS_TYPE>::m_RegExpData = _data;
			TK_REG_EXP_DBG_MODE("Request Parse [...] data=" /*<< etk::displayElem(RegExpNode<CLASS_TYPE>::m_RegExpData)*/ );
			m_data.clear();
			
			char32_t lastElement = 'a';
			bool multipleElement = false;
			//
			for (int32_t kkk=0; kkk<RegExpNode<CLASS_TYPE>::m_RegExpData.size(); kkk++) {
				if (RegExpNode<CLASS_TYPE>::m_RegExpData[kkk] == regexpOpcodeTo && multipleElement == true) {
					TK_ERROR("Can not have 2 consecutive - in [...]");
					return 0;
				} else if (multipleElement == true) {
					char32_t jjj='\0';
					for (jjj=lastElement+1; jjj <= RegExpNode<CLASS_TYPE>::m_RegExpData[kkk]; jjj+=1) {
						m_data.push_back(jjj);
					}
					multipleElement = false;
				} else if(RegExpNode<CLASS_TYPE>::m_RegExpData[kkk] == regexpOpcodeTo) {
					multipleElement = true;
				} else {
					lastElement = RegExpNode<CLASS_TYPE>::m_RegExpData[kkk];
					m_data.push_back(lastElement);
				}
			}
			// check size ...
			if (m_data.size() == 0) {
				TK_ERROR("No data inside [...] ");
				return 0;
			}
			return _data.size();
		};
		virtual bool parse(const CLASS_TYPE& _data, int64_t _currentPos, int64_t _lenMax, int64_t& _findLen) {
			_findLen = 0;
			TK_REG_EXP_DBG_MODE("Parse node : [...]{" << RegExpNode<CLASS_TYPE>::m_multipleMin
			                    << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			if (0==m_data.size()) {
				TK_ERROR("No data inside type elemTypeValue");
				return false;
			}
			TK_REG_EXP_DBG_MODE("one of element value List : " /*<< etk::displayElem(m_data)*/);
			bool tmpFind = true;
			uint32_t jjj=0;
			for (jjj=0; jjj<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind ==true && jjj < _lenMax; jjj++) {
				tmpFind=false;
				for (int64_t iii=0; iii<m_data.size(); iii++) {
					if (m_data[iii] == _data[_currentPos+jjj]) {
						_findLen += 1;
						tmpFind=true;
						break;
					}
				}
			}
			if (    jjj>=RegExpNode<CLASS_TYPE>::m_multipleMin
			     && jjj<=RegExpNode<CLASS_TYPE>::m_multipleMax
			     && _findLen>0)
			{
				TK_REG_EXP_DBG_MODE("find " << _findLen);
				return true;
			} else if( 0 == RegExpNode<CLASS_TYPE>::m_multipleMin ) {
				TK_REG_EXP_DBG_MODE("find size=0");
				return true;
			}
			return false;
		};
		void display(uint32_t _level) {
			TK_INFO("Find NODE : " << levelSpace(_level) << "@[...]@ {" << RegExpNode<CLASS_TYPE>::m_multipleMin
			        << "," << RegExpNode<CLASS_TYPE>::m_multipleMax
			        << "}  subdata=" /*<< etk::displayElem(RegExpNode<CLASS_TYPE>::m_RegExpData)*/
			        << " data: " /*<< etk::displayElem(m_data)*/ );
		};
};
#undef __class__
#define __class__ "etk::RegExpNodeDigit"

/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class RegExpNodeDigit : public etk::RegExpNode<CLASS_TYPE> {
	public :
		/**
		 * @brief Constructor
		 */
		RegExpNodeDigit(void) { };
		/**
		 * @brief Destructor
		 */
		~RegExpNodeDigit(void) { };
		virtual bool parse(const CLASS_TYPE& _data, int64_t _currentPos, int64_t _lenMax, int64_t& _findLen) {
			_findLen = 0;
			TK_REG_EXP_DBG_MODE("Parse node : Digit{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "} : "<< _data[_currentPos] << " lenMax=" << _lenMax);
			bool tmpFind = true;
			uint32_t jjj;
			for (jjj=0; jjj<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind ==true && jjj < _lenMax; jjj++) {
				char32_t tmpVal = _data[_currentPos+jjj];
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
		void display(uint32_t _level) {
			TK_INFO("Find NODE : " << levelSpace(_level) << "@Digit@ {"
			        << RegExpNode<CLASS_TYPE>::m_multipleMin << ","
			        << RegExpNode<CLASS_TYPE>::m_multipleMax <<
			        "}  subdata=" /*<< etk::displayElem(RegExpNode<CLASS_TYPE>::m_RegExpData)*/);
		};
};
#undef __class__
#define __class__ "etk::RegExpNodeDigitNot"

/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class RegExpNodeDigitNot : public etk::RegExpNode<CLASS_TYPE> {
	public :
		/**
		 * @brief Constructor
		 */
		RegExpNodeDigitNot(void) { };
		/**
		 * @brief Destructor
		 */
		~RegExpNodeDigitNot(void) { };
		virtual bool parse(const CLASS_TYPE& _data, int64_t _currentPos, int64_t _lenMax, int64_t& _findLen) {
			_findLen = 0;
			TK_REG_EXP_DBG_MODE("Parse node : DigitNot{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			bool tmpFind = true;
			uint32_t jjj;
			for (jjj=0; jjj<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind ==true && jjj < _lenMax; jjj++) {
				char32_t tmpVal = _data[_currentPos+jjj];
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
		void display(uint32_t _level) {
			TK_INFO("Find NODE : " << levelSpace(_level) << "@DigitNot@ {" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}  subdata=" /*<< etk::displayElem(RegExpNode<CLASS_TYPE>::m_RegExpData)*/ );
		};
};
#undef __class__
#define __class__ "etk::RegExpNodeLetter"

/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class RegExpNodeLetter : public etk::RegExpNode<CLASS_TYPE> {
	public:
		/**
		 * @brief Constructor
		 */
		RegExpNodeLetter(void) { };
		/**
		 * @brief Destructor
		 */
		~RegExpNodeLetter(void) { };
		virtual bool parse(const CLASS_TYPE& _data, int64_t _currentPos, int64_t _lenMax, int64_t& _findLen) {
			_findLen = 0;
			TK_REG_EXP_DBG_MODE("Parse node : Letter{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			bool tmpFind = true;
			uint32_t jjj;
			for (jjj=0; jjj<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind ==true && jjj < _lenMax; jjj++) {
				char32_t tmpVal = _data[_currentPos+jjj];
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
		void display(uint32_t _level) {
			TK_INFO("Find NODE : " << levelSpace(_level) << "@Letter@ {"
			        << RegExpNode<CLASS_TYPE>::m_multipleMin << ","
			        << RegExpNode<CLASS_TYPE>::m_multipleMax << "}  subdata="
			        /*<< etk::displayElem(RegExpNode<CLASS_TYPE>::m_RegExpData) */);
		};
};
#undef __class__
#define __class__ "etk::RegExpNodeLetterNot"

/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class RegExpNodeLetterNot : public etk::RegExpNode<CLASS_TYPE> {
	public :
		/**
		 * @brief Constructor
		 */
		RegExpNodeLetterNot(void) { };
		/**
		 * @brief Destructor
		 */
		~RegExpNodeLetterNot(void) { };
		virtual bool parse(const CLASS_TYPE& _data, int64_t _currentPos, int64_t _lenMax, int64_t& _findLen) {
			_findLen = 0;
			TK_REG_EXP_DBG_MODE("Parse node : LetterNot{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			bool tmpFind = true;
			uint32_t jjj;
			for (jjj=0; jjj<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind ==true && jjj < _lenMax; jjj++) {
				char32_t tmpVal = _data[_currentPos+jjj];
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
		void display(uint32_t _level) {
			TK_INFO("Find NODE : " << levelSpace(_level) << "@LetterNot@ {"
			        << RegExpNode<CLASS_TYPE>::m_multipleMin << ","
			        << RegExpNode<CLASS_TYPE>::m_multipleMax << "}  subdata="
			        /*<< etk::displayElem(RegExpNode<CLASS_TYPE>::m_RegExpData)*/ );
		};
};
#undef __class__
#define __class__ "etk::RegExpNodeWhiteSpace"

/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class RegExpNodeWhiteSpace : public etk::RegExpNode<CLASS_TYPE> {
	public :
		/**
		 * @brief Constructor
		 */
		RegExpNodeWhiteSpace(void) { };
		/**
		 * @brief Destructor
		 */
		~RegExpNodeWhiteSpace(void) { };
		virtual bool parse(const CLASS_TYPE& _data, int64_t _currentPos, int64_t _lenMax, int64_t& _findLen) {
			_findLen = 0;
			TK_REG_EXP_DBG_MODE("Parse node : Space{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			bool tmpFind = true;
			uint32_t jjj;
			for (jjj=0; jjj<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind ==true && jjj < _lenMax; jjj++) {
				char32_t tmpVal = _data[_currentPos+jjj];
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
		void display(uint32_t _level) {
			TK_INFO("Find NODE : " << levelSpace(_level) << "@Space@ {"
			        << RegExpNode<CLASS_TYPE>::m_multipleMin << ","
			        << RegExpNode<CLASS_TYPE>::m_multipleMax << "}  subdata="
			        /*<< etk::displayElem(RegExpNode<CLASS_TYPE>::m_RegExpData)*/ );
		};
};
#undef __class__
#define __class__ "etk::RegExpNodeWhiteSpaceNot"

/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class RegExpNodeWhiteSpaceNot : public etk::RegExpNode<CLASS_TYPE> {
	public :
		/**
		 * @brief Constructor
		 */
		RegExpNodeWhiteSpaceNot(void) { };
		/**
		 * @brief Destructor
		 */
		~RegExpNodeWhiteSpaceNot(void) { };
		virtual bool parse(const CLASS_TYPE& _data, int64_t _currentPos, int64_t _lenMax, int64_t& _findLen) {
			_findLen = 0;
			TK_REG_EXP_DBG_MODE("Parse node : SpaceNot{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			bool tmpFind = true;
			uint32_t jjj;
			for (jjj=0; jjj<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind ==true && jjj < _lenMax; jjj++) {
				char32_t tmpVal = _data[_currentPos+jjj];
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
		void display(uint32_t _level) {
			TK_INFO("Find NODE : " << levelSpace(_level) << "@SpaceNot@ {"
			        << RegExpNode<CLASS_TYPE>::m_multipleMin << ","
			        << RegExpNode<CLASS_TYPE>::m_multipleMax << "}  subdata="
			        /*<< etk::displayElem(RegExpNode<CLASS_TYPE>::m_RegExpData) */);
		};
};
#undef __class__
#define __class__	"etk::RegExpNodeWordChar"

/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class RegExpNodeWordChar : public etk::RegExpNode<CLASS_TYPE> {
	public :
		/**
		 * @brief Constructor
		 */
		RegExpNodeWordChar(void) { };
		/**
		 * @brief Destructor
		 */
		~RegExpNodeWordChar(void) { };
		virtual bool parse(const CLASS_TYPE& _data, int64_t _currentPos, int64_t _lenMax, int64_t& _findLen) {
			_findLen = 0;
			TK_REG_EXP_DBG_MODE("Parse node : Word{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			bool tmpFind = true;
			uint32_t jjj;
			for (jjj=0; jjj<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind ==true && jjj < _lenMax; jjj++) {
				char32_t tmpVal = _data[_currentPos+jjj];
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
		void display(uint32_t _level) {
			TK_INFO("Find NODE : " << levelSpace(_level) << "@Word@ {"
			        << RegExpNode<CLASS_TYPE>::m_multipleMin << ","
			        << RegExpNode<CLASS_TYPE>::m_multipleMax << "}  subdata="
			        /*<< etk::displayElem(RegExpNode<CLASS_TYPE>::m_RegExpData) */);
		};
};
#undef __class__
#define __class__	"etk::RegExpNodeWordCharNot"
/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class RegExpNodeWordCharNot : public etk::RegExpNode<CLASS_TYPE> {
	public :
		/**
		 * @brief Constructor
		 */
		RegExpNodeWordCharNot(void) { };
		/**
		 * @brief Destructor
		 */
		~RegExpNodeWordCharNot(void) { };
		virtual bool parse(const CLASS_TYPE& _data, int64_t _currentPos, int64_t _lenMax, int64_t& _findLen) {
			_findLen = 0;
			TK_REG_EXP_DBG_MODE("Parse node : WordNot{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			bool tmpFind = true;
			uint32_t jjj;
			for (jjj=0; jjj<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind ==true && jjj < _lenMax; jjj++) {
				char32_t tmpVal = _data[_currentPos+jjj];
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
		void display(uint32_t _level) {
			TK_INFO("Find NODE : " << levelSpace(_level) << "@WordNot@ {"
			        << RegExpNode<CLASS_TYPE>::m_multipleMin << ","
			        << RegExpNode<CLASS_TYPE>::m_multipleMax << "}  subdata="
			        /*<< etk::displayElem(RegExpNode<CLASS_TYPE>::m_RegExpData) */);
		};
};
#undef __class__
#define __class__ "etk::RegExpNodeDot"

/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class RegExpNodeDot : public etk::RegExpNode<CLASS_TYPE> {
	public :
		/**
		 * @brief Constructor
		 */
		RegExpNodeDot(void) { };
		/**
		 * @brief Destructor
		 */
		~RegExpNodeDot(void) { };
		virtual bool parse(const CLASS_TYPE& _data, int64_t _currentPos, int64_t _lenMax, int64_t& _findLen) {
			_findLen = 0;
			TK_REG_EXP_DBG_MODE("Parse node : '.'{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			// equivalent a : [^\x00-\x08\x0A-\x1F\x7F]
			bool tmpFind = true;
			uint32_t jjj;
			for (jjj=0; jjj<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind ==true && jjj < _lenMax; jjj++) {
				char32_t tmpVal = _data[_currentPos+jjj];
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
		void display(uint32_t _level) {
			TK_INFO("Find NODE : " << levelSpace(_level) << "@.@ {"
			<< RegExpNode<CLASS_TYPE>::m_multipleMin << ","
			<< RegExpNode<CLASS_TYPE>::m_multipleMax << "}  subdata="
			/*<< etk::displayElem(RegExpNode<CLASS_TYPE>::m_RegExpData) */);
		};
};

#undef __class__
#define __class__	"etk::RegExpNodeSOL"

/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class RegExpNodeSOL : public etk::RegExpNode<CLASS_TYPE> {
	public :
		/**
		 * @brief Constructor
		 */
		RegExpNodeSOL(void) { };
		/**
		 * @brief Destructor
		 */
		~RegExpNodeSOL(void) { };
		virtual bool parse(const CLASS_TYPE& _data, int64_t _currentPos, int64_t _lenMax, int64_t& _findLen) {
			_findLen = 0;
			// TODO : ...
			TK_INFO("Parse node : SOL{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			return false;
		};
		void display(uint32_t _level) {
			TK_INFO("Find NODE : " << levelSpace(_level) << "@SOL@ {"
			        << RegExpNode<CLASS_TYPE>::m_multipleMin << ","
			        << RegExpNode<CLASS_TYPE>::m_multipleMax << "}  subdata="
			        /*<< etk::displayElem(RegExpNode<CLASS_TYPE>::m_RegExpData) */);
		};
};

#undef __class__
#define __class__ "etk::RegExpNodeEOL"

/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class RegExpNodeEOL : public etk::RegExpNode<CLASS_TYPE> {
	public :
		/**
		 * @brief Constructor
		 */
		RegExpNodeEOL(void) { };
		/**
		 * @brief Destructor
		 */
		~RegExpNodeEOL(void) { };
		virtual bool parse(const CLASS_TYPE& _data, int64_t _currentPos, int64_t _lenMax, int64_t& _findLen) {
			_findLen = 0;
			// TODO : ...
			TK_INFO("Parse node : EOL{" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			return false;
		};
		void display(uint32_t _level) {
			TK_INFO("Find NODE : " << levelSpace(_level) << "@EOL@ {"
			        << RegExpNode<CLASS_TYPE>::m_multipleMin << ","
			        << RegExpNode<CLASS_TYPE>::m_multipleMax << "}  subdata="
			        /*<< etk::displayElem(RegExpNode<CLASS_TYPE>::m_RegExpData) */);
		};
};

class elementPos_ts {
	public:
		int64_t start;
		int64_t stop;
};

#undef __class__
#define __class__	"etk::RegExpNodePTheseElem"

template<class CLASS_TYPE> class RegExpNodePThese;

/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class RegExpNodePTheseElem : public etk::RegExpNode<CLASS_TYPE> {
	protected :
		// SubNodes :
		std::vector<RegExpNode<CLASS_TYPE>*> m_subNode;
	public :
		/**
		 * @brief Constructor
		 */
		RegExpNodePTheseElem(void) { };
		/**
		 * @brief Destructor
		 */
		~RegExpNodePTheseElem(void) { };
		int32_t generate(const std::vector<char32_t>& _data) {
			RegExpNode<CLASS_TYPE>::m_RegExpData = _data;
			TK_REG_EXP_DBG_MODE("Request Parse (elem) data=" /*<< etk::displayElem(RegExpNode<CLASS_TYPE>::m_RegExpData)*/ );
			int64_t pos = 0;
			int64_t elementSize = 0;
			std::vector<char32_t> tmpData;
			while (pos < RegExpNode<CLASS_TYPE>::m_RegExpData.size()) {
				tmpData.clear();
				switch (RegExpNode<CLASS_TYPE>::m_RegExpData[pos]) {
					case regexpOpcodePTheseIn:{
							elementSize=getLenOfPThese(RegExpNode<CLASS_TYPE>::m_RegExpData, pos);
							for (int64_t kkk=pos+1; kkk<pos+elementSize+1; kkk++) {
								tmpData.push_back(RegExpNode<CLASS_TYPE>::m_RegExpData[kkk]);
							}
							RegExpNodePThese<CLASS_TYPE> * myElem = new RegExpNodePThese<CLASS_TYPE>();
							(void)myElem->generate(tmpData);
							// add to the subnode list :
							m_subNode.push_back(myElem);
							// move current position ...
							pos += elementSize+1;
						}
						break;
					case regexpOpcodePTheseOut:
						TK_ERROR("Impossible case :  ')' " << pos);
						return false;
					case regexpOpcodeBracketIn: {
							elementSize=getLenOfBracket(RegExpNode<CLASS_TYPE>::m_RegExpData, pos);
							for (int64_t kkk=pos+1; kkk<pos+elementSize+1; kkk++) {
								tmpData.push_back(RegExpNode<CLASS_TYPE>::m_RegExpData[kkk]);
							}
							RegExpNodeBracket<CLASS_TYPE> * myElem = new RegExpNodeBracket<CLASS_TYPE>();
							(void)myElem->generate(tmpData);
							// add to the subnode list : 
							m_subNode.push_back(myElem);
							// move current position ...
							pos += elementSize+1;
						}
						break;
					case regexpOpcodeBracketOut:
						TK_ERROR("Impossible case :  ']' " << pos);
						return false;
					case regexpOpcodeBracetIn: {
							elementSize=getLenOfBrace(RegExpNode<CLASS_TYPE>::m_RegExpData, pos);
							for (int64_t kkk=pos+1; kkk<pos+elementSize+1; kkk++) {
								tmpData.push_back(RegExpNode<CLASS_TYPE>::m_RegExpData[kkk]);
							}
							uint32_t min = 0;
							uint32_t max = 0;
							if (false == parseBrace(tmpData, min, max)) {
								return false;
							}
							setMultiplicityOnLastNode(min, max);
							pos += elementSize+1;
						}
						break;
					case regexpOpcodeBracetOut:
						TK_ERROR("Impossible case :  '}' " << pos);
						return false;
					case regexpOpcodeTo:
						TK_ERROR("Impossible case :  '-' " << pos);
						return false;
					case regexpOpcodeStar:
						setMultiplicityOnLastNode(0, 0x7FFFFFFF);
						break;
					case regexpOpcodeQuestion:
						setMultiplicityOnLastNode(0, 1);
						break;
					case regexpOpcodePlus:
						setMultiplicityOnLastNode(1, 0x7FFFFFFF);
						break;
					case regexpOpcodePipe:
						TK_ERROR("Impossible case :  '|' " << pos);
						return false;
					case regexpOpcodeDot:
						m_subNode.push_back(new RegExpNodeDot<CLASS_TYPE>());
						break;
					case regexpOpcodeStartOfLine:
						m_subNode.push_back(new RegExpNodeSOL<CLASS_TYPE>());
						break;
					case regexpOpcodeEndOfLine:
						m_subNode.push_back(new RegExpNodeEOL<CLASS_TYPE>());
						break;
					case regexpOpcodeDigit:
						m_subNode.push_back(new RegExpNodeDigit<CLASS_TYPE>());
						break;
					case regexpOpcodeDigitNot:
						m_subNode.push_back(new RegExpNodeDigitNot<CLASS_TYPE>());
						break;
					case regexpOpcodeLetter:
						m_subNode.push_back(new RegExpNodeLetter<CLASS_TYPE>());
						break;
					case regexpOpcodeLetterNot:
						m_subNode.push_back(new RegExpNodeLetterNot<CLASS_TYPE>());
						break;
					case regexpOpcodeSpace:
						m_subNode.push_back(new RegExpNodeWhiteSpace<CLASS_TYPE>());
						break;
					case regexpOpcodeSpaceNot:
						m_subNode.push_back(new RegExpNodeWhiteSpaceNot<CLASS_TYPE>());
						break;
					case regexpOpcodeWord:
						m_subNode.push_back(new RegExpNodeWordChar<CLASS_TYPE>());
						break;
					case regexpOpcodeWordNot:
						m_subNode.push_back(new RegExpNodeWordCharNot<CLASS_TYPE>());
						break;
					
					default: {
							elementSize = getLenOfNormal(RegExpNode<CLASS_TYPE>::m_RegExpData, pos);
							for (int64_t kkk=pos; kkk<pos+elementSize; kkk++) {
								tmpData.push_back(RegExpNode<CLASS_TYPE>::m_RegExpData[kkk]);
							}
							RegExpNodeValue<CLASS_TYPE> * myElem = new RegExpNodeValue<CLASS_TYPE>();
							(void)myElem->generate(tmpData);
							// add to the subnode list : 
							m_subNode.push_back(myElem);
							// move current position ...
							pos += elementSize-1;
						}
						break;
				}
				pos++;
			}
			return _data.size();
		};
		
		virtual bool parse(const CLASS_TYPE& _data, int64_t _currentPos, int64_t _lenMax, int64_t& _findLen) {
			_findLen = 0;
			TK_REG_EXP_DBG_MODE("Parse node : (Elem){" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			// NOTE 1 : Must done only one time in EVERY case ...
			// NOTE 2 : All element inside must be OK
			if (0 == m_subNode.size()) {
				return false;
			}
			int64_t tmpCurrentPos = _currentPos;
			for (int64_t iii=0; iii<m_subNode.size(); iii++) {
				int64_t tmpFindLen;
				if (false == m_subNode[iii]->parse(_data, tmpCurrentPos, _lenMax, tmpFindLen)) {
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
		
		void display(uint32_t _level) {
			TK_INFO("Find NODE : " << levelSpace(_level) << "@(Elem)@ {"
			        << RegExpNode<CLASS_TYPE>::m_multipleMin << ","
			        << RegExpNode<CLASS_TYPE>::m_multipleMax << "}  subdata="
			        /*<< etk::displayElem(RegExpNode<CLASS_TYPE>::m_RegExpData) */);
			for(int64_t iii=0; iii<m_subNode.size(); iii++) {
				m_subNode[iii]->display(_level+1);
			}
		};
	private :
		/**
		 * @brief Set the number of repeate time on a the last node in the list ...
		 * @param[in] _min Minimum of the multiplicity
		 * @param[in] _max Maximum of the multiplicity
		 * @return true if we find the node, false otherwise
		 */
		bool setMultiplicityOnLastNode(uint32_t _min, uint32_t _max) {
			if (0==m_subNode.size()) {
				TK_ERROR("Set multiplicity on an inexistant element ....");
				return false;
			}
			RegExpNode<CLASS_TYPE> * myNode = m_subNode[m_subNode.size()-1];
			if (NULL==myNode) {
				TK_ERROR("INTERNAL error ==> node not generated");
				return false;
			}
			myNode->setMult(_min, _max);
			return true;
		}
};

#undef __class__
#define __class__ "etk::RegExpNodePThese"

/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class RegExpNodePThese : public etk::RegExpNode<CLASS_TYPE> {
	protected :
		std::vector<RegExpNode<CLASS_TYPE>*> m_subNode; //!< Subnode list 
	public :
		/**
		 * @brief Constructor
		 */
		RegExpNodePThese(void) { };
		/**
		 * @brief Destructor
		 */
		~RegExpNodePThese(void) { }
		int32_t generate(const std::vector<char32_t>& _data) {
			RegExpNode<CLASS_TYPE>::m_RegExpData = _data;
			TK_REG_EXP_DBG_MODE("Request Parse (...) data=" /*<< etk::displayElem(RegExpNode<CLASS_TYPE>::m_RegExpData)*/ );
			//Find all the '|' in the string (and at the good level ...) 
			int64_t pos = 0;
			int32_t elementSize = getLenOfPTheseElem(RegExpNode<CLASS_TYPE>::m_RegExpData, pos);
			// generate all the "elemTypePTheseElem" of the Node
			while (elementSize>0) {
				// geerate output deta ...
				std::vector<char32_t> tmpData;
				for (int64_t kkk=pos; kkk<pos+elementSize; kkk++) {
					tmpData.push_back(RegExpNode<CLASS_TYPE>::m_RegExpData[kkk]);
				}
				RegExpNodePTheseElem<CLASS_TYPE> * myElem = new RegExpNodePTheseElem<CLASS_TYPE>();
				(void)myElem->generate(tmpData);
				// add to the subnode list : 
				m_subNode.push_back(myElem);
				pos += elementSize+1;
				TK_REG_EXP_DBG_MODE("plop=" /*<< etk::displayElem(RegExpNode<CLASS_TYPE>::m_RegExpData, pos, pos+1)*/ );
				elementSize = getLenOfPTheseElem(RegExpNode<CLASS_TYPE>::m_RegExpData, pos);
				TK_REG_EXP_DBG_MODE("find " << elementSize << " elements");
			}
			if (    pos == 0
			     && elementSize == 0) {
				TK_ERROR("No data in the (...) element at " << pos);
				return false;
			}
			return _data.size();
		};
		virtual bool parse(const CLASS_TYPE& _data, int64_t _currentPos, int64_t _lenMax, int64_t& _findLen) {
			_findLen = 0;
			TK_REG_EXP_DBG_MODE("Parse node : (...){" << RegExpNode<CLASS_TYPE>::m_multipleMin << "," << RegExpNode<CLASS_TYPE>::m_multipleMax << "}");
			if (0 == m_subNode.size()) {
				return false;
			}
			bool tmpFind = true;
			int64_t jjj =0;
			for (jjj=0; jjj<RegExpNode<CLASS_TYPE>::m_multipleMax && tmpFind == true ; jjj++) {
				tmpFind = false;
				for (int64_t iii=0; iii<m_subNode.size(); iii++) {
					int64_t tmpFindLen;
					if (true == m_subNode[iii]->parse(_data, _currentPos+_findLen, _lenMax, tmpFindLen)) {
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
		
		void display(uint32_t _level) {
			if (-1 == _level) {
				TK_INFO("regExp :" /*<< etk::displayElem(RegExpNode<CLASS_TYPE>::m_RegExpData) */);
			} else {
				TK_INFO("Find NODE : " << levelSpace(_level) << "@(...)@ {"
				        << RegExpNode<CLASS_TYPE>::m_multipleMin << ","
				        << RegExpNode<CLASS_TYPE>::m_multipleMax << "}  subdata="
				        /*<< etk::displayElem(RegExpNode<CLASS_TYPE>::m_RegExpData) */);
				for(int32_t i=0; i<m_subNode.size(); i++) {
					m_subNode[i]->display(_level+1);
				}
			}
		};
		/**
		 * @brief Just display the regExp in color ...
		 */
		void drawColoredRegEx(void) {
			TK_INFO("regExp :" /*<< etk::displayElem(RegExpNode<CLASS_TYPE>::m_RegExpData)*/ );
		}
};
#undef __class__
#define __class__	"etk::RegExp"

/**
 * @brief Regular expression interface template.
 * 
 * List of elment that can be displayed :
 * 
 * [pre]
 *     (...)                 sub element is separate with |
 *     \d                    Digits                         [0-9]
 *     \D                    NOT a digit                    [^0-9]
 *     \l                    Letters                        [a-zA-Z]
 *     \L                    NOT a Letter                   [^a-zA-Z]
 *     \s                    Whitespace                     [ \t\n\r\f\v]
 *     \S                    NOT Whitespace                 [^ \t\n\r\f\v]
 *     \w                    "Word" character               [a-zA-Z0-9_]
 *     \W                    NOT a "Word" character         [^a-zA-Z0-9_]
 *     \@                    at the start or the end        not in the parsing of element ==> check if \w is not present   (other regExp will be <> ...)
 *     [anjdi] or [a-gt-j]   range
 *     .                     dot                            [^\x00-\x08\x0A-\x1F\x7F]
 * ==> TODO :
 *     $                     End / Start of line of line    ==> ce sera un truc suplé comme le \@
 *     ^in the []            invertion of the range element
 * 
 * multiplicity :
 *     *     ==> {0, 2147483647}
 *     ?     ==> {0, 1}
 *     +     ==> {1, 2147483647}
 *     {x}   ==> {x, x}
 *     {x,y} ==> {x, y}
 * [/pre]
 * 
 * @param[in] CLASS_TYPE Type of theclass that might be parsed. This class might have a interface : operator[] that return a char or a char32_t.
 * 
 * Regular is easy to use:
 */
template<class CLASS_TYPE> class RegExp {
	private:
		std::u32string m_expressionRequested; //!< Regular expression parsed ...
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
		RegExp(const std::u32string &_exp=U"") :
		  m_expressionRequested(U""),
		  m_isOk(false),
		  m_notBeginWithChar(false),
		  m_notEndWithChar(false) {
			m_areaFind.start=0;
			m_areaFind.stop=0;
			if (_exp.size() != 0) {
				compile(_exp);
			}
		}
		/**
		 * @previous
		 */
		RegExp(const std::string &_exp) :
		  m_expressionRequested(U""),
		  m_isOk(false),
		  m_notBeginWithChar(false),
		  m_notEndWithChar(false) {
			m_areaFind.start=0;
			m_areaFind.stop=0;
			if (_exp.size() != 0) {
				compile(std::to_u32string(_exp));
			}
		};
		
		/**
		 * @brief Destructor
		 */
		~RegExp(void) {
			m_isOk = false;
		};
		
		/**
		 * @brief Set a new regular expression matching
		 * @param[in] _exp the new expression to search
		 */
		void compile(const std::string &_exp) {
			if (_exp.size() != 0) {
				TK_REG_EXP_DBG_MODE("normal string parse : '" << _exp << "'");
				compile(std::to_u32string(_exp));
			}
		}
		/**
		 * @previous
		 */
		void compile(const std::u32string &_regexp) {
			m_expressionRequested = _regexp;
			std::vector<char32_t> tmpExp;
			
			TK_REG_EXP_DBG_MODE("---------------------------------------------------------------------");
			TK_REG_EXP_DBG_MODE("Parse RegExp : (" << m_expressionRequested << ")" );
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
			for (int64_t iii=0; iii<_regexp.size(); iii++) {
				if (_regexp[iii] == '\\') {
					if(iii+1>=_regexp.size()) {
						TK_ERROR("Dangerous parse of the element pos " << iii << " \\ with nothing after");
						// TODO : Generate Exeption ...
						return;
					}
					int64_t jjj;
					// Find the element in the list...
					for (jjj=0; jjj<constConvertionTableSize; jjj++) {
						if(		true == constConvertionTable[jjj].haveBackSlash 
							&&	_regexp[iii+1] == constConvertionTable[jjj].inputValue)
						{
							if (constConvertionTable[jjj].newValue==0) {
								tmpExp.push_back(constConvertionTable[jjj].specialChar);
							} else {
								tmpExp.push_back(constConvertionTable[jjj].newValue);
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
					int64_t jjj;
					// find the element in the list...
					for (jjj=0; jjj<constConvertionTableSize; jjj++) {
						if(		false == constConvertionTable[jjj].haveBackSlash 
							&&	_regexp[iii] == constConvertionTable[jjj].inputValue)
						{
							if (constConvertionTable[jjj].newValue==0) {
								tmpExp.push_back(constConvertionTable[jjj].specialChar);
							} else {
								tmpExp.push_back(constConvertionTable[jjj].newValue);
							}
							break;
						}
					}
					// not find : normal element
					if (jjj==constConvertionTableSize) {
						//TK_REG_EXP_DBG_MODE("parse : '" << _regexp[iii] << "'" );
						tmpExp.push_back(_regexp[iii]);
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
			if (false == checkGoodPosition(tmpExp) ) {
				return;
			}
			
			//TK_REG_EXP_DBG_MODE("Main element :" /*<< etk::displayElem(tmpExp)*/ );
			if (    tmpExp.size()>0
			     && tmpExp[0] == regexpOpcodeNoChar)
			{
				//TK_DEBUG("=> must not begin with char");
				m_notBeginWithChar = true;
				// remove element
				tmpExp.erase(tmpExp.begin());
			}
			if (    tmpExp.size()>0
			     && tmpExp[tmpExp.size()-1] == regexpOpcodeNoChar)
			{
				//TK_DEBUG("=> must not end with char");
				m_notEndWithChar = true;
				// remove element
				tmpExp.erase(tmpExp.end()-1);
			}
			
			if (tmpExp.size() != m_exprRootNode.generate(tmpExp) ) {
				return;
			}
			// TODO : optimize node here ...
			//drawColoredRegEx();
			//display();
		
			// all OK ... play again 
			m_isOk = true;
		};
		
		/**
		 * @brief Get the regular expression string
		 * @return the string representing the RegExp
		 */
		std::string getRegExp(void) const {
			return std::to_string(m_expressionRequested);
		};
		/**
		 * @previous
		 */
		const std::u32string& getURegExp(void) const {
			return m_expressionRequested;
		};
		
		/**
		 * @brief Get the status if the regular expression parsing
		 * @return true : the regExp is correctly parsed
		 * @return false : an error occcured (check log ...)
		 */
		bool getStatus(void) {
			return m_isOk;
		};
		// process the regular expression
		
		/**
		 * @brief Parse the defined data with the compiled regular expression.
		 * @param[in] _SearchIn Data where to search the regular expression.
		 * @param[in] _startPos start position to search
		 * @param[in] _endPos end position to search
		 * @param[in] _escapeChar special char that remove other char real type
		 * @return true : find something, false otherwise
		 */
		bool parse(const CLASS_TYPE& _SearchIn,
		           int64_t _startPos,
		           int64_t _endPos,
		           char32_t _escapeChar=0) {
			if (false == m_isOk) {
				return false;
			}
			int64_t buflen = _SearchIn.size();
			if (_endPos > buflen) {
				_endPos = buflen;
			}
			if (_startPos > _endPos) {
				return false;
			}
			for (int64_t iii=_startPos; iii<_endPos; iii++) {
				int64_t findLen=0;
				int64_t maxlen = _endPos-iii;
				if (true == m_notBeginWithChar) {
					if (iii>0) {
						char32_t tmpVal = _SearchIn[iii-1];
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
				if (true == m_exprRootNode.parse(_SearchIn, iii, maxlen, findLen)) {
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
						if (iii+findLen < _SearchIn.size() ) {
							char32_t tmpVal = _SearchIn[iii+findLen];
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
		
		bool processOneElement(const CLASS_TYPE& _SearchIn,
		                       int64_t _startPos,
		                       int64_t _endPos,
		                       char32_t _escapeChar=0) {
			if (false == m_isOk) {
				return false;
			}
			int64_t buflen = _SearchIn.size();
			if (_endPos > buflen) {
				_endPos = buflen;
			}
			if (_startPos > _endPos) {
				return false;
			}
			int64_t findLen=0;
			int64_t maxlen = _endPos-_startPos;
			if (true == m_notBeginWithChar) {
				if (_startPos>0) {
					char32_t tmpVal = _SearchIn[_startPos-1];
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
			if (true == m_exprRootNode.parse(_SearchIn, _startPos, maxlen, findLen)) {
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
					if (_startPos+findLen < _SearchIn.size() ) {
						char32_t tmpVal = _SearchIn[_startPos+findLen];
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
		int64_t	start(void) {
			return m_areaFind.start;
		};
		
		/**
		 * @brief Get the expression stop position detected
		 * @return position of the stop regExp
		 */
		int64_t	stop(void) {
			return m_areaFind.stop;
		};
		
		/**
		 * @brief Display the reg Exp
		 */
		void display(void) {
			m_exprRootNode.display(0);
		};
		/**
		 * @brief Just display the regExp in color ...
		 */
		void drawColoredRegEx(void) {
			m_exprRootNode.drawColoredRegEx();
		}
		/**
		 * @brief Get decorated regular expression. This generate a [class[ewol::compositing::Text]] decoration text. Note that can be use in [class[ewol::widget::Label]].
		 * @return The decorated string
		 */
		std::string getRegExDecorated(void) {
			// TODO : do it...
			return "";
		}
	private:
		/**
		 * @brief Check forbidden element in a regular expression element.
		 * @param[in] _tmpExp The regular expression to check.
		 * @param[in] _pos Position to start the check.
		 * @return true The current node is correct.
		 * @return false An error in parsing has appeared.
		 */
		bool checkGoodPosition(const std::vector<char32_t>& _tmpExp, int64_t& _pos) {
			char32_t curentCode = _tmpExp[_pos];
			char32_t endCode = regexpOpcodePTheseOut;
			const char *input = "(...)";
			if (curentCode == regexpOpcodeBracketIn) {
				endCode = regexpOpcodeBracketOut;
				input = "[...]";
			} else if (curentCode == regexpOpcodeBracetIn){
				endCode = regexpOpcodeBracetOut;
				input = "{x,x}";
			}
			_pos++;
			if (_pos >= _tmpExp.size()) {
				TK_ERROR("ended with: ( or { or [ ... not permited");
				return false;
			}
			//TK_DEBUG(" ==> Find ELEMENT : ([{");
			// case dependent : 
			if (    curentCode == regexpOpcodeBracketIn
			     || curentCode == regexpOpcodeBracetIn) {
				while(_pos<_tmpExp.size()) {
					//TK_DEBUG("check : " << tmpExp[pos]);
					// if we find the end : 
					if (endCode == _tmpExp[_pos]) {
						return true;
					} else {
						// otherwise, we check the error in the element ...
						char *find = NULL;
						switch (_tmpExp[_pos]) {
							case regexpOpcodePTheseIn:		find = (char*)"(";			break;
							case regexpOpcodeBracketIn:		find = (char*)"[";			break;
							case regexpOpcodeBracetIn:		find = (char*)"{";			break;
							case regexpOpcodePTheseOut:		find = (char*)")";			break;
							case regexpOpcodeBracketOut:		find = (char*)"]";			break;
							case regexpOpcodeBracetOut:		find = (char*)"}";			break;
							case regexpOpcodeStar:			find = (char*)"*";			break;
							case regexpOpcodeDot:				find = (char*)".";			break;
							case regexpOpcodeQuestion:		find = (char*)"?";			break;
							case regexpOpcodePlus:			find = (char*)"+";			break;
							case regexpOpcodePipe:			find = (char*)"|";			break;
							case regexpOpcodeStartOfLine:	find = (char*)"^";			break;
							case regexpOpcodeEndOfLine:		find = (char*)"$";			break;
							case regexpOpcodeDigit:			find = (char*)"\\d";		break;
							case regexpOpcodeDigitNot:		find = (char*)"\\D";		break;
							case regexpOpcodeLetter:			find = (char*)"\\l";		break;
							case regexpOpcodeLetterNot:		find = (char*)"\\L";		break;
							case regexpOpcodeSpace:			find = (char*)"\\s";		break;
							case regexpOpcodeSpaceNot:		find = (char*)"\\S";		break;
							case regexpOpcodeWord:			find = (char*)"\\w";		break;
							case regexpOpcodeWordNot:		find = (char*)"\\W";		break;
							case regexpOpcodeNoChar:			find = (char*)"\\@";		break;
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
				while(_pos< _tmpExp.size()) {
					if (endCode == _tmpExp[_pos]) {
						// find the last element
						return true;
					} else if (	_tmpExp[_pos] == regexpOpcodeBracetOut) {
						TK_ERROR("find } inside a (...) without start {");
						return false;
					} else if (	_tmpExp[_pos] == regexpOpcodeBracketOut) {
						TK_ERROR("find ] inside a (...) without start [");
						return false;
					} else {
						if(    _tmpExp[_pos] == regexpOpcodePTheseIn
						    || _tmpExp[_pos] == regexpOpcodeBracketIn
						    || _tmpExp[_pos] == regexpOpcodeBracetIn ) {
							if (false==checkGoodPosition(_tmpExp, _pos) ) {
								return false;
							}
						}
					}
					_pos++;
				}
			}
			
			// we did not find the cloder . ...
			if (endCode == regexpOpcodeBracketOut) {
				TK_ERROR("Missing ']' at the end");
			}
			if (endCode == regexpOpcodeBracetOut) {
				TK_ERROR("Missing '}' at the end");
			}
			if (endCode == regexpOpcodePTheseOut) {
				TK_ERROR("Missing ')' at the end");
			}
			return false;
		};
		
		/**
		 * @brief Check all the element in a regular expression ( count [],{},(),...)
		 * @param[in] _tmpExp Regular expression to check.
		 * @return true The regular expression is correct.
		 * @return false an error occured in the regular expression.
		 */
		bool checkGoodPosition(const std::vector<char32_t>& _tmpExp) {
			int64_t pos = 0;
			while (pos < _tmpExp.size()) {
				//TK_DEBUG("check : " << tmpExp[pos]);
				if(    _tmpExp[pos] == regexpOpcodePTheseIn
				    || _tmpExp[pos] == regexpOpcodeBracketIn
				    || _tmpExp[pos] == regexpOpcodeBracetIn)
				{
					// attention the i position change inside the finction...
					if (false==checkGoodPosition(_tmpExp, pos) ) {
						TK_ERROR("Error at position : " << pos+1 );
						return false;
					} else {
						//TK_DEBUG(" <== Find ELEMENT : ]})");
					}
				} else if(_tmpExp[pos] == regexpOpcodePTheseOut) {
					TK_ERROR("can find ')' with no start : ')'");
					return false;
				} else if(_tmpExp[pos] == regexpOpcodeBracketOut) {
					TK_ERROR("can find ']' with no start : '['");
					return false;
				} else if(_tmpExp[pos] == regexpOpcodeBracetOut) {
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
#define __class__ (NULL)

#endif
