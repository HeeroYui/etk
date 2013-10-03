/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_STREAM_H__
#define __ETK_STREAM_H__

#include <etk/types.h>
#include <etk/os/Mutex.h>

namespace etk
{
	#define MAX_LOG_SIZE		(16000)
	#define MAX_LOG_SIZE_TMP	(512)

	class CEndl{};
	class CStart{};
	
	class CCout{
		private:
			char             m_tmpChar[MAX_LOG_SIZE+1];
			char             tmp[MAX_LOG_SIZE_TMP];
			etk::Mutex       m_mutex;
			#if defined(__TARGET_OS__Android)
			public:
				int8_t       m_levelAndroid; //!< specific level for Android
			#endif
		public:
			CCout(void);
			~CCout(void);
			CCout& operator << (const etk::UniChar& _t);;
			CCout& operator << (int8_t _t);
			CCout& operator << (int16_t _t);
			CCout& operator << (int32_t _t);
			CCout& operator << (int64_t _t);
			CCout& operator << (uint8_t _t);
			CCout& operator << (uint16_t _t);
			CCout& operator << (uint32_t _t);
			CCout& operator << (uint64_t _t);
			CCout& operator << (double _t);
			CCout& operator << (float _t);
			CCout& operator << (char * _t);
			CCout& operator << (const char * _t);
			CCout& operator << (char _t);
			CCout& operator << (bool _t);
			CCout& operator << (CStart _ccc);
			CCout& operator << (etk::CEndl _t);
	};
	extern etk::CCout cout;
	extern etk::CEndl endl;
	extern etk::CStart cstart;
	
	typedef enum {
		LOG_LEVEL_NONE,
		LOG_LEVEL_CRITICAL,
		LOG_LEVEL_ERROR,
		LOG_LEVEL_WARNING,
		LOG_LEVEL_INFO,
		LOG_LEVEL_DEBUG,
		LOG_LEVEL_VERBOSE
	} logLevel_te;
	
	/**
	 * @brief Debug operator To display the curent element in a Human redeable information
	 */
	etk::CCout& operator <<(etk::CCout &_os, const etk::logLevel_te _obj);
	
	void displayBacktrace(void);
};

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


#endif

