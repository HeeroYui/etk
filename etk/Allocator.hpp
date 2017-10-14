/** @file
 * @author Edouard DUPIN
 * @copyright 2017, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once
#include <etk/types.hpp>

// it is define bu generic "include <new>" ==> no double define of placement new
#ifndef _NEW
	// Default placement versions of operator new (use char* instead of void* to permit no multiple definition).
	inline void* operator new(size_t, char* _p) throw() {
		return _p;
	}
	inline void operator delete (void*, char*) throw() {
		
	}
#endif
