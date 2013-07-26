/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_TOOL_H__
#define __ETK_TOOL_H__

#include <etk/types.h>
#include <etk/UString.h>

namespace etk {
	namespace tool {
		float   frand(float _a, float _b);
		int32_t irand(int32_t _a, int32_t _b);
		
		void SortList(etk::Vector<etk::UString *>& _list);
		bool strnCmpNoCase(const char* _input1, const char* _input2, int32_t _maxLen);
		etk::UString SimplifyPath(etk::UString _input);
		
	};
};

#endif
