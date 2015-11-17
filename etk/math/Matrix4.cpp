/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <etk/types.h>
#include <etk/math/Matrix4.h>
#include <etk/debug.h>
#include <math.h>

#if 1

void etk::Matrix4::identity() {
	for(int32_t iii=0; iii<4*4 ; iii++) {
		m_mat[iii] = 0;
	}
	m_mat[0] = 1.0;
	m_mat[5] = 1.0;
	m_mat[10] = 1.0;
	m_mat[15] = 1.0;
}

etk::Matrix4::Matrix4() {
	identity();
}

etk::Matrix4::Matrix4(const Matrix4& _obj) {
	for(int32_t iii=0; iii<4*4 ; iii++) {
		m_mat[iii] = _obj.m_mat[iii];
	}
}

etk::Matrix4::Matrix4(float _a1, float _b1, float _c1, float _d1,
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

etk::Matrix4::Matrix4(float* _obj) {
	if (_obj == nullptr) {
		identity();
		return;
	}
	for(int32_t iii=0; iii<4*4 ; ++iii) {
		m_mat[iii] = _obj[iii];
	}
}

etk::Matrix4::~Matrix4() {
	
}

const etk::Matrix4& etk::Matrix4::operator= (const etk::Matrix4& _obj ) {
	for(int32_t iii=0; iii<4*4 ; ++iii) {
		m_mat[iii] = _obj.m_mat[iii];
	}
	return *this;
}

bool etk::Matrix4::operator== (const etk::Matrix4& _obj) const {
	for(int32_t iii=0; iii<4*4 ; ++iii) {
		if(m_mat[iii] != _obj.m_mat[iii]) {
			return false;
		}
	}
	return true;
}

bool etk::Matrix4::operator!= (const etk::Matrix4& _obj) const {
	for(int32_t iii=0; iii<4*4 ; ++iii) {
		if(m_mat[iii] != _obj.m_mat[iii]) {
			return true;
		}
	}
	return false;
}

const etk::Matrix4& etk::Matrix4::operator+= (const etk::Matrix4& _obj) {
	for(int32_t iii=0; iii<4*4 ; ++iii) {
		m_mat[iii] += _obj.m_mat[iii];
	}
	return *this;
}

etk::Matrix4 etk::Matrix4::operator+ (const etk::Matrix4& _obj) const {
	etk::Matrix4 tmpp(*this);
	tmpp += _obj;
	return tmpp;
}

const etk::Matrix4& etk::Matrix4::operator-= (const etk::Matrix4& _obj) {
	for(int32_t iii=0; iii<4*4 ; ++iii) {
		m_mat[iii] -= _obj.m_mat[iii];
	}
	return *this;
}

etk::Matrix4 etk::Matrix4::operator- (const etk::Matrix4& _obj) const {
	etk::Matrix4 tmpp(*this);
	tmpp += _obj;
	return tmpp;
}

const etk::Matrix4& etk::Matrix4::operator*= (const etk::Matrix4& _obj) {
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

etk::Matrix4 etk::Matrix4::operator* (const etk::Matrix4& _obj) const {
	etk::Matrix4 tmpp(*this);
	tmpp *= _obj;
	return tmpp;
}

vec3 etk::Matrix4::operator*(const vec3& _point) const {
	return vec3( m_mat[0]*_point.x() + m_mat[1]*_point.y() + m_mat[2]*_point.z()  + m_mat[3],
	             m_mat[4]*_point.x() + m_mat[5]*_point.y() + m_mat[6]*_point.z()  + m_mat[7],
	             m_mat[8]*_point.x() + m_mat[9]*_point.y() + m_mat[10]*_point.z() + m_mat[11] );
}

void etk::Matrix4::transpose() {
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

void etk::Matrix4::scale(const vec3& _vect) {
	scale(_vect.x(), _vect.y(), _vect.z());
}

void etk::Matrix4::scale(float _sx, float _sy, float _sz) {
	m_mat[0] *= _sx;	m_mat[1] *= _sy;	m_mat[2] *= _sz;
	m_mat[4] *= _sx;	m_mat[5] *= _sy;	m_mat[6] *= _sz;
	m_mat[8] *= _sx;	m_mat[9] *= _sy;	m_mat[10] *= _sz;
}

void etk::Matrix4::rotate(const vec3& vect, float angleRad)
{
	etk::Matrix4 tmpMat = etk::matRotate(vect, angleRad);
	*this *= tmpMat;
}

void etk::Matrix4::translate(const vec3& vect)
{
	etk::Matrix4 tmpMat = etk::matTranslate(vect);
	*this *= tmpMat;
}


etk::Matrix4 etk::matFrustum(float xmin, float xmax, float ymin, float ymax, float zNear, float zFar)
{
	etk::Matrix4 tmp;
	for(int32_t iii=0; iii<4*4 ; iii++) {
		tmp.m_mat[iii] = 0;
	}
	
	//  0  1  2  3
	//  4  5  6  7
	//  8  9 10 11
	// 12 13 14 15
	
	tmp.m_mat[0]  = (2.0 * zNear) / (xmax - xmin);
	tmp.m_mat[5]  = (2.0 * zNear) / (ymax - ymin);
	tmp.m_mat[10] = -(zFar + zNear) / (zFar - zNear);
	tmp.m_mat[2] = (xmax + xmin) / (xmax - xmin);
	tmp.m_mat[6] = (ymax + ymin) / (ymax - ymin);
	tmp.m_mat[14] = -1.0;
	tmp.m_mat[11] = -(2.0 * zFar * zNear) / (zFar - zNear);
	
	return tmp;
}

etk::Matrix4 etk::matPerspective(float fovx, float aspect, float zNear, float zFar)
{
	//TK_DEBUG("drax perspective: fovx=" << fovx << "->" << aspect << "  " << zNear << "->" << zFar);
	float xmax = zNear * tanf(fovx/2.0);
	float xmin = -xmax;
	
	float ymin = xmin / aspect;
	float ymax = xmax / aspect;
	//TK_DEBUG("drax perspective: " << xmin << "->" << xmax << " & " << ymin << "->" << ymax << " " << zNear << "->" << zFar);
	return etk::matFrustum(xmin, xmax, ymin, ymax, zNear, zFar);
}

etk::Matrix4 etk::matOrtho(float left, float right, float bottom, float top, float nearVal, float farVal)
{
	etk::Matrix4 tmp;
	for(int32_t iii=0; iii<4*4 ; iii++) {
		tmp.m_mat[iii] = 0;
	}
	tmp.m_mat[0] = 2.0 / (right - left);
	tmp.m_mat[5] = 2.0 / (top - bottom);
	tmp.m_mat[10] = -2.0 / (farVal - nearVal);
	tmp.m_mat[3]  = -1*(right + left) / (right - left);
	tmp.m_mat[7]  = -1*(top + bottom) / (top - bottom);
	tmp.m_mat[11] = -1*(farVal + nearVal) / (farVal - nearVal);
	tmp.m_mat[15] = 1;
	return tmp;
}

etk::Matrix4 etk::matTranslate(vec3 vect)
{
	etk::Matrix4 tmp;
	// set translation :
	tmp.m_mat[3] = vect.x();
	tmp.m_mat[7] = vect.y();
	tmp.m_mat[11] = vect.z();
	//TK_INFO("Translate :");
	//etk::matrix::Display(tmp);
	return tmp;
}

etk::Matrix4 etk::matScale(vec3 vect)
{
	etk::Matrix4 tmp;
	tmp.scale(vect);
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

etk::Matrix4 etk::matRotate(vec3 vect, float angleRad)
{
	etk::Matrix4 tmp;
	float cosVal = cos(angleRad);
	float sinVal = sin(angleRad);
	float invVal = 1.0-cosVal;
	// set rotation : 
	tmp.m_mat[0]  = vect.x() * vect.x() * invVal + cosVal;
	tmp.m_mat[1]  = vect.x() * vect.y() * invVal - vect.z() * sinVal;
	tmp.m_mat[2]  = vect.x() * vect.z() * invVal + vect.y() * sinVal;
	
	tmp.m_mat[4]  = vect.y() * vect.x() * invVal + vect.z() * sinVal;
	tmp.m_mat[5]  = vect.y() * vect.y() * invVal + cosVal;
	tmp.m_mat[6]  = vect.y() * vect.z() * invVal - vect.x() * sinVal;
	
	tmp.m_mat[8]  = vect.z() * vect.x() * invVal - vect.y() * sinVal;
	tmp.m_mat[9]  = vect.z() * vect.y() * invVal + vect.x() * sinVal;
	tmp.m_mat[10] = vect.z() * vect.z() * invVal + cosVal;
	return tmp;
}

etk::Matrix4 etk::matRotate2(vec3 vect)
{
	return matLookAt(vect, vec3(0,0,0), vec3(0,1,0));
}

etk::Matrix4 etk::matLookAt(const vec3& _eye,
                            const vec3& _target,
                            const vec3& _up)
{
	etk::Matrix4 tmp;
	
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


float etk::Matrix4::coFactor(int32_t row, int32_t col) const
{
	return (   (   m_mat[((row+1)&3)*4 + ((col+1)&3)] * m_mat[((row+2)&3)*4 + ((col+2)&3)] * m_mat[((row+3)&3)*4 + ((col+3)&3)]
	             + m_mat[((row+1)&3)*4 + ((col+2)&3)] * m_mat[((row+2)&3)*4 + ((col+3)&3)] * m_mat[((row+3)&3)*4 + ((col+1)&3)]
	             + m_mat[((row+1)&3)*4 + ((col+3)&3)] * m_mat[((row+2)&3)*4 + ((col+1)&3)] * m_mat[((row+3)&3)*4 + ((col+2)&3)] )
	         - (   m_mat[((row+3)&3)*4 + ((col+1)&3)] * m_mat[((row+2)&3)*4 + ((col+2)&3)] * m_mat[((row+1)&3)*4 + ((col+3)&3)]
	             + m_mat[((row+3)&3)*4 + ((col+2)&3)] * m_mat[((row+2)&3)*4 + ((col+3)&3)] * m_mat[((row+1)&3)*4 + ((col+1)&3)]
	             + m_mat[((row+3)&3)*4 + ((col+3)&3)] * m_mat[((row+2)&3)*4 + ((col+1)&3)] * m_mat[((row+1)&3)*4 + ((col+2)&3)] )
	       ) * ((row + col) & 1 ? -1.0f : +1.0f);
}


float etk::Matrix4::determinant() const
{
	return m_mat[0] * coFactor(0, 0) +
	       m_mat[1] * coFactor(0, 1) +
	       m_mat[2] * coFactor(0, 2) +
	       m_mat[3] * coFactor(0, 3);
}


etk::Matrix4 etk::Matrix4::invert()
{
	float det = determinant();
	if(fabsf(det) < (1.0e-7f)) {
		// The matrix is not invertible! Singular case!
		return *this;
	}
	etk::Matrix4 temp;
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


std::ostream& etk::operator <<(std::ostream& _os, const etk::Matrix4& _obj) {
	_os << "matrix4 : (";
	for (int32_t iii=0; iii<16; iii++) {
		_os << _obj.m_mat[iii];
		_os << ",";
	}
	return _os;
}
#else

std::ostream& operator <<(std::ostream& _os, const mat4& _obj) {
	_os << "matrix4 : ({";
	for (int32_t iii=0; iii<4; iii++) {
		if (iii!= 0) {
			_os << "},{";
		}
		for (int32_t jjj=0; jjj<4; jjj++) {
			if (jjj!= 0) {
				_os << ",";
			}
			_os << _obj.getElem(jjj,iii);
		}
	}
	_os << "})";
	return _os;
}


mat4 etk::matTranslate(const vec3& _vect) {
	mat4 tmp;
	tmp.translation(_vect);
	return tmp;
}

mat4 etk::matScale(const vec3& _vect) {
	mat4 tmp;
	tmp.scale(_vect);
	return tmp;
}

mat4 etk::matRotate(const vec3& _vect, float _angleRad) {
	mat4 tmp;
	tmp.rotation(_angleRad, _vect);
	return tmp;
}

#endif

