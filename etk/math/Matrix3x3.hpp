/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once
#include <etk/types.hpp>
#include <etk/math/Vector3D.hpp>

extern "C" {
	#include <math.h>
}

namespace etk {
	/**
	 *  @brief This class represents a 3x3 matrix.
	 */
	class Matrix3x3 {
		public:
			float m_mat[3*3]; //!< matrix data
		public :
			/**
			 * @brief Constructor that load zero matrix
			 */
			Matrix3x3();
			/**
			 * @brief Configuration constructorwith single value.
			 * @param[in] _value single vamue
			 */
			Matrix3x3(float value);
			/**
			 * @brief Configuration constructor.
			 * @param[in] _a1 element 0x0
			 * @param[in] _a2 element 0x1
			 * @param[in] _a3 element 0x2
			 * @param[in] _b1 element 1x0
			 * @param[in] _b2 element 1x1
			 * @param[in] _b3 element 1x2
			 * @param[in] _c1 element 2x0
			 * @param[in] _c2 element 2x1
			 * @param[in] _c3 element 2x2
			 */
			Matrix3x3(float _a1, float _a2, float _a3,
			        float _b1, float _b2, float _b3,
			        float _c1, float _c2, float _c3);
			/**
			 * @brief Copy constructor.
			 * @param[in] _obj Matrix object to copy
			 */
			Matrix3x3(const Matrix3x3& _obj);
			/**
			 * @brief Set Value on the matrix
			 * @param[in] _a1 element 0x0
			 * @param[in] _a2 element 0x1
			 * @param[in] _a3 element 0x2
			 * @param[in] _b1 element 1x0
			 * @param[in] _b2 element 1x1
			 * @param[in] _b3 element 1x2
			 * @param[in] _c1 element 2x0
			 * @param[in] _c2 element 2x1
			 * @param[in] _c3 element 2x2
			 */
			void setValue(float _a1, float _a2, float _a3,
			              float _b1, float _b2, float _b3,
			              float _c1, float _c2, float _c3);
			/**
			 * @brief Load Zero matrix
			 */
			void setZero();
			/**
			 * @brief get the colom id values
			 * @param[in] _iii Id of the colomn
			 * @return Vector 3D vith the values
			 */
			vec3 getColumn(uint32_t _iii) const;
			/**
			 * @brief get the row id values
			 * @param[in] _iii Id of the row
			 * @return Vector 3D vith the values
			 */
			vec3 getRow(uint32_t _iii) const;
			/**
			 * @brief get a transpose matrix of this one.
			 * @return the transpose matrix
			 */
			Matrix3x3 getTranspose() const;
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
			Matrix3x3 getInverse() const;
			/**
			 * @brief Inverts the current matrix.
			 * @note The determinant must be != 0, otherwithe the matrix can't be inverted.
			 */
			void inverse();
			/**
			 * @brief get the matrix with the absolute value
			 * @return matix in absolute
			 */
			Matrix3x3 getAbsolute() const;
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
			static Matrix3x3 identity();
			/**
			 * @brief create a ZERO matrix
			 * @return created new matrix
			 */
			static Matrix3x3 zero();
			/**
			 * @brief create a skew-symmetric matrix using a given vector that can be used to compute cross product with another vector using matrix multiplication
			 * @param[in] _vector Vector to comute
			 * @return Matrix to compute
			 */
			static Matrix3x3 computeSkewSymmetricMatrixForCrossProduct(const vec3& _vector);
			/**
			 * @brief Operator= Asign the current object with an other object
			 * @param[in] _obj Reference on the external object
			 * @return Local reference of the vector asigned
			 */
			const Matrix3x3& operator= (const Matrix3x3& _obj );
			/**
			 * @brief Equality compare operator with an other object.
			 * @param[in] _obj Reference on the comparing object
			 * @return true The Objects are identical
			 * @return false The Objects are NOT identical
			 */
			bool operator== (const Matrix3x3& _obj) const;
			/**
			 * @brief In-Equality compare operator with an other object.
			 * @param[in] _obj Reference on the comparing object
			 * @return true The Objects are NOT identical
			 * @return false The Objects are identical
			 */
			bool operator!= (const Matrix3x3& _obj) const;
			/**
			 * @brief Operator+= Addition an other matrix with this one
			 * @param[in] _obj Reference on the external object
			 * @return Local reference of the vector additionned
			 */
			const Matrix3x3& operator+= (const Matrix3x3& _obj);
			/**
			 * @brief Operator+ Addition an other matrix with this one
			 * @param[in] _obj Reference on the external object
			 * @return New vector containing the value
			 */
			Matrix3x3 operator+ (const Matrix3x3& _obj) const;
			/**
			 * @brief Operator-= Decrement an other matrix with this one
			 * @param[in] _obj Reference on the external object
			 * @return Local reference of the vector decremented
			 */
			const Matrix3x3& operator-= (const Matrix3x3& _obj);
			/**
			 * @brief Operator- Decrement an other matrix with this one
			 * @param[in] _obj Reference on the external object
			 * @return New vector containing the value
			 */
			Matrix3x3 operator- (const Matrix3x3& _obj) const;
			/**
			 * @brief Operator*= Multiplication an other matrix with this one
			 * @param[in] _obj Reference on the external object
			 * @return Local reference of the vector multiplicated
			 */
			const Matrix3x3& operator *= (const Matrix3x3& _obj);
			/**
			 * @brief Operator* Multiplication an other matrix with this one
			 * @param[in] _obj Reference on the external object
			 * @return New vector containing the value
			 */
			Matrix3x3 operator * (const Matrix3x3& _obj) const;
			/**
			 * @brief Operator*= Multiplication a value
			 * @param[in] _value value to multiply all the matrix
			 * @return Local reference of the vector multiplicated
			 */
			const Matrix3x3& operator *= (float _value);
			/**
			 * @brief Operator*= Multiplication a value
			 * @param[in] _value value to multiply all the matrix
			 * @return Local reference of the vector multiplicated
			 */
			Matrix3x3 operator * (float _value) const;
			/**
			 * @brief Operator* apply matrix on a vector
			 * @param[in] _point Point value to apply the matrix
			 * @return New vector containing the value
			 */
			vec3 operator * (const vec3& _point) const;
	};
	//! @not_in_doc
	etk::Stream& operator <<(etk::Stream& _os, const etk::Matrix3x3& _obj);
}

etk::Matrix3x3 operator-(const etk::Matrix3x3& _matrix);

// simplify using of matrix ...
using mat3 = etk::Matrix3x3; //!< Use simplification in upper application to use matrix like openGL shader


