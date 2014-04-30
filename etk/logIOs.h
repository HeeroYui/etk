/**
 * @author Edouard DUPIN
 *
 * @copyright 2011, Edouard DUPIN, all right reserved
 *
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_LOG_IOS_H__
#define __ETK_LOG_IOS_H__

#ifdef __cplusplus
extern "C" {
#endif
#ifdef __TARGET_OS__IOs
	void iosNSLog(const char * _value);
#endif
#ifdef __cplusplus
}
#endif

#endif

