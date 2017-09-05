/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once
extern "C" {
	#include <stdlib.h>
	#include <stdio.h>
	#include <stdarg.h>
	#include <string.h>
	#include <assert.h>
	// defien type : uintXX_t and intXX_t
	#define __STDC_LIMIT_MACROS
	// note in android include the macro of min max are overwitten
	#include <stdint.h>
	#include <stddef.h>
}
#ifndef size_t
	using size_t=uint64_t;
#endif
#ifndef INT8_MIN
	#define INT8_MIN  (-128)
#endif
#ifndef INT8_MAX
	#define INT8_MAX  (127)
#endif
#ifndef UINT8_MAX
	#define UINT8_MAX (255U)
#endif
#ifndef INT16_MIN
	#define INT16_MIN  (-32768)
#endif
#ifndef INT16_MAX
	#define INT16_MAX  (32767)
#endif
#ifndef UINT16_MAX
	#define UINT16_MAX (65535U)
#endif
#ifndef INT32_MIN
	#define INT32_MIN  (-2147483647-1)
#endif
#ifndef INT32_MAX
	#define INT32_MAX  (2147483647)
#endif
#ifndef UINT32_MAX
	#define UINT32_MAX (4294967295U)
#endif
#ifndef INT64_MIN
	#define INT64_MIN  (__INT64_C(-9223372036854775807)-1)
#endif
#ifndef INT64_MAX
	#define INT64_MAX  (__INT64_C(9223372036854775807))
#endif
#ifndef UINT64_MAX
	#define UINT64_MAX (__UINT64_C(18446744073709551615))
#endif

#ifndef ETK_BUILD_LINEARMATH
	//! @brief If not using linear math from bullet lib, we need to define the basic element of a btScalar (float)
	using btScalar = float;
#endif

#ifndef _WIN32
	extern "C" {
		#include <math.h>
	}
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

#if 0
typedef decltype(nullptr) etk::NullPtr;
#else
namespace etk {
	class NullPtr {
		public:
			// When tested a pointer, acts as 0.
			template<class T>
			operator T*() const {
				return 0;
			}
			template<class C, class T>      // When tested as a member pointer, acts as 0.
			operator T C::*() const {
				return 0;
			}
			typedef void* (etk::NullPtr::*bool_)() const;
			// An rvalue of type etk::NullPtr can be converted to an rvalue of type bool; the resulting value is false.
			/*
			operator bool_() const {
				// We can't use operator bool(){ return false; } because bool is convertable to int which breaks other required functionality.
				return false;
			}
			*/
			// We can't enable this without generating warnings about nullptr being uninitialized after being used when created without "= {}".
			//void* mSizeofVoidPtr;         // sizeof(etk::NullPtr) == sizeof(void*). Needs to be public if etk::NullPtr is to be a POD.
			template <typename ETK_TYPE_FUNCTION_RETURN, typename... ETK_TYPE_FUNCTION_ARGS>
			ETK_TYPE_FUNCTION_RETURN operator()(ETK_TYPE_FUNCTION_ARGS... _args) {
				throw;
				//return ETK_TYPE_FUNCTION_RETURN();
			}
		private:
			//void operator&() const;         // Address cannot be taken. ==> TODO: this is really bad, because this create an error in many code
	};
	
	inline NullPtr nullptrGet() {
		// etk::nullptr exists.
		NullPtr n = { };
		return n;
	}
}

// If somebody hasn't already defined nullptr in a custom way...
#if !defined(nullptr)
	#define nullptr etk::nullptrGet()
#endif

#endif

template<class T>
inline bool operator==(T* p, const etk::NullPtr) {
	return p == 0;
}

template<class T>
inline bool operator==(const etk::NullPtr, T* p)
{ return p == 0; }

template<class T, class U>
inline bool operator==(T U::* p, const etk::NullPtr)
{ return p == 0; }

template<class T, class U>
inline bool operator==(const etk::NullPtr, T U::* p)
{ return p == 0; }

inline bool operator==(const etk::NullPtr, const etk::NullPtr)
{ return true; }

inline bool operator!=(const etk::NullPtr, const etk::NullPtr)
{ return false; }

inline bool operator<(const etk::NullPtr, const etk::NullPtr)
{ return false; }

inline bool operator>(const etk::NullPtr, const etk::NullPtr)
{ return false; }

inline bool operator<=(const etk::NullPtr, const etk::NullPtr)
{ return true; }

inline bool operator>=(const etk::NullPtr, const etk::NullPtr)
{ return true; }

// TODO: remove ...
// exported to global namespace.
//using etk::NullPtr;


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
}
#include <etk/move.hpp>
#include <etk/Stream.hpp>
