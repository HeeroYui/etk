/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_MESSAGE_FIFO_H__
#define __ETK_MESSAGE_FIFO_H__

#include <etk/os/Mutex.h>
#include <etk/os/Semaphore.h>
#include <vector>

namespace etk
{
	template<class MY_TYPE=int32_t> class MessageFifo
	{
		private :
			etk::Mutex m_mutex;
			etk::Semaphore m_semaphore;
			std::vector<MY_TYPE> m_data;
		public :
			MessageFifo(void)
			{
				// nothing to do ...
			};
			~MessageFifo(void)
			{
				// nothing to do ...
			};
			
			bool wait(MY_TYPE &_data)
			{
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
			bool wait(MY_TYPE &_data, uint32_t _timeOutInUs)
			{
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
			int32_t count(void)
			{
				m_mutex.lock();
				int32_t nbElement = m_data.size();
				m_mutex.unLock();
				return nbElement;
			};
			void post(MY_TYPE &_data)
			{
				m_mutex.lock();
				m_data.push_back(_data);
				m_semaphore.post();
				m_mutex.unLock();
			};
			void clean(void)
			{
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
