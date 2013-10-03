/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/os/Semaphore.h>
#include <etk/DebugInternal.h>

etk::Semaphore::Semaphore(uint32_t _nbBasicElement, uint32_t _nbMessageMax)
{
	// create interface mutex :
	m_semaphore = createSemaphore(NULL, _nbBasicElement, _nbMessageMax, NULL);
	TK_ASSERT(m_semaphore != 0, "Error creating SEMAPHORE ...");
}


etk::Semaphore::~Semaphore(void)
{
	CloseHandle(m_semaphore);
}

uint32_t etk::Semaphore::getCount(void)
{
	LONG tmpData = 0;
	releaseSemaphore(m_semaphore, 0, &tmpData);
	return tmpData;
}

void etk::Semaphore::post(void)
{
	releaseSemaphore(m_semaphore, 1, NULL);
}


void etk::Semaphore::wait(void)
{
	waitForSingleObject(m_semaphore, INFINITE);
}


bool etk::Semaphore::wait(uint64_t _timeOutInUs)
{
	DWORD result = waitForSingleObject(m_semaphore, _timeOutInUs);
	if (result == WAIT_FAILED) {
		TK_ERROR("Failed to wait for semaphore ");
		return false;
	} else {
		return result == WAIT_OBJECT_0;
	}
}

