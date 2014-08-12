/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <etk/types.h>

#ifndef __ETK_MATH_VECTOR3D_H__
#define __ETK_MATH_VECTOR3D_H__

#include <etk/debug.h>
#include <math.h>
#include <LinearMath/btScalar.h>
#include <LinearMath/btMinMax.h>
#include <LinearMath/btVector3.h>
#include <LinearMath/btQuaternion.h>

namespace etk {
	template <typename T> class Vector3D {
		public:
			T m_floats[4];
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
				// hide a bullet warning
				(void)btInfinityMask;
			}
			/**
			 * @brief Constructor from scalars 
			 * @param _x X value
			 * @param _y Y value 
			 * @param _z Z value 
			 */
			Vector3D(const T& _x, const T& _y, const T& _z) {
				m_floats[0] = _x;
				m_floats[1] = _y;
				m_floats[2] = _z;
				m_floats[3] = 0;
			}
			
			/**
			 * @brief Add a vector to this one 
			 * @param _v The vector to add to this one
			 */
			Vector3D<T>& operator+=(const Vector3D<T>& _v) {
				m_floats[0] += _v.m_floats[0];
				m_floats[1] += _v.m_floats[1];
				m_floats[2] += _v.m_floats[2];
				return *this;
			}
			//! @previous
			Vector3D<T> operator+(const Vector3D<T>& _v) {
				return Vector3D<T>(m_floats[0] + _v.m_floats[0],
				                   m_floats[1] + _v.m_floats[1],
				                   m_floats[2] + _v.m_floats[2]);
			}
			
			
			/**
			 * @brief Subtract a vector from this one
			 * @param _v The vector to subtract
			 */
			Vector3D<T>& operator-=(const Vector3D<T>& _v) {
				m_floats[0] -= _v.m_floats[0]; 
				m_floats[1] -= _v.m_floats[1];
				m_floats[2] -= _v.m_floats[2];
				return *this;
			}
			//! @previous
			Vector3D<T> operator-(const Vector3D<T>& _v) {
				return Vector3D<T>(m_floats[0] - _v.m_floats[0],
				                   m_floats[1] - _v.m_floats[1],
				                   m_floats[2] - _v.m_floats[2]);
			}
			
			/**
			 * @brief Scale the vector
			 * @param _s Scale factor
			 */
			Vector3D<T>& operator*=(const T& _s) {
				m_floats[0] *= _s; 
				m_floats[1] *= _s;
				m_floats[2] *= _s;
				return *this;
			}
			//! @previous
			Vector3D<T> operator*(const T& _s) {
				return Vector3D<T>(m_floats[0] * _s,
				                   m_floats[1] * _s,
				                   m_floats[2] * _s);
			}
			
			/**
			 * @brief Inversely scale the vector 
			 * @param _s Scale factor to divide by
			 */
			Vector3D<T>& operator/=(const Vector3D<T>& _s) {
				if (_s != 0) {
					return *this *= btScalar(1.0) / _s;
				}
				return *this;
			}
			//! @previous
			Vector3D<T>& operator/=(const T& _s) {
				if (_s != 0) {
					m_floats[0] /= _s;
					m_floats[1] /= _s;
					m_floats[2] /= _s;
					return *this;
				}
				return *this;
			}
			
			/**
			 * @brief Return the dot product
			 * @param _v The other vector in the dot product
			 */
			btScalar dot(const Vector3D<T>& _v) const {
				return   m_floats[0] * _v.m_floats[0]
				       + m_floats[1] * _v.m_floats[1]
				       + m_floats[2] * _v.m_floats[2];
			}
			
			/**
			 * @brief Return the length of the vector squared
			 */
			btScalar length2() const {
				return dot(*this);
			}
			
			/**
			 * @brief Return the length of the vector
			 */
			btScalar length() const {
				return btSqrt(length2());
			}
			
			/**
			 * @brief Return the distance squared between the ends of this and another vector
			 * This is symantically treating the vector like a point
			 */
			btScalar distance2(const btVector3& _v) const {
				return (_v - *this).length2();
			}
			
			/**
			 * @brief Return the distance between the ends of this and another vector
			 * This is symantically treating the vector like a point
			 */
			btScalar distance(const btVector3& _v) const {
				return (_v - *this).length();
			}
			
			Vector3D<T>& safeNormalize() {
				Vector3D<T> absVec = this->absolute();
				int maxIndex = absVec.maxAxis();
				if (absVec[maxIndex]>0)
				{
					*this /= absVec[maxIndex];
					return *this /= length();
				}
				setValue(1,0,0);
				return *this;
			}
			
			/**
			 * @brief Normalize this vector 
			 * x^2 + y^2 + z^2 = 1
			 */
			Vector3D<T>& normalize() {
				return *this /= length();
			}
			
			/**
			 * @brief Return a normalized version of this vector
			 */
			Vector3D<T> normalized() const {
				return *this / length();
			}
			
			/**
			 * @brief Return a rotated version of this vector
			 * @param _wAxis The axis to rotate about
			 * @param _angle The angle to rotate by
			 */
			Vector3D<T> rotate( const Vector3D<T>& _wAxis, const btScalar _angle ) const {
				Vector3D<T> o = _wAxis * _wAxis.dot( *this );
				Vector3D<T> x = *this - o;
				Vector3D<T> y;
				y = _wAxis.cross( *this );
				return ( o + x * cosf(_angle) + y * sinf(_angle) );
			}
			
			/**
			 * @brief Return the angle between this and another vector
			 * @param _v The other vector
			 */
			btScalar angle(const Vector3D<T>& _v) const {
				btScalar s = sqrtf(length2() * _v.length2());
				if (0!=s) {
					return acosf(dot(_v) / s);
				}
				return 0;
			}
			
			/**
			 * @brief Return a vector will the absolute values of each element
			 */
			Vector3D<T> absolute() const {
				return Vector3D<T>( abs(m_floats[0]),
				                    abs(m_floats[1]),
				                    abs(m_floats[2]));
			}
			
			/**
			 * @brief Return the cross product between this and another vector
			 * @param _v The other vector
			 */
			Vector3D<T> cross(const Vector3D<T>& _v) const {
				return Vector3D<T>(m_floats[1] * _v.m_floats[2] - m_floats[2] * _v.m_floats[1],
				                   m_floats[2] * _v.m_floats[0] - m_floats[0] * _v.m_floats[2],
				                   m_floats[0] * _v.m_floats[1] - m_floats[1] * _v.m_floats[0]);
			}
			
			T triple(const Vector3D<T>& _v1, const Vector3D<T>& _v2) const {
				return   m_floats[0] * (_v1.m_floats[1] * _v2.m_floats[2] - _v1.m_floats[2] * _v2.m_floats[1])
				       + m_floats[1] * (_v1.m_floats[2] * _v2.m_floats[0] - _v1.m_floats[0] * _v2.m_floats[2])
				       + m_floats[2] * (_v1.m_floats[0] * _v2.m_floats[1] - _v1.m_floats[1] * _v2.m_floats[0]);
			}
			
			/**
			 * @brief Return the axis with the smallest value 
			 * Note return values are 0,1,2 for x, y, or z
			 */
			int32_t minAxis() const {
				if (m_floats[0] < m_floats[1]) {
					return m_floats[0] < m_floats[2] ? 0 : 2;
				}
				return m_floats[1] < m_floats[2] ? 1 : 2;
			}
			
			/**
			 * @brief Return the axis with the largest value
			 * Note return values are 0,1,2 for x, y, or z
			 */
			int32_t maxAxis() const {
				if (m_floats[0] < m_floats[1]) {
					return m_floats[1] < m_floats[2] ? 2 : 1;
				}
				return m_floats[0] < m_floats[2] ? 2 : 0;
			}
			
			int32_t furthestAxis() const {
				return absolute().minAxis();
			}
			
			int32_t closestAxis() const {
				return absolute().maxAxis();
			}
			
			void setInterpolate3(const Vector3D<T>& _v0, const Vector3D<T>& _v1, T _rt) {
				btScalar s = 1.0 - _rt;
				m_floats[0] = s * _v0.m_floats[0] + _rt * _v1.m_floats[0];
				m_floats[1] = s * _v0.m_floats[1] + _rt * _v1.m_floats[1];
				m_floats[2] = s * _v0.m_floats[2] + _rt * _v1.m_floats[2];
				//don't do the unused w component
				//		m_co[3] = s * v0[3] + rt * v1[3];
			}
			
			/**
			 * @brief Return the linear interpolation between this and another vector 
			 * @param _v The other vector 
			 * @param _t The ration of this to v (t = 0 => return this, t=1 => return other)
			 */
			Vector3D<T> lerp(const Vector3D<T>& _v, const btScalar& _t) const {
				return Vector3D<T>(m_floats[0] + (_v.m_floats[0] - m_floats[0]) * _t,
				                   m_floats[1] + (_v.m_floats[1] - m_floats[1]) * _t,
				                   m_floats[2] + (_v.m_floats[2] - m_floats[2]) * _t);
			}
			
			/**
			 * @brief Elementwise multiply this vector by the other 
			 * @param _v The other vector
			 */
			Vector3D<T>& operator*=(const Vector3D<T>& _v) {
				m_floats[0] *= _v.m_floats[0]; 
				m_floats[1] *= _v.m_floats[1];
				m_floats[2] *= _v.m_floats[2];
				return *this;
			}
			//! @previous
			Vector3D<T> operator*(const Vector3D<T>& _v) {
				return Vector3D<T>(m_floats[0] * _v.m_floats[0],
				                   m_floats[1] * _v.m_floats[1],
				                   m_floats[2] * _v.m_floats[2]);
			}
			
			/**
			 * @brief Return the x value
			 */
			const T& getX() const {
				return m_floats[0];
			}
			/**
			 * @brief Return the y value
			 */
			const T& getY() const {
				return m_floats[1];
			}
			/**
			 * @brief Return the z value
			 */
			const T& getZ() const {
				return m_floats[2];
			}
			/**
			 * @brief Set the x value
			 */
			void setX(T _x) {
				m_floats[0] = _x;
			};
			/**
			 * @brief Set the y value
			 */
			void setY(T _y) {
				m_floats[1] = _y;
			};
			/**
			 * @brief Set the z value
			 */
			void setZ(T _z) {
				m_floats[2] = _z;
			};
			/**
			 * @brief Set the w value
			 */
			void setW(T _w) {
				m_floats[3] = _w;
			};
			/**
			 * @brief Return the x value
			 */
			const T& x() const {
				return m_floats[0];
			}
			/**
			 * @brief Return the y value
			 */
			const T& y() const {
				return m_floats[1];
			}
			/**
			 * @brief Return the z value
			 */
			const T& z() const {
				return m_floats[2];
			}
			/**
			 * @brief Return the w value
			 */
			const T& w() const {
				return m_floats[3];
			}
			
			operator T *() {
				return &m_floats[0];
			}
			//! @previous
			operator const T *() const {
				return &m_floats[0];
			}
			
			bool operator==(const Vector3D<T>& _other) const {
				return (    (m_floats[3] == _other.m_floats[3])
				         && (m_floats[2] == _other.m_floats[2])
				         && (m_floats[1] == _other.m_floats[1])
				         && (m_floats[0] == _other.m_floats[0]));
			}
			
			bool operator!=(const Vector3D<T>& _other) const {
				return (    (m_floats[3] != _other.m_floats[3])
				         || (m_floats[2] != _other.m_floats[2])
				         || (m_floats[1] != _other.m_floats[1])
				         || (m_floats[0] != _other.m_floats[0]));
			}
			
			/**
			 * @brief Set each element to the max of the current values and the values of another btVector3
			 * @param _other The other btVector3 to compare with 
			 */
			void setMax(const Vector3D<T>& _other) {
				btSetMax(m_floats[0], _other.m_floats[0]);
				btSetMax(m_floats[1], _other.m_floats[1]);
				btSetMax(m_floats[2], _other.m_floats[2]);
				btSetMax(m_floats[3], _other.m_floats[3]);
			}
			
			/**
			 * @brief Set each element to the min of the current values and the values of another btVector3
			 * @param _other The other btVector3 to compare with 
			 */
			void setMin(const Vector3D<T>& _other) {
				btSetMin(m_floats[0], _other.m_floats[0]);
				btSetMin(m_floats[1], _other.m_floats[1]);
				btSetMin(m_floats[2], _other.m_floats[2]);
				btSetMin(m_floats[3], _other.m_floats[3]);
			}
			
			void setValue(const T& _x, const T& _y, const T& _z) {
				m_floats[0]=_x;
				m_floats[1]=_y;
				m_floats[2]=_z;
				m_floats[3] = 0;
			}
			
			void getSkewSymmetricMatrix(Vector3D<T>* _v0,Vector3D<T>* _v1,Vector3D<T>* _v2) const {
				_v0->setValue(0.   ,-z() ,y());
				_v1->setValue(z()  ,0.   ,-x());
				_v2->setValue(-y() ,x()  ,0.);
			}
			
			void setZero() {
				setValue(0,0,0);
			}
			
			bool isZero() const {
				return m_floats[0] == 0 && m_floats[1] == 0 && m_floats[2] == 0;
			}
	};
	/**
	 * @brief Debug operator To display the curent element in a Human redeable information
	 */
	std::ostream& operator <<(std::ostream& _os, const etk::Vector3D<int32_t>& _obj);
	//! @previous
	std::ostream& operator <<(std::ostream& _os, const btVector3& _obj);
	//! @previous
	std::ostream& operator <<(std::ostream& _os, const etk::Vector3D<uint32_t>& _obj);
	//! @previous
	std::ostream& operator <<(std::ostream& _os, const etk::Vector3D<bool>& _obj);
	
};

// To siplify the writing of the code ==> this permit to have the same name with the glsl language...
typedef btVector3                 vec3;
typedef etk::Vector3D<float>     ovec3;  // specific for OpenGL ... ==> never change this ...
typedef etk::Vector3D<int32_t>   ivec3;
// not compatible with glsl ... but it is better to have a same writing
typedef etk::Vector3D<uint32_t> uivec3;
typedef etk::Vector3D<bool>      bvec3;


vec3 quaternionToEulerXYZ(const btQuaternion& quat);

inline vec3 vec3ClipInt32(const vec3& val) {
	return vec3((int32_t)val.x(), (int32_t)val.y(), (int32_t)val.z());
}
inline vec3 vec3ClipInt64(const vec3& val) {
	return vec3((int64_t)val.x(), (int64_t)val.y(), (int64_t)val.z());
}

namespace std {
	std::string to_string(const vec3& _obj);
	std::string to_string(const bvec3& _obj);
	std::string to_string(const ivec3& _obj);
	std::string to_string(const uivec3& _obj);
	std::u32string to_u32string(const vec3& _obj);
	std::u32string to_u32string(const bvec3& _obj);
	std::u32string to_u32string(const ivec3& _obj);
	std::u32string to_u32string(const uivec3& _obj);
	bool from_string(vec3& _variableRet, const std::string& _value);
	bool from_string(bvec3& _variableRet, const std::string& _value);
	bool from_string(ivec3& _variableRet, const std::string& _value);
	bool from_string(uivec3& _variableRet, const std::string& _value);
	bool from_string(vec3& _variableRet, const std::u32string& _value);
	bool from_string(bvec3& _variableRet, const std::u32string& _value);
	bool from_string(ivec3& _variableRet, const std::u32string& _value);
	bool from_string(uivec3& _variableRet, const std::u32string& _value);
};

namespace etk {
	std::ostream& operator <<(std::ostream& _os, const std::vector<vec3>& _obj);
	//! @previous
	std::ostream& operator <<(std::ostream& _os, const std::vector<ivec3>& _obj);
	//! @previous
	std::ostream& operator <<(std::ostream& _os, const std::vector<uivec3>& _obj);
	//! @previous
	std::ostream& operator <<(std::ostream& _os, const std::vector<bvec3>& _obj);
};

#endif

