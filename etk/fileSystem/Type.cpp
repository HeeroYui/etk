/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#include <etk/types.hpp>
#include <etk/fileSystem/Type.hpp>

etk::Stream& etk::operator <<(etk::Stream &_os, const enum etk::fileSystem::Type &_obj) {
	switch (_obj) {
		case etk::fileSystem::Type::Unknow:
			_os << "etk::fileSystem::Type::Unknow";
			break;
		case etk::fileSystem::Type::Direct:
			_os << "etk::fileSystem::Type::Direct";
			break;
		case etk::fileSystem::Type::Home:
			_os << "etk::fileSystem::Type::Home";
			break;
		case etk::fileSystem::Type::Data:
			_os << "etk::fileSystem::Type::Data";
			break;
		case etk::fileSystem::Type::UserData:
			_os << "etk::fileSystem::Type::UserData";
			break;
		case etk::fileSystem::Type::Cache:
			_os << "etk::fileSystem::Type::Cache";
			break;
		case etk::fileSystem::Type::Theme:
			_os << "etk::fileSystem::Type::Theme";
			break;
		case etk::fileSystem::Type::ThemeData:
			_os << "etk::fileSystem::Type::Theme(DATA)";
			break;
		default:
			_os << "etk::fileSystem::Type::????";
			break;
	}
	return _os;
}


