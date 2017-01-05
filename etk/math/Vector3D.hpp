/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/types.hpp>

#pragma once

#include <cmath>

#ifdef ETK_BUILD_LINEARMATH
	#include <LinearMath/btScalar.h>
	#include <LinearMath/btMinMax.h>
	#include <LinearMath/btVector3.h>
	#include <LinearMath/btQuaternion.h>
#else
	namespace etk {
		template <typename T> class Vector3D;
	};
	//! @brief compatibility with bullet lib
	typedef etk::Vector3D<float> btVector3;
#endif

namespace etk {
	/**
	 * @brief Vectorial 3-dimention vector (x/y/z)
	 */
	template <typename T> class Vector3D {
		public:
			T m_floats[4]; //!< all internal values
		public:
			/**
			 * @brief No initialization constructor (faster ...)
			 */
			Vector3D() {
				#ifdef DEBUG
					// in debug mode we set supid value to prevent forget of the inits ...
					m_floats[0] = (T)34673363;
					m_floats[1] = (T)34523535;
					m_floats[2] = (T)43523424;
					m_floats[3] = (T)23452345;
				#endif
				#if (    !defined(__TARGET_OS__MacOs) \
				      && !defined(__TARGET_OS__IOs) \
				      && defined(ETK_BUILD_LINEARMATH))
					// hide a bullet warning
					(void)btInfinityMask;
				#endif
			}
			/**
			 * @brief Constructor from scalars 
			 * @param[in] _xxx X value
			 * @param[in] _yyy Y value
			 * @param[in] _zzz Z value
			 */
			Vector3D(const T& _xxx, const T& _yyy, const T& _zzz) {
				m_floats[0] = _xxx;
				m_floats[1] = _yyy;
				m_floats[2] = _zzz;
				m_floats[3] = 0;
			}
			/**
			 * @brief Add a vector to this one 
			 * @param[in] _obj The vector to add to this one
			 * @return Local reference of the vector
			 */
			Vector3D<T>& operator+=(const Vector3D<T>& _obj) {
				m_floats[0] += _obj.m_floats[0];
				m_floats[1] += _obj.m_floats[1];
				m_floats[2] += _obj.m_floats[2];
				return *this;
			}
			/**
			 * @brief Add a vector to this one 
			 * @param[in] _obj The vector to add to this one
			 * @return New vector containing the value
			 */
			Vector3D<T> operator+(const Vector3D<T>& _obj) {
				return Vector3D<T>(m_floats[0] + _obj.m_floats[0],
				                   m_floats[1] + _obj.m_floats[1],
				                   m_floats[2] + _obj.m_floats[2]);
			}
			/**
			 * @brief Subtract a vector from this one
			 * @param[in] _obj The vector to subtract
			 * @return Local reference of the vector
			 */
			Vector3D<T>& operator-=(const Vector3D<T>& _obj) {
				m_floats[0] -= _obj.m_floats[0]; 
				m_floats[1] -= _obj.m_floats[1];
				m_floats[2] -= _obj.m_floats[2];
				return *this;
			}
			/**
			 * @brief Subtract a vector from this one
			 * @param[in] _obj The vector to subtract
			 * @return New vector containing the value
			 */
			Vector3D<T> operator-(const Vector3D<T>& _obj) {
				return Vector3D<T>(m_floats[0] - _obj.m_floats[0],
				                   m_floats[1] - _obj.m_floats[1],
				                   m_floats[2] - _obj.m_floats[2]);
			}
			/**
			 * @brief Scale the vector
			 * @param[in] _val Scale factor
			 * @return Local reference of the vector
			 */
			Vector3D<T>& operator*=(const T& _val) {
				m_floats[0] *= _val; 
				m_floats[1] *= _val;
				m_floats[2] *= _val;
				return *this;
			}
			/**
			 * @brief Scale the vector
			 * @param[in] _val Scale factor
			 * @return New vector containing the value
			 */
			Vector3D<T> operator*(const T& _val) {
				return Vector3D<T>(m_floats[0] * _val,
				                   m_floats[1] * _val,
				                   m_floats[2] * _val);
			}
			/**
			 * @brief Inversely scale the vector 
			 * @param[in] _val Scale factor to divide by
			 * @return Local reference of the vector
			 */
			Vector3D<T>& operator/=(const Vector3D<T>& _val) {
				if (_val != 0) {
					return *this *= float(1.0) / _val;
				}
				return *this;
			}
			/**
			 * @brief Inversely scale the vector 
			 * @param[in] _val Scale factor to divide by
			 * @return Local reference of the vector
			 */
			Vector3D<T>& operator/=(const T& _val) {
				if (_val != 0) {
					m_floats[0] /= _val;
					m_floats[1] /= _val;
					m_floats[2] /= _val;
					return *this;
				}
				return *this;
			}
			/**
			 * @brief Return the dot product
			 * @param[in] _obj The other vector in the dot product
			 * @return Dot product value
			 */
			float dot(const Vector3D<T>& _obj) const {
				return   m_floats[0] * _obj.m_floats[0]
				       + m_floats[1] * _obj.m_floats[1]
				       + m_floats[2] * _obj.m_floats[2];
			}
			/**
			 * @brief Get the length of the vector squared
			 * @return Squared length value.
			 */
			float length2() const {
				return dot(*this);
			}
			/**
			 * @brief Get the length of the vector
			 * @return Length value
			 */
			float length() const {
				#if __CPP_objERSION__ >= 2011 && !defined(__STDCPP_LLVM__)
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
			float distance2(const Vector3D<T>& _obj) const {
				return (_obj - *this).length2();
			}
			/**
			 * @brief Return the distance between the ends of this and another vector
			 * This is symantically treating the vector like a point
			 * @param[in] _obj The other vector to compare distance
			 * @return the distance of the 2 points
			 */
			float distance(const Vector3D<T>& _obj) const {
				return (_obj - *this).length();
			}
			/**
			 * @brief Normalize this vector x^2 + y^2 + z^2 = 1 (check if not deviding by 0, if it is the case ==> return (1,0,0))
			 * @return Local reference of the vector normalized
			 */
			Vector3D<T>& safeNormalize() {
				Vector3D<T> absVec = this->absolute();
				int maxIndex = absVec.maxAxis();
				if (absVec[maxIndex]>0) {
					*this /= absVec[maxIndex];
					return *this /= length();
				}
				setValue(1,0,0);
				return *this;
			}
			/**
			 * @brief Normalize this vector x^2 + y^2 + z^2 = 1
			 * @return Local reference of the vector normalized
			 */
			Vector3D<T>& normalize() {
				return *this /= length();
			}
			/**
			 * @brief Return a normalized version of this vector
			 * @return New vector containing the value
			 */
			Vector3D<T> normalized() const {
				Vector3D<T> out = *this;
				out /= length();
				return out;
			}
			/**
			 * @brief Return a rotated version of this vector
			 * @param[in] _wAxis The axis to rotate about
			 * @param[in] _angle The angle to rotate by
			 * @return New vector containing the value
			 */
			Vector3D<T> rotate( const Vector3D<T>& _wAxis, const float _angle ) const {
				Vector3D<T> o = _wAxis * _wAxis.dot( *this );
				Vector3D<T> x = *this - o;
				Vector3D<T> y;
				y = _wAxis.cross( *this );
				return ( o + x * cosf(_angle) + y * sinf(_angle) );
			}
			/**
			 * @brief Calculate the angle between this and another vector
			 * @param[in] _obj The other vector
			 * @return Angle in radian
			 */
			float angle(const Vector3D<T>& _obj) const {
				float s = sqrtf(length2() * _obj.length2());
				if (0!=s) {
					return acosf(dot(_obj) / s);
				}
				return 0;
			}
			/**
			 * @brief Return a vector will the absolute values of each element
			 * @return New vector containing the value
			 */
			Vector3D<T> absolute() const {
				return Vector3D<T>( abs(m_floats[0]),
				                    abs(m_floats[1]),
				                    abs(m_floats[2]));
			}
			/**
			 * @brief Return the cross product between this and another vector
			 * @param[in] _obj The other vector
			 * @return Vector with the result of the cross product
			 */
			Vector3D<T> cross(const Vector3D<T>& _obj) const {
				return Vector3D<T>(m_floats[1] * _obj.m_floats[2] - m_floats[2] * _obj.m_floats[1],
				                   m_floats[2] * _obj.m_floats[0] - m_floats[0] * _obj.m_floats[2],
				                   m_floats[0] * _obj.m_floats[1] - m_floats[1] * _obj.m_floats[0]);
			}
			/**
			 * @brief Return the triple product between this and another vector and another
			 * @param[in] _obj1 The other vector 1
			 * @param[in] _obj2 The other vector 2
			 * @return Value with the result of the triple product
			 */
			T triple(const Vector3D<T>& _obj1, const Vector3D<T>& _obj2) const {
				return   m_floats[0] * (_obj1.m_floats[1] * _obj2.m_floats[2] - _obj1.m_floats[2] * _obj2.m_floats[1])
				       + m_floats[1] * (_obj1.m_floats[2] * _obj2.m_floats[0] - _obj1.m_floats[0] * _obj2.m_floats[2])
				       + m_floats[2] * (_obj1.m_floats[0] * _obj2.m_floats[1] - _obj1.m_floats[1] * _obj2.m_floats[0]);
			}
			/**
			 * @brief Return the axis with the smallest value
			 * @return values 0,1,2 for x, y, or z
			 */
			int32_t minAxis() const {
				if (m_floats[0] < m_floats[1]) {
					return m_floats[0] < m_floats[2] ? 0 : 2;
				}
				return m_floats[1] < m_floats[2] ? 1 : 2;
			}
			/**
			 * @brief Return the axis with the largest value
			 * @return values 0,1,2 for x, y, or z
			 */
			int32_t maxAxis() const {
				if (m_floats[0] < m_floats[1]) {
					return m_floats[1] < m_floats[2] ? 2 : 1;
				}
				return m_floats[0] < m_floats[2] ? 2 : 0;
			}
			/**
			 * @brief Return the axis with the smallest ABSOLUTE value
			 * @return values 0,1,2 for x, y, or z
			 */
			int32_t furthestAxis() const {
				return absolute().minAxis();
			}
			/**
			 * @brief Return the axis with the largest ABSOLUTE value
			 * @return values 0,1,2 for x, y, or z
			 */
			int32_t closestAxis() const {
				return absolute().maxAxis();
			}
			/**
			 * @brief Interpolate the vector with a ration between 2 others
			 * @param[in] _obj0 First vector
			 * @param[in] _obj1 Second vector
			 * @param[in] _ratio Ratio between _obj0 and _obj1
			 */
			void setInterpolate3(const Vector3D<T>& _obj0, const Vector3D<T>& _obj1, T _ratio) {
				float inverse = 1.0 - _ratio;
				m_floats[0] = inverse * _obj0.m_floats[0] + _ratio * _obj1.m_floats[0];
				m_floats[1] = inverse * _obj0.m_floats[1] + _ratio * _obj1.m_floats[1];
				m_floats[2] = inverse * _obj0.m_floats[2] + _ratio * _obj1.m_floats[2];
				//		m_co[3] = s * v0[3] + rt * v1[3];
			}
			/**
			 * @brief Return the linear interpolation between this and another vector
			 * @param[in] _obj The other vector 
			 * @param[in] _ratio The ratio of this to _obj (_ratio = 0 => return copy of this, _ratio=1 => return other)
			 * @return New vector containing the value
			 */
			Vector3D<T> lerp(const Vector3D<T>& _obj, const float& _ratio) const {
				return Vector3D<T>(m_floats[0] + (_obj.m_floats[0] - m_floats[0]) * _ratio,
				                   m_floats[1] + (_obj.m_floats[1] - m_floats[1]) * _ratio,
				                   m_floats[2] + (_obj.m_floats[2] - m_floats[2]) * _ratio);
			}
			/**
			 * @brief Elementwise multiply this vector by the other
			 * @param _obj The other vector
			 * @return Local reference of the vector normalized
			 */
			Vector3D<T>& operator*=(const Vector3D<T>& _obj) {
				m_floats[0] *= _obj.m_floats[0]; 
				m_floats[1] *= _obj.m_floats[1];
				m_floats[2] *= _obj.m_floats[2];
				return *this;
			}
			/**
			 * @brief Elementwise multiply this vector by the other
			 * @param _obj The other vector
			 * @return New vector containing the value
			 */
			Vector3D<T> operator*(const Vector3D<T>& _obj) {
				return Vector3D<T>(m_floats[0] * _obj.m_floats[0],
				                   m_floats[1] * _obj.m_floats[1],
				                   m_floats[2] * _obj.m_floats[2]);
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
			 * @brief Set the x value
			 * @param[in] _x New value
			 */
			void setX(T _x) {
				m_floats[0] = _x;
			}
			/**
			 * @brief Set the y value
			 * @param[in] _y New value
			 */
			void setY(T _y) {
				m_floats[1] = _y;
			}
			/**
			 * @brief Set the z value
			 * @param[in] _z New value
			 */
			void setZ(T _z) {
				m_floats[2] = _z;
			}
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
			bool operator==(const Vector3D<T>& _obj) const {
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
			bool operator!=(const Vector3D<T>& _obj) const {
				return (    (m_floats[3] != _obj.m_floats[3])
				         || (m_floats[2] != _obj.m_floats[2])
				         || (m_floats[1] != _obj.m_floats[1])
				         || (m_floats[0] != _obj.m_floats[0]));
			}
			/**
			 * @brief Set each element to the max of the current values and the values of another Vector3D<T>
			 * @param _obj The other Vector3D<T> to compare with 
			 */
			void setMax(const Vector3D<T>& _obj) {
				btSetMax(m_floats[0], _obj.m_floats[0]);
				btSetMax(m_floats[1], _obj.m_floats[1]);
				btSetMax(m_floats[2], _obj.m_floats[2]);
				btSetMax(m_floats[3], _obj.m_floats[3]);
			}
			/**
			 * @brief Set each element to the min of the current values and the values of another Vector3D<T>
			 * @param _obj The other Vector3D<T> to compare with 
			 */
			void setMin(const Vector3D<T>& _obj) {
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
			 */
			void setValue(const T& _xxx, const T& _yyy, const T& _zzz) {
				m_floats[0]=_xxx;
				m_floats[1]=_yyy;
				m_floats[2]=_zzz;
				m_floats[3] = 0;
			}
			/**
			 * @brief Create a skew matrix of the object
			 * @param[out] _obj0 Vector matric first line
			 * @param[out] _obj1 Vector matric second line
			 * @param[out] _obj2 Vector matric third line
			 */
			void getSkewSymmetricMatrix(Vector3D<T>* _obj0,Vector3D<T>* _obj1,Vector3D<T>* _obj2) const {
				_obj0->setValue(0.   ,-z() ,y());
				_obj1->setValue(z()  ,0.   ,-x());
				_obj2->setValue(-y() ,x()  ,0.);
			}
			/**
			 * @brief Set 0 value on all the vector
			 */
			void setZero() {
				setValue(0,0,0);
			}
			/**
			 * @brief Check if the vector is equal to (0,0,0)
			 * @return true The value is equal to (0,0,0)
			 * @return false The value is NOT equal to (0,0,0)
			 */
			bool isZero() const {
				return    m_floats[0] == 0
				       && m_floats[1] == 0
				       && m_floats[2] == 0;
			}
	};
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const etk::Vector3D<int32_t>& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const etk::Vector3D<uint32_t>& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const etk::Vector3D<bool>& _obj);
};

// To siplify the writing of the code ==> this permit to have the same name with the glsl language...
#ifdef ETK_BUILD_LINEARMATH
	using vec3 = btVector3; //!< wrapper on etk::Vector3D<float> to have the same naming has OpenGL shader
#else
	using vec3 = etk::Vector3D<float>; //!< wrapper on etk::Vector3D<float> to have the same naming has OpenGL shader
#endif
using ovec3 = etk::Vector3D<float>; //!< wrapper on etk::Vector3D<float> to be complient all time with openGL internal mode (instead of vec3)
using ivec3 = etk::Vector3D<int32_t>; //!< wrapper on etk::Vector3D<int32_t> to have the same naming has OpenGL shader
// not compatible with glsl ... but it is better to have a same writing
using uivec3 = etk::Vector3D<uint32_t>; //!< wrapper on etk::Vector3D<uint32_t> to have the same naming has OpenGL shader
using bvec3 = etk::Vector3D<bool>; //!< wrapper on etk::Vector3D<bool> to have the same naming has OpenGL shader

//! @not_in_doc
std::ostream& operator <<(std::ostream& _os, const vec3& _obj);

#ifdef ETK_BUILD_LINEARMATH
	vec3 quaternionToEulerXYZ(const btQuaternion& quat);
#endif

/**
 * @brief Limit at integer value the input vector: vec3(1.2, 5.6, -2.9) ==> vec3(1.0, 5.0, -2.0)
 * @param _val input vector to limit
 * @return reduced range of vector
 */
inline vec3 vec3ClipInt32(const vec3& _val) {
	return vec3(int32_t(_val.x()), int32_t(_val.y()), int32_t(_val.z()));
}
/**
 * @brief Limit at integer value the input vector: vec3(1.2, 5.6, -2.9) ==> vec3(1.0, 5.0, -2.0)
 * @param _val input vector to limit
 * @return reduced range of vector
 */
inline vec3 vec3ClipInt64(const vec3& _val) {
	return vec3(int64_t(_val.x()), int64_t(_val.y()), int64_t(_val.z()));
}

namespace etk {
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const std::vector<vec3>& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const std::vector<ivec3>& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const std::vector<uivec3>& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const std::vector<bvec3>& _obj);
}


