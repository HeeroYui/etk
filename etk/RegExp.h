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
#include <memory>

//#define TK_REG_EXP_DBG_MODE TK_VERBOSE
#define TK_REG_EXP_DBG_MODE TK_DEBUG

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
	$					End / Start of line of line 			==> ce sera un truc suplémentaire comme le \@
==> TODO :
	^in the []			invertion of the range element
	Sart of line
	force regexp to be the shortest.

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
namespace regexp {
enum parseStatus {
	parseStatusUnknow, //!< No status set
	parseStatusNone, //!< parse have no data
	parseStatusPartial, //!< parse is done partially, and can have more data
	parseStatusFull //!< can not parse more elements
};
//! @not-in-doc
extern const struct convertionTable constConvertionTable[];
//! @not-in-doc
extern const int64_t constConvertionTableSize;
//! @not-in-doc
std::string createString(const std::vector<char32_t>& _data, int64_t _start=0, int64_t _stop=0x7FFFFFFF);
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
#define __class__ "regExp::FindProperty"

/**
 * @brief Node Elements for every-one
 * @not-in-doc
 */
class FindProperty {
	public:
		int64_t m_positionStart; //!< find start position
		int64_t m_positionStop; //!< find end position
		uint32_t m_multiplicity; //!< curent multiplicity of find element
		std::vector<FindProperty> m_subProperty; //!< list of all sub elements
		enum parseStatus status; //!< curent status of parsing
	public:
		FindProperty() :
		  m_positionStart(-1),
		  m_positionStop(-1),
		  m_multiplicity(0),
		  status(parseStatusUnknow) {
			// nothing to do ...
		}
		int64_t getPositionStart() {
			return m_positionStart;
		}
		void setPositionStart(int64_t _newPos) {
			m_positionStart = _newPos;
		}
		int64_t getPositionStop() {
			return m_positionStop;
		}
		void setPositionStop(int64_t _newPos) {
			m_positionStop = _newPos;
		}
		uint32_t getMultiplicity() {
			return m_multiplicity;
		}
		void setMultiplicity(uint32_t _newVal) {
			m_multiplicity = _newVal;
		}
		void multiplicityDecrement() {
			m_multiplicity--;
		}
		void multiplicityIncrement() {
			m_multiplicity++;
		}
		int64_t getFindLen() {
			if (m_positionStop < 0) {
				return 0;
			}
			return m_positionStop - m_positionStart;
		}
		void display(const std::string& _data, int32_t _level = 0) {
			TK_INFO("prop : " << levelSpace(_level) << " ["
			        << m_positionStart << ","
			        << m_positionStop << "] mul="
			        << m_multiplicity << " data='"
			        << std::string(_data, m_positionStart, m_positionStop-m_positionStart) << "'");
			for (auto &it : m_subProperty) {
				it.display(_data, _level++);
			}
		}
		void display(int32_t _level = 0) {
			TK_INFO("prop : " << levelSpace(_level) << " ["
			        << m_positionStart << ","
			        << m_positionStop << "] mul="
			        << m_multiplicity);
			for (auto &it : m_subProperty) {
				it.display(_level++);
			}
		}
};

#undef __class__
#define __class__ "regExp::Node"

/**
 * @brief Node Elements for every-one
 * @not-in-doc
 */
template<class CLASS_TYPE> class Node {
	protected :
		// Data Section ... (can have no data...)
		std::vector<char32_t> m_regExpData; //!< data to parse and compare in some case ...
		int32_t m_nodeLevel;
	public :
		/**
		 * @brief Constructor
		 */
		Node(int32_t _level) :
		  m_regExpData(),
		  m_nodeLevel(_level),
		  m_multipleMin(1),
		  m_multipleMax(1) {
			
		};
		/**
		 * @brief Destructor
		 */
		virtual ~Node() { };
		/**
		 * @brief Generate the regular expression with the current "converted string"
		 * @param[in] _data Property of the regexp
		 * @param[in] _level Node level in the tree
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
		 * @return Full Find something (can not find more...)
		 * @return Partial can find more data ...
		 * @return None Find nothing
		 */
		virtual enum parseStatus parse(const CLASS_TYPE& _data, int64_t _currentPos, int64_t _lenMax, FindProperty& _property)=0;
		/**
		 * @brief Display the current node properties
		 * @param[in] level of the node
		 */
		virtual void display() {
			TK_INFO("Find NODE : " << levelSpace(m_nodeLevel) << "@???@ {" << getMultMin() << "," << getMultMax() << "}  subdata=" << createString(m_regExpData) );
		};
	protected :
		uint32_t m_multipleMin; //!< minimum repetition (included)
		uint32_t m_multipleMax; //!< maximum repetition (included)
	public:
		/**
		 * @brief Set the multiplicity of this Node.
		 * @param[in] _min The minimum appear time.
		 * @param[in] _max The maximum appear time.
		 */
		void setMult(uint32_t _min, uint32_t _max) {
			m_multipleMin = std::max(_min, (uint32_t)0);
			m_multipleMax = std::max(_max, (uint32_t)1);
		}
	protected:
		/**
		 * @brief Get the minimum multiplicity.
		 * @return The minimum appear availlable.
		 */
		uint32_t getMultMin() const {
			return m_multipleMin;
		};
		/**
		 * @brief Get the maximum multiplicity.
		 * @return The maximum appear availlable.
		 */
		uint32_t getMultMax() const {
			return m_multipleMax;
		};
};

#undef __class__
#define __class__ "regExp::NodeValue"

template<class CLASS_TYPE> class NodeValue : public Node<CLASS_TYPE> {
	protected :
		// SubNodes :
		std::vector<char32_t> m_data;
	public :
		
		/**
		 * @brief Constructor
		 */
		NodeValue(int32_t _level) : Node<CLASS_TYPE>::Node(_level) { };
		NodeValue(const std::vector<char32_t>& _data, int32_t _level) : Node<CLASS_TYPE>::Node(_level) {
			generate(_data);
		};
		
		int32_t generate(const std::vector<char32_t>& _data) {
			Node<CLASS_TYPE>::m_regExpData = _data;
			TK_REG_EXP_DBG_MODE("Request Parse \"Value\" data=" << createString(Node<CLASS_TYPE>::m_regExpData) );
			m_data.clear();
			for (int32_t i=0; i<(int64_t)Node<CLASS_TYPE>::m_regExpData.size(); i++) {
				m_data.push_back(Node<CLASS_TYPE>::m_regExpData[i]);
			}
			return _data.size();
		};
		virtual enum parseStatus parse(const CLASS_TYPE& _data, int64_t _currentPos, int64_t _lenMax, FindProperty& _property) {
			TK_REG_EXP_DBG_MODE("Parse " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " Value{" << Node<CLASS_TYPE>::m_multipleMin << "," << Node<CLASS_TYPE>::m_multipleMax << "} : " << (char)m_data[0]);
			if (m_data.size() == 0) {
				TK_ERROR("No data inside type elemTypeValue");
				return parseStatusNone;
			}
			bool tmpFind = true;
			int32_t findLen = 0;
			while(    _property.getMultiplicity() < Node<CLASS_TYPE>::m_multipleMax
			       && tmpFind == true) {
				uint32_t ofset = 0;
				int64_t kkk;
				for (kkk=0; findLen+kkk<_lenMax && kkk < (int64_t)m_data.size(); kkk++) {
					TK_REG_EXP_DBG_MODE("     " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << "      check element value : '" << (char)m_data[kkk] << "' ?= '" << (char)_data[_currentPos+findLen+kkk] << "'");
					if (m_data[kkk] != (char32_t)_data[_currentPos+findLen+kkk]) {
						tmpFind=false;
						break;
					}
					ofset++;
				}
				if (kkk != (int64_t)m_data.size()) {
					// parsing not ended ...
					tmpFind = false;
				}
				// Update local ofset of data
				if (tmpFind == true) {
					findLen += ofset;
				}
				_property.multiplicityIncrement();
			}
			_property.setPositionStop(_property.getPositionStart() + findLen);
			if (    _property.getMultiplicity() >= Node<CLASS_TYPE>::m_multipleMin
			     && _property.getMultiplicity() <= Node<CLASS_TYPE>::m_multipleMax
			     && findLen > 0) {
				TK_REG_EXP_DBG_MODE("     " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << "      value find " << _property.getPositionStop() - _property.getPositionStart() << " [" << _property.getPositionStart() << ".." << _property.getPositionStop() << "]");
				return parseStatusFull;
			} else if (Node<CLASS_TYPE>::m_multipleMin == 0) {
				TK_REG_EXP_DBG_MODE("     " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << "      find size=0");
				return parseStatusFull;
			}
			return parseStatusNone;
		};
		
		void display() {
			TK_INFO("Find NODE : " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << "@Value@ {"
			        << Node<CLASS_TYPE>::m_multipleMin << ","
			        << Node<CLASS_TYPE>::m_multipleMax << "} subdata="
			        << createString(Node<CLASS_TYPE>::m_regExpData)
			        << " data: " << createString(m_data) );
		};
};
#undef __class__
#define __class__ "regExp::NodeRangeValue"

/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class NodeRangeValue : public Node<CLASS_TYPE> {
	private:
		std::vector<std::pair<char32_t, char32_t>> m_rangeList;
		std::vector<char32_t> m_dataList;
		bool m_invert;
	public :
		/**
		 * @brief Constructor
		 */
		NodeRangeValue(int32_t _level) : Node<CLASS_TYPE>::Node(_level), m_invert(false) { };
		/**
		 * @brief Destructor
		 */
		virtual ~NodeRangeValue() { };
		void addRange(char32_t _start, char32_t _stop) {
			m_rangeList.push_back(std::make_pair(_start, _stop));
		}
		void addValue(char32_t _value) {
			m_dataList.push_back(_value);
		}
		void setInvertion(bool _newVal) {
			m_invert = _newVal;
		}
		virtual const char* getDescriptiveName() const {
			return "auto-range";
		}
		// Truc a faire : multipliciter min, return partiel, et ...
		virtual enum parseStatus parse(const CLASS_TYPE& _data, int64_t _currentPos, int64_t _lenMax, FindProperty& _property) {
			int32_t findLen = 0;
			TK_REG_EXP_DBG_MODE("Parse " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " " << getDescriptiveName() << "{" << Node<CLASS_TYPE>::m_multipleMin << "," << Node<CLASS_TYPE>::m_multipleMax << "}");
			char32_t tmpVal = _data[_currentPos];
			bool find = false;
			// Check range
			for (auto &it : m_rangeList) {
				if (    tmpVal >= it.first
				     && tmpVal <= it.second) {
					find = true;
					break;
				}
			}
			// Check Value
			if (find == false) {
				for (auto &it : m_dataList) {
					if (tmpVal == it) {
						find = true;
						break;
					}
				}
			}
			// check inverse request:
			if (    (    find == true
			          && m_invert == false)
			     || (    find == false
			          && m_invert == true) ) {
				find = true;
			} else {
				find = false;
			}
			if (find == true) {
				_property.multiplicityIncrement();
				int64_t newPosVal = _property.getPositionStop();
				if (newPosVal == -1) {
					newPosVal = _property.getPositionStart() + 1;
				} else {
					newPosVal++;
				}
				if(_property.getMultiplicity() > Node<CLASS_TYPE>::m_multipleMax) {
					_property.multiplicityDecrement();
					return parseStatusFull;
				} else {
					_property.setPositionStop(newPosVal);
					if (_currentPos>=_lenMax) {
						return parseStatusFull;
					} else {
						return parseStatusPartial;
					}
				}
			}
			if (_property.getPositionStop() != -1) {
				return parseStatusFull;
			}
			return parseStatusNone;
		};
		virtual void display() {
			TK_INFO("Find NODE : " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " " << getDescriptiveName() << " {"
			        << Node<CLASS_TYPE>::m_multipleMin << ","
			        << Node<CLASS_TYPE>::m_multipleMax <<
			        "}  subdata=" << createString(Node<CLASS_TYPE>::m_regExpData));
		};
};

#undef __class__
#define __class__ "regExp::NodeBracket"

/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class NodeBracket : public NodeRangeValue<CLASS_TYPE> {
	public:
		/**
		 * @brief Constructor
		 */
		NodeBracket(int32_t _level) : NodeRangeValue<CLASS_TYPE>::NodeRangeValue(_level) {
			
		};
		NodeBracket(const std::vector<char32_t>& _data, int32_t _level) : NodeRangeValue<CLASS_TYPE>::NodeRangeValue(_level)  {
			generate(_data);
		};
		virtual const char* getDescriptiveName() const {
			return "[...]";
		}
		int32_t generate(const std::vector<char32_t>& _data) {
			Node<CLASS_TYPE>::m_regExpData = _data;
			TK_REG_EXP_DBG_MODE("Request Parse [...] data=" << createString(Node<CLASS_TYPE>::m_regExpData) );
			
			char32_t lastElement = 0;
			bool multipleElement = false;
			//
			for (int32_t kkk=0; kkk<(int64_t)Node<CLASS_TYPE>::m_regExpData.size(); kkk++) {
				if (    Node<CLASS_TYPE>::m_regExpData[kkk] == regexpOpcodeTo
				     && multipleElement == true) {
					TK_ERROR("Can not have 2 consecutive - in [...]");
					return 0;
				} else if (multipleElement == true) {
					NodeRangeValue<CLASS_TYPE>::addRange(lastElement, Node<CLASS_TYPE>::m_regExpData[kkk]);
					multipleElement = false;
					lastElement = 0;
				} else if(Node<CLASS_TYPE>::m_regExpData[kkk] == regexpOpcodeTo) {
					multipleElement = true;
				} else {
					if (lastElement != 0) {
						NodeRangeValue<CLASS_TYPE>::addValue(lastElement);
					}
					lastElement = Node<CLASS_TYPE>::m_regExpData[kkk];
				}
			}
			if (lastElement != 0) {
				NodeRangeValue<CLASS_TYPE>::addValue(lastElement);
			}
			return _data.size();
		};
};
#undef __class__
#define __class__ "RegExp::NodeDigit"

/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class NodeDigit : public NodeRangeValue<CLASS_TYPE> {
	public :
		/**
		 * @brief Constructor
		 */
		NodeDigit(int32_t _level) : NodeRangeValue<CLASS_TYPE>::NodeRangeValue(_level) {
			NodeRangeValue<CLASS_TYPE>::addRange('0', '9');
		};
		virtual const char* getDescriptiveName() const {
			return "Digit";
		}
};
#undef __class__
#define __class__ "regExp::NodeDigitNot"

/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class NodeDigitNot : public NodeRangeValue<CLASS_TYPE> {
	public :
		/**
		 * @brief Constructor
		 */
		NodeDigitNot(int32_t _level) : NodeRangeValue<CLASS_TYPE>::NodeRangeValue(_level) {
			NodeRangeValue<CLASS_TYPE>::addRange('0', '9');
			NodeRangeValue<CLASS_TYPE>::setInvertion(true);
		};
		virtual const char* getDescriptiveName() const {
			return "DigitNot";
		}
};
#undef __class__
#define __class__ "regExp::NodeLetter"

/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class NodeLetter : public NodeRangeValue<CLASS_TYPE> {
	public:
		/**
		 * @brief Constructor
		 */
		NodeLetter(int32_t _level) : NodeRangeValue<CLASS_TYPE>::NodeRangeValue(_level) {
			NodeRangeValue<CLASS_TYPE>::addRange('a', 'z');
			NodeRangeValue<CLASS_TYPE>::addRange('A', 'Z');
		};
		virtual const char* getDescriptiveName() const {
			return "Letter";
		}
};
#undef __class__
#define __class__ "regExp::NodeLetterNot"

/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class NodeLetterNot : public NodeRangeValue<CLASS_TYPE> {
	public :
		/**
		 * @brief Constructor
		 */
		NodeLetterNot(int32_t _level) : NodeRangeValue<CLASS_TYPE>::NodeRangeValue(_level) {
			NodeRangeValue<CLASS_TYPE>::addRange('a', 'z');
			NodeRangeValue<CLASS_TYPE>::addRange('A', 'Z');
			NodeRangeValue<CLASS_TYPE>::setInvertion(true);
		};
		virtual const char* getDescriptiveName() const {
			return "LetterNot";
		}
};
#undef __class__
#define __class__ "regExp::NodeWhiteSpace"

/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class NodeWhiteSpace : public NodeRangeValue<CLASS_TYPE> {
	public :
		/**
		 * @brief Constructor
		 */
		NodeWhiteSpace(int32_t _level) : NodeRangeValue<CLASS_TYPE>::NodeRangeValue(_level) {
			NodeRangeValue<CLASS_TYPE>::addValue(' ');
			NodeRangeValue<CLASS_TYPE>::addValue('\t');
			NodeRangeValue<CLASS_TYPE>::addValue('\n');
			NodeRangeValue<CLASS_TYPE>::addValue('\r');
			NodeRangeValue<CLASS_TYPE>::addValue('\f');
			NodeRangeValue<CLASS_TYPE>::addValue('\v');
		};
		virtual const char* getDescriptiveName() const {
			return "Space";
		}
};
#undef __class__
#define __class__ "regExp::NodeWhiteSpaceNot"

/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class NodeWhiteSpaceNot : public NodeRangeValue<CLASS_TYPE> {
	public :
		/**
		 * @brief Constructor
		 */
		NodeWhiteSpaceNot(int32_t _level) : NodeRangeValue<CLASS_TYPE>::NodeRangeValue(_level) {
			NodeRangeValue<CLASS_TYPE>::addValue(' ');
			NodeRangeValue<CLASS_TYPE>::addValue('\t');
			NodeRangeValue<CLASS_TYPE>::addValue('\n');
			NodeRangeValue<CLASS_TYPE>::addValue('\r');
			NodeRangeValue<CLASS_TYPE>::addValue('\f');
			NodeRangeValue<CLASS_TYPE>::addValue('\v');
			NodeRangeValue<CLASS_TYPE>::setInvertion(true);
		}
		virtual const char* getDescriptiveName() const {
			return "SpaceNot";
		}
};
#undef __class__
#define __class__ "regExp::NodeWordChar"

/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class NodeWordChar : public NodeRangeValue<CLASS_TYPE> {
	public :
		/**
		 * @brief Constructor
		 */
		NodeWordChar(int32_t _level) : NodeRangeValue<CLASS_TYPE>::NodeRangeValue(_level) {
			NodeRangeValue<CLASS_TYPE>::addRange('a', 'z');
			NodeRangeValue<CLASS_TYPE>::addRange('A', 'Z');
			NodeRangeValue<CLASS_TYPE>::addRange('0', '9');
		};
		virtual const char* getDescriptiveName() const {
			return "Word";
		}
};
#undef __class__
#define __class__ "regExp::NodeWordCharNot"
/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class NodeWordCharNot : public NodeRangeValue<CLASS_TYPE> {
	public :
		/**
		 * @brief Constructor
		 */
		NodeWordCharNot(int32_t _level) : NodeRangeValue<CLASS_TYPE>::NodeRangeValue(_level) {
			NodeRangeValue<CLASS_TYPE>::addRange('a', 'z');
			NodeRangeValue<CLASS_TYPE>::addRange('A', 'Z');
			NodeRangeValue<CLASS_TYPE>::addRange('0', '9');
			NodeRangeValue<CLASS_TYPE>::setInvertion(true);
		};
		virtual const char* getDescriptiveName() const {
			return "WordNot";
		}
};
#undef __class__
#define __class__ "regExp::NodeDot"

/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class NodeDot : public NodeRangeValue<CLASS_TYPE> {
	public :
		/**
		 * @brief Constructor
		 */
		NodeDot(int32_t _level) : NodeRangeValue<CLASS_TYPE>::NodeRangeValue(_level) {
			NodeRangeValue<CLASS_TYPE>::addValue('\0');
			NodeRangeValue<CLASS_TYPE>::setInvertion(true);
		};
		virtual const char* getDescriptiveName() const {
			return "dot";
		}
};

#undef __class__
#define __class__ "regExp::NodeEOL"

/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class NodeEOL : public NodeRangeValue<CLASS_TYPE> {
	public :
		/**
		 * @brief Constructor
		 */
		NodeEOL(int32_t _level) : NodeRangeValue<CLASS_TYPE>::NodeRangeValue(_level) {
			NodeRangeValue<CLASS_TYPE>::addValue('\r');
			NodeRangeValue<CLASS_TYPE>::addValue('\n');
		}
		virtual const char* getDescriptiveName() const {
			return "EOL";
		}
};


#undef __class__
#define __class__ "regExp::NodeSOL"

/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class NodeSOL : public Node<CLASS_TYPE> {
	public :
		/**
		 * @brief Constructor
		 */
		NodeSOL(int32_t _level) : Node<CLASS_TYPE>::Node(_level) { };
		/**
		 * @brief Destructor
		 */
		~NodeSOL() { };
		virtual enum parseStatus parse(const CLASS_TYPE& _data, int64_t _currentPos, int64_t _lenMax, FindProperty& _property) {
			int32_t findLen = 0;
			bool tmpFind = false;
			TK_REG_EXP_DBG_MODE("Parse " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " SOL{" << Node<CLASS_TYPE>::m_multipleMin << "," << Node<CLASS_TYPE>::m_multipleMax << "}");
			// TODO : is it really what I want ... (maybe next ellement will be requested... (check if previous element is \r or \n
			while (    _property.getMultiplicity() < Node<CLASS_TYPE>::m_multipleMax
			        && tmpFind == true
			        && _property.getMultiplicity() <_lenMax) {
				char32_t tmpVal = _data[_currentPos+_property.getMultiplicity()];
				// TODO : check if the file is a \r\n file ...
				if (    tmpVal == 0x0d /* <cr> */
				     || tmpVal == 0x0A /* <lf> */) {
					findLen += 1;
				} else {
					tmpFind=false;
				}
				_property.multiplicityIncrement();
			}
			_property.setPositionStop(_property.getPositionStart() + findLen);
			if(    _property.getMultiplicity()>=Node<CLASS_TYPE>::m_multipleMin
			    && _property.getMultiplicity()<=Node<CLASS_TYPE>::m_multipleMax
			    && findLen>0 ) {
				TK_REG_EXP_DBG_MODE("find " << findLen);
				return parseStatusFull;
			} else if( 0 == Node<CLASS_TYPE>::m_multipleMin ) {
				TK_REG_EXP_DBG_MODE("find size=0");
				return parseStatusFull;
			}
			return parseStatusNone;
		};
		void display() {
			TK_INFO("Find NODE : " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << "@SOL@ {"
			        << Node<CLASS_TYPE>::m_multipleMin << ","
			        << Node<CLASS_TYPE>::m_multipleMax << "}  subdata="
			        << createString(Node<CLASS_TYPE>::m_regExpData) );
		};
};


class elementPos_ts {
	public:
		int64_t start;
		int64_t stop;
};

#undef __class__
#define __class__ "regExp::NodePTheseElem"

template<class CLASS_TYPE> class NodePThese;

/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class NodePTheseElem : public Node<CLASS_TYPE> {
	protected :
		// SubNodes :
		std::vector<Node<CLASS_TYPE>*> m_subNode;
	public :
		/**
		 * @brief Constructor
		 */
		NodePTheseElem(int32_t _level) : Node<CLASS_TYPE>::Node(_level) { };
		NodePTheseElem(const std::vector<char32_t>& _data, int32_t _level) : Node<CLASS_TYPE>::Node(_level) {
			generate(_data);
		};
		/**
		 * @brief Destructor
		 */
		~NodePTheseElem() {
			/*
			for (auto it : m_subNode) {
				delete *it;
				*it = nullptr;
			}
			*/
			m_subNode.clear();
		};
		int32_t generate(const std::vector<char32_t>& _data) {
			Node<CLASS_TYPE>::m_regExpData = _data;
			TK_REG_EXP_DBG_MODE("Request Parse (elem) data=" << createString(Node<CLASS_TYPE>::m_regExpData) );
			int64_t pos = 0;
			int64_t elementSize = 0;
			std::vector<char32_t> tmpData;
			while (pos < (int64_t)Node<CLASS_TYPE>::m_regExpData.size()) {
				tmpData.clear();
				switch (Node<CLASS_TYPE>::m_regExpData[pos]) {
					case regexpOpcodePTheseIn:{
							elementSize=getLenOfPThese(Node<CLASS_TYPE>::m_regExpData, pos);
							for (int64_t kkk=pos+1; kkk<pos+elementSize+1; kkk++) {
								tmpData.push_back(Node<CLASS_TYPE>::m_regExpData[kkk]);
							}
							// add to the subnode list :
							m_subNode.push_back(new NodePThese<CLASS_TYPE>(tmpData, Node<CLASS_TYPE>::m_nodeLevel+1));
							// move current position ...
							pos += elementSize+1;
						}
						break;
					case regexpOpcodePTheseOut:
						TK_ERROR("Impossible case :  ')' " << pos);
						return false;
					case regexpOpcodeBracketIn: {
							elementSize=getLenOfBracket(Node<CLASS_TYPE>::m_regExpData, pos);
							for (int64_t kkk=pos+1; kkk<pos+elementSize+1; kkk++) {
								tmpData.push_back(Node<CLASS_TYPE>::m_regExpData[kkk]);
							}
							// add to the subnode list : 
							m_subNode.push_back(new NodeBracket<CLASS_TYPE>(tmpData, Node<CLASS_TYPE>::m_nodeLevel+1));
							// move current position ...
							pos += elementSize+1;
						}
						break;
					case regexpOpcodeBracketOut:
						TK_ERROR("Impossible case :  ']' " << pos);
						return false;
					case regexpOpcodeBracetIn: {
							elementSize=getLenOfBrace(Node<CLASS_TYPE>::m_regExpData, pos);
							for (int64_t kkk=pos+1; kkk<pos+elementSize+1; kkk++) {
								tmpData.push_back(Node<CLASS_TYPE>::m_regExpData[kkk]);
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
						m_subNode.push_back(new NodeDot<CLASS_TYPE>(Node<CLASS_TYPE>::m_nodeLevel+1));
						break;
					case regexpOpcodeStartOfLine:
						m_subNode.push_back(new NodeSOL<CLASS_TYPE>(Node<CLASS_TYPE>::m_nodeLevel+1));
						break;
					case regexpOpcodeEndOfLine:
						m_subNode.push_back(new NodeEOL<CLASS_TYPE>(Node<CLASS_TYPE>::m_nodeLevel+1));
						break;
					case regexpOpcodeDigit:
						m_subNode.push_back(new NodeDigit<CLASS_TYPE>(Node<CLASS_TYPE>::m_nodeLevel+1));
						break;
					case regexpOpcodeDigitNot:
						m_subNode.push_back(new NodeDigitNot<CLASS_TYPE>(Node<CLASS_TYPE>::m_nodeLevel+1));
						break;
					case regexpOpcodeLetter:
						m_subNode.push_back(new NodeLetter<CLASS_TYPE>(Node<CLASS_TYPE>::m_nodeLevel+1));
						break;
					case regexpOpcodeLetterNot:
						m_subNode.push_back(new NodeLetterNot<CLASS_TYPE>(Node<CLASS_TYPE>::m_nodeLevel+1));
						break;
					case regexpOpcodeSpace:
						m_subNode.push_back(new NodeWhiteSpace<CLASS_TYPE>(Node<CLASS_TYPE>::m_nodeLevel+1));
						break;
					case regexpOpcodeSpaceNot:
						m_subNode.push_back(new NodeWhiteSpaceNot<CLASS_TYPE>(Node<CLASS_TYPE>::m_nodeLevel+1));
						break;
					case regexpOpcodeWord:
						m_subNode.push_back(new NodeWordChar<CLASS_TYPE>(Node<CLASS_TYPE>::m_nodeLevel+1));
						break;
					case regexpOpcodeWordNot:
						m_subNode.push_back(new NodeWordCharNot<CLASS_TYPE>(Node<CLASS_TYPE>::m_nodeLevel+1));
						break;
					
					default: {
							elementSize = getLenOfNormal(Node<CLASS_TYPE>::m_regExpData, pos);
							for (int64_t kkk=pos; kkk<pos+elementSize; kkk++) {
								tmpData.push_back(Node<CLASS_TYPE>::m_regExpData[kkk]);
							}
							// add to the subnode list : 
							m_subNode.push_back(new NodeValue<CLASS_TYPE>(tmpData, Node<CLASS_TYPE>::m_nodeLevel+1));
							// move current position ...
							pos += elementSize-1;
						}
						break;
				}
				pos++;
			}
			return _data.size();
		};
		
		virtual enum parseStatus parse(const CLASS_TYPE& _data, int64_t _currentPos, int64_t _lenMax, FindProperty& _property) {
			int32_t findLen = 0;
			TK_REG_EXP_DBG_MODE("Parse " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (Elem)");
			// NOTE 1 : Must done only one time in EVERY case ...
			// NOTE 2 : All element inside must be OK
			if (0 == m_subNode.size()) {
				return parseStatusNone;
			}
			int64_t tmpCurrentPos = _currentPos;
			for (size_t iii=0; iii<m_subNode.size(); ++iii) {
				enum parseStatus status;
				FindProperty prop;
				prop.setPositionStart(tmpCurrentPos);
				int32_t offset = 0;
				do {
					status = m_subNode[iii]->parse(_data, tmpCurrentPos, _lenMax, prop);
					offset = prop.getFindLen();
					tmpCurrentPos = prop.getPositionStop();
					if (    status == parseStatusPartial
					     && iii+1<m_subNode.size() ) {
							TK_REG_EXP_DBG_MODE("Parse " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel+1) << " (Elem) 2        second parse ...");
							int64_t tmpCurrentPos2 = tmpCurrentPos;
							int findLen2 = 0;
							bool error = false;
							for (size_t jjj=iii+1; jjj<m_subNode.size(); ++jjj) {
								enum parseStatus status2;
								FindProperty prop2;
								prop2.setPositionStart(tmpCurrentPos2);
								int32_t offset2 = 0;
								do {
									status2 = m_subNode[jjj]->parse(_data, tmpCurrentPos2, _lenMax, prop2);
									offset2 = prop2.getFindLen();
									tmpCurrentPos2 = prop.getPositionStop();
								} while (status2 == parseStatusPartial);
								if (status2 == parseStatusNone) {
									error = true;
									break;
								} else {
									TK_REG_EXP_DBG_MODE("Parse " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (Elem) 2       find : " << prop2.getFindLen() << " [" << _property.getPositionStart() << " " << tmpCurrentPos2 << "]");
								}
							}
							if (error == false) {
								_property.setPositionStop(tmpCurrentPos2);
								TK_REG_EXP_DBG_MODE("Parse " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (Elem) 2    return : " << _property.getFindLen());
								return parseStatusFull;
							}
							TK_REG_EXP_DBG_MODE("Parse " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (Elem) 2        second parse ... (done)");
					}
				} while (status == parseStatusPartial);
				if (status == parseStatusNone) {
					findLen = 0;
					return parseStatusNone;
				} else {
					TK_REG_EXP_DBG_MODE("Parse " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (Elem)    find : " << prop.getFindLen() << " [" << _property.getPositionStart() << " " << tmpCurrentPos << "]");
				}
			}
			if (tmpCurrentPos<_currentPos) {
				findLen = 0;
			} else {
				findLen = tmpCurrentPos - _currentPos;
			}
			_property.setPositionStop(tmpCurrentPos);
			TK_REG_EXP_DBG_MODE("Parse " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (Elem)    return : " << _property.getFindLen());
			return parseStatusFull;
		};
		
		void display() {
			TK_INFO("Find NODE : " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << "@(Elem)@ {"
			        << Node<CLASS_TYPE>::m_multipleMin << ","
			        << Node<CLASS_TYPE>::m_multipleMax << "}  subdata="
			        << createString(Node<CLASS_TYPE>::m_regExpData) );
			for(auto &it : m_subNode) {
				it->display();
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
			if (m_subNode.size() == 0) {
				TK_ERROR("Set multiplicity on an inexistant element ....");
				return false;
			}
			m_subNode.back()->setMult(_min, _max);
			return true;
		}
};

#undef __class__
#define __class__ "regExp::NodePThese"

/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class NodePThese : public Node<CLASS_TYPE> {
	protected :
		std::vector<Node<CLASS_TYPE>*> m_subNode; //!< Subnode list 
	public :
		/**
		 * @brief Constructor
		 */
		NodePThese(int32_t _level=0) : Node<CLASS_TYPE>::Node(_level) { };
		NodePThese(const std::vector<char32_t>& _data, int32_t _level) : Node<CLASS_TYPE>::Node(_level) {
			generate(_data);
		};
		/**
		 * @brief Destructor
		 */
		~NodePThese() {
			/*
			for (auto it : m_subNode) {
				delete *it;
				*it = nullptr;
			}
			*/
			m_subNode.clear();
		}
		int32_t generate(const std::vector<char32_t>& _data) {
			Node<CLASS_TYPE>::m_regExpData = _data;
			TK_REG_EXP_DBG_MODE("Request Parse (...) data=" << createString(Node<CLASS_TYPE>::m_regExpData) );
			//Find all the '|' in the string (and at the good level ...) 
			int64_t pos = 0;
			int32_t elementSize = getLenOfPTheseElem(Node<CLASS_TYPE>::m_regExpData, pos);
			// generate all the "elemTypePTheseElem" of the Node
			while (elementSize>0) {
				// geerate output deta ...
				std::vector<char32_t> tmpData;
				for (int64_t kkk=pos; kkk<pos+elementSize; kkk++) {
					tmpData.push_back(Node<CLASS_TYPE>::m_regExpData[kkk]);
				}
				// add to the subnode list : 
				m_subNode.push_back(new NodePTheseElem<CLASS_TYPE>(tmpData, Node<CLASS_TYPE>::m_nodeLevel+1));
				pos += elementSize+1;
				TK_REG_EXP_DBG_MODE("plop=" << createString(Node<CLASS_TYPE>::m_regExpData, pos, pos+1) );
				elementSize = getLenOfPTheseElem(Node<CLASS_TYPE>::m_regExpData, pos);
				TK_REG_EXP_DBG_MODE("find " << elementSize << " elements");
			}
			if (    pos == 0
			     && elementSize == 0) {
				TK_ERROR("No data in the (...) element at " << pos);
				return false;
			}
			return _data.size();
		};
		virtual enum parseStatus parse(const CLASS_TYPE& _data, int64_t _currentPos, int64_t _lenMax, FindProperty& _property) {
			int32_t findLen = 0;
			TK_REG_EXP_DBG_MODE("Parse " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (...){" << Node<CLASS_TYPE>::m_multipleMin << "," << Node<CLASS_TYPE>::m_multipleMax << "}");
			if (0 == m_subNode.size()) {
				return parseStatusNone;
			}
			bool tmpFind = true;
			while (    _property.getMultiplicity() < Node<CLASS_TYPE>::m_multipleMax
			        && tmpFind == true) {
				tmpFind = false;
				for (auto &it : m_subNode) {
					enum parseStatus status;
					FindProperty prop;
					prop.setPositionStart(_currentPos+findLen);
					int32_t offset = 0;
					do {
						status = it->parse(_data, _currentPos+findLen+offset, _lenMax, prop);
						offset = prop.getFindLen();
						TK_REG_EXP_DBG_MODE("Parse " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (...)    mult=" << _property.getMultiplicity() << "     tmp " << prop.getFindLen());
					} while (status == parseStatusPartial);
					if (status == parseStatusFull) {
						findLen += prop.getFindLen();
						tmpFind = true;
					} else if (status == parseStatusPartial) {
						
					}
				}
				TK_REG_EXP_DBG_MODE("Parse " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (...)    mult=" << _property.getMultiplicity() << " find " << findLen);
				_property.multiplicityIncrement();
			}
			_property.setPositionStop(_property.getPositionStart() + findLen);
			if(    _property.getMultiplicity()>=Node<CLASS_TYPE>::m_multipleMin
			    && _property.getMultiplicity()<=Node<CLASS_TYPE>::m_multipleMax
			    && findLen>0 ) {
				TK_REG_EXP_DBG_MODE("find " << findLen);
				return parseStatusFull;
			} else if( 0 == Node<CLASS_TYPE>::m_multipleMin ) {
				TK_REG_EXP_DBG_MODE("find size=0");
				return parseStatusFull;
			}
			return parseStatusNone;
		};
		
		void display() {
			if (9999 <= Node<CLASS_TYPE>::m_nodeLevel) {
				TK_INFO("regExp :" << createString(Node<CLASS_TYPE>::m_regExpData) );
			} else {
				TK_INFO("Find NODE : " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << "@(...)@ {"
				        << Node<CLASS_TYPE>::m_multipleMin << ","
				        << Node<CLASS_TYPE>::m_multipleMax << "}  subdata="
				        << createString(Node<CLASS_TYPE>::m_regExpData) );
				for(auto &it : m_subNode) {
					it->display();
				}
			}
		};
		/**
		 * @brief Just display the regExp in color ...
		 */
		void drawColoredRegEx() {
			TK_INFO("regExp :" << createString(Node<CLASS_TYPE>::m_regExpData) );
		}
		/**
		 * @brief get the string represented the regexp (colored)
		 * @return Regexp string
		 */
		std::string getColoredRegEx() {
			return createString(Node<CLASS_TYPE>::m_regExpData);
		}
};
}
#undef __class__
#define __class__ "RegExp"

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
		regexp::elementPos_ts m_areaFind; //!< position around selection
		regexp::NodePThese<CLASS_TYPE> m_exprRootNode; //!< The tree where data is set
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
		~RegExp() {
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
			for (int64_t iii=0; iii<(int64_t)_regexp.size(); iii++) {
				if (_regexp[iii] == '\\') {
					if(iii+1>=(int64_t)_regexp.size()) {
						TK_ERROR("Dangerous parse of the element pos " << iii << " \\ with nothing after");
						// TODO : Generate Exeption ...
						return;
					}
					int64_t jjj;
					// Find the element in the list...
					for (jjj=0; jjj<regexp::constConvertionTableSize; jjj++) {
						if(		true == regexp::constConvertionTable[jjj].haveBackSlash 
							&&	_regexp[iii+1] == (char32_t)regexp::constConvertionTable[jjj].inputValue)
						{
							if (regexp::constConvertionTable[jjj].newValue==0) {
								tmpExp.push_back(regexp::constConvertionTable[jjj].specialChar);
							} else {
								tmpExp.push_back(regexp::constConvertionTable[jjj].newValue);
							}
							break;
						}
					}
					// check error : 
					if (jjj==regexp::constConvertionTableSize) {
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
					for (jjj=0; jjj<regexp::constConvertionTableSize; jjj++) {
						if(		false == regexp::constConvertionTable[jjj].haveBackSlash 
							&&	_regexp[iii] == (char32_t)regexp::constConvertionTable[jjj].inputValue)
						{
							if (regexp::constConvertionTable[jjj].newValue==0) {
								tmpExp.push_back(regexp::constConvertionTable[jjj].specialChar);
							} else {
								tmpExp.push_back(regexp::constConvertionTable[jjj].newValue);
							}
							break;
						}
					}
					// not find : normal element
					if (jjj==regexp::constConvertionTableSize) {
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
			
			//TK_REG_EXP_DBG_MODE("Main element :" << createString(tmpExp) );
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
			
			if ((int64_t)tmpExp.size() != (int64_t)m_exprRootNode.generate(tmpExp) ) {
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
		std::string getRegExp() const {
			return std::to_string(m_expressionRequested);
		};
		/**
		 * @previous
		 */
		const std::u32string& getURegExp() const {
			return m_expressionRequested;
		};
		
		/**
		 * @brief Get the status if the regular expression parsing
		 * @return true : the regExp is correctly parsed
		 * @return false : an error occcured (check log ...)
		 */
		bool getStatus() {
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
				TK_REG_EXP_DBG_MODE("parse element : " << iii << " : '" << _SearchIn[iii] << "'");
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
				regexp::FindProperty prop;
				prop.setPositionStart(iii);
				if (m_exprRootNode.parse(_SearchIn, iii, maxlen, prop) == regexp::parseStatusFull) {
					findLen = prop.getFindLen();
					TK_DEBUG("main search find : " << findLen << " elements");
					if (    _escapeChar != 0
					     && iii>0) {
						if (_escapeChar == (char32_t)_SearchIn[iii-1]) {
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
					prop.display();
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
			m_exprRootNode.setPositionStart(_startPos);
			regexp::FindProperty prop;
			if (m_exprRootNode.parse(_SearchIn, _startPos, maxlen, prop) == regexp::parseStatusFull) {
				findLen = m_exprRootNode.getFindLen();
				if (    _escapeChar != 0
				     && _startPos>0) {
					if (_escapeChar == (char32_t)_SearchIn[_startPos-1]) {
						//==> detected escape char ==> try find again ...
						return false;
					}
				}
				// Check end :
				if (m_notEndWithChar == true) {
					if (_startPos+findLen < (int64_t)_SearchIn.size() ) {
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
		int64_t	start() {
			return m_areaFind.start;
		};
		
		/**
		 * @brief Get the expression stop position detected
		 * @return position of the stop regExp
		 */
		int64_t	stop() {
			return m_areaFind.stop;
		};
		
		/**
		 * @brief Display the reg Exp
		 */
		void display() {
			m_exprRootNode.display(0);
		};
		/**
		 * @brief Just display the regExp in color ...
		 */
		void drawColoredRegEx() {
			m_exprRootNode.drawColoredRegEx();
		}
		/**
		 * @brief Get decorated regular expression. This generate a [class[ewol::compositing::Text]] decoration text. Note that can be use in [class[ewol::widget::Label]].
		 * @return The decorated string
		 */
		std::string getRegExDecorated() {
			return m_exprRootNode.getColoredRegEx();
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
			if (_pos >= (int64_t)_tmpExp.size()) {
				TK_ERROR("ended with: ( or { or [ ... not permited");
				return false;
			}
			//TK_DEBUG(" ==> Find ELEMENT : ([{");
			// case dependent : 
			if (    curentCode == regexpOpcodeBracketIn
			     || curentCode == regexpOpcodeBracetIn) {
				while(_pos<(int64_t)_tmpExp.size()) {
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
							case regexpOpcodeBracketOut:	find = (char*)"]";			break;
							case regexpOpcodeBracetOut:		find = (char*)"}";			break;
							case regexpOpcodeStar:			find = (char*)"*";			break;
							case regexpOpcodeDot:			find = (char*)".";			break;
							case regexpOpcodeQuestion:		find = (char*)"?";			break;
							case regexpOpcodePlus:			find = (char*)"+";			break;
							case regexpOpcodePipe:			find = (char*)"|";			break;
							case regexpOpcodeStartOfLine:	find = (char*)"^";			break;
							case regexpOpcodeEndOfLine:		find = (char*)"$";			break;
							case regexpOpcodeDigit:			find = (char*)"\\d";		break;
							case regexpOpcodeDigitNot:		find = (char*)"\\D";		break;
							case regexpOpcodeLetter:		find = (char*)"\\l";		break;
							case regexpOpcodeLetterNot:		find = (char*)"\\L";		break;
							case regexpOpcodeSpace:			find = (char*)"\\s";		break;
							case regexpOpcodeSpaceNot:		find = (char*)"\\S";		break;
							case regexpOpcodeWord:			find = (char*)"\\w";		break;
							case regexpOpcodeWordNot:		find = (char*)"\\W";		break;
							case regexpOpcodeNoChar:		find = (char*)"\\@";		break;
							default:													break;
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
				while(_pos< (int64_t)_tmpExp.size()) {
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
			while (pos < (int64_t)_tmpExp.size()) {
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
