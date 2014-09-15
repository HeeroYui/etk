/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ETK_TYPES_H__
#define __ETK_TYPES_H__

#include <iostream>

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
// defien type : uintXX_t and intXX_t
#define __STDC_LIMIT_MACROS
// note in android include the macro of min max are overwitten
#include <stdint.h>
// in case of android error ...
#ifdef __TARGET_OS__Android
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

/*
	Target ARCH values (CPU core TYPE):
		__TARGET_ARCH__ARM
		__TARGET_ARCH__POWER_PC
		__TARGET_ARCH__INTEL
		__TARGET_ARCH__AMD
		__TARGET_ARCH__MICROCHIP
		...
	Target ARCH_VERSION values:
		__TARGET_ARCH_VERSION__05_00 // for exemple arm v5 (very small ==> simple core...)
		__TARGET_ARCH_VERSION__07_00 // for exemple arm v7 (with NEON)
	Target ADDR values (adressing mode):
		__TARGET_ADDR__16BITS
		__TARGET_ADDR__32BITS
		__TARGET_ADDR__64BITS
		__TARGET_ADDR__128BITS
	
	Target CORE values (adressing mode):
		__TARGET_CORE__1 // 1 core
		__TARGET_CORE__2 // 2 core
		__TARGET_CORE__3 // 3 core
		__TARGET_CORE__4 // 4 core
		__TARGET_CORE__X // x core ==> must auto update
		..
*/

// Check windows
#ifdef _WIN32
	#define __TARGET_ARCH__32BITS
#endif
#ifdef _WIN64
	#define __TARGET_ARCH__64BITS
#endif

// Check GCC
#if __GNUC__
	#if __x86_64__ || __ppc64__
		#define __TARGET_ARCH__64BITS
	#else
		#define __TARGET_ARCH__32BITS
	#endif
#endif

#include <etk/stdTools.h>
#ifndef _WIN32
	typedef float float_t;
#endif

#endif
