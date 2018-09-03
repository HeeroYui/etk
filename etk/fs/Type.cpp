/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#include <etk/types.hpp>
#include <etk/fs/Type.hpp>

etk::Stream& etk::operator <<(etk::Stream &_os, const enum etk::fs::Type &_obj) {
	switch (_obj) {
		case etk::fs::Type::Unknow:
			_os << "etk::fs::Type::Unknow";
			break;
		case etk::fs::Type::Direct:
			_os << "etk::fs::Type::Direct";
			break;
		case etk::fs::Type::Home:
			_os << "etk::fs::Type::Home";
			break;
		case etk::fs::Type::Data:
			_os << "etk::fs::Type::Data";
			break;
		case etk::fs::Type::UserData:
			_os << "etk::fs::Type::UserData";
			break;
		case etk::fs::Type::Cache:
			_os << "etk::fs::Type::Cache";
			break;
		case etk::fs::Type::Theme:
			_os << "etk::fs::Type::Theme";
			break;
		case etk::fs::Type::ThemeData:
			_os << "etk::fs::Type::Theme(DATA)";
			break;
		default:
			_os << "etk::fs::Type::????";
			break;
	}
	return _os;
}


