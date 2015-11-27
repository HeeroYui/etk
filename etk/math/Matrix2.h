/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ETK_TYPES_MATRIX2_H__
#define __ETK_TYPES_MATRIX2_H__

#include <etk/math/Vector2D.h>
#include <etk/types.h>
namespace etk {
	class Matrix2 {
		public:
			/*
			 *  sx  shx  tx
			 *  sy  shy  ty
			 */
			float m_mat[2*3];
			/**
			 * @brief Load Identity matrix
			 */
			void identity();
		public:
			/*****************************************************
			 *    Constructor
			 *****************************************************/
			Matrix2();
			Matrix2(const Matrix2& _obj);
			Matrix2(float _sx,
			        float _shy,
			        float _shx,
			        float _sy,
			        float _tx,
			        float _ty);
			Matrix2(const float* _values);
			Matrix2(const double* _values);
			/*****************************************************
			 *    Destructor
			 *****************************************************/
			~Matrix2();
			/*****************************************************
			 *    = assigment
			 *****************************************************/
			const Matrix2& operator= (const Matrix2& _obj );
			/*****************************************************
			 *    == operator
			 *****************************************************/
			bool operator== (const Matrix2& _obj) const;
			/*****************************************************
			 *    != operator
			 *****************************************************/
			bool  operator!= (const Matrix2& _obj) const;
			/*****************************************************
			 *    += operator
			 *****************************************************/
			const Matrix2& operator+= (const Matrix2& _obj);
			/*****************************************************
			 *    + operator
			 *****************************************************/
			Matrix2 operator+ (const Matrix2& _obj) const;
			/*****************************************************
			 *    -= operator
			 *****************************************************/
			const Matrix2& operator-= (const Matrix2& _obj);
			/*****************************************************
			 *    - operator
			 *****************************************************/
			Matrix2 operator- (const Matrix2& _obj) const;
			/*****************************************************
			 *    *= operator
			 *****************************************************/
			const Matrix2& operator *= (const Matrix2& _obj);
			/*****************************************************
			 *    * operator
			 *****************************************************/
			Matrix2 operator * (const Matrix2& _obj);
			vec2 operator * (const vec2& _obj);
			/*****************************************************
			 *    ~ operator
			 *****************************************************/
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
			 * @param[in] _value Single value to scale in X andf Y.
			 */
			void scale(const vec2& _vect);
			//! @previous
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
	Matrix2 mat2Rotate(float _angleRad);
	Matrix2 mat2Scale(const vec2& _scale);
	Matrix2 mat2Scale(float _scale);
	Matrix2 mat2Translate(const vec2& _translate);
	Matrix2 mat2Skew(const vec2& _skew);
	std::ostream& operator <<(std::ostream& _os, const etk::Matrix2& _obj);
}
// simplify using of matrix ...
typedef etk::Matrix2 mat2;

#endif

