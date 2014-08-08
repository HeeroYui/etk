/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <etk/types.h>

#ifndef __ETK_DEBUG_H__
#define __ETK_DEBUG_H__

#include <etk/log.h>

namespace etk {
	int32_t getLogId();
};
// TODO : Review this problem of multiple intanciation of "std::stringbuf sb"
#define ETK_BASE(info,data) \
	do { \
		if (info <= etk::log::getLevel(etk::getLogId())) { \
			std::stringbuf sb; \
			std::ostream tmpStream(&sb); \
			tmpStream << data; \
			etk::log::logStream(etk::getLogId(), info, __LINE__, __class__, __func__, tmpStream); \
		} \
	} while(0)

#define TK_CRITICAL(data)      ETK_BASE(1, data)
#define TK_ERROR(data)         ETK_BASE(2, data)
#define TK_WARNING(data)       ETK_BASE(3, data)
#ifdef DEBUG
	#define TK_INFO(data)          ETK_BASE(4, data)
	#define TK_DEBUG(data)         ETK_BASE(5, data)
	#define TK_VERBOSE(data)       ETK_BASE(6, data)
	#define TK_TODO(data)          ETK_BASE(4, "TODO : " << data)
#else
	#define TK_INFO(data)          do { } while(false)
	#define TK_DEBUG(data)         do { } while(false)
	#define TK_VERBOSE(data)       do { } while(false)
	#define TK_TODO(data)          do { } while(false)
#endif

#define TK_HIDDEN(data)          do { } while(false)

#define TK_ASSERT(cond,data) \
	do { \
		if (!(cond)) { \
			TK_CRITICAL(data); \
			assert(!#cond); \
		} \
	} while (0)

#endif

