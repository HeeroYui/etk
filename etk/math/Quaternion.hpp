/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>

#include <cmath>
#include <etk/math/Matrix3x3.hpp>
#include <etk/math/Vector3D.hpp>

namespace etk {
	/**
	 * @brief This class represents a quaternion.
	 */
	struct Quaternion {
		public:
			float m_floats[4]; //!< all internal values
		public:
			/**
			 * @brief No initialization constructor (faster ...)
			 */
			Quaternion() {
				m_floats[0] = 0.0f;
				m_floats[1] = 0.0f;
				m_floats[2] = 0.0f;
				m_floats[3] = 0.0f;
			}
			/**
			 * @brief Constructor from scalars.
			 * @param _xxx X value
			 * @param _yyy Y value
			 * @param _zzz Z value
			 * @param _www W value
			 */
			Quaternion(const float& _xxx, const float& _yyy, const float& _zzz, const float& _www) {
				m_floats[0] = _xxx;
				m_floats[1] = _yyy;
				m_floats[2] = _zzz;
				m_floats[3] = _www;
			}
			/**
			 * @brief Constructor with the component w and a vector 3D.
			 * @param _www W value
			 * @param _vec 3D vector value
			 */
			Quaternion(float _www, const vec3& _vec) {
				m_floats[0] = _vec.x();
				m_floats[1] = _vec.y();
				m_floats[2] = _vec.z();
				m_floats[3] = _www;
			}
			/**
			 * @brief Constructor with Euler angles (in radians) to a quaternion
			 * @param _eulerAngles list of all euleu angle
			 */
			Quaternion(const vec3& _eulerAngles) {
				setEulerAngles(_eulerAngles);
			}
			/**
			 * @brief Create a unit quaternion from a rotation matrix
			 * @param _matrix generic matrix
			 */
			Quaternion(const etk::Matrix3x3& _matrix);
			/**
			 * @brief Add a vector to this one.
			 * @param[in] _obj The vector to add to this one
			 * @return Local reference of the vector
			 */
			Quaternion& operator+=(const Quaternion& _obj) {
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
			Quaternion operator+(const Quaternion& _obj) {
				return Quaternion(m_floats[0] + _obj.m_floats[0],
				                   m_floats[1] + _obj.m_floats[1],
				                   m_floats[2] + _obj.m_floats[2],
				                   m_floats[3] + _obj.m_floats[3]);
			}
			/**
			 * @brief Subtract a vector from this one
			 * @param _obj The vector to subtract
			 * @return Local reference of the vector
			 */
			Quaternion& operator-=(const Quaternion& _obj) {
				m_floats[0] -= _obj.m_floats[0];
				m_floats[1] -= _obj.m_floats[1];
				m_floats[2] -= _obj.m_floats[2];
				m_floats[3] -= _obj.m_floats[3];
				return *this;
			}
			/**
			 * @brief Subtract a vector from this one
			 * @param _obj The vector to subtract
			 * @return New quaternion containing the value
			 */
			Quaternion operator-(const Quaternion& _obj) {
				return Quaternion(m_floats[0] - _obj.m_floats[0],
				                   m_floats[1] - _obj.m_floats[1],
				                   m_floats[2] - _obj.m_floats[2],
				                   m_floats[3] - _obj.m_floats[3]);
			}
			/**
			 * @brief Scale the quaternion
			 * @param[in] _val Scale factor
			 * @return Local reference of the quaternion
			 */
			Quaternion& operator*=(const float& _val) {
				m_floats[0] *= _val;
				m_floats[1] *= _val;
				m_floats[2] *= _val;
				m_floats[3] *= _val;
				return *this;
			}
			/**
			 * @brief Scale the quaternion
			 * @param[in] _val Scale factor
			 * @return New quaternion containing the value
			 */
			Quaternion operator*(const float& _val) const {
				return Quaternion(m_floats[0] * _val,
				                   m_floats[1] * _val,
				                   m_floats[2] * _val,
				                   m_floats[3] * _val);
			}
			/**
			 * @brief Inversely scale the quaternion
			 * @param[in] _val Scale factor to divide by.
			 * @return Local reference of the quaternion
			 */
			Quaternion& operator/=(const float& _val) {
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
			 * @brief Inversely scale the quaternion
			 * @param[in] _val Scale factor to divide by.
			 * @return New quaternion containing the value
			 */
			Quaternion operator/(const float& _val) const {
				if (_val != 0) {
					return Quaternion(m_floats[0] / _val,
					                   m_floats[1] / _val,
					                   m_floats[2] / _val,
					                   m_floats[3] / _val);
				}
				return *this;
			}
			/**
			 * @brief Return the dot product
			 * @param _obj The other quaternion in the dot product
			 * @return Dot result value
			 */
			float dot(const Quaternion& _obj) const {
				return   m_floats[0] * _obj.m_floats[0]
				       + m_floats[1] * _obj.m_floats[1]
				       + m_floats[2] * _obj.m_floats[2]
				       + m_floats[3] * _obj.m_floats[3];
			}
			/**
			 * @brief Return the squared length of the quaternion.
			 * @return Squared length value.
			 */
			float length2() const {
				return dot(*this);
			}
			/**
			 * @brief Return the length of the quaternion
			 * @return Length value
			 */
			float length() const {
				#if __CPP_VERSION__ >= 2011 && !defined(__TARGET_OS__MacOs) && !defined(__TARGET_OS__IOs)
					return std::sqrt(length2());
				#else
					return sqrt(length2());
				#endif
			}
			/**
			 * @brief Return the distance squared between the ends of this and another quaternion
			 * This is symantically treating the quaternion like a point
			 * @param[in] _obj The other quaternion to compare distance
			 * @return the square distance of the 2 points
			 */
			/*
			float distance2(const Quaternion& _obj) const {
				return (_obj - *this).length2();
			}
			*/
			/**
			 * @brief Return the distance between the ends of this and another quaternion
			 * This is symantically treating the quaternion like a point
			 * @param[in] _obj The other quaternion to compare distance
			 * @return the distance of the 2 points
			 */
			/*
			float distance(const Quaternion& _obj) const {
				return (_obj - *this).length();
			}
			*/
			/**
			 * @brief Normalize this quaternion x^2 + y^2 + z^2 + w^2 = 1
			 * @return Local reference of the quaternion normalized
			 */
			Quaternion& normalize() {
				float invLength = 1.0f / length();
				m_floats[0] *= invLength;
				m_floats[1] *= invLength;
				m_floats[2] *= invLength;
				m_floats[3] *= invLength;
				return *this;
			}
			/**
			 * @brief Return a normalized version of this quaternion
			 * @return New quaternion containing the value
			 */
			Quaternion normalized() const {
				etk::Quaternion tmp = *this;
				tmp.normalize();
				return tmp;
			}
			/**
			 * @brief Return a quaternion will the absolute values of each element
			 * @return New quaternion with the absolute value
			 */
			Quaternion absolute() const {
				return Quaternion( std::abs(m_floats[0]),
				                   std::abs(m_floats[1]),
				                   std::abs(m_floats[2]),
				                   std::abs(m_floats[3]));
			}
			/**
			 * @brief Get X value
			 * @return the x value
			 */
			const float& getX() const {
				return m_floats[0];
			}
			/**
			 * @brief Get Y value
			 * @return the y value
			 */
			const float& getY() const {
				return m_floats[1];
			}
			/**
			 * @brief Get Z value
			 * @return the z value
			 */
			const float& getZ() const {
				return m_floats[2];
			}
			/**
			 * @brief Get W value
			 * @return the w value
			 */
			const float& getW() const {
				return m_floats[3];
			}
			/**
			 * @brief Set the x value
			 * @param[in] _x New value
			 */
			void setX(float _x) {
				m_floats[0] = _x;
			};
			/**
			 * @brief Set the y value
			 * @param[in] _y New value
			 */
			void setY(float _y) {
				m_floats[1] = _y;
			};
			/**
			 * @brief Set the z value
			 * @param[in] _z New value
			 */
			void setZ(float _z) {
				m_floats[2] = _z;
			};
			/**
			 * @brief Set the w value
			 * @param[in] _w New value
			 */
			void setW(float _w) {
				m_floats[3] = _w;
			};
			/**
			 * @brief Get X value
			 * @return the x value
			 */
			const float& x() const {
				return m_floats[0];
			}
			/**
			 * @brief Get Y value
			 * @return the y value
			 */
			const float& y() const {
				return m_floats[1];
			}
			/**
			 * @brief Get Z value
			 * @return the z value
			 */
			const float& z() const {
				return m_floats[2];
			}
			/**
			 * @brief Get W value
			 * @return the w value
			 */
			const float& w() const {
				return m_floats[3];
			}
			/**
			 * @brief Cast the quaternion in the type T* requested.
			 * @return Pointer on the data
			 */
			operator float *() {
				return &m_floats[0];
			}
			/**
			 * @brief Cast the quaternion in the type const float* requested.
			 * @return Pointer on the const data
			 */
			operator const float *() const {
				return &m_floats[0];
			}
			/**
			 * @brief Equality compare operator with an other object.
			 * @param[in] _obj Reference on the comparing object
			 * @return true The Objects are identical
			 * @return false The Objects are NOT identical
			 */
			bool operator==(const Quaternion& _obj) const {
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
			bool operator!=(const Quaternion& _obj) const {
				return (    (m_floats[3] != _obj.m_floats[3])
				         || (m_floats[2] != _obj.m_floats[2])
				         || (m_floats[1] != _obj.m_floats[1])
				         || (m_floats[0] != _obj.m_floats[0]));
			}
			/**
			 * @brief Multiply this quaternion by the other.
			 * @param _obj The other quaternion
			 * @return Local reference of the quaternion
			 */
			Quaternion& operator*=(const Quaternion& _obj) {
				vec3 base = getVectorV();
				vec3 crossValue = base.cross(_obj.getVectorV());
				m_floats[0] = m_floats[3] * _obj.m_floats[0] + _obj.m_floats[3] * m_floats[0] + crossValue.x();
				m_floats[1] = m_floats[3] * _obj.m_floats[1] + _obj.m_floats[3] * m_floats[1] + crossValue.y();
				m_floats[2] = m_floats[3] * _obj.m_floats[2] + _obj.m_floats[3] * m_floats[2] + crossValue.z();
				m_floats[3] = m_floats[3] * _obj.m_floats[3] - base.dot(_obj.getVectorV());
				return *this;
			}
			/**
			 * @brief Multiply this quaternion by the other.
			 * @param _obj The other quaternion
			 * @return New quaternion containing the value
			 */
			Quaternion operator*(const Quaternion& _obj) const {
				etk::Quaternion tmp = *this;
				tmp *= _obj;
				return tmp;
			}
			/**
			 * @brief Operator* with a vector. This methods rotates a point given the rotation of a quaternion
			 * @param[in] _point Point to move
			 * @return Point with the updated position
			 */
			vec3 operator*(const vec3& _point) const {
				// TODO :Xheck this ==> if seams a little complicated ...
				Quaternion p(0.0, _point);
				return (((*this) * p) * getConjugate()).getVectorV();
			}
			/**
			 * @brief Set each element to the max of the current values and the values of another Vector
			 * @param _obj The other Vector to compare with
			 */
			void setMax(const Quaternion& _obj) {
				std::max(m_floats[0], _obj.m_floats[0]);
				std::max(m_floats[1], _obj.m_floats[1]);
				std::max(m_floats[2], _obj.m_floats[2]);
				std::max(m_floats[3], _obj.m_floats[3]);
			}
			/**
			 * @brief Set each element to the min of the current values and the values of another Vector
			 * @param _obj The other Vector to compare with
			 */
			void setMin(const Quaternion& _obj) {
				std::min(m_floats[0], _obj.m_floats[0]);
				std::min(m_floats[1], _obj.m_floats[1]);
				std::min(m_floats[2], _obj.m_floats[2]);
				std::min(m_floats[3], _obj.m_floats[3]);
			}
			/**
			 * @brief Set Value on the quaternion
			 * @param[in] _xxx X value.
			 * @param[in] _yyy Y value.
			 * @param[in] _zzz Z value.
			 * @param[in] _www W value.
			 */
			void setValue(const float& _xxx, const float& _yyy, const float& _zzz, const float& _www) {
				m_floats[0]=_xxx;
				m_floats[1]=_yyy;
				m_floats[2]=_zzz;
				m_floats[3]=_www;
			}
			/**
			 * @brief Set 0 value on all the quaternion
			 */
			void setZero() {
				setValue(0,0,0,0);
			}
			/**
			 * @brief get a 0 value on all a quaternion
			 * @return a zero quaternion
			 */
			static Quaternion zero();
			/**
			 * @brief Check if the quaternion is equal to (0,0,0,0)
			 * @return true The value is equal to (0,0,0,0)
			 * @return false The value is NOT equal to (0,0,0,0)
			 */
			bool isZero() const {
				return    m_floats[0] == 0
				       && m_floats[1] == 0
				       && m_floats[2] == 0
				       && m_floats[3] == 0;
			}
			/**
			 * @brief Set identity value at the quaternion
			 */
			void setIdentity() {
				setValue(0,0,0,1);
			}
			/**
			 * @brief get an identity quaternion
			 * @return an identity quaternion
			 */
			static Quaternion identity();
			/**
			 * @brief get x, y, z in a vec3
			 */
			vec3 getVectorV() const {
				return vec3(m_floats[0],
				            m_floats[1],
				            m_floats[2]);
			}
			/**
			 * @brief Inverse the quaternion
			 */
			void inverse() {
				float invLengthSquare = 1.0f / length2();
				m_floats[0] *= -invLengthSquare;
				m_floats[1] *= -invLengthSquare;
				m_floats[2] *= -invLengthSquare;
				m_floats[3] *= invLengthSquare;
			}
			/**
			 * @brief Return the inverse of the quaternion
			 * @return inverted quaternion
			 */
			Quaternion getInverse() const {
				etk::Quaternion tmp = *this;
				tmp.inverse();
				return tmp;
			}
			/**
			 * @brief Return the unit quaternion
			 * @return Quaternion unitarised
			 */
			Quaternion getUnit() const {
				return normalized();
			}
			/**
			 * @brief Conjugate the quaternion
			 */
			void conjugate() {
				m_floats[0] *= -1.0f;
				m_floats[1] *= -1.0f;
				m_floats[2] *= -1.0f;
			}
			/**
			 * @brief Return the conjugate of the quaternion
			 * @return Conjugate quaternion
			 */
			Quaternion getConjugate() const {
				etk::Quaternion tmp = *this;
				tmp.conjugate();
				return tmp;
			}
			/**
			 * @brief Compute the rotation angle (in radians) and the rotation axis
			 * @param[out] _angle Angle of the quaternion
			 * @param[out] _axis Axis of the quaternion
			 */
			void getAngleAxis(float& _angle, vec3& _axis) const;
			/**
			 * @brief Get the orientation matrix corresponding to this quaternion
			 * @return the 3x3 transformation matrix
			 */
			etk::Matrix3x3 getMatrix() const;
			/**
			 * @brief Compute the spherical linear interpolation between two quaternions.
			 * @param[in] _obj1 First quaternion
			 * @param[in] _obj2 Second quaternion
			 * @param[in] _ttt linar coefficient interpolation to be such that [0..1]
			 */
			static Quaternion slerp(const Quaternion& _obj1, const Quaternion& _obj2, float _ttt);
			/**
			 * @brief Configure the quaternion with euler angles.
			 * @param[out] _angles Eular angle of the quaternion.
			 */
			void setEulerAngles(const vec3& _angles);
	};
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const etk::Quaternion& _obj);
}

