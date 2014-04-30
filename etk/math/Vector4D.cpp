/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/math/Vector4D.h>

std::ostream& etk::operator <<(std::ostream &_os, const etk::Vector4D<int32_t>& _obj) {
	_os << "(";
	_os << _obj.x();
	_os << ",";
	_os << _obj.y();
	_os << ",";
	_os << _obj.z();
	_os << ",";
	_os << _obj.w();
	_os << ")";
	return _os;
}

std::ostream& etk::operator <<(std::ostream &_os, const etk::Vector4D<float>& _obj) {
	_os << "(";
	_os << _obj.x();
	_os << ",";
	_os << _obj.y();
	_os << ",";
	_os << _obj.z();
	_os << ",";
	_os << _obj.w();
	_os << ")";
	return _os;
}

std::ostream& etk::operator <<(std::ostream &_os, const etk::Vector4D<uint32_t>& _obj) {
	_os << "(";
	_os << _obj.x();
	_os << ",";
	_os << _obj.y();
	_os << ",";
	_os << _obj.z();
	_os << ",";
	_os << _obj.w();
	_os << ")";
	return _os;
}

std::ostream& etk::operator <<(std::ostream &_os, const etk::Vector4D<bool>& _obj) {
	_os << "(";
	_os << _obj.x();
	_os << ",";
	_os << _obj.y();
	_os << ",";
	_os << _obj.z();
	_os << ",";
	_os << _obj.w();
	_os << ")";
	return _os;
}

