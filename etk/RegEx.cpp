/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */


#include <etk/RegEx.hpp>

const struct etk::conversionTable etk::regex::constConversionTable[] = {
	// haveBackSlash, inputValue, newValue
	{ false			, '('  , 0   , etk::regexOpcodePTheseIn},
	{ true			, '('  , '(' , etk::regexOpcodeError},
	{ false			, ')'  , 0   , etk::regexOpcodePTheseOut},
	{ true			, ')'  , ')' , etk::regexOpcodeError},
	{ false			, '['  , 0   , etk::regexOpcodeBracketIn},
	{ true			, '['  , '[' , etk::regexOpcodeError},
	{ false			, ']'  , 0   , etk::regexOpcodeBracketOut},
	{ true			, ']'  , ']' , etk::regexOpcodeError},
	{ false			, '{'  , 0   , etk::regexOpcodeBraceIn},
	{ true			, '{'  , '{' , etk::regexOpcodeError},
	{ false			, '}'  , 0   , etk::regexOpcodeBraceOut},
	{ true			, '}'  , '}' , etk::regexOpcodeError},
	{ false			, '-'  , 0   , etk::regexOpcodeTo},
	{ true			, '-'  , '-' , etk::regexOpcodeError},
	{ false			, '*'  , 0   , etk::regexOpcodeStar},
	{ true			, '*'  , '*' , etk::regexOpcodeError},
	{ false			, '.'  , 0   , etk::regexOpcodeDot},
	{ true			, '.'  , '.' , etk::regexOpcodeError},
	{ true			, 'e'  , 0   , etk::regexOpcodeEOF},
	{ false			, 'e'  , 'e' , etk::regexOpcodeError},
	{ false			, '?'  , 0   , etk::regexOpcodeQuestion},
	{ true			, '?'  , '?' , etk::regexOpcodeError},
	{ false			, '+'  , 0   , etk::regexOpcodePlus},
	{ true			, '+'  , '+' , etk::regexOpcodeError},
	{ false			, '|'  , 0   , etk::regexOpcodePipe},
	{ true			, '|'  , '|' , etk::regexOpcodeError},
	{ false			, '^'  , 0   , etk::regexOpcodeStartOfLine},
	{ true			, '^'  , '^' , etk::regexOpcodeError},
	{ false			, '$'  , 0   , etk::regexOpcodeEndOfLine},
	{ true			, '$'  , '$' , etk::regexOpcodeError},
	{ true			, 'd'  , 0   , etk::regexOpcodeDigit},
	{ true			, 'D'  , 0   , etk::regexOpcodeDigitNot},
	{ true			, 'l'  , 0   , etk::regexOpcodeLetter},
	{ true			, 'L'  , 0   , etk::regexOpcodeLetterNot},
	{ true			, 's'  , 0   , etk::regexOpcodeSpace},
	{ true			, 'S'  , 0   , etk::regexOpcodeSpaceNot},
	{ true			, 'w'  , 0   , etk::regexOpcodeWord},
	{ true			, 'W'  , 0   , etk::regexOpcodeWordNot},
	{ true			, 'a'  , '\a', etk::regexOpcodeError},
	{ true			, 'b'  , '\b', etk::regexOpcodeError},
	{ true			, 'e'  , 0x1B, etk::regexOpcodeError}, // Escape character <Esc>
	{ true			, 'f'  , '\f', etk::regexOpcodeError},
	{ true			, 'n'  , '\n', etk::regexOpcodeError},
	{ true			, 'r'  , '\r', etk::regexOpcodeError},
	{ true			, 't'  , '\t', etk::regexOpcodeError},
	{ true			, 'v'  , '\v', etk::regexOpcodeError},
	{ true			, '\\' , '\\', etk::regexOpcodeError},
	{ true			, '&'  , '&' , etk::regexOpcodeError},
	{ true			, '0'  , '\0', etk::regexOpcodeError},
	{ true			, '@'  , 0   , etk::regexOpcodeNoChar},
};
const int64_t etk::regex::constConversionTableSize = sizeof(etk::regex::constConversionTable) / sizeof(struct etk::conversionTable) ;

static const char* parseStatusTable[] = {
	"parseStatusUnknown",
	"parseStatusNone",
	"parseStatusPartial",
	"parseStatusFull"
};
std::ostream& etk::regex::operator <<(std::ostream& _os, enum etk::regex::parseStatus _obj) {
	_os << parseStatusTable[_obj];
	return _os;
}
std::ostream& etk::regex::operator <<(std::ostream& _os, const etk::regex::FindProperty& _obj) {
	_os << "property([" << _obj.getPositionStart() << "," << _obj.getPositionStop() << "]*" << _obj.getMultiplicity() << " " << _obj.getStatus() << ")";
	return _os;
}

std::string etk::regex::createString(const std::vector<char32_t>& _data, int64_t _start, int64_t _stop) {
	std::string output(ETK_BASH_COLOR_NORMAL);
	for (int64_t iii=_start; iii<(int64_t)_data.size() && iii<_stop ; iii++) {
		switch(_data[iii]) {
			case regexOpcodePTheseIn:          output += std::string(ETK_BASH_COLOR_RED)		+ (char*)"(" + ETK_BASH_COLOR_NORMAL;		break;
			case regexOpcodePTheseOut:         output += std::string(ETK_BASH_COLOR_RED)		+ (char*)")" + ETK_BASH_COLOR_NORMAL;		break;
			case regexOpcodeBracketIn:         output += std::string(ETK_BASH_COLOR_YELLOW)	+ (char*)"[" + ETK_BASH_COLOR_NORMAL;		break;
			case regexOpcodeBracketOut:        output += std::string(ETK_BASH_COLOR_YELLOW)	+ (char*)"]" + ETK_BASH_COLOR_NORMAL;		break;
			case regexOpcodeTo:                output += std::string(ETK_BASH_COLOR_YELLOW)	+ (char*)"-" + ETK_BASH_COLOR_NORMAL;		break;
			case regexOpcodeBraceIn:           output += std::string(ETK_BASH_COLOR_GREEN)		+ (char*)"{" + ETK_BASH_COLOR_NORMAL;		break;
			case regexOpcodeBraceOut:          output += std::string(ETK_BASH_COLOR_GREEN)		+ (char*)"}" + ETK_BASH_COLOR_NORMAL;		break;
			case regexOpcodeStar:              output += std::string(ETK_BASH_COLOR_BLUE)		+ (char*)"*" + ETK_BASH_COLOR_NORMAL;		break;
			case regexOpcodeDot:               output += std::string(ETK_BASH_COLOR_BLUE)		+ (char*)"." + ETK_BASH_COLOR_NORMAL;		break;
			case regexOpcodeQuestion:          output += std::string(ETK_BASH_COLOR_BLUE)		+ (char*)"?" + ETK_BASH_COLOR_NORMAL;		break;
			case regexOpcodePlus:              output += std::string(ETK_BASH_COLOR_BLUE)		+ (char*)"+" + ETK_BASH_COLOR_NORMAL;		break;
			case regexOpcodePipe:              output += std::string(ETK_BASH_COLOR_BLUE)		+ (char*)"|" + ETK_BASH_COLOR_NORMAL;		break;
			case regexOpcodeNoChar:            output += std::string(ETK_BASH_COLOR_MAGENTA)	+ (char*)"@" + ETK_BASH_COLOR_NORMAL;		break;
			case regexOpcodeStartOfLine:       output += std::string(ETK_BASH_COLOR_MAGENTA)	+ (char*)"^" + ETK_BASH_COLOR_NORMAL;		break;
			case regexOpcodeEndOfLine:         output += std::string(ETK_BASH_COLOR_MAGENTA)	+ (char*)"$" + ETK_BASH_COLOR_NORMAL;		break;
			case regexOpcodeDigit:             output += std::string(ETK_BASH_COLOR_MAGENTA)	+ (char*)"\\d" + ETK_BASH_COLOR_NORMAL;	break;
			case regexOpcodeDigitNot:          output += std::string(ETK_BASH_COLOR_MAGENTA)	+ (char*)"\\D" + ETK_BASH_COLOR_NORMAL;	break;
			case regexOpcodeLetter:            output += std::string(ETK_BASH_COLOR_MAGENTA)	+ (char*)"\\l" + ETK_BASH_COLOR_NORMAL;	break;
			case regexOpcodeLetterNot:         output += std::string(ETK_BASH_COLOR_MAGENTA)	+ (char*)"\\L" + ETK_BASH_COLOR_NORMAL;	break;
			case regexOpcodeSpace:             output += std::string(ETK_BASH_COLOR_MAGENTA)	+ (char*)"\\s" + ETK_BASH_COLOR_NORMAL;	break;
			case regexOpcodeSpaceNot:          output += std::string(ETK_BASH_COLOR_MAGENTA)	+ (char*)"\\S" + ETK_BASH_COLOR_NORMAL;	break;
			case regexOpcodeWord:              output += std::string(ETK_BASH_COLOR_MAGENTA)	+ (char*)"\\w" + ETK_BASH_COLOR_NORMAL;	break;
			case regexOpcodeWordNot:           output += std::string(ETK_BASH_COLOR_MAGENTA)	+ (char*)"\\W" + ETK_BASH_COLOR_NORMAL;	break;
			case regexOpcodeEOF:               output += std::string(ETK_BASH_COLOR_MAGENTA)	+ (char*)"\\e" + ETK_BASH_COLOR_NORMAL;	break;
			case '\n':                          output += std::string(ETK_BASH_COLOR_MAGENTA)	+ (char*)"\\n" + ETK_BASH_COLOR_NORMAL;	break;
			case '\t':                          output += std::string(ETK_BASH_COLOR_MAGENTA)	+ (char*)"\\t" + ETK_BASH_COLOR_NORMAL;	break;
			default:
				char plop[10];
				int8_t nb = u32char::convertUtf8(_data[iii], plop);
				plop[nb] = '\0';
				output += plop;
				break;
		}
	}
	return output;
}

char* etk::regex::levelSpace(uint32_t _level) {
	static char* tmpSpace = "                                                            ";
	if (_level>30) {
		return tmpSpace;
	}
	return tmpSpace + 60 - 2*_level;
}


int64_t etk::regex::getLenOfPTheseElement(const std::vector<char32_t>& _data, int64_t _startPos) {
	if (_startPos>=(int64_t)_data.size()){
		return 0;
	}
	int64_t pos = _startPos;
	int32_t nbOpen = 0;
	// special case of the (...) or | ==> we search '|' or ')'
	if(    _data[pos] == regexOpcodePTheseOut
	    || _data[pos] == regexOpcodePipe) {
		return 0;
	}
	// find size ...
	while (pos < (int64_t)_data.size() ) {
		if(_data[pos] == regexOpcodePTheseIn) {
			// find a sub section : 
			nbOpen++;
		} else if(0 < nbOpen) {
			if (_data[pos] == regexOpcodePTheseOut) {
				nbOpen--;
				if (0 > nbOpen) {
					TK_ERROR("Error in the (...) find element at "<< pos);
					return -1;
				}
			}
		} else if(    _data[pos] == regexOpcodePTheseOut
		           || _data[pos] == regexOpcodePipe) {
			// Find the end of the (...)
			// just return the size inside
			int32_t sizeInside = pos - _startPos;
			if (0 >= sizeInside) {
				TK_ERROR("Error in the (...) no data at "<< pos-1);
				return 0;
			}
			return sizeInside;
		}
		pos++;
	}
	return pos - _startPos;
}

int64_t etk::regex::getLenOfPThese(const std::vector<char32_t>& _data, int64_t _startPos) {
	int64_t pos = _startPos;
	int32_t nbOpen = 0;
	// special case of the (...) or | ==> we search '|' or ')'
	if(_data[pos]==regexOpcodePTheseOut) {
		return 0;
	}
	if(_data[pos]!=regexOpcodePTheseIn) {
		TK_ERROR(" find error in  PThese");
		return 0;
	}
	pos++;
	// find size ...
	while (pos < (int64_t)_data.size() ) {
		if(_data[pos]==regexOpcodePTheseIn) {
			// find a sub section : 
			nbOpen++;
		} else if(0 < nbOpen) {
			if (_data[pos]==regexOpcodePTheseOut) {
				nbOpen--;
				if (0 > nbOpen) {
					TK_ERROR("Error in the (...) find element at "<< pos);
					return 0;
				}
			}
		} else if(_data[pos]==regexOpcodePTheseOut) {
			// Find the end of the (...)
			// just return the size inside
			int32_t sizeInside = pos - _startPos-1;
			if (0 >= sizeInside) {
				TK_ERROR("Error in the (...) no data at "<< pos-1);
				return 0;
			}
			return sizeInside;
		}
		pos++;
	}
	return 0;
}


int64_t etk::regex::getLenOfBracket(const std::vector<char32_t>& _data, int64_t _startPos) {
	int64_t pos = _startPos;
	// special case of the (...) or | ==> we search '|' or ')'
	if(_data[pos]==regexOpcodeBracketOut) {
		return 0;
	}
	if(_data[pos] != regexOpcodeBracketIn) {
		TK_ERROR("find no [...");
		return 0;
	}
	pos++;
	// find size ...
	while (pos < (int64_t)_data.size() ) {
		if(_data[pos] == regexOpcodeBracketOut) {
			// Find the end of the [...]
			// just return the size inside
			int32_t sizeInside = pos - _startPos -1 ;
			if (0 >= sizeInside) {
				TK_ERROR("Error in the [...] no data at "<< pos-1);
				return 0;
			}
			return sizeInside;
		} else if (    _data[pos] == regexOpcodeStartOfLine
		            || _data[pos] == regexOpcodeDigit
		            || _data[pos] == regexOpcodeLetter
		            || _data[pos] == regexOpcodeSpace
		            || _data[pos] == regexOpcodeWord
		            || _data[pos] == regexOpcodeTo) {
			// nothing to do ... it is permitted
		} else if(_data[pos] > 0xFF ) {
			std::string displayElement;
			if (_data[pos] == regexOpcodeStartOfLine) {
				displayElement = "^";
			} else if (_data[pos] == regexOpcodeDigitNot) {
				displayElement = "\\D";
			} else if (_data[pos] == regexOpcodeLetterNot) {
				displayElement = "\\L";
			} else if (_data[pos] == regexOpcodeSpaceNot) {
				displayElement = "\\S";
			} else if (_data[pos] == regexOpcodeWordNot) {
				displayElement = "\\W";
			} else {
				displayElement = (char)_data[pos];
			}
			TK_ERROR("Error in the [...] not permitted element at "<< pos << " '" << displayElement << "'");
			return 0;
		}
		pos++;
	}
	return 0;
}


int64_t etk::regex::getLenOfBrace(const std::vector<char32_t>& _data, int64_t _startPos) {
	int32_t pos = _startPos;
	// special case of the (...) or | ==> we search '|' or ')'
	if(_data[pos]==regexOpcodeBraceOut) {
		return 0;
	}
	if(_data[pos]!=regexOpcodeBraceIn) {
		TK_ERROR(" did not find brace IN { ");
		return 0;
	}
	pos++;
	// find size ...
	while (pos < (int64_t)_data.size() ) {
		if(_data[pos]==regexOpcodeBraceOut) {
			// Find the end of the [...]
			// just return the size inside
			int32_t sizeInside = pos - _startPos -1 ;
			if (0 >= sizeInside) {
				TK_ERROR("Error in the {...} no data at "<< pos-1);
				return 0;
			}
			return sizeInside;
		} else if(    _data[pos] != ','
		           && (    _data[pos] < '0'
		                || _data[pos] > '9') ) {
			TK_ERROR("Error in the {...} not permitted element at "<< pos << " '" << _data[pos] << "'");
			return 0;
		}
		pos++;
	}
	return 0;
}


int64_t etk::regex::getLenOfNormal(const std::vector<char32_t>& _data, int64_t _startPos) {
	int64_t pos = _startPos;
	// find size ...
	while (pos < (int64_t)_data.size() ) {
		switch(_data[pos]) {
			case regexOpcodePTheseIn:
			case regexOpcodePTheseOut:
			case regexOpcodeBracketIn:
			case regexOpcodeBracketOut:
			case regexOpcodeBraceIn:
			case regexOpcodeBraceOut:
			case regexOpcodeTo:
			case regexOpcodeStar:
			case regexOpcodeDot:
			case regexOpcodeQuestion:
			case regexOpcodePlus:
			case regexOpcodePipe:
			case regexOpcodeStartOfLine:
			case regexOpcodeEndOfLine:
			case regexOpcodeDigit:
			case regexOpcodeDigitNot:
			case regexOpcodeLetter:
			case regexOpcodeLetterNot:
			case regexOpcodeSpace:
			case regexOpcodeSpaceNot:
			case regexOpcodeWord:
			case regexOpcodeWordNot:
				{
					// just return the size inside
					int32_t sizeInside = pos - _startPos;
					if (0 >= sizeInside) {
						TK_ERROR("Error in the normal data :  no data ...");
					}
					return sizeInside;
				}
				break;
			default :
				// nothing to do ...
				break;
		}
		pos++;
	}
	if ((int64_t)pos - (int64_t)_startPos < 0) {
		return 0;
	}
	return pos - _startPos ;
}


bool etk::regex::parseBrace(const std::vector<char32_t>& _data, uint32_t& _min, uint32_t& _max) {
	int64_t k=0;
	int32_t firstElement = 0;
	int32_t SecondElement = 0;
	while(k < (int64_t)_data.size()) {
		if (_data[k] == ',') {
			k++;
			break;
		} if (_data[k] == '}' ) {
			SecondElement = firstElement;
			goto allIsSet;
		} else if(u32char::isInteger(_data[k]) == true) {
			firstElement *= 10;
			firstElement += u32char::toInt(_data[k]);
		} else {
			TK_ERROR("Can not parse this element " << (char)_data[k] << " at pos " << k);
			return false;
		}
		k++;
	}
	if (k == (int64_t)_data.size()) {
		SecondElement = firstElement;
	}
	while(k < (int64_t)_data.size()) {
		if (_data[k] == ',') {
			TK_ERROR("Can not find a second , in {} at pos " << k);
			return false;
		} if (_data[k] == '}') {
			goto allIsSet;
		} else if (true == u32char::isInteger(_data[k])) {
			SecondElement *= 10;
			SecondElement += u32char::toInt(_data[k]);
		} else {
			TK_ERROR("Can not parse this element " << _data[k] << " at pos " << k);
			return false;
		}
		k++;
	}
	
allIsSet:
	if (SecondElement == 0 && firstElement != 0) {
		_min = 0;
		_max = firstElement;
	} else {
		_min = firstElement;
		_max = SecondElement;
	}
	if (_min > _max) {
		TK_ERROR("Minimum=" << _min << " can not be < maximum=" << _max );
		return false;
	}
	return true;
}

std::string etk::regex::autoStr(const std::string& _data) {
	std::string out;
	for (auto &it : _data) {
		if (it == '\n') {
			out += "\\n";
		} else if (it == '\t') {
			out += "\\t";
		} else if (it == '\r') {
			out += "\\r";
		} else if (it == '\0') {
			out += "\\0";
		} else if (it == ' ') {
			out += " ";
		} else if (it <= 0x20) {
			out += std::to_string((int32_t)it);
		} else {
			out += it;
		}
	}
	return out;
}


std::string etk::regex::autoStr(char _data) {
	std::string out;
	if (_data == '\n') {
		out += "\\n";
	} else if (_data == '\t') {
		out += "\\t";
	} else if (_data == '\r') {
		out += "\\r";
	} else if (_data == '\0') {
		out += "\\0";
	} else if (_data == ' ') {
		out += " ";
	} else if (_data <= 0x20) {
		out += std::to_string((int32_t)_data);
	} else {
		out += _data;
	}
	return out;
}

std::string etk::regex::strTick(int32_t _pos) {
	std::string out;
	for (int32_t iii=0; iii<_pos; ++iii) {
		out += " ";
	}
	out += "^";
	return out;
}



namespace etk {
	template<> std::string to_string<etk::RegEx<std::string>>(const etk::RegEx<std::string>& _val) {
		return _val.getRegEx();
	}
	template<> std::string to_string<etk::RegEx<std::u32string>>(const etk::RegEx<std::u32string>& _val) {
		return _val.getRegEx();
	}
	template<> std::u32string to_u32string<etk::RegEx<std::string>>(const etk::RegEx<std::string>& _val) {
		return _val.getURegEx();
	}
	template<> std::u32string to_u32string<etk::RegEx<std::u32string>>(const etk::RegEx<std::u32string>& _val) {
		return _val.getURegEx();
	}
	
	template<> bool from_string<etk::RegEx<std::string>>(etk::RegEx<std::string>& _variableRet, const std::u32string& _value) {
		_variableRet.compile(_value);
		return true;
	}
	template<> bool from_string<etk::RegEx<std::u32string>>(etk::RegEx<std::u32string>& _variableRet, const std::u32string& _value) {
		_variableRet.compile(_value);
		return true;
	}
	template<> bool from_string<etk::RegEx<std::string>>(etk::RegEx<std::string>& _variableRet, const std::string& _value) {
		_variableRet.compile(_value);
		return true;
	}
	template<> bool from_string<etk::RegEx<std::u32string>>(etk::RegEx<std::u32string>& _variableRet, const std::string& _value) {
		_variableRet.compile(_value);
		return true;
	}
};