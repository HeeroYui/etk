/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include <etk/types.hpp>

#pragma once

#include <etk/math/Vector3D.hpp>

#include <cmath>

namespace etk {
	/**
	 * @brief Convert degree in radian
	 * @param[in] _val Value to converted in degree
	 * @return Angle in radian
	 */
	template<class T>
	T degreeToRadian(T _val) {
		return _val*M_PI/T(180.0);
	}
	/**
	 * @brief Convert radian in degree
	 * @param[in] _val Value to converted in radian
	 * @return Angle in degree
	 */
	template<class T>
	T radianToDegree(T _val) {
		return _val*T(180.0)/M_PI;
	}
	/**
	 * @brief Transformation matrix for vector 3D.
	 */
	class Matrix4 {
		public:
			float m_mat[4*4]; //!< matrix data
		public:
			/**
			 * @brief configure identity of the matrix
			 */
			void identity();
			/**
			 * @brief Constructor that load identity
			 */
			Matrix4();
			/**
			 * @brief Copy constructor.
			 * @param[in] _obj Matrix object to copy
			 */
			Matrix4(const Matrix4& _obj);
			/**
			 * @brief Configuration constructor.
			 * @param[in] _a1 1st colomn, 1 line value
			 * @param[in] _b1 2nd colomn, 1 line value
			 * @param[in] _c1 3rd colomn, 1 line value
			 * @param[in] _d1 4th colomn, 1 line value
			 * @param[in] _a2 1st colomn, 2 line value
			 * @param[in] _b2 2nd colomn, 2 line value
			 * @param[in] _c2 3rd colomn, 2 line value
			 * @param[in] _d2 4th colomn, 2 line value
			 * @param[in] _a3 1st colomn, 3 line value
			 * @param[in] _b3 2nd colomn, 3 line value
			 * @param[in] _c3 3rd colomn, 3 line value
			 * @param[in] _d3 4th colomn, 3 line value
			 * @param[in] _a4 1st colomn, 4 line value
			 * @param[in] _b4 2nd colomn, 4 line value
			 * @param[in] _c4 3rd colomn, 4 line value
			 * @param[in] _d4 4th colomn, 4 line value
			 */
			Matrix4(float _a1, float _b1, float _c1, float _d1,
			        float _a2, float _b2, float _c2, float _d2,
			        float _a3, float _b3, float _c3, float _d3,
			        float _a4, float _b4, float _c4, float _d4);
			/**
			 * @brief Configuration constructor.
			 * @param[in] _values vector of values
			 */
			Matrix4(float* _values);
			/**
			 * @brief Operator= Asign the current object with an other object
			 * @param[in] _obj Reference on the external object
			 * @return Local reference of the vector asigned
			 */
			const Matrix4& operator= (const Matrix4& _obj);
			/**
			 * @brief Equality compare operator with an other object.
			 * @param[in] _obj Reference on the comparing object
			 * @return true The Objects are identical
			 * @return false The Objects are NOT identical
			 */
			bool operator== (const Matrix4& _obj) const;
			/**
			 * @brief In-Equality compare operator with an other object.
			 * @param[in] _obj Reference on the comparing object
			 * @return true The Objects are NOT identical
			 * @return false The Objects are identical
			 */
			bool operator!= (const Matrix4& _obj) const;
			/**
			 * @brief Operator+= Addition an other matrix with this one
			 * @param[in] _obj Reference on the external object
			 * @return Local reference of the vector additionned
			 */
			const Matrix4& operator+= (const Matrix4& _obj);
			/**
			 * @brief Operator+ Addition an other matrix with this one
			 * @param[in] _obj Reference on the external object
			 * @return New vector containing the value
			 */
			Matrix4 operator+ (const Matrix4& _obj) const;
			/**
			 * @brief Operator-= Decrement an other matrix with this one
			 * @param[in] _obj Reference on the external object
			 * @return Local reference of the vector decremented
			 */
			const Matrix4& operator-= (const Matrix4& _obj);
			/**
			 * @brief Operator- Decrement an other matrix with this one
			 * @param[in] _obj Reference on the external object
			 * @return New vector containing the value
			 */
			Matrix4 operator- (const Matrix4& _obj) const;
			/**
			 * @brief Operator*= Multiplication an other matrix with this one
			 * @param[in] _obj Reference on the external object
			 * @return Local reference of the vector multiplicated
			 */
			const Matrix4& operator*= (const Matrix4& _obj);
			/**
			 * @brief Operator* Multiplication an other matrix with this one
			 * @param[in] _obj Reference on the external object
			 * @return New vector containing the value
			 */
			Matrix4 operator* (const Matrix4& _obj) const;
			/**
			 * @brief Operator* apply matrix on a vector
			 * @param[in] _point Point value to apply the matrix
			 * @return New vector containing the value
			 */
			vec3 operator*(const vec3& _point) const;
			/**
			 * @brief Transpose the current matix (usefull for OpenGL display)
			 */
			void transpose();
			/**
			 * @brief Scale the current Matrix.
			 * @param[in] _vect Scale vector to apply.
			 */
			void scale(const vec3& _vect);
			/**
			 * @brief Scale the current Matrix.
			 * @param[in] _sx Scale X value to apply.
			 * @param[in] _sy Scale Y value to apply.
			 * @param[in] _sz Scale Z value to apply.
			 */
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
	/**
	 * @brief Create projection matrix with the box parameter (camera view in -z axis)
	 * @param[in] _xmin X minimum size of the frustum
	 * @param[in] _xmax X maximum size of the frustum
	 * @param[in] _ymin Y minimum size of the frustum
	 * @param[in] _ymax Y maximum size of the frustum
	 * @param[in] _zNear Z minimum size of the frustum
	 * @param[in] _zFar Z maximum size of the frustum
	 * @return New matrix of the transformation requested
	 */
	Matrix4 matFrustum(float _xmin, float _xmax, float _ymin, float _ymax, float _zNear, float _zFar);
	/**
	 * @brief Create projection matrix with human repensentation view (camera view in -z axis)
	 * @param[in] _foxy Focal in radian of the camera
	 * @param[in] _aspect aspect ratio of the camera
	 * @param[in] _zNear Z near size of the camera
	 * @param[in] _zFar Z far size of the camera
	 * @return New matrix of the transformation requested
	 */
	Matrix4 matPerspective(float _foxy, float _aspect, float _zNear, float _zFar);
	/**
	 * @brief Create orthogonal projection matrix with the box parameter (camera view in -z axis)
	 * @param[in] _left left size of the camera
	 * @param[in] _right Right size of the camera
	 * @param[in] _bottom Buttom size of the camera
	 * @param[in] _top Top Size of the camera
	 * @param[in] _nearVal Z near size of the camera
	 * @param[in] _farVal Z far size of the camera
	 * @return New matrix of the transformation requested
	 */
	Matrix4 matOrtho(float _left, float _right, float _bottom, float _top, float _nearVal, float _farVal);
	/**
	 * @brief Create a matrix 3D with a simple translation
	 * @param[in] _translate 3 dimention translation
	 * @return New matrix of the transformation requested
	 */
	Matrix4 matTranslate(vec3 _translate);
	/**
	 * @brief Create a matrix 3D with a simple scale
	 * @param[in] _scale 3 dimention scale
	 * @return New matrix of the transformation requested
	 */
	Matrix4 matScale(vec3 _scale);
	/**
	 * @brief Create a matrix 3D with a simple rotation
	 * @param[in] _normal vector aroud witch apply the rotation
	 * @param[in] _angleRad Radian angle to set at the matrix
	 * @return New matrix of the transformation requested
	 */
	Matrix4 matRotate(vec3 _normal, float _angleRad=0.0);
	//! @not_in_doc
	Matrix4 matRotate2(vec3 _vect);	/**
	 * @brief Create projection matrix with camera property (camera view in -z axis)
	 * @param[in] _eye Optical center of the camera
	 * @param[in] _target Point of where the camera is showing
	 * @param[in] _up Up vector of the camera
	 * @return New matrix of the transformation requested
	 */
	Matrix4 matLookAt(const vec3& _eye,
	                  const vec3& _target,
	                  const vec3& _up);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const etk::Matrix4& _obj);
};


// To siplify the writing of the code ==> this permit to have the same name with the glsl language...
using mat4 = etk::Matrix4; //!< Matrix naming like openGl shader

