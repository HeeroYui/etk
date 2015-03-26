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

static etk::log::level getLogLevel(const std::string& _value) {
	if (_value == "0") {
		return etk::log::logLevelNone;
	} else if (_value == "1") {
		return etk::log::logLevelCritical;
	} else if (_value == "2") {
		return etk::log::logLevelError;
	} else if (_value == "3") {
		return etk::log::logLevelWarning;
	} else if (_value == "4") {
		return etk::log::logLevelInfo;
	} else if (_value == "5") {
		return etk::log::logLevelDebug;
	} else if (_value == "6") {
		return etk::log::logLevelVerbose;
	}
	TK_ERROR("Unknow log level : " << _value);
	return etk::log::logLevelVerbose;
}

void etk::init(int _argc, char** _argv) {
	TK_INFO("E-TK system init (BEGIN)");
	etk::setArgZero(_argv[0]);
	for (int32_t iii=0; iii<_argc ; ++iii) {
		std::string data = _argv[iii];
		if (etk::start_with(data, "--etk-log-level=")) {
			etk::log::setLevel(getLogLevel(std::string(data.begin()+16, data.end())));
		} else if (etk::start_with(data, "-l=")) {
			etk::log::setLevel(getLogLevel(std::string(data.begin()+2, data.end())));
		} else if (etk::start_with(data, "--etk-log-color")) {
			etk::log::setColor(true);
		} else if (etk::start_with(data, "--etk-log-no-color")) {
			etk::log::setColor(false);
		} else if (etk::start_with(data, "--etk-log-config=")) {
			std::string value(data.begin()+17, data.end());
			etk::log::setTime(false);
			etk::log::setLine(false);
			etk::log::setFunction(false);
			etk::log::setLibName(false);
			etk::log::setThreadId(false);
			etk::log::setThreadNameEnable(false);
			for (size_t iii=0; iii<value.size(); ++iii) {
				if (value[iii] == 't') {
					etk::log::setTime(true);
				} else if (value[iii] == 'T') {
					etk::log::setThreadId(true);
				} else if (value[iii] == 'N') {
					etk::log::setThreadNameEnable(true);
				} else if (value[iii] == 'L') {
					etk::log::setLine(true);
				} else if (value[iii] == 'l') {
					etk::log::setLibName(true);
				} else if (value[iii] == 'f') {
					etk::log::setFunction(true);
				} else {
					TK_ERROR("In program argument: --etk-log-config= , the value '" << value[iii] << "' is not supported");
				}
			}
		} else if (etk::start_with(data, "--etk-log-lib=")) {
			std::string value(data.begin()+14, data.end());
			std::vector<std::string> list = etk::split(value, ':');
			if (list.size() != 2) {
				TK_ERROR("Can not set the --etk-log-lib= with value='" << value << "' not formated name:X");
				continue;
			}
			etk::log::setLevel(list[0], getLogLevel(list[1]));
		} else if (    data == "-h"
		            || data == "--help") {
			etk::log::setLevel(etk::log::logLevelInfo);
			TK_INFO("etk - help : ");
			TK_INFO("    " << _argv[0] << " [options]");
			TK_INFO("        -l/--etk-log-level=   Change the default log level (set all Log lovel):");
			TK_INFO("            0: debug None (default in release)");
			TK_INFO("            1: debug Critical");
			TK_INFO("            2: debug Error");
			TK_INFO("            3: debug Warning");
			TK_INFO("            4: debug Info (default in debug)");
			TK_INFO("            5: debug Debug");
			TK_INFO("            6: debug Verbose");
			TK_INFO("        --etk-log-lib=name:X  Set a library specific level:");
			TK_INFO("            name  Name of the library");
			TK_INFO("            X     Log level to set [0..6]");
			TK_INFO("        --etk-log-color       Enable color in log (default in Linux/debug)");
			TK_INFO("        --etk-log-no-color    Disable color in log (default in Linux/release and Other)");
			TK_INFO("        --etk-log-config=     Configure the Log interface");
			TK_INFO("            t: diplay time");
			TK_INFO("            T: diplay thread id");
			TK_INFO("            N: diplay thread name");
			TK_INFO("            L: diplay line number");
			TK_INFO("            l: diplay lib name");
			TK_INFO("            f: diplay fundtion name");
			TK_INFO("        -h/--help: this help");
			TK_INFO("    example:");
			TK_INFO("        " << _argv[0] << " --etk-log-color --etk-log-level=2 --etk-log-lib=etk:5 --etk-log-lib=appl:6 --etk-log-config=NLlf");
		} else if (etk::start_with(data, "--etk")) {
			TK_ERROR("Can not parse the argument : '" << data << "'");
		}
	}
	TK_INFO("E-TK system init (END)");
}