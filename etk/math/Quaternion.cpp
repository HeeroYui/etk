/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/math/Quaternion.hpp>

std::ostream& etk::operator <<(std::ostream &_os, const etk::Quaternion& _obj) {
	_os << "(";
	_os << _obj.x();
	_os << ",";
	_os << _obj.y();
	_os << ",";
	_os << _obj.z();
	_os << ",";
	_os << _obj.w();
	_os << ")";
	return _os;
}

etk::Quaternion::Quaternion(const etk::Matrix3x3& _matrix) {
	float trace = _matrix.getTrace();
	if (trace < 0.0f) {
		if (_matrix.m_mat[4] > _matrix.m_mat[0]) {
			if(_matrix.m_mat[8] > _matrix.m_mat[4]) {
				float rrr = sqrt(_matrix.m_mat[8] - _matrix.m_mat[0] - _matrix.m_mat[4] + 1.0f);
				float sss = 0.5f / rrr;
				m_floats[0] = (_matrix.m_mat[6] + _matrix.m_mat[2]) * sss;
				m_floats[1] = (_matrix.m_mat[5] + _matrix.m_mat[7]) * sss;
				m_floats[2] = 0.5f * rrr;
				m_floats[3] = (_matrix.m_mat[3] - _matrix.m_mat[1]) * sss;
			} else {
				float rrr = sqrt(_matrix.m_mat[4] - _matrix.m_mat[8] - _matrix.m_mat[0] + 1.0f);
				float sss = 0.5f / rrr;
				m_floats[0] = (_matrix.m_mat[1] + _matrix.m_mat[3]) * sss;
				m_floats[1] = 0.5f * rrr;
				m_floats[2] = (_matrix.m_mat[5] + _matrix.m_mat[7]) * sss;
				m_floats[3] = (_matrix.m_mat[2] - _matrix.m_mat[6]) * sss;
			}
		} else if (_matrix.m_mat[8] > _matrix.m_mat[0]) {
			float rrr = sqrt(_matrix.m_mat[8] - _matrix.m_mat[0] - _matrix.m_mat[4] + 1.0f);
			float sss = 0.5f / rrr;
			m_floats[0] = (_matrix.m_mat[6] + _matrix.m_mat[2]) * sss;
			m_floats[1] = (_matrix.m_mat[5] + _matrix.m_mat[7]) * sss;
			m_floats[2] = 0.5f * rrr;
			m_floats[3] = (_matrix.m_mat[3] - _matrix.m_mat[1]) * sss;
		} else {
			float rrr = sqrt(_matrix.m_mat[0] - _matrix.m_mat[4] - _matrix.m_mat[8] + 1.0f);
			float sss = 0.5f / rrr;
			m_floats[0] = 0.5f * rrr;
			m_floats[1] = (_matrix.m_mat[1] + _matrix.m_mat[3]) * sss;
			m_floats[2] = (_matrix.m_mat[6] - _matrix.m_mat[2]) * sss;
			m_floats[3] = (_matrix.m_mat[7] - _matrix.m_mat[5]) * sss;
		}
	} else {
		float rrr = sqrt(trace + 1.0f);
		float sss = 0.5f / rrr;
		m_floats[0] = (_matrix.m_mat[7] - _matrix.m_mat[5]) * sss;
		m_floats[1] = (_matrix.m_mat[2] - _matrix.m_mat[6]) * sss;
		m_floats[2] = (_matrix.m_mat[3] - _matrix.m_mat[1]) * sss;
		m_floats[3] = 0.5f * rrr;
	}
}

void etk::Quaternion::getAngleAxis(float& _angle, vec3& _axis) const {
	etk::Quaternion quaternion = getUnit();
	_angle = acos(quaternion.w()) * 2.0f;
	vec3 rotationAxis(quaternion.x(), quaternion.y(), quaternion.z());
	rotationAxis = rotationAxis.normalized();
	_axis.setValue(rotationAxis.x(), rotationAxis.y(), rotationAxis.z());
}

etk::Matrix3x3 etk::Quaternion::getMatrix() const {
	float nQ =   m_floats[0]*m_floats[0]
	           + m_floats[1]*m_floats[1]
	           + m_floats[2]*m_floats[2]
	           + m_floats[3]*m_floats[3];
	float sss = 0.0f;
	if (nQ > 0.0f) {
		sss = 2.0f / nQ;
	}
	float xs = m_floats[0]*sss;
	float ys = m_floats[1]*sss;
	float zs = m_floats[2]*sss;
	float wxs = m_floats[3]*xs;
	float wys = m_floats[3]*ys;
	float wzs = m_floats[3]*zs;
	float xxs = m_floats[0]*xs;
	float xys = m_floats[0]*ys;
	float xzs = m_floats[0]*zs;
	float yys = m_floats[1]*ys;
	float yzs = m_floats[1]*zs;
	float zzs = m_floats[2]*zs;
	return etk::Matrix3x3(1.0f - yys - zzs,
	                      xys - wzs,
	                      xzs + wys,
	                      xys + wzs,
	                      1.0f - xxs - zzs,
	                      yzs - wxs,
	                      xzs - wys,
	                      yzs + wxs,
	                      1.0f - xxs - yys);
}

etk::Quaternion etk::Quaternion::slerp(const Quaternion& _obj1,
                                       const Quaternion& _obj2,
                                       float _ttt) {
	TK_ASSERT(_ttt >= 0.0f && _ttt <= 1.0f, "wrong intermolation");
	float invert = 1.0f;
	float cosineTheta = _obj1.dot(_obj2);
	if (cosineTheta < 0.0f) {
		cosineTheta = -cosineTheta;
		invert = -1.0f;
	}
	if(1-cosineTheta < 0.00001f) {
		return _obj1 * (1.0f-_ttt) + _obj2 * (_ttt * invert);
	}
	float theta = acos(cosineTheta);
	float sineTheta = sin(theta);
	float coeff1 = sin((1.0f-_ttt)*theta) / sineTheta;
	float coeff2 = sin(_ttt*theta) / sineTheta * invert;
	return _obj1 * coeff1 + _obj2 * coeff2;
}

void etk::Quaternion::setEulerAngles(const vec3& _angles) {
	float angle = _angles.x() * 0.5f;
	float sinX = std::sin(angle);
	float cosX = std::cos(angle);
	angle = _angles.y() * 0.5f;
	float sinY = std::sin(angle);
	float cosY = std::cos(angle);
	angle = _angles.z() * 0.5f;
	float sinZ = std::sin(angle);
	float cosZ = std::cos(angle);
	float cosYcosZ = cosY * cosZ;
	float sinYcosZ = sinY * cosZ;
	float cosYsinZ = cosY * sinZ;
	float sinYsinZ = sinY * sinZ;
	m_floats[0] = sinX * cosYcosZ - cosX * sinYsinZ;
	m_floats[1] = cosX * sinYcosZ + sinX * cosYsinZ;
	m_floats[2] = cosX * cosYsinZ - sinX * sinYcosZ;
	m_floats[3] = cosX * cosYcosZ + sinX * sinYsinZ;
	normalize();
}

etk::Quaternion etk::Quaternion::zero() {
	return etk::Quaternion(0,0,0,0);
}

etk::Quaternion etk::Quaternion::identity() {
	return etk::Quaternion(0,0,0,1);
}
