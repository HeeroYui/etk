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

etk::Matrix4 etk::Matrix4::Perspective(float left, float right, float bottom, float top, float nearVal, float farVal)
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
	//TK_INFO("Perspective :");
	//etk::matrix::Display(tmp);
	return tmp;
}

etk::Matrix4 etk::Matrix4::Translate(etk::Vector3D<float> vect)
{
	etk::Matrix4 tmp;
	// set translation :
	tmp.m_mat[3] = vect.x;
	tmp.m_mat[7] = vect.y;
	tmp.m_mat[11] = vect.z;
	//TK_INFO("Translate :");
	//etk::matrix::Display(tmp);
	return tmp;
}

etk::Matrix4 etk::Matrix4::Scale(etk::Vector3D<float> vect)
{
	etk::Matrix4 tmp;
	// set scale :
	tmp.m_mat[0] = vect.x;
	tmp.m_mat[5] = vect.y;
	tmp.m_mat[10] = vect.z;
	//TK_INFO("Scale :");
	//etk::matrix::Display(tmp);
	return tmp;
}

etk::Matrix4 etk::Matrix4::Rotate(etk::Vector3D<float> vect, float angleRad)
{
	etk::Matrix4 tmp;
	float cosVal = cos(angleRad);
	float sinVal = sin(angleRad);
	float invVal = 1.0-cosVal;
	// set rotation : 
	tmp.m_mat[0]  = vect.x * vect.x * invVal + cosVal;
	tmp.m_mat[1]  = vect.x * vect.y * invVal - vect.z * cosVal;
	tmp.m_mat[2]  = vect.x * vect.z * invVal + vect.y * sinVal;
	
	tmp.m_mat[4]  = vect.y * vect.x * invVal + vect.z * sinVal;
	tmp.m_mat[5]  = vect.y * vect.y * invVal + cosVal;
	tmp.m_mat[6]  = vect.y * vect.z * invVal - vect.x * sinVal;
	
	tmp.m_mat[8]  = vect.z * vect.x * invVal - vect.y * sinVal;
	tmp.m_mat[9]  = vect.z * vect.y * invVal + vect.x * sinVal;
	tmp.m_mat[10] = vect.z * vect.z * invVal + cosVal;
	return tmp;
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
