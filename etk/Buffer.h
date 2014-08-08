/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ETK_BUFFER_H__
#define __ETK_BUFFER_H__

#include <etk/os/FSNode.h>

#undef __class__
#define __class__	"etk::Buffer"

// minimum gapSize when allocated
#define GAP_SIZE_MIN		(80)
// maximum gap that is automaticly resize
#define GAP_SIZE_MAX		(GAP_SIZE_MIN*4)

/*
    ______________________________________________________________________________________
    |                                                                                    |
    |                                                                                    |
    |                 <GapStart                                                          |
    |                 *******************************************************************|
    |******************************************                                          |
    |                                 Gap Stop >                                         |
    |                                                                                    |
    |                                                                                    |
    |                                                                                    |
    |                                                                                    |
    |                                                                                    |
    |                                                                                    |
    |                                                                                    |
    |                                                                                    |
    |                                                                                    |
    |                                                                                    |
    |____________________________________________________________________________________|
*/

namespace etk {
	/**
	 * @brief This is an access on raw data that contain an internal gap.
	 *        the gap size has an offset to increase an an offset to decrease.
	 */
	class Buffer {
		private:
			int8_t* m_data; //!< pointer on the curetn table of Data
			int32_t m_allocated; //!< Current allocated size
			// empty part of the buffer data
			int32_t m_gapStart; //!< points to the first character of the gap
			int32_t m_gapEnd; //!< points to the first char after the gap
		public:
			/**
			 * @brief Create an empty vector
			 * @param[in] _count Minimum request size of the Buffer
			 */
			Buffer(int32_t _count = 0) :
			  m_data(NULL),
			  m_allocated(0),
			  m_gapStart(0),
			  m_gapEnd(GAP_SIZE_MIN) {
				changeAllocation(_count+GAP_SIZE_MIN);
			}
			/**
			 * @brief Re-copy constructor (copy all needed data)
			 * @param[in] _obj Buffer that might be copy
			 */
			Buffer(const etk::Buffer& _obj) :
			  m_data(NULL),
			  m_allocated(_obj.m_allocated),
			  m_gapStart(_obj.m_gapStart),
			  m_gapEnd(_obj.m_gapEnd) {
				// allocate all same data
				m_data = (int8_t *)malloc( m_allocated * sizeof(int8_t) );
				TK_ASSERT(NULL!=m_data, "Error in data allocation");
				// Copy all data ...
				memcpy(m_data, _obj.m_data, m_allocated * sizeof(int8_t) );
			}
			/**
			 * @brief Destructor of the current Class
			 */
			~Buffer() {
				if (m_data != NULL) {
					free(m_data);
				}
				m_data = NULL;
				m_allocated = 0;
				m_gapStart = 0;
				m_gapEnd = 0;
			};
			/**
			 * @brief Store the selected data in the requested file.
			 * @param[in] _file Name of the file that might be written.
			 * @return true if the data corectly stored
			 * @return false if an error occured
			 */
			bool dumpIn(const std::string& _file) {
				etk::FSNode file(_file);
				if (false == file.fileOpenWrite()) {
					return false;
				}
				bool ret = true;
				// write Data
				file.fileWrite(m_data, sizeof(int8_t), m_gapStart);
				file.fileWrite(&m_data[m_gapEnd], sizeof(int8_t), m_allocated - m_gapEnd);
				file.fileClose();
				return ret;
			}
			/**
			 * @brief Load data fron a selected file name.
			 * @param[in] _file Name of the file to store buffer data.
			 * @return true if the data corectly stored
			 * @return false if an error occured
			 */
			bool dumpFrom(const std::string& _file) {
				etk::FSNode file(_file);
				if (false == file.fileOpenRead()) {
					return false;
				}
				bool ret = true;
				int64_t length = file.fileSize();
				// error case ...
				if (length > 2000000000) {
					return false;
				}
				// allocate the current buffer : 
				changeAllocation(length + GAP_SIZE_MIN);
				// insert Data
				int32_t nbReadData = file.fileRead(&m_data[GAP_SIZE_MIN], sizeof(int8_t), length);
				TK_INFO("load data : filesize=" << length << ", readData=" << nbReadData);
				// check ERROR
				if (nbReadData != length) {
					TK_ERROR("load data pb : filesize=" << length << ", readData=" << nbReadData);
					ret = false;
				}
				// set the gapsize at the fd ...
				m_gapStart = 0;
				m_gapEnd = GAP_SIZE_MIN;
				file.fileClose();
				return ret;
			}
			
			/**
			 * @brief Re-copy operator
			 * @param[in] _obj Buffer that might be copy
			 * @return reference on the curent copied Buffer
			 */
			etk::Buffer& operator=(const etk::Buffer& _obj) {
				if( this == &_obj ) {// avoid copy to itself
					return *this;
				}
				if (NULL != m_data) {
					free(m_data);
					m_data = NULL;
				}
				// Set the new value
				m_allocated = _obj.m_allocated;
				m_gapStart  = _obj.m_gapStart;
				m_gapEnd    = _obj.m_gapEnd;
				// allocate all same data
				m_data = (int8_t *)malloc( m_allocated * sizeof(int8_t) );
				TK_ASSERT(NULL!=m_data, "Error in data allocation");
				// Copy all data ...
				memcpy(m_data, _obj.m_data, m_allocated * sizeof(int8_t) );
				// Return the curent pointer
				return *this;
			}
			/**
			 * @brief Get the data at the requested position (gap abstraction done).
			 * @param[in] _pos Position in the buffer.
			 * @return Element at the request pos.
			 */
			int8_t operator[] (int32_t _pos) const {
				TK_ASSERT(0 <= _pos || _pos < size(), "try to read an element non existing");
				if (_pos < m_gapStart) {
					return m_data[_pos];
				}
				return m_data[_pos + m_gapEnd-m_gapStart];
			}
			
			/**
			 * @brief Get a current element in the vector
			 * @param[in] _pos Desired position read
			 * @return Reference on the Element
			 */
			int8_t& get(int32_t _pos) const {
				TK_ASSERT(0 <= _pos || _pos < size(), "try to read an element non existing");
				if (_pos < m_gapStart) {
					return m_data[_pos];
				}
				return m_data[_pos + m_gapEnd-m_gapStart];
			}
			/**
			 * @brief Get elements from a specific position.
			 * @param[in] _pos Position of the first element.
			 * @param[in] _nbElement Number of element needed.
			 * @return The data requested
			 */
			std::vector<int8_t> get(int32_t _pos, int32_t _nbElement) {
				std::vector<int8_t> tmpBuffer;
				tmpBuffer.clear();
				if (_pos < m_gapStart) {
					if (_pos + _nbElement < m_gapStart) {
						for (int32_t iii = _pos; iii<_pos+_nbElement; ++iii) {
							tmpBuffer.push_back(m_data[iii]);
						}
					} else {
						for (int32_t iii = _pos; iii<m_gapStart; ++iii) {
							tmpBuffer.push_back(m_data[iii]);
						}
						for (int32_t iii = m_gapEnd; iii<m_gapEnd - (_nbElement - (m_gapStart - _pos)); ++iii) {
							tmpBuffer.push_back(m_data[iii]);
						}
					}
				} else {
					for (int32_t iii = _pos+(m_gapEnd-m_gapStart);
					     iii<_pos+(m_gapEnd-m_gapStart)+_nbElement;
					     ++iii) {
						tmpBuffer.push_back(m_data[iii]);
					}
				}
				return tmpBuffer;
			}
			/**
			 * @brief Add at the Last position of the Buffer.
			 * @param[in] _item Element to add.
			 */
			void push_back(const int8_t& _item) {
				insert(size(), _item);
			}
			/**
			 * @brief Insert One item at the specify position.
			 * @param[in] _pos Position where data might be inserted
			 * @param[in] _items Data that might be inserted.
			 */
			void insert(int32_t _pos, const int8_t& _item) {
				if(    _pos > size()
				    || _pos < 0 ) {
					TK_ERROR("Request higher than buffer size : pos=" << _pos << " bufferSize=" << size());
					return;
				}
				if( 0 == gapSize() ) {
					if (false == gapResize(_pos, GAP_SIZE_MIN + 1) ) {
						return;
					}
				} else if(    _pos == m_gapStart
				           && _pos == m_gapEnd-1 )
				{
					// mothing to do ...
				} else {
					if (gapMove(_pos) == false) {
						return;
					}
				}
				if(_pos == m_gapStart) {
					m_data[m_gapStart] = _item;
					m_gapStart++;
				} else {
					m_data[m_gapEnd-1] = _item;
					m_gapEnd--;
				}
			}
			/**
			 * @brief Insert data in the Buffer.
			 * @param[in] _pos Position where data might be inserted
			 * @param[in] _items Data that might be inserted.
			 */
			void insert(int32_t _pos, const std::vector<int8_t>& _items) {
				insert(_pos, &_items[0], _items.size());
			}
			/**
			 * @brief Insert data in the buffer
			 * @param[in] _pos Position where data might be inserted
			 * @param[in] _items Data that might be inserted. (no need of '\0')
			 * @param[in] _nbElement number of element to insert
			 */
			void insert(int32_t _pos, const int8_t* _items, int32_t _nbElement) {
				if(    _pos > size()
				    || _pos < 0 ) {
					TK_ERROR("Request higher than buffer size : pos=" << _pos << " bufferSize="<<size());
					return;
				}
				if(_nbElement > gapSize()) {
					if (false == gapResize(_pos, GAP_SIZE_MIN + _nbElement) ) {
						return;
					}
				} else {
					if (false == gapMove(_pos) ) {
						return;
					}
				}
				for(int32_t iii=0; iii<_nbElement; ++iii) {
					m_data[m_gapStart+iii] = _items[iii];
				}
				m_gapStart += _nbElement;
			}
			/**
			 * @brief Replace one element in the buffer with an other.
			 * @param[in] _pos Position of the element to remove.
			 * @param[in] _items Element that might be inserted.
			 */
			void replace(int32_t _pos, const int8_t& _item) {
				if(    _pos > size()
				    || _pos < 0 ) {
					TK_ERROR("Request higher than buffer size : pos=" << _pos << " bufferSize="<<size());
					return;
				}
				// just replace the element, not update Gap position
				if (_pos < m_gapStart) {
					m_data[_pos] = _item;
				} else {
					m_data[_pos+gapSize()] = _item;
				}
			}
			/**
			 * @brief Replace a part of the buffer with the specified data.
			 * @param[in] _pos The first element to remove.
			 * @param[in] _nbRemoveElement number of element to remove.
			 * @param[in] _items Data that will be inserted.
			 */
			void replace(int32_t _pos, int32_t _nbRemoveElement, const std::vector<int8_t>& _items) {
				replace(_pos, _nbRemoveElement, &_items[0], _items.size());
			}
			/**
			 * @brief Replace a part of the buffer with the specified data.
			 * @param[in] _pos The first element to remove.
			 * @param[in] _nbRemoveElement number of element to remove.
			 * @param[in] _items Data that might be inserted.
			 * @param[in] _nbElement Number of element that might be added.
			 */
			void replace(int32_t _pos, int32_t _nbRemoveElement, const int8_t* _items, int32_t _nbElement) {
				if(    _pos > size()
				    || _pos < 0 ) {
					TK_ERROR("Request higher than buffer size : pos=" << _pos << " bufferSize="<<size());
					return;
				}
				if( _pos+_nbRemoveElement > size() ) {
					TK_ERROR("Request remove more element than expected in the buffer pos+nbRemoveElement="
					         << _pos+_nbRemoveElement << " bufferSize=" << size());
					return;
				}
				if (false == gapMove(_pos)) {
					return;
				}
				// Remove elements :
				m_gapEnd += _nbRemoveElement;
				//Display();
				// insert elements
				insert(_pos, _items, _nbElement);
				// Resize buffer if needed...
				gapCheckMaxSize();
			}
			/**
			 * @brief Remove specific data in the buffer.
			 * @param[in] _pos The first element to remove.
			 * @param[in] _nbRemoveElement Number of element to remove.
			 */
			void remove(int32_t _pos, int32_t _nbRemoveElement = 1) {
				if(    _pos > size()
				    || _pos < 0 ) {
					TK_ERROR("Request higher than buffer size : pos=" << _pos << " bufferSize="<<size());
					return;
				}
				if( _pos+_nbRemoveElement > size() ) {
					TK_ERROR("Request remove more element than expected in the buffer pos+nbRemoveElement="
					         << _pos+_nbRemoveElement << " bufferSize=" << size());
					return;
				}
				if (gapMove(_pos) == false) {
					return;
				}
				// Remove elements :
				if (m_allocated == m_gapEnd) {
					m_gapStart -= _nbRemoveElement;
				} else {
					m_gapEnd += _nbRemoveElement;
				}
				// Resize buffer if needed...
				gapCheckMaxSize();
			}
			/**
			 * @brief Remove the last element of the Buffer.
			 */
			void pop_back() {
				if (size() > 0) {
					remove( size() );
				}
			}
			/**
			 * @brief Remove all the data in the buffer.
			 */
			void clear() {
				remove(0, size() );
			}
		protected:
			/**
			 * @brief Get a current element in the Buffer (iterator system)
			 * @param[in] _realElementPosition Real position in the buffer (only use in the ITERATOR)
			 * @return Reference on the Element
			 */
			int8_t& getDirect(int32_t _realElementPosition) {
				return m_data[_realElementPosition];
			};
		public:
			/**
			 * @brief Get the number of element in the vector. This does not contain the gap size.
			 * @return The size of the set data.
			 */
			int32_t size() const {
				return m_allocated - gapSize();
			};
		private:
			/**
			 * @brief Change the current allocation to the new one (depend on the current size)
			 * @param[in] _newSize Minimum number of element needed
			 */
			void changeAllocation(int32_t _newSize) {
				// set the minimal size to 1
				if(_newSize <= 0) {
					_newSize = 1;
				}
				// set the size with the corect chose type : 
				if (_newSize == m_allocated) {
					return;
				}
				//TODO : use new and delete and multiple of power of 2.
				TK_DEBUG("Change Allocation : " << m_allocated << " ==> " << _newSize);
				// check if something is allocated : 
				if (m_data == NULL) {
					// no data allocated ==> request an allocation (might be the first)
					m_data = (int8_t *)malloc( _newSize * sizeof(int8_t) );
				} else {
					// move datas
					m_data = (int8_t *)realloc( m_data, _newSize* sizeof(int8_t) );
				}
				// Check result with assert : 
				TK_ASSERT(m_data != NULL, "Error in data allocation");
				// set the new allocation size
				m_allocated = _newSize;
			}
			/**
			 * @brief Move the current gap at an other position
			 * @param[in] _pos Position of the new Gap.
			 * @return false The operation can not be proccesed.
			 * @return true The operation done correctly.
			 */
			bool gapMove(int32_t _pos) {
				if(    _pos > size()
				    || _pos < 0 ) {
					TK_ERROR("Request higher than buffer size : pos=" << _pos << " bufferSize=" << size());
					return false;
				}
				int32_t gapLen = m_gapEnd - m_gapStart;
				if (_pos > m_gapStart) {
					memmove(&m_data[m_gapStart], &m_data[m_gapEnd], _pos - m_gapStart);
				} else {
					memmove(&m_data[_pos + gapLen], &m_data[_pos], m_gapStart - _pos);
				}
				m_gapEnd += _pos - m_gapStart;
				m_gapStart += _pos - m_gapStart;
				return true;
			}
			/**
			 * @brief Change The gap position and size
			 * @param[in] _pos Position of the new Gap.
			 * @param[in] _newGapLen Size of the new gap (can be bigger than GAP_SIZE_MAX).
			 * @return false The operation can not be done.
			 * @return true The operation done correctly.
			 */
			bool gapResize(int32_t _pos, int32_t _newGapLen) {
				if(    _pos > size()
				    || _pos < 0 ) {
					TK_ERROR("Request higher than buffer size : pos=" << _pos << " bufferSize=" << size());
					return false;
				}
				int32_t previousSize = size();
				if (_newGapLen == gapSize() ) {
					// nothing to do ...
					return true;
				} else {
					if (_newGapLen > gapSize() ) {
						// reallocation
						changeAllocation( previousSize + _newGapLen);
					}
					// move Data
					if (_pos <= m_gapStart) {
						// just move the end of the gap
						memmove(&m_data[m_gapStart + _newGapLen], &m_data[m_gapEnd], previousSize - m_gapStart);
						// update gap end position
						m_gapEnd = m_gapStart + _newGapLen;
						if (_pos < m_gapStart) {
							if (false == gapMove(_pos)) {
								return false;
							}
						}
					} else {
						if (false == gapMove(_pos) ) {
							return false;
						}
						memmove(&m_data[m_gapStart + _newGapLen], &m_data[m_gapEnd], previousSize - m_gapStart);
					}
					if (_newGapLen < gapSize() ) {
						// rellocation
						changeAllocation(previousSize + _newGapLen);
					}
				}
				// update gap position
				m_gapStart = _pos;
				m_gapEnd = _pos + _newGapLen;
				return true;
			}
			/**
			 * @brief Get the current gap size.
			 * @return The number of element in the gap.
			 */
			int32_t gapSize() const {
				return m_gapEnd - m_gapStart;
			}
			/**
			 * @brief Control if the writing gap is not too big (automatic call when resize the buffer).
			 */
			void gapCheckMaxSize() {
				if(gapSize() > GAP_SIZE_MAX) {
					int32_t currentSize = size();
					// Change the gap Size
					if (false == gapResize(m_gapStart, GAP_SIZE_MAX) ) {
						return;
					}
					// remove deprecated elements at the end of the buffer ...
					changeAllocation(currentSize + GAP_SIZE_MAX);
				}
			}
	};
};

#undef __class__
#define __class__	NULL


#endif
