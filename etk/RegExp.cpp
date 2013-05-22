/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */


#include <etk/RegExp.h>



const etk::convertionTable_ts etk::constConvertionTable[] = {
	// haveBackSlash, inputValue, newValue
	{ false			, '('  , 0   , REGEXP_OPCODE_PTHESE_IN},
	{ true			, '('  , '(' , REGEXP_OPCODE_ERROR},
	{ false			, ')'  , 0   , REGEXP_OPCODE_PTHESE_OUT},
	{ true			, ')'  , ')' , REGEXP_OPCODE_ERROR},
	{ false			, '['  , 0   , REGEXP_OPCODE_BRACKET_IN},
	{ true			, '['  , '[' , REGEXP_OPCODE_ERROR},
	{ false			, ']'  , 0   , REGEXP_OPCODE_BRACKET_OUT},
	{ true			, ']'  , ']' , REGEXP_OPCODE_ERROR},
	{ false			, '{'  , 0   , REGEXP_OPCODE_BRACE_IN},
	{ true			, '{'  , '{' , REGEXP_OPCODE_ERROR},
	{ false			, '}'  , 0   , REGEXP_OPCODE_BRACE_OUT},
	{ true			, '}'  , '}' , REGEXP_OPCODE_ERROR},
	{ false			, '-'  , 0   , REGEXP_OPCODE_TO},
	{ true			, '-'  , '-' , REGEXP_OPCODE_ERROR},
	{ false			, '*'  , 0   , REGEXP_OPCODE_STAR},
	{ true			, '*'  , '*' , REGEXP_OPCODE_ERROR},
	{ false			, '.'  , 0   , REGEXP_OPCODE_DOT},
	{ true			, '.'  , '.' , REGEXP_OPCODE_ERROR},
	{ false			, '?'  , 0   , REGEXP_OPCODE_QUESTION},
	{ true			, '?'  , '?' , REGEXP_OPCODE_ERROR},
	{ false			, '+'  , 0   , REGEXP_OPCODE_PLUS},
	{ true			, '+'  , '+' , REGEXP_OPCODE_ERROR},
	{ false			, '|'  , 0   , REGEXP_OPCODE_PIPE},
	{ true			, '|'  , '|' , REGEXP_OPCODE_ERROR},
	{ false			, '^'  , 0   , REGEXP_OPCODE_START_OF_LINE},
	{ true			, '^'  , '^' , REGEXP_OPCODE_ERROR},
	{ false			, '$'  , 0   , REGEXP_OPCODE_END_OF_LINE},
	{ true			, '$'  , '$' , REGEXP_OPCODE_ERROR},
	{ true			, 'd'  , 0   , REGEXP_OPCODE_DIGIT},
	{ true			, 'D'  , 0   , REGEXP_OPCODE_DIGIT_NOT},
	{ true			, 'l'  , 0   , REGEXP_OPCODE_LETTER},
	{ true			, 'L'  , 0   , REGEXP_OPCODE_LETTER_NOT},
	{ true			, 's'  , 0   , REGEXP_OPCODE_SPACE},
	{ true			, 'S'  , 0   , REGEXP_OPCODE_SPACE_NOT},
	{ true			, 'w'  , 0   , REGEXP_OPCODE_WORD},
	{ true			, 'W'  , 0   , REGEXP_OPCODE_WORD_NOT},
	{ true			, 'a'  , '\a', REGEXP_OPCODE_ERROR},
	{ true			, 'b'  , '\b', REGEXP_OPCODE_ERROR},
	{ true			, 'e'  , 0x1B, REGEXP_OPCODE_ERROR}, // Escape character <Esc>
	{ true			, 'f'  , '\f', REGEXP_OPCODE_ERROR},
	{ true			, 'n'  , '\n', REGEXP_OPCODE_ERROR},
	{ true			, 'r'  , '\r', REGEXP_OPCODE_ERROR},
	{ true			, 't'  , '\t', REGEXP_OPCODE_ERROR},
	{ true			, 'v'  , '\v', REGEXP_OPCODE_ERROR},
	{ true			, '\\' , '\\', REGEXP_OPCODE_ERROR},
	{ true			, '&'  , '&' , REGEXP_OPCODE_ERROR},
	{ true			, '0'  , '\0', REGEXP_OPCODE_ERROR},
	{ true			, '@'  , 0   , REGEXP_OPCODE_NO_CHAR},
};
const int32_t etk::constConvertionTableSize = sizeof(etk::constConvertionTable) / sizeof(etk::convertionTable_ts) ;

void etk::DisplayElem(const etk::Vector<etk::UniChar>& _data, int32_t _start, int32_t _stop)
{
	etk::cout<< ETK_BASH_COLOR_NORMAL;
	for (int32_t iii=_start; iii<_data.Size() && iii<_stop ; iii++) {
		switch(_data[iii].Get())
		{
			case REGEXP_OPCODE_PTHESE_IN:		etk::cout<<ETK_BASH_COLOR_RED		<< (char*)"(" << ETK_BASH_COLOR_NORMAL;		break;
			case REGEXP_OPCODE_PTHESE_OUT:		etk::cout<<ETK_BASH_COLOR_RED		<< (char*)")" << ETK_BASH_COLOR_NORMAL;		break;
			case REGEXP_OPCODE_BRACKET_IN:		etk::cout<<ETK_BASH_COLOR_YELLOW	<< (char*)"[" << ETK_BASH_COLOR_NORMAL;		break;
			case REGEXP_OPCODE_BRACKET_OUT:		etk::cout<<ETK_BASH_COLOR_YELLOW	<< (char*)"]" << ETK_BASH_COLOR_NORMAL;		break;
			case REGEXP_OPCODE_TO:				etk::cout<<ETK_BASH_COLOR_YELLOW	<< (char*)"-" << ETK_BASH_COLOR_NORMAL;		break;
			case REGEXP_OPCODE_BRACE_IN:		etk::cout<<ETK_BASH_COLOR_GREEN		<< (char*)"{" << ETK_BASH_COLOR_NORMAL;		break;
			case REGEXP_OPCODE_BRACE_OUT:		etk::cout<<ETK_BASH_COLOR_GREEN		<< (char*)"}" << ETK_BASH_COLOR_NORMAL;		break;
			case REGEXP_OPCODE_STAR:			etk::cout<<ETK_BASH_COLOR_BLUE		<< (char*)"*" << ETK_BASH_COLOR_NORMAL;		break;
			case REGEXP_OPCODE_DOT:				etk::cout<<ETK_BASH_COLOR_BLUE		<< (char*)"." << ETK_BASH_COLOR_NORMAL;		break;
			case REGEXP_OPCODE_QUESTION:		etk::cout<<ETK_BASH_COLOR_BLUE		<< (char*)"?" << ETK_BASH_COLOR_NORMAL;		break;
			case REGEXP_OPCODE_PLUS:			etk::cout<<ETK_BASH_COLOR_BLUE		<< (char*)"+" << ETK_BASH_COLOR_NORMAL;		break;
			case REGEXP_OPCODE_PIPE:			etk::cout<<ETK_BASH_COLOR_BLUE		<< (char*)"|" << ETK_BASH_COLOR_NORMAL;		break;
			case REGEXP_OPCODE_NO_CHAR:			etk::cout<<ETK_BASH_COLOR_MAGENTA	<< (char*)"@" << ETK_BASH_COLOR_NORMAL;		break;
			case REGEXP_OPCODE_START_OF_LINE:	etk::cout<<ETK_BASH_COLOR_MAGENTA	<< (char*)"^" << ETK_BASH_COLOR_NORMAL;		break;
			case REGEXP_OPCODE_END_OF_LINE:		etk::cout<<ETK_BASH_COLOR_MAGENTA	<< (char*)"$" << ETK_BASH_COLOR_NORMAL;		break;
			case REGEXP_OPCODE_DIGIT:			etk::cout<<ETK_BASH_COLOR_MAGENTA	<< (char*)"\\d" << ETK_BASH_COLOR_NORMAL;	break;
			case REGEXP_OPCODE_DIGIT_NOT:		etk::cout<<ETK_BASH_COLOR_MAGENTA	<< (char*)"\\D" << ETK_BASH_COLOR_NORMAL;	break;
			case REGEXP_OPCODE_LETTER:			etk::cout<<ETK_BASH_COLOR_MAGENTA	<< (char*)"\\l" << ETK_BASH_COLOR_NORMAL;	break;
			case REGEXP_OPCODE_LETTER_NOT:		etk::cout<<ETK_BASH_COLOR_MAGENTA	<< (char*)"\\L" << ETK_BASH_COLOR_NORMAL;	break;
			case REGEXP_OPCODE_SPACE:			etk::cout<<ETK_BASH_COLOR_MAGENTA	<< (char*)"\\s" << ETK_BASH_COLOR_NORMAL;	break;
			case REGEXP_OPCODE_SPACE_NOT:		etk::cout<<ETK_BASH_COLOR_MAGENTA	<< (char*)"\\S" << ETK_BASH_COLOR_NORMAL;	break;
			case REGEXP_OPCODE_WORD:			etk::cout<<ETK_BASH_COLOR_MAGENTA	<< (char*)"\\w" << ETK_BASH_COLOR_NORMAL;	break;
			case REGEXP_OPCODE_WORD_NOT:		etk::cout<<ETK_BASH_COLOR_MAGENTA	<< (char*)"\\W" << ETK_BASH_COLOR_NORMAL;	break;
			case '\n':							etk::cout<<ETK_BASH_COLOR_MAGENTA	<< (char*)"\\n" << ETK_BASH_COLOR_NORMAL;	break;
			case '\t':							etk::cout<<ETK_BASH_COLOR_MAGENTA	<< (char*)"\\t" << ETK_BASH_COLOR_NORMAL;	break;
			default:							etk::cout<< _data[iii];									break;
		}
	}
}
char * etk::levelSpace(int32_t _level)
{
	switch(_level)
	{
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


int32_t etk::GetLenOfPTheseElem(const etk::Vector<etk::UniChar>& _data, int32_t _startPos)
{
	if (_startPos>=_data.Size()){
		return 0;
	}
	int32_t pos = _startPos;
	int32_t nbOpen = 0;
	// special case of the (...) or | ==> we search '|' or ')'
	if(    _data[pos] == REGEXP_OPCODE_PTHESE_OUT
	    || _data[pos] == REGEXP_OPCODE_PIPE) {
		return 0;
	}
	// find size ...
	while (pos < (int32_t)_data.Size() ) {
		if(_data[pos] == REGEXP_OPCODE_PTHESE_IN) {
			// find a sub section : 
			nbOpen++;
		} else if(0 < nbOpen) {
			if (_data[pos] == REGEXP_OPCODE_PTHESE_OUT) {
				nbOpen--;
				if (0 > nbOpen) {
					TK_ERROR("Error in the (...) find element at "<< pos);
					return -1;
				}
			}
		} else if(    _data[pos] == REGEXP_OPCODE_PTHESE_OUT
		           || _data[pos] == REGEXP_OPCODE_PIPE) {
			// Find the end of the (...)
			// just return the size inside
			int32_t sizeInside = pos - _startPos;
			if (0 >= sizeInside) {
				TK_ERROR("Error in the (...) no data at "<< pos-1);
				return -1;
			} else {
				return sizeInside;
			}
		}
		pos++;
	}
	return pos - _startPos;
}

int32_t etk::GetLenOfPThese(const etk::Vector<etk::UniChar>& _data, int32_t _startPos)
{
	int32_t pos = _startPos;
	int32_t nbOpen = 0;
	// special case of the (...) or | ==> we search '|' or ')'
	if(_data[pos]==REGEXP_OPCODE_PTHESE_OUT) {
		return 0;
	} else if(_data[pos]==REGEXP_OPCODE_PTHESE_IN) {
		pos++;
		// find size ...
		while (pos < _data.Size() ) {
			if(_data[pos]==REGEXP_OPCODE_PTHESE_IN) {
				// find a sub section : 
				nbOpen++;
			} else if(0 < nbOpen) {
				if (_data[pos]==REGEXP_OPCODE_PTHESE_OUT) {
					nbOpen--;
					if (0 > nbOpen) {
						TK_ERROR("Error in the (...) find element at "<< pos);
						return -1;
					}
				}
			} else if(_data[pos]==REGEXP_OPCODE_PTHESE_OUT) {
				// Find the end of the (...)
				// just return the size inside
				int32_t sizeInside = pos - _startPos-1;
				if (0 >= sizeInside) {
					TK_ERROR("Error in the (...) no data at "<< pos-1);
					return -1;
				} else {
					return sizeInside;
				}
			}
			pos++;
		}
	} else {
		return -1;
	}
	return 0;
}


int32_t etk::GetLenOfBracket(const etk::Vector<etk::UniChar>& _data, int32_t _startPos)
{
	int32_t pos = _startPos;
	// special case of the (...) or | ==> we search '|' or ')'
	if(_data[pos]==REGEXP_OPCODE_BRACKET_OUT) {
		return 0;
	} else if(_data[pos] == REGEXP_OPCODE_BRACKET_IN) {
		pos++;
		// find size ...
		while (pos < _data.Size() ) {
			if(_data[pos]==REGEXP_OPCODE_BRACKET_OUT) {
				// Find the end of the [...]
				// just return the size inside
				int32_t sizeInside = pos - _startPos -1 ;
				if (0 >= sizeInside) {
					TK_ERROR("Error in the [...] no data at "<< pos-1);
					return sizeInside;
				} else {
					return sizeInside;
				}
			} else if(    _data[pos] != REGEXP_OPCODE_TO
			           && _data[pos] > 0xFF ) {
				TK_ERROR("Error in the [...] not permited element at "<< pos << " '" << (char)_data[pos].Get() << "'");
				return false;
			}
			pos++;
		}
	} else {
		return -1;
	}
	return 0;
}


int32_t etk::GetLenOfBrace(const etk::Vector<etk::UniChar>& _data, int32_t _startPos)
{
	int32_t pos = _startPos;
	// special case of the (...) or | ==> we search '|' or ')'
	if(_data[pos]==REGEXP_OPCODE_BRACE_OUT) {
		return 0;
	} else if(_data[pos]==REGEXP_OPCODE_BRACE_IN) {
		pos++;
		// find size ...
		while (pos < _data.Size() ) {
			if(_data[pos]==REGEXP_OPCODE_BRACE_OUT) {
				// Find the end of the [...]
				// just return the size inside
				int32_t sizeInside = pos - _startPos -1 ;
				if (0 >= sizeInside) {
					TK_ERROR("Error in the {...} no data at "<< pos-1);
					return sizeInside;
				} else {
					return sizeInside;
				}
			} else if(    _data[pos] != ','
			           && (    _data[pos] < '0'
			                || _data[pos] > '9') ) {
				TK_ERROR("Error in the {...} not permited element at "<< pos << " '" << _data[pos].Get() << "'");
				return false;
			}
			pos++;
		}
	} else {
		return -1;
	}
	return 0;
}


int32_t etk::GetLenOfNormal(const etk::Vector<etk::UniChar>& _data, int32_t _startPos)
{
	int32_t pos = _startPos;

	// find size ...
	while (pos < _data.Size() ) {
		switch(_data[pos].Get())
		{
			case REGEXP_OPCODE_PTHESE_IN:
			case REGEXP_OPCODE_PTHESE_OUT:
			case REGEXP_OPCODE_BRACKET_IN:
			case REGEXP_OPCODE_BRACKET_OUT:
			case REGEXP_OPCODE_BRACE_IN:
			case REGEXP_OPCODE_BRACE_OUT:
			case REGEXP_OPCODE_TO:
			case REGEXP_OPCODE_STAR:
			case REGEXP_OPCODE_DOT:
			case REGEXP_OPCODE_QUESTION:
			case REGEXP_OPCODE_PLUS:
			case REGEXP_OPCODE_PIPE:
			case REGEXP_OPCODE_START_OF_LINE:
			case REGEXP_OPCODE_END_OF_LINE:
			case REGEXP_OPCODE_DIGIT:
			case REGEXP_OPCODE_DIGIT_NOT:
			case REGEXP_OPCODE_LETTER:
			case REGEXP_OPCODE_LETTER_NOT:
			case REGEXP_OPCODE_SPACE:
			case REGEXP_OPCODE_SPACE_NOT:
			case REGEXP_OPCODE_WORD:
			case REGEXP_OPCODE_WORD_NOT:
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
	return pos - _startPos ;
}


bool etk::ParseBrace(const etk::Vector<etk::UniChar>& _data, int32_t& _min, int32_t& _max)
{
	//TK_INFO("parse {...} in "; DisplayElem(data); );
	int32_t k=0;
	
	int32_t firstElement = 0;
	int32_t SecondElement = 0;
	
	while(k<_data.Size()) {
		if (_data[k]==',') {
			k++;
			break;
		} if (_data[k]=='}') {
			SecondElement = firstElement;
			goto allIsSet;
		} else if(true==_data[k].IsInteger()) {
			firstElement *=10;
			firstElement += _data[k].ToInt32();
		} else {
			TK_ERROR("Can not parse this element " << (char)_data[k].Get() << " at pos " << k);
			return false;
		}
		k++;
	}
	if (k==_data.Size()) {
		SecondElement = firstElement;
	}
	while(k<_data.Size()) {
		if (_data[k]==',') {
			TK_ERROR("Can not find a second , in {} at pos " << k);
			return false;
		} if (_data[k]=='}') {
			goto allIsSet;
		} else if (true==_data[k].IsInteger()) {
			SecondElement *=10;
			SecondElement += _data[k].ToInt32();
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


