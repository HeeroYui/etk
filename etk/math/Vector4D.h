/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <etk/types.h>

#include <math.h>
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
	template <typename T> class Vector4D {
		public:
			T m_floats[4];
		public:
			/**
			 * @brief No initialization constructor (faster ...)
			 */
			Vector4D() {
				#ifdef DEBUG
					// in debug mode we set supid value to prevent forget of the inits ...
					m_floats[0] = (T)34673363;
					m_floats[1] = (T)34523535;
					m_floats[2] = (T)43523424;
					m_floats[3] = (T)23452345;
				#endif
			}
			/**
			 * @brief Constructor from scalars 
			 * @param x X value
			 * @param y Y value 
			 * @param z Z value 
			 */
			Vector4D(const T& _x, const T& _y, const T& _z, const T& _w) {
				m_floats[0] = _x;
				m_floats[1] = _y;
				m_floats[2] = _z;
				m_floats[3] = _w;
			}
			
			/**
			 * @brief Add a vector to this one 
			 * @param The vector to add to this one
			 */
			Vector4D<T>& operator+=(const Vector4D<T>& v) {
				m_floats[0] += v.m_floats[0];
				m_floats[1] += v.m_floats[1];
				m_floats[2] += v.m_floats[2];
				m_floats[3] += v.m_floats[3];
				return *this;
			}
			Vector4D<T> operator+(const Vector4D<T>& v) {
				return Vector4D<T>(m_floats[0] + v.m_floats[0],
				                   m_floats[1] + v.m_floats[1],
				                   m_floats[2] + v.m_floats[2],
				                   m_floats[3] + v.m_floats[3]);
			}
			
			
			/**
			 * @brief Subtract a vector from this one
			 * @param The vector to subtract
			 */
			Vector4D<T>& operator-=(const Vector4D<T>& v) {
				m_floats[0] -= v.m_floats[0];
				m_floats[1] -= v.m_floats[1];
				m_floats[2] -= v.m_floats[2];
				m_floats[3] -= v.m_floats[3];
				return *this;
			}
			Vector4D<T> operator-(const Vector4D<T>& v) {
				return Vector4D<T>(m_floats[0] - v.m_floats[0],
				                   m_floats[1] - v.m_floats[1],
				                   m_floats[2] - v.m_floats[2],
				                   m_floats[3] - v.m_floats[3]);
			}
			
			/**
			 * @brief Scale the vector
			 * @param s Scale factor
			 */
			Vector4D<T>& operator*=(const T& s) {
				m_floats[0] *= s; 
				m_floats[1] *= s;
				m_floats[2] *= s;
				m_floats[3] *= s;
				return *this;
			}
			Vector4D<T> operator*(const T& s) {
				return Vector4D<T>(m_floats[0] * s,
				                   m_floats[1] * s,
				                   m_floats[2] * s,
				                   m_floats[3] * s);
			}
			
			/**
			 * @brief Inversely scale the vector 
			 * @param s Scale factor to divide by
			 */
			Vector4D<T>& operator/=(const Vector4D<T>& s) {
				if (0!=s) {
					return *this *= 1.0f / s;
				}
				return *this;
			}
			Vector4D<T>& operator/=(const T& s) {
				if (0!=s) {
					m_floats[0]/=s;
					m_floats[1]/=s;
					m_floats[2]/=s;
					m_floats[3]/=s;
					return *this;
				}
				return *this;
			}
			
			/**
			 * @brief Return the dot product
			 * @param v The other vector in the dot product
			 */
			float dot(const Vector4D<T>& v) const {
				return	m_floats[0] * v.m_floats[0] + 
						m_floats[1] * v.m_floats[1] + 
						m_floats[2] * v.m_floats[2] + 
						m_floats[3] * v.m_floats[3];
			}
			
			/**
			 * @brief Return the length of the vector squared
			 */
			float length2() const {
				return dot(*this);
			}
			
			/**
			 * @brief Return the length of the vector
			 */
			float length() const {
				#ifdef ETK_BUILD_LINEARMATH
					return btSqrt(length2());
				#else
					#if __CPP_VERSION__ >= 2011 && !defined(__TARGET_OS__MacOs) && !defined(__TARGET_OS__IOs)
						return std::sqrt(length2());
					#else
						return sqrt(length2());
					#endif
				#endif
			}
			
			/**
			 * @brief Return the distance squared between the ends of this and another vector
			 * This is symantically treating the vector like a point
			 */
			float distance2(const Vector4D<T>& v) const {
				return (v - *this).length2();
			}
			
			/**
			 * @brief Return the distance between the ends of this and another vector
			 * This is symantically treating the vector like a point
			 */
			float distance(const Vector4D<T>& v) const {
				return (v - *this).length();
			}
			/*
			Vector4D<T>& safeNormalize()  {
				Vector4D<T> absVec = this->absolute();
				int maxIndex = absVec.maxAxis();
				if (absVec[maxIndex]>0)
				{
					*this /= absVec[maxIndex];
					return *this /= length();
				}
				setValue(1,0,0);
				return *this;
			}
			*/
			/**
			 * @brief Normalize this vector 
			 * x^2 + y^2 + z^2 = 1
			 */
			Vector4D<T>& normalize()  {
				return *this /= length();
			}
			
			/**
			 * @brief Return a normalized version of this vector
			 */
			Vector4D<T> normalized() const {
				return *this / length();
			}
			
			/**
			 * @brief Return a rotated version of this vector
			 * @param wAxis The axis to rotate about
			 * @param angle The angle to rotate by
			 */
			 /*
			Vector4D<T> rotate( const Vector3D<T>& wAxis, const btScalar angle ) const {
				Vector4D<T> o = wAxis * wAxis.dot( *this );
				Vector4D<T> _x = *this - o;
				Vector4D<T> _y;
				_y = wAxis.cross( *this );
				return ( o + _x * cosf(angle) + _y * sinf(angle) );
			}
			*/
			/**
			 * @brief Return the angle between this and another vector
			 * @param v The other vector
			 */
			/*
			btScalar angle(const Vector3D<T>& v) const {
				btScalar s = sqrtf(length2() * v.length2());
				if (0!=s) {
					return acosf(dot(v) / s);
				}
				return 0;
			}
			*/
			/**
			 * @brief Return a vector will the absolute values of each element
			 */
			Vector4D<T> absolute() const {
				return Vector4D<T>( abs(m_floats[0]),
				                    abs(m_floats[1]),
				                    abs(m_floats[2]),
				                    abs(m_floats[3]));
			}
			
			/**
			 * @brief Return the cross product between this and another vector
			 * @param v The other vector
			 */
			 /*
			Vector4D<T> cross(const Vector4D<T>& v) const {
				return Vector4D<T>(m_floats[1] * v.m_floats[2] - m_floats[2] * v.m_floats[1],
				                   m_floats[2] * v.m_floats[0] - m_floats[0] * v.m_floats[2],
				                   m_floats[0] * v.m_floats[1] - m_floats[1] * v.m_floats[0]);
			}
			
			T triple(const Vector4D<T>& v1, const Vector4D<T>& v2) const {
				return   m_floats[0] * (v1.m_floats[1] * v2.m_floats[2] - v1.m_floats[2] * v2.m_floats[1])
				       + m_floats[1] * (v1.m_floats[2] * v2.m_floats[0] - v1.m_floats[0] * v2.m_floats[2])
				       + m_floats[2] * (v1.m_floats[0] * v2.m_floats[1] - v1.m_floats[1] * v2.m_floats[0]);
			}
			*/
			/**
			 * @brief Return the axis with the smallest value 
			 * Note return values are 0,1,2 for x, y, or z
			 */
			/*
			int32_t minAxis() const {
				return m_floats[0] < m_floats[1] ? (m_floats[0] <m_floats[2] ? 0 : 2) : (m_floats[1] <m_floats[2] ? 1 : 2);
			}
			*/
			/**
			 * @brief Return the axis with the largest value
			 * Note return values are 0,1,2 for x, y, or z
			 */
			/*
			int32_t maxAxis() const  {
				return m_floats[0] < m_floats[1] ? (m_floats[1] <m_floats[2] ? 2 : 1) : (m_floats[0] <m_floats[2] ? 2 : 0);
			}
			
			int32_t furthestAxis() const {
				return absolute().minAxis();
			}
			
			int32_t closestAxis() const {
				return absolute().maxAxis();
			}
			
			void setInterpolate3(const Vector4D<T>& v0, const Vector4D<T>& v1, T rt) {
				btScalar s = 1 - rt;
				m_floats[0] = s * v0.m_floats[0] + rt * v1.m_floats[0];
				m_floats[1] = s * v0.m_floats[1] + rt * v1.m_floats[1];
				m_floats[2] = s * v0.m_floats[2] + rt * v1.m_floats[2];
				m_floats[3] = s * v0.m_floats[3] + rt * v1.m_floats[3];
				//don't do the unused w component
				//		m_co[3] = s * v0[3] + rt * v1[3];
			}
			*/
			/**
			 * @brief Return the linear interpolation between this and another vector 
			 * @param v The other vector 
			 * @param t The ration of this to v (t = 0 => return this, t=1 => return other)
			 */
			/*
			Vector3D<T> lerp(const Vector4D<T>& v, const btScalar& t) const  {
				return Vector3D<T>(m_floats[0] + (v.m_floats[0] - m_floats[0]) * t,
				                   m_floats[1] + (v.m_floats[1] - m_floats[1]) * t,
				                   m_floats[2] + (v.m_floats[2] - m_floats[2]) * t,
				                   m_floats[3] + (v.m_floats[3] - m_floats[3]) * t);
			}
			*/
			/**
			 * @brief Elementwise multiply this vector by the other 
			 * @param v The other vector
			 */
			Vector4D<T>& operator*=(const Vector4D<T>& v) {
				m_floats[0] *= v.m_floats[0];
				m_floats[1] *= v.m_floats[1];
				m_floats[2] *= v.m_floats[2];
				m_floats[3] *= v.m_floats[3];
				return *this;
			}
			Vector4D<T> operator*(const Vector4D<T>& v) {
				return Vector4D<T>(m_floats[0] * v.m_floats[0],
				                   m_floats[1] * v.m_floats[1],
				                   m_floats[2] * v.m_floats[2],
				                   m_floats[3] * v.m_floats[3]);
			}
			
			/**
			 * @brief Return the x value
			 */
			const T& getX() const { return m_floats[0]; }
			/**
			 * @brief Return the y value
			 */
			const T& getY() const { return m_floats[1]; }
			/**
			 * @brief Return the z value
			 */
			const T& getZ() const { return m_floats[2]; }
			/**
			 * @brief Return the z value
			 */
			const T& getW() const { return m_floats[3]; }
			/**
			 * @brief Set the x value
			 */
			void	setX(T _x) { m_floats[0] = _x;};
			/**
			 * @brief Set the y value
			 */
			void	setY(T _y) { m_floats[1] = _y;};
			/**
			 * @brief Set the z value
			 */
			void	setZ(T _z) { m_floats[2] = _z;};
			/**
			 * @brief Set the w value
			 */
			void	setW(T _w) { m_floats[3] = _w;};
			/**
			 * @brief Return the x value
			 */
			const T& x() const { return m_floats[0]; }
			/**
			 * @brief Return the y value
			 */
			const T& y() const { return m_floats[1]; }
			/**
			 * @brief Return the z value
			 */
			const T& z() const { return m_floats[2]; }
			/**
			 * @brief Return the w value
			 */
			const T& w() const { return m_floats[3]; }
			
			operator       T *()       { return &m_floats[0]; }
			operator const T *() const { return &m_floats[0]; }
			
			bool operator==(const Vector4D<T>& other) const {
				return (    (m_floats[3]==other.m_floats[3])
				         && (m_floats[2]==other.m_floats[2])
				         && (m_floats[1]==other.m_floats[1])
				         && (m_floats[0]==other.m_floats[0]));
			}
			
			bool operator!=(const Vector4D<T>& other) const {
				return (    (m_floats[3]!=other.m_floats[3])
				         || (m_floats[2]!=other.m_floats[2])
				         || (m_floats[1]!=other.m_floats[1])
				         || (m_floats[0]!=other.m_floats[0]));
			}
			
			/**
			 * @brief Set each element to the max of the current values and the values of another btVector3
			 * @param other The other btVector3 to compare with 
			 */
			void setMax(const Vector4D<T>& other) {
				btSetMax(m_floats[0], other.m_floats[0]);
				btSetMax(m_floats[1], other.m_floats[1]);
				btSetMax(m_floats[2], other.m_floats[2]);
				btSetMax(m_floats[3], other.m_floats[3]);
			}
			
			/**
			 * @brief Set each element to the min of the current values and the values of another btVector3
			 * @param other The other btVector3 to compare with 
			 */
			void setMin(const Vector4D<T>& other) {
				btSetMin(m_floats[0], other.m_floats[0]);
				btSetMin(m_floats[1], other.m_floats[1]);
				btSetMin(m_floats[2], other.m_floats[2]);
				btSetMin(m_floats[3], other.m_floats[3]);
			}
			
			void setValue(const T& _x, const T& _y, const T& _z, const T& _w) {
				m_floats[0]=_x;
				m_floats[1]=_y;
				m_floats[2]=_z;
				m_floats[3]=_w;
			}
			/*
			void getSkewSymmetricMatrix(Vector3D<T>* v0,Vector3D<T>* v1,Vector3D<T>* v2) const {
				v0->setValue(0.   ,-z() ,y());
				v1->setValue(z()  ,0.   ,-x());
				v2->setValue(-y() ,x()  ,0.);
			}
			*/
			void setZero() {
				setValue(0,0,0,0);
			}
			
			bool isZero() const {
				return m_floats[0] == 0 && m_floats[1] == 0 && m_floats[2] == 0 && m_floats[3] == 0;
			}
	};
	/**
	 * @brief Debug operator To display the curent element in a Human redeable information
	 */
	std::ostream& operator <<(std::ostream& _os, const etk::Vector4D<int32_t>& _obj);
	std::ostream& operator <<(std::ostream& _os, const etk::Vector4D<float>& _obj);
	std::ostream& operator <<(std::ostream& _os, const etk::Vector4D<uint32_t>& _obj);
	std::ostream& operator <<(std::ostream& _os, const etk::Vector4D<bool>& _obj);
}

// To siplify the writing of the code ==> this permit to have the same name with the glsl language...
typedef etk::Vector4D<float>      vec4;
typedef etk::Vector4D<int32_t>   ivec4;
// not compatible with glsl ... but it is better to have a same writing
typedef etk::Vector4D<uint32_t> uivec4;
typedef etk::Vector4D<bool>      bvec4;


