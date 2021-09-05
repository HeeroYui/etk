/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#include <etk/Exception.hpp>
#include <etk/system.hpp>
#include <stdio.h>

etk::String etk::exec(const etk::String& _cmd) {
	FILE* pipe = popen(_cmd.c_str(), "r");
	if (!pipe) {
		ETK_THROW_EXCEPTION(etk::exception::RuntimeError("popen() failed!"));
		return "";
	}
	etk::String out;
	try {
		char buffer[128];
		while (fgets(buffer, 128, pipe) != NULL) {
			out += buffer;
		}
	} catch (...) {
		pclose(pipe);
		ETK_THROW_EXCEPTION(etk::exception::RuntimeError("Broken pipe"));
	}
	pclose(pipe);
	return out;
}


