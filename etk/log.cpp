/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/log.h>
#include <time.h>
#include <mutex>

#if defined(__TARGET_OS__Android)
#	include <android/log.h>
#endif

#include <etk/logIOs.h>

/*
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
*/
#ifdef DEBUG
	#define DEFAULT_LOG_LEVEL etk::log::logLevelInfo
	#define DEFAULT_LOG_COLOR true
	#define DEFAULT_LOG_LINE true
	#define DEFAULT_LOG_CLASS true
	#define DEFAULT_LOG_TIME true
#else
	#define DEFAULT_LOG_LEVEL etk::log::logLevelNone
	#define DEFAULT_LOG_COLOR false
	#define DEFAULT_LOG_LINE false
	#define DEFAULT_LOG_CLASS false
	#define DEFAULT_LOG_TIME true
#endif

enum etk::log::level& getDefaultLevel(void) {
	static enum etk::log::level g_val = DEFAULT_LOG_LEVEL;
	return g_val;
}

std::vector<std::pair<std::string, enum etk::log::level>>& getList(void) {
	static std::vector<std::pair<std::string, enum etk::log::level>> g_val;
	return g_val;
}

int32_t etk::log::registerInstance(const std::string& _name) {
	for (size_t iii = 0; iii < getList().size(); ++iii) {
		if (getList()[iii].first == _name) {
			return iii;
		}
	}
	getList().push_back(std::make_pair(_name, getDefaultLevel()));
	//std::cout << "register log : '" << _name << "'=" << getList().size()-1 << std::endl;
	return getList().size()-1;
}

void etk::log::setLevel(const std::string& _name, enum level _level) {
	for (size_t iii = 0; iii < getList().size(); ++iii) {
		if (getList()[iii].first == _name) {
			getList()[iii].second = _level;
			return;
		}
	}
	getList().push_back(std::make_pair(_name, _level));
}

void etk::log::setLevel(enum level _level) {
	getDefaultLevel() = _level;
	for (size_t iii = 0; iii < getList().size(); ++iii) {
		getList()[iii].second = _level;
	}
}

void etk::log::setLevel(int32_t _id, enum level _level) {
	if (_id < 0 || _id > (int32_t)getList().size()) {
		// ERROR...
		return;
	}
	getList()[_id].second = _level;
}


int32_t etk::log::getLevel(int32_t _id) {
	if (_id < 0 || _id > (int32_t)getList().size()) {
		// ERROR...
		return 0;
	}
	return (int32_t)getList()[_id].second;
}

std::vector<std::string> etk::log::getListInstance(void) {
	std::vector<std::string> out;
	for (size_t iii = 0; iii < getList().size(); ++iii) {
		out.push_back(getList()[iii].first);
	}
	return out;
}

void etk::log::logStream(int32_t _id, int32_t _level, int32_t _ligne, const char* _className, const char* _funcName, const std::ostream& _log) {
	std::ostringstream oss;
	oss << _log.rdbuf();
	std::string sss =oss.str();
	etk::log::logChar(_id, _level, _ligne, _className, _funcName, sss.c_str());
}

void etk::log::logChar1(int32_t _id, int32_t _level, const char* _log) {
	etk::log::logChar(_id, _level, -1, NULL, NULL, _log);
}

void etk::log::logStream1(int32_t _id, int32_t _level, const std::ostream& _log) {
	std::ostringstream oss;
	oss << _log.rdbuf();
	std::string sss =oss.str();
	etk::log::logChar(_id, _level, -1, NULL, NULL, sss.c_str());
}

static bool& getColor(void) {
	static bool g_val = DEFAULT_LOG_COLOR;
	return g_val;
}

void etk::log::setColor(bool _status) {
	getColor() = _status;
}

static bool& getTime(void) {
	static bool g_val = DEFAULT_LOG_TIME;
	return g_val;
}
void etk::log::setTime(bool _status) {
	getTime() = _status;
}

static bool& getLine(void) {
	static bool g_val = DEFAULT_LOG_LINE;
	return g_val;
}
void etk::log::setLine(bool _status) {
	getLine() = _status;
}

static bool& getFunction(void) {
	static bool g_val = DEFAULT_LOG_CLASS;
	return g_val;
}
void etk::log::setFunction(bool _status) {
	getFunction() = _status;
}


static void getDisplayTime(char* data) {
#ifdef __TARGET_OS__Android
	struct timeval  now;
	gettimeofday(&now, NULL);
	sprintf(data, " %2dh%2d'%2d | ", (int32_t)(now.tv_sec/3600)%24, (int32_t)(now.tv_sec/60)%60, (int32_t)(now.tv_sec%60));
#else
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	sprintf(data, " %2dh%2d'%2d | ", (timeinfo->tm_hour)%24, timeinfo->tm_min, timeinfo->tm_sec);
#endif
}

//regular colors
#define ETK_BASH_COLOR_BLACK			"\e[0;30m"
#define ETK_BASH_COLOR_RED				"\e[0;31m"
#define ETK_BASH_COLOR_GREEN			"\e[0;32m"
#define ETK_BASH_COLOR_YELLOW			"\e[0;33m"
#define ETK_BASH_COLOR_BLUE				"\e[0;34m"
#define ETK_BASH_COLOR_MAGENTA			"\e[0;35m"
#define ETK_BASH_COLOR_CYAN				"\e[0;36m"
#define ETK_BASH_COLOR_WHITE			"\e[0;37m"
//emphasized (bolded) colors
#define ETK_BASH_COLOR_BOLD_BLACK		"\e[1;30m"
#define ETK_BASH_COLOR_BOLD_RED			"\e[1;31m"
#define ETK_BASH_COLOR_BOLD_GREEN		"\e[1;32m"
#define ETK_BASH_COLOR_BOLD_YELLOW		"\e[1;33m"
#define ETK_BASH_COLOR_BOLD_BLUE		"\e[1;34m"
#define ETK_BASH_COLOR_BOLD_MAGENTA		"\e[1;35m"
#define ETK_BASH_COLOR_BOLD_CYAN		"\e[1;36m"
#define ETK_BASH_COLOR_BOLD_WHITE		"\e[1;37m"
//background colors
#define ETK_BASH_COLOR_BG_BLACK			"\e[40m"
#define ETK_BASH_COLOR_BG_RED			"\e[41m"
#define ETK_BASH_COLOR_BG_GREEN			"\e[42m"
#define ETK_BASH_COLOR_BG_YELLOW		"\e[43m"
#define ETK_BASH_COLOR_BG_BLUE			"\e[44m"
#define ETK_BASH_COLOR_BG_MAGENTA		"\e[45m"
#define ETK_BASH_COLOR_BG_CYAN			"\e[46m"
#define ETK_BASH_COLOR_BG_WHITE			"\e[47m"
// Return to the normal color setings
#define ETK_BASH_COLOR_NORMAL			"\e[0m"
//go to the Top of bash
#define ETK_BASH_GO_TOP					"\e[0;0f"


void etk::log::logChar(int32_t _id, int32_t _level, int32_t _ligne, const char* _className, const char* _funcName, const char* _log) {
	static std::mutex g_lock;
	char handle[1024] = "";
	memset(handle, ' ', 1024);
	handle[0] = '\0';
	char* pointer = handle;
	if(getColor() == true) {
		switch(_level) {
			default:
				// nothing to do ...
				break;
			case logLevelCritical:
				strcat(pointer, ETK_BASH_COLOR_BOLD_RED);
				break;
			case logLevelError:
				strcat(pointer, ETK_BASH_COLOR_RED);
				break;
			case logLevelWarning:
				strcat(pointer, ETK_BASH_COLOR_MAGENTA);
				break;
			case logLevelInfo:
				strcat(pointer, ETK_BASH_COLOR_CYAN);
				break;
			case logLevelDebug:
				strcat(pointer, ETK_BASH_COLOR_YELLOW);
				break;
			case logLevelVerbose:
				strcat(pointer, ETK_BASH_COLOR_WHITE);
				break;
		}
		pointer = handle+strlen(handle);
	}
	if(getTime() == true) {
		getDisplayTime(pointer);
		pointer = handle+strlen(handle);
	}
	#if !defined(__TARGET_OS__Android)
		switch(_level) {
			default:
				strcat(pointer, "[?] ");
				break;
			case logLevelCritical:
				strcat(pointer, "[C] ");
				break;
			case logLevelError:
				strcat(pointer, "[E] ");
				break;
			case logLevelWarning:
				strcat(pointer, "[W] ");
				break;
			case logLevelInfo:
				strcat(pointer, "[I] ");
				break;
			case logLevelDebug:
				strcat(pointer, "[D] ");
				break;
			case logLevelVerbose:
				strcat(pointer, "[V] ");
				break;
		}
		pointer = handle+strlen(handle);
	#endif
	if (_id >= 0) {
		int32_t len = strlen(handle);
		strcat(pointer, getList()[_id].first.c_str());
		pointer = handle+strlen(handle);
		while (strlen(handle) - len < 8) {
			*pointer++ = ' ';
			*pointer = '\0';
		}
		*pointer++ = '|';
		*pointer++ = ' ';
		*pointer = '\0';
	}
	if(getLine() == true) {
		if (_ligne >= 0) {
			sprintf(pointer, "(l=%5d)", _ligne);
			pointer = handle+strlen(handle);
			*pointer++ = ' ';
			*pointer = '\0';
		}
	}
	if(getFunction() == true) {
		int32_t len = strlen(handle);
		if (_className != NULL) {
			snprintf(pointer, 70, "%s::", _className);
			pointer = handle+strlen(handle);
		}
		if (_funcName != NULL) {
			snprintf(pointer, 70, "%s", _funcName);
			pointer = handle+strlen(handle);
		}
		while (strlen(handle) - len < 60) {
			*pointer++ = ' ';
			*pointer = '\0';
		}
		*pointer++ = '|';
		*pointer++ = ' ';
		*pointer = '\0';
	}
	if (strlen(_log) > 1024-strlen(handle)-20) {
		memcpy(pointer, _log, 1024-strlen(handle)-21);
		handle[1024-25] = ' ';
		handle[1024-24] = '.';
		handle[1024-23] = '.';
		handle[1024-22] = '.';
		handle[1024-21] = '\0';
	} else {
		strcat(pointer, _log);
	}
	pointer = handle+strlen(handle);
	if(getColor() == true) {
		strcat(pointer, ETK_BASH_COLOR_NORMAL);
	}
	
	g_lock.lock();
	#if defined(__TARGET_OS__Android)
		// TODO : Set package name instead of ewol ...
		switch(_level) {
			default:
				__android_log_print(ANDROID_LOG_VERBOSE, "EWOL", "%s", handle);
				break;
			case logLevelCritical:
				__android_log_print(ANDROID_LOG_FATAL, "EWOL", "%s", handle);
				break;
			case logLevelError:
				__android_log_print(ANDROID_LOG_ERROR, "EWOL", "%s", handle);
				break;
			case logLevelWarning:
				__android_log_print(ANDROID_LOG_WARN, "EWOL", "%s", handle);
				break;
			case logLevelInfo:
				__android_log_print(ANDROID_LOG_INFO, "EWOL", "%s", handle);
				break;
			case logLevelDebug:
				__android_log_print(ANDROID_LOG_DEBUG, "EWOL", "%s", handle);
				break;
			case logLevelVerbose:
				__android_log_print(ANDROID_LOG_VERBOSE, "EWOL", "%s", handle);
				break;
		}
	#elif defined(__TARGET_OS__IOs)
		iosNSLog(handle);
	#else
		std::cout << handle << std::endl;
	#endif
	g_lock.unlock();
}


