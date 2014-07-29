/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */


#include <etk/RegExp.h>



const struct etk::convertionTable etk::regexp::constConvertionTable[] = {
	// haveBackSlash, inputValue, newValue
	{ false			, '('  , 0   , etk::regexpOpcodePTheseIn},
	{ true			, '('  , '(' , etk::regexpOpcodeError},
	{ false			, ')'  , 0   , etk::regexpOpcodePTheseOut},
	{ true			, ')'  , ')' , etk::regexpOpcodeError},
	{ false			, '['  , 0   , etk::regexpOpcodeBracketIn},
	{ true			, '['  , '[' , etk::regexpOpcodeError},
	{ false			, ']'  , 0   , etk::regexpOpcodeBracketOut},
	{ true			, ']'  , ']' , etk::regexpOpcodeError},
	{ false			, '{'  , 0   , etk::regexpOpcodeBracetIn},
	{ true			, '{'  , '{' , etk::regexpOpcodeError},
	{ false			, '}'  , 0   , etk::regexpOpcodeBracetOut},
	{ true			, '}'  , '}' , etk::regexpOpcodeError},
	{ false			, '-'  , 0   , etk::regexpOpcodeTo},
	{ true			, '-'  , '-' , etk::regexpOpcodeError},
	{ false			, '*'  , 0   , etk::regexpOpcodeStar},
	{ true			, '*'  , '*' , etk::regexpOpcodeError},
	{ false			, '.'  , 0   , etk::regexpOpcodeDot},
	{ true			, '.'  , '.' , etk::regexpOpcodeError},
	{ false			, '?'  , 0   , etk::regexpOpcodeQuestion},
	{ true			, '?'  , '?' , etk::regexpOpcodeError},
	{ false			, '+'  , 0   , etk::regexpOpcodePlus},
	{ true			, '+'  , '+' , etk::regexpOpcodeError},
	{ false			, '|'  , 0   , etk::regexpOpcodePipe},
	{ true			, '|'  , '|' , etk::regexpOpcodeError},
	{ false			, '^'  , 0   , etk::regexpOpcodeStartOfLine},
	{ true			, '^'  , '^' , etk::regexpOpcodeError},
	{ false			, '$'  , 0   , etk::regexpOpcodeEndOfLine},
	{ true			, '$'  , '$' , etk::regexpOpcodeError},
	{ true			, 'd'  , 0   , etk::regexpOpcodeDigit},
	{ true			, 'D'  , 0   , etk::regexpOpcodeDigitNot},
	{ true			, 'l'  , 0   , etk::regexpOpcodeLetter},
	{ true			, 'L'  , 0   , etk::regexpOpcodeLetterNot},
	{ true			, 's'  , 0   , etk::regexpOpcodeSpace},
	{ true			, 'S'  , 0   , etk::regexpOpcodeSpaceNot},
	{ true			, 'w'  , 0   , etk::regexpOpcodeWord},
	{ true			, 'W'  , 0   , etk::regexpOpcodeWordNot},
	{ true			, 'a'  , '\a', etk::regexpOpcodeError},
	{ true			, 'b'  , '\b', etk::regexpOpcodeError},
	{ true			, 'e'  , 0x1B, etk::regexpOpcodeError}, // Escape character <Esc>
	{ true			, 'f'  , '\f', etk::regexpOpcodeError},
	{ true			, 'n'  , '\n', etk::regexpOpcodeError},
	{ true			, 'r'  , '\r', etk::regexpOpcodeError},
	{ true			, 't'  , '\t', etk::regexpOpcodeError},
	{ true			, 'v'  , '\v', etk::regexpOpcodeError},
	{ true			, '\\' , '\\', etk::regexpOpcodeError},
	{ true			, '&'  , '&' , etk::regexpOpcodeError},
	{ true			, '0'  , '\0', etk::regexpOpcodeError},
	{ true			, '@'  , 0   , etk::regexpOpcodeNoChar},
};
const int64_t etk::regexp::constConvertionTableSize = sizeof(etk::regexp::constConvertionTable) / sizeof(struct etk::convertionTable) ;

static const char* parseStatusTable[] = {
	"parseStatusUnknow",
	"parseStatusNone",
	"parseStatusPartial",
	"parseStatusFull"
};
std::ostream& etk::regexp::operator <<(std::ostream& _os, enum etk::regexp::parseStatus _obj) {
	_os << parseStatusTable[_obj];
	return _os;
}
std::ostream& etk::regexp::operator <<(std::ostream& _os, const etk::regexp::FindProperty& _obj) {
	_os << "property([" << _obj.getPositionStart() << "," << _obj.getPositionStop() << "]*" << _obj.getMultiplicity() << " " << _obj.getStatus() << ")";
	return _os;
}

std::string etk::regexp::createString(const std::vector<char32_t>& _data, int64_t _start, int64_t _stop) {
	std::string output(ETK_BASH_COLOR_NORMAL);
	for (int64_t iii=_start; iii<(int64_t)_data.size() && iii<_stop ; iii++) {
		switch(_data[iii]) {
			case regexpOpcodePTheseIn:		output += std::string(ETK_BASH_COLOR_RED)		+ (char*)"(" + ETK_BASH_COLOR_NORMAL;		break;
			case regexpOpcodePTheseOut:		output += std::string(ETK_BASH_COLOR_RED)		+ (char*)")" + ETK_BASH_COLOR_NORMAL;		break;
			case regexpOpcodeBracketIn:		output += std::string(ETK_BASH_COLOR_YELLOW)	+ (char*)"[" + ETK_BASH_COLOR_NORMAL;		break;
			case regexpOpcodeBracketOut:	output += std::string(ETK_BASH_COLOR_YELLOW)	+ (char*)"]" + ETK_BASH_COLOR_NORMAL;		break;
			case regexpOpcodeTo:			output += std::string(ETK_BASH_COLOR_YELLOW)	+ (char*)"-" + ETK_BASH_COLOR_NORMAL;		break;
			case regexpOpcodeBracetIn:		output += std::string(ETK_BASH_COLOR_GREEN)		+ (char*)"{" + ETK_BASH_COLOR_NORMAL;		break;
			case regexpOpcodeBracetOut:		output += std::string(ETK_BASH_COLOR_GREEN)		+ (char*)"}" + ETK_BASH_COLOR_NORMAL;		break;
			case regexpOpcodeStar:			output += std::string(ETK_BASH_COLOR_BLUE)		+ (char*)"*" + ETK_BASH_COLOR_NORMAL;		break;
			case regexpOpcodeDot:			output += std::string(ETK_BASH_COLOR_BLUE)		+ (char*)"." + ETK_BASH_COLOR_NORMAL;		break;
			case regexpOpcodeQuestion:		output += std::string(ETK_BASH_COLOR_BLUE)		+ (char*)"?" + ETK_BASH_COLOR_NORMAL;		break;
			case regexpOpcodePlus:			output += std::string(ETK_BASH_COLOR_BLUE)		+ (char*)"+" + ETK_BASH_COLOR_NORMAL;		break;
			case regexpOpcodePipe:			output += std::string(ETK_BASH_COLOR_BLUE)		+ (char*)"|" + ETK_BASH_COLOR_NORMAL;		break;
			case regexpOpcodeNoChar:		output += std::string(ETK_BASH_COLOR_MAGENTA)	+ (char*)"@" + ETK_BASH_COLOR_NORMAL;		break;
			case regexpOpcodeStartOfLine:	output += std::string(ETK_BASH_COLOR_MAGENTA)	+ (char*)"^" + ETK_BASH_COLOR_NORMAL;		break;
			case regexpOpcodeEndOfLine:		output += std::string(ETK_BASH_COLOR_MAGENTA)	+ (char*)"$" + ETK_BASH_COLOR_NORMAL;		break;
			case regexpOpcodeDigit:			output += std::string(ETK_BASH_COLOR_MAGENTA)	+ (char*)"\\d" + ETK_BASH_COLOR_NORMAL;	break;
			case regexpOpcodeDigitNot:		output += std::string(ETK_BASH_COLOR_MAGENTA)	+ (char*)"\\D" + ETK_BASH_COLOR_NORMAL;	break;
			case regexpOpcodeLetter:		output += std::string(ETK_BASH_COLOR_MAGENTA)	+ (char*)"\\l" + ETK_BASH_COLOR_NORMAL;	break;
			case regexpOpcodeLetterNot:		output += std::string(ETK_BASH_COLOR_MAGENTA)	+ (char*)"\\L" + ETK_BASH_COLOR_NORMAL;	break;
			case regexpOpcodeSpace:			output += std::string(ETK_BASH_COLOR_MAGENTA)	+ (char*)"\\s" + ETK_BASH_COLOR_NORMAL;	break;
			case regexpOpcodeSpaceNot:		output += std::string(ETK_BASH_COLOR_MAGENTA)	+ (char*)"\\S" + ETK_BASH_COLOR_NORMAL;	break;
			case regexpOpcodeWord:			output += std::string(ETK_BASH_COLOR_MAGENTA)	+ (char*)"\\w" + ETK_BASH_COLOR_NORMAL;	break;
			case regexpOpcodeWordNot:		output += std::string(ETK_BASH_COLOR_MAGENTA)	+ (char*)"\\W" + ETK_BASH_COLOR_NORMAL;	break;
			case '\n':						output += std::string(ETK_BASH_COLOR_MAGENTA)	+ (char*)"\\n" + ETK_BASH_COLOR_NORMAL;	break;
			case '\t':						output += std::string(ETK_BASH_COLOR_MAGENTA)	+ (char*)"\\t" + ETK_BASH_COLOR_NORMAL;	break;
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

char* etk::regexp::levelSpace(uint32_t _level) {
	static char* tmpSpace = "                                                            ";
	if (_level>30) {
		return tmpSpace;
	}
	return tmpSpace + 60 - 2*_level;
}


int64_t etk::regexp::getLenOfPTheseElem(const std::vector<char32_t>& _data, int64_t _startPos) {
	if (_startPos>=(int64_t)_data.size()){
		return 0;
	}
	int64_t pos = _startPos;
	int32_t nbOpen = 0;
	// special case of the (...) or | ==> we search '|' or ')'
	if(    _data[pos] == regexpOpcodePTheseOut
	    || _data[pos] == regexpOpcodePipe) {
		return 0;
	}
	// find size ...
	while (pos < (int64_t)_data.size() ) {
		if(_data[pos] == regexpOpcodePTheseIn) {
			// find a sub section : 
			nbOpen++;
		} else if(0 < nbOpen) {
			if (_data[pos] == regexpOpcodePTheseOut) {
				nbOpen--;
				if (0 > nbOpen) {
					TK_ERROR("Error in the (...) find element at "<< pos);
					return -1;
				}
			}
		} else if(    _data[pos] == regexpOpcodePTheseOut
		           || _data[pos] == regexpOpcodePipe) {
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

int64_t etk::regexp::getLenOfPThese(const std::vector<char32_t>& _data, int64_t _startPos) {
	int64_t pos = _startPos;
	int32_t nbOpen = 0;
	// special case of the (...) or | ==> we search '|' or ')'
	if(_data[pos]==regexpOpcodePTheseOut) {
		return 0;
	}
	if(_data[pos]!=regexpOpcodePTheseIn) {
		TK_ERROR(" find error in  PThese");
		return 0;
	}
	pos++;
	// find size ...
	while (pos < (int64_t)_data.size() ) {
		if(_data[pos]==regexpOpcodePTheseIn) {
			// find a sub section : 
			nbOpen++;
		} else if(0 < nbOpen) {
			if (_data[pos]==regexpOpcodePTheseOut) {
				nbOpen--;
				if (0 > nbOpen) {
					TK_ERROR("Error in the (...) find element at "<< pos);
					return 0;
				}
			}
		} else if(_data[pos]==regexpOpcodePTheseOut) {
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


int64_t etk::regexp::getLenOfBracket(const std::vector<char32_t>& _data, int64_t _startPos) {
	int64_t pos = _startPos;
	// special case of the (...) or | ==> we search '|' or ')'
	if(_data[pos]==regexpOpcodeBracketOut) {
		return 0;
	}
	if(_data[pos] != regexpOpcodeBracketIn) {
		TK_ERROR("find no {...");
		return 0;
	}
	pos++;
	// find size ...
	while (pos < (int64_t)_data.size() ) {
		if(_data[pos]==regexpOpcodeBracketOut) {
			// Find the end of the [...]
			// just return the size inside
			int32_t sizeInside = pos - _startPos -1 ;
			if (0 >= sizeInside) {
				TK_ERROR("Error in the [...] no data at "<< pos-1);
				return 0;
			}
			return sizeInside;
		} else if(    _data[pos] != regexpOpcodeTo
		           && _data[pos] > 0xFF ) {
			TK_ERROR("Error in the [...] not permited element at "<< pos << " '" << (char)_data[pos] << "'");
			return 0;
		}
		pos++;
	}
	return 0;
}


int64_t etk::regexp::getLenOfBrace(const std::vector<char32_t>& _data, int64_t _startPos) {
	int32_t pos = _startPos;
	// special case of the (...) or | ==> we search '|' or ')'
	if(_data[pos]==regexpOpcodeBracetOut) {
		return 0;
	}
	if(_data[pos]!=regexpOpcodeBracetIn) {
		TK_ERROR(" did not find brace IN { ");
		return 0;
	}
	pos++;
	// find size ...
	while (pos < (int64_t)_data.size() ) {
		if(_data[pos]==regexpOpcodeBracetOut) {
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
			TK_ERROR("Error in the {...} not permited element at "<< pos << " '" << _data[pos] << "'");
			return 0;
		}
		pos++;
	}
	return 0;
}


int64_t etk::regexp::getLenOfNormal(const std::vector<char32_t>& _data, int64_t _startPos) {
	int64_t pos = _startPos;
	// find size ...
	while (pos < (int64_t)_data.size() ) {
		switch(_data[pos]) {
			case regexpOpcodePTheseIn:
			case regexpOpcodePTheseOut:
			case regexpOpcodeBracketIn:
			case regexpOpcodeBracketOut:
			case regexpOpcodeBracetIn:
			case regexpOpcodeBracetOut:
			case regexpOpcodeTo:
			case regexpOpcodeStar:
			case regexpOpcodeDot:
			case regexpOpcodeQuestion:
			case regexpOpcodePlus:
			case regexpOpcodePipe:
			case regexpOpcodeStartOfLine:
			case regexpOpcodeEndOfLine:
			case regexpOpcodeDigit:
			case regexpOpcodeDigitNot:
			case regexpOpcodeLetter:
			case regexpOpcodeLetterNot:
			case regexpOpcodeSpace:
			case regexpOpcodeSpaceNot:
			case regexpOpcodeWord:
			case regexpOpcodeWordNot:
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


bool etk::regexp::parseBrace(const std::vector<char32_t>& _data, uint32_t& _min, uint32_t& _max) {
	//TK_INFO("parse {...} in "; DisplayElem(data); );
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

std::string etk::regexp::autoStr(const std::string& _data) {
	std::string out;
	for (auto &it : _data) {
		if (it == '\n') {
			out += "\\n";
		} else if (it == '\t') {
			out += "\\t";
		} else if (it == '\r') {
			out += "\\r";
		} else {
			out += it;
		}
	}
	return out;
}


std::string etk::regexp::autoStr(char _data) {
	std::string out;
	if (_data == '\n') {
		out += "\\n";
	} else if (_data == '\t') {
		out += "\\t";
	} else if (_data == '\r') {
		out += "\\r";
	} else {
		out += _data;
	}
	return out;
}

std::string etk::regexp::strTick(int32_t _pos) {
	std::string out;
	for (int32_t iii=0; iii<_pos; ++iii) {
		out += " ";
	}
	out += "^";
	return out;
}