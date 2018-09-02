/**
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL-2 (see license file)
 */

#include <etk/io/SeekMode.hpp>

etk::Stream& etk::operator <<(etk::Stream &_os, const enum etk::io::SeekMode &_obj) {
	switch (_obj) {
		case etk::io::SeekMode::Start:
			_os << "etk::SeekMode::Start";
			break;
		case etk::io::SeekMode::End:
			_os << "etk::SeekMode::End";
			break;
		case etk::io::SeekMode::Current:
			_os << "etk::SeekMode::Current";
			break;
	}
	return _os;
}

