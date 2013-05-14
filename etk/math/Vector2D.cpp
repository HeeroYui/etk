/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/math/Vector2D.h>

etk::CCout& etk::operator <<(etk::CCout& _os, const etk::Vector2D<int32_t>& _obj)
{
	_os << "(";
	_os << _obj.x();
	_os << ",";
	_os << _obj.y();
	_os << ")";
	return _os;
}

etk::CCout& etk::operator <<(etk::CCout& _os, const etk::Vector2D<float>& _obj)
{
	_os << "(";
	_os << _obj.x();
	_os << ",";
	_os << _obj.y();
	_os << ")";
	return _os;
}

etk::CCout& etk::operator <<(etk::CCout& _os, const etk::Vector2D<uint32_t>& _obj)
{
	_os << "(";
	_os << _obj.x();
	_os << ",";
	_os << _obj.y();
	_os << ")";
	return _os;
}

etk::CCout& etk::operator <<(etk::CCout& _os, const etk::Vector2D<bool>& _obj)
{
	_os << "(";
	_os << _obj.x();
	_os << ",";
	_os << _obj.y();
	_os << ")";
	return _os;
}


namespace etk
{
	template<> Vector2D<bool>::operator etk::UString(void) const
	{
		etk::UString str;
		str = "(";
		str += x();
		str += ",";
		str += y();
		str += ")";
		return str;
	}
	
	template<> Vector2D<bool>::Vector2D(const etk::UString& _str)
	{
		m_floats[0] = false;
		m_floats[1] = false;
		if (_str.StartWith("(")) {
			if (_str.StartWith("(t")) {
				if (_str.CompareNoCase("(true,true)")) {
					m_floats[0] = true;
					m_floats[1] = true;
				} else if (_str.CompareNoCase("(true,false)")) {
					m_floats[0] = true;
					m_floats[1] = false;
				} else if (_str.CompareNoCase("(true)")) {
					m_floats[0] = true;
					m_floats[1] = true;
				}
			} else if (_str.StartWith("(f")) {
				if (_str.CompareNoCase("(false,true)")) {
					m_floats[0] = false;
					m_floats[1] = true;
				} else if (_str.CompareNoCase("(false,false)")) {
					m_floats[0] = false;
					m_floats[1] = false;
				} else if (_str.CompareNoCase("(false)")) {
					m_floats[0] = false;
					m_floats[1] = false;
				}
			} else {
				if (_str.CompareNoCase("(1,1)")) {
					m_floats[0] = true;
					m_floats[1] = true;
				} else if (_str.CompareNoCase("(1)")) {
					m_floats[0] = true;
					m_floats[1] = true;
				} else if (_str.CompareNoCase("(1,0)")) {
					m_floats[0] = true;
					m_floats[1] = false;
				} else if (_str.CompareNoCase("(0,1)")) {
					m_floats[0] = false;
					m_floats[1] = true;
				} else if (_str.CompareNoCase("(0,0)")) {
					m_floats[0] = false;
					m_floats[1] = false;
				} else if (_str.CompareNoCase("(0)")) {
					m_floats[0] = false;
					m_floats[1] = false;
				}
			}
		} else {
			if (_str.StartWith("t")) {
				if (_str.CompareNoCase("true,true")) {
					m_floats[0] = true;
					m_floats[1] = true;
				} else if (_str.CompareNoCase("true,false")) {
					m_floats[0] = true;
					m_floats[1] = false;
				} else if (_str.CompareNoCase("true")) {
					m_floats[0] = true;
					m_floats[1] = true;
				}
			} else if (_str.StartWith("f")) {
				if (_str.CompareNoCase("false,true")) {
					m_floats[0] = false;
					m_floats[1] = true;
				} else if (_str.CompareNoCase("false,false")) {
					m_floats[0] = false;
					m_floats[1] = false;
				} else if (_str.CompareNoCase("false")) {
					m_floats[0] = false;
					m_floats[1] = false;
				}
			} else {
				if (_str.CompareNoCase("1,1")) {
					m_floats[0] = true;
					m_floats[1] = true;
				} else if (_str.CompareNoCase("1")) {
					m_floats[0] = true;
					m_floats[1] = true;
				} else if (_str.CompareNoCase("1,0")) {
					m_floats[0] = true;
					m_floats[1] = false;
				} else if (_str.CompareNoCase("0,1")) {
					m_floats[0] = false;
					m_floats[1] = true;
				} else if (_str.CompareNoCase("0,0")) {
					m_floats[0] = false;
					m_floats[1] = false;
				} else if (_str.CompareNoCase("0")) {
					m_floats[0] = false;
					m_floats[1] = false;
				}
			}
		}
	}
	
	template<> Vector2D<int32_t>::operator etk::UString(void) const
	{
		etk::UString str;
		str = "(";
		str += x();
		str += ",";
		str += y();
		str += ")";
		return str;
	}
	
	template<> Vector2D<int32_t>::Vector2D(const etk::UString& _str)
	{
		m_floats[0] = 0;
		m_floats[1] = 0;
		if (_str.StartWith("(")) {
			int32_t val1=0;
			int32_t val2=0;
			sscanf(_str.c_str(), "(%d,%d)", &val1, &val2);
			m_floats[0] = val1;
			m_floats[1] = val2;
		} else {
			int32_t val1=0;
			int32_t val2=0;
			sscanf(_str.c_str(), "%d,%d", &val1, &val2);
			m_floats[0] = val1;
			m_floats[1] = val2;
		}
	}
	
	template<> Vector2D<uint32_t>::operator etk::UString(void) const
	{
		etk::UString str;
		str = "(";
		str += x();
		str += ",";
		str += y();
		str += ")";
		return str;
	}
	
	template<> Vector2D<uint32_t>::Vector2D(const etk::UString& _str)
	{
		m_floats[0] = 0;
		m_floats[1] = 0;
		if (_str.StartWith("(")) {
			int32_t val1=0;
			int32_t val2=0;
			sscanf(_str.c_str(), "(%d,%d)", &val1, &val2);
			m_floats[0] = etk_max(0,val1);
			m_floats[1] = etk_max(0,val2);
		} else {
			int32_t val1=0;
			int32_t val2=0;
			sscanf(_str.c_str(), "%d,%d", &val1, &val2);
			m_floats[0] = etk_max(0,val1);
			m_floats[1] = etk_max(0,val2);
		}
	}
	
	template<> Vector2D<float>::operator etk::UString(void) const
	{
		etk::UString str;
		str = "(";
		str += x();
		str += ",";
		str += y();
		str += ")";
		return str;
	}
	
	template<> Vector2D<float>::Vector2D(const etk::UString& _str)
	{
		m_floats[0] = 0;
		m_floats[1] = 0;
		//TK_DEBUG("start parsing od vec2 with \"" << str << "\"");
		if (_str.StartWith("(")) {
			//TK_DEBUG("    start with (");
			sscanf(_str.c_str(), "(%f,%f)", &m_floats[0], &m_floats[1]);
		} else {
			sscanf(_str.c_str(), "%f,%f", &m_floats[0], &m_floats[1]);
		}
		//TK_DEBUG("    result " << *this);
	}

};


