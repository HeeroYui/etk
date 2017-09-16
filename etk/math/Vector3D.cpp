/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/math/Vector3D.hpp>
#include <etk/stdTools.hpp>
#include <etk/debug.hpp>
#include <etk/typeInfo.hpp>

ETK_DECLARE_TYPE(etk::Vector3D<int32_t>);
ETK_DECLARE_TYPE(etk::Vector3D<float>);
ETK_DECLARE_TYPE(etk::Vector3D<uint32_t>);
ETK_DECLARE_TYPE(etk::Vector3D<bool>);

etk::Stream& etk::operator <<(etk::Stream& _os, const etk::Vector3D<int32_t>& _obj) {
	_os << "(";
	_os << _obj.x();
	_os << ",";
	_os << _obj.y();
	_os << ",";
	_os << _obj.z();
	_os << ")";
	return _os;
}

#ifdef ETK_BUILD_LINEARMATH
	etk::Stream& operator <<(etk::Stream& _os, const btVector3& _obj) {
		_os << "(";
		_os << _obj.x();
		_os << ",";
		_os << _obj.y();
		_os << ",";
		_os << _obj.z();
		_os << ")";
		return _os;
	}
#endif

etk::Stream& etk::operator <<(etk::Stream& _os, const etk::Vector3D<float>& _obj) {
	_os << "(";
	_os << _obj.x();
	_os << ",";
	_os << _obj.y();
	_os << ",";
	_os << _obj.z();
	_os << ")";
	return _os;
}

etk::Stream& etk::operator <<(etk::Stream& _os, const etk::Vector3D<uint32_t>& _obj) {
	_os << "(";
	_os << _obj.x();
	_os << ",";
	_os << _obj.y();
	_os << ",";
	_os << _obj.z();
	_os << ")";
	return _os;
}

etk::Stream& etk::operator <<(etk::Stream& _os, const etk::Vector3D<bool>& _obj) {
	_os << "(";
	_os << _obj.x();
	_os << ",";
	_os << _obj.y();
	_os << ",";
	_os << _obj.z();
	_os << ")";
	return _os;
}



#ifdef ETK_BUILD_LINEARMATH
	etk::Stream& operator <<(etk::Stream& _os, const etk::Vector<btVector3>& _obj) {
		for (size_t iii = 0; iii < _obj.size(); ++iii) {
			if (iii != 0) {
				_os << " ";
			}
			_os << _obj[iii];
		}
		return _os;
	}
#endif

etk::Stream& etk::operator <<(etk::Stream& _os, const etk::Vector<etk::Vector3D<float>>& _obj) {
	for (size_t iii = 0; iii < _obj.size(); ++iii) {
		if (iii != 0) {
			_os << " ";
		}
		_os << _obj[iii];
	}
	return _os;
}

etk::Stream& etk::operator <<(etk::Stream& _os, const etk::Vector<etk::Vector3D<int32_t>>& _obj) {
	for (size_t iii = 0; iii < _obj.size(); ++iii) {
		if (iii != 0) {
			_os << " ";
		}
		_os << _obj[iii];
	}
	return _os;
}

etk::Stream& etk::operator <<(etk::Stream& _os, const etk::Vector<etk::Vector3D<uint32_t>>& _obj) {
	for (size_t iii = 0; iii < _obj.size(); ++iii) {
		if (iii != 0) {
			_os << " ";
		}
		_os << _obj[iii];
	}
	return _os;
}

etk::Stream& etk::operator <<(etk::Stream& _os, const etk::Vector<etk::Vector3D<bool>>& _obj) {
	for (size_t iii = 0; iii < _obj.size(); ++iii) {
		if (iii != 0) {
			_os << " ";
		}
		_os << _obj[iii];
	}
	return _os;
}

#ifdef __ETK_BUILD_LINEARMATH__
vec3 quaternionToEulerXYZ(const btQuaternion& _quat) {
	// back to the euler angle : 
	float xxx = _quat.x();
	float yyy = _quat.y();
	float zzz = _quat.z();
	float www = _quat.w();
	double xxx2 = xxx*xxx;
	double yyy2 = yyy*yyy;
	double zzz2 = zzz*zzz;
	double www2 = www*www;
	// http://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
	return vec3( atan2(2.0*(yyy*zzz + xxx*www) , (-xxx2-yyy2+zzz2+www2) ),
	             asin(2.0*(xxx*zzz-yyy*www)),
	             atan2(2.0*(xxx*yyy + zzz*www), (xxx2-yyy2-zzz2+www2) ) );
}
#endif

namespace etk {
	template<> etk::String toString<vec3>(const vec3& _obj) {
		etk::String str;
		str = "(";
		str += etk::toString(_obj.x());
		str += ",";
		str += etk::toString(_obj.y());
		str += ",";
		str += etk::toString(_obj.z());
		str += ")";
		return str;
	}
	#if __CPP_VERSION__ >= 2011
		template<> etk::UString toUString<vec3>(const vec3& _obj) {
			return etk::toUString(etk::toString(_obj));
		}
	#endif
	
	template<> etk::String toString<ivec3>(const ivec3& _obj) {
		etk::String str;
		str = "(";
		str += etk::toString(_obj.x());
		str += ",";
		str += etk::toString(_obj.y());
		str += ",";
		str += etk::toString(_obj.z());
		str += ")";
		return str;
	}
	#if __CPP_VERSION__ >= 2011
		template<> etk::UString toUString<ivec3>(const ivec3& _obj) {
			return etk::toUString(etk::toString(_obj));
		}
	#endif
	
	template<> etk::String toString<uivec3>(const uivec3& _obj) {
		etk::String str;
		str = "(";
		str += etk::toString(_obj.x());
		str += ",";
		str += etk::toString(_obj.y());
		str += ",";
		str += etk::toString(_obj.z());
		str += ")";
		return str;
	}
	#if __CPP_VERSION__ >= 2011
		template<> etk::UString toUString<uivec3>(const uivec3& _obj) {
			return etk::toUString(etk::toString(_obj));
		}
	#endif
	
	template<> etk::String toString<bvec3>(const bvec3& _obj) {
		etk::String str;
		str = "(";
		str += etk::toString(_obj.x());
		str += ",";
		str += etk::toString(_obj.y());
		str += ",";
		str += etk::toString(_obj.z());
		str += ")";
		return str;
	}
	#if __CPP_VERSION__ >= 2011
		template<> etk::UString toUString<bvec3>(const bvec3& _obj) {
			return etk::toUString(etk::toString(_obj));
		}
	#endif
	
	template<> bool from_string<vec3>(vec3& _variableRet, const etk::String& _value) {
		float floats[3];
		floats[0] = 0;
		floats[1] = 0;
		floats[2] = 0;
		// copy to permit to modify it :
		etk::String tmpStr = _value;
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
			floats[0] = etk::string_to_float(tmpStr);
			floats[1] = floats[0];
			floats[2] = floats[1];
		} else {
			floats[0] = etk::string_to_float(etk::String(tmpStr, 0, posComa));
			tmpStr.erase(0,posComa+1);
			posComa = tmpStr.find(',');
			if (posComa == etk::String::npos) {
				// no coma ...
				// in every case, we parse the first element :
				floats[1] = etk::string_to_float(tmpStr);
				floats[2] = floats[1];
			} else {
				floats[1] = etk::string_to_float(etk::String(tmpStr, 0, posComa));
				tmpStr.erase(0,posComa+1);
				floats[2] = etk::string_to_float(tmpStr);
			}
		}
		_variableRet.setValue(floats[0], floats[1], floats[2]);
		TK_VERBOSE("Parse : '" << _value << "' ==> " << _variableRet);
		return true;
	}
	#if __CPP_VERSION__ >= 2011
		template<> bool from_string<vec3>(vec3& _variableRet, const etk::UString& _value) {
			return from_string(_variableRet, etk::toString(_value));
		}
	#endif
	
	template<> bool from_string<ivec3>(ivec3& _variableRet, const etk::String& _value) {
		int32_t floats[3];
		floats[0] = 0;
		floats[1] = 0;
		floats[2] = 0;
		// copy to permit to modify it :
		etk::String tmpStr = _value;
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
			floats[0] = etk::string_to_int32_t(tmpStr);
			floats[1] = floats[0];
			floats[2] = floats[1];
		} else {
			floats[0] = etk::string_to_int32_t(etk::String(tmpStr, 0, posComa));
			tmpStr.erase(0,posComa+1);
			posComa = tmpStr.find(',');
			if (posComa == etk::String::npos) {
				// no coma ...
				// in every case, we parse the first element :
				floats[1] = etk::string_to_int32_t(tmpStr);
				floats[2] = floats[1];
			} else {
				floats[1] = etk::string_to_int32_t(etk::String(tmpStr, 0, posComa));
				tmpStr.erase(0,posComa+1);
				floats[2] = etk::string_to_int32_t(tmpStr);
			}
		}
		_variableRet.setValue(floats[0], floats[1], floats[2]);
		TK_VERBOSE("Parse : '" << _value << "' ==> " << _variableRet);
		return true;
	}
	#if __CPP_VERSION__ >= 2011
		template<> bool from_string<ivec3>(ivec3& _variableRet, const etk::UString& _value) {
			return from_string(_variableRet, etk::toString(_value));
		}
	#endif
	
	template<> bool from_string<uivec3>(uivec3& _variableRet, const etk::String& _value) {
		uint32_t floats[3];
		floats[0] = 0;
		floats[1] = 0;
		floats[2] = 0;
		// copy to permit to modify it :
		etk::String tmpStr = _value;
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
			floats[0] = etk::string_to_int32_t(tmpStr);
			floats[1] = floats[0];
			floats[2] = floats[1];
		} else {
			floats[0] = etk::string_to_int32_t(etk::String(tmpStr, 0, posComa));
			tmpStr.erase(0,posComa+1);
			posComa = tmpStr.find(',');
			if (posComa == etk::String::npos) {
				// no coma ...
				// in every case, we parse the first element :
				floats[1] = etk::string_to_int32_t(tmpStr);
				floats[2] = floats[1];
			} else {
				floats[1] = etk::string_to_int32_t(etk::String(tmpStr, 0, posComa));
				tmpStr.erase(0,posComa+1);
				floats[2] = etk::string_to_int32_t(tmpStr);
			}
		}
		_variableRet.setValue(floats[0], floats[1], floats[2]);
		TK_VERBOSE("Parse : '" << _value << "' ==> " << _variableRet);
		return true;
	}
	#if __CPP_VERSION__ >= 2011
		template<> bool from_string<uivec3>(uivec3& _variableRet, const etk::UString& _value) {
			return from_string(_variableRet, etk::toString(_value));
		}
	#endif
	
	template<> bool from_string<bvec3>(bvec3& _variableRet, const etk::String& _value) {
		bool floats[3];
		floats[0] = false;
		floats[1] = false;
		floats[2] = false;
		// copy to permit to modify it :
		etk::String tmpStr = _value;
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
			floats[0] = etk::string_to_bool(tmpStr);
			floats[1] = floats[0];
			floats[2] = floats[1];
		} else {
			floats[0] = etk::string_to_bool(etk::String(tmpStr, 0, posComa));
			tmpStr.erase(0,posComa+1);
			posComa = tmpStr.find(',');
			if (posComa == etk::String::npos) {
				// no coma ...
				// in every case, we parse the first element :
				floats[1] = etk::string_to_bool(tmpStr);
				floats[2] = floats[1];
			} else {
				floats[1] = etk::string_to_bool(etk::String(tmpStr, 0, posComa));
				tmpStr.erase(0,posComa+1);
				floats[2] = etk::string_to_bool(tmpStr);
			}
		}
		_variableRet.setValue(floats[0], floats[1], floats[2]);
		TK_VERBOSE("Parse : '" << _value << "' ==> " << _variableRet);
		return true;
	}
	#if __CPP_VERSION__ >= 2011
		template<> bool from_string<bvec3>(bvec3& _variableRet, const etk::UString& _value) {
			return from_string(_variableRet, etk::toString(_value));
		}
	#endif
};
