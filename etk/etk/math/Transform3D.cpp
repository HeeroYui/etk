/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#include <etk/types.hpp>
#include <etk/math/Transform3D.hpp>
#include <etk/typeInfo.hpp>

ETK_DECLARE_TYPE(etk::Transform3D);

etk::Transform3D::Transform3D():
  m_position(vec3(0.0, 0.0, 0.0)),
  m_orientation(Quaternion::identity()) {
	
}
etk::Transform3D::Transform3D(const vec3& _position, const Matrix3x3& _orientation):
  m_position(_position),
  m_orientation(Quaternion(_orientation)) {
	
}
etk::Transform3D::Transform3D(const vec3& _position, const Quaternion& _orientation):
  m_position(_position),
  m_orientation(_orientation) {
	
}
etk::Transform3D::Transform3D(const Transform3D& _other):
  m_position(_other.m_position),
  m_orientation(_other.m_orientation) {
	
}

etk::Transform3D etk::Transform3D::identity() {
	return etk::Transform3D(vec3(0.0, 0.0, 0.0), Quaternion::identity());
}

etk::Stream& etk::operator <<(etk::Stream& _os, const etk::Transform3D& _obj) {
	_os << "transform3D(" << _obj.getPosition() << ";" << _obj.getOrientation() << ")";
	return _os;
}

