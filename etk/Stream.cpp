/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/types.h>
#include <etk/Stream.h>

etk::CCout etk::cout;
etk::CEndl etk::endl;
etk::CHex etk::hex;
etk::CStart etk::cstart;


#if defined(__TARGET_OS__Android)
#	include <android/log.h>
#	define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "EWOL", __VA_ARGS__))
#	define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "EWOL", __VA_ARGS__))
#	define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "EWOL", __VA_ARGS__))
#endif

etk::CCout& etk::operator <<(etk::CCout &os, const etk::logLevel_te obj)
{
	switch (obj)
	{
		case LOG_LEVEL_CRITICAL:
			#if !defined(__TARGET_OS__Windows)
				os << ETK_BASH_COLOR_BOLD_RED;
			#endif
			os << "[C]";
			break;
		case LOG_LEVEL_ERROR:
			#if !defined(__TARGET_OS__Windows)
				os << ETK_BASH_COLOR_RED;
			#endif
			os << "[E]";
			break;
		case LOG_LEVEL_WARNING:
			#if !defined(__TARGET_OS__Windows)
				os << ETK_BASH_COLOR_MAGENTA;
			#endif
			os << "[W]";
			break;
		case LOG_LEVEL_INFO:
			#if !defined(__TARGET_OS__Windows)
				os << ETK_BASH_COLOR_CYAN;
			#endif
			os << "[I]";
			break;
		case LOG_LEVEL_DEBUG:
			#if !defined(__TARGET_OS__Windows)
				os << ETK_BASH_COLOR_YELLOW;
			#endif
			os << "[D]";
			break;
		case LOG_LEVEL_VERBOSE:
			#if !defined(__TARGET_OS__Windows)
				os << ETK_BASH_COLOR_WHITE;
			#endif
			os << "[V]";
			break;
		default:
			os << "[?]";
			break;
	}
	return os;
}



etk::CCout::CCout()
{
	hex=false;
	memset(m_tmpChar, 0, (MAX_LOG_SIZE+1)*sizeof(char));
};


etk::CCout::~CCout()
{
	
};


etk::CCout& etk::CCout::operator << (CHex t)
{
	hex = true;
	return *this;
}


etk::CCout& etk::CCout::operator << (int t)
{
	snprintf(tmp, MAX_LOG_SIZE_TMP, "%d", t);
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	hex = false;
	return *this;
}


etk::CCout& etk::CCout::operator << (unsigned int t)
{
	snprintf(tmp, MAX_LOG_SIZE_TMP, "%u", t);
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	hex = false;
	return *this;
}


etk::CCout& etk::CCout::operator << (long t)
{
	if (true == hex) {
		snprintf(tmp, MAX_LOG_SIZE_TMP, "0x%08X", (unsigned int)t);
		strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
		hex = false;
	} else {
		snprintf(tmp, MAX_LOG_SIZE_TMP, "%ld", t);
		strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	}
	return *this;
}


etk::CCout& etk::CCout::operator << (long long t)
{
	if (true == hex) {
		snprintf(tmp, MAX_LOG_SIZE_TMP, "0x%08X%08X", (unsigned int)(t>>32), (unsigned int)(t));
		strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
		hex = false;
	} else {
		snprintf(tmp, MAX_LOG_SIZE_TMP, "%lld", t);
		strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	}
	return *this;
}


etk::CCout& etk::CCout::operator << (double t)
{
	snprintf(tmp, MAX_LOG_SIZE_TMP, "%f", t);
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	hex = false;
	return *this;
}


etk::CCout& etk::CCout::operator << (float t)
{
	snprintf(tmp, MAX_LOG_SIZE_TMP, "%f", t);
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	hex = false;
	return *this;
}


etk::CCout& etk::CCout::operator << (char * t)
{
	snprintf(tmp, MAX_LOG_SIZE_TMP, "%s", t);
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	hex = false;
	return *this;
}


etk::CCout& etk::CCout::operator << (const char * t)
{
	snprintf(tmp, MAX_LOG_SIZE_TMP, "%s", t);
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	hex = false;
	return *this;
}


etk::CCout& etk::CCout::operator << (char t)
{
	snprintf(tmp, MAX_LOG_SIZE_TMP, "%c", t);
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	hex = false;
	return *this;
}


etk::CCout& etk::CCout::operator << (bool t)
{
	if (t) {
		strncat(m_tmpChar, "true", MAX_LOG_SIZE);
	} else {
		strncat(m_tmpChar, "false", MAX_LOG_SIZE);
	}
	return *this;
}


etk::CCout& etk::CCout::operator << (CStart ccc)
{
	m_mutex.Lock();
	return *this;
}


etk::CCout& etk::CCout::operator << (etk::CEndl t)
{
	strncat(m_tmpChar, ETK_BASH_COLOR_NORMAL, MAX_LOG_SIZE);
	strncat(m_tmpChar, "\n", MAX_LOG_SIZE);
	m_tmpChar[MAX_LOG_SIZE] = '\0';
#if defined(__TARGET_OS__Android)
	LOGI("%s", m_tmpChar);
#else
	printf("%s", m_tmpChar);
#endif
	memset(m_tmpChar, 0, (MAX_LOG_SIZE+1)*sizeof(char));
	m_mutex.UnLock();
	return *this;
}



