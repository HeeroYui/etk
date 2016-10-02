/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include <etk/etk.hpp>
#include <elog/log.hpp>
#include <etk/types.hpp>
#include <etk/debug.hpp>
#include <elog/elog.hpp>
#include <etk/os/FSNode.hpp>

void etk::init(int _argc, const char** _argv) {
	TK_INFO("E-TK system init (BEGIN) " << _argv[0]);
	elog::init(_argc, _argv);
	etk::setArgZero(_argv[0]);
	for (int32_t iii=0; iii<_argc ; ++iii) {
		std::string data = _argv[iii];
		if (    data == "-h"
		     || data == "--help") {
			TK_PRINT("etk - help : ");
			TK_PRINT("    " << _argv[0] << " [options]");
			/*
			TK_PRINT("        --etk-log-lib=name:X  Set a library specific level:");
			TK_PRINT("            name  Name of the library");
			TK_PRINT("            X     Log level to set [0..6]");
			*/
			TK_PRINT("        -h/--help: this help");
			TK_PRINT("    example:");
			TK_PRINT("        " << _argv[0] << " ...");
		} else if (etk::start_with(data, "--etk")) {
			TK_ERROR("Can not parse the argument : '" << data << "'");
		}
	}
	TK_INFO("E-TK system init (END)");
}

std::string etk::getApplicationName() {
	return etk::FSNodeGetApplicationName();
}
