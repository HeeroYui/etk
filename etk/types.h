/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_TYPES_H__
#define __ETK_TYPES_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
// defien type : uintXX_t and intXX_t
#include <stdint.h>

typedef uint32_t uniChar_t;

typedef enum {
	ERR_NONE = 0, //!< No error, luckily everything went fine
	ERR_FAIL, //!< Miscellaneous failure
	ERR_INVAL, //!< Invalid entry parameter
	ERR_MEM, //!< Dynamic memory allocation failure
	ERR_TIMEOUT, //!< Request time out
	ERR_BUSY, //!< Element curently Busy
}erreurCode_te;


#define etk_min(elemA, elemB)               (((elemA)<(elemB)) ? (elemA) : (elemB))
#define etk_max(elemA, elemB)               (((elemA)<(elemB)) ? (elemB) : (elemA))
#define etk_avg(minimim, elem, maximum)     (((minimim)>(elem)) ? (minimim) : ((maximum)<(elem)) ? (maximum) : (elem))

#endif
