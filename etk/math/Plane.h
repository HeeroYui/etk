/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_TYPES_PLANE_H__
#define __ETK_TYPES_PLANE_H__

#include <etk/debug.h>
#include <vector>

namespace etk {
	template <typename T> class Plane {
		public :
			//member variables
			etk::Vector3D<T> m_normal; //!< X.N+intercept=0
			T m_intercept;
		public:
			/*****************************************************
			 *    Constructor
			 *****************************************************/
			Plane(void) :
			  m_normal(0, 0, 0),
			  m_intercept(0) {
				
			}
			Plane(etk::Vector3D<T> _normal, T _intercept=0) :
			  m_normal(_normal),
			  m_intercept(_intercept) {
				
			}
			Plane(const Plane& obj) :
			  m_normal(obj.m_normal),
			  m_intercept(obj.m_intercept) {
				
			}
			/*****************************************************
			 *    Destructor
			 *****************************************************/
			~Plane(void) {
				
			};
			
			/**
			 * @brief
			 * @param[in,out]
			 * @return
			 */
			void setNormal(const etk::Vector3D<T>& _obj) {
				m_normal = _obj;
			};
			
			/**
			 * @brief
			 * @param[in,out]
			 * @return
			 */
			void setIntercept(float _intercept) {
				m_intercept=_intercept;
			};
			
			/**
			 * @brief
			 * @param[in,out]
			 * @return
			 */
			void setFromPoints(const etk::Vector3D<T>& p0,
			                   const etk::Vector3D<T>& p1,
			                   const etk::Vector3D<T>& p2) {
				m_normal = (_p1 - _p0).crossProduct(_p2 - _p0);
				m_normal.normalize();
				calculateIntercept(_p0);
			};
			
			/**
			 * @brief
			 * @param[in,out]
			 * @return
			 */
			void calculateIntercept(const etk::Vector3D<T>& _pointOnPlane) {
				m_intercept=-m_normal.dotProduct(_pointOnPlane);
			}
			
			/**
			 * @brief
			 * @param[in,out]
			 * @return
			 */
			void normalize(void) {
				float normalLength=m_normal.getLength();
				m_normal/=normalLength;
				m_intercept/=normalLength;
			};
			
			/**
			 * @brief
			 * @param[in,out]
			 * @return
			 */
			etk::Vector3D<T> getNormal(void) {
				return m_normal;
			};
			
			/**
			 * @brief
			 * @param[in,out]
			 * @return
			 */
			float getIntercept(void) {
				return m_intercept;
			}
			
			//find point of intersection of 3 planes
			/**
			 * @brief
			 * @param[in,out]
			 * @return
			 */
			bool intersect3(const Plane<T>& _p2,
			                const Plane<T>& _p3,
			                etk::Vector3D<T>& _result) {
				float denominator = m_normal.dotProduct((_p2.m_normal).crossProduct(_p3.m_normal));
				//scalar triple product of normals
				if(denominator==0.0f) {
					//no intersection
					return false;
				}
				etk::Vector3D<T> temp1, temp2, temp3;
				temp1 = (_p2.m_normal.crossProduct(_p3.m_normal))*m_intercept;
				temp2 = (_p3.m_normal.crossProduct(m_normal)) * _p2.m_intercept;
				temp3 = (m_normal.crossProduct(_p2.m_normal)) * _p3.m_intercept;
				
				result=(temp1+temp2+temp3)/(-denominator);
				
				return true;
			};
			
			/**
			 * @brief
			 * @param[in,out]
			 * @return
			 */
			float getDistance(const etk::Vector3D<T>& _point) const {
				return   _point.x * m_normal.x
				       + _point.y * m_normal.y
				       + _point.z * m_normal.z
				       + m_intercept;
			};
			
			/**
			 * @brief
			 * @param[in,out]
			 * @return
			 */
			Plane<T> linearInterpolate(const Plane<T>& _p2, float _factor) {
				Plane<T> result;
				result.m_normal=m_normal*(1.0f-_factor) + _p2.m_normal*_factor;
				result.m_normal.normalize();
				result.m_intercept=m_intercept*(1.0f-_factor) + _p2.m_intercept*_factor;
				return result;
			};
			
			//operators
			/**
			 * @brief
			 * @param[in,out]
			 * @return
			 */
			bool operator==(const Plane<T> & _obj) const {
				if(    m_normal == _obj.m_normal
				    && m_intercept == _obj.m_intercept) {
					return true;
				}
				return false;
			};
			
			/**
			 * @brief
			 * @param[in,out]
			 * @return
			 */
			bool operator!=(const Plane<T>& _obj) const {
				return!((*this) == _obj);
			}
			
			//unary operators
			/**
			 * @brief
			 * @param[in,out]
			 * @return
			 */
			Plane<T> operator-(void) const {
				return Plane<T>(-m_normal, -m_intercept);
			}
			
			/**
			 * @brief
			 * @param[in,out]
			 * @return
			 */
			Plane<T> operator+(void) const {
				return *this;
			}
	};
};

#endif

