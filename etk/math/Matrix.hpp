/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/math/Vector2D.hpp>
#include <etk/Vector.hpp>

namespace etk {
	/**
	 * @brief 2 dimention matrix template to manage simpliest algo
	 * @note Prototype
	 */
	template <typename T> class Matrix {
		private:
			uivec2 m_size; //!< Size of the Matrix
			etk::Vector<T> m_data; //!< Data of the matrix
		public:
			/**
			 * @brief Contructor that create a Vector with a specific size and specific raw data
			 * @param[in] _size Dimention of the matrix
			 * @param[in] _defaultVal Default list of element that might be set in the matrix
			 */
			Matrix(const ivec2& _size, T* _defaultVal=nullptr) :
			  m_size(_size),
			  etk::Vector2D<T>(_size.x()* _size.y()) {
				if (defaultVal == nullptr) {
					clear();
					return;
				}
				// copy all the elements
				for(size_t iii = 0;
				    iii <= m_size.x()*m_size.y();
				    ++iii) {
					// cast and set value : 
					m_data[iii] = T(_defaultVal++);
				}
			}
			/**
			 * @brief default contructor that create a Vector with a specific size and specific raw data
			 * @param[in] _width Dimention width of the matrix
			 * @param[in] _heigh Dimention heigh of the matrix
			 * @param[in] _defaultVal Default list of element that might be set in the matrix
			 */
			Matrix(int32_t _width=0, int32_t _heigh=0, T* _defaultVal=nullptr) :
			  m_size(_width, _heigh),
			  etk::Vector2D<T>(_width*_heigh) {
				if (_defaultVal == nullptr) {
					clear();
					return;
				}
				// copy all the elements
				for(size_t iii = 0;
				    iii <= m_size.x()*m_size.y();
				    ++iii) {
					// cast and set value : 
					m_data[iii] = T(_defaultVal++);
				}
			}
			/**
			 * @brief Copy contructor with ETK_TYPE_MATRIX_2 type matrix input
			 * @param[in] _obj Object matrix to copy
			 */
			template<class ETK_TYPE_MATRIX_2>
			Matrix(const Matrix<ETK_TYPE_MATRIX_2>& _obj) :
			  m_size(_obj.m_size),
			  etk::Vector2D<T>(_obj.m_size.x()* _obj.m_size.y()) {
				// copy all the elements
				for(size_t iii = 0;
				    iii <= m_size.x()*m_size.y();
				    ++iii) {
					// cast and set value : 
					m_data[iii] = T(_obj.m_data[iii]);
				}
			}
			/**
			 * @brief Virtualisation of destructor
			 */
			virtual ~Matrix() = default;
			
			/**
			 * @brief Operator= Asign the current object with an other object
			 * @param[in] _obj Reference on the external object
			 * @return Local reference of the vector asigned
			 */
			const Matrix<T>& operator= (const Matrix<T>& _obj ) {
				// check if it was the same pointer
				if (this == &_obj ) {
					return *this;
				}
				// copy data :
				m_size = _obj.m_size;
				m_data = _obj.m_data;
				return *this;
			}
			/**
			 * @brief Operator= Asign the current object with a unique value
			 * @param[in] _value Value to set in the matrix data
			 * @return Local reference of the vector asigned
			 */
			const Matrix<T>& operator= (T& _value) {
				// set data :
				for(size_t iii = 0;
				    iii <= m_size.x()*m_size.y();
				    ++iii) {
					m_data = _value;
				}
				return *this;
			}
			/**
			 * @brief Equality compare operator with an other object.
			 * @param[in] _obj Reference on the comparing object
			 * @return true The Objects are identical
			 * @return false The Objects are NOT identical
			 */
			bool operator== (const Matrix<T>& _obj) const {
				return (m_data == _obj.m_data);
			}
			/**
			 * @brief In-Equality compare operator with an other object.
			 * @param[in] _obj Reference on the comparing object
			 * @return true The Objects are NOT identical
			 * @return false The Objects are identical
			 */
			bool operator!= (const Matrix<T>& _obj) const {
				return (m_data != _obj.m_data);
			}
			/**
			 * @brief Operator+= Addition an other matrix with this one
			 * <pre>
			 *    (a b)   (e f)   (a+e b+f)
			 *    (c d) + (g h) = (c+g d+h)
			 * </pre>
			 * @note If the size are different, we create a matrix witth the max size of the 2 others ...
			 * @param[in] _obj Reference on the external object
			 * @return Local reference of the vector additionned
			 */
			const Matrix<T>& operator+= (const Matrix<T>& _obj) {
				if (m_size != _obj.m_size) {
					//TK_CRITICAL("add 2 Matrix with différent size ... ==> generate the max size of all the 2 matrix");
					etk::Matrix<T> tmpMatrix(etk::max(m_size.x(),_obj.m_size.x()), etk::max(m_size.y(),_obj.m_size.y()));
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
					// copy data for the same size:
					for (int32_t iii=0; iii< m_data.size(); iii++) {
						m_data[iii] += _obj.m_data[iii];
					}
				}
				return *this;
			}
			/**
			 * @brief Operator+= Addition an other matrix with this one
			 * <pre>
			 *    (a b)   (e f)   (a+e b+f)
			 *    (c d) + (g h) = (c+g d+h)
			 * </pre>
			 * @note If the size are different, we create a matrix witth the max size of the 2 others ...
			 * @param[in] _obj Reference on the external object
			 * @return New matrix containing the value
			 */
			Matrix<T> operator+ (const Matrix<T>& _obj) {
				Matrix<T> tmpp(*this);
				tmpp += _obj;
				return tmpp;
			}
			/**
			 * @brief Operator+= Addition an other matrix with this one
			 * <pre>
			 *    (a b)   (e f)   (a-e b-f)
			 *    (c d) - (g h) = (c-g d-h)
			 * </pre>
			 * @note If the size are different, we create a matrix witth the max size of the 2 others ...
			 * @param[in] _obj Reference on the external object
			 * @return Local reference of the vector additionned
			 */
			const Matrix<T>& operator-= (const Matrix<T>& _obj) {
				if (m_size != _obj.m_size) {
					//TK_CRITICAL("less 2 Matrix with different size ... ==> generate the max size of all the 2 matrix");
					etk::Matrix<T> tmpMatrix(etk::max(m_size.x(),_obj.m_size.x()), etk::max(m_size.y(),_obj.m_size.y()));
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
			/**
			 * @brief Operator+= Addition an other matrix with this one
			 * <pre>
			 *    (a b)   (e f)   (a-e b-f)
			 *    (c d) - (g h) = (c-g d-h)
			 * </pre>
			 * @note If the size are different, we create a matrix witth the max size of the 2 others ...
			 * @param[in] _obj Reference on the external object
			 * @return New matrix containing the value
			 */
			Matrix<T> operator- (const Matrix<T>& _obj) {
				Matrix<T> tmpp(*this);
				tmpp += _obj;
				return tmpp;
			}
			/**
			 * @brief Operator*= Multiplication an other matrix with this one
			 * @param[in] _obj Reference on the external object
			 * @return Local reference of the vector multiplicated
			 */
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
			/**
			 * @brief Operator* Multiplication an other matrix with this one
			 * @param[in] _obj Reference on the external object
			 * @return New matrix containing the value
			 */
			Matrix<T> operator* (const Matrix<T>& _obj) {
				Matrix tmpp(*this);
				tmpp *= _obj;
				return tmpp;
			}
			// TODO : Check if is possible to do elemntValue = mayMatrix[xxx, yyy]
			/**
			 * @brief Operator[] Access at the first element (const pointer) of a line
			 * <pre>
			 *   elemntValue = mayMatrix[YYY][xxx];
			 * </pre>
			 * @param[in] _yyy Line Id requested [0..m_size.y()]
			 * @return Const pointer on the first line element
			 */
			const T* operator[] (int32_t _yyy) const {
				return &m_data[_yyy*m_size.x()];
			}
			/**
			 * @brief Operator[] Access at the first element (pointer) of a line
			 * <pre>
			 *   elemntValue = mayMatrix[YYY][xxx];
			 * </pre>
			 * @param[in] _yyy Line Id requested [0..m_size.y()]
			 * @return Pointer on the first line element
			 */
			T* operator[] (int32_t _yyy) {
				return &m_data[_yyy*m_size.x()];
			}
			/**
			 * @brief Operator[] Access at the element at a specific position
			 * <pre>
			 *   elemntValue = mayMatrix[ivec2(xxx,yyy)];
			 * </pre>
			 * @param[in] _pos Position in the matrix
			 * @return Const Reference on the element
			 */
			const T& operator[] (const ivec2& _pos) const {
				return m_data[_pos.y()*m_size.x() + _pos.x()];
			}
			/**
			 * @brief Operator[] Access at the element at a specific position
			 * <pre>
			 *   elemntValue = mayMatrix[ivec2(xxx,yyy)];
			 * </pre>
			 * @param[in] _pos Position in the matrix
			 * @return Reference on the element
			 */
			T& operator[] (const ivec2& _pos) {
				return m_data[_pos.y()*m_size.x() + _pos.x()];
			}
			/**
			 * @brief Operator() Access at the element at a specific position
			 * <pre>
			 *   elemntValue = mayMatrix(xxx,yyy);
			 * </pre>
			 * @param[in] _xxx Colomn position in the matrix
			 * @param[in] _yyy Line position in the matrix
			 * @return Reference on the element
			 */
			T& operator () (size_t _xxx, size_t _yyy) {
				return m_data[_yyy*m_size.x() + _xxx];
			}
			/**
			 * @brief Operator- Multiply with -1
			 * @return New matrix containing the value
			 */
			Matrix<T> operator- () const {
				Matrix<T> tmp(m_size);
				for (int32_t iii=0; iii<m_data.Size(); iii++) {
					tmp.m_data[iii] = -m_data[iii];
				}
				return tmp;
			}
			/**
			 * @brief Transpose Matrix
			 * @return New matrix containing the value
			 */
			Matrix<T> transpose() const {
				// create a matrix with the inverted size
				Matrix<T> tmpMatrix(m_size);
				for (int32_t jjj=0; jjj< m_size.y(); jjj++) {
					for (int32_t iii=0; iii< m_size.x(); iii++) {
						tmpMatrix(jjj,iii) = (*this)(iii,jjj);
					}
				}
				return tmpMatrix;
			}
			/**
			 * @brief Create a convolution on the matrix : set convolution on the lines
			 * @param[in] _obj The convolution operator
			 * @return New matrix containing the current matrix concoluate
			 */
			Matrix<T> convolution(Matrix<T>& _obj) const {
				Matrix<T> tmppp(1,1);
				// TODO : ...
				return tmppp;
			}
			/**
			 * @brief generate a devide of the curent Matrix with the specify power of 2
			 * @param[in] _decalage The power of 2 of the division
			 * @return New matrix containing the matrix fix()
			 */
			Matrix<T> fix(int32_t _decalage) const {
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
			 * @brief generate a devide of the curent Matrix with the specify power of 2
			 * @param[in] _decalage The power of 2 of the division
			 * @return New matrix containing the rounded matrix
			 */
			Matrix<T> round(int32_t _decalage) const {
				Matrix<T> tmppp(m_size);
				for(int32_t iii=0; iii<m_data.size(); iii++) {
					tmppp.m_data[iii] = ( m_data[iii]+(1<<(_decalage-1)) ) >> _decalage;
				}
				return tmppp;
			};
			/**
			 * @brief Generate a resised matrix
			 * @param[in] _size new output size
			 * @return New matrix resized
			 */
			Matrix<T> resize(etk::Vector2D<int32_t> _size) const {
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
			 * @param[in] _nq Heigh of the output matrix
			 * @param[in] _q  List pointer of y
			 * @return New matrix resized
			 */
			Matrix<T> select(int32_t _np, int32_t* _p, int32_t _nq, int32_t* _q) const {
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
			T maxDifference(const Matrix<T>& _input) const {
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
					if (diff > max) {
						max = diff;
					}
				}
				return max;
			}
			/**
			 * @brief Clear all the matrix.
			 * <pre>
			 *   0 0 0 0 0
			 *   0 0 0 0 0
			 *   0 0 0 0 0
			 *   0 0 0 0 0
			 *   0 0 0 0 0
			 * </pre>
			 */
			void clear() {
				// copy data for the same size :
				for (int32_t iii=0; iii< m_size.x()*m_size.y(); iii++) {
					m_data[iii] = (T)0;
				}
			};
			/**
			 * @brief Set the matrix identity
			 * <pre>
			 *   1 0 0 0 0
			 *   0 1 0 0 0
			 *   0 0 1 0 0
			 *   0 0 0 1 0
			 * </pre>
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
			const uivec2& size() const {
				return m_size;
			};
	};
}

// To siplify the writing of the code ==> this is not compatible with GLSL ...
using dmat = etk::Matrix<double>; //!< Helper to simplify using of matrix
using mat = etk::Matrix<float>; //!< Helper to simplify using of matrix
using imat = etk::Matrix<int32_t>; //!< Helper to simplify using of matrix
using uimat = etk::Matrix<uint32_t>; //!< Helper to simplify using of matrix
