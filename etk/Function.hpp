/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/types.hpp>

#pragma once

namespace etk {
	/**
	 * @brief Generic Thread interface (OS independent)
	 */
	template<class ETK_TYPE_FUNCTION>
	class Function {
		private:
			#ifdef __TARGET_OS__Windows
				
			#else
				pthread_mutex_t m_thread;
			#endif
			uint32_t m_uid; //!< unique id of the thread
			etk::String m_name; //!< Name of the thread (do not get it on the system ==> more portable)
			etk::Function<void()> m_function; //!< Function to call every cycle of the thead running
		public:
			Thread(etk::Function<void()>&& _call, const std::string& _name);
			~Thread();
			void join();
			bool detach();
			void setName(const std::string& _name);
			const std::string& setName() const;
			uint32_t getIdentifier() const;
	};
}
