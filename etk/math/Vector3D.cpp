/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <etk/math/Vector3D.h>

std::ostream& etk::operator <<(std::ostream& _os, const etk::Vector3D<int32_t>& _obj) {
	_os << "(";
	_os << _obj.x();
	_os << ",";
	_os << _obj.y();
	_os << ",";
	_os << _obj.z();
	_os << ")";
	return _os;
}

std::ostream& etk::operator <<(std::ostream& _os, const btVector3& _obj) {
	_os << "(";
	_os << _obj.x();
	_os << ",";
	_os << _obj.y();
	_os << ",";
	_os << _obj.z();
	_os << ")";
	return _os;
}

std::ostream& etk::operator <<(std::ostream& _os, const etk::Vector3D<uint32_t>& _obj) {
	_os << "(";
	_os << _obj.x();
	_os << ",";
	_os << _obj.y();
	_os << ",";
	_os << _obj.z();
	_os << ")";
	return _os;
}

std::ostream& etk::operator <<(std::ostream& _os, const etk::Vector3D<bool>& _obj) {
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


std::string std::to_string(const vec3& _obj) {
	std::string str;
	str = "(";
	str += std::to_string(_obj.x());
	str += ",";
	str += std::to_string(_obj.y());
	str += ",";
	str += std::to_string(_obj.z());
	str += ")";
	return str;
}

std::string std::to_string(const ivec3& _obj) {
	std::string str;
	str = "(";
	str += std::to_string(_obj.x());
	str += ",";
	str += std::to_string(_obj.y());
	str += ",";
	str += std::to_string(_obj.z());
	str += ")";
	return str;
}

std::string std::to_string(const uivec3& _obj) {
	std::string str;
	str = "(";
	str += std::to_string(_obj.x());
	str += ",";
	str += std::to_string(_obj.y());
	str += ",";
	str += std::to_string(_obj.z());
	str += ")";
	return str;
}

std::string std::to_string(const bvec3& _obj) {
	std::string str;
	str = "(";
	str += std::to_string(_obj.x());
	str += ",";
	str += std::to_string(_obj.y());
	str += ",";
	str += std::to_string(_obj.z());
	str += ")";
	return str;
}
