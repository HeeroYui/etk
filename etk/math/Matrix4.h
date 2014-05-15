/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/types.h>

#ifndef __ETK_TYPES_MATRIX4_H__
#define __ETK_TYPES_MATRIX4_H__

#include <math.h>
#include <etk/math/Vector3D.h>

#define DEG_TO_RAD(a)       ((a)*M_PI/180.0f)
#define RAD_TO_DEG(a)       ((a)*180.0f/M_PI)

namespace etk {
	class Matrix4 {
		public:
			float m_mat[4*4];
			void identity() {
				for(int32_t iii=0; iii<4*4 ; iii++) {
					m_mat[iii] = 0;
				}
				m_mat[0] = 1.0;
				m_mat[5] = 1.0;
				m_mat[10] = 1.0;
				m_mat[15] = 1.0;
			}
			/*****************************************************
			 *    Constructor
			 *****************************************************/
			Matrix4() {
				identity();
			}
			Matrix4(const Matrix4& obj) {
				for(int32_t iii=0; iii<4*4 ; iii++) {
					m_mat[iii] = obj.m_mat[iii];
				}
			}
			Matrix4(float a1, float b1, float c1, float d1,
			       float a2, float b2, float c2, float d2,
			       float a3, float b3, float c3, float d3,
			       float a4, float b4, float c4, float d4) {
				m_mat[0] = a1;
				m_mat[1] = b1;
				m_mat[2] = c1;
				m_mat[3] = d1;
				m_mat[4] = a2;
				m_mat[5] = b2;
				m_mat[6] = c2;
				m_mat[7] = d2;
				m_mat[8] = a3;
				m_mat[9] = b3;
				m_mat[10] = c3;
				m_mat[11] = d3;
				m_mat[12] = a4;
				m_mat[13] = b4;
				m_mat[14] = c4;
				m_mat[15] = d4;
			}
			Matrix4(float * obj) {
				if (NULL == obj) {
					identity();
					return;
				}
				for(int32_t iii=0; iii<4*4 ; iii++) {
					m_mat[iii] = obj[iii];
				}
			}
			/*****************************************************
			 *    Destructor
			 *****************************************************/
			virtual ~Matrix4() {
				
			}
			/*****************************************************
			 *    = assigment
			 *****************************************************/
			const Matrix4& operator= (const Matrix4& obj ) {
				for(int32_t iii=0; iii<4*4 ; iii++) {
					m_mat[iii] = obj.m_mat[iii];
				}
				return *this;
			}
			/*****************************************************
			 *    == operator
			 *****************************************************/
			bool  operator== (const Matrix4& obj) const {
				for(int32_t iii=0; iii<4*4 ; iii++) {
					if(m_mat[iii] != obj.m_mat[iii]) {
						return false;
					}
				}
				return true;
			}
			/*****************************************************
			 *    != operator
			 *****************************************************/
			bool  operator!= (const Matrix4& obj) const {
				for(int32_t iii=0; iii<4*4 ; iii++) {
					if(m_mat[iii] != obj.m_mat[iii]) {
						return true;
					}
				}
				return false;
			}
			/*****************************************************
			 *    += operator
			 *****************************************************/
			const Matrix4& operator+= (const Matrix4& obj) {
				for(int32_t iii=0; iii<4*4 ; iii++) {
					m_mat[iii] += obj.m_mat[iii];
				}
				return *this;
			}
			/*****************************************************
			 *    + operator
			 *****************************************************/
			Matrix4 operator+ (const Matrix4& obj) const {
				Matrix4 tmpp(*this);
				tmpp += obj;
				return tmpp;
			}
			/*****************************************************
			 *    -= operator
			 *****************************************************/
			const Matrix4& operator-= (const Matrix4& obj) {
				for(int32_t iii=0; iii<4*4 ; iii++) {
					m_mat[iii] -= obj.m_mat[iii];
				}
				return *this;
			}
			/*****************************************************
			 *    - operator
			 *****************************************************/
			Matrix4 operator- (const Matrix4& obj) const {
				Matrix4 tmpp(*this);
				tmpp += obj;
				return tmpp;
			}
			/*****************************************************
			 *    *= operator
			 *****************************************************/
			const Matrix4& operator*= (const Matrix4& obj) {
				// output Matrix
				float matrixOut[4*4];
				for(int32_t jjj=0; jjj<4 ; jjj++) {
					float* tmpLeft = m_mat + jjj*4;
					for(int32_t iii=0; iii<4 ; iii++) {
						const float* tmpUpper = obj.m_mat+iii;
						float* tmpLeft2 = tmpLeft;
						float tmpElement = 0;
						for(int32_t kkk=0; kkk<4 ; kkk++) {
							tmpElement += *tmpUpper * *tmpLeft2;
							tmpUpper += 4;
							tmpLeft2++;
						}
						matrixOut[jjj*4+iii] = tmpElement;
					}
				}
				// set it at the output
				for(int32_t iii=0; iii<4*4 ; iii++) {
					m_mat[iii] = matrixOut[iii];
				}
				return *this;
			}
			/*****************************************************
			 *    * operator
			 *****************************************************/
			Matrix4 operator* (const Matrix4& obj) const {
				Matrix4 tmpp(*this);
				tmpp *= obj;
				return tmpp;
			}
			vec3 operator*(const vec3& point) const
			{
				return vec3( m_mat[0]*point.x() + m_mat[1]*point.y() + m_mat[2]*point.z()  + m_mat[3],
				             m_mat[4]*point.x() + m_mat[5]*point.y() + m_mat[6]*point.z()  + m_mat[7],
				             m_mat[8]*point.x() + m_mat[9]*point.y() + m_mat[10]*point.z() + m_mat[11] );
			}
			/*****************************************************
			 *  other basic function :
			 *****************************************************/
			void transpose()
			{
				float tmpVal = m_mat[1];
				m_mat[1] = m_mat[4];
				m_mat[4] = tmpVal;
				
				tmpVal = m_mat[2];
				m_mat[2] = m_mat[8];
				m_mat[8] = tmpVal;
				
				tmpVal = m_mat[6];
				m_mat[6] = m_mat[9];
				m_mat[9] = tmpVal;
				
				tmpVal = m_mat[3];
				m_mat[3] = m_mat[12];
				m_mat[12] = tmpVal;
				
				tmpVal = m_mat[7];
				m_mat[7] = m_mat[13];
				m_mat[13] = tmpVal;
				
				tmpVal = m_mat[11];
				m_mat[11] = m_mat[14];
				m_mat[14] = tmpVal;
			}
			void scale(const vec3& p)
			{
				scale(p.x(), p.y(), p.z());
			}
			void scale(float sx, float sy, float sz)
			{
				m_mat[0] *= sx;	m_mat[1] *= sy;	m_mat[2] *= sz;
				m_mat[4] *= sx;	m_mat[5] *= sy;	m_mat[6] *= sz;
				m_mat[8] *= sx;	m_mat[9] *= sy;	m_mat[10] *= sz;
			}
			/**
			 * @brief Makes a rotation matrix about an arbitrary axis.
			 * @param[in] vect vector to apply the angle.
			 * @param[in] angleRad angle to apply.
			 */
			void rotate(const vec3& vect, float angleRad=0.0);
			/**
			 * @brief Makes a translation of the matrix
			 * @param[in] vect Translation to apply.
			 */
			void translate(const vec3& vect);
			/**
			 * @brief Computes a cofactor. Used for matrix inversion.
			 * @param[in] row Id of raw.
			 * @param[in] col Id of colomn.
			 * @return the coFactorValue.
			 */
			float coFactor(int32_t row, int32_t col) const;
			/**
			 * @brief Computes the determinant of the matrix.
			 * @return The determinent Value.
			 */
			float determinant() const;
			/**
			 * @brief Inverts the matrix.
			 * @note The determinant must be != 0, otherwithe the matrix can't be inverted.
			 * @return The inverted matrix.
			 */
			Matrix4 invert();
	};
	Matrix4 matFrustum(float xmin, float xmax, float ymin, float ymax, float zNear, float zFar);
	Matrix4 matPerspective(float foxy, float aspect, float zNear, float zFar);
	Matrix4 matOrtho(float left, float right, float bottom, float top, float nearVal, float farVal);
	Matrix4 matTranslate(vec3 vect);
	Matrix4 matScale(vec3 vect);
	Matrix4 matRotate(vec3 vect, float angleRad=0.0);
	Matrix4 matRotate2(vec3 vect);
	Matrix4 matLookAt(vec3 eye,
	                  vec3 center,
	                  vec3 up);
	/**
	 * @brief Debug operator To display the curent element in a Human redeable information
	 */
	std::ostream& operator <<(std::ostream& _os, const etk::Matrix4& _obj);
};


// To siplify the writing of the code ==> this permit to have the same name with the glsl language...
typedef etk::Matrix4  mat4;

#endif
