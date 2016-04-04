/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#pragma once

#include <etk/math/Vector2D.h>
#include <etk/types.h>
namespace etk {
	/**
	 * @brief Transformation matrix for vector 2D.
	 */
	class Matrix2 {
		public:
			/**
			 * @brief Internal data
			 *  sx  shx  tx
			 *  sy  shy  ty
			 */
			float m_mat[2*3];
		public:
			/**
			 * @brief Constructor that load identity
			 */
			Matrix2();
			/**
			 * @brief Copy constructor.
			 * @param[in] _obj Matrix object to copy
			 */
			Matrix2(const Matrix2& _obj);
			/**
			 * @brief Configuration constructor.
			 * @param[in] _sx Scale threw X axis
			 * @param[in] _shy Rotate in radian threw Y axis
			 * @param[in] _shx Rotate in radian threw X axis
			 * @param[in] _sy Scale threw Y axis
			 * @param[in] _tx Translate threw X axis
			 * @param[in] _ty translate threw Y axis
			 */
			Matrix2(float _sx,
			        float _shy,
			        float _shx,
			        float _sy,
			        float _tx,
			        float _ty);
			/**
			 * @brief Configuration constructor.
			 * @param[in] _values vector of values in float
			 */
			Matrix2(const float* _values);
			/**
			 * @brief Configuration constructor.
			 * @param[in] _values vector of values in double
			 */
			Matrix2(const double* _values);
			/**
			 * @brief Load Identity matrix
			 */
			void identity();
			/**
			 * @brief Operator= Asign the current object with an other object
			 * @param[in] _obj Reference on the external object
			 * @return Local reference of the vector asigned
			 */
			const Matrix2& operator= (const Matrix2& _obj );
			/**
			 * @brief Equality compare operator with an other object.
			 * @param[in] _obj Reference on the comparing object
			 * @return true The Objects are identical
			 * @return false The Objects are NOT identical
			 */
			bool operator== (const Matrix2& _obj) const;
			/**
			 * @brief In-Equality compare operator with an other object.
			 * @param[in] _obj Reference on the comparing object
			 * @return true The Objects are NOT identical
			 * @return false The Objects are identical
			 */
			bool  operator!= (const Matrix2& _obj) const;
			/**
			 * @brief Operator+= Addition an other matrix with this one
			 * @param[in] _obj Reference on the external object
			 * @return Local reference of the vector additionned
			 */
			const Matrix2& operator+= (const Matrix2& _obj);
			/**
			 * @brief Operator+ Addition an other matrix with this one
			 * @param[in] _obj Reference on the external object
			 * @return New vector containing the value
			 */
			Matrix2 operator+ (const Matrix2& _obj) const;
			/**
			 * @brief Operator-= Decrement an other matrix with this one
			 * @param[in] _obj Reference on the external object
			 * @return Local reference of the vector decremented
			 */
			const Matrix2& operator-= (const Matrix2& _obj);
			/**
			 * @brief Operator- Decrement an other matrix with this one
			 * @param[in] _obj Reference on the external object
			 * @return New vector containing the value
			 */
			Matrix2 operator- (const Matrix2& _obj) const;
			/**
			 * @brief Operator*= Multiplication an other matrix with this one
			 * @param[in] _obj Reference on the external object
			 * @return Local reference of the vector multiplicated
			 */
			const Matrix2& operator *= (const Matrix2& _obj);
			/**
			 * @brief Operator* Multiplication an other matrix with this one
			 * @param[in] _obj Reference on the external object
			 * @return New vector containing the value
			 */
			Matrix2 operator * (const Matrix2& _obj);
			/**
			 * @brief Operator* apply matrix on a vector
			 * @param[in] _point Point value to apply the matrix
			 * @return New vector containing the value
			 */
			vec2 operator * (const vec2& _point) const;
			/**
			 * @brief Apply matrix on a vector Scale Rotate, but NOT the translation
			 * @param[in] _point Point value to apply the matrix
			 * @return New vector containing the value
			 */
			vec2 applyScaleRotation(const vec2& _point) const;
			/**
			 * @brief Inverse the current Matrix
			 * @return New vector containing the value
			 */
			Matrix2 operator ~ () const;
			/**
			 * @brief Flip the mathix threw the X axis
			 */
			void flipX();
			/**
			 * @brief Flip the mathix threw the Y axis
			 */
			void flipY();
			/**
			 * @brief Scale the current Matrix.
			 * @param[in] _vect Vector to scale matrix.
			 */
			void scale(const vec2& _vect);
			/**
			 * @brief Scale the current Matrix.
			 * @param[in] _value Single value to scale in X andf Y.
			 */
			void scale(float _value);
			/**
			 * @brief Makes a rotation matrix.
			 * @param[in] _angleRad angle to apply.
			 */
			void rotate(float _angleRad);
			/**
			 * @brief Makes a translation of the matrix
			 * @param[in] _vect Translation to apply.
			 */
			void translate(const vec2& _vect);
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
			void invert();
	};
	/**
	 * @brief Create a matrix 2D with a simple rotation
	 * @param[in] _angleRad Radian angle to set at the matrix
	 * @return New matrix of the transformation requested
	 */
	Matrix2 mat2Rotate(float _angleRad);
	/**
	 * @brief Create a matrix 2D with a simple scale
	 * @param[in] _scale 2 dimention scale
	 * @return New matrix of the transformation requested
	 */
	Matrix2 mat2Scale(const vec2& _scale);
	/**
	 * @brief Create a matrix 2D with a simple scale
	 * @param[in] _scale same scale in 2 and Y
	 * @return New matrix of the transformation requested
	 */
	Matrix2 mat2Scale(float _scale);
	/**
	 * @brief Create a matrix 2D with a simple translation
	 * @param[in] _translate 2 dimention translation
	 * @return New matrix of the transformation requested
	 */
	Matrix2 mat2Translate(const vec2& _translate);
	/**
	 * @brief Create a matrix 2D with a simple skew
	 * @param[in] _skew 2 dimention skew
	 * @return New matrix of the transformation requested
	 */
	Matrix2 mat2Skew(const vec2& _skew);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const etk::Matrix2& _obj);
}
// simplify using of matrix ...
using mat2 = etk::Matrix2; //!< Use simplification in upper application to use matrix like openGL shader


