/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include <etk/math/Vector3D.hpp>
#include <etk/types.hpp>

#pragma once

#include <cmath>

namespace etk {
	/**
	 * @brief Vectorial 2-dimention vector (x/y)
	 */
	template <typename T> class Vector2D {
		public:
			T m_floats[2]; //!< all internal values
		public:
			/* ****************************************************
			 *    Constructor
			 *****************************************************/
			Vector2D() {
				#ifdef DEBUG
					// in debug mode we set supid value to prevent forget of the inits ...
					m_floats[0] = (T)34673363;
					m_floats[1] = (T)34523535;
				#endif
			}
			/**
			 * @brief Constructor from scalars
			 * @param[in] _xxx X value
			 * @param[in] _yyy Y value
			 */
			Vector2D(T _xxx, T _yyy) {
				m_floats[0] = _xxx;
				m_floats[1] = _yyy;
			}
			/**
			 * @brief Constructor with external vector
			 * @param[in] _obj The vector to add to this one
			 */
			Vector2D(const Vector2D<double>& _obj) {
				m_floats[0] = (T)_obj.x();
				m_floats[1] = (T)_obj.y();
			}
			/**
			 * @brief Constructor with external vector
			 * @param[in] _obj The vector to add to this one
			 */
			Vector2D(const Vector2D<float>& _obj) {
				m_floats[0] = (T)_obj.x();
				m_floats[1] = (T)_obj.y();
			}
			/**
			 * @brief Constructor with external vector
			 * @param[in] _obj The vector to add to this one
			 */
			Vector2D(const Vector2D<int32_t>& _obj) {
				m_floats[0] = (T)_obj.x();
				m_floats[1] = (T)_obj.y();
			}
			/**
			 * @brief Constructor with string data
			 * @param[in] _str Sting containing the value to parse
			 */
			Vector2D(const std::string& _str);
			#if __CPP_VERSION__ >= 2011
				Vector2D(const std::u32string& _str);
			#endif
			/**
			 * @brief Operator= Asign the current object with an other object
			 * @param[in] _obj Reference on the external object
			 * @return Local reference of the vector asigned
			 */
			const Vector2D<T>& operator= (const Vector2D<T>& _obj ) {
				m_floats[0] = _obj.m_floats[0];
				m_floats[1] = _obj.m_floats[1];
				return *this;
			}
			/**
			 * @brief Operator= Asign the current object with a value
			 * @param[in] _val Value to assign on the object
			 * @return Local reference of the vector asigned
			 */
			const Vector2D<T>& operator= (const T _val ) {
				m_floats[0] = _val;
				m_floats[1] = _val;
				return *this;
			}
			/**
			 * @brief Equality compare operator with an other object.
			 * @param[in] _obj Reference on the comparing object
			 * @return true The Objects are identical
			 * @return false The Objects are NOT identical
			 */
			bool operator== (const Vector2D<T>& _obj) const {
				return (    (T)_obj.m_floats[0] == m_floats[0]
				         && (T)_obj.m_floats[1] == m_floats[1]);
			}
			/**
			 * @brief In-Equality compare operator with an other object.
			 * @param[in] _obj Reference on the comparing object
			 * @return true The Objects are NOT identical
			 * @return false The Objects are identical
			 */
			bool operator!= (const Vector2D<T>& _obj) const {
				return (    (T)_obj.m_floats[0] != m_floats[0]
				         || (T)_obj.m_floats[1] != m_floats[1]);
			}
			/**
			 * @brief Operator+= Addition an other vertor with this one
			 * @param[in] _obj Reference on the external object
			 * @return Local reference of the vector additionned
			 */
			const Vector2D<T>& operator+= (const Vector2D<T>& _obj) {
				m_floats[0] += _obj.m_floats[0];
				m_floats[1] += _obj.m_floats[1];
				return *this;
			}
			/**
			 * @brief Operator+= Addition an other vertor with this one
			 * @param[in] _val Value to addition at x/y
			 * @return Local reference of the vector additionned
			 */
			const Vector2D<T>& operator+= (const T _val) {
				m_floats[0] += _val;
				m_floats[1] += _val;
				return *this;
			}
			/**
			 * @brief Operator+ Addition an other vertor with this one
			 * @param[in] _obj Reference on the external object
			 * @return New vector containing the value
			 */
			Vector2D<T> operator+ (const Vector2D<T>& _obj) const {
				Vector2D<T> tmpp(m_floats[0],m_floats[1]);
				tmpp.m_floats[0] += _obj.m_floats[0];
				tmpp.m_floats[1] += _obj.m_floats[1];
				return tmpp;
			}
			/**
			 * @brief Operator+ Addition an other vertor with this one
			 * @param[in] _val Value to addition at x/y
			 * @return New vector containing the value
			 */
			Vector2D<T> operator+ (const T _val) const {
				Vector2D<T> tmpp(m_floats[0],m_floats[1]);
				tmpp.m_floats[0] += _val;
				tmpp.m_floats[1] += _val;
				return tmpp;
			}
			/**
			 * @brief Operator-= Decrement an other vertor with this one
			 * @param[in] _obj Reference on the external object
			 * @return Local reference of the vector decremented
			 */
			const Vector2D<T>& operator-= (const Vector2D<T>& _obj) {
				m_floats[0] -= _obj.m_floats[0];
				m_floats[1] -= _obj.m_floats[1];
				return *this;
			}
			/**
			 * @brief Operator-= Decrement an other vertor with this one
			 * @param[in] _val Value to addition at x/y
			 * @return Local reference of the vector decremented
			 */
			const Vector2D<T>& operator-= (const T _val) {
				m_floats[0] -= _val;
				m_floats[1] -= _val;
				return *this;
			}
			/**
			 * @brief Operator- Decrement an other vertor with this one
			 * @param[in] _obj Reference on the external object
			 * @return New vector containing the value
			 */
			Vector2D<T> operator- (const Vector2D<T>& _obj) const {
				Vector2D<T> tmpp(m_floats[0],m_floats[1]);
				tmpp.m_floats[0] -= _obj.m_floats[0];
				tmpp.m_floats[1] -= _obj.m_floats[1];
				return tmpp;
			}
			/**
			 * @brief Operator- Decrement an other vertor with this one
			 * @param[in] _val Value to addition at x/y
			 * @return New vector containing the value
			 */
			Vector2D<T> operator- (const T _val) const {
				Vector2D<T> tmpp(m_floats[0],m_floats[1]);
				tmpp.m_floats[0] -= _val;
				tmpp.m_floats[1] -= _val;
				return tmpp;
			}
			/**
			 * @brief Operator*= Multiplication an other vertor with this one
			 * @param[in] _obj Reference on the external object
			 * @return Local reference of the vector multiplicated
			 */
			const Vector2D<T>& operator*= (const Vector2D<T>& _obj) {
				m_floats[0] *= _obj.m_floats[0];
				m_floats[1] *= _obj.m_floats[1];
				return *this;
			}
			/**
			 * @brief Operator*= Multiplication an other vertor with this one
			 * @param[in] _val Value to addition at x/y
			 * @return Local reference of the vector multiplicated
			 */
			const Vector2D<T>& operator*= (const T _val) {
				m_floats[0] *= _val;
				m_floats[1] *= _val;
				return *this;
			}
			/**
			 * @brief Operator* Multiplication an other vertor with this one
			 * @param[in] _obj Reference on the external object
			 * @return New vector containing the value
			 */
			Vector2D<T> operator* (const Vector2D<T>& _obj) const {
				Vector2D<T> tmpp(m_floats[0],m_floats[1]);
				tmpp.m_floats[0] *= _obj.m_floats[0];
				tmpp.m_floats[1] *= _obj.m_floats[1];
				return tmpp;
			}
			/**
			 * @brief Operator* Multiplication an other vertor with this one
			 * @param[in] _val Value to addition at x/y
			 * @return New vector containing the value
			 */
			Vector2D<T> operator* (const T _val) const {
				Vector2D<T> tmpp(m_floats[0],m_floats[1]);
				tmpp.m_floats[0] *= _val;
				tmpp.m_floats[1] *= _val;
				return tmpp;
			}
			/**
			 * @brief Operator/= Dividing an other vertor with this one
			 * @param[in] _obj Reference on the external object
			 * @return Local reference of the vector divided
			 */
			Vector2D<T> operator/ (const Vector2D<T>& _obj) const{
				Vector2D<T> tmpp(m_floats[0], m_floats[1]);
				tmpp.m_floats[0] /= _obj.m_floats[0];
				tmpp.m_floats[1] /= _obj.m_floats[1];
				return tmpp;
			}
			/**
			 * @brief Operator/= Dividing an other vertor with this one
			 * @param[in] _val Value to addition at x/y
			 * @return Local reference of the vector divided
			 */
			Vector2D<T> operator/ (const T _val) const {
				Vector2D<T> tmpp(m_floats[0], m_floats[1]);
				tmpp.m_floats[0] /= _val;
				tmpp.m_floats[1] /= _val;
				return tmpp;
			}
			/**
			 * @brief Operator/ Dividing an other vertor with this one
			 * @param[in] _obj Reference on the external object
			 * @return New vector containing the value
			 */
			const Vector2D<T>& operator/= (const Vector2D<T>& _obj) {
				m_floats[0] /= _obj.m_floats[0];
				m_floats[1] /= _obj.m_floats[1];
				return *this;
			}
			/**
			 * @brief Operator/ Dividing an other vertor with this one
			 * @param[in] _val Value to addition at x/y
			 * @return New vector containing the value
			 */
			const Vector2D<T>& operator/= (const T _val) {
				m_floats[0] /= _val;
				m_floats[1] /= _val;
				return *this;
			}
			/**
			 * @brief Operator++ Pre-incrementation of this vector
			 * @return Local reference of the vector incremented
			 */
			Vector2D<T>& operator++() {
				++m_floats[0];
				++m_floats[1];
				return *this;
			}
			/**
			 * @brief Operator++ Post-incrementation of this vector
			 * @return New vector containing the last value
			 */
			Vector2D<T> operator++(int) {
				Vector2D<T> result = *this;
				++(*this);
				return result;
			}
			/**
			 * @brief Operator++ Pre-decrementation of this vector
			 * @return Local reference of the vector incremented
			 */
			Vector2D<T>& operator--() {
				--m_floats[0];
				--m_floats[1];
				return *this;
			}
			/**
			 * @brief Operator++ Post-decrementation of this vector
			 * @return New vector containing the last value
			 */
			Vector2D<T> operator--(int) {
				Vector2D<T> result = *this;
				--(*this);
				return result;
			}
			/**
			 * @brief Return the cross product / determinant
			 * @param _obj The other vector in the cross product
			 * @return cross product value
			 */
			T cross(const Vector2D<T>& _obj) const {
				return   m_floats[0] * _obj.m_floats[1]
				       - m_floats[1] * _obj.m_floats[0];
			}
			/**
			 * @brief Return the dot product
			 * @param _obj The other vector in the dot product
			 * @return Dot product value
			 */
			T dot(const Vector2D<T>& _obj) const {
				return   m_floats[0] * _obj.m_floats[0]
				       + m_floats[1] * _obj.m_floats[1];
			}
			/**
			 * @brief Get the length of the vector squared
			 * @return Squared length value.
			 */
			T length2() const {
				return dot(*this);
			}
			/**
			 * @brief Get the length of the vector
			 * @return Length value
			 */
			float length() const {
				#if __CPP_VERSION__ >= 2011 && !defined(__STDCPP_LLVM__)
					return std::sqrt(length2());
				#else
					return sqrt(length2());
				#endif
			}
			/**
			 * @brief Return the distance squared between the ends of this and another vector
			 * This is symantically treating the vector like a point
			 * @param[in] _obj The other vector to compare distance
			 * @return the square distance of the 2 points
			 */
			T distance2(const Vector2D<T>& _obj) const {
				return (_obj - *this).length2();
			}
			/**
			 * @brief Return the distance between the ends of this and another vector
			 * This is symantically treating the vector like a point
			 * @param[in] _obj The other vector to compare distance
			 * @return the distance of the 2 points
			 */
			float distance(const Vector2D<T>& _obj) const {
				return (_obj - *this).length();
			}
			/**
			 * @brief Normalize this vector x^2 + y^2 = 1
			 * @return Local reference of the vector normalized
			 */
			Vector2D<T>& normalize() {
				*this /= length();
				return *this;
			}
			/**
			 * @brief Normalize this vector x^2 + y^2 = 1 (check if not deviding by 0, if it is the case ==> return (1,0))
			 * @return Local reference of the vector normalized
			 */
			Vector2D<T>& safeNormalize() {
				T tmp = length();
				if (tmp != 0) {
					*this /= length();
					return *this;
				}
				setValue(1,0);
				return *this;
			}
			/**
			 * @brief Return a normalized version of this vector
			 * @return New vector containing the value
			 */
			Vector2D<T> normalized() const {
				return *this / length();
			}
			/**
			 * @brief Return a vector will the absolute values of each element
			 * @return New vector containing the value
			 */
			Vector2D<T> absolute() const {
				return Vector2D<T>( abs(m_floats[0]),
				                    abs(m_floats[1]));
			}
			/**
			 * @brief Return the axis with the smallest value 
			 * @return values are 0,1 for x or y
			 */
			int32_t minAxis() const {
				return m_floats[0] < m_floats[1] ? 0 : 1;
			}
			/**
			 * @brief Return the axis with the largest value
			 * @return values are 0,1 for x or y
			 */
			int32_t maxAxis() const {
				return m_floats[0] < m_floats[1] ? 1 : 0;
			}
			/**
			 * @brief Return the axis with the smallest ABSOLUTE value
			 * @return values 0,1 for x, or z
			 */
			int32_t furthestAxis() const {
				return absolute().minAxis();
			}
			/**
			 * @brief Return the axis with the largest ABSOLUTE value
			 * @return values 0,1 for x or y
			 */
			int32_t closestAxis() const {
				return absolute().maxAxis();
			}
			/**
			 * @brief Get X value
			 * @return the x value
			 */
			const T& getX() const {
				return m_floats[0];
			}
			/**
			 * @brief Get Y value
			 * @return the y value
			 */
			const T& getY() const {
				return m_floats[1];
			}
			/**
			 * @brief Set the x value
			 * @param[in] _xxx New value
			 */
			void setX(T _xxx) {
				m_floats[0] = _xxx;
			};
			/**
			 * @brief Set the y value
			 * @param[in] _yyy New value
			 */
			void setY(T _yyy) {
				m_floats[1] = _yyy;
			};
			/**
			 * @brief Get X value
			 * @return the x value
			 */
			const T& x() const {
				return m_floats[0];
			}
			/**
			 * @brief Get Y value
			 * @return the y value
			 */
			const T& y() const {
				return m_floats[1];
			}
			/**
			 * @brief Cast the vector in the type T* requested.
			 * @return Pointer on the data
			 */
			operator T *() {
				return &m_floats[0];
			}
			/**
			 * @brief Cast the vector in the type const T* requested.
			 * @return Pointer on the const data
			 */
			operator const T *() const {
				return &m_floats[0];
			}
			/**
			 * @brief Set each element to the max of the current values and the values of another vector
			 * @param _other The other vector to compare with
			 */
			void setMax(const Vector2D<T>& _other) {
				m_floats[0] = std::max(m_floats[0], _other.m_floats[0]);
				m_floats[1] = std::max(m_floats[1], _other.m_floats[1]);
			}
			/**
			 * @brief Set each element to the min of the current values and the values of another vector
			 * @param _other The other vector to compare with
			 */
			void setMin(const Vector2D<T>& _other) {
				m_floats[0] = std::min(m_floats[0], _other.m_floats[0]);
				m_floats[1] = std::min(m_floats[1], _other.m_floats[1]);
			}
			/**
			 * @brief Set Value on the vector
			 * @param[in] _xxx X value.
			 * @param[in] _yyy Y value.
			 */
			void setValue(const T& _xxx, const T& _yyy) {
				m_floats[0] = _xxx;
				m_floats[1] = _yyy;
			}
			/**
			 * @brief Set 0 value on all the vector
			 */
			void setZero() {
				setValue(0,0);
			}
			/**
			 * @brief Check if the vector is equal to (0,0)
			 * @return true The value is equal to (0,0)
			 * @return false The value is NOT equal to (0,0)
			 */
			bool isZero() const {
				return    m_floats[0] == 0
				       && m_floats[1] == 0;
			}
			/**
			 * @brief String caster of the object.
			 * @return the Object cated in string (x.x,y.y)
			 */
			operator std::string() const;
			#if __CPP_VERSION__ >= 2011
				/**
				 * @brief String caster of the object.
				 * @return the Object cated in string (x.x,y.y)
				 */
				operator std::u32string() const;
			#endif
	};
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const etk::Vector2D<int32_t>& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const etk::Vector2D<float>& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const etk::Vector2D<uint32_t>& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const etk::Vector2D<bool>& _obj);
};
// To siplify the writing of the code ==> this permit to have the same name with the glsl language...
using   vec2 = etk::Vector2D<float>;//!< wrapper on etk::Vector2D<float> to have the same naming has OpenGL shader
using  ivec2 = etk::Vector2D<int32_t>;//!< wrapper on etk::Vector2D<int32_t> to have the same naming has OpenGL shader
// not compatible with glsl ... but it is better to have a same writing
using uivec2 = etk::Vector2D<uint32_t>;//!< wrapper on etk::Vector2D<uint32_t> to have the same naming has OpenGL shader
using  bvec2 = etk::Vector2D<bool>; //!< wrapper on etk::Vector2D<bool> to have the same naming has OpenGL shader

/**
 * @brief Limit at integer value the input vector: vec3(1.2, -2.9) ==> vec3(1.0, -2.0)
 * @param[in] _val input vector to limit
 * @return reduced range of vector
 */
inline vec2 vec2ClipInt32(const vec2& _val) {
	return vec2((int32_t)_val.x(), (int32_t)_val.y());
}
/**
 * @brief Limit at integer value the input vector: vec3(1.2, -2.9) ==> vec3(1.0, -2.0)
 * @param[in] _val input vector to limit
 * @return reduced range of vector
 */
inline vec2 vec2ClipInt64(const vec2& _val) {
	return vec2((int64_t)_val.x(), (int64_t)_val.y());
}

/**
 * @brief Rotate the vector at a specific position with a specific angle
 * @param[in] _obj Vector to rotate
 * @param[in] _point Poit to do the rotation
 * @param[in] _angle Angle in radian to rotate the vector
 * @return New vector wit totation applyed
 */
vec2 vec2rotate(const vec2& _obj, const vec2& _point, float _angle);

namespace etk {
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const std::vector<vec2 >& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const std::vector<ivec2 >& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const std::vector<uivec2 >& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const std::vector<bvec2 >& _obj);
}
