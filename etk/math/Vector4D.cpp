/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/math/Vector4D.hpp>
#include <etk/typeInfo.hpp>
#include <etk/String.hpp>

ETK_DECLARE_TYPE(etk::Vector4D<int32_t>);
ETK_DECLARE_TYPE(etk::Vector4D<float>);
ETK_DECLARE_TYPE(etk::Vector4D<uint32_t>);
ETK_DECLARE_TYPE(etk::Vector4D<bool>);

etk::Stream& etk::operator <<(etk::Stream &_os, const etk::Vector4D<int32_t>& _obj) {
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

etk::Stream& etk::operator <<(etk::Stream &_os, const etk::Vector4D<float>& _obj) {
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

etk::Stream& etk::operator <<(etk::Stream &_os, const etk::Vector4D<uint32_t>& _obj) {
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

etk::Stream& etk::operator <<(etk::Stream &_os, const etk::Vector4D<bool>& _obj) {
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

