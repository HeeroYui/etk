/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/types.h>
#include <etk/Stream.h>
#include <etk/DebugInternal.h>

#if defined(__TARGET_OS__Linux) && DEBUG_LEVEL > 2
	#include <execinfo.h>
	#include <cxxabi.h>
	#include <dlfcn.h>
	#define MAX_DEPTH  (256)
	void etk::DisplayBacktrace(void)
	{
		// retrieve call-stack
		void * trace[MAX_DEPTH];
		int stack_depth = backtrace(trace, MAX_DEPTH);
		
		TK_ERROR("Back-trace : ");
		for (int32_t i = 1; i < stack_depth; i++) {
			Dl_info dlinfo;
			if(!dladdr(trace[i], &dlinfo)) {
				break;
			}
			const char * symname = dlinfo.dli_sname;
			int    status;
			char * demangled = abi::__cxa_demangle(symname, NULL, 0, &status);
			if(status == 0 && demangled) {
				symname = demangled;
			}
			TK_WARNING("  " << dlinfo.dli_fname << ": ");
			TK_ERROR("        " << symname);
			if(NULL != demangled) {
				free(demangled);
			}
		}
		assert(false);
	}
#else
	void etk::DisplayBacktrace(void)
	{
		
	}
#endif

etk::CCout etk::cout;
etk::CEndl etk::endl;
etk::CStart etk::cstart;


#if defined(__TARGET_OS__Android)
#	include <android/log.h>
#endif

etk::CCout& etk::operator <<(etk::CCout &os, const etk::logLevel_te obj)
{
	switch (obj)
	{
		case LOG_LEVEL_CRITICAL:
			#if !defined(__TARGET_OS__Windows)
				os << ETK_BASH_COLOR_BOLD_RED;
			#endif
			#if defined(__TARGET_OS__Android)
				m_levelAndroid = ANDROID_LOG_FATAL;
			#endif
			os << "[C]";
			break;
		case LOG_LEVEL_ERROR:
			#if !defined(__TARGET_OS__Windows)
				os << ETK_BASH_COLOR_RED;
			#endif
			#if defined(__TARGET_OS__Android)
				m_levelAndroid = ANDROID_LOG_ERROR;
			#endif
			os << "[E]";
			break;
		case LOG_LEVEL_WARNING:
			#if !defined(__TARGET_OS__Windows)
				os << ETK_BASH_COLOR_MAGENTA;
			#endif
			#if defined(__TARGET_OS__Android)
				m_levelAndroid = ANDROID_LOG_WARN;
			#endif
			os << "[W]";
			break;
		case LOG_LEVEL_INFO:
			#if !defined(__TARGET_OS__Windows)
				os << ETK_BASH_COLOR_CYAN;
			#endif
			#if defined(__TARGET_OS__Android)
				m_levelAndroid = ANDROID_LOG_INFO;
			#endif
			os << "[I]";
			break;
		case LOG_LEVEL_DEBUG:
			#if !defined(__TARGET_OS__Windows)
				os << ETK_BASH_COLOR_YELLOW;
			#endif
			#if defined(__TARGET_OS__Android)
				m_levelAndroid = ANDROID_LOG_DEBUG;
			#endif
			os << "[D]";
			break;
		case LOG_LEVEL_VERBOSE:
			#if !defined(__TARGET_OS__Windows)
				os << ETK_BASH_COLOR_WHITE;
			#endif
			#if defined(__TARGET_OS__Android)
				m_levelAndroid = ANDROID_LOG_VERBOSE;
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
	#if defined(__TARGET_OS__Android)
		m_levelAndroid = 0;
	#endif
	memset(m_tmpChar, 0, (MAX_LOG_SIZE+1)*sizeof(char));
};


etk::CCout::~CCout()
{
	
};


etk::CCout& etk::CCout::operator << (const etk::UniChar& t)
{
	snprintf(tmp, MAX_LOG_SIZE_TMP, "%u", t.Get());
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	return *this;
}

etk::CCout& etk::CCout::operator << (int8_t t)
{
	snprintf(tmp, MAX_LOG_SIZE_TMP, "%d", t);
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	return *this;
}
etk::CCout& etk::CCout::operator << (int16_t t)
{
	snprintf(tmp, MAX_LOG_SIZE_TMP, "%d", t);
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	return *this;
}
etk::CCout& etk::CCout::operator << (int32_t t)
{
	snprintf(tmp, MAX_LOG_SIZE_TMP, "%d", t);
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	return *this;
}
etk::CCout& etk::CCout::operator << (int64_t t)
{
	#if __WORDSIZE == 64
		snprintf(tmp, MAX_LOG_SIZE_TMP, "%ld", t);
	#else
		snprintf(tmp, MAX_LOG_SIZE_TMP, "%lld", t);
	#endif
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	return *this;
}

etk::CCout& etk::CCout::operator << (uint8_t t)
{
	snprintf(tmp, MAX_LOG_SIZE_TMP, "%u", t);
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	return *this;
}
etk::CCout& etk::CCout::operator << (uint16_t t)
{
	snprintf(tmp, MAX_LOG_SIZE_TMP, "%u", t);
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	return *this;
}
etk::CCout& etk::CCout::operator << (uint32_t t)
{
	snprintf(tmp, MAX_LOG_SIZE_TMP, "%u", t);
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	return *this;
}
etk::CCout& etk::CCout::operator << (uint64_t t)
{
	#if __WORDSIZE == 64
		snprintf(tmp, MAX_LOG_SIZE_TMP, "%lu", t);
	#else
		snprintf(tmp, MAX_LOG_SIZE_TMP, "%llu", t);
	#endif
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	return *this;
}


etk::CCout& etk::CCout::operator << (double t)
{
	snprintf(tmp, MAX_LOG_SIZE_TMP, "%f", t);
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	return *this;
}


etk::CCout& etk::CCout::operator << (float t)
{
	snprintf(tmp, MAX_LOG_SIZE_TMP, "%f", t);
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	return *this;
}


etk::CCout& etk::CCout::operator << (char * t)
{
	snprintf(tmp, MAX_LOG_SIZE_TMP, "%s", t);
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	return *this;
}


etk::CCout& etk::CCout::operator << (const char * t)
{
	snprintf(tmp, MAX_LOG_SIZE_TMP, "%s", t);
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	return *this;
}


etk::CCout& etk::CCout::operator << (char t)
{
	snprintf(tmp, MAX_LOG_SIZE_TMP, "%c", t);
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
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
	__android_log_print(m_levelAndroid, "EWOL", "%s", m_tmpChar);
#else
	printf("%s", m_tmpChar);
#endif
	memset(m_tmpChar, 0, (MAX_LOG_SIZE+1)*sizeof(char));
	m_mutex.UnLock();
	return *this;
}



