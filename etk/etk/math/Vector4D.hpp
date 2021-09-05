/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/Stream.hpp>

extern "C" {
	#include <math.h>
}
#ifdef ETK_BUILD_LINEARMATH
	#include <LinearMath/btScalar.h>
	#include <LinearMath/btMinMax.h>
	#include <LinearMath/btVector3.h>
	#include <LinearMath/btQuaternion.h>
#else
	namespace etk {
		template <typename T> class Vector4D;
	};
#endif
namespace etk {
	/**
	 * @brief Vectorial 4-dimention vector (x/y/z/w)
	 */
	template <typename T> class Vector4D {
		public:
			T m_floats[4]; //!< all internal values
		public:
			/**
			 * @brief No initialization constructor (faster ...)
			 */
			Vector4D() {
				#ifdef DEBUG
					// in debug mode we set supid value to prevent forget of the inits ...
					m_floats[0] = T(34673363);
					m_floats[1] = T(34523535);
					m_floats[2] = T(43523424);
					m_floats[3] = T(23452345);
				#endif
			}
			/**
			 * @brief Constructor from scalars.
			 * @param _xxx X value
			 * @param _yyy Y value
			 * @param _zzz Z value
			 * @param _www W value
			 */
			Vector4D(const T& _xxx, const T& _yyy, const T& _zzz, const T& _www) {
				m_floats[0] = _xxx;
				m_floats[1] = _yyy;
				m_floats[2] = _zzz;
				m_floats[3] = _www;
			}
			/**
			 * @brief Add a vector to this one.
			 * @param[in] _obj The vector to add to this one
			 * @return Local reference of the vector
			 */
			Vector4D<T>& operator+=(const Vector4D<T>& _obj) {
				m_floats[0] += _obj.m_floats[0];
				m_floats[1] += _obj.m_floats[1];
				m_floats[2] += _obj.m_floats[2];
				m_floats[3] += _obj.m_floats[3];
				return *this;
			}
			/**
			 * @brief Add a vector to this one.
			 * @param[in] _obj The vector to add to this one
			 * @return New vector containing the value
			 */
			Vector4D<T> operator+(const Vector4D<T>& _obj) {
				return Vector4D<T>(m_floats[0] + _obj.m_floats[0],
				                   m_floats[1] + _obj.m_floats[1],
				                   m_floats[2] + _obj.m_floats[2],
				                   m_floats[3] + _obj.m_floats[3]);
			}
			/**
			 * @brief Subtract a vector from this one
			 * @param _obj The vector to subtract
			 * @return Local reference of the vector
			 */
			Vector4D<T>& operator-=(const Vector4D<T>& _obj) {
				m_floats[0] -= _obj.m_floats[0];
				m_floats[1] -= _obj.m_floats[1];
				m_floats[2] -= _obj.m_floats[2];
				m_floats[3] -= _obj.m_floats[3];
				return *this;
			}
			/**
			 * @brief Subtract a vector from this one
			 * @param _obj The vector to subtract
			 * @return New vector containing the value
			 */
			Vector4D<T> operator-(const Vector4D<T>& _obj) {
				return Vector4D<T>(m_floats[0] - _obj.m_floats[0],
				                   m_floats[1] - _obj.m_floats[1],
				                   m_floats[2] - _obj.m_floats[2],
				                   m_floats[3] - _obj.m_floats[3]);
			}
			/**
			 * @brief Scale the vector
			 * @param[in] _val Scale factor
			 * @return Local reference of the vector
			 */
			Vector4D<T>& operator*=(const T& _val) {
				m_floats[0] *= _val;
				m_floats[1] *= _val;
				m_floats[2] *= _val;
				m_floats[3] *= _val;
				return *this;
			}
			/**
			 * @brief Scale the vector
			 * @param[in] _val Scale factor
			 * @return New vector containing the value
			 */
			Vector4D<T> operator*(const T& _val) {
				return Vector4D<T>(m_floats[0] * _val,
				                   m_floats[1] * _val,
				                   m_floats[2] * _val,
				                   m_floats[3] * _val);
			}
			/**
			 * @brief Inversely scale the vector
			 * @param[in] _val Scale factor to divide by.
			 * @return Local reference of the vector
			 */
			Vector4D<T>& operator/=(const T& _val) {
				if (_val != 0) {
					m_floats[0] /= _val;
					m_floats[1] /= _val;
					m_floats[2] /= _val;
					m_floats[3] /= _val;
					return *this;
				}
				return *this;
			}
			/**
			 * @brief Inversely scale the vector
			 * @param[in] _val Scale factor to divide by.
			 * @return New vector containing the value
			 */
			Vector4D<T> operator/(const T& _val) {
				if (_val != 0) {
					return Vector4D<T>(m_floats[0] / _val,
					                   m_floats[1] / _val,
					                   m_floats[2] / _val,
					                   m_floats[3] / _val);
				}
				return *this;
			}
			/**
			 * @brief Return the dot product
			 * @param _obj The other vector in the dot product
			 * @return Dot result value
			 */
			float dot(const Vector4D<T>& _obj) const {
				return	m_floats[0] * _obj.m_floats[0] + 
						m_floats[1] * _obj.m_floats[1] + 
						m_floats[2] * _obj.m_floats[2] + 
						m_floats[3] * _obj.m_floats[3];
			}
			/**
			 * @brief Return the squared length of the vector.
			 * @return Squared length value.
			 */
			float length2() const {
				return dot(*this);
			}
			/**
			 * @brief Return the length of the vector
			 * @return Length value
			 */
			float length() const {
				#ifdef ETK_BUILD_LINEARMATH
					return btSqrt(length2());
				#else
					#if __CPP_VERSION__ >= 2011 && !defined(__TARGET_OS__MacOs) && !defined(__TARGET_OS__IOs)
						return etk::sqrt(length2());
					#else
						return sqrt(length2());
					#endif
				#endif
			}
			/**
			 * @brief Return the distance squared between the ends of this and another vector
			 * This is symantically treating the vector like a point
			 * @param[in] _obj The other vector to compare distance
			 * @return the square distance of the 2 points
			 */
			float distance2(const Vector4D<T>& _obj) const {
				return (_obj - *this).length2();
			}
			/**
			 * @brief Return the distance between the ends of this and another vector
			 * This is symantically treating the vector like a point
			 * @param[in] _obj The other vector to compare distance
			 * @return the distance of the 2 points
			 */
			float distance(const Vector4D<T>& _obj) const {
				return (_obj - *this).length();
			}
			/**
			 * @brief Normalize this vector x^2 + y^2 + z^2 + w^2 = 1
			 * @return Local reference of the vector normalized
			 */
			Vector4D<T>& normalize() {
				return *this /= length();
			}
			/**
			 * @brief Return a normalized version of this vector
			 * @return New vector containing the value
			 */
			Vector4D<T> normalized() const {
				return *this / length();
			}
			/**
			 * @brief Return a vector will the absolute values of each element
			 * @return New vector with the absolute value
			 */
			Vector4D<T> absolute() const {
				return Vector4D<T>( etk::abs(m_floats[0]),
				                    etk::abs(m_floats[1]),
				                    etk::abs(m_floats[2]),
				                    etk::abs(m_floats[3]));
			}
			/**
			 * @brief Multiply this vector by the other.
			 * @param _obj The other vector
			 * @return Local reference of the vector
			 */
			Vector4D<T>& operator*=(const Vector4D<T>& _obj) {
				m_floats[0] *= _obj.m_floats[0];
				m_floats[1] *= _obj.m_floats[1];
				m_floats[2] *= _obj.m_floats[2];
				m_floats[3] *= _obj.m_floats[3];
				return *this;
			}
			/**
			 * @brief Multiply this vector by the other.
			 * @param _obj The other vector
			 * @return New vector containing the value
			 */
			Vector4D<T> operator*(const Vector4D<T>& _obj) {
				return Vector4D<T>(m_floats[0] * _obj.m_floats[0],
				                   m_floats[1] * _obj.m_floats[1],
				                   m_floats[2] * _obj.m_floats[2],
				                   m_floats[3] * _obj.m_floats[3]);
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
			 * @brief Get Z value
			 * @return the z value
			 */
			const T& getZ() const {
				return m_floats[2];
			}
			/**
			 * @brief Get W value
			 * @return the w value
			 */
			const T& getW() const {
				return m_floats[3];
			}
			/**
			 * @brief Set the x value
			 * @param[in] _x New value
			 */
			void setX(T _x) {
				m_floats[0] = _x;
			};
			/**
			 * @brief Set the y value
			 * @param[in] _y New value
			 */
			void setY(T _y) {
				m_floats[1] = _y;
			};
			/**
			 * @brief Set the z value
			 * @param[in] _z New value
			 */
			void setZ(T _z) {
				m_floats[2] = _z;
			};
			/**
			 * @brief Set the w value
			 * @param[in] _w New value
			 */
			void setW(T _w) {
				m_floats[3] = _w;
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
			 * @brief Get Z value
			 * @return the z value
			 */
			const T& z() const {
				return m_floats[2];
			}
			/**
			 * @brief Get W value
			 * @return the w value
			 */
			const T& w() const {
				return m_floats[3];
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
			 * @brief Equality compare operator with an other object.
			 * @param[in] _obj Reference on the comparing object
			 * @return true The Objects are identical
			 * @return false The Objects are NOT identical
			 */
			bool operator==(const Vector4D<T>& _obj) const {
				return (    (m_floats[3] == _obj.m_floats[3])
				         && (m_floats[2] == _obj.m_floats[2])
				         && (m_floats[1] == _obj.m_floats[1])
				         && (m_floats[0] == _obj.m_floats[0]));
			}
			/**
			 * @brief In-Equality compare operator with an other object.
			 * @param[in] _obj Reference on the comparing object
			 * @return true The Objects are NOT identical
			 * @return false The Objects are identical
			 */
			bool operator!=(const Vector4D<T>& _obj) const {
				return (    (m_floats[3] != _obj.m_floats[3])
				         || (m_floats[2] != _obj.m_floats[2])
				         || (m_floats[1] != _obj.m_floats[1])
				         || (m_floats[0] != _obj.m_floats[0]));
			}
			/**
			 * @brief Set each element to the max of the current values and the values of another Vector
			 * @param _obj The other Vector to compare with
			 */
			void setMax(const Vector4D<T>& _obj) {
				btSetMax(m_floats[0], _obj.m_floats[0]);
				btSetMax(m_floats[1], _obj.m_floats[1]);
				btSetMax(m_floats[2], _obj.m_floats[2]);
				btSetMax(m_floats[3], _obj.m_floats[3]);
			}
			/**
			 * @brief Set each element to the min of the current values and the values of another Vector
			 * @param _obj The other Vector to compare with
			 */
			void setMin(const Vector4D<T>& _obj) {
				btSetMin(m_floats[0], _obj.m_floats[0]);
				btSetMin(m_floats[1], _obj.m_floats[1]);
				btSetMin(m_floats[2], _obj.m_floats[2]);
				btSetMin(m_floats[3], _obj.m_floats[3]);
			}
			/**
			 * @brief Set Value on the vector
			 * @param[in] _xxx X value.
			 * @param[in] _yyy Y value.
			 * @param[in] _zzz Z value.
			 * @param[in] _www W value.
			 */
			void setValue(const T& _xxx, const T& _yyy, const T& _zzz, const T& _www) {
				m_floats[0]=_xxx;
				m_floats[1]=_yyy;
				m_floats[2]=_zzz;
				m_floats[3]=_www;
			}
			/**
			 * @brief Set 0 value on all the vector
			 */
			void setZero() {
				setValue(0,0,0,0);
			}
			/**
			 * @brief Check if the vector is equal to (0,0,0,0)
			 * @return true The value is equal to (0,0,0,0)
			 * @return false The value is NOT equal to (0,0,0,0)
			 */
			bool isZero() const {
				return    m_floats[0] == 0
				       && m_floats[1] == 0
				       && m_floats[2] == 0
				       && m_floats[3] == 0;
			}
	};
	//! @not_in_doc
	etk::Stream& operator <<(etk::Stream& _os, const etk::Vector4D<int32_t>& _obj);
	//! @not_in_doc
	etk::Stream& operator <<(etk::Stream& _os, const etk::Vector4D<float>& _obj);
	//! @not_in_doc
	etk::Stream& operator <<(etk::Stream& _os, const etk::Vector4D<uint32_t>& _obj);
	//! @not_in_doc
	etk::Stream& operator <<(etk::Stream& _os, const etk::Vector4D<bool>& _obj);
}

// To siplify the writing of the code ==> this permit to have the same name with the glsl language...
using vec4 = etk::Vector4D<float>; //!< wrapper on etk::Vector4D<float> to have the same naming has OpenGL shader
using ivec4 = etk::Vector4D<int32_t>; //!< wrapper on etk::Vector4D<int32_t> to have the same naming has OpenGL shader
// not compatible with glsl ... but it is better to have a same writing
using uivec4 = etk::Vector4D<uint32_t>; //!< wrapper on etk::Vector4D<uint32_t> to have the same naming has OpenGL shader
using bvec4 = etk::Vector4D<bool>; //!< wrapper on etk::Vector4D<bool> to have the same naming has OpenGL shader


