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


namespace etk {
	template<> Vector2D<bool>::operator std::string(void) const {
		std::string str;
		str = "(";
		str += std::to_string(x());
		str += ",";
		str += std::to_string(y());
		str += ")";
		return str;
	}
	template<> Vector2D<bool>::operator std::u32string(void) const {
		std::u32string str;
		str = U"(";
		str += to_u32string(x());
		str += U",";
		str += to_u32string(y());
		str += U")";
		return str;
	}
	
	template<> Vector2D<bool>::Vector2D(const std::string& _str) {
		m_floats[0] = false;
		m_floats[1] = false;
		// copy to permit to modify it :
		std::string tmpStr = _str;
		if (tmpStr[0] == '(') {
			tmpStr.erase(tmpStr.begin());
		}
		if (tmpStr[tmpStr.size()-1] == ')') {
			tmpStr.erase(tmpStr.end()-1);
		}
		size_t posComa = tmpStr.find(',');
		if (posComa == std::string::npos) {
			// no coma ...
			// in every case, we parse the first element :
			m_floats[0] = stobool(tmpStr);
			m_floats[1] = m_floats[0];
		} else {
			m_floats[0] = stobool(std::string(tmpStr, 0, posComa));
			tmpStr.erase(0, posComa+1);
			m_floats[1] = stobool(tmpStr);
		}
		TK_VERBOSE("Parse : \"" << _str << "\" ==> " << *this);
	}
	template<> Vector2D<bool>::Vector2D(const std::u32string& _str) {
		m_floats[0] = false;
		m_floats[1] = false;
		// copy to permit to modify it :
		std::u32string tmpStr = _str;
		if (tmpStr[0] == '(') {
			tmpStr.erase(tmpStr.begin());
		}
		if (tmpStr[tmpStr.size()-1] == ')') {
			tmpStr.erase(tmpStr.end()-1);
		}
		size_t posComa = tmpStr.find(',');
		if (posComa == std::string::npos) {
			// no coma ...
			// in every case, we parse the first element :
			m_floats[0] = stobool(tmpStr);
			m_floats[1] = m_floats[0];
		} else {
			m_floats[0] = stobool(std::u32string(tmpStr, 0, posComa));
			tmpStr.erase(0, posComa+1);
			m_floats[1] = stobool(tmpStr);
		}
		TK_VERBOSE("Parse : \"" << _str << "\" ==> " << *this);
	}
	
	template<> Vector2D<int32_t>::operator std::string(void) const {
		std::string str;
		str = "(";
		str += std::to_string(x());
		str += ",";
		str += std::to_string(y());
		str += ")";
		return str;
	}
	template<> Vector2D<int32_t>::operator std::u32string(void) const {
		std::u32string str;
		str = U"(";
		str += to_u32string(x());
		str += U",";
		str += to_u32string(y());
		str += U")";
		return str;
	}
	
	template<> Vector2D<int32_t>::Vector2D(const std::string& _str) {
		m_floats[0] = 0;
		m_floats[1] = 0;
		// copy to permit to modify it :
		std::string tmpStr = _str;
		if (tmpStr[0] == '(') {
			tmpStr.erase(tmpStr.begin());
		}
		if (tmpStr[tmpStr.size()-1] == ')') {
			tmpStr.erase(tmpStr.end()-1);
		}
		
		size_t posComa = tmpStr.find(',');
		if (posComa == std::string::npos) {
			// no coma ...
			// in every case, we parse the first element :
			m_floats[0] = stoi(tmpStr);
			m_floats[1] = m_floats[0];
		} else {
			m_floats[0] = stoi(std::string(tmpStr, 0, posComa));
			tmpStr.erase(0,posComa+1);
			m_floats[1] = stoi(tmpStr);
		}
		TK_VERBOSE("Parse : \"" << _str << "\" ==> " << *this);
	}
	template<> Vector2D<int32_t>::Vector2D(const std::u32string& _str) {
		m_floats[0] = 0;
		m_floats[1] = 0;
		// copy to permit to modify it :
		std::u32string tmpStr = _str;
		if (tmpStr[0] == '(') {
			tmpStr.erase(tmpStr.begin());
		}
		if (tmpStr[tmpStr.size()-1] == ')') {
			tmpStr.erase(tmpStr.end()-1);
		}
		
		size_t posComa = tmpStr.find(',');
		if (posComa == 0) {
			// no coma ...
			// in every case, we parse the first element :
			m_floats[0] = stoi(tmpStr);
			m_floats[1] = m_floats[0];
		} else {
			m_floats[0] = stoi(std::u32string(tmpStr, 0, posComa));
			tmpStr.erase(0,posComa+1);
			m_floats[1] = stoi(tmpStr);
		}
		TK_VERBOSE("Parse : \"" << _str << "\" ==> " << *this);
	}
	
	template<> Vector2D<uint32_t>::operator std::string(void) const {
		std::string str;
		str = "(";
		str += std::to_string(x());
		str += ",";
		str += std::to_string(y());
		str += ")";
		return str;
	}
	
	template<> Vector2D<uint32_t>::operator std::u32string(void) const {
		std::u32string str;
		str = U"(";
		str += to_u32string(x());
		str += U",";
		str += to_u32string(y());
		str += U")";
		return str;
	}
	
	template<> Vector2D<uint32_t>::Vector2D(const std::string& _str)
	{
		m_floats[0] = 0;
		m_floats[1] = 0;
		// copy to permit to modify it :
		std::string tmpStr = _str;
		if (tmpStr[0] == '(') {
			tmpStr.erase(tmpStr.begin());
		}
		if (tmpStr[tmpStr.size()-1] == ')') {
			tmpStr.erase(tmpStr.end()-1);
		}
		size_t posComa = tmpStr.find(',');
		if (posComa == std::string::npos) {
			// no coma ...
			// in every case, we parse the first element :
			m_floats[0] = stoi(tmpStr);
			m_floats[1] = m_floats[0];
		} else {
			m_floats[0] = stoi(std::string(tmpStr, 0, posComa));
			tmpStr.erase(0,posComa+1);
			m_floats[1] = stoi(tmpStr);
		}
		TK_VERBOSE("Parse : \"" << _str << "\" ==> " << *this);
	}
	template<> Vector2D<uint32_t>::Vector2D(const std::u32string& _str)
	{
		m_floats[0] = 0;
		m_floats[1] = 0;
		// copy to permit to modify it :
		std::u32string tmpStr = _str;
		if (tmpStr[0] == '(') {
			tmpStr.erase(tmpStr.begin());
		}
		if (tmpStr[tmpStr.size()-1] == ')') {
			tmpStr.erase(tmpStr.end()-1);
		}
		size_t posComa = tmpStr.find(',');
		if (posComa == std::string::npos) {
			// no coma ...
			// in every case, we parse the first element :
			m_floats[0] = stoi(tmpStr);
			m_floats[1] = m_floats[0];
		} else {
			m_floats[0] = stoi(std::u32string(tmpStr, 0, posComa));
			tmpStr.erase(0,posComa+1);
			m_floats[1] = stoi(tmpStr);
		}
		TK_VERBOSE("Parse : \"" << _str << "\" ==> " << *this);
	}
	
	template<> Vector2D<float>::operator std::string(void) const {
		std::string str;
		str = "(";
		str += std::to_string(x());
		str += ",";
		str += std::to_string(y());
		str += ")";
		return str;
	}
	template<> Vector2D<float>::operator std::u32string(void) const {
		std::u32string str;
		str = U"(";
		str += to_u32string(x());
		str += U",";
		str += to_u32string(y());
		str += U")";
		return str;
	}
	
	template<> Vector2D<float>::Vector2D(const std::string& _str) {
		m_floats[0] = 0;
		m_floats[1] = 0;
		// copy to permit to modify it :
		std::string tmpStr = _str;
		if (tmpStr[0] == '(') {
			tmpStr.erase(tmpStr.begin());
		}
		if (tmpStr[tmpStr.size()-1] == ')') {
			tmpStr.erase(tmpStr.end()-1);
		}
		size_t posComa = tmpStr.find(',');
		if (posComa == std::string::npos) {
			// no coma ...
			// in every case, we parse the first element :
			m_floats[0] = stof(tmpStr);
			m_floats[1] = m_floats[0];
		} else {
			m_floats[0] = stof(std::string(tmpStr, 0, posComa));
			tmpStr.erase(0,posComa+1);
			m_floats[1] = stof(tmpStr);
		}
		TK_VERBOSE("Parse : \"" << _str << "\" ==> " << *this);
	}
	template<> Vector2D<float>::Vector2D(const std::u32string& _str) {
		m_floats[0] = 0;
		m_floats[1] = 0;
		// copy to permit to modify it :
		std::u32string tmpStr = _str;
		if (tmpStr[0] == '(') {
			tmpStr.erase(tmpStr.begin());
		}
		if (tmpStr[tmpStr.size()-1] == ')') {
			tmpStr.erase(tmpStr.end()-1);
		}
		size_t posComa = tmpStr.find(',');
		if (posComa == std::string::npos) {
			// no coma ...
			// in every case, we parse the first element :
			m_floats[0] = stof(tmpStr);
			m_floats[1] = m_floats[0];
		} else {
			m_floats[0] = stof(std::u32string(tmpStr, 0, posComa));
			tmpStr.erase(0,posComa+1);
			m_floats[1] = stof(tmpStr);
		}
		TK_VERBOSE("Parse : \"" << _str << "\" ==> " << *this);
	}

};


