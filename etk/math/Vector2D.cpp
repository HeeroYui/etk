/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/math/Vector2D.hpp>
#include <etk/stdTools.hpp>
#include <etk/debug.hpp>
#include <etk/typeInfo.hpp>

ETK_DECLARE_TYPE(etk::Vector2D<int32_t>);
ETK_DECLARE_TYPE(etk::Vector2D<float>);
ETK_DECLARE_TYPE(etk::Vector2D<uint32_t>);
ETK_DECLARE_TYPE(etk::Vector2D<bool>);

etk::Stream& etk::operator <<(etk::Stream& _os, const etk::Vector2D<int32_t>& _obj) {
	_os << "(";
	_os << _obj.x();
	_os << ",";
	_os << _obj.y();
	_os << ")";
	return _os;
}

etk::Stream& etk::operator <<(etk::Stream& _os, const etk::Vector2D<float>& _obj) {
	_os << "(";
	_os << _obj.x();
	_os << ",";
	_os << _obj.y();
	_os << ")";
	return _os;
}

etk::Stream& etk::operator <<(etk::Stream& _os, const etk::Vector2D<uint32_t>& _obj) {
	_os << "(";
	_os << _obj.x();
	_os << ",";
	_os << _obj.y();
	_os << ")";
	return _os;
}

etk::Stream& etk::operator <<(etk::Stream& _os, const etk::Vector2D<bool>& _obj) {
	_os << "(";
	_os << _obj.x();
	_os << ",";
	_os << _obj.y();
	_os << ")";
	return _os;
}

etk::Stream& etk::operator <<(etk::Stream& _os, const etk::Vector<vec2 >& _obj) {
	for (size_t iii = 0; iii < _obj.size(); ++iii) {
		if (iii != 0) {
			_os << " ";
		}
		_os << _obj[iii];
	}
	return _os;
}

etk::Stream& etk::operator <<(etk::Stream& _os, const etk::Vector<ivec2 >& _obj) {
	for (size_t iii = 0; iii < _obj.size(); ++iii) {
		if (iii != 0) {
			_os << " ";
		}
		_os << _obj[iii];
	}
	return _os;
}

etk::Stream& etk::operator <<(etk::Stream& _os, const etk::Vector<uivec2 >& _obj) {
	for (size_t iii = 0; iii < _obj.size(); ++iii) {
		if (iii != 0) {
			_os << " ";
		}
		_os << _obj[iii];
	}
	return _os;
}

etk::Stream& etk::operator <<(etk::Stream& _os, const etk::Vector<bvec2 >& _obj) {
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
		float sinAngle = etk::sin(_angle);
		float cosAngle = etk::cos(_angle);
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
	template<> Vector2D<bool>::operator etk::String() const {
		etk::String str;
		str = "(";
		str += etk::toString(x());
		str += ",";
		str += etk::toString(y());
		str += ")";
		return str;
	}
	#if __CPP_VERSION__ >= 2011
		template<> Vector2D<bool>::operator etk::UString() const {
			etk::UString str;
			str = U"(";
			str += etk::toUString(x());
			str += U",";
			str += etk::toUString(y());
			str += U")";
			return str;
		}
	#endif
	
	template<> Vector2D<bool>::Vector2D(const etk::String& _str) {
		m_floats[0] = false;
		m_floats[1] = false;
		// copy to permit to modify it :
		etk::String tmpStr = _str;
		if (tmpStr[0] == '(') {
			tmpStr.erase(tmpStr.begin());
		}
		if (tmpStr[tmpStr.size()-1] == ')') {
			tmpStr.erase(tmpStr.end()-1);
		}
		size_t posComa = tmpStr.find(',');
		if (posComa == etk::String::npos) {
			// no coma ...
			// in every case, we parse the first element :
			m_floats[0] = etk::string_to_bool(tmpStr);
			m_floats[1] = m_floats[0];
		} else {
			m_floats[0] = etk::string_to_bool(etk::String(tmpStr, 0, posComa));
			tmpStr.erase(0, posComa+1);
			m_floats[1] = etk::string_to_bool(tmpStr);
		}
		TK_VERBOSE("Parse : '" << _str << "' ==> " << *this);
	}
	#if __CPP_VERSION__ >= 2011
		template<> Vector2D<bool>::Vector2D(const etk::UString& _str) {
			m_floats[0] = false;
			m_floats[1] = false;
			// copy to permit to modify it :
			etk::UString tmpStr = _str;
			if (tmpStr[0] == '(') {
				tmpStr.erase(tmpStr.begin());
			}
			if (tmpStr[tmpStr.size()-1] == ')') {
				tmpStr.erase(tmpStr.end()-1);
			}
			size_t posComa = tmpStr.find(',');
			if (posComa == etk::String::npos) {
				// no coma ...
				// in every case, we parse the first element :
				m_floats[0] = etk::string_to_bool(tmpStr);
				m_floats[1] = m_floats[0];
			} else {
				m_floats[0] = etk::string_to_bool(etk::UString(tmpStr, 0, posComa));
				tmpStr.erase(0, posComa+1);
				m_floats[1] = etk::string_to_bool(tmpStr);
			}
			TK_VERBOSE("Parse : '" << _str << "' ==> " << *this);
		}
	#endif
	
	template<> Vector2D<int32_t>::operator etk::String() const {
		etk::String str;
		str = "(";
		str += etk::toString(x());
		str += ",";
		str += etk::toString(y());
		str += ")";
		return str;
	}
	#if __CPP_VERSION__ >= 2011
		template<> Vector2D<int32_t>::operator etk::UString() const {
			etk::UString str;
			str = U"(";
			str += etk::toUString(x());
			str += U",";
			str += etk::toUString(y());
			str += U")";
			return str;
		}
	#endif
	
	template<> Vector2D<int32_t>::Vector2D(const etk::String& _str) {
		m_floats[0] = 0;
		m_floats[1] = 0;
		// copy to permit to modify it :
		etk::String tmpStr = _str;
		if (tmpStr[0] == '(') {
			tmpStr.erase(tmpStr.begin());
		}
		if (tmpStr[tmpStr.size()-1] == ')') {
			tmpStr.erase(tmpStr.end()-1);
		}
		
		size_t posComa = tmpStr.find(',');
		if (posComa == etk::String::npos) {
			// no coma ...
			// in every case, we parse the first element :
			m_floats[0] = etk::string_to_int32_t(tmpStr);
			m_floats[1] = m_floats[0];
		} else {
			m_floats[0] = etk::string_to_int32_t(etk::String(tmpStr, 0, posComa));
			tmpStr.erase(0,posComa+1);
			m_floats[1] = etk::string_to_int32_t(tmpStr);
		}
		TK_VERBOSE("Parse : \"" << _str << "\" ==> " << *this);
	}
	#if __CPP_VERSION__ >= 2011
		template<> Vector2D<int32_t>::Vector2D(const etk::UString& _str) {
			m_floats[0] = 0;
			m_floats[1] = 0;
			// copy to permit to modify it :
			etk::UString tmpStr = _str;
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
				m_floats[0] = etk::string_to_int32_t(etk::UString(tmpStr, 0, posComa));
				tmpStr.erase(0,posComa+1);
				m_floats[1] = etk::string_to_int32_t(tmpStr);
			}
			TK_VERBOSE("Parse : \"" << _str << "\" ==> " << *this);
		}
	#endif
	
	template<> Vector2D<uint32_t>::operator etk::String() const {
		etk::String str;
		str = "(";
		str += etk::toString(x());
		str += ",";
		str += etk::toString(y());
		str += ")";
		return str;
	}
	#if __CPP_VERSION__ >= 2011
		template<> Vector2D<uint32_t>::operator etk::UString() const {
			etk::UString str;
			str = U"(";
			str += etk::toUString(x());
			str += U",";
			str += etk::toUString(y());
			str += U")";
			return str;
		}
	#endif
	
	template<> Vector2D<uint32_t>::Vector2D(const etk::String& _str) {
		m_floats[0] = 0;
		m_floats[1] = 0;
		// copy to permit to modify it :
		etk::String tmpStr = _str;
		if (tmpStr[0] == '(') {
			tmpStr.erase(tmpStr.begin());
		}
		if (tmpStr[tmpStr.size()-1] == ')') {
			tmpStr.erase(tmpStr.end()-1);
		}
		size_t posComa = tmpStr.find(',');
		if (posComa == etk::String::npos) {
			// no coma ...
			// in every case, we parse the first element :
			m_floats[0] = etk::string_to_int32_t(tmpStr);
			m_floats[1] = m_floats[0];
		} else {
			m_floats[0] = etk::string_to_int32_t(etk::String(tmpStr, 0, posComa));
			tmpStr.erase(0,posComa+1);
			m_floats[1] = etk::string_to_int32_t(tmpStr);
		}
		TK_VERBOSE("Parse : \"" << _str << "\" ==> " << *this);
	}
	#if __CPP_VERSION__ >= 2011
		template<> Vector2D<uint32_t>::Vector2D(const etk::UString& _str) {
			m_floats[0] = 0;
			m_floats[1] = 0;
			// copy to permit to modify it :
			etk::UString tmpStr = _str;
			if (tmpStr[0] == '(') {
				tmpStr.erase(tmpStr.begin());
			}
			if (tmpStr[tmpStr.size()-1] == ')') {
				tmpStr.erase(tmpStr.end()-1);
			}
			size_t posComa = tmpStr.find(',');
			if (posComa == etk::String::npos) {
				// no coma ...
				// in every case, we parse the first element :
				m_floats[0] = etk::string_to_int32_t(tmpStr);
				m_floats[1] = m_floats[0];
			} else {
				m_floats[0] = etk::string_to_int32_t(etk::UString(tmpStr, 0, posComa));
				tmpStr.erase(0,posComa+1);
				m_floats[1] = etk::string_to_int32_t(tmpStr);
			}
			TK_VERBOSE("Parse : \"" << _str << "\" ==> " << *this);
		}
	#endif
	
	template<> Vector2D<float>::operator etk::String() const {
		etk::String str;
		str = "(";
		str += etk::toString(x());
		str += ",";
		str += etk::toString(y());
		str += ")";
		return str;
	}
	#if __CPP_VERSION__ >= 2011
		template<> Vector2D<float>::operator etk::UString() const {
			etk::UString str;
			str = U"(";
			str += etk::toUString(x());
			str += U",";
			str += etk::toUString(y());
			str += U")";
			return str;
		}
	#endif
	
	template<> Vector2D<float>::Vector2D(const etk::String& _str) {
		m_floats[0] = 0;
		m_floats[1] = 0;
		// copy to permit to modify it :
		etk::String tmpStr = _str;
		if (tmpStr[0] == '(') {
			tmpStr.erase(tmpStr.begin());
		}
		if (tmpStr[tmpStr.size()-1] == ')') {
			tmpStr.erase(tmpStr.end()-1);
		}
		size_t posComa = tmpStr.find(',');
		if (posComa == etk::String::npos) {
			// no coma ...
			// in every case, we parse the first element :
			m_floats[0] = etk::string_to_float(tmpStr);
			m_floats[1] = m_floats[0];
		} else {
			m_floats[0] = etk::string_to_float(etk::String(tmpStr, 0, posComa));
			tmpStr.erase(0,posComa+1);
			m_floats[1] = etk::string_to_float(tmpStr);
		}
		TK_VERBOSE("Parse : \"" << _str << "\" ==> " << *this);
	}
	#if __CPP_VERSION__ >= 2011
		template<> Vector2D<float>::Vector2D(const etk::UString& _str) {
			m_floats[0] = 0;
			m_floats[1] = 0;
			// copy to permit to modify it :
			etk::UString tmpStr = _str;
			if (tmpStr[0] == '(') {
				tmpStr.erase(tmpStr.begin());
			}
			if (tmpStr[tmpStr.size()-1] == ')') {
				tmpStr.erase(tmpStr.end()-1);
			}
			size_t posComa = tmpStr.find(',');
			if (posComa == etk::String::npos) {
				// no coma ...
				// in every case, we parse the first element :
				m_floats[0] = etk::string_to_float(tmpStr);
				m_floats[1] = m_floats[0];
			} else {
				m_floats[0] = etk::string_to_float(etk::UString(tmpStr, 0, posComa));
				tmpStr.erase(0,posComa+1);
				m_floats[1] = etk::string_to_float(tmpStr);
			}
			TK_VERBOSE("Parse : \"" << _str << "\" ==> " << *this);
		}
	#endif

	template<> etk::String toString<vec2>(const vec2& _obj) {
		etk::String str;
		str = "(";
		str += etk::toString(_obj.x());
		str += ",";
		str += etk::toString(_obj.y());
		str += ")";
		return str;
	}
	#if __CPP_VERSION__ >= 2011
		template<> etk::UString toUString<vec2>(const vec2& _obj) {
			return etk::toUString(etk::toString(_obj));
		}
	#endif
	
	template<> etk::String toString<ivec2>(const ivec2& _obj) {
		etk::String str;
		str = "(";
		str += etk::toString(_obj.x());
		str += ",";
		str += etk::toString(_obj.y());
		str += ")";
		return str;
	}
	#if __CPP_VERSION__ >= 2011
		template<> etk::UString toUString<ivec2>(const ivec2& _obj) {
			return etk::toUString(etk::toString(_obj));
		}
	#endif
	
	template<> etk::String toString<uivec2>(const uivec2& _obj) {
		etk::String str;
		str = "(";
		str += etk::toString(_obj.x());
		str += ",";
		str += etk::toString(_obj.y());
		str += ")";
		return str;
	}
	#if __CPP_VERSION__ >= 2011
		template<> etk::UString toUString<uivec2>(const uivec2& _obj) {
			return etk::toUString(etk::toString(_obj));
		}
	#endif
	
	template<> etk::String toString<bvec2>(const bvec2& _obj) {
		etk::String str;
		str = "(";
		str += etk::toString(_obj.x());
		str += ",";
		str += etk::toString(_obj.y());
		str += ")";
		return str;
	}
	#if __CPP_VERSION__ >= 2011
		template<> etk::UString toUString<bvec2>(const bvec2& _obj) {
			return etk::toUString(etk::toString(_obj));
		}
	#endif
	
	template<> bool from_string<vec2>(vec2& _variableRet, const etk::String& _value) {
		_variableRet = vec2(_value);
		return true;
	}
	#if __CPP_VERSION__ >= 2011
		template<> bool from_string<vec2>(vec2& _variableRet, const etk::UString& _value) {
			return from_string(_variableRet, etk::toString(_value));
		}
	#endif
	
	template<> bool from_string<ivec2>(ivec2& _variableRet, const etk::String& _value) {
		_variableRet = ivec2(_value);
		return true;
	}
	#if __CPP_VERSION__ >= 2011
		template<> bool from_string<ivec2>(ivec2& _variableRet, const etk::UString& _value) {
			return from_string(_variableRet, etk::toString(_value));
		}
	#endif
	
	template<> bool from_string<uivec2>(uivec2& _variableRet, const etk::String& _value) {
		_variableRet = uivec2(_value);
		return true;
	}
	#if __CPP_VERSION__ >= 2011
		template<> bool from_string<uivec2>(uivec2& _variableRet, const etk::UString& _value) {
			return from_string(_variableRet, etk::toString(_value));
		}
	#endif
	
	template<> bool from_string<bvec2>(bvec2& _variableRet, const etk::String& _value) {
		_variableRet = bvec2(_value);
		return true;
	}
	#if __CPP_VERSION__ >= 2011
		template<> bool from_string<bvec2>(bvec2& _variableRet, const etk::UString& _value) {
			return from_string(_variableRet, etk::toString(_value));
		}
	#endif
};
