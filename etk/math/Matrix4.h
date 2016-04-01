/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <etk/types.h>

#pragma once

#include <etk/math/Vector3D.h>

#if 1
#include <math.h>

#define DEG_TO_RAD(a)       ((a)*M_PI/180.0f)
#define RAD_TO_DEG(a)       ((a)*180.0f/M_PI)

namespace etk {
	class Matrix4 {
		public:
			float m_mat[4*4];
			void identity();
			/*****************************************************
			 *    Constructor
			 *****************************************************/
			Matrix4();
			Matrix4(const Matrix4& _obj);
			Matrix4(float _a1, float _b1, float _c1, float _d1,
			        float _a2, float _b2, float _c2, float _d2,
			        float _a3, float _b3, float _c3, float _d3,
			        float _a4, float _b4, float _c4, float _d4);
			Matrix4(float* _obj);
			/*****************************************************
			 *    Destructor
			 *****************************************************/
			~Matrix4();
			/*****************************************************
			 *    = assigment
			 *****************************************************/
			const Matrix4& operator= (const Matrix4& _obj );
			/*****************************************************
			 *    == operator
			 *****************************************************/
			bool operator== (const Matrix4& _obj) const;
			/*****************************************************
			 *    != operator
			 *****************************************************/
			bool operator!= (const Matrix4& _obj) const;
			/*****************************************************
			 *    += operator
			 *****************************************************/
			const Matrix4& operator+= (const Matrix4& _obj);
			/*****************************************************
			 *    + operator
			 *****************************************************/
			Matrix4 operator+ (const Matrix4& _obj) const;
			/*****************************************************
			 *    -= operator
			 *****************************************************/
			const Matrix4& operator-= (const Matrix4& _obj);
			/*****************************************************
			 *    - operator
			 *****************************************************/
			Matrix4 operator- (const Matrix4& _obj) const;
			/*****************************************************
			 *    *= operator
			 *****************************************************/
			const Matrix4& operator*= (const Matrix4& _obj);
			/*****************************************************
			 *    * operator
			 *****************************************************/
			Matrix4 operator* (const Matrix4& _obj) const;
			vec3 operator*(const vec3& _point) const;
			/*****************************************************
			 *  other basic function :
			 *****************************************************/
			void transpose();
			/**
			 * @brief Scale the current Matrix.
			 * @param[in] _vect Scale vector to apply.
			 */
			void scale(const vec3& _vect);
			//! @previous
			void scale(float _sx, float _sy, float _sz);
			/**
			 * @brief Makes a rotation matrix about an arbitrary axis.
			 * @param[in] _vect vector to apply the angle.
			 * @param[in] _angleRad angle to apply.
			 */
			void rotate(const vec3& _vect, float _angleRad=0.0);
			/**
			 * @brief Makes a translation of the matrix
			 * @param[in] _vect Translation to apply.
			 */
			void translate(const vec3& _vect);
			/**
			 * @brief Computes a cofactor. Used for matrix inversion.
			 * @param[in] _row Id of raw.
			 * @param[in] _col Id of colomn.
			 * @return the coFactorValue.
			 */
			float coFactor(int32_t _row, int32_t _col) const;
			/**
			 * @brief Computes the determinant of the matrix.
			 * @return The determinent Value.
			 */
			float determinant() const;
			/**
			 * @brief Inverts the matrix.
			 * @note The determinant must be != 0, otherwithe the matrix can't be inverted.
			 * @return The inverted matrix.
			 */
			Matrix4 invert();
	};
	Matrix4 matFrustum(float _xmin, float _xmax, float _ymin, float _ymax, float _zNear, float _zFar);
	Matrix4 matPerspective(float _foxy, float _aspect, float _zNear, float _zFar);
	Matrix4 matOrtho(float _left, float _right, float _bottom, float _top, float _nearVal, float _farVal);
	Matrix4 matTranslate(vec3 _vect);
	Matrix4 matScale(vec3 _vect);
	Matrix4 matRotate(vec3 _vect, float _angleRad=0.0);
	Matrix4 matRotate2(vec3 _vect);
	Matrix4 matLookAt(const vec3& _eye,
	                  const vec3& _target,
	                  const vec3& _up);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const etk::Matrix4& _obj);
};


// To siplify the writing of the code ==> this permit to have the same name with the glsl language...
typedef etk::Matrix4 mat4;
#else
	// include matrix from bulletlib mat4 interface:
	#include <vectormath/scalar/vectormath_aos.h>
	// To siplify the writing of the code ==> this permit to have the same name with the glsl language...
	typedef Vectormath::Aos::Matrix4  mat4;
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const mat4& _obj);
	
	// TODO : Remove this ???
	namespace etk {
		mat4 matTranslate(const vec3& _vect);
		mat4 matScale(const vec3& _vect);
		mat4 matRotate(const vec3& _vect, float _angleRad=0.0);
	}
#endif


