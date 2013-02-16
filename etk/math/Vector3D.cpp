/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/math/Vector3D.h>

etk::CCout& etk::operator <<(etk::CCout &os, const etk::Vector3D<int32_t> obj)
{
	os << "(";
	os << obj.x();
	os << ",";
	os << obj.y();
	os << ",";
	os << obj.z();
	os << ")";
	return os;
}

etk::CCout& etk::operator <<(etk::CCout &os, const btVector3 obj)
{
	os << "(";
	os << obj.x();
	os << ",";
	os << obj.y();
	os << ",";
	os << obj.z();
	os << ")";
	return os;
}

etk::CCout& etk::operator <<(etk::CCout &os, const etk::Vector3D<uint32_t> obj)
{
	os << "(";
	os << obj.x();
	os << ",";
	os << obj.y();
	os << ",";
	os << obj.z();
	os << ")";
	return os;
}

etk::CCout& etk::operator <<(etk::CCout &os, const etk::Vector3D<bool> obj)
{
	os << "(";
	os << obj.x();
	os << ",";
	os << obj.y();
	os << ",";
	os << obj.z();
	os << ")";
	return os;
}


vec3 quaternionToEulerXYZ(const btQuaternion& quat)
{
	// back to the euler angle : 
	float xxx = quat.x();
	float yyy = quat.y();
	float zzz = quat.z();
	float www = quat.w();
	double xxx2 = xxx*xxx;
	double yyy2 = yyy*yyy;
	double zzz2 = zzz*zzz;
	double www2 = www*www;
	// http://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
	return vec3( atan2(2.0*(yyy*zzz + xxx*www) , (-xxx2-yyy2+zzz2+www2) ),
	             asin(2.0*(xxx*zzz-yyy*www)),
	             atan2(2.0*(xxx*yyy + zzz*www), (xxx2-yyy2-zzz2+www2) ) );
}
