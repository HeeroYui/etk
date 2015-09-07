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

#include <mutex>
#include <vector>
#include <condition_variable>

namespace etk {
	/**
	 * @brief Fifo tamplate is a simple messaged fifo element to
	 * transfer data message from a thead to an other.
	 * @param[in] MY_TYPE Type of the fifo message are tranfered.
	 */
	template<class MY_TYPE=int32_t> class Fifo {
		private :
			std::mutex m_mutex; //!< protection of the internal data.
			std::condition_variable m_condition; //!< Message system to send event on an other thread.
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
				std::unique_lock<std::mutex> lock(m_mutex);
				// Check if data is not previously here
				while(m_data.size() == 0) {
					m_condition.wait(lock);
				}
				// End Waiting message :
				if (m_data.size() > 0) {
					// copy element :
					std::swap(_data, m_data[0]);
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
				std::unique_lock<std::mutex> lock(m_mutex);
				// Check if data is not previously here
				while(m_data.size() == 0) {
					if (m_condition.wait_for(lock, std::chrono::microseconds(_timeOutInUs)) == std::cv_status::timeout) {
						return false;
					}
				}
				// End Waiting message :
				if (m_data.size() > 0) {
					// copy element :
					std::swap(_data, m_data[0]);
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
				std::unique_lock<std::mutex> lock(m_mutex);
				int32_t nbElement = m_data.size();
				return nbElement;
			};
			/**
			 * @brief Send a message at the other thread by setting a new message in the fifo.
			 * @param[in] _data New data to add at the fifo.
			 */
			void post(MY_TYPE &_data) {
				std::unique_lock<std::mutex> lock(m_mutex);
				m_data.push_back(_data);
				m_condition.notify_all();
			};
			//! @previous
			void post(const MY_TYPE &_data) {
				std::unique_lock<std::mutex> lock(m_mutex);
				m_data.push_back(_data);
				m_condition.notify_all();
			};
			/**
			 * @brief Remove all the message in the fifo.
			 */
			void clean() {
				std::unique_lock<std::mutex> lock(m_mutex);
				// remove data
				m_data.clear();
				m_condition.wait_for(lock, std::chrono::microseconds(0));
			};
	};
};

#endif
