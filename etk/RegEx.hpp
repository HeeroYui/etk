/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/debug.hpp>
#include <etk/stdTools.hpp>
#include <vector>
#include <memory>

#define TK_REG_DEBUG TK_HIDDEN
//#define TK_REG_DEBUG TK_VERBOSE
//#define TK_REG_DEBUG TK_DEBUG

#define TK_REG_DEBUG_3 TK_HIDDEN
//#define TK_REG_DEBUG_3 TK_VERBOSE
//#define TK_REG_DEBUG_3 TK_DEBUG

#define TK_REG_DEBUG_2 TK_HIDDEN
//#define TK_REG_DEBUG_2 TK_VERBOSE

//regular colors
#define ETK_BASH_COLOR_BLACK			"\e[0;30m"
#define ETK_BASH_COLOR_RED				"\e[0;31m"
#define ETK_BASH_COLOR_GREEN			"\e[0;32m"
#define ETK_BASH_COLOR_YELLOW			"\e[0;33m"
#define ETK_BASH_COLOR_BLUE				"\e[0;34m"
#define ETK_BASH_COLOR_MAGENTA			"\e[0;35m"
#define ETK_BASH_COLOR_CYAN				"\e[0;36m"
#define ETK_BASH_COLOR_WHITE			"\e[0;37m"
//emphasized (bold) colors
#define ETK_BASH_COLOR_BOLD_BLACK		"\e[1;30m"
#define ETK_BASH_COLOR_BOLD_RED			"\e[1;31m"
#define ETK_BASH_COLOR_BOLD_GREEN		"\e[1;32m"
#define ETK_BASH_COLOR_BOLD_YELLOW		"\e[1;33m"
#define ETK_BASH_COLOR_BOLD_BLUE		"\e[1;34m"
#define ETK_BASH_COLOR_BOLD_MAGENTA		"\e[1;35m"
#define ETK_BASH_COLOR_BOLD_CYAN		"\e[1;36m"
#define ETK_BASH_COLOR_BOLD_WHITE		"\e[1;37m"
//background colors
#define ETK_BASH_COLOR_BACKGROUND_BLACK			"\e[40m"
#define ETK_BASH_COLOR_BACKGROUND_RED			"\e[41m"
#define ETK_BASH_COLOR_BACKGROUND_GREEN			"\e[42m"
#define ETK_BASH_COLOR_BACKGROUND_YELLOW		"\e[43m"
#define ETK_BASH_COLOR_BACKGROUND_BLUE			"\e[44m"
#define ETK_BASH_COLOR_BACKGROUND_MAGENTA		"\e[45m"
#define ETK_BASH_COLOR_BACKGROUND_CYAN			"\e[46m"
#define ETK_BASH_COLOR_BACKGROUND_WHITE			"\e[47m"
// Return to the normal color settings
#define ETK_BASH_COLOR_NORMAL			"\e[0m"


namespace etk {
//in the unicode section we have : [E000..F8FF]   private area ==> we will store element in this area:
// internal define to permit to have all needed system
enum regExPrivateSection {
	regexOpcodePTheseIn=0xE000,/* ( */
	regexOpcodePTheseOut,/* ) */
	regexOpcodeBracketIn,/* [ */
	regexOpcodeBracketOut,/* ] */
	regexOpcodeBraceIn,/* { */
	regexOpcodeBraceOut,/* } */
	regexOpcodeTo,/* - */
	regexOpcodeStar,/* * */
	regexOpcodeDot,/* . */
	regexOpcodeEOF,/* \e */
	regexOpcodeQuestion,/* ? */
	regexOpcodePlus,/* + */
	regexOpcodePipe,/* | */
	regexOpcodeStartOfLine,/* ^  this is also NOT, but not manage */
	regexOpcodeEndOfLine,/* $ */
	regexOpcodeDigit,/* \d */
	regexOpcodeDigitNot,/* \D */
	regexOpcodeLetter,/* \l */
	regexOpcodeLetterNot,/* \L */
	regexOpcodeSpace,/* \s */
	regexOpcodeSpaceNot,/* \S */
	regexOpcodeWord,/* \w */
	regexOpcodeWordNot,/* \W */
	regexOpcodeNoChar,/* \@ */
	regexOpcodeError, // not used
};
/*
normal mode :
	(...)               sub element is separate with |
	\d                  Digits                                  [0-9]
	\D                  NOT a digit                             [^0-9]
	\l                  Letters                                 [a-zA-Z]
	\L                  NOT a Letter                            [^a-zA-Z]
	\s                  White space                             [ \t\n\r\f\v]
	\S                  NOT White space                         [^ \t\n\r\f\v]
	\w                  "Word" character                        [a-zA-Z0-9_]
	\W                  NOT a "Word" character                  [^a-zA-Z0-9_]
	\@                  at the start or the end                 not in the parsing of element ==> check if \w is not present   (other regEx will be <> ...)
	\e                  end-of-file / end-of-data               [\x00] ==> not counted
	[anjdi] or [a-gt-j] range: It support the \d \w \s \l elements. If you add at the first element a '^' it will invert the value selected
	.                   dot                                     [^\x00]
	$                   End / Start of line of line             ==> same as \@
	@                   Previous
==> TODO :
	Start of line
	force regex to be the shortest.
	    short:  [a-z]{2,4}?   in string "  abghjkh  " ==> find "ab"
	    greedy: [a-z]{2,4}    in string "  abghjkh  " ==> find "abgh"
	    short:  [a-z]+? ==> at least 1
	    greedy: [a-z]+
	    short:  [a-z]*? ==> at least 0
	    greedy: [a-z]*

multiplicity:
	*     ==> {0, 2147483647} (try to have the minimum size)
	?     ==> {0, 1} (or force the size to be the smallest)
	+     ==> {1, 2147483647} (try to have the minimum size)
	{x}   ==> {x, x} (try to have the minimum size)
	{x,y} ==> {x, y} (try to have the minimum size)

option of the system parsing:
	enable-multiple-lines ...
*/

class OptionList {
	public:
		bool m_multilineEnable;
};

/**
 * @brief Conversion table of every element in a regular expression.
 * @not-in-doc
 */
struct conversionTable {
	bool haveBackSlash;
	char inputValue;
	char newValue;
	enum etk::regExPrivateSection specialChar;
};
namespace regex {
enum parseStatus {
	parseStatusUnknown, //!< No status set
	parseStatusNone, //!< parse have no data
	parseStatusPartial, //!< parse is done partially, and can have more data
	parseStatusFull //!< can not parse more elements
};
//! @not-in-doc
std::ostream& operator <<(std::ostream& _os, enum parseStatus _obj);
//! @not-in-doc
extern const struct conversionTable constConversionTable[];
//! @not-in-doc
extern const int64_t constConversionTableSize;
//! @not-in-doc
std::string createString(const std::vector<char32_t>& _data, int64_t _start=0, int64_t _stop=0x7FFFFFFF);
//! @not-in-doc
char * levelSpace(uint32_t _level);
//! @not-in-doc
int64_t getLenOfPTheseElement(const std::vector<char32_t>& _data, int64_t _startPos);
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
//! @not-in-doc
std::string autoStr(const std::string& _data);
std::string autoStr(char _data);
std::string strTick(int32_t _pos);

/**
 * @brief Node Elements for every-one
 * @not-in-doc
 */
class FindProperty {
	public:
		int64_t m_positionStart; //!< find start position
		int64_t m_positionStop; //!< find end position
		uint32_t m_multiplicity; //!< current multiplicity of find element
		enum parseStatus m_status; //!< current status of parsing
		int32_t m_subIndex; //!< under index int the upper list ... for (...) 
	public:
		std::vector<FindProperty> m_subProperty; //!< list of all sub elements
	public:
		FindProperty() :
		  m_positionStart(-1),
		  m_positionStop(-1),
		  m_multiplicity(0),
		  m_status(parseStatusUnknown),
		  m_subIndex(-1) {
			// nothing to do ...
		}
		void reset() {
		  m_positionStart = -1;
		  m_positionStop = -1;
		  m_multiplicity = 0;
		  m_status = parseStatusUnknown;
		  m_subIndex = -1;
		}
		int64_t getPositionStart() const {
			return m_positionStart;
		}
		void setPositionStart(int64_t _newPos) {
			m_positionStart = _newPos;
			if (m_positionStop < m_positionStart) {
				m_positionStop = m_positionStart;
			}
		}
		int64_t getPositionStop() const {
			return m_positionStop;
		}
		void setPositionStop(int64_t _newPos) {
			m_positionStop = _newPos;
			if (m_positionStop < m_positionStart) {
				TK_CRITICAL("set voluntary a stop position before end : " << this << " start=" << m_positionStart << " stop=" << m_positionStop);
			}
		}
		uint32_t getMultiplicity() const {
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
		int64_t getFindLen() const {
			if (m_positionStop < 0) {
				return 0;
			}
			return m_positionStop - m_positionStart;
		}
		void setStatus(enum parseStatus _status) {
			m_status = _status;
		}
		enum parseStatus getStatus() const {
			return m_status;
		}
		int32_t getSubIndex() const {
			return m_subIndex;
		}
		void setSubIndex(int32_t _newIndex) {
			m_subIndex = _newIndex;
		}
		template<class CLASS_TYPE>
		static void display(const FindProperty& _element, const CLASS_TYPE& _data, int32_t _level = 0) {
			std::string tmp;
			for (int32_t iii=_element.m_positionStart; iii<_element.m_positionStop; ++iii) {
				tmp += _data[iii];
			}
			TK_INFO("prop : " << levelSpace(_level) << " ["
			        << _element.m_positionStart << ","
			        << _element.m_positionStop << "]*"
			        << _element.m_multiplicity << " data='"
			        << tmp << "'");
			for (auto &it : _element.m_subProperty) {
				FindProperty::display<CLASS_TYPE>(it, _data, _level+1);
			}
		}
		void display(int32_t _level = 0) const {
			TK_INFO("prop : " << levelSpace(_level) << " ["
			        << m_positionStart << ","
			        << m_positionStop << "]*"
			        << m_multiplicity);
			for (auto &it : m_subProperty) {
				it.display(_level+1);
			}
		}
};

std::ostream& operator <<(std::ostream& _os, const FindProperty& _obj);

/**
 * @brief Node Elements for every-one
 * @not-in-doc
 */
template<class CLASS_TYPE> class Node {
	protected :
		// Data Section ... (can have no data...)
		std::vector<char32_t> m_regExData; //!< data to parse and compare in some case ...
		int32_t m_nodeLevel;
	public :
		/**
		 * @brief Constructor
		 */
		Node(int32_t _level) :
		  m_regExData(),
		  m_nodeLevel(_level),
		  m_canHaveMultiplicity(true),
		  m_multipleMin(1),
		  m_multipleMax(1),
		  m_countOutput(true) {
			
		};
		/**
		 * @brief Destructor
		 */
		virtual ~Node() { };
		/**
		 * @brief Generate the regular expression with the current "converted string"
		 * @param[in] _data Property of the regex
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
		 * @param[in] _lenMax Maximum position to parse the data (can be not the end of the data due to the fact sometime we want to parse sub section).
		 * @return Full Find something (can not find more...)
		 * @return Partial can find more data ...
		 * @return None Find nothing
		 */
		virtual void parse(const CLASS_TYPE& _data, int64_t _currentPos, int64_t _lenMax, FindProperty& _property)=0;
		/**
		 * @brief Display the current node properties
		 * @param[in] level of the node
		 */
		virtual void display() {
			TK_INFO("Find NODE : " << levelSpace(m_nodeLevel) << "@???@ {" << getMultiplicityMin() << "," << getMultiplicityMax() << "}  under-data=" << createString(m_regExData) );
		};
	protected:
		bool m_canHaveMultiplicity; //!< minimum repetition (included)
	public:
		/**
		 * @brief Set the multiplicity capabilities.
		 * @param[in] _newVal new capabilities.
		 */
		void setMultiplicityAbility(bool _newVal) {
			m_canHaveMultiplicity = _newVal;
			if (_newVal == false) {
				m_multipleMin = 1;
				m_multipleMax = 1;
			}
		};
	protected:
		/**
		 * @brief Get the multiplicity capabilities.
		 * @return Multiplicity available.
		 */
		bool getMultiplicityAbility() const {
			return m_canHaveMultiplicity;
		};
	protected:
		uint32_t m_multipleMin; //!< minimum repetition (included)
		uint32_t m_multipleMax; //!< maximum repetition (included)
	public:
		/**
		 * @brief Set the multiplicity of this Node.
		 * @param[in] _min The minimum appear time.
		 * @param[in] _max The maximum appear time.
		 */
		void setMultiplicity(uint32_t _min, uint32_t _max) {
			if (m_canHaveMultiplicity == false) {
				TK_WARNING("can not set multiplicity ...");
				return;
			}
			m_multipleMin = std::max(_min, (uint32_t)0);
			m_multipleMax = std::max(_max, (uint32_t)1);
		}
	protected:
		/**
		 * @brief Get the minimum multiplicity.
		 * @return The minimum appear available.
		 */
		uint32_t getMultiplicityMin() const {
			return m_multipleMin;
		};
		/**
		 * @brief Get the maximum multiplicity.
		 * @return The maximum appear available.
		 */
		uint32_t getMultiplicityMax() const {
			return m_multipleMax;
		};
	protected:
		bool m_countOutput; //!< minimum repetition (included)
	public:
		/**
		 * @brief Set the output count available in regex.
		 * @param[in] _newVal new capabilities.
		 */
		void setCountOutput(bool _newVal) {
			m_countOutput = _newVal;
		};
	protected:
		/**
		 * @brief Get the output count available in regex.
		 * @return count available.
		 */
		bool getCountOutput() const {
			return m_countOutput;
		};
};

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
			Node<CLASS_TYPE>::m_regExData = _data;
			TK_REG_DEBUG("Request Parse \"Value\" data=" << createString(Node<CLASS_TYPE>::m_regExData) );
			m_data.clear();
			for (int32_t i=0; i<(int64_t)Node<CLASS_TYPE>::m_regExData.size(); i++) {
				m_data.push_back(Node<CLASS_TYPE>::m_regExData[i]);
			}
			return _data.size();
		};
		virtual void parse(const CLASS_TYPE& _data, int64_t _currentPos, int64_t _lenMax, FindProperty& _property) {
			TK_REG_DEBUG("Parse " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " Value{" << Node<CLASS_TYPE>::m_multipleMin << "," << Node<CLASS_TYPE>::m_multipleMax << "} : " << (char)m_data[0]);
			TK_REG_DEBUG("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << "       " << createString(Node<CLASS_TYPE>::m_regExData));
			TK_REG_DEBUG_3("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " Value " << _property);
			if (m_data.size() == 0) {
				TK_ERROR("No data inside type elementTypeValue");
				_property.setStatus(parseStatusNone);
				return;
			}
			if (_property.getStatus() != parseStatusPartial) {
				if (Node<CLASS_TYPE>::m_multipleMin == 0) {
					_property.setPositionStop(_property.getPositionStart());
					_property.setStatus(parseStatusPartial);
					TK_REG_DEBUG("Parse " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << "     ==> partial (minSize=0)");
					return;
				}
			}
			bool tmpFind = true;
			int32_t findLen = 0;
			while(    _property.getMultiplicity() < Node<CLASS_TYPE>::m_multipleMax
			       && tmpFind == true) {
				uint32_t offset = 0;
				int64_t kkk;
				for (kkk=0; findLen+kkk<_lenMax && kkk < (int64_t)m_data.size(); kkk++) {
					TK_REG_DEBUG("     " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel)
					                    << "      check element value : '"
					                    << etk::regex::autoStr((char)m_data[kkk])
					                    << "' ?= '"
					                    << etk::regex::autoStr((char)_data[_currentPos+findLen+kkk])
					                    << "'");
					if (m_data[kkk] != (char32_t)_data[_currentPos+findLen+kkk]) {
						tmpFind=false;
						break;
					}
					offset++;
				}
				if (kkk != (int64_t)m_data.size()) {
					// parsing not ended ...
					tmpFind = false;
				}
				// Update local offset of data
				if (tmpFind == true) {
					findLen += offset;
				}
				_property.multiplicityIncrement();
			}
			_property.setPositionStop(_property.getPositionStart() + findLen);
			if (    _property.getMultiplicity() >= Node<CLASS_TYPE>::m_multipleMin
			     && _property.getMultiplicity() <= Node<CLASS_TYPE>::m_multipleMax
			     && findLen > 0) {
				_property.setStatus(parseStatusFull);
				TK_REG_DEBUG("     " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << "      value find " << _property);
				return;
			} else if (Node<CLASS_TYPE>::m_multipleMin == 0) {
				_property.setStatus(parseStatusFull);
				TK_REG_DEBUG("     " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << "      value find " << _property);
				return;
			}
			_property.setStatus(parseStatusNone);
			return;
		};
		
		void display() {
			TK_INFO("Find NODE : " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << "@Value@ {"
			        << Node<CLASS_TYPE>::m_multipleMin << ","
			        << Node<CLASS_TYPE>::m_multipleMax << "} under-data="
			        << createString(Node<CLASS_TYPE>::m_regExData)
			        << " data: " << createString(m_data) );
		};
};

/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class NodeRangeValue : public Node<CLASS_TYPE> {
	private:
		std::vector<std::pair<char32_t, char32_t>> m_rangeList;
		std::vector<char32_t> m_dataList;
		bool m_invert;
		const char *m_typeName;
	public :
		/**
		 * @brief Constructor
		 */
		NodeRangeValue(int32_t _level) :
		  Node<CLASS_TYPE>::Node(_level),
		  m_invert(false),
		  m_typeName("auto-range") {
			
		};
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
		void setInvert(bool _newVal) {
			m_invert = _newVal;
		}
		const char* getDescriptiveName() const {
			return m_typeName;
		}
		void setDescriptiveName(const char* _name) {
			m_typeName = _name;
		}
		// TODO: multiplicity minimum, return partial, and ...
		virtual void parse(const CLASS_TYPE& _data, int64_t _currentPos, int64_t _lenMax, FindProperty& _property) {
			int32_t findLen = 0;
			TK_REG_DEBUG("Parse " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " " << getDescriptiveName() << "{" << Node<CLASS_TYPE>::m_multipleMin << "," << Node<CLASS_TYPE>::m_multipleMax << "}");
			TK_REG_DEBUG("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << "       " << createString(Node<CLASS_TYPE>::m_regExData));
			TK_REG_DEBUG_3("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " " << getDescriptiveName() << " " << _property);
			if (_property.getStatus() != parseStatusPartial) {
				if (Node<CLASS_TYPE>::m_multipleMin == 0) {
					_property.setPositionStop(_property.getPositionStart());
					_property.setStatus(parseStatusPartial);
					TK_REG_DEBUG("Parse " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << "     ==> partial (minSize=0)");
					return;
				}
			}
			char32_t tmpVal = _data[_currentPos];
			bool find = false;
			// Check range
			for (auto &it : m_rangeList) {
				TK_REG_DEBUG_3("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " " << getDescriptiveName() << "     range : " << autoStr(it.first) << " < " << autoStr(tmpVal) << " < " << autoStr(it.second));
				if (    tmpVal >= it.first
				     && tmpVal <= it.second) {
					TK_REG_DEBUG_3("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " " << getDescriptiveName() << "             OK");
					find = true;
					break;
				}
			}
			// Check Value
			if (find == false) {
				for (auto &it : m_dataList) {
					TK_REG_DEBUG_3("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " " << getDescriptiveName() << "     value : '" << autoStr(tmpVal) << "'=?='" << autoStr(it) << "'");
					if (tmpVal == it) {
						TK_REG_DEBUG_3("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " " << getDescriptiveName() << "             OK");
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
				TK_REG_DEBUG("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " " << getDescriptiveName() << " : Find (invert=" << m_invert << ")");
			} else {
				TK_REG_DEBUG("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " " << getDescriptiveName() << " : Not find (invert=" << m_invert << ")");
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
					_property.setStatus(parseStatusFull);
				} else {
					if (Node<CLASS_TYPE>::getCountOutput() == true) {
						_property.setPositionStop(newPosVal);
					} else {
						_property.setPositionStop(_property.getPositionStart());
					}
					if (_currentPos>=_lenMax) {
						_property.setStatus(parseStatusFull);
					} else {
						if(_property.getMultiplicity() == Node<CLASS_TYPE>::m_multipleMax) {
							_property.setStatus(parseStatusFull);
						} else {
							_property.setStatus(parseStatusPartial);
						}
					}
				}
			}else {
				if (_property.getPositionStop() != -1) {
					if (_property.getMultiplicity() == 0) {
						// simple optimisation ==> permit to remove parsing 1 cycle
						_property.setStatus(parseStatusNone);
					} else {
						_property.setStatus(parseStatusFull);
					}
				} else if (_property.getMultiplicity() == Node<CLASS_TYPE>::m_multipleMin) {
					_property.setPositionStop(_property.getPositionStart());
					_property.setStatus(parseStatusFull);
				} else {
					_property.setStatus(parseStatusNone);
				}
			}
			TK_REG_DEBUG("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " " << getDescriptiveName() << " : out=" << _property);
			return;
		};
		virtual void display() {
			TK_INFO("Find NODE : " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " " << getDescriptiveName() << " {"
			        << Node<CLASS_TYPE>::m_multipleMin << ","
			        << Node<CLASS_TYPE>::m_multipleMax <<
			        "}  under-data=" << createString(Node<CLASS_TYPE>::m_regExData));
		};
};

/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class NodeBracket : public NodeRangeValue<CLASS_TYPE> {
	public:
		/**
		 * @brief Constructor
		 */
		NodeBracket(int32_t _level) : NodeRangeValue<CLASS_TYPE>::NodeRangeValue(_level) {
			NodeRangeValue<CLASS_TYPE>::setDescriptiveName("[...]");
		};
		NodeBracket(const std::vector<char32_t>& _data, int32_t _level) : NodeRangeValue<CLASS_TYPE>::NodeRangeValue(_level)  {
			generate(_data);
		};
		int32_t generate(const std::vector<char32_t>& _data) {
			Node<CLASS_TYPE>::m_regExData = _data;
			TK_REG_DEBUG("Request Parse [...] data=" << createString(Node<CLASS_TYPE>::m_regExData) );
			
			char32_t lastElement = 0;
			bool multipleElement = false;
			// Parse the elements:
			for (int32_t kkk=0; kkk<(int64_t)Node<CLASS_TYPE>::m_regExData.size(); kkk++) {
				if (    kkk == 0
				     && Node<CLASS_TYPE>::m_regExData[kkk] == regexOpcodeStartOfLine) {
					// Check if the user request an invert check:
					NodeRangeValue<CLASS_TYPE>::setInvert(true);
				} else if (Node<CLASS_TYPE>::m_regExData[kkk] == regexOpcodeStartOfLine) {
					TK_ERROR("Unsupported Element '^' inside the [...] not at the first element");
					return 0;
				} else if (Node<CLASS_TYPE>::m_regExData[kkk] == regexOpcodeDigit) {
					NodeRangeValue<CLASS_TYPE>::addRange('0', '9');
				} else if (Node<CLASS_TYPE>::m_regExData[kkk] == regexOpcodeLetter) {
					NodeRangeValue<CLASS_TYPE>::addRange('a', 'z');
					NodeRangeValue<CLASS_TYPE>::addRange('A', 'Z');
				} else if (Node<CLASS_TYPE>::m_regExData[kkk] == regexOpcodeSpace) {
					NodeRangeValue<CLASS_TYPE>::addValue(' ');
					NodeRangeValue<CLASS_TYPE>::addValue('\t');
					NodeRangeValue<CLASS_TYPE>::addValue('\n');
					NodeRangeValue<CLASS_TYPE>::addValue('\r');
					NodeRangeValue<CLASS_TYPE>::addValue('\f');
					NodeRangeValue<CLASS_TYPE>::addValue('\v');
				} else if (Node<CLASS_TYPE>::m_regExData[kkk] == regexOpcodeWord) {
					NodeRangeValue<CLASS_TYPE>::addRange('a', 'z');
					NodeRangeValue<CLASS_TYPE>::addRange('A', 'Z');
					NodeRangeValue<CLASS_TYPE>::addRange('0', '9');
				} else if (    Node<CLASS_TYPE>::m_regExData[kkk] == regexOpcodeTo
				     && multipleElement == true) {
					TK_ERROR("Can not have 2 consecutive - in [...]");
					return 0;
				} else if (multipleElement == true) {
					NodeRangeValue<CLASS_TYPE>::addRange(lastElement, Node<CLASS_TYPE>::m_regExData[kkk]);
					multipleElement = false;
					lastElement = 0;
				} else if(Node<CLASS_TYPE>::m_regExData[kkk] == regexOpcodeTo) {
					multipleElement = true;
				} else {
					if (lastElement != 0) {
						NodeRangeValue<CLASS_TYPE>::addValue(lastElement);
					}
					lastElement = Node<CLASS_TYPE>::m_regExData[kkk];
				}
			}
			if (lastElement != 0) {
				NodeRangeValue<CLASS_TYPE>::addValue(lastElement);
			}
			return _data.size();
		};
};

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
		virtual void parse(const CLASS_TYPE& _data, int64_t _currentPos, int64_t _lenMax, FindProperty& _property) {
			int32_t findLen = 0;
			bool tmpFind = false;
			TK_REG_DEBUG("Parse " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " SOL{" << Node<CLASS_TYPE>::m_multipleMin << "," << Node<CLASS_TYPE>::m_multipleMax << "}");
			TK_REG_DEBUG("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << "       " << createString(Node<CLASS_TYPE>::m_regExData));
			// TODO : is it really what I want ... (maybe next element will be requested... (check if previous element is \r or \n
			while (    _property.getMultiplicity() < Node<CLASS_TYPE>::m_multipleMax
			        && tmpFind == true
			        && _property.getMultiplicity() <_lenMax) {
				char32_t tmpVal = _data[_currentPos+_property.getMultiplicity()];
				// TODO : check if the file is a \r\n file ...
				if (    tmpVal == 0x0d /* <cr> */
				     || tmpVal == 0x0A /* <lf> */) {
					findLen += 1;
				} else {
					tmpFind = false;
				}
				_property.multiplicityIncrement();
			}
			_property.setPositionStop(_property.getPositionStart() + findLen);
			if(    _property.getMultiplicity() >= Node<CLASS_TYPE>::m_multipleMin
			    && _property.getMultiplicity() <= Node<CLASS_TYPE>::m_multipleMax
			    && findLen > 0 ) {
				TK_REG_DEBUG("find " << findLen);
				_property.setStatus(parseStatusFull);
				return;
			} else if(Node<CLASS_TYPE>::m_multipleMin == 0) {
				TK_REG_DEBUG("find size=0");
				_property.setStatus(parseStatusFull);
				return;
			}
			_property.setStatus(parseStatusNone);
			return;
		};
		void display() {
			TK_INFO("Find NODE : " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << "@SOL@ {"
			        << Node<CLASS_TYPE>::m_multipleMin << ","
			        << Node<CLASS_TYPE>::m_multipleMax << "}  under-data="
			        << createString(Node<CLASS_TYPE>::m_regExData) );
		};
};


class ElementPos {
	public:
		int64_t start;
		int64_t stop;
};

template<class CLASS_TYPE> class NodePThese;

/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class NodePTheseElement : public Node<CLASS_TYPE> {
	protected :
		// SubNodes :
		std::vector<Node<CLASS_TYPE>*> m_subNode;
	public :
		/**
		 * @brief Constructor
		 */
		NodePTheseElement(int32_t _level) : Node<CLASS_TYPE>::Node(_level) { };
		NodePTheseElement(const std::vector<char32_t>& _data, int32_t _level) : Node<CLASS_TYPE>::Node(_level) {
			generate(_data);
		};
		/**
		 * @brief Destructor
		 */
		~NodePTheseElement() {
			/*
			for (auto it : m_subNode) {
				delete *it;
				*it = nullptr;
			}
			*/
			m_subNode.clear();
		};
		int32_t generate(const std::vector<char32_t>& _data) {
			Node<CLASS_TYPE>::m_regExData = _data;
			TK_REG_DEBUG("Request Parse (element) data=" << createString(Node<CLASS_TYPE>::m_regExData) );
			int64_t pos = 0;
			int64_t elementSize = 0;
			std::vector<char32_t> tmpData;
			while (pos < (int64_t)Node<CLASS_TYPE>::m_regExData.size()) {
				tmpData.clear();
				switch (Node<CLASS_TYPE>::m_regExData[pos]) {
					case regexOpcodePTheseIn:{
							elementSize=getLenOfPThese(Node<CLASS_TYPE>::m_regExData, pos);
							for (int64_t kkk=pos+1; kkk<pos+elementSize+1; ++kkk) {
								tmpData.push_back(Node<CLASS_TYPE>::m_regExData[kkk]);
							}
							// add to the under-node list :
							m_subNode.push_back(new NodePThese<CLASS_TYPE>(tmpData, Node<CLASS_TYPE>::m_nodeLevel+1));
							// move current position ...
							pos += elementSize+1;
						}
						break;
					case regexOpcodePTheseOut:
						TK_ERROR("Impossible case :  ')' " << pos);
						return false;
					case regexOpcodeBracketIn: {
							elementSize=getLenOfBracket(Node<CLASS_TYPE>::m_regExData, pos);
							for (int64_t kkk=pos+1; kkk<pos+elementSize+1; ++kkk) {
								tmpData.push_back(Node<CLASS_TYPE>::m_regExData[kkk]);
							}
							// add to the under-node list : 
							m_subNode.push_back(new NodeBracket<CLASS_TYPE>(tmpData, Node<CLASS_TYPE>::m_nodeLevel+1));
							// move current position ...
							pos += elementSize+1;
						}
						break;
					case regexOpcodeBracketOut:
						TK_ERROR("Impossible case :  ']' " << pos);
						return false;
					case regexOpcodeBraceIn: {
							elementSize = getLenOfBrace(Node<CLASS_TYPE>::m_regExData, pos);
							for (int64_t kkk=pos+1; kkk<pos+elementSize+1; ++kkk) {
								tmpData.push_back(Node<CLASS_TYPE>::m_regExData[kkk]);
							}
							uint32_t min = 0;
							uint32_t max = 0;
							if (parseBrace(tmpData, min, max) == false) {
								return false;
							}
							setMultiplicityOnLastNode(min, max);
							pos += elementSize+1;
						}
						break;
					case regexOpcodeBraceOut:
						TK_ERROR("Impossible case :  '}' " << pos);
						return false;
					case regexOpcodeTo:
						TK_ERROR("Impossible case :  '-' " << pos);
						return false;
					case regexOpcodeStar:
						setMultiplicityOnLastNode(0, 0x7FFFFFFF);
						break;
					case regexOpcodeQuestion:
						setMultiplicityOnLastNode(0, 1);
						break;
					case regexOpcodePlus:
						setMultiplicityOnLastNode(1, 0x7FFFFFFF);
						break;
					case regexOpcodePipe:
						TK_ERROR("Impossible case :  '|' " << pos);
						return false;
					case regexOpcodeEOF:
						{
							NodeRangeValue<CLASS_TYPE>* tmpNode = new NodeRangeValue<CLASS_TYPE>(Node<CLASS_TYPE>::m_nodeLevel+1);
							tmpNode->setDescriptiveName("EOF");
							tmpNode->addValue('\0');
							tmpNode->setCountOutput(false);
							tmpNode->setMultiplicityAbility(false);
							m_subNode.push_back(tmpNode);
						}
						break;
					case regexOpcodeDot:
						{
							NodeRangeValue<CLASS_TYPE>* tmpNode = new NodeRangeValue<CLASS_TYPE>(Node<CLASS_TYPE>::m_nodeLevel+1);
							tmpNode->setDescriptiveName("dot");
							tmpNode->addValue('\0');
							tmpNode->setInvert(true);
							m_subNode.push_back(tmpNode);
						}
						break;
					case regexOpcodeStartOfLine:
						m_subNode.push_back(new NodeSOL<CLASS_TYPE>(Node<CLASS_TYPE>::m_nodeLevel+1));
						break;
					case regexOpcodeEndOfLine:
						{
							NodeRangeValue<CLASS_TYPE>* tmpNode = new NodeRangeValue<CLASS_TYPE>(Node<CLASS_TYPE>::m_nodeLevel+1);
							tmpNode->setDescriptiveName("EOL");
							tmpNode->addValue('\n');
							m_subNode.push_back(tmpNode);
						}
						break;
					case regexOpcodeDigit:
						{
							NodeRangeValue<CLASS_TYPE>* tmpNode = new NodeRangeValue<CLASS_TYPE>(Node<CLASS_TYPE>::m_nodeLevel+1);
							tmpNode->setDescriptiveName("digit");
							tmpNode->addRange('0', '9');
							m_subNode.push_back(tmpNode);
						}
						break;
					case regexOpcodeDigitNot:
						{
							NodeRangeValue<CLASS_TYPE>* tmpNode = new NodeRangeValue<CLASS_TYPE>(Node<CLASS_TYPE>::m_nodeLevel+1);
							tmpNode->setDescriptiveName("digit-not");
							tmpNode->addRange('0', '9');
							tmpNode->setInvert(true);
							m_subNode.push_back(tmpNode);
						}
						break;
					case regexOpcodeLetter:
						{
							NodeRangeValue<CLASS_TYPE>* tmpNode = new NodeRangeValue<CLASS_TYPE>(Node<CLASS_TYPE>::m_nodeLevel+1);
							tmpNode->setDescriptiveName("letter");
							tmpNode->addRange('a', 'z');
							tmpNode->addRange('A', 'Z');
							m_subNode.push_back(tmpNode);
						}
						break;
					case regexOpcodeLetterNot:
						{
							NodeRangeValue<CLASS_TYPE>* tmpNode = new NodeRangeValue<CLASS_TYPE>(Node<CLASS_TYPE>::m_nodeLevel+1);
							tmpNode->setDescriptiveName("letter-not");
							tmpNode->addRange('a', 'z');
							tmpNode->addRange('A', 'Z');
							tmpNode->setInvert(true);
							m_subNode.push_back(tmpNode);
						}
						break;
					case regexOpcodeSpace:
						{
							NodeRangeValue<CLASS_TYPE>* tmpNode = new NodeRangeValue<CLASS_TYPE>(Node<CLASS_TYPE>::m_nodeLevel+1);
							tmpNode->setDescriptiveName("space");
							tmpNode->addValue(' ');
							tmpNode->addValue('\t');
							tmpNode->addValue('\n');
							tmpNode->addValue('\r');
							tmpNode->addValue('\f');
							tmpNode->addValue('\v');
							m_subNode.push_back(tmpNode);
						}
						break;
					case regexOpcodeSpaceNot:
						{
							NodeRangeValue<CLASS_TYPE>* tmpNode = new NodeRangeValue<CLASS_TYPE>(Node<CLASS_TYPE>::m_nodeLevel+1);
							tmpNode->setDescriptiveName("space-not");
							tmpNode->addValue(' ');
							tmpNode->addValue('\t');
							tmpNode->addValue('\n');
							tmpNode->addValue('\r');
							tmpNode->addValue('\f');
							tmpNode->addValue('\v');
							tmpNode->setInvert(true);
							m_subNode.push_back(tmpNode);
						}
						break;
					case regexOpcodeWord:
						{
							NodeRangeValue<CLASS_TYPE>* tmpNode = new NodeRangeValue<CLASS_TYPE>(Node<CLASS_TYPE>::m_nodeLevel+1);
							tmpNode->setDescriptiveName("word");
							tmpNode->addRange('a', 'z');
							tmpNode->addRange('A', 'Z');
							tmpNode->addRange('0', '9');
							m_subNode.push_back(tmpNode);
						}
						break;
					case regexOpcodeWordNot:
						{
							NodeRangeValue<CLASS_TYPE>* tmpNode = new NodeRangeValue<CLASS_TYPE>(Node<CLASS_TYPE>::m_nodeLevel+1);
							tmpNode->setDescriptiveName("word-not");
							tmpNode->addRange('a', 'z');
							tmpNode->addRange('A', 'Z');
							tmpNode->addRange('0', '9');
							tmpNode->setInvert(true);
							m_subNode.push_back(tmpNode);
						}
						break;
					default: {
							elementSize = getLenOfNormal(Node<CLASS_TYPE>::m_regExData, pos);
							for (int64_t kkk=pos; kkk<pos+elementSize; kkk++) {
								tmpData.push_back(Node<CLASS_TYPE>::m_regExData[kkk]);
							}
							// add to the under-node list : 
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
		virtual void parse(const CLASS_TYPE& _data, int64_t _currentPos, int64_t _lenMax, FindProperty& _property) {
			//TK_REG_DEBUG_2("Parse " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (element) data to parse : '" << autoStr(std::string(_data, _currentPos, _lenMax-_currentPos)) << "'");
			//TK_REG_DEBUG_2("Parse " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (element) m_data='" << autoStr(Node<CLASS_TYPE>::m_data) << "'");
			TK_REG_DEBUG("Parse " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (element) " << _property);
			TK_REG_DEBUG("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << "       work on: " << createString(Node<CLASS_TYPE>::m_regExData));
			TK_REG_DEBUG("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << "       pos=" << _currentPos << " ==> " << _lenMax);
			int findLen = 0;
			bool error = false;
			size_t iii = 0;
			int64_t tmpCurrentPos = _currentPos;
			FindProperty prop;
			if (_property.m_subProperty.size() != 0) {
				// rewind the list:
				bool findPartialNode = false;
				for (int64_t jjj=_property.m_subProperty.size()-1; jjj>=0; --jjj) {
					if (_property.m_subProperty[jjj].getPositionStart() < _currentPos) {
						break;
					}
					if (_property.m_subProperty[jjj].getStatus() == parseStatusPartial) {
						findPartialNode = true;
						prop = _property.m_subProperty[jjj];
						tmpCurrentPos = prop.getPositionStop();
						_property.m_subProperty.erase(_property.m_subProperty.begin()+jjj, _property.m_subProperty.end());
						iii = jjj;
						TK_REG_DEBUG("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (element) rewind=" << iii);
						break;
					}
				}
				// We did not find the element:
				if (findPartialNode == false) {
					_property.m_subProperty.clear();
					_property.reset();
					prop.setPositionStart(tmpCurrentPos);
				}
			} else {
				prop.setPositionStart(tmpCurrentPos);
			}
			while (iii < m_subNode.size()) {
				//TK_REG_DEBUG_2("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (element=" << iii << "/" << m_subNode.size() << ") data='" << autoStr(std::string(_data, tmpCurrentPos, _lenMax-tmpCurrentPos)) << "'");
				m_subNode[iii]->parse(_data, tmpCurrentPos, _lenMax, prop);
				if (prop.getStatus() == parseStatusNone) {
					TK_REG_DEBUG("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (element=" << iii << "/" << m_subNode.size() << ") ===None===      : " << prop);
					// rewind the list:
					bool findPartialNode = false;
					for (int64_t jjj=_property.m_subProperty.size()-1; jjj>=0; --jjj) {
						if (_property.m_subProperty[jjj].getStatus() == parseStatusPartial) {
							findPartialNode = true;
							prop = _property.m_subProperty[jjj];
							tmpCurrentPos = prop.getPositionStop();
							_property.m_subProperty.erase(_property.m_subProperty.begin()+jjj, _property.m_subProperty.end());
							iii = jjj;
							TK_REG_DEBUG("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (element=?/" << m_subNode.size() << ") == rewind at " << iii << "");
							break;
						}
					}
					// We did not find the element :
					if (findPartialNode == false) {
						_property.setStatus(parseStatusNone);
						TK_REG_DEBUG("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (element) return=" << _property);
						return;
					} else {
						if (tmpCurrentPos >= (int64_t)_data.size()) {
							TK_REG_DEBUG("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (element=?/" << m_subNode.size() << ") Reach end of buffer");
							_property.setStatus(parseStatusNone);
							return;
						}
						//prop.setPositionStart(tmpCurrentPos);
						continue;
					}
				}
				if (prop.getPositionStart() > prop.getPositionStop()) {
					TK_CRITICAL("Very bad case ... : " << prop);
				}
				tmpCurrentPos = prop.getPositionStop();
				_property.m_subProperty.push_back(prop);
				TK_REG_DEBUG("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (element=" << iii << "/" << m_subNode.size() << ") === OK === find : " << prop);
				prop.reset();
				prop.setPositionStart(tmpCurrentPos);
				iii++;
			}
			_property.setStatus(parseStatusFull);
			// Display sub List :
			for (auto &it : _property.m_subProperty) {
				TK_REG_DEBUG("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (element) sub=" << it);
			}
			for (int64_t iii=_property.m_subProperty.size()-1; iii>=0; --iii) {
				if (_property.m_subProperty[iii].getStatus() == parseStatusPartial) {
					_property.setStatus(parseStatusPartial);
					break;
				}
			}
			if (_property.m_subProperty.size()>0) {
				_property.setPositionStop(_property.m_subProperty.back().getPositionStop() );
			} else {
				TK_WARNING("RegEx ERROR");
			}
			TK_REG_DEBUG("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (element) return=" << _property);
		}
		
		void display() {
			TK_INFO("Find NODE : " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << "@(Element)@ {"
			        << Node<CLASS_TYPE>::m_multipleMin << ","
			        << Node<CLASS_TYPE>::m_multipleMax << "}  under-data="
			        << createString(Node<CLASS_TYPE>::m_regExData) );
			for(auto &it : m_subNode) {
				it->display();
			}
		};
	private :
		/**
		 * @brief Set the number of repeat time on a the last node in the list ...
		 * @param[in] _min Minimum of the multiplicity
		 * @param[in] _max Maximum of the multiplicity
		 * @return true if we find the node, false otherwise
		 */
		bool setMultiplicityOnLastNode(uint32_t _min, uint32_t _max) {
			if (m_subNode.size() == 0) {
				TK_ERROR("Set multiplicity on an inexistent element ....");
				return false;
			}
			m_subNode.back()->setMultiplicity(_min, _max);
			return true;
		}
};

/**
 * @not-in-doc
 */
template<class CLASS_TYPE> class NodePThese : public Node<CLASS_TYPE> {
	protected :
		std::vector<Node<CLASS_TYPE>*> m_subNode; //!< Under-node list 
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
			Node<CLASS_TYPE>::m_regExData = _data;
			TK_REG_DEBUG("Request Parse (...) data=" << createString(Node<CLASS_TYPE>::m_regExData) );
			//Find all the '|' in the string (and at the good level ...) 
			int64_t pos = 0;
			int32_t elementSize = getLenOfPTheseElement(Node<CLASS_TYPE>::m_regExData, pos);
			// generate all the "elementTypePTheseElement" of the Node
			while (elementSize>0) {
				// Generate output data ...
				std::vector<char32_t> tmpData;
				for (int64_t kkk=pos; kkk<pos+elementSize; kkk++) {
					tmpData.push_back(Node<CLASS_TYPE>::m_regExData[kkk]);
				}
				// add to the under-node list : 
				m_subNode.push_back(new NodePTheseElement<CLASS_TYPE>(tmpData, Node<CLASS_TYPE>::m_nodeLevel+1));
				pos += elementSize+1;
				TK_REG_DEBUG("plop=" << createString(Node<CLASS_TYPE>::m_regExData, pos, pos+1) );
				elementSize = getLenOfPTheseElement(Node<CLASS_TYPE>::m_regExData, pos);
				TK_REG_DEBUG("find " << elementSize << " elements");
			}
			if (    pos == 0
			     && elementSize == 0) {
				TK_ERROR("No data in the (...) element at " << pos);
				return false;
			}
			return _data.size();
		};
		virtual void parse(const CLASS_TYPE& _data, int64_t _currentPos, int64_t _lenMax, FindProperty& _property) {
			TK_REG_DEBUG("Parse " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (...) {" << Node<CLASS_TYPE>::m_multipleMin << "," << Node<CLASS_TYPE>::m_multipleMax << "}");
			TK_REG_DEBUG("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << "       work on: " << createString(Node<CLASS_TYPE>::m_regExData));
			TK_REG_DEBUG("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << "       pos=" << _currentPos << " ==> " << _lenMax);
			TK_REG_DEBUG_2("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (...) data='" << autoStr(std::string(_data, _currentPos, _lenMax-_currentPos)) << "'");
			TK_REG_DEBUG_3("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (...) input property=" << _property);
			if (m_subNode.size() == 0) {
				_property.setStatus(parseStatusNone);
				return;
			}
			// prevent overflow
			if (_currentPos == _lenMax) {
				_property.setStatus(parseStatusNone);
				return;
			}
			if (_property.getStatus() != parseStatusPartial) {
				if (Node<CLASS_TYPE>::m_multipleMin == 0) {
					TK_REG_DEBUG("Parse " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << "     ==> partial (minSize=0)");
					_property.setStatus(parseStatusPartial);
					_property.setPositionStop(_property.getPositionStart());
					return;
				}
			}
			bool haveSubPartial = false;
			for (int64_t iii=_property.m_subProperty.size()-1; iii>=0; --iii) {
				if (_property.m_subProperty[iii].getStatus() == parseStatusPartial) {
					TK_REG_DEBUG("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (...) Have partial");
					haveSubPartial = true;
					break;
				}
			}
			if (    haveSubPartial == false
			     && _property.getMultiplicity() >= Node<CLASS_TYPE>::m_multipleMax) {
				_property.setStatus(parseStatusFull);
				return;
			}
			int64_t tmpCurrentPos = _currentPos;
			FindProperty prop;
			size_t iiiStartPos = 0;
			if (haveSubPartial == true) {
				for (int64_t jjj=_property.m_subProperty.size()-1; jjj>=0; --jjj) {
					if (_property.m_subProperty[jjj].getStatus() == parseStatusPartial) {
						prop = _property.m_subProperty[jjj];
						tmpCurrentPos = prop.getPositionStop();
						_property.m_subProperty.erase(_property.m_subProperty.begin()+jjj, _property.m_subProperty.end());
						iiiStartPos = prop.getSubIndex();
						TK_REG_DEBUG("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (...) Rewind to " << iiiStartPos << " last element=" << prop);
						_property.setPositionStop(tmpCurrentPos);
						break;
					}
				}
			} else {
				if (    _property.getPositionStop() < 0
				     && Node<CLASS_TYPE>::m_multipleMin == 0
				     && _property.getMultiplicity() == 0) {
					TK_REG_DEBUG("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (...) Finish to " << iiiStartPos << " last element=" << prop);
					_property.setPositionStop(_property.getPositionStart());
					_property.setStatus(parseStatusPartial);
					return;
				}
				prop.setPositionStart(tmpCurrentPos);
			}
			int32_t findLen = _property.getFindLen();
			int32_t offset = 0;
			_property.setStatus(parseStatusFull);
			bool tmpFind = true;
			while (    _property.getMultiplicity() <= Node<CLASS_TYPE>::m_multipleMax
			        && tmpFind == true) {
				tmpFind = false;
				if (tmpCurrentPos+offset>=_lenMax) {
					TK_REG_DEBUG("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (... ---/" << m_subNode.size() << ") ==> out of range : " << tmpCurrentPos << "+" << offset << " >= " << _lenMax);
					prop.setStatus(parseStatusFull);
					if (prop.getPositionStart() > prop.getPositionStop()) {
						TK_CRITICAL("Very bad case ... : " << prop);
					}
					_property.m_subProperty.push_back(prop);
					break;
				}
				for (size_t iii=iiiStartPos; iii<m_subNode.size() && tmpCurrentPos+offset<_lenMax; ++iii) {
					TK_REG_DEBUG("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (... " << iii << "/" << m_subNode.size() << ")");
					m_subNode[iii]->parse(_data, tmpCurrentPos+offset, _lenMax, prop);
					//offset = prop.getFindLen();
					if (    prop.getStatus() == parseStatusFull
					     || prop.getStatus() == parseStatusPartial) {
						TK_REG_DEBUG("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (... " << iii << "/" << m_subNode.size() << ") --- OK --- prop=" << prop);
						findLen += prop.getFindLen();
						offset += prop.getFindLen();
						prop.setSubIndex(iii);
						if (prop.getPositionStart() > prop.getPositionStop()) {
							TK_CRITICAL("Very bad case ... : " << prop);
						}
						_property.m_subProperty.push_back(prop);
						tmpFind = true;
						prop.reset();
						prop.setPositionStart(tmpCurrentPos+offset);
						break;
					}
					TK_REG_DEBUG("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (... " << iii << "/" << m_subNode.size() << ") ---NONE---");
					prop.reset();
					prop.setPositionStart(tmpCurrentPos+offset);
				}
				iiiStartPos = 0;
				if (tmpFind == true) {
					_property.setMultiplicity(_property.m_subProperty.size());
					TK_REG_DEBUG("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (...) multiplicity=" << _property.getMultiplicity() << " find " << findLen);
					if (_property.getMultiplicity() >= Node<CLASS_TYPE>::m_multipleMin) {
						_property.setStatus(parseStatusPartial);
						break;
					}
				}
			}
			for (int64_t iii=_property.m_subProperty.size()-1; iii>=0; --iii) {
				TK_REG_DEBUG("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (...)     sub=" << _property.m_subProperty[iii]);
				if (_property.m_subProperty[iii].getStatus() == parseStatusPartial) {
					_property.setStatus(parseStatusPartial);
					break;
				}
			}
			if (_property.m_subProperty.size() == 0) {
				TK_REG_DEBUG("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (...)  sub empty ...");
				_property.setPositionStop(_property.getPositionStart());
			} else {
				TK_REG_DEBUG("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (...)  sub finished ...");
				FindProperty::display<CLASS_TYPE>(_property, _data, 2);
				_property.setPositionStop(_property.m_subProperty.back().getPositionStop());
			}
			if(    _property.getMultiplicity() >= Node<CLASS_TYPE>::m_multipleMin
			    && _property.getMultiplicity() <= Node<CLASS_TYPE>::m_multipleMax
			    && findLen> 0  ) {
				TK_REG_DEBUG("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (...) return=" << _property);
				return;
			} else if( 0 == Node<CLASS_TYPE>::m_multipleMin ) {
				TK_REG_DEBUG("      " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << " (...) return=" << _property);
				return;
			}
			_property.setStatus(parseStatusNone);
			return;
		};
		
		void display() {
			if (9999 <= Node<CLASS_TYPE>::m_nodeLevel) {
				TK_INFO("regEx :" << createString(Node<CLASS_TYPE>::m_regExData) );
			} else {
				TK_INFO("Find NODE : " << levelSpace(Node<CLASS_TYPE>::m_nodeLevel) << "@(...)@ {"
				        << Node<CLASS_TYPE>::m_multipleMin << ","
				        << Node<CLASS_TYPE>::m_multipleMax << "}  under-data="
				        << createString(Node<CLASS_TYPE>::m_regExData) );
				for(auto &it : m_subNode) {
					it->display();
				}
			}
		};
		/**
		 * @brief Just display the regEx in color ...
		 */
		void drawColoredRegEx() {
			TK_INFO("regEx :" << createString(Node<CLASS_TYPE>::m_regExData) );
		}
		/**
		 * @brief get the string represented the regex (colored)
		 * @return Regex string
		 */
		std::string getColoredRegEx() {
			return createString(Node<CLASS_TYPE>::m_regExData);
		}
};
}

/**
 * @brief Regular expression interface template.
 * 
 * List of element that can be displayed:
 * 
 * [pre]
 *     (...)                 sub element is separate with |
 *     \d                    Digits                         [0-9]
 *     \D                    NOT a digit                    [^0-9]
 *     \l                    Letters                        [a-zA-Z]
 *     \L                    NOT a Letter                   [^a-zA-Z]
 *     \s                    White space                    [ \t\n\r\f\v]
 *     \S                    NOT White space                [^ \t\n\r\f\v]
 *     \w                    "Word" character               [a-zA-Z0-9_]
 *     \W                    NOT a "Word" character         [^a-zA-Z0-9_]
 *     \@                    at the start or the end        not in the parsing of element ==> check if \w is not present   (other regEx will be <> ...)
 *     [anjdi] or [a-gt-j]   range. It support the \d \w \s \l elements. If you add at the first element a '^' it will invert the value selected
 *     .                     dot                            [^\x00-\x08\x0A-\x1F\x7F]
 * ==> TODO :
 *     $                     End / Start of line of line    ==> same as \@
 *     ^in the []            invert the range element
 * 
 * multiplicity :
 *     *     ==> {0, 2147483647}
 *     ?     ==> {0, 1}
 *     +     ==> {1, 2147483647}
 *     {x}   ==> {x, x}
 *     {x,y} ==> {x, y}
 * [/pre]
 * 
 * @param[in] CLASS_TYPE Type of the class that might be parsed. This class might have a interface : operator[] that return a char or a char32_t.
 * 
 * Regular is easy to use:
 */
template<class CLASS_TYPE> class RegEx {
	private:
		std::u32string m_expressionRequested; //!< Regular expression parsed ...
		regex::ElementPos m_areaFind; //!< position around selection
		regex::NodePThese<CLASS_TYPE> m_expressionRootNode; //!< The tree where data is set
		bool m_isOk; //!< Known if we can process with this regEx
		bool m_notBeginWithChar; //!< The regular expression must not have previously a char [a-zA-Z0-9_]
		bool m_notEndWithChar; //!< The regular expression must not have after the end a char [a-zA-Z0-9_]
		bool m_maximize; //!< by default the regex find the minimum size of a regex .
		OptionList m_options; //!< Global option list of the reg-ex.
	public:
		/**
		 * @brief Constructor
		 * @param[in,out] _expression Regular expression to parse
		 */
		RegEx(const std::u32string &_expression=U"") :
		  m_expressionRequested(U""),
		  m_isOk(false),
		  m_notBeginWithChar(false),
		  m_notEndWithChar(false),
		  m_maximize(false) {
			m_areaFind.start=0;
			m_areaFind.stop=0;
			if (_expression.size() != 0) {
				compile(_expression);
			}
		}
		/**
		 * @previous
		 */
		RegEx(const std::string &_expression) :
		  m_expressionRequested(U""),
		  m_isOk(false),
		  m_notBeginWithChar(false),
		  m_notEndWithChar(false),
		  m_maximize(false) {
			m_areaFind.start=0;
			m_areaFind.stop=0;
			if (_expression.size() != 0) {
				compile(etk::to_u32string(_expression));
			}
		};
		/**
		 * @brief Destructor
		 */
		~RegEx() {
			m_isOk = false;
		};
		
		/**
		 * @brief SetMaximizing of the regex
		 * @param[in] _value Maximize or not the regEx
		 */
		void setMaximize(bool _value) {
			m_maximize = _value;
		}
		/**
		 * @brief Set a new regular expression matching
		 * @param[in] _expression the new expression to search
		 */
		// TODO : Add an error ...
		void compile(const std::string &_expression) {
			if (_expression.size() != 0) {
				TK_REG_DEBUG("normal string parse : '" << _expression << "'");
				compile(etk::to_u32string(_expression));
			}
		}
		/**
		 * @previous
		 */
		void compile(const std::u32string &_expression) {
			m_expressionRequested = _expression;
			std::vector<char32_t> tmpExpression;
			
			TK_REG_DEBUG("---------------------------------------------------------------------");
			TK_REG_DEBUG("Parse RegEx : (" << m_expressionRequested << ")" );
			m_isOk = false;
			m_areaFind.start=0;
			m_areaFind.stop=0;
			m_notBeginWithChar = false;
			m_notEndWithChar = false;
			
			// Change in the regular Opcode ==> replace \x with the correct element ... x if needed
			int32_t countBraceIn = 0;
			int32_t countBraceOut = 0;
			int32_t countPTheseIn = 0;
			int32_t countPTheseOut = 0;
			int32_t countBracketIn = 0;
			int32_t countBracketOut = 0;
			for (int64_t iii=0; iii<(int64_t)_expression.size(); iii++) {
				if (_expression[iii] == '\\') {
					if(iii+1>=(int64_t)_expression.size()) {
						TK_ERROR("Dangerous parse of the element pos " << iii << " \\ with nothing after");
						// TODO : Generate Exception ...
						return;
					}
					int64_t jjj;
					// Find the element in the list...
					for (jjj=0; jjj<regex::constConversionTableSize; ++jjj) {
						if (    regex::constConversionTable[jjj].haveBackSlash == true
						     && _expression[iii+1] == (char32_t)regex::constConversionTable[jjj].inputValue) {
							if (regex::constConversionTable[jjj].newValue == 0) {
								tmpExpression.push_back(regex::constConversionTable[jjj].specialChar);
							} else {
								tmpExpression.push_back(regex::constConversionTable[jjj].newValue);
							}
							break;
						}
					}
					// check error : 
					if (jjj == regex::constConversionTableSize) {
						TK_WARNING(" parse : " << _expression);
						TK_WARNING("         " << etk::regex::strTick(iii+1));
						TK_ERROR("Dangerous parse of the \\x with the value : '" << _expression[iii+1] << "' at element " << iii);
						return;
					}
					// less one char in the regular expression ...
					iii++;
				} else {
					if (_expression[iii] == '(') {
						countPTheseIn++;
					} else if (_expression[iii] == ')') {
						countPTheseOut++;
					} else if (_expression[iii] == '[') {
						countBracketIn++;
					} else if (_expression[iii] == ']') {
						countBracketOut++;
					} else if (_expression[iii] == '{') {
						countBraceIn++;
					} else if (_expression[iii] == '}') {
						countBraceOut++;
					}
					int64_t jjj;
					// find the element in the list...
					for (jjj=0; jjj<regex::constConversionTableSize; ++jjj) {
						if(		regex::constConversionTable[jjj].haveBackSlash == false
							&&	_expression[iii] == (char32_t)regex::constConversionTable[jjj].inputValue)
						{
							if (regex::constConversionTable[jjj].newValue == 0) {
								tmpExpression.push_back(regex::constConversionTable[jjj].specialChar);
							} else {
								tmpExpression.push_back(regex::constConversionTable[jjj].newValue);
							}
							break;
						}
					}
					// not find : normal element
					if (jjj == regex::constConversionTableSize) {
						//TK_REG_DEBUG("parse : '" << _regex[iii] << "'" );
						tmpExpression.push_back(_expression[iii]);
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
			if (checkGoodPosition(tmpExpression) == false) {
				return;
			}
			
			//TK_REG_DEBUG("Main element :" << createString(tmpExpression) );
			if (    tmpExpression.size() > 0
			     && tmpExpression[0] == regexOpcodeNoChar) {
				//TK_DEBUG("=> must not begin with char");
				m_notBeginWithChar = true;
				// remove element
				tmpExpression.erase(tmpExpression.begin());
			}
			if (    tmpExpression.size() > 0
			     && tmpExpression[tmpExpression.size()-1] == regexOpcodeNoChar) {
				//TK_DEBUG("=> must not end with char");
				m_notEndWithChar = true;
				// remove element
				tmpExpression.erase(tmpExpression.end()-1);
			}
			
			if ((int64_t)tmpExpression.size() != (int64_t)m_expressionRootNode.generate(tmpExpression) ) {
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
		 * @return the string representing the RegEx
		 */
		std::string getRegEx() const {
			return etk::to_string(m_expressionRequested);
		};
		/**
		 * @previous
		 */
		const std::u32string& getURegEx() const {
			return m_expressionRequested;
		};
		
		/**
		 * @brief Get the status if the regular expression parsing
		 * @return true : the regEx is correctly parsed
		 * @return false : an error occurred (check log ...)
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
		 * @return true : find something, false otherwise
		 */
		bool parse(const CLASS_TYPE& _SearchIn,
		           int64_t _startPos,
		           int64_t _endPos) {
			if (m_isOk == false) {
				return false;
			}
			TK_REG_DEBUG("Request parse : " << _startPos << " --> " << _endPos);
			int64_t bufferLength = _SearchIn.size();
			if (_endPos > bufferLength) {
				_endPos = bufferLength;
			}
			if (_startPos > _endPos) {
				return false;
			}
			for (int64_t iii=_startPos; iii<_endPos; iii++) {
				int64_t findLen=0;
				int64_t maxLen = _endPos-iii;
				TK_REG_DEBUG("----------------------------------------------");
				TK_REG_DEBUG("parse element : " << iii << " : '" << _SearchIn[iii] << "'");
				if (m_notBeginWithChar == true) {
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
				regex::FindProperty prop;
				prop.setPositionStart(iii);
				bool needOneMoreCycle = true;
				bool oneCycleDone = false;
				while (needOneMoreCycle == true) {
					needOneMoreCycle = false;
					m_expressionRootNode.parse(_SearchIn, iii, _endPos, prop);
					TK_REG_DEBUG("res=" << prop.getStatus());
					if (    prop.getStatus() == regex::parseStatusNone
					     && m_maximize == true
					     && oneCycleDone == false) {
						// TODO : do it better Patch the case of ".*" search with maximizing
						oneCycleDone = true;
						needOneMoreCycle = true;
					}
					if (    prop.getStatus() == regex::parseStatusFull
					     || prop.getStatus() == regex::parseStatusPartial ) {
						findLen = prop.getFindLen();
						TK_REG_DEBUG_3("main search find : " << findLen << " elements data=" << std::string(_SearchIn, prop.getPositionStart(), prop.getFindLen()));
						// Check end :
						if (m_notEndWithChar == true) {
							TK_REG_DEBUG("Check end is not a char: '" << (char)_SearchIn[iii+findLen] << "'");
							if (_startPos+findLen < (int64_t)_SearchIn.size() ) {
								char32_t tmpVal = _SearchIn[iii+findLen];
								if(    (    tmpVal >= 'a'
								         && tmpVal <= 'z' )
								    || (    tmpVal >= 'A'
								         && tmpVal <= 'Z' )
								    || (    tmpVal >= '0'
								         && tmpVal <= '9' )
								    || (    tmpVal == '_' ) ) {
									// go on the next char ...
									TK_REG_DEBUG("Need one more cycle ...");
									needOneMoreCycle = true;
								}
							}
						}
						if (    m_maximize == true
						     && prop.getStatus() == regex::parseStatusPartial) {
							needOneMoreCycle = true;
						}
						if (needOneMoreCycle == false) {
							m_areaFind.start = iii;
							m_areaFind.stop  = iii + findLen;
							return true;
						}
						if (prop.getStatus() == regex::parseStatusFull) {
							// We really not find the element ==> stop ...
							break;
						}
					}
				}
			}
			return false;
		};
		
		
		bool processOneElement(const CLASS_TYPE& _SearchIn,
		                       int64_t _startPos,
		                       int64_t _endPos) {
			if (m_isOk == false) {
				return false;
			}
			int64_t bufferLength = _SearchIn.size();
			if (_endPos > bufferLength) {
				_endPos = bufferLength;
			}
			if (_startPos > _endPos) {
				return false;
			}
			int64_t findLen=0;
			int64_t maxLen = _endPos-_startPos;
			if (m_notBeginWithChar == true) {
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
			regex::FindProperty prop;
			prop.setPositionStart(_startPos);
			bool needOneMoreCycle = true;
			while (needOneMoreCycle == true) {
				needOneMoreCycle = false;
				m_expressionRootNode.parse(_SearchIn, _startPos, _endPos, prop);
				if (    prop.getStatus() == regex::parseStatusFull
				     || prop.getStatus() == regex::parseStatusPartial ) {
					findLen = prop.getFindLen();
					TK_REG_DEBUG_3("main search find : " << findLen << " elements");
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
								needOneMoreCycle = true;
							}
						}
					}
					if (    m_maximize == true
					     && prop.getStatus() == regex::parseStatusPartial) {
						needOneMoreCycle = true;
					}
					if (needOneMoreCycle == false) {
						m_areaFind.start = _startPos;
						m_areaFind.stop  = _startPos + findLen;
						return true;
					}
					if (prop.getStatus() == regex::parseStatusFull) {
						// We really not find the element ==> stop ...
						return false;
					}
				}
			}
			return false;
		};
		
		
		/**
		 * @brief Get the expression start position detected
		 * @return position of the start regEx
		 */
		int64_t	start() {
			return m_areaFind.start;
		};
		
		/**
		 * @brief Get the expression stop position detected
		 * @return position of the stop regEx
		 */
		int64_t	stop() {
			return m_areaFind.stop;
		};
		
		/**
		 * @brief Display the regEx
		 */
		void display() {
			m_expressionRootNode.display();
		};
		/**
		 * @brief Just display the regEx in color ...
		 */
		void drawColoredRegEx() {
			m_expressionRootNode.drawColoredRegEx();
		}
		/**
		 * @brief Get decorated regular expression. This generate a [class[ewol::compositing::Text]] decoration text. Note that can be use in [class[ewol::widget::Label]].
		 * @return The decorated string
		 */
		std::string getRegExDecorated() {
			return m_expressionRootNode.getColoredRegEx();
		}
	private:
		/**
		 * @brief Check forbidden element in a regular expression element.
		 * @param[in] _tmpExpression The regular expression to check.
		 * @param[in] _pos Position to start the check.
		 * @return true The current node is correct.
		 * @return false An error in parsing has appeared.
		 */
		bool checkGoodPosition(const std::vector<char32_t>& _tmpExpression, int64_t& _pos) {
			char32_t currentCode = _tmpExpression[_pos];
			char32_t endCode = regexOpcodePTheseOut;
			const char *input = "(...)";
			if (currentCode == regexOpcodeBracketIn) {
				endCode = regexOpcodeBracketOut;
				input = "[...]";
			} else if (currentCode == regexOpcodeBraceIn){
				endCode = regexOpcodeBraceOut;
				input = "{x,x}";
			}
			_pos++;
			if (_pos >= (int64_t)_tmpExpression.size()) {
				TK_ERROR("ended with: ( or { or [ ... not permitted");
				return false;
			}
			//TK_DEBUG(" ==> Find ELEMENT : ([{");
			// case dependent:
			int32_t localOffset = 0;
			if (    currentCode == regexOpcodeBracketIn
			     || currentCode == regexOpcodeBraceIn) {
				while(_pos<(int64_t)_tmpExpression.size()) {
					//TK_DEBUG("check : " << tmpExpression[pos]);
					// if we find the end : 
					if (endCode == _tmpExpression[_pos]) {
						return true;
					} else {
						// otherwise, we check the error in the element ...
						char *find = nullptr;
						switch (_tmpExpression[_pos]) {
							case regexOpcodePTheseIn:		find = (char*)"(";			break;
							case regexOpcodeBracketIn:		find = (char*)"[";			break;
							case regexOpcodeBraceIn:		find = (char*)"{";			break;
							case regexOpcodePTheseOut:		find = (char*)")";			break;
							case regexOpcodeBracketOut:		find = (char*)"]";			break;
							case regexOpcodeBraceOut:		find = (char*)"}";			break;
							case regexOpcodeStar:			find = (char*)"*";			break;
							case regexOpcodeDot:			find = (char*)".";			break;
							case regexOpcodeQuestion:		find = (char*)"?";			break;
							case regexOpcodePlus:			find = (char*)"+";			break;
							case regexOpcodePipe:			find = (char*)"|";			break;
							case regexOpcodeEndOfLine:		find = (char*)"$";			break;
							case regexOpcodeDigitNot:		find = (char*)"\\D";		break;
							case regexOpcodeLetterNot:		find = (char*)"\\L";		break;
							case regexOpcodeSpaceNot:		find = (char*)"\\S";		break;
							case regexOpcodeWordNot:		find = (char*)"\\W";		break;
							case regexOpcodeNoChar:		find = (char*)"\\@";		break;
							case regexOpcodeStartOfLine:
								if (    endCode == regexOpcodeBracketOut
								     || localOffset != 0) {
									find = (char*)"^";			break;
								}
							default:													break;
						}
						// Specific element forbidden for (...) but not for [...]
						if (endCode == regexOpcodeBracketOut) {
							switch (_tmpExpression[_pos]) {
								case regexOpcodeDigit:			find = (char*)"\\d";		break;
								case regexOpcodeLetter:		find = (char*)"\\l";		break;
								case regexOpcodeSpace:			find = (char*)"\\s";		break;
								case regexOpcodeWord:			find = (char*)"\\w";		break;
								default:													break;
							}
						}
						if (find != nullptr) {
							(void)input;
							TK_ERROR("can not have : '" << find << "' inside " << input << " element");
							return false;
						}
					}
					_pos++;
					localOffset++;
				}
			} else {
				while(_pos< (int64_t)_tmpExpression.size()) {
					if (endCode == _tmpExpression[_pos]) {
						// find the last element
						return true;
					} else if (	_tmpExpression[_pos] == regexOpcodeBraceOut) {
						TK_ERROR("find } inside a (...) without start {");
						return false;
					} else if (	_tmpExpression[_pos] == regexOpcodeBracketOut) {
						TK_ERROR("find ] inside a (...) without start [");
						return false;
					} else {
						if(    _tmpExpression[_pos] == regexOpcodePTheseIn
						    || _tmpExpression[_pos] == regexOpcodeBracketIn
						    || _tmpExpression[_pos] == regexOpcodeBraceIn ) {
							if (checkGoodPosition(_tmpExpression, _pos) == false ) {
								return false;
							}
						}
					}
					_pos++;
				}
			}
			
			// we did not find the closer...
			if (endCode == regexOpcodeBracketOut) {
				TK_ERROR("Missing ']' at the end");
			}
			if (endCode == regexOpcodeBraceOut) {
				TK_ERROR("Missing '}' at the end");
			}
			if (endCode == regexOpcodePTheseOut) {
				TK_ERROR("Missing ')' at the end");
			}
			return false;
		};
		
		/**
		 * @brief Check all the element in a regular expression ( count [],{},(),...)
		 * @param[in] _tmpExpression Regular expression to check.
		 * @return true The regular expression is correct.
		 * @return false an error occurred in the regular expression.
		 */
		bool checkGoodPosition(const std::vector<char32_t>& _tmpExpression) {
			int64_t pos = 0;
			while (pos < (int64_t)_tmpExpression.size()) {
				//TK_DEBUG("check : " << tmpExpression[pos]);
				if(    _tmpExpression[pos] == regexOpcodePTheseIn
				    || _tmpExpression[pos] == regexOpcodeBracketIn
				    || _tmpExpression[pos] == regexOpcodeBraceIn)
				{
					// attention the i position change inside the function...
					if (checkGoodPosition(_tmpExpression, pos) == false) {
						TK_ERROR("Error at position : " << pos+1 );
						return false;
					} else {
						//TK_DEBUG(" <== Find ELEMENT : ]})");
					}
				} else if(_tmpExpression[pos] == regexOpcodePTheseOut) {
					TK_ERROR("can find ')' with no start : ')'");
					return false;
				} else if(_tmpExpression[pos] == regexOpcodeBracketOut) {
					TK_ERROR("can find ']' with no start : '['");
					return false;
				} else if(_tmpExpression[pos] == regexOpcodeBraceOut) {
					TK_ERROR("can find '}' with no start : '{'");
					return false;
				}
				pos++;
			}
			return true;
		};
	public:
		/* ****************************************************
		 *    == operator
		 *****************************************************/
		bool operator== (const RegEx<CLASS_TYPE>& _obj) const {
			return _obj.m_expressionRequested == m_expressionRequested;
		}
		bool operator!= (const RegEx<CLASS_TYPE>& _obj) const {
			return _obj.m_expressionRequested != m_expressionRequested;
		}


};

}; // end of etk namespace
