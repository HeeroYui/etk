/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/tool.h>
#include <etk/os/FSNode.h>
// for the rand ...
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

float etk::tool::frand(float _a, float _b)
{
	return ( rand()/(float)RAND_MAX ) * (_b-_a) + _a;
}


int32_t etk::tool::irand(int32_t _a, int32_t _b)
{
	return (int32_t)(( rand()/(float)RAND_MAX ) * ((float)_b-(float)_a) + (float)_a);
}

void etk::tool::sortList(std::vector<std::u32string *> &_list)
{
	std::vector<std::u32string *> tmpList = _list;
	_list.clear();
	for(int32_t iii=0; iii<tmpList.size(); iii++) {
		
		int32_t findPos = 0;
		for(int32_t jjj=0; jjj<_list.size(); jjj++) {
			//EWOL_DEBUG("compare : \""<<*tmpList[iii] << "\" and \"" << *m_listDirectory[jjj] << "\"");
			if (*tmpList[iii] > *_list[jjj]) {
				findPos = jjj+1;
			}
		}
		//EWOL_DEBUG("position="<<findPos);
		_list.insert(_list.begin()+findPos, tmpList[iii]);
	}
}


bool etk::tool::strnCmpNoCase(const char * _input1, const char * _input2, int32_t _maxLen)
{
	int32_t iii=0;
	while ('\0' != *_input1 && '\0' != *_input2 && iii < _maxLen) {
		char in1 = *_input1;
		char in2 = *_input2;
		if (in1 != in2) {
			if (in1 <= 'Z' && in1 >= 'A') {
				in1 = in1 - 'A' + 'a';
			}
			if (in2 <= 'Z' && in2 >= 'A') {
				in2 = in2 - 'A' + 'a';
			}
			if (in1 != in2) {
				return false;
			}
		}
		iii++;
		_input1++;
		_input2++;
	}
	return true;
}


std::u32string etk::tool::simplifyPath(std::u32string _input)
{
	size_t findStartPos = _input.find('/') + 1;
	size_t findPos = _input.find('/', findStartPos);
	//TK_DEBUG("Siplify : \"" << input << "\"");
	int32_t preventBadCode = 0;
	while (findPos!=0)
	{
		//TK_DEBUG("      string=\"" << input << "\"");
		//TK_DEBUG("      '/' @" << findPos);
		if (_input.size()<findPos+1) {
			// no more element ...
			break;
		}
		if(    _input[findPos+1] == '/'
		    || (    _input[findPos+1] == '.'
		         && _input.size()==findPos+2 )) {
			// cleane the element path
			_input.erase(findPos+1, 1);
			//TK_DEBUG("      Remove // string=\"" << input << "\"");
		} else {
			if (_input.size()<findPos+2) {
				// no more element ...
				break;
			}
			if(    _input[findPos+1] == '.'
			    && _input[findPos+2] == '.') {
				// cleane the element path
				_input.erase(findStartPos, findPos+3 - findStartPos );
				//TK_DEBUG("      Remove xxx/.. string=\"" << input << "\"");
			} else if(    _input[findPos+1] == '.'
			           && _input[findPos+2] == '/') {
				// cleane the element path
				_input.erase(findPos+1, 2);
				//TK_DEBUG("      Remove ./ string=\"" << input << "\"");
			} else {
				findStartPos = findPos+1;
			}
		}
		findPos = _input.find('/', findStartPos);
		preventBadCode++;
		if (preventBadCode>5000) {
			TK_CRITICAL("ERROR when getting the small path ... this is loop prevention...");
			break;
		}
	}
	#ifndef __TARGET_OS__Windows
		// for the target that supported the Realpath system :
		char buf[MAX_FILE_NAME];
		memset(buf, 0, MAX_FILE_NAME);
		char * ok = realpath(to_u8string(_input).c_str(), buf);
		if (!ok) {
			TK_ERROR("Error to get the real path");
			_input = U"/";
		} else {
			_input = to_u32string(buf);
		}
	#endif
	
	//TK_DEBUG("   ==> \"" << input << "\"");
	return _input;
}

