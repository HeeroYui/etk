/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <etk/types.h>
#include <etk/math/Vector2D.h>
#include <vector>

namespace etk {
	template <typename T> class Matrix {
		private:
			ivec2 m_size;
			std::vector<T> m_data;
		public:
			/*****************************************************
			 *    Constructor
			 *****************************************************/
			Matrix(ivec2 _size, T* _defaultVal=nullptr) :
			  m_size(_size),
			  etk::Vector2D<T>(_size.x.x()* _size.y()) {
				if (defaultVal != nullptr) {
					// copy all the elements
					for(int32_t iii=0; iii<=m_size.x()*m_size.y(); iii++) {
						// cast and set value : 
						m_data[iii] = T(_defaultVal++);
					}
				} else {
					Clear();
				}
			};
			Matrix(int32_t _width=0, int32_t _heigh=0, T* _defaultVal=nullptr) :
			  m_size(_width, _heigh),
			  etk::Vector2D<T>(_width*_heigh) {
				if (_defaultVal != nullptr) {
					// copy all the elements
					for(int32_t iii=0; iii<=m_size.x()*m_size.y(); iii++) {
						// cast and set value : 
						m_data[iii] = (T)_defaultVal++;
					}
				} else {
					Clear();
				}
			};
			Matrix(const Matrix<double>& obj) :
			  m_size(_obj.m_size),
			  etk::Vector2D<T>(_obj.m_size.x()* _obj.m_size.y()) {
				// copy all the elements
				for(int32_t iii=0; iii<=m_size.x()*m_size.y(); iii++) {
					// cast and set value : 
					m_data[iii] = (T)_obj.m_data[iii];
				}
			}
			Matrix(const Matrix<float>& _obj) :
			  m_size(_obj.m_size),
			  etk::Vector2D<T>(_obj.m_size.x()* _obj.m_size.y()) {
				// copy all the elements
				for(int32_t iii=0; iii<=m_size.x()*m_size.y(); iii++) {
					// cast and set value : 
					m_data[iii] = (T)_obj.m_data[iii];
				}
			}
			Matrix(const Matrix<int32_t>& _obj) :
			  m_size(_obj.m_size.x(), _obj.m_size.y()),
			  etk::Vector2D<T>(_obj.m_size.x()* _obj.m_size.y()) {
				// copy all the elements
				for (int32_t iii=0; iii<=m_size.x()*m_size.y(); iii++) {
					// cast and set value : 
					m_data[iii] = (T)_obj.m_data[iii];
				}
			}
			/*****************************************************
			 *    Destructor
			 *****************************************************/
			virtual ~Matrix() {};
			
			/*****************************************************
			 *    = assigment
			 *****************************************************/
			const Matrix<T>& operator= (const Matrix<T>& _obj ) {
				// check if it was the same pointer
				if (this == &_obj ) {
					return *this;
				}
				// copy data :
				m_size = _obj.m_size;
				m_data = _obj.m_data;
				return *this;
			};
			const Matrix<T>& operator= (T& _value) {
				// set data :
				for (int32_t iii=0; iii<m_data.size(); iii++) {
					m_data = _value;
				}
				return *this;
			};
			/*****************************************************
			 *    == operator
			 *****************************************************/
			bool operator== (const Matrix<T>& _obj) const {
				return (m_data == _obj.m_data);
			};
			/*****************************************************
			 *    != operator
			 *****************************************************/
			bool operator!= (const Matrix<T>& _obj) const {
				return (m_data != _obj.m_data);
			};
			/*****************************************************
			 *    += operator
			 *****************************************************/
			const Matrix<T>& operator+= (const Matrix<T>& _obj) {
				if (m_size != _obj.m_size) {
					//TK_CRITICAL("add 2 Matrix with différent size ... ==> generate the max size of all the 2 matrix");
					etk::Matrix<T> tmpMatrix(std::max(m_size.x(),_obj.m_size.x()), std::max(m_size.y(),_obj.m_size.y()));
					for (int32_t jjj=0; jjj< m_size.y(); jjj++) {
						T* tmpPointer = tmpMatrix[jjj];
						T* tmpPointerIn = (*this)[jjj];
						for (int32_t iii=0; iii< m_size.x(); iii++) {
							tmpPointer[iii] = tmpPointerIn[iii];
						}
					}
					for (int32_t jjj=0; jjj< _obj.m_size.y(); jjj++) {
						T* tmpPointer = tmpMatrix[jjj];
						T* tmpPointerIn = _obj[jjj];
						for (int32_t iii=0; iii< _obj.m_size.x(); iii++) {
							tmpPointer[iii] += tmpPointerIn[iii];
						}
					}
					// copy in local :
					m_size = tmpMatrix.m_size;
					m_data = tmpMatrix.m_data;
				} else {
					// copy data for the same size :
					for (int32_t iii=0; iii< m_data.size(); iii++) {
						m_data[iii] += _obj.m_data[iii];
					}
				}
				return *this;
			};
			/*****************************************************
			 *    + operator
			 *****************************************************/
			Matrix<T> operator+ (const Matrix<T>& _obj) {
				Matrix<T> tmpp(*this);
				tmpp += _obj;
				return tmpp;
			}
			/*****************************************************
			 *    -= operator
			 *****************************************************/
			const Matrix<T>& operator-= (const Matrix<T>& _obj) {
				if (m_size != _obj.m_size) {
					//TK_CRITICAL("less 2 Matrix with diffÃ©rent size ... ==> generate the max size of all the 2 matrix");
					etk::Matrix<T> tmpMatrix(std::max(m_size.x(),_obj.m_size.x()), std::max(m_size.y(),_obj.m_size.y()));
					for (int32_t jjj=0; jjj< m_size.y; jjj++) {
						T* tmpPointer = tmpMatrix[jjj];
						T* tmpPointerIn = (*this)[jjj];
						for (int32_t iii=0; iii< m_size.x(); iii++) {
							tmpPointer[iii] = tmpPointerIn[iii];
						}
					}
					for (int32_t jjj=0; jjj< _obj.m_size.y(); jjj++) {
						T* tmpPointer = tmpMatrix[jjj];
						T* tmpPointerIn = _obj[jjj];
						for (int32_t iii=0; iii< _obj.m_size.x(); iii++) {
							tmpPointer[iii] -= tmpPointerIn[iii];
						}
					}
					// copy in local :
					m_size = tmpMatrix.m_size;
					m_data = tmpMatrix.m_data;
				} else {
					// copy data for the same size :
					for (int32_t iii=0; iii< m_data.size(); iii++) {
						m_data[iii] -= _obj.m_data[iii];
					}
				}
				return *this;
			};
			/*****************************************************
			 *    - operator
			 *****************************************************/
			Matrix<T> operator- (const Matrix<T>& _obj) {
				Matrix<T> tmpp(*this);
				tmpp += _obj;
				return tmpp;
			}
			/*****************************************************
			 *    *= operator
			 *****************************************************/
			const Matrix<T>& operator*= (const Matrix<T>& _obj) {
				if(    m_size.x() != _obj.m_size.y()
				    || m_size.y() != _obj.m_size.x()) {
					//TK_CRITICAL("Error while multipliying 2 matrix with different size ==> impossible case ...");
					return *this;
				}
				etk::Matrix<T> tmpMatrix(m_size);
				for (int32_t jjj=0; jjj< _obj.m_size.y(); jjj++) {
					for (int32_t iii=0; iii< _obj.m_size.x(); iii++) {
						T tmpVal = 0;
						for (int32_t kkk=0; kkk< _obj.m_size.x(); kkk++) {
							tmpVal += (*this)[jjj][iii+kkk] * _obj[jjj+kkk][iii];
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
			Matrix<T> operator* (const Matrix<T>& _obj) {
				Matrix tmpp(*this);
				tmpp *= _obj;
				return tmpp;
			}
			/*****************************************************
			 *    [] operator
			 *****************************************************/
			const T* operator[] (int32_t _line) const {
				return &m_data[_line*m_size.x()];
			}
			T* operator[] (int32_t _line) {
				return &m_data[_line*m_size.x()];
			}
			/*****************************************************
			 *    () operator
			 *****************************************************/
			T& operator () (int32_t _line, int32_t _colomn) {
				return m_data[_line*m_size.x() + _colomn];
			}
			/*****************************************************
			 *    - operator
			 *****************************************************/
			Matrix<T> operator - () {
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
			Matrix<T> transpose() {
				// create a matrix with the inverted size
				Matrix<T> tmpMatrix(m_size);
				for (int32_t jjj=0; jjj< m_size.y(); jjj++) {
					for (int32_t iii=0; iii< m_size.x(); iii++) {
						tmpMatrix(jjj,iii) = (*this)(iii,jjj);
					}
				}
				return tmpMatrix;
			};
			/**
			 * @ brief Create a convolution on the matrix : set convolution on the lines
			 * @ param[in] _obj The convolution operator
			 * @ return the value of the convolution
			 */
			Matrix<T>& convolution(Matrix<T>& _obj) {
				Matrix<T> tmppp(1,1);
				// TODO : ...
				return tmppp;
			};
			/**
			 * @ brief generate a devide of the curent Matrix with the specify power of 2
			 * @ param[in] _decalage The power of 2 of the division
			 * @ return the result
			 */
			Matrix<T>& fix(int32_t _decalage) {
				Matrix<T> tmppp(m_size);
				T tmpVal = 0;
				for(int32_t iii=0; iii<m_data.size(); iii++) {
					tmpVal = m_data[iii];
					if (tmpVal < 0 && (tmpVal & ~(~0 << _decalage))) {
						tmpVal = tmpVal >> _decalage;
						tmpVal++;
					} else {
						tmpVal = tmpVal >> _decalage;
					}
					tmppp.m_data[iii] = tmpVal;
				}
				return tmppp;
			};
			/**
			 * @ brief generate a devide of the curent Matrix with the specify power of 2
			 * @ param[in] _decalage The power of 2 of the division
			 * @ return the result
			 */
			Matrix<T>& round(int32_t _decalage) {
				Matrix<T> tmppp(m_size);
				for(int32_t iii=0; iii<m_data.size(); iii++) {
					tmppp.m_data[iii] = ( m_data[iii]+(1<<(_decalage-1)) ) >> _decalage;
				}
				return tmppp;
			};
			/**
			 * @ brief Generate a resised matrix
			 * @ param[in] _size new output size
			 * @ return Te resied matrix
			 */
			Matrix<T>& resize(etk::Vector2D<int32_t> _size) {
				Matrix<T> tmppp(_size);
				for(int32_t iii=0; iii<m_data.m_size.x() && iii<tmppp.m_size.x(); iii++) {
					for(int32_t jjj=0; jjj<m_data.m_size.y() && jjj<tmppp.m_size.y(); jjj++) {
						tmppp(iii,jjj) = (*this)(iii,jjj);
					}
				}
				return tmppp;
			};
			/**
			 * @brief Select element in the matrix from a list of element Ids
			 * @param[in] _np Width of the output matrix
			 * @param[in] _p  List pointer of x
			 * @param[in] _np Heigh of the output matrix
			 * @param[in] _q  List pointer of y
			 * @return the new matrix
			 */
			Matrix<T>& select(int32_t _np, int32_t* _p, int32_t _nq, int32_t* _q) {
				if (_np < 1 || _nq < 1) {
					TK_WARNING("bad index array sizes");
				}
				Matrix<T> tmppp(_np, _nq);
				for (int32_t iii=0; iii<_np; iii++) {
					for (int32_t jjj=0; jjj<_nq; jjj++) {
						if(    _p[i] < 0
						    || _p[i] >= m_size.x()
						    || _q[i] < 0
						    || _q[i] >= m_size.y()) {
							TK_WARNING("bad index arrays");
						}
						tmppp(iii,jjj) = (*this)(_p[i],_q[j]);
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
			void clearUpperTriangle() {
				if (m_size.x() != m_size.y()) {
					TK_WARNING("better to do with square Matrix");
				}
				for (int32_t iii=0; iii<m_size.x(); iii++) {
					for (int32_t jjj=iii+1; jjj<m_size.y(); jjj++)
						m_data[iii*m_size.x() + jjj] = 0;
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
			void clearLowerTriangle() {
				if (m_size.x() != m_size.y()) {
					TK_WARNING("better to do with square Matrix");
				}
				for (int32_t iii=0; iii<m_size.x(); iii++) {
					for (int32_t jjj=0; jjj<m_size.y() && jjj<iii; jjj++)
						m_data[iii*m_size.x() + jjj] = 0;
					}
				}
			};
			/**
			 * @brief Generate a compleate random Matrix.
			 * @param[in] _range The min/max value of the random Generation [-range..range].
			 */
			void makeRandom(float _range) {
				for(int32_t iii=0; iii<m_data.size(); iii++) {
					m_data[iii] = (T)etk::tool::frand(-_range, _range);
				}
			};
			/**
			 * @brief Return the maximum of the diff for this Matrix.
			 * @param[in] _input The compared Matix.
			 * @return The absolute max value.
			 */
			T maxDifference(const Matrix<T>& _input) {
				if (m_size != _input.m_size) {
					TK_WARNING("better to do with same size Matrix");
				}
				T max = 0;
				for(int32_t iii = 0;
				    iii < m_data.size() && iii < _input.m_data.size();
				    ++iii) {
					T diff = m_data[iii] - _input.m_data[iii];
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
			void clear() {
				// copy data for the same size :
				for (int32_t iii=0; iii< m_size.x()*m_size.y(); iii++) {
					m_data[iii] = (T)0;
				}
			};
			/**
			 * @brief Set the diagonal at 1
			 */
			void identity() {
				// copy data for the same size :
				for (int32_t iii=0; iii< std::mim(m_size.x(), m_size.y()); iii++) {
					(*this)(iii,iii) = (T)1;
				}
			};
			/**
			 * @brief Clear and set the diagonal at 1
			 */
			void eye() {
				clear();
				identity();
			};
			/**
			 * @brief Get the size of the current Matrix.
			 * @return Dimention of the matrix
			 */
			Vector2D<int32_t> size() {
				return m_size;
			};
	};
}

// To siplify the writing of the code ==> this is not compatible with GLSL ...
typedef etk::Matrix<float>       mat;
typedef etk::Matrix<int32_t>    imat;
typedef etk::Matrix<uint32_t>  uimat;
