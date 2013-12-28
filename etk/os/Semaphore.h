/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_SEMAPHORE_H__
#define __ETK_SEMAPHORE_H__

#include <etk/types.h>

#ifdef __TARGET_OS__Windows
	#include <windows.h>
#else
	#include <pthread.h>
#endif

namespace etk {
	/**
	 * @brief Generic semaphore wrapper ( it is os independent)
	 */
	class Semaphore {
		private:
			#ifdef __TARGET_OS__Windows
				HANDLE m_semaphore;
			#else
				pthread_mutex_t m_mutex;
				pthread_cond_t m_condition;
				uint32_t m_data;
				uint32_t m_maximum;
			#endif
		public:
			/**
			 * @brief Contruct the inithialized semaphore.
			 * @param[in] _nbBasicElement Number of element basicly set in the semaphore list
			 * @param[in] _nbMessageMax Nunber of maximun message that can be set.
			 */
			Semaphore(uint32_t _nbBasicElement=0, uint32_t _nbMessageMax=1);
			/**
			 * @brief Generic destructor.
			 */
			~Semaphore(void);
			/**
			 * @brief Get the number of element in the semaphore.
			 * @return Number of stored elements.
			 */
			uint32_t getCount(void);
			/**
			 * @brief Post a new semaphore
			 */
			void post(void);
			/**
			 * @brief Wait for a new semaphore post by an other thread.
			 */
			void wait(void);
			/**
			 * @brief Wait for a new semaphore post by an other thread,
			 * with a timeout in micro-second.
			 * @param[in] _timeOutInUs Number of micro-second to wait a semaphore.
			 * @return true The function get a semaphore.
			 * @return false The time-out appear or an error occured.
			 */
			bool wait(uint64_t _timeOutInUs);
	};
};

#endif
