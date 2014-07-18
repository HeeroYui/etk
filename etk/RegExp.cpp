/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */


#include <etk/RegExp.h>



const struct etk::convertionTable etk::constConvertionTable[] = {
	// haveBackSlash, inputValue, newValue
	{ false			, '('  , 0   , regexpOpcodePTheseIn},
	{ true			, '('  , '(' , regexpOpcodeError},
	{ false			, ')'  , 0   , regexpOpcodePTheseOut},
	{ true			, ')'  , ')' , regexpOpcodeError},
	{ false			, '['  , 0   , regexpOpcodeBracketIn},
	{ true			, '['  , '[' , regexpOpcodeError},
	{ false			, ']'  , 0   , regexpOpcodeBracketOut},
	{ true			, ']'  , ']' , regexpOpcodeError},
	{ false			, '{'  , 0   , regexpOpcodeBracetIn},
	{ true			, '{'  , '{' , regexpOpcodeError},
	{ false			, '}'  , 0   , regexpOpcodeBracetOut},
	{ true			, '}'  , '}' , regexpOpcodeError},
	{ false			, '-'  , 0   , regexpOpcodeTo},
	{ true			, '-'  , '-' , regexpOpcodeError},
	{ false			, '*'  , 0   , regexpOpcodeStar},
	{ true			, '*'  , '*' , regexpOpcodeError},
	{ false			, '.'  , 0   , regexpOpcodeDot},
	{ true			, '.'  , '.' , regexpOpcodeError},
	{ false			, '?'  , 0   , regexpOpcodeQuestion},
	{ true			, '?'  , '?' , regexpOpcodeError},
	{ false			, '+'  , 0   , regexpOpcodePlus},
	{ true			, '+'  , '+' , regexpOpcodeError},
	{ false			, '|'  , 0   , regexpOpcodePipe},
	{ true			, '|'  , '|' , regexpOpcodeError},
	{ false			, '^'  , 0   , regexpOpcodeStartOfLine},
	{ true			, '^'  , '^' , regexpOpcodeError},
	{ false			, '$'  , 0   , regexpOpcodeEndOfLine},
	{ true			, '$'  , '$' , regexpOpcodeError},
	{ true			, 'd'  , 0   , regexpOpcodeDigit},
	{ true			, 'D'  , 0   , regexpOpcodeDigitNot},
	{ true			, 'l'  , 0   , regexpOpcodeLetter},
	{ true			, 'L'  , 0   , regexpOpcodeLetterNot},
	{ true			, 's'  , 0   , regexpOpcodeSpace},
	{ true			, 'S'  , 0   , regexpOpcodeSpaceNot},
	{ true			, 'w'  , 0   , regexpOpcodeWord},
	{ true			, 'W'  , 0   , regexpOpcodeWordNot},
	{ true			, 'a'  , '\a', regexpOpcodeError},
	{ true			, 'b'  , '\b', regexpOpcodeError},
	{ true			, 'e'  , 0x1B, regexpOpcodeError}, // Escape character <Esc>
	{ true			, 'f'  , '\f', regexpOpcodeError},
	{ true			, 'n'  , '\n', regexpOpcodeError},
	{ true			, 'r'  , '\r', regexpOpcodeError},
	{ true			, 't'  , '\t', regexpOpcodeError},
	{ true			, 'v'  , '\v', regexpOpcodeError},
	{ true			, '\\' , '\\', regexpOpcodeError},
	{ true			, '&'  , '&' , regexpOpcodeError},
	{ true			, '0'  , '\0', regexpOpcodeError},
	{ true			, '@'  , 0   , regexpOpcodeNoChar},
};
const int64_t etk::constConvertionTableSize = sizeof(etk::constConvertionTable) / sizeof(struct etk::convertionTable) ;


std::string etk::createString(const std::vector<char32_t>& _data, int64_t _start, int64_t _stop) {
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

char * etk::levelSpace(uint32_t _level) {
	switch(_level) {
		case 0:		return (char*)"";
		case 1:		return (char*)"  ";
		case 2:		return (char*)"    ";
		case 3:		return (char*)"      ";
		case 4:		return (char*)"        ";
		case 5:		return (char*)"          ";
		case 6:		return (char*)"            ";
		case 7:		return (char*)"              ";
		case 8:		return (char*)"                ";
		case 9:		return (char*)"                  ";
		case 10:	return (char*)"                    ";
		case 11:	return (char*)"                      ";
		case 12:	return (char*)"                        ";
		case 13:	return (char*)"                          ";
		case 14:	return (char*)"                            ";
		case 15:	return (char*)"                              ";
		case 16:	return (char*)"                                ";
		default:	return (char*)"                                  ";
	}
}


int64_t etk::getLenOfPTheseElem(const std::vector<char32_t>& _data, int64_t _startPos) {
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

int64_t etk::getLenOfPThese(const std::vector<char32_t>& _data, int64_t _startPos) {
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


int64_t etk::getLenOfBracket(const std::vector<char32_t>& _data, int64_t _startPos) {
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


int64_t etk::getLenOfBrace(const std::vector<char32_t>& _data, int64_t _startPos) {
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


int64_t etk::getLenOfNormal(const std::vector<char32_t>& _data, int64_t _startPos) {
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


bool etk::parseBrace(const std::vector<char32_t>& _data, uint32_t& _min, uint32_t& _max)
{
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


