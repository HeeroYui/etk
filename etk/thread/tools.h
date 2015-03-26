/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <etk/types.h>

#ifndef __ETK_THREAD_TOOLS_H__
#define __ETK_THREAD_TOOLS_H__

#include <etk/thread.h>

namespace etk {
	namespace thread {
		/**
		 * @brief get human readable thread ID. (not the std::thread::get_id())
		 * @return the ID of the thread.
		 */
		uint32_t getId();
		/**
		 * @brief get human readable thread ID. (not the std::thread::get_id())
		 * @param[in] _thread Thread handle
		 * @return the ID of the thread.
		 */
		uint32_t getId(std11::thread& _thread);
		/**
		 * @brief Set the Current thread name
		 * @param[in] _name New name of the thread
		 */
		void setName(const std::string& _name);
		/**
		 * @brief Set an other thread name
		 * @param[in] _thread Thread handle
		 * @param[in] _name New name of the thread
		 */
		void setName(std11::thread& _thread, const std::string& _name);
		/**
		 * @brief Set the Current thread name
		 * @return The current name of the thread
		 */
		std::string getName();
		/**
		 * @brief Get an other thread name
		 * @praram[in] _thread Thread handle
		 * @return The external thread name of the thread
		 */
		std::string getName(std11::thread& _thread);
		/**
		 * @brief Set the Current thread priority [-20..0] for RT and ]0..50] for normal priority
		 * @param[in] _priority New priority of the thread
		 * @note If your process have not the right to change thread name, it does not work
		 */
		void setPriority(int32_t _priority);
		/**
		 * @brief Set an other thread priority [-20..0] for RT and ]0..50] for normal priority
		 * @param[in] _thread Thread handle
		 * @param[in] _priority New priority of the thread
		 * @note If your process have not the right to change thread name, it does not work
		 */
		void setPriority(std11::thread& _thread, int32_t _priority);
		/**
		 * @brief get the Current thread priority [-20..0] for RT and ]0..50] for normal priority
		 * @return current priority of the thread
		 */
		int32_t getPriority();
		/**
		 * @brief Get an other thread priority [-20..0] for RT and ]0..50] for normal priority
		 * @param[in] _thread Thread handle
		 * @return current priority of the thread
		 */
		int32_t getPriority(std11::thread& _thread);
	}
}

#endif