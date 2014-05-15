/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */


#include <etk/os/Mutex.h>

etk::Mutex::Mutex()
{
	InitializeCriticalSection(&m_mutex);
}


etk::Mutex::~Mutex()
{
	DeleteCriticalSection(&m_mutex);
}


void etk::Mutex::lock()
{
	EnterCriticalSection(&m_mutex);
}


bool etk::Mutex::tryLock()
{
	return TryEnterCriticalSection(&m_mutex) != 0;
}


void etk::Mutex::unLock()
{
	LeaveCriticalSection(&m_mutex);
}

