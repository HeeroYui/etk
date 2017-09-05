/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once
#include <etk/types.hpp>
#include <elog/log.hpp>
namespace etest {
	int32_t getLogId();
};

#define ETEST_BASE(info,data) ELOG_BASE(etest::getLogId(),info,data)

#define ETEST_PRINT(data)         ETEST_BASE(-1, data)
#define ETEST_CRITICAL(data)      ETEST_BASE(1, data)
#define ETEST_ERROR(data)         ETEST_BASE(2, data)
#define ETEST_WARNING(data)       ETEST_BASE(3, data)
#ifdef DEBUG
	#define ETEST_INFO(data)          ETEST_BASE(4, data)
	#define ETEST_DEBUG(data)         ETEST_BASE(5, data)
	#define ETEST_VERBOSE(data)       ETEST_BASE(6, data)
	#define ETEST_TODO(data)          ETEST_BASE(4, "TODO : " << data)
#else
	#define ETEST_INFO(data)          do { } while(false)
	#define ETEST_DEBUG(data)         do { } while(false)
	#define ETEST_VERBOSE(data)       do { } while(false)
	#define ETEST_TODO(data)          do { } while(false)
#endif

#define ETEST_HIDDEN(data)          do { } while(false)

#ifdef DEBUG
	#define ETEST_CHECK_INOUT(condition) \
		do { \
			if (!(condition)) { \
				ETEST_ERROR("Wrong condition : " #condition); \
			} \
		} while (0)
#else
	#define ETEST_CHECK_INOUT(condition)          do { } while(false)
#endif

#define ETEST_ASSERT(condition,data) \
	do { \
		if (!(condition)) { \
			ETEST_CRITICAL(data); \
			assert(!#condition); \
		} \
	} while (0)


