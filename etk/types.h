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

#include <etk/stdTools.h>
#ifndef _WIN32
	typedef float float_t;
#endif

#endif
