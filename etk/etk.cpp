/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/etk.hpp>
#include <elog/log.hpp>
#include <etk/types.hpp>
#include <etk/debug.hpp>
#include <elog/elog.hpp>
#include <etk/os/FSNode.hpp>

static int32_t nbTimeInit = 0;

void etk::unInit() {
	if (nbTimeInit > 1) {
		nbTimeInit--;
		// not the time to uninit
		return;
	}
	nbTimeInit--;
	if (nbTimeInit < 0) {
		TK_ERROR("E-TK system un-init More un-init than init ...");
		nbTimeInit = 0;
		return;
	}
	TK_INFO("E-TK system un-init (BEGIN)");
	TK_INFO("E-TK system un-init (END)");
}

void etk::init(int _argc, const char** _argv) {
	if (nbTimeInit > 0) {
		nbTimeInit++;
		// already init
		return;
	}
	nbTimeInit++;
	if (_argc >= 1) {
		TK_INFO("E-TK system init (BEGIN) " << _argv[0]);
	} else {
		TK_INFO("E-TK system init (BEGIN) ");
	}
	elog::init(_argc, _argv);
	#if !defined(__TARGET_OS__Android) and !defined(__TARGET_OS__IOs)
		// This action is done by the main wrapper...
		if (_argc >= 1) {
			etk::setArgZero(_argv[0]);
		}
	#endif
	
	for (int32_t iii=0; iii<_argc ; ++iii) {
		std::string data = _argv[iii];
		if (    data == "-h"
		     || data == "--help") {
			TK_PRINT("etk - help : ");
			if (_argc >= 1) {
				TK_PRINT("    " << _argv[0] << " [options]");
			}
			/*
			TK_PRINT("        --etk-log-lib=name:X  Set a library specific level:");
			TK_PRINT("            name  Name of the library");
			TK_PRINT("            X     Log level to set [0..6]");
			*/
			TK_PRINT("        -h/--help: this help");
		} else if (etk::start_with(data, "--etk")) {
			TK_ERROR("Can not parse the argument : '" << data << "'");
		}
	}
	TK_INFO("E-TK system init (END)");
}

std::string etk::getApplicationName() {
	return etk::FSNodeGetApplicationName();
}
