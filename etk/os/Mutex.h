/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_MUTEX_H__
#define __ETK_MUTEX_H__

#include <etk/types.h>

#ifdef __TARGET_OS__Windows
	#include <windows.h>
#else
	#include <pthread.h>
#endif

namespace etk
{
	class Mutex
	{
		private:
			#ifdef __TARGET_OS__Windows
				CRITICAL_SECTION m_mutex;
			#else
				pthread_mutex_t  m_mutex;
			#endif
		public:
			Mutex(void);
			~Mutex(void);
			void lock(void);
			bool tryLock(void);
			void unLock(void);
	};
	
};

#endif
