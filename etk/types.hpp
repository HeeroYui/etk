/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once
#include <cstdlib>
#include <cstdio>
#include <stdarg.h>
#include <cstring>
#include <cassert>
// defien type : uintXX_t and intXX_t
#define __STDC_LIMIT_MACROS
// note in android include the macro of min max are overwitten
#include <cstdint>
// in case of android error ...
#ifdef __TARGET_OS__Android
	#if __ANDROID_BOARD_ID__ <= 20
		#ifndef __STDINT_LIMITS
			#define INT8_MIN  (-128)
			#define INT8_MAX  (127)
			#define UINT8_MAX (255U)
			
			#define INT16_MIN  (-32768)
			#define INT16_MAX  (32767)
			#define UINT16_MAX (65535U)
			
			#define INT32_MIN  (-2147483647-1)
			#define INT32_MAX  (2147483647)
			#define UINT32_MAX (4294967295U)
			
			#define INT64_MIN  (__INT64_C(-9223372036854775807)-1)
			#define INT64_MAX  (__INT64_C(9223372036854775807))
			#define UINT64_MAX (__UINT64_C(18446744073709551615))
		#endif
	#endif
#endif

#ifndef ETK_BUILD_LINEARMATH
	//! @brief If not using linear math from bullet lib, we need to define the basic element of a btScalar (float)
	using btScalar = float;
#endif

#ifndef _WIN32
	#include <cmath>
	#ifndef _MATH_H_MATHDEF
		//! @brief Generate a basic type for floating point unit selection (not finished)
		using float_t = float;
	#endif
#endif

#ifdef _WIN32
	//#define ETK_EXPORT_API extern "C" __declspec( dllimport )
	#define ETK_EXPORT_API 
#else
	#define ETK_EXPORT_API extern "C" __attribute__ ((visibility ("default")))
#endif

#ifdef _WIN32
	#define ETK_EXPORT_VISIBILITY 
#else
	#define ETK_EXPORT_VISIBILITY __attribute__ ((visibility ("default")))
#endif

#if (defined(__TARGET_OS__Windows))
	#define M_PI 3.14159265358979323846
#endif

namespace etk {
	template <class TYPE> const TYPE& min(const TYPE& _val1, const TYPE& _val2) {
		return (_val1 > _val2) ? _val2 : _val1;
	}
	template <class TYPE> const TYPE& max(const TYPE& _val1, const TYPE& _val2) {
		return (_val1 > _val2) ? _val1 : _val2;
	}
	/**
	 * @brief in std, we have min, max but not avg ==> it is missing... the Define of avg template.
	 * @param[in] _min Minimum value of the range
	 * @param[in] _val The value that we want a min/max
	 * @param[in] _max Maximum value of the range
	 * @return Value that min/max applied
	 */
	template <class TYPE> const TYPE& avg(const TYPE& _min, const TYPE& _val, const TYPE& _max) {
		return etk::min(etk::max(_min,_val),_max);
	}
};


namespace etk {
	template<class ETK_ITERATOR_TYPE>
	size_t distance(const ETK_ITERATOR_TYPE& _start, const ETK_ITERATOR_TYPE& _stop) {
		size_t out = 0;
		ETK_ITERATOR_TYPE tmp = _start;
		while (tmp != _stop) {
			out++;
			++tmp;
		}
		return out;
	}

	template<class ETK_MOVE_TYPE>
	struct _Remove_reference {
		// remove reference
		typedef ETK_MOVE_TYPE m_type;
	};
	template<class ETK_MOVE_TYPE>
	struct _Remove_reference<ETK_MOVE_TYPE&> {
		// remove reference
		typedef ETK_MOVE_TYPE m_type;
	};
	template<class ETK_MOVE_TYPE>
	struct _Remove_reference<ETK_MOVE_TYPE&&> {
		// remove rvalue reference
		typedef ETK_MOVE_TYPE m_type;
	};
	
	template<class ETK_MOVE_TYPE> inline
	typename etk::_Remove_reference<ETK_MOVE_TYPE>::m_type&& move(ETK_MOVE_TYPE&& _obj) {
		// forward _Arg as movable
		return ((typename etk::_Remove_reference<ETK_MOVE_TYPE>::m_type&&)_obj);
	}
	/*
	
	template<class ETK_MOVE_TYPE>
	eETK_MOVE_TYPE&& move(ETK_MOVE_TYPE&& _obj) {
		// forward _Arg as movable
		return ((ETK_MOVE_TYPE&&)_obj);
	}
	*/

}

#include <etk/Stream.hpp>

