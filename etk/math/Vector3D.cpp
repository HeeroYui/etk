/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <etk/math/Vector3D.h>
#include <etk/stdTools.h>

std::ostream& etk::operator <<(std::ostream& _os, const ivec3& _obj) {
	_os << "(";
	_os << _obj.x();
	_os << ",";
	_os << _obj.y();
	_os << ",";
	_os << _obj.z();
	_os << ")";
	return _os;
}

std::ostream& operator <<(std::ostream& _os, const vec3& _obj) {
	_os << "(";
	_os << _obj.x();
	_os << ",";
	_os << _obj.y();
	_os << ",";
	_os << _obj.z();
	_os << ")";
	return _os;
}

std::ostream& etk::operator <<(std::ostream& _os, const uivec3& _obj) {
	_os << "(";
	_os << _obj.x();
	_os << ",";
	_os << _obj.y();
	_os << ",";
	_os << _obj.z();
	_os << ")";
	return _os;
}

std::ostream& etk::operator <<(std::ostream& _os, const bvec3& _obj) {
	_os << "(";
	_os << _obj.x();
	_os << ",";
	_os << _obj.y();
	_os << ",";
	_os << _obj.z();
	_os << ")";
	return _os;
}


std::ostream& etk::operator <<(std::ostream& _os, const std::vector<vec3>& _obj) {
	for (size_t iii = 0; iii < _obj.size(); ++iii) {
		if (iii != 0) {
			_os << " ";
		}
		_os << _obj[iii];
	}
	return _os;
}

std::ostream& etk::operator <<(std::ostream& _os, const std::vector<ivec3>& _obj) {
	for (size_t iii = 0; iii < _obj.size(); ++iii) {
		if (iii != 0) {
			_os << " ";
		}
		_os << _obj[iii];
	}
	return _os;
}

std::ostream& etk::operator <<(std::ostream& _os, const std::vector<uivec3>& _obj) {
	for (size_t iii = 0; iii < _obj.size(); ++iii) {
		if (iii != 0) {
			_os << " ";
		}
		_os << _obj[iii];
	}
	return _os;
}

std::ostream& etk::operator <<(std::ostream& _os, const std::vector<bvec3>& _obj) {
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
	template<> std::string to_string<vec3>(const vec3& _obj) {
		std::string str;
		str = "(";
		str += etk::to_string(_obj.x());
		str += ",";
		str += etk::to_string(_obj.y());
		str += ",";
		str += etk::to_string(_obj.z());
		str += ")";
		return str;
	}
	#if __CPP_VERSION__ >= 2011
		template<> std::u32string to_u32string<vec3>(const vec3& _obj) {
			return etk::to_u32string(etk::to_string(_obj));
		}
	#endif
	
	template<> std::string to_string<ivec3>(const ivec3& _obj) {
		std::string str;
		str = "(";
		str += etk::to_string(_obj.x());
		str += ",";
		str += etk::to_string(_obj.y());
		str += ",";
		str += etk::to_string(_obj.z());
		str += ")";
		return str;
	}
	#if __CPP_VERSION__ >= 2011
		template<> std::u32string to_u32string<ivec3>(const ivec3& _obj) {
			return etk::to_u32string(etk::to_string(_obj));
		}
	#endif
	
	template<> std::string to_string<uivec3>(const uivec3& _obj) {
		std::string str;
		str = "(";
		str += etk::to_string(_obj.x());
		str += ",";
		str += etk::to_string(_obj.y());
		str += ",";
		str += etk::to_string(_obj.z());
		str += ")";
		return str;
	}
	#if __CPP_VERSION__ >= 2011
		template<> std::u32string to_u32string<uivec3>(const uivec3& _obj) {
			return etk::to_u32string(etk::to_string(_obj));
		}
	#endif
	
	template<> std::string to_string<bvec3>(const bvec3& _obj) {
		std::string str;
		str = "(";
		str += etk::to_string(_obj.x());
		str += ",";
		str += etk::to_string(_obj.y());
		str += ",";
		str += etk::to_string(_obj.z());
		str += ")";
		return str;
	}
	#if __CPP_VERSION__ >= 2011
		template<> std::u32string to_u32string<bvec3>(const bvec3& _obj) {
			return etk::to_u32string(etk::to_string(_obj));
		}
	#endif
	
	template<> bool from_string<vec3>(vec3& _variableRet, const std::string& _value) {
		float floats[3];
		floats[0] = 0;
		floats[1] = 0;
		floats[2] = 0;
		// copy to permit to modify it :
		std::string tmpStr = _value;
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
			floats[0] = etk::string_to_float(tmpStr);
			floats[1] = floats[0];
			floats[2] = floats[1];
		} else {
			floats[0] = etk::string_to_float(std::string(tmpStr, 0, posComa));
			tmpStr.erase(0,posComa+1);
			posComa = tmpStr.find(',');
			if (posComa == std::string::npos) {
				// no coma ...
				// in every case, we parse the first element :
				floats[1] = etk::string_to_float(tmpStr);
				floats[2] = floats[1];
			} else {
				floats[1] = etk::string_to_float(std::string(tmpStr, 0, posComa));
				tmpStr.erase(0,posComa+1);
				floats[2] = etk::string_to_float(tmpStr);
			}
		}
		_variableRet.setValue(floats[0], floats[1], floats[2]);
		TK_VERBOSE("Parse : '" << _value << "' ==> " << _variableRet);
		return true;
	}
	#if __CPP_VERSION__ >= 2011
		template<> bool from_string<vec3>(vec3& _variableRet, const std::u32string& _value) {
			return from_string(_variableRet, etk::to_string(_value));
		}
	#endif
	
	template<> bool from_string<ivec3>(ivec3& _variableRet, const std::string& _value) {
		int32_t floats[3];
		floats[0] = 0;
		floats[1] = 0;
		floats[2] = 0;
		// copy to permit to modify it :
		std::string tmpStr = _value;
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
			floats[0] = etk::string_to_int32_t(tmpStr);
			floats[1] = floats[0];
			floats[2] = floats[1];
		} else {
			floats[0] = etk::string_to_int32_t(std::string(tmpStr, 0, posComa));
			tmpStr.erase(0,posComa+1);
			posComa = tmpStr.find(',');
			if (posComa == std::string::npos) {
				// no coma ...
				// in every case, we parse the first element :
				floats[1] = etk::string_to_int32_t(tmpStr);
				floats[2] = floats[1];
			} else {
				floats[1] = etk::string_to_int32_t(std::string(tmpStr, 0, posComa));
				tmpStr.erase(0,posComa+1);
				floats[2] = etk::string_to_int32_t(tmpStr);
			}
		}
		_variableRet.setValue(floats[0], floats[1], floats[2]);
		TK_VERBOSE("Parse : '" << _value << "' ==> " << _variableRet);
		return true;
	}
	#if __CPP_VERSION__ >= 2011
		template<> bool from_string<ivec3>(ivec3& _variableRet, const std::u32string& _value) {
			return from_string(_variableRet, etk::to_string(_value));
		}
	#endif
	
	template<> bool from_string<uivec3>(uivec3& _variableRet, const std::string& _value) {
		uint32_t floats[3];
		floats[0] = 0;
		floats[1] = 0;
		floats[2] = 0;
		// copy to permit to modify it :
		std::string tmpStr = _value;
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
			floats[0] = etk::string_to_int32_t(tmpStr);
			floats[1] = floats[0];
			floats[2] = floats[1];
		} else {
			floats[0] = etk::string_to_int32_t(std::string(tmpStr, 0, posComa));
			tmpStr.erase(0,posComa+1);
			posComa = tmpStr.find(',');
			if (posComa == std::string::npos) {
				// no coma ...
				// in every case, we parse the first element :
				floats[1] = etk::string_to_int32_t(tmpStr);
				floats[2] = floats[1];
			} else {
				floats[1] = etk::string_to_int32_t(std::string(tmpStr, 0, posComa));
				tmpStr.erase(0,posComa+1);
				floats[2] = etk::string_to_int32_t(tmpStr);
			}
		}
		_variableRet.setValue(floats[0], floats[1], floats[2]);
		TK_VERBOSE("Parse : '" << _value << "' ==> " << _variableRet);
		return true;
	}
	#if __CPP_VERSION__ >= 2011
		template<> bool from_string<uivec3>(uivec3& _variableRet, const std::u32string& _value) {
			return from_string(_variableRet, etk::to_string(_value));
		}
	#endif
	
	template<> bool from_string<bvec3>(bvec3& _variableRet, const std::string& _value) {
		bool floats[3];
		floats[0] = false;
		floats[1] = false;
		floats[2] = false;
		// copy to permit to modify it :
		std::string tmpStr = _value;
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
			floats[0] = etk::string_to_bool(tmpStr);
			floats[1] = floats[0];
			floats[2] = floats[1];
		} else {
			floats[0] = etk::string_to_bool(std::string(tmpStr, 0, posComa));
			tmpStr.erase(0,posComa+1);
			posComa = tmpStr.find(',');
			if (posComa == std::string::npos) {
				// no coma ...
				// in every case, we parse the first element :
				floats[1] = etk::string_to_bool(tmpStr);
				floats[2] = floats[1];
			} else {
				floats[1] = etk::string_to_bool(std::string(tmpStr, 0, posComa));
				tmpStr.erase(0,posComa+1);
				floats[2] = etk::string_to_bool(tmpStr);
			}
		}
		_variableRet.setValue(floats[0], floats[1], floats[2]);
		TK_VERBOSE("Parse : '" << _value << "' ==> " << _variableRet);
		return true;
	}
	#if __CPP_VERSION__ >= 2011
		template<> bool from_string<bvec3>(bvec3& _variableRet, const std::u32string& _value) {
			return from_string(_variableRet, etk::to_string(_value));
		}
	#endif
};
