/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <etk/etk.h>
#include <elog/log.h>
#include <etk/types.h>
#include <etk/debug.h>
#include <etk/os/FSNode.h>

static elog::level getLogLevel(const std::string& _value) {
	if (_value == "0") {
		return elog::logLevelNone;
	} else if (_value == "1") {
		return elog::logLevelCritical;
	} else if (_value == "2") {
		return elog::logLevelError;
	} else if (_value == "3") {
		return elog::logLevelWarning;
	} else if (_value == "4") {
		return elog::logLevelInfo;
	} else if (_value == "5") {
		return elog::logLevelDebug;
	} else if (_value == "6") {
		return elog::logLevelVerbose;
	}
	TK_ERROR("Unknow log level : " << _value);
	return elog::logLevelVerbose;
}

void etk::init(int _argc, const char** _argv) {
	TK_INFO("E-TK system init (BEGIN)");
	etk::setArgZero(_argv[0]);
	for (int32_t iii=0; iii<_argc ; ++iii) {
		std::string data = _argv[iii];
		if (etk::start_with(data, "--etk-log-level=")) {
			elog::setLevel(getLogLevel(std::string(data.begin()+16, data.end())));
		} else if (etk::start_with(data, "-l=")) {
			elog::setLevel(getLogLevel(std::string(data.begin()+2, data.end())));
		} else if (etk::start_with(data, "--etk-log-color")) {
			elog::setColor(true);
		} else if (etk::start_with(data, "--etk-log-no-color")) {
			elog::setColor(false);
		} else if (etk::start_with(data, "--etk-log-config=")) {
			std::string value(data.begin()+17, data.end());
			elog::setTime(false);
			elog::setLine(false);
			elog::setFunction(false);
			elog::setLibName(false);
			elog::setThreadId(false);
			elog::setThreadNameEnable(false);
			for (size_t iii=0; iii<value.size(); ++iii) {
				if (value[iii] == 't') {
					elog::setTime(true);
				} else if (value[iii] == 'T') {
					elog::setThreadId(true);
				} else if (value[iii] == 'N') {
					elog::setThreadNameEnable(true);
				} else if (value[iii] == 'L') {
					elog::setLine(true);
				} else if (value[iii] == 'l') {
					elog::setLibName(true);
				} else if (value[iii] == 'f') {
					elog::setFunction(true);
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
			elog::setLevel(list[0], getLogLevel(list[1]));
		} else if (    data == "-h"
		            || data == "--help") {
			elog::setLevel(elog::logLevelInfo);
			TK_PRINT("etk - help : ");
			TK_PRINT("    " << _argv[0] << " [options]");
			TK_PRINT("        -l/--etk-log-level=   Change the default log level (set all Log lovel):");
			TK_PRINT("            0: debug None (default in release)");
			TK_PRINT("            1: debug Critical");
			TK_PRINT("            2: debug Error");
			TK_PRINT("            3: debug Warning");
			TK_PRINT("            4: debug Info (default in debug)");
			TK_PRINT("            5: debug Debug");
			TK_PRINT("            6: debug Verbose");
			TK_PRINT("        --etk-log-lib=name:X  Set a library specific level:");
			TK_PRINT("            name  Name of the library");
			TK_PRINT("            X     Log level to set [0..6]");
			TK_PRINT("        --etk-log-color       Enable color in log (default in Linux/debug)");
			TK_PRINT("        --etk-log-no-color    Disable color in log (default in Linux/release and Other)");
			TK_PRINT("        --etk-log-config=     Configure the Log interface");
			TK_PRINT("            t: diplay time");
			TK_PRINT("            T: diplay thread id");
			TK_PRINT("            N: diplay thread name");
			TK_PRINT("            L: diplay line number");
			TK_PRINT("            l: diplay lib name");
			TK_PRINT("            f: diplay fundtion name");
			TK_PRINT("        -h/--help: this help");
			TK_PRINT("    example:");
			TK_PRINT("        " << _argv[0] << " --etk-log-color --etk-log-level=2 --etk-log-lib=etk:5 --etk-log-lib=appl:6 --etk-log-config=NLlf");
		} else if (etk::start_with(data, "--etk")) {
			TK_ERROR("Can not parse the argument : '" << data << "'");
		}
	}
	TK_INFO("E-TK system init (END)");
}

std::string etk::getApplicationName() {
	return etk::FSNodeGetApplicationName();
}
