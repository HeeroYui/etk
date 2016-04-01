/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <etk/math/Matrix2.h>

std::ostream& etk::operator <<(std::ostream& _os, const etk::Matrix2& _obj) {
	_os << "{";
	_os << _obj.m_mat[0] << ",";
	_os << _obj.m_mat[4] << ",";
	_os << _obj.m_mat[1] << ",";
	_os << _obj.m_mat[3] << ",";
	_os << _obj.m_mat[2] << ",";
	_os << _obj.m_mat[5] << "}";
	return _os;
}

void etk::Matrix2::identity() {
	m_mat[0] = 1.0;
	m_mat[1] = 0.0;
	m_mat[2] = 0.0;
	m_mat[3] = 1.0;
	m_mat[4] = 0.0;
	m_mat[5] = 0.0;
}

etk::Matrix2::Matrix2() {
	// TODO: Remove this ...
	identity();
}
etk::Matrix2::Matrix2(const etk::Matrix2& _obj) {
	for(int32_t iii=0; iii<2*3 ; iii++) {
		m_mat[iii] = _obj.m_mat[iii];
	}
}

etk::Matrix2::Matrix2(float _sx,
                      float _shy,
                      float _shx,
                      float _sy,
                      float _tx,
                      float _ty) {
	m_mat[0] = _sx;
	m_mat[4] = _shy;
	m_mat[1] = _shx;
	m_mat[3] = _sy;
	m_mat[2] = _tx;
	m_mat[5] = _ty;
}

etk::Matrix2::Matrix2(const float* _values) {
	if (_values == nullptr) {
		identity();
		return;
	}
	m_mat[0] = _values[0];
	m_mat[4] = _values[1];
	m_mat[1] = _values[2];
	m_mat[3] = _values[3];
	m_mat[2] = _values[4];
	m_mat[5] = _values[5];
}

etk::Matrix2::Matrix2(const double* _values) {
	if (_values == nullptr) {
		identity();
		return;
	}
	m_mat[0] = _values[0];
	m_mat[4] = _values[1];
	m_mat[1] = _values[2];
	m_mat[3] = _values[3];
	m_mat[2] = _values[4];
	m_mat[5] = _values[5];
}

etk::Matrix2::~Matrix2() {
	
}

const etk::Matrix2& etk::Matrix2::operator= (const etk::Matrix2& _obj ) {
	for(int32_t iii=0; iii<2*3 ; ++iii) {
		m_mat[iii] = _obj.m_mat[iii];
	}
	return *this;
}

bool etk::Matrix2::operator== (const etk::Matrix2& _obj) const {
	for(int32_t iii=0; iii<2*3 ; ++iii) {
		if(m_mat[iii] != _obj.m_mat[iii]) {
			return false;
		}
	}
	return true;
}

bool etk::Matrix2::operator!= (const etk::Matrix2& _obj) const {
	for(int32_t iii=0; iii<2*3 ; ++iii) {
		if(m_mat[iii] != _obj.m_mat[iii]) {
			return true;
		}
	}
	return false;
}

const etk::Matrix2& etk::Matrix2::operator+= (const etk::Matrix2& _obj) {
	for(int32_t iii=0; iii<2*3 ; ++iii) {
		m_mat[iii] += _obj.m_mat[iii];
	}
	return *this;
}

etk::Matrix2 etk::Matrix2::operator+ (const etk::Matrix2& _obj) const {
	etk::Matrix2 tmpp(*this);
	tmpp += _obj;
	return tmpp;
}

const etk::Matrix2& etk::Matrix2::operator-= (const etk::Matrix2& _obj) {
	for(int32_t iii=0; iii<2*3 ; ++iii) {
		m_mat[iii] -= _obj.m_mat[iii];
	}
	return *this;
}

etk::Matrix2 etk::Matrix2::operator- (const etk::Matrix2& _obj) const {
	etk::Matrix2 tmpp(*this);
	tmpp += _obj;
	return tmpp;
}

const etk::Matrix2& etk::Matrix2::operator *= (const etk::Matrix2& _obj) {
	float t0 = m_mat[0]  * _obj.m_mat[0] + m_mat[4] * _obj.m_mat[1];
	float t2 = m_mat[1] * _obj.m_mat[0] + m_mat[3]  * _obj.m_mat[1];
	float t4 = m_mat[2]  * _obj.m_mat[0] + m_mat[5]  * _obj.m_mat[1] + _obj.m_mat[2];
	m_mat[4] = m_mat[0]  * _obj.m_mat[4] + m_mat[4] * _obj.m_mat[3];
	m_mat[3] = m_mat[1] * _obj.m_mat[4] + m_mat[3]  * _obj.m_mat[3];
	m_mat[5] = m_mat[2]  * _obj.m_mat[4] + m_mat[5]  * _obj.m_mat[3] + _obj.m_mat[5];
	m_mat[0] = t0;
	m_mat[1] = t2;
	m_mat[2] = t4;
	return *this;
}

etk::Matrix2 etk::Matrix2::operator * (const etk::Matrix2& _obj) {
	etk::Matrix2 tmp(*this);
	tmp *= _obj;
	return tmp;
}

vec2 etk::Matrix2::operator * (const vec2& _obj) const {
	return vec2(_obj.x()*m_mat[0] + _obj.y()*m_mat[1] + m_mat[2],
	            _obj.x()*m_mat[4] + _obj.y()*m_mat[3] + m_mat[5]);
}

vec2 etk::Matrix2::applyScaleRotation(const vec2& _obj) const {
	return vec2(_obj.x()*m_mat[0] + _obj.y()*m_mat[1],
	            _obj.x()*m_mat[4] + _obj.y()*m_mat[3]);
}

etk::Matrix2 etk::Matrix2::operator ~ () const {
	etk::Matrix2 tmp(*this);
	tmp.invert();
	return tmp;
}

void etk::Matrix2::flipX() {
	m_mat[0] = -m_mat[0];
	m_mat[4] = -m_mat[4];
	m_mat[2] = -m_mat[2];
}

void etk::Matrix2::flipY() {
	m_mat[1] = -m_mat[1];
	m_mat[3] = -m_mat[3];
	m_mat[5] = -m_mat[5];
}

void etk::Matrix2::scale(const vec2& _vect) {
	m_mat[0] *= _vect.x();
	m_mat[1] *= _vect.x();
	m_mat[2] *= _vect.x();
	m_mat[4] *= _vect.y();
	m_mat[3] *= _vect.y();
	m_mat[5] *= _vect.y();
}

void etk::Matrix2::scale(float _value) {
	m_mat[0] *= _value;
	m_mat[1] *= _value;
	m_mat[2] *= _value;
	m_mat[4] *= _value;
	m_mat[3] *= _value;
	m_mat[5] *= _value;
}

void etk::Matrix2::rotate(float _angleRad) {
	float ca = cos(_angleRad); 
	float sa = sin(_angleRad);
	float t0 = m_mat[0]  * ca - m_mat[4] * sa;
	float t2 = m_mat[1] * ca - m_mat[3] * sa;
	float t4 = m_mat[2]  * ca - m_mat[5] * sa;
	m_mat[4] = m_mat[0]  * sa + m_mat[4] * ca;
	m_mat[3]  = m_mat[1] * sa + m_mat[3] * ca; 
	m_mat[5]  = m_mat[2]  * sa + m_mat[5] * ca;
	m_mat[0]  = t0;
	m_mat[1] = t2;
	m_mat[2]  = t4;
}

void etk::Matrix2::translate(const vec2& _vect) {
	m_mat[2] += _vect.x();
	m_mat[5] += _vect.y();
}

float etk::Matrix2::determinant() const {
	return m_mat[0] * m_mat[3] - m_mat[4] * m_mat[1];
}

void etk::Matrix2::invert() {
	float det = 1.0f / determinant();
	float t0 = m_mat[3] * det;
	m_mat[3] = m_mat[0] * det;
	m_mat[4] = -m_mat[4] * det;
	m_mat[1] = -m_mat[1] * det;
	float t4 = -m_mat[2] * t0 - m_mat[5] * m_mat[1];
	m_mat[5] = -m_mat[2] * m_mat[4] - m_mat[5] * m_mat[3];
	m_mat[0] = t0;
	m_mat[2] = t4;
}

etk::Matrix2 etk::mat2Rotate(float _angleRad) {
	return Matrix2(cos(_angleRad), sin(_angleRad), -sin(_angleRad), cos(_angleRad), 0.0, 0.0);
};

etk::Matrix2 etk::mat2Scale(const vec2& _scale) {
	return Matrix2(_scale.x(), 0.0, 0.0, _scale.y(), 0.0, 0.0);
};

etk::Matrix2 etk::mat2Scale(float _scale) {
	return Matrix2(_scale, 0.0, 0.0, _scale, 0.0, 0.0);
};

etk::Matrix2 etk::mat2Translate(const vec2& _translate) {
	return Matrix2(1.0, 0.0, 0.0, 1.0, _translate.x(), _translate.y());
};

etk::Matrix2 etk::mat2Skew(const vec2& _skew) {
	return Matrix2(1.0, tan(_skew.y()), tan(_skew.x()), 1.0, 0.0, 0.0);
};
