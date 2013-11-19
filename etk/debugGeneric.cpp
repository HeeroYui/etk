/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/debugGeneric.h>
#include <time.h>

// Max string size : (wide screan console nb caractere)
#define EDN_LOG_MAX_LENGTH 250


#define FUNCTION_NAME_SIZE	(70)

void debug::displayFuncName(int32_t _ligne, const char* _className, const char* _funcName, const char* _libName)
{
	char tmpName[FUNCTION_NAME_SIZE] = "";
	
	if (NULL == _className) {
		if (NULL == _libName) {
			snprintf(tmpName, FUNCTION_NAME_SIZE-1, "???????? | (l=%5d) %s                                             ",_ligne, _funcName);
		} else {
			snprintf(tmpName, FUNCTION_NAME_SIZE-1, "%s | (l=%5d) %s                                             ",_libName, _ligne, _funcName);
		}
	} else {
		if (NULL == _libName) {
			snprintf(tmpName, FUNCTION_NAME_SIZE-1, "???????? | (l=%5d) %s::%s                                             ",_ligne, _className, _funcName);
		} else {
			snprintf(tmpName, FUNCTION_NAME_SIZE-1, "%s | (l=%5d) %s::%s                                             ", _libName, _ligne, _className, _funcName);
		}
	}
	tmpName[FUNCTION_NAME_SIZE-4] = ' ';
	tmpName[FUNCTION_NAME_SIZE-3] = '|';
	tmpName[FUNCTION_NAME_SIZE-2] = ' ';
	tmpName[FUNCTION_NAME_SIZE-1] = '\0';
	etk::cout << tmpName;
}

void debug::displayTime(void)
{
	char tmpdata[50];
#ifdef __TARGET_OS__Android
	struct timeval  now;
	gettimeofday(&now, NULL);
	sprintf(tmpdata, " %2dh%2d'%2d | ", (int32_t)(now.tv_sec/3600)%24, (int32_t)(now.tv_sec/60)%60, (int32_t)(now.tv_sec%60));
#else
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	sprintf(tmpdata, " %2dh%2d'%2d | ", (timeinfo->tm_hour)%24, timeinfo->tm_min, timeinfo->tm_sec);
#endif
	etk::cout << tmpdata ;
}


#ifdef __TARGET_OS__Android
enum etk::logLevel g_requestedLevel = etk::logLevelDebug;
#else
enum etk::logLevel g_requestedLevel = etk::logLevelWarning;
#endif
void debug::setGeneralLevel(enum etk::logLevel _ccc) {
	g_requestedLevel = _ccc;
}

