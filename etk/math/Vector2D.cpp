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
		// copy to permit to modify it :
		etk::UString tmpStr = _str;
		if (_str.startWith("(")) {
			tmpStr.remove(0,1);
		}
		if (tmpStr.endWith(")")) {
			tmpStr.remove(tmpStr.size()-1,1);
		}
		int32_t posComa = tmpStr.findForward(',');
		if (posComa <= 0) {
			// no coma ...
			// in every case, we parse the first element :
			m_floats[0] = tmpStr.toBool();
			m_floats[1] = m_floats[0];
		} else {
			m_floats[0] = tmpStr.extract(0,posComa).toBool();
			tmpStr.remove(0,posComa+1);
			m_floats[1] = tmpStr.toBool();
		}
		TK_VERBOSE("Parse : \"" << _str << "\" ==> " << *this);
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
		// copy to permit to modify it :
		etk::UString tmpStr = _str;
		if (_str.startWith("(")) {
			tmpStr.remove(0,1);
		}
		if (tmpStr.endWith(")")) {
			tmpStr.remove(tmpStr.size()-1,1);
		}
		
		int32_t posComa = tmpStr.findForward(',');
		if (posComa <= 0) {
			// no coma ...
			// in every case, we parse the first element :
			m_floats[0] = tmpStr.toInt32();
			m_floats[1] = m_floats[0];
		} else {
			m_floats[0] = tmpStr.extract(0,posComa).toInt32();
			tmpStr.remove(0,posComa+1);
			m_floats[1] = tmpStr.toInt32();
		}
		TK_VERBOSE("Parse : \"" << _str << "\" ==> " << *this);
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
		// copy to permit to modify it :
		etk::UString tmpStr = _str;
		if (_str.startWith("(")) {
			tmpStr.remove(0,1);
		}
		if (tmpStr.endWith(")")) {
			tmpStr.remove(tmpStr.size()-1,1);
		}
		int32_t posComa = tmpStr.findForward(',');
		if (posComa <= 0) {
			// no coma ...
			// in every case, we parse the first element :
			m_floats[0] = tmpStr.toUInt32();
			m_floats[1] = m_floats[0];
		} else {
			m_floats[0] = tmpStr.extract(0,posComa).toUInt32();
			tmpStr.remove(0,posComa+1);
			m_floats[1] = tmpStr.toUInt32();
		}
		TK_VERBOSE("Parse : \"" << _str << "\" ==> " << *this);
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
		// copy to permit to modify it :
		etk::UString tmpStr = _str;
		if (_str.startWith("(")) {
			tmpStr.remove(0,1);
		}
		if (tmpStr.endWith(")")) {
			tmpStr.remove(tmpStr.size()-1,1);
		}
		int32_t posComa = tmpStr.findForward(',');
		if (posComa <= 0) {
			// no coma ...
			// in every case, we parse the first element :
			m_floats[0] = tmpStr.toFloat();
			m_floats[1] = m_floats[0];
		} else {
			m_floats[0] = tmpStr.extract(0,posComa).toFloat();
			tmpStr.remove(0,posComa+1);
			m_floats[1] = tmpStr.toFloat();
		}
		TK_VERBOSE("Parse : \"" << _str << "\" ==> " << *this);
	}

};


