/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <iostream>

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

#include <etk/stdTools.hpp>

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

