/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/types.h>
#include <etk/Stream.h>
#include <etk/debug.h>

#if defined(__TARGET_OS__Linux) && DEBUG_LEVEL > 2
	#include <execinfo.h>
	#include <cxxabi.h>
	#include <dlfcn.h>
	#define MAX_DEPTH  (256)
	void etk::displayBacktrace(bool _breakAtEnd) {
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
		if (_breakAtEnd == true) {
			assert(false);
		}
	}
#else
	void etk::displayBacktrace(bool _breakAtEnd) {
		#if DEBUG_LEVEL > 2
			assert(false);
		#endif
	}
#endif

etk::CCout etk::cout;
etk::CEndl etk::endl;
etk::CStart etk::cstart;


#if defined(__TARGET_OS__Android)
#	include <android/log.h>
#endif

etk::CCout& etk::operator <<(etk::CCout &_os, const enum etk::logLevel _obj)
{
	switch (_obj)
	{
		case logLevelCritical:
			#if !defined(__TARGET_OS__Windows)
				_os << ETK_BASH_COLOR_BOLD_RED;
			#endif
			#if defined(__TARGET_OS__Android)
				_os.m_levelAndroid = ANDROID_LOG_FATAL;
			#else
				_os << "[C]";
			#endif
			break;
		case logLevelError:
			#if !defined(__TARGET_OS__Windows)
				_os << ETK_BASH_COLOR_RED;
			#endif
			#if defined(__TARGET_OS__Android)
				_os.m_levelAndroid = ANDROID_LOG_ERROR;
			#else 
				_os << "[E]";
			#endif
			break;
		case logLevelWarning:
			#if !defined(__TARGET_OS__Windows)
				_os << ETK_BASH_COLOR_MAGENTA;
			#endif
			#if defined(__TARGET_OS__Android)
				_os.m_levelAndroid = ANDROID_LOG_WARN;
			#else
				_os << "[W]";
			#endif
			break;
		case logLevelInfo:
			#if !defined(__TARGET_OS__Windows)
				_os << ETK_BASH_COLOR_CYAN;
			#endif
			#if defined(__TARGET_OS__Android)
				_os.m_levelAndroid = ANDROID_LOG_INFO;
			#else
				_os << "[I]";
			#endif
			break;
		case logLevelDebug:
			#if !defined(__TARGET_OS__Windows)
				_os << ETK_BASH_COLOR_YELLOW;
			#endif
			#if defined(__TARGET_OS__Android)
				_os.m_levelAndroid = ANDROID_LOG_DEBUG;
			#else
				_os << "[D]";
			#endif
			break;
		case logLevelVerbose:
			#if !defined(__TARGET_OS__Windows)
				_os << ETK_BASH_COLOR_WHITE;
			#endif
			#if defined(__TARGET_OS__Android)
				_os.m_levelAndroid = ANDROID_LOG_VERBOSE;
			#else
				_os << "[V]";
			#endif
			break;
		default:
			#if !defined(__TARGET_OS__Android)
				_os << "[?]";
			#endif
			break;
	}
	return _os;
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


etk::CCout& etk::CCout::operator << (const etk::UChar& _t)
{
	char output[5];
	_t.getUtf8(output);
	snprintf(tmp, MAX_LOG_SIZE_TMP, "%s", output);
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	return *this;
}

etk::CCout& etk::CCout::operator << (int8_t _t)
{
	snprintf(tmp, MAX_LOG_SIZE_TMP, "%d", _t);
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	return *this;
}
etk::CCout& etk::CCout::operator << (int16_t _t)
{
	snprintf(tmp, MAX_LOG_SIZE_TMP, "%d", _t);
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	return *this;
}
etk::CCout& etk::CCout::operator << (int32_t _t)
{
	snprintf(tmp, MAX_LOG_SIZE_TMP, "%d", _t);
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	return *this;
}
etk::CCout& etk::CCout::operator << (int64_t _t)
{
	#if __WORDSIZE == 64
		snprintf(tmp, MAX_LOG_SIZE_TMP, "%ld", _t);
	#else
		snprintf(tmp, MAX_LOG_SIZE_TMP, "%lld", _t);
	#endif
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	return *this;
}

etk::CCout& etk::CCout::operator << (uint8_t _t)
{
	snprintf(tmp, MAX_LOG_SIZE_TMP, "%u", _t);
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	return *this;
}
etk::CCout& etk::CCout::operator << (uint16_t _t)
{
	snprintf(tmp, MAX_LOG_SIZE_TMP, "%u", _t);
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	return *this;
}
etk::CCout& etk::CCout::operator << (uint32_t _t)
{
	snprintf(tmp, MAX_LOG_SIZE_TMP, "%u", _t);
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	return *this;
}
etk::CCout& etk::CCout::operator << (uint64_t _t)
{
	#if __WORDSIZE == 64
		snprintf(tmp, MAX_LOG_SIZE_TMP, "%lu", _t);
	#else
		snprintf(tmp, MAX_LOG_SIZE_TMP, "%llu", _t);
	#endif
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	return *this;
}


etk::CCout& etk::CCout::operator << (double _t)
{
	snprintf(tmp, MAX_LOG_SIZE_TMP, "%f", _t);
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	return *this;
}


etk::CCout& etk::CCout::operator << (float _t)
{
	snprintf(tmp, MAX_LOG_SIZE_TMP, "%f", _t);
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	return *this;
}


etk::CCout& etk::CCout::operator << (char * _t)
{
	snprintf(tmp, MAX_LOG_SIZE_TMP, "%s", _t);
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	return *this;
}


etk::CCout& etk::CCout::operator << (const char * _t)
{
	snprintf(tmp, MAX_LOG_SIZE_TMP, "%s", _t);
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	return *this;
}


etk::CCout& etk::CCout::operator << (char _t)
{
	snprintf(tmp, MAX_LOG_SIZE_TMP, "%c", _t);
	strncat(m_tmpChar, tmp, MAX_LOG_SIZE);
	return *this;
}


etk::CCout& etk::CCout::operator << (bool _t)
{
	if (_t) {
		strncat(m_tmpChar, "true", MAX_LOG_SIZE);
	} else {
		strncat(m_tmpChar, "false", MAX_LOG_SIZE);
	}
	return *this;
}


etk::CCout& etk::CCout::operator << (CStart _ccc)
{
	m_mutex.lock();
	return *this;
}


etk::CCout& etk::CCout::operator << (etk::CEndl _t)
{
#if !defined(__TARGET_OS__Windows)
	strncat(m_tmpChar, ETK_BASH_COLOR_NORMAL, MAX_LOG_SIZE);
#endif
	strncat(m_tmpChar, "\n", MAX_LOG_SIZE);
	m_tmpChar[MAX_LOG_SIZE] = '\0';
#if defined(__TARGET_OS__Android)
	__android_log_print(m_levelAndroid, "EWOL", "%s", m_tmpChar);
#else
	printf("%s", m_tmpChar);
#endif
	memset(m_tmpChar, 0, (MAX_LOG_SIZE+1)*sizeof(char));
	m_mutex.unLock();
	return *this;
}



