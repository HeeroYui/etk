/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/types.h>
#include <etk/math/Matrix4.h>
#include <etk/DebugInternal.h>
#include <math.h>


void etk::Matrix4::Rotate(const vec3& vect, float angleRad)
{
	etk::Matrix4 tmpMat = etk::matRotate(vect, angleRad);
	*this *= tmpMat;
}

void etk::Matrix4::Translate(const vec3& vect)
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
	tmp.Scale(vect);
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

etk::Matrix4 etk::matLookAt(vec3 eye,
                            vec3 center,
                            vec3 up)
{
	etk::Matrix4 tmp;
	
	vec3 forward = center - eye;
	forward.normalize();
	vec3 side = forward.cross(up);
	side.normalize();
	
	vec3 plane_up = side.cross(forward);
	plane_up.normalize();
	
	tmp.m_mat[0] = side.x();
	tmp.m_mat[1] = plane_up.x();
	tmp.m_mat[2] = -forward.x();
	tmp.m_mat[3] = 0.0f;
	
	tmp.m_mat[4] = side.y();
	tmp.m_mat[5] = plane_up.y();
	tmp.m_mat[6] = -forward.y();
	tmp.m_mat[7] = 0.0f;
	
	tmp.m_mat[8] = side.z();
	tmp.m_mat[9] = plane_up.z();
	tmp.m_mat[10] = -forward.z();
	tmp.m_mat[11] = 0.0f;
	
	tmp.m_mat[12] = 0.0f;
	tmp.m_mat[13] = 0.0f;
	tmp.m_mat[14] = 0.0f;
	tmp.m_mat[15] = 1.0f;
	return tmp;
}



float etk::Matrix4::CoFactor(int32_t row, int32_t col) const
{
	return (   (   m_mat[((row+1)&3)*4 + ((col+1)&3)] * m_mat[((row+2)&3)*4 + ((col+2)&3)] * m_mat[((row+3)&3)*4 + ((col+3)&3)]
	             + m_mat[((row+1)&3)*4 + ((col+2)&3)] * m_mat[((row+2)&3)*4 + ((col+3)&3)] * m_mat[((row+3)&3)*4 + ((col+1)&3)]
	             + m_mat[((row+1)&3)*4 + ((col+3)&3)] * m_mat[((row+2)&3)*4 + ((col+1)&3)] * m_mat[((row+3)&3)*4 + ((col+2)&3)] )
	         - (   m_mat[((row+3)&3)*4 + ((col+1)&3)] * m_mat[((row+2)&3)*4 + ((col+2)&3)] * m_mat[((row+1)&3)*4 + ((col+3)&3)]
	             + m_mat[((row+3)&3)*4 + ((col+2)&3)] * m_mat[((row+2)&3)*4 + ((col+3)&3)] * m_mat[((row+1)&3)*4 + ((col+1)&3)]
	             + m_mat[((row+3)&3)*4 + ((col+3)&3)] * m_mat[((row+2)&3)*4 + ((col+1)&3)] * m_mat[((row+1)&3)*4 + ((col+2)&3)] )
	       ) * ((row + col) & 1 ? -1.0f : +1.0f);
}


float etk::Matrix4::Determinant() const
{
	return	m_mat[0] * CoFactor(0, 0) +
			m_mat[1] * CoFactor(0, 1) +
			m_mat[2] * CoFactor(0, 2) +
			m_mat[3] * CoFactor(0, 3);
}


etk::Matrix4 etk::Matrix4::Invert()
{
	float det = Determinant();
	if(fabsf(det) < (1.0e-7f)) {
		// The matrix is not invertible! Singular case!
		return *this;
	}
	etk::Matrix4 temp;
	float iDet = 1.0f / det;
	temp.m_mat[0] = CoFactor(0,0) * iDet;
	temp.m_mat[1] = CoFactor(0,1) * iDet;
	temp.m_mat[2] = CoFactor(0,2) * iDet;
	temp.m_mat[3] = CoFactor(0,3) * iDet;
	temp.m_mat[4] = CoFactor(1,0) * iDet;
	temp.m_mat[5] = CoFactor(1,1) * iDet;
	temp.m_mat[6] = CoFactor(1,2) * iDet;
	temp.m_mat[7] = CoFactor(1,3) * iDet;
	temp.m_mat[8] = CoFactor(2,0) * iDet;
	temp.m_mat[9] = CoFactor(2,1) * iDet;
	temp.m_mat[10] = CoFactor(2,2) * iDet;
	temp.m_mat[11] = CoFactor(2,3) * iDet;
	temp.m_mat[12] = CoFactor(3,0) * iDet;
	temp.m_mat[13] = CoFactor(3,1) * iDet;
	temp.m_mat[14] = CoFactor(3,2) * iDet;
	temp.m_mat[15] = CoFactor(3,3) * iDet;
	return temp;
}


etk::CCout& etk::operator <<(etk::CCout &os, const etk::Matrix4 obj)
{
	os << "matrix4 : (";
	for (int32_t iii=0; iii<16; iii++) {
		os << obj.m_mat[iii];
		os << ",";
	}
	return os;
}
