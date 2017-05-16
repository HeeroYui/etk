/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/math/Matrix3x3.hpp>


std::ostream& etk::operator <<(std::ostream& _os, const etk::Matrix3x3& _obj) {
	_os << "{";
	_os << _obj.m_mat[0] << ",";
	_os << _obj.m_mat[1] << ",";
	_os << _obj.m_mat[2] << ";";
	_os << _obj.m_mat[3] << ",";
	_os << _obj.m_mat[4] << ",";
	_os << _obj.m_mat[5] << ";";
	_os << _obj.m_mat[6] << ",";
	_os << _obj.m_mat[7] << ",";
	_os << _obj.m_mat[8] << "}";
	return _os;
}

etk::Matrix3x3::Matrix3x3() {
	m_mat[0] = 0.0f;
	m_mat[1] = 0.0f;
	m_mat[2] = 0.0f;
	m_mat[3] = 0.0f;
	m_mat[4] = 0.0f;
	m_mat[5] = 0.0f;
	m_mat[6] = 0.0f;
	m_mat[7] = 0.0f;
	m_mat[8] = 0.0f;
}

etk::Matrix3x3::Matrix3x3(float _value) {
	m_mat[0] = _value;
	m_mat[1] = _value;
	m_mat[2] = _value;
	m_mat[3] = _value;
	m_mat[4] = _value;
	m_mat[5] = _value;
	m_mat[6] = _value;
	m_mat[7] = _value;
	m_mat[8] = _value;
}

etk::Matrix3x3::Matrix3x3(float _a1, float _a2, float _a3,
                      float _b1, float _b2, float _b3,
                      float _c1, float _c2, float _c3) {
	m_mat[0] = _a1; m_mat[1] = _a2; m_mat[2] = _a3;
	m_mat[3] = _b1; m_mat[4] = _b2; m_mat[5] = _b3;
	m_mat[6] = _c1; m_mat[7] = _c2; m_mat[8] = _c3;
}

etk::Matrix3x3::Matrix3x3(const etk::Matrix3x3& _obj) {
	m_mat[0] = _obj.m_mat[0];
	m_mat[1] = _obj.m_mat[1];
	m_mat[2] = _obj.m_mat[2];
	m_mat[3] = _obj.m_mat[3];
	m_mat[4] = _obj.m_mat[4];
	m_mat[5] = _obj.m_mat[5];
	m_mat[6] = _obj.m_mat[6];
	m_mat[7] = _obj.m_mat[7];
	m_mat[8] = _obj.m_mat[8];
}

void etk::Matrix3x3::setValue(float _a1, float _a2, float _a3,
                            float _b1, float _b2, float _b3,
                            float _c1, float _c2, float _c3) {
	m_mat[0] = _a1; m_mat[1] = _a2; m_mat[2] = _a3;
	m_mat[3] = _b1; m_mat[4] = _b2; m_mat[5] = _b3;
	m_mat[6] = _c1; m_mat[7] = _c2; m_mat[8] = _c3;
}

void etk::Matrix3x3::setZero() {
	m_mat[0] = 0.0f;
	m_mat[1] = 0.0f;
	m_mat[2] = 0.0f;
	m_mat[3] = 0.0f;
	m_mat[4] = 0.0f;
	m_mat[5] = 0.0f;
	m_mat[6] = 0.0f;
	m_mat[7] = 0.0f;
	m_mat[8] = 0.0f;
}

vec3 etk::Matrix3x3::getColumn(uint32_t _iii) const {
	if (_iii == 0) {
		return vec3(m_mat[0], m_mat[3], m_mat[6]);
	} else if (_iii == 1) {
		return vec3(m_mat[1], m_mat[4], m_mat[7]);
	}
	return vec3(m_mat[2], m_mat[5], m_mat[8]);
}

vec3 etk::Matrix3x3::getRow(uint32_t _iii) const {
	if (_iii == 0) {
		return vec3(m_mat[0], m_mat[1], m_mat[2]);
	} else if (_iii == 1) {
		return vec3(m_mat[3], m_mat[4], m_mat[5]);
	}
	return vec3(m_mat[6], m_mat[7], m_mat[8]);
}

etk::Matrix3x3 etk::Matrix3x3::getTranspose() const {
	return etk::Matrix3x3(m_mat[0], m_mat[3], m_mat[6],
	                    m_mat[1], m_mat[4], m_mat[7],
	                    m_mat[2], m_mat[5], m_mat[8]);
}

void etk::Matrix3x3::transpose() {
	float tmp = m_mat[1];
	m_mat[1] = m_mat[3];
	m_mat[3] = tmp;
	tmp = m_mat[2];
	m_mat[2] = m_mat[6];
	m_mat[6] = tmp;
	tmp = m_mat[5];
	m_mat[5] = m_mat[7];
	m_mat[7] = tmp;
}

float etk::Matrix3x3::determinant() const {
	return   m_mat[0]*(m_mat[4]*m_mat[8]-m_mat[7]*m_mat[5])
	       - m_mat[1]*(m_mat[3]*m_mat[8]-m_mat[6]*m_mat[5])
	       + m_mat[2]*(m_mat[3]*m_mat[7]-m_mat[6]*m_mat[4]);
}

float etk::Matrix3x3::getTrace() const {
    return (m_mat[0] + m_mat[4] + m_mat[8]);
}

void etk::Matrix3x3::setIdentity() {
    m_mat[0] = 1.0; m_mat[1] = 0.0; m_mat[2] = 0.0;
    m_mat[3] = 0.0; m_mat[4] = 1.0; m_mat[5] = 0.0;
    m_mat[6] = 0.0; m_mat[7] = 0.0; m_mat[8] = 1.0;
}

etk::Matrix3x3 etk::Matrix3x3::identity() {
    return etk::Matrix3x3(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
}

etk::Matrix3x3 etk::Matrix3x3::zero() {
    return etk::Matrix3x3(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
}

void etk::Matrix3x3::absolute() {
	m_mat[0] = std::abs(m_mat[0]);
	m_mat[1] = std::abs(m_mat[1]);
	m_mat[2] = std::abs(m_mat[2]);
	m_mat[3] = std::abs(m_mat[3]);
	m_mat[4] = std::abs(m_mat[4]);
	m_mat[5] = std::abs(m_mat[5]);
	m_mat[6] = std::abs(m_mat[6]);
	m_mat[7] = std::abs(m_mat[7]);
	m_mat[8] = std::abs(m_mat[8]);
}

etk::Matrix3x3 etk::Matrix3x3::getAbsolute() const {
	return etk::Matrix3x3(std::abs(m_mat[0]), std::abs(m_mat[1]), std::abs(m_mat[2]),
	                    std::abs(m_mat[3]), std::abs(m_mat[4]), std::abs(m_mat[5]),
	                    std::abs(m_mat[6]), std::abs(m_mat[7]), std::abs(m_mat[8]));
}



const etk::Matrix3x3& etk::Matrix3x3::operator= (const etk::Matrix3x3& _obj ) {
	for(int32_t iii=0; iii<3*3 ; ++iii) {
		m_mat[iii] = _obj.m_mat[iii];
	}
	return *this;
}

bool etk::Matrix3x3::operator== (const etk::Matrix3x3& _obj) const {
	for(int32_t iii=0; iii<3*3 ; ++iii) {
		if(m_mat[iii] != _obj.m_mat[iii]) {
			return false;
		}
	}
	return true;
}

bool etk::Matrix3x3::operator!= (const etk::Matrix3x3& _obj) const {
	for(int32_t iii=0; iii<3*3 ; ++iii) {
		if(m_mat[iii] != _obj.m_mat[iii]) {
			return true;
		}
	}
	return false;
}

const etk::Matrix3x3& etk::Matrix3x3::operator+= (const etk::Matrix3x3& _obj) {
	for(int32_t iii=0; iii<3*3 ; ++iii) {
		m_mat[iii] += _obj.m_mat[iii];
	}
	return *this;
}

etk::Matrix3x3 etk::Matrix3x3::operator+ (const etk::Matrix3x3& _obj) const {
	etk::Matrix3x3 tmpp(*this);
	tmpp += _obj;
	return tmpp;
}

const etk::Matrix3x3& etk::Matrix3x3::operator-= (const etk::Matrix3x3& _obj) {
	for(int32_t iii=0; iii<3*3 ; ++iii) {
		m_mat[iii] -= _obj.m_mat[iii];
	}
	return *this;
}

etk::Matrix3x3 etk::Matrix3x3::operator- (const etk::Matrix3x3& _obj) const {
	etk::Matrix3x3 tmpp(*this);
	tmpp -= _obj;
	return tmpp;
}

const etk::Matrix3x3& etk::Matrix3x3::operator *= (const etk::Matrix3x3& _obj) {
	float a1 = m_mat[0]*_obj.m_mat[0] + m_mat[1]*_obj.m_mat[3] + m_mat[2]*_obj.m_mat[6];
	float b1 = m_mat[3]*_obj.m_mat[0] + m_mat[4]*_obj.m_mat[3] + m_mat[5]*_obj.m_mat[6];
	float c1 = m_mat[6]*_obj.m_mat[0] + m_mat[7]*_obj.m_mat[3] + m_mat[8]*_obj.m_mat[6];
	float a2 = m_mat[0]*_obj.m_mat[1] + m_mat[1]*_obj.m_mat[4] + m_mat[2]*_obj.m_mat[7];
	float b2 = m_mat[3]*_obj.m_mat[1] + m_mat[4]*_obj.m_mat[4] + m_mat[5]*_obj.m_mat[7];
	float c2 = m_mat[6]*_obj.m_mat[1] + m_mat[7]*_obj.m_mat[4] + m_mat[8]*_obj.m_mat[7];
	m_mat[2] = m_mat[0]*_obj.m_mat[2] + m_mat[1]*_obj.m_mat[5] + m_mat[2]*_obj.m_mat[8];
	m_mat[5] = m_mat[3]*_obj.m_mat[2] + m_mat[4]*_obj.m_mat[5] + m_mat[5]*_obj.m_mat[8];
	m_mat[8] = m_mat[6]*_obj.m_mat[2] + m_mat[7]*_obj.m_mat[5] + m_mat[8]*_obj.m_mat[8];
	m_mat[0] = a1;
	m_mat[3] = b1;
	m_mat[6] = c1;
	m_mat[1] = a2;
	m_mat[4] = b2;
	m_mat[7] = c2;
	return *this;
}

etk::Matrix3x3 etk::Matrix3x3::operator * (const etk::Matrix3x3& _obj) const {
	etk::Matrix3x3 tmp(*this);
	tmp *= _obj;
	return tmp;
}

vec3 etk::Matrix3x3::operator * (const vec3& _point) const {
	return vec3(_point.x()*m_mat[0] + _point.y()*m_mat[1] + _point.z()*m_mat[2],
	            _point.x()*m_mat[3] + _point.y()*m_mat[4] + _point.z()*m_mat[5],
	            _point.x()*m_mat[6] + _point.y()*m_mat[7] + _point.z()*m_mat[8]);
}

const etk::Matrix3x3& etk::Matrix3x3::operator *= (float _value) {
	m_mat[0] *= _value;
	m_mat[1] *= _value;
	m_mat[2] *= _value;
	m_mat[3] *= _value;
	m_mat[4] *= _value;
	m_mat[5] *= _value;
	m_mat[6] *= _value;
	m_mat[7] *= _value;
	m_mat[8] *= _value;
	return *this;
}

etk::Matrix3x3 etk::Matrix3x3::operator * (float _value) const {
	etk::Matrix3x3 tmp(*this);
	tmp *= _value;
	return tmp;
}

void etk::Matrix3x3::inverse() {
	*this = getInverse();
}

etk::Matrix3x3 etk::Matrix3x3::getInverse() const {
	float det = determinant();
	//assert(std::abs(det) > MACHINE_EPSILON);
	float invDet = 1.0f / det;
	return etk::Matrix3x3( (m_mat[4]*m_mat[8]-m_mat[7]*m_mat[5]),
	                      -(m_mat[1]*m_mat[8]-m_mat[7]*m_mat[2]),
	                       (m_mat[1]*m_mat[5]-m_mat[2]*m_mat[4]),
	                      -(m_mat[3]*m_mat[8]-m_mat[6]*m_mat[5]),
	                       (m_mat[0]*m_mat[8]-m_mat[6]*m_mat[2]),
	                      -(m_mat[0]*m_mat[5]-m_mat[3]*m_mat[2]),
	                       (m_mat[3]*m_mat[7]-m_mat[6]*m_mat[4]),
	                      -(m_mat[0]*m_mat[7]-m_mat[6]*m_mat[1]),
	                       (m_mat[0]*m_mat[4]-m_mat[1]*m_mat[3]))* invDet;
}

etk::Matrix3x3 etk::Matrix3x3::computeSkewSymmetricMatrixForCrossProduct(const vec3& vector) {
    return etk::Matrix3x3( 0.0f      , -vector.z(),  vector.y(),
                           vector.z(),  0.0f      , -vector.x(),
                          -vector.y(),  vector.x(),  0.0f);
}

etk::Matrix3x3 operator-(const etk::Matrix3x3& _matrix) {
	return etk::Matrix3x3(-_matrix.m_mat[0], -_matrix.m_mat[1], -_matrix.m_mat[2],
	                      -_matrix.m_mat[3], -_matrix.m_mat[4], -_matrix.m_mat[5],
	                      -_matrix.m_mat[6], -_matrix.m_mat[7], -_matrix.m_mat[8]);
}
