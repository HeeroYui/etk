/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <etk/types.h>

#pragma once

#include <etk/debug.h>
#include <vector>

namespace etk {
	/**
	 * @brief Plane equation template: define a plane equation
	 * @todo Validate it, this is a !!! PROTOTYPE !!!
	 */
	template <typename T> class Plane {
		private:
			etk::Vector3D<T> m_normal; //!< X.N+intercept=0
			T m_intercept; //!< interception value
		public:
			/**
			 * @brief Constructor of a Plane
			 */
			Plane() :
			  m_normal(0, 0, 0),
			  m_intercept(0) {
				
			}
			/**
			 * @brief Constructor of a Plane
			 * @param[in] _normal Normal of the plane
			 * @param[in] _intercept Interception value of the plane
			 */
			Plane(etk::Vector3D<T> _normal, T _intercept=0) :
			  m_normal(_normal),
			  m_intercept(_intercept) {
				
			}
			/**
			 * @brief Copy constructor of a Plane
			 * @param[in] _obj Plane object to copy
			 */
			Plane(const Plane& _obj) :
			  m_normal(_obj.m_normal),
			  m_intercept(_obj.m_intercept) {
				
			}
			/**
			 * @brief Set the normal of the plane
			 * @param[in] _obj Vector of the normal
			 */
			void setNormal(const etk::Vector3D<T>& _obj) {
				m_normal = _obj;
			}
			/**
			 * @brief Set interception value of the plane
			 * @param[in] _intercept Value of the intercept
			 */
			void setIntercept(float _intercept) {
				m_intercept=_intercept;
			}
			/**
			 * @brief Set the plane with 3 points in the space
			 * @param[in] _p0 First point
			 * @param[in] _p1 Second point
			 * @param[in] _p2 Thrid point
			 */
			void setFromPoints(const etk::Vector3D<T>& _p0,
			                   const etk::Vector3D<T>& _p1,
			                   const etk::Vector3D<T>& _p2) {
				m_normal = (_p1 - _p0).cross(_p2 - _p0);
				m_normal.normalize();
				calculateIntercept(_p0);
			}
			/**
			 * @brief Calculate interception value with a point in the plane
			 * @param[in] _pointOnPlane Point in the plane
			 */
			void calculateIntercept(const etk::Vector3D<T>& _pointOnPlane) {
				m_intercept=-m_normal.dot(_pointOnPlane);
			}
			/**
			 * @brief Normalize tha plane properties
			 */
			void normalize() {
				float normalLength = m_normal.getLength();
				if (normalLength == 0) {
					return;
				}
				m_normal /= normalLength;
				m_intercept /= normalLength;
			}
			/**
			 * @brief Get the normal of the plane
			 * @return Vector of the normal
			 */
			const etk::Vector3D<T>& getNormal() const {
				return m_normal;
			}
			/**
			 * @brief Get intercept Value of the plane
			 * @return The Intercept value
			 */
			T getIntercept() const {
				return m_intercept;
			}
			/**
			 * @brief Get the intersection between 3 planes
			 * @param[in] _p2 Second plane
			 * @param[in] _p3 Third plane
			 * @return vec3(0,0,0) No Intersection find, else when find
			 */
			etk::Vector3D<T> intersect3(const Plane<T>& _p2,
			                            const Plane<T>& _p3) {
				float denominator = m_normal.dot((_p2.m_normal).cross(_p3.m_normal));
				//scalar triple product of normals
				if(denominator==0.0f) {
					//no intersection
					return etk::Vector3D<T>(0,0,0);
				}
				etk::Vector3D<T> temp1, temp2, temp3;
				temp1 = (_p2.m_normal.cross(_p3.m_normal))*m_intercept;
				temp2 = (_p3.m_normal.cross(m_normal)) * _p2.m_intercept;
				temp3 = (m_normal.cross(_p2.m_normal)) * _p3.m_intercept;
				return (temp1+temp2+temp3) / (-denominator);
			}
			/**
			 * @brief Get distance from a point to the plane
			 * @param[in] _point Point to calculate the distance
			 * @return distance of the Point
			 */
			float getDistance(const etk::Vector3D<T>& _point) const {
				return   _point.x() * m_normal.x()
				       + _point.y() * m_normal.y()
				       + _point.z() * m_normal.z()
				       + m_intercept;
			}
			/**
			 * @brief Create a linear interpolation of the plane with an other
			 * @param[in] _p2 Second plane
			 * @param[in] _factor Factor to scale
			 * @return New plane equation
			 */
			Plane<T> linearInterpolate(const Plane<T>& _p2, float _factor) {
				Plane<T> result;
				result.m_normal=m_normal*(1.0f-_factor) + _p2.m_normal*_factor;
				result.m_normal.normalize();
				result.m_intercept=m_intercept*(1.0f-_factor) + _p2.m_intercept*_factor;
				return result;
			}
			/**
			 * @brief Equality compare operator with an other object.
			 * @param[in] _obj Reference on the comparing object
			 * @return true The Objects are identical
			 * @return false The Objects are NOT identical
			 */
			bool operator==(const Plane<T>& _obj) const {
				if(    m_normal == _obj.m_normal
				    && m_intercept == _obj.m_intercept) {
					return true;
				}
				return false;
			}
			/**
			 * @brief In-Equality compare operator with an other object.
			 * @param[in] _obj Reference on the comparing object
			 * @return true The Objects are NOT identical
			 * @return false The Objects are identical
			 */
			bool operator!=(const Plane<T>& _obj) const {
				return!((*this) == _obj);
			}
	};
}


