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

#ifndef FLT_EPSILON
	#define FLT_EPSILON (1.192092896e-07f)
#endif
#ifndef FLT_MAX
	#define FLT_MAX (3.402823466e+38f)
#endif
#ifndef FLT_MIN
	#define FLT_MIN (1.175494351e-38f)
#endif

#ifndef DBL_EPSILON
	#define DBL_EPSILON (2.2204460492503131e-016)
#endif
#ifndef DBL_MAX
	#define DBL_MAX (1.7976931348623158e+308)
#endif
#ifndef DBL_MIN
	#define DBL_MIN (2.2250738585072014e-308)
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

#include <etk/NullPtr.hpp>

#include <etk/stdTools.hpp>
#include <etk/move.hpp>
//#include <etk/Stream.hpp>
