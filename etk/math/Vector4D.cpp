/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/math/Vector4D.h>

etk::CCout& etk::operator <<(etk::CCout &os, const etk::Vector4D<int32_t> obj)
{
	os << "(";
	os << obj.x();
	os << ",";
	os << obj.y();
	os << ",";
	os << obj.z();
	os << ",";
	os << obj.w();
	os << ")";
	return os;
}

etk::CCout& etk::operator <<(etk::CCout &os, const etk::Vector4D<float> obj)
{
	os << "(";
	os << obj.x();
	os << ",";
	os << obj.y();
	os << ",";
	os << obj.z();
	os << ",";
	os << obj.w();
	os << ")";
	return os;
}

etk::CCout& etk::operator <<(etk::CCout &os, const etk::Vector4D<uint32_t> obj)
{
	os << "(";
	os << obj.x();
	os << ",";
	os << obj.y();
	os << ",";
	os << obj.z();
	os << ",";
	os << obj.w();
	os << ")";
	return os;
}

etk::CCout& etk::operator <<(etk::CCout &os, const etk::Vector4D<bool> obj)
{
	os << "(";
	os << obj.x();
	os << ",";
	os << obj.y();
	os << ",";
	os << obj.z();
	os << ",";
	os << obj.w();
	os << ")";
	return os;
}

