/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once
#include <etk/types.hpp>

// Libraries
#include <etk/math/Matrix3x3.hpp>
#include <etk/math/Vector3D.hpp>
#include <etk/math/Quaternion.hpp>

namespace etk {
	/**
	 * @brief This class represents a position and an orientation in 3D. It can also be seen as representing a translation and a rotation.
	 */
	class Transform {
		public:
			Transform():
			  m_position(vec3(0.0, 0.0, 0.0)),
			  m_orientation(Quaternion::identity()) {
				
			}
			Transform(const vec3& _position, const Matrix3x3& _orientation):
			  m_position(_position),
			  m_orientation(Quaternion(_orientation)) {
				
			}
			Transform(const vec3& _position, const Quaternion& _orientation):
			  m_position(_position),
			  m_orientation(_orientation) {
				
			}
			Transform(const Transform& _other):
			  m_position(_other.m_position),
			  m_orientation(_other.m_orientation) {
				
			}
		protected:
			vec3 m_position; //! Position
		public:
			/// Return the origin of the transform
			const vec3& getPosition() const {
				return m_position;
			}
			/// Set the origin of the transform
			void setPosition(const vec3& _position) {
				m_position = _position;
			}
		protected:
			Quaternion m_orientation; //!< Orientation
		public:
			/// Return the orientation quaternion
			const Quaternion& getOrientation() const {
				return m_orientation;
			}
			/// Set the rotation quaternion
			void setOrientation(const Quaternion& _orientation) {
				m_orientation = _orientation;
			}
		public:
			/// Set the transform to the identity transform
			void setToIdentity() {
				m_position = vec3(0.0, 0.0, 0.0);
				m_orientation = Quaternion::identity();
			}
			/// Set the transform from an OpenGL transform matrix
			void setFromOpenGL(float* _matrix) {
				Matrix3x3 matrix(_matrix[0], _matrix[4], _matrix[8],
				                 _matrix[1], _matrix[5], _matrix[9],
				                 _matrix[2], _matrix[6], _matrix[10]);
				m_orientation = Quaternion(matrix);
				m_position.setValue(_matrix[12], _matrix[13], _matrix[14]);
			}
			/// Get the OpenGL matrix of the transform
			void getOpenGLMatrix(float* _matrix) const {
				const Matrix3x3& matrix = m_orientation.getMatrix();
				_matrix[0] = matrix[0][0];
				_matrix[1] = matrix[1][0];
				_matrix[2] = matrix[2][0];
				_matrix[3] = 0.0;
				_matrix[4] = matrix[0][1];
				_matrix[5] = matrix[1][1];
				_matrix[6] = matrix[2][1];
				_matrix[7] = 0.0;
				_matrix[8] = matrix[0][2];
				_matrix[9] = matrix[1][2];
				_matrix[10] = matrix[2][2];
				_matrix[11] = 0.0;
				_matrix[12] = m_position.x();
				_matrix[13] = m_position.y();
				_matrix[14] = m_position.z();
				_matrix[15] = 1.0;
			}
			/// Return the inverse of the transform
			Transform getInverse() const  {
				const Quaternion& invQuaternion = m_orientation.getInverse();
				Matrix3x3 invMatrix = invQuaternion.getMatrix();
				return Transform(invMatrix * (-m_position), invQuaternion);
			}
			/// Return an interpolated transform
			Transform interpolateTransforms(const Transform& _old,
			                                const Transform& _new,
			                                float _interpolationFactor) {
				vec3 interPosition = _old.m_position * (decimal(1.0) - _interpolationFactor) +
				                     _new.m_position * _interpolationFactor;
				Quaternion interOrientation = Quaternion::slerp(_old.m_orientation,
				                                                _naw.m_orientation,
				                                                _interpolationFactor);
				return Transform(interPosition, interOrientation);
			}
			/// Return the identity transform
			Transform identity() {
				return Transform(vec3(0, 0, 0), Quaternion::identity());
			}
			/// Return the transformed vector
			vec3 operator*(const vec3& _vector) const {
				return (m_orientation.getMatrix() * _vector) + m_position;
			}
			/// Operator of multiplication of a transform with another one
			Transform operator*(const Transform& _transform2) const {
				return Transform(m_position + m_orientation.getMatrix() * _transform2.m_position,
				                 m_orientation * _transform2.m_orientation);
			}
			/// Return true if the two transforms are equal
			bool operator==(const Transform& _transform2) const {
				return (m_position == _transform2.m_position) && (m_orientation == _transform2.m_orientation);
			}
			/// Return true if the two transforms are different
			bool operator!=(const Transform& _transform2) const {
				return !(*this == _transform2);
			}
			/// Assignment operator
			Transform& operator=(const Transform& _transform) {
				if (&_transform != this) {
					m_position = _transform.m_position;
					m_orientation = _transform.m_orientation;
				}
				return *this;
			}
	};
}


