/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/math/Vector2D.hpp>
#include <etk/stdTools.hpp>
#include <etk/debug.hpp>

std::ostream& etk::operator <<(std::ostream& _os, const etk::Vector2D<int32_t>& _obj) {
	_os << "(";
	_os << _obj.x();
	_os << ",";
	_os << _obj.y();
	_os << ")";
	return _os;
}

std::ostream& etk::operator <<(std::ostream& _os, const etk::Vector2D<float>& _obj) {
	_os << "(";
	_os << _obj.x();
	_os << ",";
	_os << _obj.y();
	_os << ")";
	return _os;
}

std::ostream& etk::operator <<(std::ostream& _os, const etk::Vector2D<uint32_t>& _obj) {
	_os << "(";
	_os << _obj.x();
	_os << ",";
	_os << _obj.y();
	_os << ")";
	return _os;
}

std::ostream& etk::operator <<(std::ostream& _os, const etk::Vector2D<bool>& _obj) {
	_os << "(";
	_os << _obj.x();
	_os << ",";
	_os << _obj.y();
	_os << ")";
	return _os;
}

std::ostream& etk::operator <<(std::ostream& _os, const std::vector<vec2 >& _obj) {
	for (size_t iii = 0; iii < _obj.size(); ++iii) {
		if (iii != 0) {
			_os << " ";
		}
		_os << _obj[iii];
	}
	return _os;
}

std::ostream& etk::operator <<(std::ostream& _os, const std::vector<ivec2 >& _obj) {
	for (size_t iii = 0; iii < _obj.size(); ++iii) {
		if (iii != 0) {
			_os << " ";
		}
		_os << _obj[iii];
	}
	return _os;
}

std::ostream& etk::operator <<(std::ostream& _os, const std::vector<uivec2 >& _obj) {
	for (size_t iii = 0; iii < _obj.size(); ++iii) {
		if (iii != 0) {
			_os << " ";
		}
		_os << _obj[iii];
	}
	return _os;
}

std::ostream& etk::operator <<(std::ostream& _os, const std::vector<bvec2 >& _obj) {
	for (size_t iii = 0; iii < _obj.size(); ++iii) {
		if (iii != 0) {
			_os << " ";
		}
		_os << _obj[iii];
	}
	return _os;
}

vec2 vec2rotate(const vec2& _val, const vec2& _point, float _angle) {
	vec2 out = _val;
	#if __CPP_VERSION__ >= 2011 && !defined(__STDCPP_LLVM__)
		float sinAngle = std::sin(_angle);
		float cosAngle = std::cos(_angle);
	#else
		float sinAngle = sin(_angle);
		float cosAngle = cos(_angle);
	#endif
	if (_point == vec2(0,0)) {
		float tempX = out.x() * cosAngle - out.y() * sinAngle;
		float xVal = out.x();
		out.setValue(tempX,
		             out.y() * cosAngle + xVal * sinAngle);
	} else {
		float tempX = out.x() - _point.x();
		float tempY = out.y() - _point.y();
		out.setValue(tempX * cosAngle - tempY * sinAngle + _point.x(),
		             tempY * cosAngle + tempX * sinAngle + _point.y());
	}
	return out;
}

namespace etk {
	template<> Vector2D<bool>::operator std::string() const {
		std::string str;
		str = "(";
		str += etk::to_string(x());
		str += ",";
		str += etk::to_string(y());
		str += ")";
		return str;
	}
	#if __CPP_VERSION__ >= 2011
		template<> Vector2D<bool>::operator std::u32string() const {
			std::u32string str;
			str = U"(";
			str += etk::to_u32string(x());
			str += U",";
			str += etk::to_u32string(y());
			str += U")";
			return str;
		}
	#endif
	
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
			m_floats[0] = etk::string_to_bool(tmpStr);
			m_floats[1] = m_floats[0];
		} else {
			m_floats[0] = etk::string_to_bool(std::string(tmpStr, 0, posComa));
			tmpStr.erase(0, posComa+1);
			m_floats[1] = etk::string_to_bool(tmpStr);
		}
		TK_VERBOSE("Parse : '" << _str << "' ==> " << *this);
	}
	#if __CPP_VERSION__ >= 2011
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
				m_floats[0] = etk::string_to_bool(tmpStr);
				m_floats[1] = m_floats[0];
			} else {
				m_floats[0] = etk::string_to_bool(std::u32string(tmpStr, 0, posComa));
				tmpStr.erase(0, posComa+1);
				m_floats[1] = etk::string_to_bool(tmpStr);
			}
			TK_VERBOSE("Parse : '" << _str << "' ==> " << *this);
		}
	#endif
	
	template<> Vector2D<int32_t>::operator std::string() const {
		std::string str;
		str = "(";
		str += etk::to_string(x());
		str += ",";
		str += etk::to_string(y());
		str += ")";
		return str;
	}
	#if __CPP_VERSION__ >= 2011
		template<> Vector2D<int32_t>::operator std::u32string() const {
			std::u32string str;
			str = U"(";
			str += etk::to_u32string(x());
			str += U",";
			str += etk::to_u32string(y());
			str += U")";
			return str;
		}
	#endif
	
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
			m_floats[0] = etk::string_to_int32_t(tmpStr);
			m_floats[1] = m_floats[0];
		} else {
			m_floats[0] = etk::string_to_int32_t(std::string(tmpStr, 0, posComa));
			tmpStr.erase(0,posComa+1);
			m_floats[1] = etk::string_to_int32_t(tmpStr);
		}
		TK_VERBOSE("Parse : \"" << _str << "\" ==> " << *this);
	}
	#if __CPP_VERSION__ >= 2011
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
				m_floats[0] = etk::string_to_int32_t(tmpStr);
				m_floats[1] = m_floats[0];
			} else {
				m_floats[0] = etk::string_to_int32_t(std::u32string(tmpStr, 0, posComa));
				tmpStr.erase(0,posComa+1);
				m_floats[1] = etk::string_to_int32_t(tmpStr);
			}
			TK_VERBOSE("Parse : \"" << _str << "\" ==> " << *this);
		}
	#endif
	
	template<> Vector2D<uint32_t>::operator std::string() const {
		std::string str;
		str = "(";
		str += etk::to_string(x());
		str += ",";
		str += etk::to_string(y());
		str += ")";
		return str;
	}
	#if __CPP_VERSION__ >= 2011
		template<> Vector2D<uint32_t>::operator std::u32string() const {
			std::u32string str;
			str = U"(";
			str += etk::to_u32string(x());
			str += U",";
			str += etk::to_u32string(y());
			str += U")";
			return str;
		}
	#endif
	
	template<> Vector2D<uint32_t>::Vector2D(const std::string& _str) {
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
			m_floats[0] = etk::string_to_int32_t(tmpStr);
			m_floats[1] = m_floats[0];
		} else {
			m_floats[0] = etk::string_to_int32_t(std::string(tmpStr, 0, posComa));
			tmpStr.erase(0,posComa+1);
			m_floats[1] = etk::string_to_int32_t(tmpStr);
		}
		TK_VERBOSE("Parse : \"" << _str << "\" ==> " << *this);
	}
	#if __CPP_VERSION__ >= 2011
		template<> Vector2D<uint32_t>::Vector2D(const std::u32string& _str) {
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
				m_floats[0] = etk::string_to_int32_t(tmpStr);
				m_floats[1] = m_floats[0];
			} else {
				m_floats[0] = etk::string_to_int32_t(std::u32string(tmpStr, 0, posComa));
				tmpStr.erase(0,posComa+1);
				m_floats[1] = etk::string_to_int32_t(tmpStr);
			}
			TK_VERBOSE("Parse : \"" << _str << "\" ==> " << *this);
		}
	#endif
	
	template<> Vector2D<float>::operator std::string() const {
		std::string str;
		str = "(";
		str += etk::to_string(x());
		str += ",";
		str += etk::to_string(y());
		str += ")";
		return str;
	}
	#if __CPP_VERSION__ >= 2011
		template<> Vector2D<float>::operator std::u32string() const {
			std::u32string str;
			str = U"(";
			str += etk::to_u32string(x());
			str += U",";
			str += etk::to_u32string(y());
			str += U")";
			return str;
		}
	#endif
	
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
			m_floats[0] = etk::string_to_float(tmpStr);
			m_floats[1] = m_floats[0];
		} else {
			m_floats[0] = etk::string_to_float(std::string(tmpStr, 0, posComa));
			tmpStr.erase(0,posComa+1);
			m_floats[1] = etk::string_to_float(tmpStr);
		}
		TK_VERBOSE("Parse : \"" << _str << "\" ==> " << *this);
	}
	#if __CPP_VERSION__ >= 2011
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
				m_floats[0] = etk::string_to_float(tmpStr);
				m_floats[1] = m_floats[0];
			} else {
				m_floats[0] = etk::string_to_float(std::u32string(tmpStr, 0, posComa));
				tmpStr.erase(0,posComa+1);
				m_floats[1] = etk::string_to_float(tmpStr);
			}
			TK_VERBOSE("Parse : \"" << _str << "\" ==> " << *this);
		}
	#endif

	template<> std::string to_string<vec2>(const vec2& _obj) {
		std::string str;
		str = "(";
		str += etk::to_string(_obj.x());
		str += ",";
		str += etk::to_string(_obj.y());
		str += ")";
		return str;
	}
	#if __CPP_VERSION__ >= 2011
		template<> std::u32string to_u32string<vec2>(const vec2& _obj) {
			return etk::to_u32string(etk::to_string(_obj));
		}
	#endif
	
	template<> std::string to_string<ivec2>(const ivec2& _obj) {
		std::string str;
		str = "(";
		str += etk::to_string(_obj.x());
		str += ",";
		str += etk::to_string(_obj.y());
		str += ")";
		return str;
	}
	#if __CPP_VERSION__ >= 2011
		template<> std::u32string to_u32string<ivec2>(const ivec2& _obj) {
			return etk::to_u32string(etk::to_string(_obj));
		}
	#endif
	
	template<> std::string to_string<uivec2>(const uivec2& _obj) {
		std::string str;
		str = "(";
		str += etk::to_string(_obj.x());
		str += ",";
		str += etk::to_string(_obj.y());
		str += ")";
		return str;
	}
	#if __CPP_VERSION__ >= 2011
		template<> std::u32string to_u32string<uivec2>(const uivec2& _obj) {
			return etk::to_u32string(etk::to_string(_obj));
		}
	#endif
	
	template<> std::string to_string<bvec2>(const bvec2& _obj) {
		std::string str;
		str = "(";
		str += etk::to_string(_obj.x());
		str += ",";
		str += etk::to_string(_obj.y());
		str += ")";
		return str;
	}
	#if __CPP_VERSION__ >= 2011
		template<> std::u32string to_u32string<bvec2>(const bvec2& _obj) {
			return etk::to_u32string(etk::to_string(_obj));
		}
	#endif
	
	template<> bool from_string<vec2>(vec2& _variableRet, const std::string& _value) {
		_variableRet = vec2(_value);
		return true;
	}
	#if __CPP_VERSION__ >= 2011
		template<> bool from_string<vec2>(vec2& _variableRet, const std::u32string& _value) {
			return from_string(_variableRet, etk::to_string(_value));
		}
	#endif
	
	template<> bool from_string<ivec2>(ivec2& _variableRet, const std::string& _value) {
		_variableRet = ivec2(_value);
		return true;
	}
	#if __CPP_VERSION__ >= 2011
		template<> bool from_string<ivec2>(ivec2& _variableRet, const std::u32string& _value) {
			return from_string(_variableRet, etk::to_string(_value));
		}
	#endif
	
	template<> bool from_string<uivec2>(uivec2& _variableRet, const std::string& _value) {
		_variableRet = uivec2(_value);
		return true;
	}
	#if __CPP_VERSION__ >= 2011
		template<> bool from_string<uivec2>(uivec2& _variableRet, const std::u32string& _value) {
			return from_string(_variableRet, etk::to_string(_value));
		}
	#endif
	
	template<> bool from_string<bvec2>(bvec2& _variableRet, const std::string& _value) {
		_variableRet = bvec2(_value);
		return true;
	}
	#if __CPP_VERSION__ >= 2011
		template<> bool from_string<bvec2>(bvec2& _variableRet, const std::u32string& _value) {
			return from_string(_variableRet, etk::to_string(_value));
		}
	#endif
};
