/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_MATH_VECTOR2D_H__
#define __ETK_MATH_VECTOR2D_H__

#include <etk/types.h>
#include <etk/Stream.h>
#include <math.h>

namespace etk
{
	template <typename T> class Vector2D
	{
		public:
			T x;
			T y;
		public:
			/*****************************************************
			 *    Constructor
			 *****************************************************/
			 Vector2D(T _x=0, T _y=0)                : x(_x), y(_y) { };
			 Vector2D(const Vector2D<double>& obj)   : x((T)obj.x), y((T)obj.y) { };
			 Vector2D(const Vector2D<float>& obj)    : x((T)obj.x), y((T)obj.y) { };
			 Vector2D(const Vector2D<int32_t>& obj)  : x((T)obj.x), y((T)obj.y) { };
			~Vector2D(void) { };
			/*****************************************************
			 *    = assigment
			 *****************************************************/
			const Vector2D<T>& operator= (const Vector2D<T>& obj ) {
				x = obj.x;
				y = obj.y;
				return *this;
			}
			const Vector2D<T>& operator= (const T val ) {
				x = val;
				y = val;
				return *this;
			}
			/*****************************************************
			 *    == operator
			 *****************************************************/
			bool  operator== (const Vector2D<T>& obj) const {
				if ((T)obj.x == x && (T)obj.y == y) {
					return true;
				}
				return false;
			}
			/*****************************************************
			 *    != operator
			 *****************************************************/
			bool  operator!= (const Vector2D<T>& obj) const {
				if ((T)obj.x == x && (T)obj.y == y) {
					return false;
				}
				return true;
			}
			/*****************************************************
			 *    += operator
			 *****************************************************/
			const Vector2D<T>& operator+= (const Vector2D<T>& obj) {
				x += obj.x;
				y += obj.y;
				return *this;
			}
			const Vector2D<T>& operator+= (const T val) {
				x += val;
				y += val;
				return *this;
			}
			/*****************************************************
			 *    + operator
			 *****************************************************/
			Vector2D<T> operator+ (const Vector2D<T>& obj) {
				Vector2D<T> tmpp(x,y);
				tmpp.x += obj.x;
				tmpp.y += obj.y;
				return tmpp;
			}
			Vector2D<T> operator+ (const T val) {
				Vector2D<T> tmpp(x,y);
				tmpp.x += val;
				tmpp.y += val;
				return tmpp;
			}
			/*****************************************************
			 *    -= operator
			 *****************************************************/
			const Vector2D<T>& operator-= (const Vector2D<T>& obj) {
				x -= obj.x;
				y -= obj.y;
				return *this;
			}
			const Vector2D<T>& operator-= (const T val) {
				x -= val;
				y -= val;
				return *this;
			}
			/*****************************************************
			 *    - operator
			 *****************************************************/
			Vector2D<T> operator- (const Vector2D<T>& obj) {
				Vector2D<T> tmpp(x,y);
				tmpp.x -= obj.x;
				tmpp.y -= obj.y;
				return tmpp;
			}
			Vector2D<T> operator- (const T val) {
				Vector2D<T> tmpp(x,y);
				tmpp.x -= val;
				tmpp.y -= val;
				return tmpp;
			}
			/*****************************************************
			 *    /= operator
			 *****************************************************/
			const Vector2D<T>& operator/= (const Vector2D<T>& obj) {
				if (obj.x!=0) {
					x /= obj.x;
				}
				if (obj.y!=0) {
					y /= obj.y;
				}
				return *this;
			}
			const Vector2D<T>& operator/= (const T val) {
				if (val != 0) {
					x /= val;
					y /= val;
				}
				return *this;
			}
			/*****************************************************
			 *    / operator
			 *****************************************************/
			Vector2D<T> operator/ (const Vector2D<T>& obj) {
				Vector2D<T> tmpp(x,y);
				tmpp.x /= (T)obj.x;
				tmpp.y /= (T)obj.y;
				return tmpp;
			}
			Vector2D<T> operator/ (const T val) {
				Vector2D<T> tmpp(x,y);
				tmpp.x /= val;
				tmpp.y /= val;
				return tmpp;
			}
			/*****************************************************
			 *    *= operator
			 *****************************************************/
			const Vector2D<T>& operator*= (const Vector2D<T>& obj) {
				x *= obj.x;
				y *= obj.y;
				return *this;
			}
			const Vector2D<T>& operator*= (const T val) {
				x *= val;
				y *= val;
				return *this;
			}
			/*****************************************************
			 *    * operator
			 *****************************************************/
			Vector2D<T> operator* (const Vector2D<T>& obj) {
				Vector2D<T> tmpp(x,y);
				tmpp.x *= obj.x;
				tmpp.y *= obj.y;
				return tmpp;
			}
			Vector2D<T> operator* (const T val) {
				Vector2D<T> tmpp(x,y);
				tmpp.x *= val;
				tmpp.y *= val;
				return tmpp;
			}
			/*****************************************************
			 *    ++ operator
			 *****************************************************/
			Vector2D<T>& operator++() // prefix
			{
				++x;
				++y;
				return *this;
			}
			Vector2D<T> operator++(int unused) // postfix
			{
				Vector2D<T> result = *this;
				++(*this);
				return result;
			}
			/*****************************************************
			 *    -- operator
			 *****************************************************/
			Vector2D<T>& operator--() // prefix
			{
				--x;
				--y;
				return *this;
			}
			
			Vector2D<T> operator--(int unused) // postfix
			{
				Vector2D<T> result = *this;
				--(*this);
				return result;
			}
			
			/**
			 * @brief Set the vector at (0,0)
			 */
			void Zero(void)
			{
				x=0;
				y=0;
			};
			/**
			 * @brief Set the vector at (1,1)
			 */
			void One(void)
			{
				x=0;
				y=0;
			};
			
			/**
			 * @brief normalize the curent vector
			 */
			void Normalize(void)
			{
				float length=GetLength();
				if(    length==1
				    || length==0) {
					return;
				}
				float scalefactor = 1.0f/length;
				x *= scalefactor;
				y *= scalefactor;
			};
			
			/**
			 * @brief Get the normalized vector
			 * @return a new vector normalized
			 */
			Vector2D<T> GetNormalized(void) const
			{
				Vector2D<T> tmp(*this);
				tmp.Normalize();
				return tmp;
			};
			
			/**
			 * @brief Get the size of the vector
			 * @return the float value
			 */
			float GetLength(void) const
			{
				return (float)sqrt((x*x)+(y*y));
			};
			
			/**
			 * @brief Get the square size of the vector
			 * @return flat value
			 */
			float GetSquaredLength(void) const
			{
				return (float)(x*x)+(y*y);
			};
			
			/**
			 * @brief Linar intermolation of the curent Vector
			 * @param[in] input
			 * @param[in] factor
			 * @return the interpolate vector
			 */
			Vector2D<T> LinearInterpolate(const Vector2D<T> & input, float factor) const
			{
				return (*this)*(1.0f-factor) + input*factor;
			};
			
			/**
			 * @brief Quadratic intermolation of the curent Vector
			 * @param[in] v1
			 * @param[in] v2
			 * @param[in] factor
			 * @return the interpolate vector
			 */
			Vector2D<T> QuadraticInterpolate(const Vector2D<T> & v2, const Vector2D<T> & v3, float factor) const
			{
				return (*this)*(1.0f-factor)*(1.0f-factor) + 2*v2*factor*(1.0f-factor) + v3*factor*factor;
			};
	};
	/**
	 * @brief Debug operator To display the curent element in a Human redeable information
	 */
	etk::CCout& operator <<(etk::CCout &os, const etk::Vector2D<int32_t> obj);
	/**
	 * @brief Debug operator To display the curent element in a Human redeable information
	 */
	etk::CCout& operator <<(etk::CCout &os, const etk::Vector2D<float> obj);
	
};

// To siplify the writing of the code ==> this permit to have the same name with the glsl language...
typedef etk::Vector2D<float>      vec2;
typedef etk::Vector2D<int32_t>   ivec2;
// not compatible with glsl ... but it is better to have a same writing
typedef etk::Vector2D<uint32_t> uivec2;
typedef etk::Vector2D<bool>      bvec2;

#endif
