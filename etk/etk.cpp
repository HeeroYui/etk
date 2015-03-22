/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <etk/etk.h>
#include <etk/log.h>
#include <etk/types.h>
#include <etk/debug.h>
#include <etk/os/FSNode.h>


void etk::init(int _argc, char** _argv) {
	etk::setArgZero(_argv[0]);
	//etk::initDefaultFolder("river_sample_read");
	for (int32_t iii=0; iii<_argc ; ++iii) {
		std::string data = _argv[iii];
		if (data == "-l0") {
			etk::log::setLevel(etk::log::logLevelNone);
		} else if (data == "-l1") {
			etk::log::setLevel(etk::log::logLevelCritical);
		} else if (data == "-l2") {
			etk::log::setLevel(etk::log::logLevelError);
		} else if (data == "-l3") {
			etk::log::setLevel(etk::log::logLevelWarning);
		} else if (data == "-l4") {
			etk::log::setLevel(etk::log::logLevelInfo);
		} else if (data == "-l5") {
			etk::log::setLevel(etk::log::logLevelDebug);
		} else if (data == "-l6") {
			etk::log::setLevel(etk::log::logLevelVerbose);
		} else if (    data == "-h"
		            || data == "--help") {
			etk::log::setLevel(etk::log::logLevelInfo);
			TK_INFO("etk - help : ");
			TK_INFO("    ./" << _argv[0] << " [options]");
			TK_INFO("        -l0: debug None");
			TK_INFO("        -l1: debug Critical");
			TK_INFO("        -l2: debug Error");
			TK_INFO("        -l3: debug Warning");
			TK_INFO("        -l4: debug Info");
			TK_INFO("        -l5: debug Debug");
			TK_INFO("        -l6: debug Verbose");
			TK_INFO("        -h/--help: this help");
		}
	}
}