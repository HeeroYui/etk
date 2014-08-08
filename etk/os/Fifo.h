/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <etk/types.h>

#ifndef __ETK_MESSAGE_FIFO_H__
#define __ETK_MESSAGE_FIFO_H__

#include <etk/os/Mutex.h>
#include <etk/os/Semaphore.h>
#include <vector>

namespace etk {
	/**
	 * @brief Fifo tamplate is a simple messaged fifo element to
	 * transfer data message from a thead to an other.
	 * @param[in] MY_TYPE Type of the fifo message are tranfered.
	 */
	template<class MY_TYPE=int32_t> class Fifo {
		private :
			etk::Mutex m_mutex; //!< protection of the internal data.
			etk::Semaphore m_semaphore; //!< Message system to send event on an other thread.
			std::vector<MY_TYPE> m_data; //!< List of all message to send
		public :
			/**
			 * @brief Create a fifo with no message.
			 */
			Fifo() {
				// nothing to do ...
			};
			/**
			 * @brief Remove the fifo and all message inside.
			 */
			~Fifo() {
				// nothing to do ...
			};
			/**
			 * @brief Wait a message from the other thread. (no timeout set)
			 * @param[out] _data Data find in the fifo.
			 * @return true A data has been find.
			 * @return false No data found or closed fifo
			 */
			bool wait(MY_TYPE &_data) {
				m_mutex.lock();
				// Check if data is not previously here
				while(0==m_data.size()) {
					m_mutex.unLock();
					m_semaphore.wait();
					m_mutex.lock();
				}
				// End Waiting message :
				if (0<m_data.size()) {
					// copy element :
					_data = m_data[0];
					// remove element :
					m_data.erase(m_data.begin());
					// remove lock
					m_mutex.unLock();
					return true;
				}
				return false;
			};
			/**
			 * @brief Wait a message from the other thread, with a specified timeout.
			 * @param[out] _data keeped data from the fifo.
			 * @param[in] _timeOutInUs Time-out to wait a message in the fifo. It mightbespecify in micro-second.
			 * @return true We keep a massage.
			 * @return false No message found while time-out appear.
			 */
			bool wait(MY_TYPE &_data, uint32_t _timeOutInUs) {
				m_mutex.lock();
				// Check if data is not previously here
				while(0==m_data.size()) {
					m_mutex.unLock();
					if (false == m_semaphore.wait(_timeOutInUs)) {
						return false;
					}
					m_mutex.lock();
				}
				// End Waiting message :
				if (0<m_data.size()) {
					// copy element :
					_data = m_data[0];
					// remove element :
					m_data.erase(0);
					// remove lock
					m_mutex.unLock();
					return true;
				}
				return false;
			};
			/**
			 * @brief Get the number of message in the fifo.
			 * @return Number of message in the fifo.
			 */
			int32_t count() {
				m_mutex.lock();
				int32_t nbElement = m_data.size();
				m_mutex.unLock();
				return nbElement;
			};
			/**
			 * @brief Send a message at the other thread by setting a new message in the fifo.
			 * @param[in] _data New data to add at the fifo.
			 */
			void post(MY_TYPE &_data) {
				m_mutex.lock();
				m_data.push_back(_data);
				m_semaphore.post();
				m_mutex.unLock();
			};
			/**
			 * @brief Remove all the message in the fifo.
			 */
			void clean() {
				m_mutex.lock();
				// remove data
				m_data.clear();
				m_mutex.unLock();
				// remove semaphore
				m_semaphore.wait(0);
			};
	};
};

#endif
