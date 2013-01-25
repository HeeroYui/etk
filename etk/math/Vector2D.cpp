/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/math/Vector2D.h>

etk::CCout& etk::operator <<(etk::CCout &os, const etk::Vector2D<int32_t> obj)
{
	os << "(";
	os << obj.x();
	os << ",";
	os << obj.y();
	os << ")";
	return os;
}

etk::CCout& etk::operator <<(etk::CCout &os, const etk::Vector2D<float> obj)
{
	os << "(";
	os << obj.x();
	os << ",";
	os << obj.y();
	os << ")";
	return os;
}

etk::CCout& etk::operator <<(etk::CCout &os, const etk::Vector2D<uint32_t> obj)
{
	os << "(";
	os << obj.x();
	os << ",";
	os << obj.y();
	os << ")";
	return os;
}

etk::CCout& etk::operator <<(etk::CCout &os, const etk::Vector2D<bool> obj)
{
	os << "(";
	os << obj.x();
	os << ",";
	os << obj.y();
	os << ")";
	return os;
}

