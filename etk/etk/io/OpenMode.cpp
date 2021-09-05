/**
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL-2 (see license file)
 */

#include <etk/io/OpenMode.hpp>

etk::Stream& etk::operator <<(etk::Stream &_os, const enum etk::io::OpenMode &_obj) {
	switch (_obj) {
		case etk::io::OpenMode::Read:
			_os << "etk::OpenMode::Read";
			break;
		case etk::io::OpenMode::Write:
			_os << "etk::OpenMode::Write";
			break;
		case etk::io::OpenMode::Append:
			_os << "etk::OpenMode::Append";
			break;
	}
	return _os;
}

