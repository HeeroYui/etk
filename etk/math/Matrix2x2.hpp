/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once
#include <etk/types.hpp>
#include <etk/math/Vector2D.hpp>
#include <cmath>

namespace etk {
	/**
	 * This class represents a 2x2 matrix.
	 */
	class Matrix2x2 {
		public:
			/**
			 * @brief Internal data
			 *  sx  shx
			 *  sy  shy
			 */
			float m_mat[2*2];
		public :
			/**
			 * @brief Constructor that load zero matrix
			 */
			Matrix2x2();
			/**
			 * @brief Configuration constructorwith single value.
			 * @param[in] _value single vamue
			 */
			Matrix2x2(float _value);
			/**
			 * @brief Configuration constructor.
			 * @param[in] _a1 element 0x0
			 * @param[in] _a2 element 0x1
			 * @param[in] _b1 element 1x0
			 * @param[in] _b2 element 1x1
			 */
			Matrix2x2(float _a1, float _a2, float _b1, float _b2);
			/**
			 * @brief Copy constructor.
			 * @param[in] _obj Matrix object to copy
			 */
			Matrix2x2(const Matrix2x2& _matrix);
			/**
			 * @brief Set Value on the matrix
			 * @param[in] _a1 element 0x0
			 * @param[in] _a2 element 0x1
			 * @param[in] _b1 element 1x0
			 * @param[in] _b2 element 1x1
			 */
			void setValue(float _a1, float _a2, float _b1, float _b2);
			/**
			 * @brief Load Zero matrix
			 */
			void setZero();
			/**
			 * @brief get the colom id values
			 * @param[in] _iii Id of the colomn
			 * @return Vector 2D vith the values
			 */
			vec2 getColumn(uint32_t _iii) const;
			/**
			 * @brief get the row id values
			 * @param[in] _iii Id of the row
			 * @return Vector 2D vith the values
			 */
			vec2 getRow(uint32_t _iii) const;
			/**
			 * @brief get a transpose matrix of this one.
			 * @return the transpose matrix
			 */
			Matrix2x2 getTranspose() const;
			/**
			 * @brief Transpose the current matrix.
			 */
			void transpose();
			/**
			 * @brief Computes the determinant of the matrix.
			 * @return The determinent Value.
			 */
			float determinant() const;
			/**
			 * @brief Calculate the trace of the matrix
			 * @return value of addition of all element in the diagonal
			 */
			float getTrace() const;
			/**
			 * @brief Inverts the matrix.
			 * @note The determinant must be != 0, otherwithe the matrix can't be inverted.
			 * @return The inverted matrix.
			 */
			Matrix2x2 getInverse() const;
			/**
			 * @brief Inverts the current matrix.
			 * @note The determinant must be != 0, otherwithe the matrix can't be inverted.
			 */
			void inverse();
			/**
			 * @brief get the mathix with the absolute value
			 * @return matix in absolute
			 */
			Matrix2x2 getAbsolute() const;
			/**
			 * @brief absolutise the matrix
			 */
			void absolute();
			/**
			 * @brief Load Identity matrix
			 */
			void setIdentity();
			/**
			 * @brief create a Identity matrix
			 * @return created new matrix
			 */
			static etk::Matrix2x2 identity();
			/**
			 * @brief create a ZERO matrix
			 * @return created new matrix
			 */
			static Matrix2x2 zero();
			/**
			 * @brief Operator= Asign the current object with an other object
			 * @param[in] _obj Reference on the external object
			 * @return Local reference of the vector asigned
			 */
			const Matrix2x2& operator= (const Matrix2x2& _obj );
			/**
			 * @brief Equality compare operator with an other object.
			 * @param[in] _obj Reference on the comparing object
			 * @return true The Objects are identical
			 * @return false The Objects are NOT identical
			 */
			bool operator== (const Matrix2x2& _obj) const;
			/**
			 * @brief In-Equality compare operator with an other object.
			 * @param[in] _obj Reference on the comparing object
			 * @return true The Objects are NOT identical
			 * @return false The Objects are identical
			 */
			bool operator!= (const Matrix2x2& _obj) const;
			/**
			 * @brief Operator+= Addition an other matrix with this one
			 * @param[in] _obj Reference on the external object
			 * @return Local reference of the vector additionned
			 */
			const Matrix2x2& operator+= (const Matrix2x2& _obj);
			/**
			 * @brief Operator+ Addition an other matrix with this one
			 * @param[in] _obj Reference on the external object
			 * @return New vector containing the value
			 */
			Matrix2x2 operator+ (const Matrix2x2& _obj) const;
			/**
			 * @brief Operator-= Decrement an other matrix with this one
			 * @param[in] _obj Reference on the external object
			 * @return Local reference of the vector decremented
			 */
			const Matrix2x2& operator-= (const Matrix2x2& _obj);
			/**
			 * @brief Operator- Decrement an other matrix with this one
			 * @param[in] _obj Reference on the external object
			 * @return New vector containing the value
			 */
			Matrix2x2 operator- (const Matrix2x2& _obj) const;
			/**
			 * @brief Operator*= Multiplication an other matrix with this one
			 * @param[in] _obj Reference on the external object
			 * @return Local reference of the vector multiplicated
			 */
			const Matrix2x2& operator *= (const Matrix2x2& _obj);
			/**
			 * @brief Operator* Multiplication an other matrix with this one
			 * @param[in] _obj Reference on the external object
			 * @return New vector containing the value
			 */
			Matrix2x2 operator * (const Matrix2x2& _obj) const;
			/**
			 * @brief Operator*= Multiplication a value
			 * @param[in] _value value to multiply all the matrix
			 * @return Local reference of the vector multiplicated
			 */
			const Matrix2x2& operator *= (float _value);
			/**
			 * @brief Operator*= Multiplication a value
			 * @param[in] _value value to multiply all the matrix
			 * @return Local reference of the vector multiplicated
			 */
			Matrix2x2 operator * (float _value) const;
			/**
			 * @brief Operator* apply matrix on a vector
			 * @param[in] _point Point value to apply the matrix
			 * @return New vector containing the value
			 */
			vec2 operator * (const vec2& _point) const;
	};
	
	/**
	 * @brief Create a matrix 2D with a simple rotation
	 * @param[in] _angleRad Radian angle to set at the matrix
	 * @return New matrix of the transformation requested
	 */
	Matrix2x2 mat2x2Rotate(float _angleRad);
	/**
	 * @brief Create a matrix 2D with a simple scale
	 * @param[in] _scale 2 dimention scale
	 * @return New matrix of the transformation requested
	 */
	Matrix2x2 mat2x2Scale(const vec2& _scale);
	/**
	 * @brief Create a matrix 2D with a simple scale
	 * @param[in] _scale same scale in 2 and Y
	 * @return New matrix of the transformation requested
	 */
	Matrix2x2 mat2x2Scale(float _scale);
	/**
	 * @brief Create a matrix 2D with a simple skew
	 * @param[in] _skew 2 dimention skew
	 * @return New matrix of the transformation requested
	 */
	Matrix2x2 mat2x2Skew(const vec2& _skew);
	//! @not_in_doc
	etk::Stream& operator <<(etk::Stream& _os, const etk::Matrix2x2& _obj);
}

etk::Matrix2x2 operator-(const etk::Matrix2x2& _matrix);

// simplify using of matrix ...
using mat2 = etk::Matrix2x2; //!< Use simplification in upper application to use matrix like openGL shader


