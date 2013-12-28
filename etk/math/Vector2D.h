/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/types.h>

#ifndef __ETK_MATH_VECTOR2D_H__
#define __ETK_MATH_VECTOR2D_H__

#include <etk/Stream.h>
#include <etk/math/Vector3D.h>
#include <math.h>

namespace etk {
	template <typename T> class Vector2D {
		public:
			T m_floats[2];
		public:
			/* ****************************************************
			 *    Constructor
			 *****************************************************/
			Vector2D(void) {
				#ifdef DEBUG
					// in debug mode we set supid value to prevent forget of the inits ...
					m_floats[0] = (T)34673363;
					m_floats[1] = (T)34523535;
				#endif
			};
			
			Vector2D(T _x, T _y) {
				m_floats[0] = _x;
				m_floats[1] = _y;
			};
			Vector2D(const Vector2D<double>& obj)  { m_floats[0] = (T)obj.x(); m_floats[1] = (T)obj.y(); };
			Vector2D(const Vector2D<float>& obj)   { m_floats[0] = (T)obj.x(); m_floats[1] = (T)obj.y(); };
			Vector2D(const Vector2D<int32_t>& obj) { m_floats[0] = (T)obj.x(); m_floats[1] = (T)obj.y(); };
			Vector2D(const std::string& str);
			Vector2D(const std::u32string& str);
			~Vector2D(void) { };
			/* ****************************************************
			 *    = assigment
			 *****************************************************/
			const Vector2D<T>& operator= (const Vector2D<T>& obj ) {
				m_floats[0] = obj.m_floats[0];
				m_floats[1] = obj.m_floats[1];
				return *this;
			}
			const Vector2D<T>& operator= (const T val ) {
				m_floats[0] = val;
				m_floats[1] = val;
				return *this;
			}
			/* ****************************************************
			 *    == operator
			 *****************************************************/
			bool  operator== (const Vector2D<T>& obj) const {
				return (    (T)obj.m_floats[0] == m_floats[0]
				         && (T)obj.m_floats[1] == m_floats[1]);
			}
			/* ****************************************************
			 *    != operator
			 *****************************************************/
			bool  operator!= (const Vector2D<T>& obj) const {
				return (    (T)obj.m_floats[0] != m_floats[0]
				         || (T)obj.m_floats[1] != m_floats[1]);
			}
			/* ****************************************************
			 *    += operator
			 *****************************************************/
			const Vector2D<T>& operator+= (const Vector2D<T>& obj) {
				m_floats[0] += obj.m_floats[0];
				m_floats[1] += obj.m_floats[1];
				return *this;
			}
			const Vector2D<T>& operator+= (const T val) {
				m_floats[0] += val;
				m_floats[1] += val;
				return *this;
			}
			/* ****************************************************
			 *    + operator
			 *****************************************************/
			Vector2D<T> operator+ (const Vector2D<T>& obj) const {
				Vector2D<T> tmpp(m_floats[0],m_floats[1]);
				tmpp.m_floats[0] += obj.m_floats[0];
				tmpp.m_floats[1] += obj.m_floats[1];
				return tmpp;
			}
			Vector2D<T> operator+ (const T val) const {
				Vector2D<T> tmpp(m_floats[0],m_floats[1]);
				tmpp.m_floats[0] += val;
				tmpp.m_floats[1] += val;
				return tmpp;
			}
			/* ****************************************************
			 *    -= operator
			 *****************************************************/
			const Vector2D<T>& operator-= (const Vector2D<T>& obj) {
				m_floats[0] -= obj.m_floats[0];
				m_floats[1] -= obj.m_floats[1];
				return *this;
			}
			const Vector2D<T>& operator-= (const T val) {
				m_floats[0] -= val;
				m_floats[1] -= val;
				return *this;
			}
			/* ****************************************************
			 *    - operator
			 *****************************************************/
			Vector2D<T> operator- (const Vector2D<T>& obj) const {
				Vector2D<T> tmpp(m_floats[0],m_floats[1]);
				tmpp.m_floats[0] -= obj.m_floats[0];
				tmpp.m_floats[1] -= obj.m_floats[1];
				return tmpp;
			}
			Vector2D<T> operator- (const T val) const {
				Vector2D<T> tmpp(m_floats[0],m_floats[1]);
				tmpp.m_floats[0] -= val;
				tmpp.m_floats[1] -= val;
				return tmpp;
			}
			/* ****************************************************
			 *    *= operator
			 *****************************************************/
			const Vector2D<T>& operator*= (const Vector2D<T>& obj) {
				m_floats[0] *= obj.m_floats[0];
				m_floats[1] *= obj.m_floats[1];
				return *this;
			}
			const Vector2D<T>& operator*= (const T val) {
				m_floats[0] *= val;
				m_floats[1] *= val;
				return *this;
			}
			/* ****************************************************
			 *    * operator
			 *****************************************************/
			Vector2D<T> operator* (const Vector2D<T>& obj) const {
				Vector2D<T> tmpp(m_floats[0],m_floats[1]);
				tmpp.m_floats[0] *= obj.m_floats[0];
				tmpp.m_floats[1] *= obj.m_floats[1];
				return tmpp;
			}
			Vector2D<T> operator* (const T val) const {
				Vector2D<T> tmpp(m_floats[0],m_floats[1]);
				tmpp.m_floats[0] *= val;
				tmpp.m_floats[1] *= val;
				return tmpp;
			}
			/* ****************************************************
			 *    / operator
			 *****************************************************/
			Vector2D<T> operator/ (const Vector2D<T>& obj) const{
				Vector2D<T> tmpp(m_floats[0],m_floats[1]);
				tmpp.m_floats[0] /= obj.m_floats[0];
				tmpp.m_floats[1] /= obj.m_floats[1];
				return tmpp;
			}
			Vector2D<T> operator/ (const T val) const {
				Vector2D<T> tmpp(m_floats[0],m_floats[1]);
				tmpp.m_floats[0] /= val;
				tmpp.m_floats[1] /= val;
				return tmpp;
			}
			/* ****************************************************
			 *    ++ operator
			 *****************************************************/
			Vector2D<T>& operator++(void) {
				++m_floats[0];
				++m_floats[1];
				return *this;
			}
			Vector2D<T> operator++(int unused) {
				Vector2D<T> result = *this;
				++(*this);
				return result;
			}
			/* ****************************************************
			 *    -- operator
			 *****************************************************/
			Vector2D<T>& operator--(void) {
				--m_floats[0];
				--m_floats[1];
				return *this;
			}
			Vector2D<T> operator--(int unused) {
				Vector2D<T> result = *this;
				--(*this);
				return result;
			}
			/**
			 * @brief Return the dot product
			 * @param v The other vector in the dot product
			 */
			btScalar dot(const Vector2D<T>& v) const {
				return	m_floats[0] * v.m_floats[0] + 
						m_floats[1] * v.m_floats[1];
			}
			/**
			 * @brief Return the length of the vector squared
			 */
			btScalar length2(void) const {
				return dot(*this);
			}
			/**
			 * @brief Return the length of the vector
			 */
			btScalar length(void) const {
				return btSqrt(length2());
			}
			/**
			 * @brief Return the distance squared between the ends of this and another vector
			 * This is symantically treating the vector like a point
			 */
			btScalar distance2(const btVector3& v) const {
				return (v - *this).length2();
			}
			/**
			 * @brief Return the distance between the ends of this and another vector
			 * This is symantically treating the vector like a point
			 */
			btScalar distance(const btVector3& v) const {
				return (v - *this).length();
			}
			/**
			 * @brief Normalize this vector 
			 * x^2 + y^2 + z^2 = 1
			 */
			Vector3D<T>& normalize(void) {
				return *this /= length();
			}
			/**
			 * @brief Return a normalized version of this vector
			 */
			Vector2D<T> normalized(void) const {
				return *this / length();
			}
			/**
			 * @brief Return a vector will the absolute values of each element
			 */
			Vector2D<T> absolute(void) const {
				return Vector2D<T>( abs(m_floats[0]),
				                    abs(m_floats[1]));
			}
			/**
			 * @brief Return the axis with the smallest value 
			 * Note return values are 0,1,2 for x, y, or z
			 */
			int32_t minAxis(void) const {
				return m_floats[0] < m_floats[1] ? 0 : 1;
			}
			/**
			 * @brief Return the axis with the largest value
			 * Note return values are 0,1,2 for x, y, or z
			 */
			int32_t maxAxis(void) const {
				return m_floats[0] < m_floats[1] ? 1 : 0;
			}
			int32_t furthestAxis(void) const {
				return absolute().minAxis();
			}
			int32_t closestAxis(void) const {
				return absolute().maxAxis();
			}
			/**
			 * @brief Return the x value
			 */
			const T& getX(void) const {
				return m_floats[0];
			}
			/**
			 * @brief Return the y value
			 */
			const T& getY(void) const {
				return m_floats[1];
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
			 * @brief Return the x value
			 */
			const T& x(void) const {
				return m_floats[0];
			}
			/**
			 * @brief Return the y value
			 */
			const T& y(void) const {
				return m_floats[1];
			}
			operator T *(void) {
				return &m_floats[0];
			}
			operator const T *(void) const {
				return &m_floats[0];
			}
			/**
			 * @brief Set each element to the max of the current values and the values of another btVector3
			 * @param other The other btVector3 to compare with 
			 */
			void setMax(const Vector2D<T>& other) {
				btSetMax(m_floats[0], other.m_floats[0]);
				btSetMax(m_floats[1], other.m_floats[1]);
			}
			/**
			 * @brief Set each element to the min of the current values and the values of another btVector3
			 * @param other The other btVector3 to compare with 
			 */
			void setMin(const Vector2D<T>& other) {
				btSetMin(m_floats[0], other.m_floats[0]);
				btSetMin(m_floats[1], other.m_floats[1]);
			}
			void setValue(const T& _x, const T& _y) {
				m_floats[0]=_x;
				m_floats[1]=_y;
			}
			void setZero(void) {
				setValue(0,0);
			}
			bool isZero(void) const {
				return m_floats[0] == 0 && m_floats[1] == 0;
			}
			//!< string cast :
			operator std::string(void) const;
			operator std::u32string(void) const;
	};
	/**
	 * @brief Debug operator To display the curent element in a Human redeable information
	 */
	etk::CCout& operator <<(etk::CCout &os, const etk::Vector2D<int32_t>& obj);
	etk::CCout& operator <<(etk::CCout &os, const etk::Vector2D<float>& obj);
	etk::CCout& operator <<(etk::CCout &os, const etk::Vector2D<uint32_t>& obj);
	etk::CCout& operator <<(etk::CCout &os, const etk::Vector2D<bool>& obj);
};
// To siplify the writing of the code ==> this permit to have the same name with the glsl language...
typedef etk::Vector2D<float>      vec2;
typedef etk::Vector2D<int32_t>   ivec2;
// not compatible with glsl ... but it is better to have a same writing
typedef etk::Vector2D<uint32_t> uivec2;
typedef etk::Vector2D<bool>      bvec2;

inline vec2 vec2ClipInt32(const vec2& _val) {
	return vec2((int32_t)_val.x(), (int32_t)_val.y());
}

inline vec2 vec2ClipInt64(const vec2& _val) {
	return vec2((int64_t)_val.x(), (int64_t)_val.y());
}

#endif
