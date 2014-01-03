/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/types.h>

#ifndef __ETK_MUTEX_H__
#define __ETK_MUTEX_H__

#ifdef __TARGET_OS__Windows
	#include <windows.h>
#else
	#include <pthread.h>
#endif

namespace etk {
	/**
	 * @brief Generic mutex interface (OS independent)
	 */
	class Mutex {
		private:
			#ifdef __TARGET_OS__Windows
				CRITICAL_SECTION m_mutex;
			#else
				pthread_mutex_t  m_mutex;
			#endif
		public:
			/**
			 * @brief Create a new mutex
			 */
			Mutex(void);
			/**
			 * @brief Destroy the mutex.
			 */
			~Mutex(void);
			/**
			 * @brief Lock the mutex (Wait while the mutex is not lock)
			 */
			void lock(void);
			/**
			 * @brief Try to lock the mutex (exit if mutex is already locked)
			 * @return true The mutex is locked
			 * @return false The mutex is already locked.
			 */
			bool tryLock(void);
			/**
			 * @brief Unloc the mutex
			 */
			void unLock(void);
	};
	/**
	 * @brief AutoLock and un-lock when exit fuction.
	 */
	class AutoLockMutex {
		private:
			// Keep a reference on the mutex
			etk::Mutex &m_protect;
		public:
			/**
			 * @brief constructor that automaticly lock the mutex.
			 * @param[in] _protect Mutex to Lock.
			 */
			AutoLockMutex(etk::Mutex& _protect) :
			  m_protect(_protect) {
				m_protect.lock();
			}
			/**
			 * @brief Destructor that Auto Unlock mutex when remove.
			 */
			virtual ~AutoLockMutex(void){
				m_protect.unLock();
			}
	};
};

#endif
