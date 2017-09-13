/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/types.hpp>

#pragma once

#include <ethread/Mutex.hpp>
#include <ethread/Semaphore.hpp>
#include <etk/Vector.hpp>

namespace etk {
	/**
	 * @brief Fifo tamplate is a simple messaged fifo element to
	 * transfer data message from a thead to an other.
	 * @param[in] MY_TYPE Type of the fifo message are tranfered.
	 */
	template<class MY_TYPE=int32_t> class Fifo {
		private :
			ethread::Mutex m_mutex; //!< protection of the internal data.
			ethread::Semaphore m_semaphore; //!< protection of the internal data.
			etk::Vector<MY_TYPE> m_data; //!< List of all message to send
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
				// Check if data is not previously here
				while(m_data.size() == 0) {
					m_semaphore.wait();
				}
				ethread::UniqueLock lock(m_mutex);
				// End Waiting message :
				if (m_data.size() > 0) {
					// copy element :
					etk::swap(_data, m_data[0]);
					// remove element :
					m_data.erase(m_data.begin());
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
				// Check if data is not previously here
				while(m_data.size() == 0) {
					if (m_semaphore.wait(_timeOutInUs) == false) {
						return false;
					}
				}
				ethread::UniqueLock lock(m_mutex);
				// End Waiting message :
				if (m_data.size() > 0) {
					// copy element :
					etk::swap(_data, m_data[0]);
					// remove element :
					m_data.erase(0);
					return true;
				}
				return false;
			};
			/**
			 * @brief Get the number of message in the fifo.
			 * @return Number of message in the fifo.
			 */
			int32_t count() {
				ethread::UniqueLock lock(m_mutex);
				int32_t nbElement = m_data.size();
				return nbElement;
			};
			/**
			 * @brief Send a message at the other thread by setting a new message in the fifo.
			 * @param[in] _data New data to add at the fifo.
			 */
			void post(MY_TYPE &_data) {
				ethread::UniqueLock lock(m_mutex);
				m_data.pushBack(_data);
				m_semaphore.post();
			};
			/**
			 * @brief Send a message at the other thread by setting a new message in the fifo.
			 * @param[in] _data New data to add at the fifo.
			 */
			void post(const MY_TYPE &_data) {
				ethread::UniqueLock lock(m_mutex);
				m_data.pushBack(_data);
				m_semaphore.post();
			};
			/**
			 * @brief Remove all the message in the fifo.
			 */
			void clean() {
				ethread::UniqueLock lock(m_mutex);
				// remove data
				m_data.clear();
				//m_condition.wait_for(lock, echrono::microseconds(0));
				m_semaphore.post();
			};
	};
}

