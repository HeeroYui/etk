/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/math/Matrix2x2.hpp>

etk::Stream& etk::operator <<(etk::Stream& _os, const etk::Matrix2x2& _obj) {
	_os << "{";
	_os << _obj.m_mat[0] << ",";
	_os << _obj.m_mat[1] << ";";
	_os << _obj.m_mat[2] << ",";
	_os << _obj.m_mat[3] << "}";
	return _os;
}

etk::Matrix2x2::Matrix2x2() {
	m_mat[0] = 0.0f;
	m_mat[1] = 0.0f;
	m_mat[2] = 0.0f;
	m_mat[3] = 0.0f;
}

etk::Matrix2x2::Matrix2x2(float _value) {
	m_mat[0] = _value;
	m_mat[1] = _value;
	m_mat[2] = _value;
	m_mat[3] = _value;
}

etk::Matrix2x2::Matrix2x2(float _a1, float _a2,float _b1, float _b2) {
	m_mat[0] = _a1;
	m_mat[1] = _a2;
	m_mat[2] = _b1;
	m_mat[3] = _b2;
}

etk::Matrix2x2::Matrix2x2(const Matrix2x2& _obj) {
	m_mat[0] = _obj.m_mat[0];
	m_mat[1] = _obj.m_mat[1];
	m_mat[2] = _obj.m_mat[2];
	m_mat[3] = _obj.m_mat[3];
}

void etk::Matrix2x2::setValue(float _a1, float _a2,float _b1, float _b2) {
	m_mat[0] = _a1;
	m_mat[1] = _a2;
	m_mat[2] = _b1;
	m_mat[3] = _b2;
}

void etk::Matrix2x2::setZero() {
	m_mat[0] = 0;
	m_mat[1] = 0;
	m_mat[2] = 0;
	m_mat[3] = 0;
}

vec2 etk::Matrix2x2::getColumn(uint32_t _iii) const {
	if (_iii == 0) {
		return vec2(m_mat[0], m_mat[2]);
	}
	return vec2(m_mat[1], m_mat[3]);
}

vec2 etk::Matrix2x2::getRow(uint32_t _iii) const {
	if (_iii == 0) {
		return vec2(m_mat[0], m_mat[1]);
	}
	return vec2(m_mat[2], m_mat[3]);
}

const etk::Matrix2x2& etk::Matrix2x2::operator= (const etk::Matrix2x2& _obj ) {
	for(int32_t iii=0; iii<2*2 ; ++iii) {
		m_mat[iii] = _obj.m_mat[iii];
	}
	return *this;
}

bool etk::Matrix2x2::operator== (const etk::Matrix2x2& _obj) const {
	for(int32_t iii=0; iii<2*2 ; ++iii) {
		if(m_mat[iii] != _obj.m_mat[iii]) {
			return false;
		}
	}
	return true;
}

bool etk::Matrix2x2::operator!= (const etk::Matrix2x2& _obj) const {
	for(int32_t iii=0; iii<2*2 ; ++iii) {
		if(m_mat[iii] != _obj.m_mat[iii]) {
			return true;
		}
	}
	return false;
}

const etk::Matrix2x2& etk::Matrix2x2::operator+= (const etk::Matrix2x2& _obj) {
	for(int32_t iii=0; iii<2*2 ; ++iii) {
		m_mat[iii] += _obj.m_mat[iii];
	}
	return *this;
}

etk::Matrix2x2 etk::Matrix2x2::operator+ (const etk::Matrix2x2& _obj) const {
	etk::Matrix2x2 tmpp(*this);
	tmpp += _obj;
	return tmpp;
}

const etk::Matrix2x2& etk::Matrix2x2::operator-= (const etk::Matrix2x2& _obj) {
	for(int32_t iii=0; iii<2*2 ; ++iii) {
		m_mat[iii] -= _obj.m_mat[iii];
	}
	return *this;
}

etk::Matrix2x2 etk::Matrix2x2::operator- (const etk::Matrix2x2& _obj) const {
	etk::Matrix2x2 tmpp(*this);
	tmpp -= _obj;
	return tmpp;
}


const etk::Matrix2x2& etk::Matrix2x2::operator *= (const etk::Matrix2x2& _obj) {
	float t0 = m_mat[0] * _obj.m_mat[0] + m_mat[1] * _obj.m_mat[2];
	float t2 = m_mat[2] * _obj.m_mat[0] + m_mat[3] * _obj.m_mat[2];
	m_mat[1] = m_mat[0] * _obj.m_mat[1] + m_mat[1] * _obj.m_mat[3];
	m_mat[3] = m_mat[2] * _obj.m_mat[1] + m_mat[3] * _obj.m_mat[3];
	m_mat[0] = t0;
	m_mat[2] = t2;
	return *this;
}

etk::Matrix2x2 etk::Matrix2x2::operator * (const etk::Matrix2x2& _obj) const {
	etk::Matrix2x2 tmp(*this);
	tmp *= _obj;
	return tmp;
}

vec2 etk::Matrix2x2::operator * (const vec2& _point) const {
	return vec2(_point.x()*m_mat[0] + _point.y()*m_mat[1],
	            _point.x()*m_mat[2] + _point.y()*m_mat[3]);
}

const etk::Matrix2x2& etk::Matrix2x2::operator *= (float _value) {
	m_mat[0] *= _value;
	m_mat[1] *= _value;
	m_mat[2] *= _value;
	m_mat[3] *= _value;
	return *this;
}

etk::Matrix2x2 etk::Matrix2x2::operator * (float _value) const {
	etk::Matrix2x2 tmp(*this);
	tmp *= _value;
	return tmp;
}

etk::Matrix2x2 etk::Matrix2x2::getTranspose() const {
	return Matrix2x2(m_mat[0], m_mat[2],
	               m_mat[1], m_mat[3]);
}
void etk::Matrix2x2::transpose() {
	float tmp = m_mat[2];
	m_mat[2] = m_mat[1];
	m_mat[1] = tmp;
}

float etk::Matrix2x2::determinant() const {
	return m_mat[0] * m_mat[3] - m_mat[2] * m_mat[1];
}

float etk::Matrix2x2::getTrace() const {
	return m_mat[0] + m_mat[3];
}

void etk::Matrix2x2::setIdentity() {
	m_mat[0] = 1.0f;
	m_mat[1] = 0.0f;
	m_mat[2] = 0.0f;
	m_mat[3] = 1.0f;
}

etk::Matrix2x2 etk::Matrix2x2::identity() {
	return etk::Matrix2x2(1.0f, 0.0f, 0.0f, 1.0f);
}

etk::Matrix2x2 etk::Matrix2x2::zero() {
	return etk::Matrix2x2(0.0f, 0.0f, 0.0f, 0.0f);
}

etk::Matrix2x2 etk::Matrix2x2::getAbsolute() const {
	return Matrix2x2(etk::abs(m_mat[0]), etk::abs(m_mat[1]),
	               etk::abs(m_mat[2]), etk::abs(m_mat[3]));
}
void etk::Matrix2x2::absolute() {
	m_mat[0] = etk::abs(m_mat[0]);
	m_mat[1] = etk::abs(m_mat[1]);
	m_mat[2] = etk::abs(m_mat[2]);
	m_mat[3] = etk::abs(m_mat[3]);
}

void etk::Matrix2x2::inverse() {
	*this = getInverse();
}

etk::Matrix2x2 etk::Matrix2x2::getInverse() const {
	float det = determinant();
	//assert(etk::abs(det) > MACHINE_EPSILON);
	float invDet = 1.0f / det;
	return etk::Matrix2x2(m_mat[3], -m_mat[1], -m_mat[2], m_mat[0]) * invDet;
}



etk::Matrix2x2 etk::mat2x2Rotate(float _angleRad) {
	return Matrix2x2(cos(_angleRad), sin(_angleRad), -sin(_angleRad), cos(_angleRad));
}

etk::Matrix2x2 etk::mat2x2Scale(const vec2& _scale) {
	return Matrix2x2(_scale.x(), 0.0, 0.0, _scale.y());
}

etk::Matrix2x2 etk::mat2x2Scale(float _scale) {
	return Matrix2x2(_scale, 0.0, 0.0, _scale);
}

etk::Matrix2x2 etk::mat2x2Skew(const vec2& _skew) {
	return Matrix2x2(1.0, tan(_skew.y()), tan(_skew.x()), 1.0);
}

etk::Matrix2x2 operator-(const etk::Matrix2x2& _matrix) {
	return etk::Matrix2x2(-_matrix.m_mat[0], -_matrix.m_mat[1], -_matrix.m_mat[2], -_matrix.m_mat[3]);
}