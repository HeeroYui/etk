/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
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

namespace etk
{
	/**
	 * @brief Buffer classes. Designed for access o
	 */
	class Buffer
	{
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
				m_gapEnd(GAP_SIZE_MIN)
			{
				ChangeAllocation(_count+GAP_SIZE_MIN);
			}
			/**
			 * @brief Re-copy constructor (copy all needed data)
			 * @param[in] _obj Buffer that might be copy
			 */
			Buffer(const etk::Buffer& _obj) :
				m_data(NULL),
				m_allocated(_obj.m_allocated),
				m_gapStart(_obj.m_gapStart),
				m_gapEnd(_obj.m_gapEnd)
			{
				// allocate all same data
				m_data = (int8_t *)malloc( m_allocated * sizeof(int8_t) );
				TK_ASSERT(NULL!=m_data, "Error in data allocation");
				// Copy all data ...
				memcpy(m_data, _obj.m_data, m_allocated * sizeof(int8_t) );
			}
			/**
			 * @brief Destructor of the current Class
			 */
			~Buffer(void)
			{
				if (m_data != NULL) {
					free(m_data);
				}
				m_data = NULL;
				m_allocated = 0;
				m_gapStart = 0;
				m_gapEnd = 0;
			};
			/**
			 * @brief Save in the current file open
			 * @param[in,out] _file Pointer on the file where data might be writed
			 * @return true if OK / false if an error occured
			 */
			bool DumpIn(etk::FSNode& _file)
			{
				if (false == _file.FileOpenWrite()) {
					return false;
				}
				bool ret = true;
				// write Data
				(void)_file.FileWrite(m_data, sizeof(int8_t), m_gapStart);
				(void)_file.FileWrite(&m_data[m_gapEnd], sizeof(int8_t), m_allocated - m_gapEnd);
				_file.FileClose();
				return ret;
			}
			/**
			 * @brief Load in the current file open
			 * @param[in,out] _myFile Pointer on the file where data might be read
			 * @return true if OK / false if an error occured
			 */
			bool DumpFrom(etk::FSNode& _file)
			{
				if (false == _file.FileOpenRead()) {
					return false;
				}
				bool ret = true;
				uint32_t length = _file.FileSize();
				// error case ...
				if (length > 2000000000) {
					return false;
				}
				// allocate the current buffer : 
				ChangeAllocation(length + GAP_SIZE_MIN);
				// insert Data
				int32_t nbReadData = _file.FileRead(&m_data[GAP_SIZE_MIN], sizeof(int8_t), length);
				TK_INFO("load data : filesize=" << length << ", readData=" << nbReadData);
				// check ERROR
				if (nbReadData != length) {
					TK_ERROR("load data pb : filesize=" << length << ", readData=" << nbReadData);
					ret = false;
				}
				// set the gapsize at the end ...
				m_gapStart = 0;
				m_gapEnd = GAP_SIZE_MIN;
				_file.FileClose();
				return ret;
			}
			
			/**
			 * @brief Re-copy operator
			 * @param[in] _obj Buffer that might be copy
			 * @return reference on the curent re-copy vector
			 */
			etk::Buffer& operator=(const etk::Buffer& _obj)
			{
				if( this != &_obj ) // avoid copy to itself
				{
					if (NULL!=m_data) {
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
				}
				// Return the curent pointer
				return *this;
			}
			/**
			 * @brief Operator [] : Get the data at the requested position (gap abstraction done).
			 * @param[in] _pos Position in the buffer.
			 * @return Element at the request pos.
			 */
			int8_t operator[] (int32_t _pos) const
			{
				TK_ASSERT(0 <= _pos || _pos < Size(), "try to read an element non existing");
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
			int8_t& Get(int32_t _pos) const
			{
				TK_ASSERT(0 <= _pos || _pos < Size(), "try to read an element non existing");
				if (_pos < m_gapStart) {
					return m_data[_pos];
				}
				return m_data[_pos + m_gapEnd-m_gapStart];
			}
			#if 0
			/**
			 * @brief Get a current element in the vector
			 * @param[in] _pos Desired position read
			 * @return Reference on the Element
			 */
			esize_t Get(esize_t _pos, UniChar& _value, charset_te _charset) const
			{
				TK_ASSERT(0 <= pos || pos < Size(), "try to read an element non existing");
				if (pos < m_gapStart) {
					return m_data[pos];
				}
				return m_data[pos + m_gapEnd-m_gapStart];
			}
			#endif
			/**
			 * @brief Get elements from a specific position.
			 * @param[in] _pos Position of the first element.
			 * @param[in] _nbElement Number of element needed.
			 * @return The data requested
			 */
			etk::Vector<int8_t> Get(int32_t _pos, int32_t _nbElement)
			{
				etk::Vector<int8_t> tmpBuffer;
				tmpBuffer.Clear();
				if (_pos < m_gapStart) {
					if (_pos + _nbElement < m_gapStart) {
						tmpBuffer.PushBack(&m_data[_pos], _nbElement);
					} else {
						tmpBuffer.PushBack(&m_data[_pos], m_gapStart - _pos);
						tmpBuffer.PushBack(&m_data[m_gapEnd], _nbElement - (m_gapStart - _pos) );
					}
				} else {
					tmpBuffer.PushBack(&m_data[_pos+(m_gapEnd-m_gapStart)], _nbElement);
				}
				return tmpBuffer;
			}
			/**
			 * @brief Add at the Last position of the Vector
			 * @param[in] _item Element to add at the end of vector
			 */
			void PushBack(const int8_t& _item)
			{
				Insert(Size(), _item);
			}
			/**
			 * @brief Insert One item at the specify position.
			 * @param[in] _pos Position where data might be inserted
			 * @param[in] _items Data that might be inserted.
			 */
			void Insert(int32_t _pos, const int8_t& _item)
			{
				if(    _pos > Size()
				    || _pos < 0 ) {
					TK_ERROR("Request higher than buffer size : pos=" << _pos << " bufferSize=" << Size());
					return;
				}
				if( 0 == GapSize() ) {
					if (false == GapResize(_pos, GAP_SIZE_MIN + 1) ) {
						return;
					}
				} else if(    _pos == m_gapStart
				           && _pos == m_gapEnd-1 )
				{
					// mothing to do ...
				} else {
					if (GapMove(_pos) == false) {
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
			 * @brief Insert data in the buffer
			 * @param[in] _pos Position where data might be inserted
			 * @param[in] _items Data that might be inserted.
			 */
			void Insert(int32_t _pos, etk::Vector<int8_t>& _items)
			{
				Insert(_pos, _items.DataPointer(), _items.Size());
			}
			/**
			 * @brief Insert data in the buffer
			 * @param[in] _pos Position where data might be inserted
			 * @param[in] _items Data that might be inserted. (no need of '\0')
			 * @param[in] _nbElement number of element to insert
			 */
			void Insert(int32_t _pos, int8_t* _items, int32_t _nbElement)
			{
				if(    _pos > Size()
				    || _pos < 0 ) {
					TK_ERROR("Request higher than buffer size : pos=" << _pos << " bufferSize="<<Size());
					return;
				}
				if(_nbElement > GapSize()) {
					if (false == GapResize(_pos, GAP_SIZE_MIN + _nbElement) ) {
						return;
					}
				} else {
					if (false == GapMove(_pos) ) {
						return;
					}
				}
				for(esize_t iii=0; iii<_nbElement; iii++) {
					m_data[m_gapStart+iii] = _items[iii];
				}
				m_gapStart += _nbElement;
			}
			/**
			 * @brief Replace one element in the buffer
			 * @param[in] _pos The first element to remove.
			 * @param[in] _items Data that might be inserted.
			 */
			void Replace(int32_t _pos, const int8_t& _item)
			{
				if(    _pos > Size()
				    || _pos < 0 ) {
					TK_ERROR("Request higher than buffer size : pos=" << _pos << " bufferSize="<<Size());
					return;
				}
				// just replace the element, not update Gap position
				if (_pos < m_gapStart) {
					m_data[_pos] = _item;
				} else {
					m_data[_pos+GapSize()] = _item;
				}
			}
			/**
			 * @brief Replace specified data.
			 * @param[in] _pos The first element to remove.
			 * @param[in] _nbRemoveElement number of element to remove.
			 * @param[in] _items Data that might be inserted.
			 */
			void Replace(int32_t _pos, int32_t _nbRemoveElement, etk::Vector<int8_t>& _items)
			{
				if(    _pos > Size()
				    || _pos < 0 ) {
					TK_ERROR("Request higher than buffer size : pos=" << _pos << " bufferSize="<<Size());
					return;
				}
				if( _pos+_nbRemoveElement > Size() ) {
					TK_ERROR("Request remove more element than expected in the buffer pos+nbRemoveElement="
					         << _pos+_nbRemoveElement << " bufferSize=" << Size());
					return;
				}
				if (false == GapMove(_pos)) {
					return;
				}
				// Remove elements :
				m_gapEnd += _nbRemoveElement;
				//Display();
				// insert elements
				Insert(_pos, _items);
				// Resize buffer if needed...
				GapCheckMaxSize();
			}
			/**
			 * @brief Remove specific data in the buffer.
			 * @param[in] _pos The first element to remove
			 * @param[in] _nbRemoveElement number of element to remove
			 */
			void Remove(int32_t _pos, int32_t _nbRemoveElement = 1)
			{
				if(    _pos > Size()
				    || _pos < 0 ) {
					TK_ERROR("Request higher than buffer size : pos=" << _pos << " bufferSize="<<Size());
					return;
				}
				if( _pos+_nbRemoveElement > Size() ) {
					TK_ERROR("Request remove more element than expected in the buffer pos+nbRemoveElement="
					         << _pos+_nbRemoveElement << " bufferSize=" << Size());
					return;
				}
				if (GapMove(_pos) == false) {
					return;
				}
				// Remove elements :
				if (m_allocated == m_gapEnd) {
					m_gapStart -= _nbRemoveElement;
				} else {
					m_gapEnd += _nbRemoveElement;
				}
				// Resize buffer if needed...
				GapCheckMaxSize();
			}
			/**
			 * @brief Remove the last element of the Buffer.
			 */
			void PopBack(void)
			{
				if (Size()>0) {
					Remove( Size() );
				}
			}
			/**
			 * @brief Clean all the data in the buffer.
			 */
			void Clear(void)
			{
				Remove(0, Size() );
			}
			/**
			 * @brief Get a current element in the vector (iterator system)
			 * @param[in] _realElementPosition Real position in the buffer (only use in the ITERATOR)
			 * @return Reference on the Element
			 */
			int8_t& GetDirect(int32_t _realElementPosition)
			{
				return m_data[_realElementPosition];
			};
			/**
			 * @brief Get the number of element in the vector
			 * @return The number requested
			 */
			int32_t Size(void) const
			{
				return m_allocated - GapSize();
			};
		private:
			/**
			 * @brief Change the current allocation to the corect one (depend on the current size)
			 * @param[in] _newSize Minimum number of element needed
			 */
			void ChangeAllocation(int32_t _newSize)
			{
				// set the minimal size to 1
				if(_newSize <= 0) {
					_newSize = 1;
				}
				// set the size with the corect chose type : 
				if (_newSize == m_allocated) {
					return;
				}
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
			bool GapMove(int32_t _pos)
			{
				if(    _pos > Size()
				    || _pos < 0 ) {
					TK_ERROR("Request higher than buffer size : pos=" << _pos << " bufferSize=" << Size());
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
			 * @return false The operation can not be proccesed.
			 * @return true The operation done correctly.
			 */
			bool GapResize(int32_t _pos, int32_t _newGapLen)
			{
				if(    _pos > Size()
				    || _pos < 0 ) {
					TK_ERROR("Request higher than buffer size : pos=" << _pos << " bufferSize="<<Size());
					return false;
				}
				int32_t previousSize = Size();
				if (_newGapLen == GapSize() ) {
					// nothing to do ...
					return true;
				} else {
					if (_newGapLen > GapSize() ) {
						// reallocation
						ChangeAllocation( previousSize + _newGapLen);
					}
					// move Data
					if (_pos <= m_gapStart) {
						// just move the end of the gap
						memmove(&m_data[m_gapStart + _newGapLen], &m_data[m_gapEnd], previousSize - m_gapStart);
						// update gap end position
						m_gapEnd = m_gapStart + _newGapLen;
						if (_pos < m_gapStart) {
							if (false == GapMove(_pos)) {
								return false;
							}
						}
						// no else
					} else {
						if (false == GapMove(_pos) ) {
							return false;
						}
						memmove(&m_data[m_gapStart + _newGapLen], &m_data[m_gapEnd], previousSize - m_gapStart);
					}
					if (_newGapLen < GapSize() ) {
						// rellocation
						ChangeAllocation(previousSize + _newGapLen);
					}
				}
				// update gap position
				m_gapStart = _pos;
				m_gapEnd = _pos + _newGapLen;
				return true;
			}
			/**
			 * @brief Get the current gap size.
			 * @return The number of element in the gap
			 */
			int32_t GapSize(void) const
			{
				return m_gapEnd - m_gapStart;
			}
			/**
			 * @brief Control if the writing gap is not too big (automatic resize the buffer).
			 */
			void GapCheckMaxSize(void)
			{
				if(GapSize() > GAP_SIZE_MAX) {
					int32_t currentSize = Size();
					// Change the gap Size
					if (false == GapResize(m_gapStart, GAP_SIZE_MAX) ) {
						return;
					}
					// remove deprecated elements at the end of the buffer ...
					ChangeAllocation(currentSize + GAP_SIZE_MAX);
				}
			}
	};
};

#undef __class__
#define __class__	NULL


#endif
