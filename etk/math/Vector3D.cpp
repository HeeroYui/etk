/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/math/Vector3D.h>

etk::CCout& etk::operator <<(etk::CCout &os, const etk::Vector3D<int32_t> obj)
{
	os << "(";
	os << obj.x();
	os << ",";
	os << obj.y();
	os << ",";
	os << obj.z();
	os << ")";
	return os;
}

etk::CCout& etk::operator <<(etk::CCout &os, const btVector3 obj)
{
	os << "(";
	os << obj.x();
	os << ",";
	os << obj.y();
	os << ",";
	os << obj.z();
	os << ")";
	return os;
}

etk::CCout& etk::operator <<(etk::CCout &os, const etk::Vector3D<uint32_t> obj)
{
	os << "(";
	os << obj.x();
	os << ",";
	os << obj.y();
	os << ",";
	os << obj.z();
	os << ")";
	return os;
}

etk::CCout& etk::operator <<(etk::CCout &os, const etk::Vector3D<bool> obj)
{
	os << "(";
	os << obj.x();
	os << ",";
	os << obj.y();
	os << ",";
	os << obj.z();
	os << ")";
	return os;
}

