/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_MATH_VECTOR3D_H__
#define __ETK_MATH_VECTOR3D_H__

#include <etk/types.h>
#include <etk/DebugInternal.h>
#include <math.h>
#include <etk/Stream.h>
#include <LinearMath/btScalar.h>
#include <LinearMath/btMinMax.h>
#include <LinearMath/btVector3.h>

namespace etk
{
	template <typename T> class Vector3D
	{
		public:
			T m_floats[4];
		public:
			/**
			 * @brief No initialization constructor (faster ...)
			 */
			Vector3D(void)
			{
				
			}
			/**
			 * @brief Constructor from scalars 
			 * @param x X value
			 * @param y Y value 
			 * @param z Z value 
			 */
			Vector3D(const T& _x, const T& _y, const T& _z)
			{
				m_floats[0] = _x;
				m_floats[1] = _y;
				m_floats[2] = _z;
				m_floats[3] = 0;
			}
			
			/**
			 * @brief Add a vector to this one 
			 * @param The vector to add to this one
			 */
			Vector3D<T>& operator+=(const Vector3D<T>& v)
			{
				m_floats[0] += v.m_floats[0];
				m_floats[1] += v.m_floats[1];
				m_floats[2] += v.m_floats[2];
				return *this;
			}
			
			
			/**
			 * @brief Subtract a vector from this one
			 * @param The vector to subtract
			 */
			Vector3D<T>& operator-=(const Vector3D<T>& v) 
			{
				m_floats[0] -= v.m_floats[0]; 
				m_floats[1] -= v.m_floats[1];
				m_floats[2] -= v.m_floats[2];
				return *this;
			}
			
			/**
			 * @brief Scale the vector
			 * @param s Scale factor
			 */
			Vector3D<T>& operator*=(const T& s)
			{
				m_floats[0] *= s; 
				m_floats[1] *= s;
				m_floats[2] *= s;
				return *this;
			}
			
			/**
			 * @brief Inversely scale the vector 
			 * @param s Scale factor to divide by
			 */
			Vector3D<T>& operator/=(const Vector3D<T>& s) 
			{
				if (0!=s) {
					return *this *= btScalar(1.0) / s;
				}
				return 0;
			}
			
			/**
			 * @brief Return the dot product
			 * @param v The other vector in the dot product
			 */
			btScalar dot(const Vector3D<T>& v) const
			{
				return	m_floats[0] * v.m_floats[0] + 
						m_floats[1] * v.m_floats[1] + 
						m_floats[2] * v.m_floats[2];
			}
			
			/**
			 * @brief Return the length of the vector squared
			 */
			btScalar length2() const
			{
				return dot(*this);
			}
			
			/**
			 * @brief Return the length of the vector
			 */
			btScalar length() const
			{
				return btSqrt(length2());
			}
			
			/**
			 * @brief Return the distance squared between the ends of this and another vector
			 * This is symantically treating the vector like a point
			 */
			btScalar distance2(const btVector3& v) const
			{
				return (v - *this).length2();
			}
			
			/**
			 * @brief Return the distance between the ends of this and another vector
			 * This is symantically treating the vector like a point
			 */
			btScalar distance(const btVector3& v) const
			{
				return (v - *this).length();
			}
			
			Vector3D<T>& safeNormalize() 
			{
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
			Vector3D<T>& normalize() 
			{
				return *this /= length();
			}
			
			/**
			 * @brief Return a normalized version of this vector
			 */
			Vector3D<T> normalized() const
			{
				return *this / length();
			}
			
			/**
			 * @brief Return a rotated version of this vector
			 * @param wAxis The axis to rotate about
			 * @param angle The angle to rotate by
			 */
			Vector3D<T> rotate( const Vector3D<T>& wAxis, const btScalar angle ) const
			{
				Vector3D<T> o = wAxis * wAxis.dot( *this );
				Vector3D<T> _x = *this - o;
				Vector3D<T> _y;
				_y = wAxis.cross( *this );
				return ( o + _x * cosf(angle) + _y * sinf(angle) );
			}
			
			/**
			 * @brief Return the angle between this and another vector
			 * @param v The other vector
			 */
			btScalar angle(const Vector3D<T>& v) const
			{
				btScalar s = sqrtf(length2() * v.length2());
				if (0!=s) {
					return acosf(dot(v) / s);
				}
				return 0;
			}
			
			/**
			 * @brief Return a vector will the absolute values of each element
			 */
			Vector3D<T> absolute(void) const
			{
				return Vector3D<T>( abs(m_floats[0]),
				                    abs(m_floats[1]),
				                    abs(m_floats[2]));
			}
			
			/**
			 * @brief Return the cross product between this and another vector
			 * @param v The other vector
			 */
			Vector3D<T> cross(const Vector3D<T>& v) const
			{
				return Vector3D<T>(m_floats[1] * v.m_floats[2] - m_floats[2] * v.m_floats[1],
				                   m_floats[2] * v.m_floats[0] - m_floats[0] * v.m_floats[2],
				                   m_floats[0] * v.m_floats[1] - m_floats[1] * v.m_floats[0]);
			}
			
			T triple(const Vector3D<T>& v1, const Vector3D<T>& v2) const
			{
				return   m_floats[0] * (v1.m_floats[1] * v2.m_floats[2] - v1.m_floats[2] * v2.m_floats[1])
				       + m_floats[1] * (v1.m_floats[2] * v2.m_floats[0] - v1.m_floats[0] * v2.m_floats[2])
				       + m_floats[2] * (v1.m_floats[0] * v2.m_floats[1] - v1.m_floats[1] * v2.m_floats[0]);
			}
			
			/**
			 * @brief Return the axis with the smallest value 
			 * Note return values are 0,1,2 for x, y, or z
			 */
			int32_t minAxis(void) const
			{
				return m_floats[0] < m_floats[1] ? (m_floats[0] <m_floats[2] ? 0 : 2) : (m_floats[1] <m_floats[2] ? 1 : 2);
			}
			
			/**
			 * @brief Return the axis with the largest value
			 * Note return values are 0,1,2 for x, y, or z
			 */
			int32_t maxAxis(void) const 
			{
				return m_floats[0] < m_floats[1] ? (m_floats[1] <m_floats[2] ? 2 : 1) : (m_floats[0] <m_floats[2] ? 2 : 0);
			}
			
			int32_t furthestAxis(void) const
			{
				return absolute().minAxis();
			}
			
			int32_t closestAxis(void) const
			{
				return absolute().maxAxis();
			}
			
			void setInterpolate3(const Vector3D<T>& v0, const Vector3D<T>& v1, T rt)
			{
				btScalar s = 1 - rt;
				m_floats[0] = s * v0.m_floats[0] + rt * v1.m_floats[0];
				m_floats[1] = s * v0.m_floats[1] + rt * v1.m_floats[1];
				m_floats[2] = s * v0.m_floats[2] + rt * v1.m_floats[2];
				//don't do the unused w component
				//		m_co[3] = s * v0[3] + rt * v1[3];
			}
			
			/**
			 * @brief Return the linear interpolation between this and another vector 
			 * @param v The other vector 
			 * @param t The ration of this to v (t = 0 => return this, t=1 => return other)
			 */
			Vector3D<T> lerp(const Vector3D<T>& v, const btScalar& t) const 
			{
				return Vector3D<T>(m_floats[0] + (v.m_floats[0] - m_floats[0]) * t,
				                   m_floats[1] + (v.m_floats[1] - m_floats[1]) * t,
				                   m_floats[2] + (v.m_floats[2] - m_floats[2]) * t);
			}
			
			/**
			 * @brief Elementwise multiply this vector by the other 
			 * @param v The other vector
			 */
			Vector3D<T>& operator*=(const Vector3D<T>& v)
			{
				m_floats[0] *= v.m_floats[0]; 
				m_floats[1] *= v.m_floats[1];
				m_floats[2] *= v.m_floats[2];
				return *this;
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
			
			bool operator==(const Vector3D<T>& other) const
			{
				return (    (m_floats[3]==other.m_floats[3])
				         && (m_floats[2]==other.m_floats[2])
				         && (m_floats[1]==other.m_floats[1])
				         && (m_floats[0]==other.m_floats[0]));
			}
			
			bool operator!=(const Vector3D<T>& other) const
			{
				return (    (m_floats[3]!=other.m_floats[3])
				         || (m_floats[2]!=other.m_floats[2])
				         || (m_floats[1]!=other.m_floats[1])
				         || (m_floats[0]!=other.m_floats[0]));
			}
			
			/**
			 * @brief Set each element to the max of the current values and the values of another btVector3
			 * @param other The other btVector3 to compare with 
			 */
			void setMax(const Vector3D<T>& other)
			{
				btSetMax(m_floats[0], other.m_floats[0]);
				btSetMax(m_floats[1], other.m_floats[1]);
				btSetMax(m_floats[2], other.m_floats[2]);
				btSetMax(m_floats[3], other.m_floats[3]);
			}
			
			/**
			 * @brief Set each element to the min of the current values and the values of another btVector3
			 * @param other The other btVector3 to compare with 
			 */
			void setMin(const Vector3D<T>& other)
			{
				btSetMin(m_floats[0], other.m_floats[0]);
				btSetMin(m_floats[1], other.m_floats[1]);
				btSetMin(m_floats[2], other.m_floats[2]);
				btSetMin(m_floats[3], other.m_floats[3]);
			}
			
			void setValue(const T& _x, const T& _y, const T& _z)
			{
				m_floats[0]=_x;
				m_floats[1]=_y;
				m_floats[2]=_z;
				m_floats[3] = 0;
			}
			
			void getSkewSymmetricMatrix(Vector3D<T>* v0,Vector3D<T>* v1,Vector3D<T>* v2) const
			{
				v0->setValue(0.   ,-z() ,y());
				v1->setValue(z()  ,0.   ,-x());
				v2->setValue(-y() ,x()  ,0.);
			}
			
			void setZero(void)
			{
				setValue(0,0,0);
			}
			
			bool isZero(void) const
			{
				return m_floats[0] == 0 && m_floats[1] == 0 && m_floats[2] == 0;
			}
	};
	/**
	 * @brief Debug operator To display the curent element in a Human redeable information
	 */
	etk::CCout& operator <<(etk::CCout &os, const etk::Vector3D<int32_t> obj);
	etk::CCout& operator <<(etk::CCout &os, const btVector3 obj);
	etk::CCout& operator <<(etk::CCout &os, const etk::Vector3D<uint32_t> obj);
	etk::CCout& operator <<(etk::CCout &os, const etk::Vector3D<bool> obj);
};

// To siplify the writing of the code ==> this permit to have the same name with the glsl language...
typedef btVector3                vec3;
typedef etk::Vector3D<float>     ovec3;  // specific for OpenGL ... ==> never change this ...
typedef etk::Vector3D<int32_t>   ivec3;
// not compatible with glsl ... but it is better to have a same writing
typedef etk::Vector3D<uint32_t> uivec3;
typedef etk::Vector3D<bool>      bvec3;



#endif

