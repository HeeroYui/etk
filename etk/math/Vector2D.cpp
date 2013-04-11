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

namespace etk {

	template<> Vector2D<bool>::Vector2D(const etk::UString& str)
	{
		m_floats[0] = false;
		m_floats[1] = false;
		if (str.StartWith("(")) {
			if (str.StartWith("(t")) {
				if (str.CompareNoCase("(true,true)")) {
					m_floats[0] = true;
					m_floats[1] = true;
				} else if (str.CompareNoCase("(true,false)")) {
					m_floats[0] = true;
					m_floats[1] = false;
				} else if (str.CompareNoCase("(true)")) {
					m_floats[0] = true;
					m_floats[1] = true;
				}
			} else if (str.StartWith("(f")) {
				if (str.CompareNoCase("(false,true)")) {
					m_floats[0] = false;
					m_floats[1] = true;
				} else if (str.CompareNoCase("(false,false)")) {
					m_floats[0] = false;
					m_floats[1] = false;
				} else if (str.CompareNoCase("(false)")) {
					m_floats[0] = false;
					m_floats[1] = false;
				}
			} else {
				if (str.CompareNoCase("(1,1)")) {
					m_floats[0] = true;
					m_floats[1] = true;
				} else if (str.CompareNoCase("(1)")) {
					m_floats[0] = true;
					m_floats[1] = true;
				} else if (str.CompareNoCase("(1,0)")) {
					m_floats[0] = true;
					m_floats[1] = false;
				} else if (str.CompareNoCase("(0,1)")) {
					m_floats[0] = false;
					m_floats[1] = true;
				} else if (str.CompareNoCase("(0,0)")) {
					m_floats[0] = false;
					m_floats[1] = false;
				} else if (str.CompareNoCase("(0)")) {
					m_floats[0] = false;
					m_floats[1] = false;
				}
			}
		} else {
			if (str.StartWith("t")) {
				if (str.CompareNoCase("true,true")) {
					m_floats[0] = true;
					m_floats[1] = true;
				} else if (str.CompareNoCase("true,false")) {
					m_floats[0] = true;
					m_floats[1] = false;
				} else if (str.CompareNoCase("true")) {
					m_floats[0] = true;
					m_floats[1] = true;
				}
			} else if (str.StartWith("f")) {
				if (str.CompareNoCase("false,true")) {
					m_floats[0] = false;
					m_floats[1] = true;
				} else if (str.CompareNoCase("false,false")) {
					m_floats[0] = false;
					m_floats[1] = false;
				} else if (str.CompareNoCase("false")) {
					m_floats[0] = false;
					m_floats[1] = false;
				}
			} else {
				if (str.CompareNoCase("1,1")) {
					m_floats[0] = true;
					m_floats[1] = true;
				} else if (str.CompareNoCase("1")) {
					m_floats[0] = true;
					m_floats[1] = true;
				} else if (str.CompareNoCase("1,0")) {
					m_floats[0] = true;
					m_floats[1] = false;
				} else if (str.CompareNoCase("0,1")) {
					m_floats[0] = false;
					m_floats[1] = true;
				} else if (str.CompareNoCase("0,0")) {
					m_floats[0] = false;
					m_floats[1] = false;
				} else if (str.CompareNoCase("0")) {
					m_floats[0] = false;
					m_floats[1] = false;
				}
			}
		}
	}
	
	template<> Vector2D<int32_t>::Vector2D(const etk::UString& str)
	{
		m_floats[0] = 0;
		m_floats[1] = 0;
		if (str.StartWith("(")) {
			int32_t val1=0;
			int32_t val2=0;
			sscanf(str.c_str(), "(%d,%d)", &val1, &val2);
			m_floats[0] = val1;
			m_floats[1] = val2;
		} else {
			int32_t val1=0;
			int32_t val2=0;
			sscanf(str.c_str(), "%d,%d", &val1, &val2);
			m_floats[0] = val1;
			m_floats[1] = val2;
		}
	}
	
	template<> Vector2D<uint32_t>::Vector2D(const etk::UString& str)
	{
		m_floats[0] = 0;
		m_floats[1] = 0;
		if (str.StartWith("(")) {
			int32_t val1=0;
			int32_t val2=0;
			sscanf(str.c_str(), "(%d,%d)", &val1, &val2);
			m_floats[0] = etk_max(0,val1);
			m_floats[1] = etk_max(0,val2);
		} else {
			int32_t val1=0;
			int32_t val2=0;
			sscanf(str.c_str(), "%d,%d", &val1, &val2);
			m_floats[0] = etk_max(0,val1);
			m_floats[1] = etk_max(0,val2);
		}
	}
	
	template<> Vector2D<float>::Vector2D(const etk::UString& str)
	{
		m_floats[0] = 0;
		m_floats[1] = 0;
		if (str.StartWith("(")) {
			sscanf(str.c_str(), "(%f,%f)", &m_floats[0], &m_floats[1]);
		} else {
			sscanf(str.c_str(), "(%f,%f)", &m_floats[0], &m_floats[1]);
		}
	}

};


