/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/types.hpp>
#include <etk/math/Matrix4x4.hpp>
#include <etk/debug.hpp>
#include <cmath>
#include <etk/typeInfo.hpp>

ETK_DECLARE_TYPE(etk::Matrix4x4);

void etk::Matrix4x4::identity() {
	for(int32_t iii=0; iii<4*4 ; iii++) {
		m_mat[iii] = 0;
	}
	m_mat[0] = 1.0;
	m_mat[5] = 1.0;
	m_mat[10] = 1.0;
	m_mat[15] = 1.0;
}

etk::Matrix4x4::Matrix4x4() {
	identity();
}

etk::Matrix4x4::Matrix4x4(const Matrix4x4& _obj) {
	for(int32_t iii=0; iii<4*4 ; iii++) {
		m_mat[iii] = _obj.m_mat[iii];
	}
}

etk::Matrix4x4::Matrix4x4(float _a1, float _b1, float _c1, float _d1,
       float _a2, float _b2, float _c2, float _d2,
       float _a3, float _b3, float _c3, float _d3,
       float _a4, float _b4, float _c4, float _d4) {
	m_mat[0] = _a1;
	m_mat[1] = _b1;
	m_mat[2] = _c1;
	m_mat[3] = _d1;
	m_mat[4] = _a2;
	m_mat[5] = _b2;
	m_mat[6] = _c2;
	m_mat[7] = _d2;
	m_mat[8] = _a3;
	m_mat[9] = _b3;
	m_mat[10] = _c3;
	m_mat[11] = _d3;
	m_mat[12] = _a4;
	m_mat[13] = _b4;
	m_mat[14] = _c4;
	m_mat[15] = _d4;
}

etk::Matrix4x4::Matrix4x4(float* _obj) {
	if (_obj == null) {
		identity();
		return;
	}
	for(int32_t iii=0; iii<4*4 ; ++iii) {
		m_mat[iii] = _obj[iii];
	}
}

const etk::Matrix4x4& etk::Matrix4x4::operator= (const etk::Matrix4x4& _obj ) {
	for(int32_t iii=0; iii<4*4 ; ++iii) {
		m_mat[iii] = _obj.m_mat[iii];
	}
	return *this;
}

bool etk::Matrix4x4::operator== (const etk::Matrix4x4& _obj) const {
	for(int32_t iii=0; iii<4*4 ; ++iii) {
		if(m_mat[iii] != _obj.m_mat[iii]) {
			return false;
		}
	}
	return true;
}

bool etk::Matrix4x4::operator!= (const etk::Matrix4x4& _obj) const {
	for(int32_t iii=0; iii<4*4 ; ++iii) {
		if(m_mat[iii] != _obj.m_mat[iii]) {
			return true;
		}
	}
	return false;
}

const etk::Matrix4x4& etk::Matrix4x4::operator+= (const etk::Matrix4x4& _obj) {
	for(int32_t iii=0; iii<4*4 ; ++iii) {
		m_mat[iii] += _obj.m_mat[iii];
	}
	return *this;
}

etk::Matrix4x4 etk::Matrix4x4::operator+ (const etk::Matrix4x4& _obj) const {
	etk::Matrix4x4 tmpp(*this);
	tmpp += _obj;
	return tmpp;
}

const etk::Matrix4x4& etk::Matrix4x4::operator-= (const etk::Matrix4x4& _obj) {
	for(int32_t iii=0; iii<4*4 ; ++iii) {
		m_mat[iii] -= _obj.m_mat[iii];
	}
	return *this;
}

etk::Matrix4x4 etk::Matrix4x4::operator- (const etk::Matrix4x4& _obj) const {
	etk::Matrix4x4 tmpp(*this);
	tmpp += _obj;
	return tmpp;
}

const etk::Matrix4x4& etk::Matrix4x4::operator*= (const etk::Matrix4x4& _obj) {
	// output Matrix
	float matrixOut[4*4];
	for(int32_t jjj=0; jjj<4 ; jjj++) {
		float* tmpLeft = m_mat + jjj*4;
		for(int32_t iii=0; iii<4 ; iii++) {
			const float* tmpUpper = _obj.m_mat+iii;
			float* tmpLeft2 = tmpLeft;
			float tmpElement = 0;
			for(int32_t kkk=0; kkk<4 ; kkk++) {
				tmpElement += *tmpUpper * *tmpLeft2;
				tmpUpper += 4;
				tmpLeft2++;
			}
			matrixOut[jjj*4+iii] = tmpElement;
		}
	}
	// set it at the output
	for(int32_t iii=0; iii<4*4 ; iii++) {
		m_mat[iii] = matrixOut[iii];
	}
	return *this;
}

etk::Matrix4x4 etk::Matrix4x4::operator* (const etk::Matrix4x4& _obj) const {
	etk::Matrix4x4 tmpp(*this);
	tmpp *= _obj;
	return tmpp;
}

vec3 etk::Matrix4x4::operator*(const vec3& _point) const {
	return vec3( m_mat[0]*_point.x() + m_mat[1]*_point.y() + m_mat[2]*_point.z()  + m_mat[3],
	             m_mat[4]*_point.x() + m_mat[5]*_point.y() + m_mat[6]*_point.z()  + m_mat[7],
	             m_mat[8]*_point.x() + m_mat[9]*_point.y() + m_mat[10]*_point.z() + m_mat[11] );
}

void etk::Matrix4x4::transpose() {
	float tmpVal = m_mat[1];
	m_mat[1] = m_mat[4];
	m_mat[4] = tmpVal;
	
	tmpVal = m_mat[2];
	m_mat[2] = m_mat[8];
	m_mat[8] = tmpVal;
	
	tmpVal = m_mat[6];
	m_mat[6] = m_mat[9];
	m_mat[9] = tmpVal;
	
	tmpVal = m_mat[3];
	m_mat[3] = m_mat[12];
	m_mat[12] = tmpVal;
	
	tmpVal = m_mat[7];
	m_mat[7] = m_mat[13];
	m_mat[13] = tmpVal;
	
	tmpVal = m_mat[11];
	m_mat[11] = m_mat[14];
	m_mat[14] = tmpVal;
}

void etk::Matrix4x4::scale(const vec3& _vect) {
	scale(_vect.x(), _vect.y(), _vect.z());
}

void etk::Matrix4x4::scale(float _sx, float _sy, float _sz) {
	m_mat[0] *= _sx;	m_mat[1] *= _sy;	m_mat[2] *= _sz;
	m_mat[4] *= _sx;	m_mat[5] *= _sy;	m_mat[6] *= _sz;
	m_mat[8] *= _sx;	m_mat[9] *= _sy;	m_mat[10] *= _sz;
}

void etk::Matrix4x4::rotate(const vec3& _vect, float _angleRad) {
	etk::Matrix4x4 tmpMat = etk::matRotate(_vect, _angleRad);
	*this *= tmpMat;
}

void etk::Matrix4x4::translate(const vec3& _vect) {
	etk::Matrix4x4 tmpMat = etk::matTranslate(_vect);
	*this *= tmpMat;
}


etk::Matrix4x4 etk::matFrustum(float _xmin, float _xmax, float _ymin, float _ymax, float _zNear, float _zFar) {
	etk::Matrix4x4 tmp;
	for(int32_t iii=0; iii<4*4 ; iii++) {
		tmp.m_mat[iii] = 0;
	}
	//  0  1  2  3
	//  4  5  6  7
	//  8  9 10 11
	// 12 13 14 15
	tmp.m_mat[0]  = (2.0 * _zNear) / (_xmax - _xmin);
	tmp.m_mat[5]  = (2.0 * _zNear) / (_ymax - _ymin);
	tmp.m_mat[10] = -(_zFar + _zNear) / (_zFar - _zNear);
	tmp.m_mat[2]  = (_xmax + _xmin) / (_xmax - _xmin);
	tmp.m_mat[6]  = (_ymax + _ymin) / (_ymax - _ymin);
	tmp.m_mat[14] = -1.0;
	tmp.m_mat[11] = -(2.0 * _zFar * _zNear) / (_zFar - _zNear);
	return tmp;
}

etk::Matrix4x4 etk::matPerspective(float _fovx, float _aspect, float _zNear, float _zFar) {
	//TK_DEBUG("drax perspective: fovx=" << fovx << "->" << aspect << "  " << zNear << "->" << zFar);
	float xmax = _zNear * tanf(_fovx/2.0);
	float xmin = -xmax;
	
	float ymin = xmin / _aspect;
	float ymax = xmax / _aspect;
	//TK_DEBUG("drax perspective: " << xmin << "->" << xmax << " & " << ymin << "->" << ymax << " " << zNear << "->" << zFar);
	return etk::matFrustum(xmin, xmax, ymin, ymax, _zNear, _zFar);
}

etk::Matrix4x4 etk::matOrtho(float _left, float _right, float _bottom, float _top, float _nearVal, float _farVal) {
	etk::Matrix4x4 tmp;
	for(int32_t iii=0; iii<4*4 ; iii++) {
		tmp.m_mat[iii] = 0;
	}
	tmp.m_mat[0] = 2.0 / (_right - _left);
	tmp.m_mat[5] = 2.0 / (_top - _bottom);
	tmp.m_mat[10] = -2.0 / (_farVal - _nearVal);
	tmp.m_mat[3]  = -1*(_right + _left) / (_right - _left);
	tmp.m_mat[7]  = -1*(_top + _bottom) / (_top - _bottom);
	tmp.m_mat[11] = -1*(_farVal + _nearVal) / (_farVal - _nearVal);
	tmp.m_mat[15] = 1;
	return tmp;
}

etk::Matrix4x4 etk::matTranslate(vec3 _vect) {
	etk::Matrix4x4 tmp;
	// set translation :
	tmp.m_mat[3] = _vect.x();
	tmp.m_mat[7] = _vect.y();
	tmp.m_mat[11] = _vect.z();
	//TK_INFO("Translate :");
	//etk::matrix::Display(tmp);
	return tmp;
}

etk::Matrix4x4 etk::matScale(vec3 _vect) {
	etk::Matrix4x4 tmp;
	tmp.scale(_vect);
	/*
	// set scale :
	tmp.m_mat[0] = vect.x;
	tmp.m_mat[5] = vect.y;
	tmp.m_mat[10] = vect.z;
	*/
	//TK_INFO("Scale :");
	//etk::matrix::Display(tmp);
	return tmp;
}

etk::Matrix4x4 etk::matRotate(vec3 _vect, float _angleRad) {
	etk::Matrix4x4 tmp;
	float cosVal = cos(_angleRad);
	float sinVal = sin(_angleRad);
	float invVal = 1.0-cosVal;
	// set rotation : 
	tmp.m_mat[0]  = _vect.x() * _vect.x() * invVal + cosVal;
	tmp.m_mat[1]  = _vect.x() * _vect.y() * invVal - _vect.z() * sinVal;
	tmp.m_mat[2]  = _vect.x() * _vect.z() * invVal + _vect.y() * sinVal;
	
	tmp.m_mat[4]  = _vect.y() * _vect.x() * invVal + _vect.z() * sinVal;
	tmp.m_mat[5]  = _vect.y() * _vect.y() * invVal + cosVal;
	tmp.m_mat[6]  = _vect.y() * _vect.z() * invVal - _vect.x() * sinVal;
	
	tmp.m_mat[8]  = _vect.z() * _vect.x() * invVal - _vect.y() * sinVal;
	tmp.m_mat[9]  = _vect.z() * _vect.y() * invVal + _vect.x() * sinVal;
	tmp.m_mat[10] = _vect.z() * _vect.z() * invVal + cosVal;
	return tmp;
}

etk::Matrix4x4 etk::matRotate2(vec3 _vect) {
	return matLookAt(_vect, vec3(0,0,0), vec3(0,1,0));
}

etk::Matrix4x4 etk::matLookAt(const vec3& _eye,
                            const vec3& _target,
                            const vec3& _up) {
	etk::Matrix4x4 tmp;
	
	vec3 forward = _eye;
	forward -= _target;
	forward.safeNormalize();
	vec3 xaxis = _target.cross(_up.normalized());
	xaxis.safeNormalize();
	vec3 up2 = xaxis.cross(forward);
	xaxis.safeNormalize();
	
	tmp.m_mat[0] = xaxis.x();
	tmp.m_mat[1] = up2.x();
	tmp.m_mat[2] = forward.x();
	tmp.m_mat[3] = _eye.x();
	
	tmp.m_mat[4] = xaxis.y();
	tmp.m_mat[5] = up2.y();
	tmp.m_mat[6] = forward.y();
	tmp.m_mat[7] = _eye.y();
	
	tmp.m_mat[8] = xaxis.z();
	tmp.m_mat[9] = up2.z();
	tmp.m_mat[10] = forward.z();
	tmp.m_mat[11] = _eye.z();
	
	tmp.m_mat[12] = 0.0f;
	tmp.m_mat[13] = 0.0f;
	tmp.m_mat[14] = 0.0f;
	tmp.m_mat[15] = 1.0f;
	return tmp;
}


float etk::Matrix4x4::coFactor(int32_t _row, int32_t _col) const {
	return (   (   m_mat[((_row+1)&3)*4 + ((_col+1)&3)] * m_mat[((_row+2)&3)*4 + ((_col+2)&3)] * m_mat[((_row+3)&3)*4 + ((_col+3)&3)]
	             + m_mat[((_row+1)&3)*4 + ((_col+2)&3)] * m_mat[((_row+2)&3)*4 + ((_col+3)&3)] * m_mat[((_row+3)&3)*4 + ((_col+1)&3)]
	             + m_mat[((_row+1)&3)*4 + ((_col+3)&3)] * m_mat[((_row+2)&3)*4 + ((_col+1)&3)] * m_mat[((_row+3)&3)*4 + ((_col+2)&3)] )
	         - (   m_mat[((_row+3)&3)*4 + ((_col+1)&3)] * m_mat[((_row+2)&3)*4 + ((_col+2)&3)] * m_mat[((_row+1)&3)*4 + ((_col+3)&3)]
	             + m_mat[((_row+3)&3)*4 + ((_col+2)&3)] * m_mat[((_row+2)&3)*4 + ((_col+3)&3)] * m_mat[((_row+1)&3)*4 + ((_col+1)&3)]
	             + m_mat[((_row+3)&3)*4 + ((_col+3)&3)] * m_mat[((_row+2)&3)*4 + ((_col+1)&3)] * m_mat[((_row+1)&3)*4 + ((_col+2)&3)] )
	       ) * ((_row + _col) & 1 ? -1.0f : +1.0f);
}


float etk::Matrix4x4::determinant() const {
	return m_mat[0] * coFactor(0, 0) +
	       m_mat[1] * coFactor(0, 1) +
	       m_mat[2] * coFactor(0, 2) +
	       m_mat[3] * coFactor(0, 3);
}


etk::Matrix4x4 etk::Matrix4x4::invert() {
	float det = determinant();
	if(etk::abs(det) < (1.0e-7f)) {
		// The matrix is not invertible! Singular case!
		return *this;
	}
	etk::Matrix4x4 temp;
	float iDet = 1.0f / det;
	temp.m_mat[0] = coFactor(0,0) * iDet;
	temp.m_mat[1] = coFactor(0,1) * iDet;
	temp.m_mat[2] = coFactor(0,2) * iDet;
	temp.m_mat[3] = coFactor(0,3) * iDet;
	temp.m_mat[4] = coFactor(1,0) * iDet;
	temp.m_mat[5] = coFactor(1,1) * iDet;
	temp.m_mat[6] = coFactor(1,2) * iDet;
	temp.m_mat[7] = coFactor(1,3) * iDet;
	temp.m_mat[8] = coFactor(2,0) * iDet;
	temp.m_mat[9] = coFactor(2,1) * iDet;
	temp.m_mat[10] = coFactor(2,2) * iDet;
	temp.m_mat[11] = coFactor(2,3) * iDet;
	temp.m_mat[12] = coFactor(3,0) * iDet;
	temp.m_mat[13] = coFactor(3,1) * iDet;
	temp.m_mat[14] = coFactor(3,2) * iDet;
	temp.m_mat[15] = coFactor(3,3) * iDet;
	return temp;
}


etk::Stream& etk::operator <<(etk::Stream& _os, const etk::Matrix4x4& _obj) {
	_os << "matrix4 : (";
	for (int32_t iii=0; iii<16; iii++) {
		_os << _obj.m_mat[iii];
		_os << ",";
	}
	return _os;
}