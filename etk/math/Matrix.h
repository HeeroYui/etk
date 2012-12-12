/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_TYPES_MATRIX_H__
#define __ETK_TYPES_MATRIX_H__

#include <etk/types.h>
#include <etk/math/Vector2D.h>
#include <etk/Vector.h>

namespace etk
{
	template <typename T> class Matrix
	{
		private:
			etk::Vector2D<int32_t> m_size;
			etk::Vector<T>         m_data;
		public:
			/*****************************************************
			 *    Constructor
			 *****************************************************/
			Matrix(Vector2D<int32_t> size, T* defaultVal=NULL) :
				m_size(size),
				etk::Vector2D<T>(size.x* size.y)
			{
				if (NULL != defaultVal) {
					// copy all the elements
					for(int32_t iii=0; iii<=m_size.x*m_size.y; iii++) {
						// cast and set value : 
						m_data[iii] = (T)defaultVal++;
					}
				} else {
					Clear();
				}
			};
			Matrix(int32_t width=0, int32_t heigh=0, T* defaultVal=NULL) :
				m_size(width, heigh),
				etk::Vector2D<T>(width*heigh)
			{
				if (NULL != defaultVal) {
					// copy all the elements
					for(int32_t iii=0; iii<=m_size.x*m_size.y; iii++) {
						// cast and set value : 
						m_data[iii] = (T)defaultVal++;
					}
				} else {
					Clear();
				}
			};
			Matrix(const Matrix<double>& obj) :
				m_size(obj.m_size.x, obj.m_size.y),
				etk::Vector2D<T>(obj.m_size.x* obj.m_size.y)
			{
				// copy all the elements
				for(int32_t iii=0; iii<=m_size.x*m_size.y; iii++) {
					// cast and set value : 
					m_data[iii] = (T)obj.m_data[iii];
				}
			};
			Matrix(const Matrix<float>& obj) :
				m_size(obj.m_size.x, obj.m_size.y),
				etk::Vector2D<T>(obj.m_size.x* obj.m_size.y)
			{
				// copy all the elements
				for(int32_t iii=0; iii<=m_size.x*m_size.y; iii++) {
					// cast and set value : 
					m_data[iii] = (T)obj.m_data[iii];
				}
			};
			Matrix(const Matrix<int32_t>& obj) :
				m_size(obj.m_size.x, obj.m_size.y),
				etk::Vector2D<T>(obj.m_size.x* obj.m_size.y)
			{
				// copy all the elements
				for(int32_t iii=0; iii<=m_size.x*m_size.y; iii++) {
					// cast and set value : 
					m_data[iii] = (T)obj.m_data[iii];
				}
			};
			/*****************************************************
			 *    Destructor
			 *****************************************************/
			virtual ~Matrix(void) {};
			
			/*****************************************************
			 *    = assigment
			 *****************************************************/
			const Matrix<T>& operator= (const Matrix<T>& obj )
			{
				// check if it was the same pointer
				if( this == &obj ) {
					return *this;
				}
				// copy data :
				m_size = obj.m_size;
				m_data = obj.m_data;
				return *this;
			};
			const Matrix<T>& operator= (T& value)
			{
				// set data :
				for (int32_t iii=0; iii<m_data.Size(); iii++) {
					m_data = value;
				}
				return *this;
			};
			/*****************************************************
			 *    == operator
			 *****************************************************/
			bool  operator== (const Matrix<T>& obj) const
			{
				return (m_data == obj.m_data);
			};
			/*****************************************************
			 *    != operator
			 *****************************************************/
			bool  operator!= (const Matrix<T>& obj) const
			{
				return (m_data != obj.m_data);
			};
			/*****************************************************
			 *    += operator
			 *****************************************************/
			const Matrix<T>& operator+= (const Matrix<T>& obj)
			{
				if (m_size != obj.m_size) {
					//TK_CRITICAL("add 2 Matrix with différent size ... ==> generate the max size of all the 2 matrix");
					etk::Matrix<T> tmpMatrix(etk_max(m_size.x,obj.m_size.x), etk_max(m_size.y,obj.m_size.y));
					for (int32_t jjj=0; jjj< m_size.y; jjj++) {
						T* tmpPointer = tmpMatrix[jjj];
						T* tmpPointerIn = (*this)[jjj];
						for (int32_t iii=0; iii< m_size.x; iii++) {
							tmpPointer[iii] = tmpPointerIn[iii];
						}
					}
					for (int32_t jjj=0; jjj< obj.m_size.y; jjj++) {
						T* tmpPointer = tmpMatrix[jjj];
						T* tmpPointerIn = obj[jjj];
						for (int32_t iii=0; iii< obj.m_size.x; iii++) {
							tmpPointer[iii] += tmpPointerIn[iii];
						}
					}
					// copy in local :
					m_size = tmpMatrix.m_size;
					m_data = tmpMatrix.m_data;
				} else {
					// copy data for the same size :
					for (int32_t iii=0; iii< m_data.Size(); iii++) {
						m_data[iii] += obj.m_data[iii];
					}
				}
				return *this;
			};
			/*****************************************************
			 *    + operator
			 *****************************************************/
			Matrix<T> operator+ (const Matrix<T>& obj) {
				Matrix<T> tmpp(*this);
				tmpp += obj;
				return tmpp;
			}
			/*****************************************************
			 *    -= operator
			 *****************************************************/
			const Matrix<T>& operator-= (const Matrix<T>& obj)
			{
				if (m_size != obj.m_size) {
					//TK_CRITICAL("less 2 Matrix with diffÃ©rent size ... ==> generate the max size of all the 2 matrix");
					etk::Matrix<T> tmpMatrix(etk_max(m_size.x,obj.m_size.x), etk_max(m_size.y,obj.m_size.y));
					for (int32_t jjj=0; jjj< m_size.y; jjj++) {
						T* tmpPointer = tmpMatrix[jjj];
						T* tmpPointerIn = (*this)[jjj];
						for (int32_t iii=0; iii< m_size.x; iii++) {
							tmpPointer[iii] = tmpPointerIn[iii];
						}
					}
					for (int32_t jjj=0; jjj< obj.m_size.y; jjj++) {
						T* tmpPointer = tmpMatrix[jjj];
						T* tmpPointerIn = obj[jjj];
						for (int32_t iii=0; iii< obj.m_size.x; iii++) {
							tmpPointer[iii] -= tmpPointerIn[iii];
						}
					}
					// copy in local :
					m_size = tmpMatrix.m_size;
					m_data = tmpMatrix.m_data;
				} else {
					// copy data for the same size :
					for (int32_t iii=0; iii< m_data.Size(); iii++) {
						m_data[iii] -= obj.m_data[iii];
					}
				}
				return *this;
			};
			/*****************************************************
			 *    - operator
			 *****************************************************/
			Matrix<T> operator- (const Matrix<T>& obj) {
				Matrix<T> tmpp(*this);
				tmpp += obj;
				return tmpp;
			}
			/*****************************************************
			 *    *= operator
			 *****************************************************/
			const Matrix<T>& operator*= (const Matrix<T>& obj)
			{
				if(    m_size.x != obj.m_size.y
				    || m_size.y != obj.m_size.x) {
					//TK_CRITICAL("Error while multipliying 2 matrix with different size ==> impossible case ...");
					return *this;
				}
				etk::Matrix<T> tmpMatrix(m_size);
				for (int32_t jjj=0; jjj< obj.m_size.y; jjj++) {
					for (int32_t iii=0; iii< obj.m_size.x; iii++) {
						T tmpVal = 0;
						for (int32_t kkk=0; kkk< obj.m_size.x; kkk++) {
							tmpVal += (*this)[jjj][iii+kkk] * obj[jjj+kkk][iii];
						}
						tmpMatrix[jjj][iii] = tmpVal;
					}
				}
				// copy in local :
				m_data = tmpMatrix.m_data;
				return *this;
			};
			/*****************************************************
			 *    * operator
			 *****************************************************/
			Matrix<T> operator* (const Matrix<T>& obj) {
				Matrix tmpp(*this);
				tmpp *= obj;
				return tmpp;
			}
			/*****************************************************
			 *    [] operator
			 *****************************************************/
			const T* operator[] (int32_t line) const {
				return &m_data[line*m_size.x];
			}
			T* operator[] (int32_t line) {
				return &m_data[line*m_size.x];
			}
			/*****************************************************
			 *    () operator
			 *****************************************************/
			T& operator () (int32_t line, int32_t colomn) {
				return m_data[line*m_size.x + colomn];
			}
			/*****************************************************
			 *    - operator
			 *****************************************************/
			Matrix<T> operator - (void) {
				Matrix<T> tmp(m_size);
				for (int32_t iii=0; iii<m_data.Size(); iii++) {
					tmp.m_data[iii] = -m_data[iii];
				return tmp;
			}
			/*****************************************************
			 *    Other mathematical function
			 *****************************************************/
			/**
			 * @ brief Transpose Matrix
			 * @ return the transpose matrix
			 */
			Matrix<T> Transpose(void)
			{
				// create a matrix with the inverted size
				Matrix<T> tmpMatrix(m_size.x, m_size.y);
				for (int32_t jjj=0; jjj< m_size.y; jjj++) {
					for (int32_t iii=0; iii< m_size.x; iii++) {
						tmpMatrix(jjj,iii) = (*this)(iii,jjj);
					}
				}
				return tmpMatrix;
			};
			/**
			 * @ brief Create a convolution on the matrix : set convolution on the lines
			 * @ param[in] obj The convolution operator
			 * @ return the value of the convolution
			 */
			Matrix<T>& Convolution(Matrix<T>& obj)
			{
				Matrix<T> tmppp(1,1);
				// TODO : ...
				return tmppp;
			};
			/**
			 * @ brief generate a devide of the curent Matrix with the specify power of 2
			 * @ param[in] decalage The power of 2 of the division
			 * @ return the result
			 */
			Matrix<T>& Fix(int32_t decalage)
			{
				Matrix<T> tmppp(m_size);
				T tmpVal = 0;
				for(int32_t iii=0; iii<m_data.Size(); iii++) {
					tmpVal = m_data[iii];
					if (tmpVal < 0 && (tmpVal & ~(~0 << decalage))) {
						tmpVal = tmpVal >> decalage;
						tmpVal++;
					} else {
						tmpVal = tmpVal >> decalage;
					}
					tmppp.m_data[iii] = tmpVal;
				}
				return tmppp;
			};
			/**
			 * @ brief generate a devide of the curent Matrix with the specify power of 2
			 * @ param[in] decalage The power of 2 of the division
			 * @ return the result
			 */
			Matrix<T>& Round(int32_t decalage)
			{
				Matrix<T> tmppp(m_size);
				for(int32_t iii=0; iii<m_data.Size(); iii++) {
					tmppp.m_data[iii] = ( m_data[iii]+(1<<(decalage-1)) ) >> decalage;
				}
				return tmppp;
			};
			/**
			 * @ brief Generate a resised matrix
			 * @ param[in] size new output size
			 * @ return Te resied matrix
			 */
			Matrix<T>& Resize(etk::Vector2D<int32_t> size)
			{
				Matrix<T> tmppp(size);
				for(int32_t iii=0; iii<m_data.m_size.x && iii<tmppp.m_size.x; iii++) {
					for(int32_t jjj=0; jjj<m_data.m_size.y && jjj<tmppp.m_size.y; jjj++) {
						tmppp(iii,jjj) = (*this)(iii,jjj);
					}
				}
				return tmppp;
			};
			/**
			 * @brief Select element in the matrix from a list of element Ids
			 * @param[in] np Width of the output matrix
			 * @param[in] p  List pointer of x
			 * @param[in] np Heigh of the output matrix
			 * @param[in] q  List pointer of y
			 * @return the new matrix
			 */
			Matrix<T>& Select(int32_t np, int32_t *p, int32_t nq, int32_t *q)
			{
				if (np < 1 || nq < 1) {
					TK_WARNING("bad index array sizes");
				}
				Matrix<T> tmppp(np,nq);
				for (int32_t iii=0; iii<np; iii++) {
					for (int32_t jjj=0; jjj<nq; jjj++) {
						if(    p[i] < 0
						    || p[i] >= m_size.x
						    || q[i] < 0
						    || q[i] >= m_size.y) {
							TK_WARNING("bad index arrays");
						}
						tmppp(iii,jjj) = (*this)(p[i],q[j]);
					}
				}
				return tmppp;
			}
			/*****************************************************
			 *    utilities :
			 *****************************************************/
			/**
			 * @brief Clear the Upper triangle of the current Matrix
			 * <pre>
			 *   x 0 0 0 0
			 *   x x 0 0 0
			 *   x x x 0 0
			 *   x x x x 0
			 *   x x x x x
			 * </pre>
			 */
			void ClearUpperTriangle(void)
			{
				if (m_size.x != m_size.y) {
					TK_WARNING("better to do with square Matrix");
				}
				for (int32_t iii=0; iii<m_size.x; iii++) {
					for (int32_t jjj=iii+1; jjj<m_size.y; jjj++)
						m_data[iii*m_size.x + jjj] = 0;
					}
				}
			};
			/**
			 * @brief Clear the Lower triangle of the current Matrix
			 * <pre>
			 *   x x x x x
			 *   0 x x x x
			 *   0 0 x x x
			 *   0 0 0 x x
			 *   0 0 0 0 x
			 * </pre>
			 */
			void ClearLowerTriangle(void)
			{
				if (m_size.x != m_size.y) {
					TK_WARNING("better to do with square Matrix");
				}
				for (int32_t iii=0; iii<m_size.x; iii++) {
					for (int32_t jjj=0; jjj<m_size.y && jjj<iii; jjj++)
						m_data[iii*m_size.x + jjj] = 0;
					}
				}
			};
			/**
			 * @brief Generate a compleate random Matrix.
			 * @param[in] range The min/max value of the random Generation [-range..range].
			 */
			void MakeRandom(float range)
			{
				for(int32_t iii=0; iii<m_data.Size(); iii++) {
					m_data[iii] = (T)etk::tool::frand(-range, range);
				}
			};
			/**
			 * @brief Return the maximum of the diff for this Matrix.
			 * @param[in] input The compared Matix.
			 * @return The absolute max value.
			 */
			T MaxDifference(const Matrix<T>& input)
			{
				if (m_size != input.m_size)
					TK_WARNING("better to do with same size Matrix");
				}
				T max = 0;
				for(int32_t iii=0; iii<m_data.Size() && iii<input.m_data.Size(); iii++) {
					T diff = m_data[iii] - input.m_data[iii];
					if (diff<0) {
						diff = -diff;
					}
					if (diff > max)
						max = diff;
					}
				}
				return max;
			};
			/**
			 * @brief Clear all the matrix.
			 */
			void Clear(void)
			{
				// copy data for the same size :
				for (int32_t iii=0; iii< m_size.x*m_size.y; iii++) {
					m_data[iii] = (T)0;
				}
			};
			/**
			 * @brief Set the diagonal at 1
			 */
			void Identity(void)
			{
				// copy data for the same size :
				for (int32_t iii=0; iii< etk_min(m_size.x, m_size.y); iii++) {
					(*this)(iii,iii) = (T)1;
				}
			};
			/**
			 * @brief Clear and set the diagonal at 1
			 */
			void Eye(void)
			{
				Clear();
				Identity();
			};
			/**
			 * @brief Get the size of the current Matrix.
			 * @return Dimention of the matrix
			 */
			Vector2D<int32_t> Size(void)
			{
				return m_size;
			};
	};
};

// To siplify the writing of the code ==> this is not compatible with GLSL ...
typedef etk::Matrix<float>       mat;
typedef etk::Matrix<int32_t>    imat;
typedef etk::Matrix<uint32_t>  uimat;

#endif
