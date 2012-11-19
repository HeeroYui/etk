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
	 * @brief EdnVectorBuf classes ...
	 */
	class Buffer
	{
		private:
			int8_t*    m_data;       //!< pointer on the curetn table of Data
			int32_t    m_allocated;  //!< Current allocated size
			// empty part of the buffer data
			int32_t    m_gapStart;   //!< points to the first character of the gap
			int32_t    m_gapEnd;     //!< points to the first char after the gap
		public:
			/**
			 * @brief Create an empty vector
			 * @param[in] count Minimum request size of the Buffer
			 */
			Buffer(int32_t count = 0) :
				m_data(NULL),
				m_allocated(0),
				m_gapStart(0),
				m_gapEnd(GAP_SIZE_MIN)
			{
				ChangeAllocation(count+GAP_SIZE_MIN);
			}
			/**
			 * @brief Re-copy constructor (copy all needed data)
			 * @param[in] obj Buffer that might be copy
			 */
			Buffer(const etk::Buffer & obj) :
				m_data(NULL),
				m_allocated(obj.m_allocated),
				m_gapStart(obj.m_gapStart),
				m_gapEnd(obj.m_gapEnd)
			{
				// allocate all same data
				m_data = (int8_t *)malloc( m_allocated * sizeof(int8_t) );
				TK_ASSERT(NULL!=m_data, "Error in data allocation");
				// Copy all data ...
				memcpy(m_data, Evb.m_data, m_allocated * sizeof(int8_t) );
			}
			/**
			 * @brief Destructor of the current Class
			 */
			~EdnVectorBuf(void)
			{
				if (NULL!=m_data) {
					free(m_data);
				}
				m_data = NULL;
				m_allocated = 0;
				m_gapStart = 0;
				m_gapEnd = 0;
			};
			/**
			 * @brief Save in the current file open
			 * @param[in,out] myFile	pointer on the file where data might be writed
			 * @return true if OK / false if an error occured
			 */
			bool DumpIn(etk::FSNode &file)
			{
				bool ret = true;
				// write Data
				(void)file.FileWrite(m_data,            sizeof(int8_t), m_gapStart);
				(void)file.FileWrite(&m_data[m_gapEnd], sizeof(int8_t), m_allocated - m_gapEnd);
				return ret;
			}
			/**
			 * @brief Load in the current file open
			 * @param[in,out] myFile	pointer on the file where data might be read
			 * @return true if OK / false if an error occured
			 */
			bool DumpFrom(etk::FSNode &file)
			{
				bool ret = true;
				uint32_t length = file.FileSize();
				// error case ...
				if (length > 2000000000) {
					return false;
				}
				// allocate the current buffer : 
				ChangeAllocation(length + GAP_SIZE_MIN);
				// insert Data
				int32_t nbReadData = file.FileRead(&m_data[GAP_SIZE_MIN], sizeof(int8_t), length);
				TK_INFO("load data : filesize=" << length << ", readData=" << nbReadData);
				// check ERROR
				if (nbReadData != length) {
					TK_ERROR("load data pb : filesize=" << length << ", readData=" << nbReadData);
					ret = false;
				}
				// set the gapsize at the end ...
				m_gapStart = 0;
				m_gapEnd = GAP_SIZE_MIN;
				return ret;
			}
			
			/**
			 * @brief Re-copy operator
			 * @param[in] Evb	Vector that might be copy
			 * @return reference on the curent re-copy vector
			 */
			EdnVectorBuf& operator=(const EdnVectorBuf & Evb)
			{
				if( this != &Evb ) // avoid copy to itself
				{
					if (NULL!=m_data) {
						free(m_data);
						m_data = NULL;
					}
					// Set the new value
					m_allocated = Evb.m_allocated;
					m_gapStart  = Evb.m_gapStart;
					m_gapEnd    = Evb.m_gapEnd;
					// allocate all same data
					m_data = (int8_t *)malloc( m_allocated * sizeof(int8_t) );
					TK_ASSERT(NULL!=m_data, "Error in data allocation");
					// Copy all data ...
					memcpy(m_data, Evb.m_data, m_allocated * sizeof(int8_t) );
				}
				// Return the curent pointer
				return *this;
			}
			
			int8_t operator[] (int32_t pos)
			{
				TK_ASSERT(0 <= pos || pos < Size(), "try to read an element non existing");
				if (pos < m_gapStart) {
					return m_data[pos];
				}
				return m_data[pos + m_gapEnd-m_gapStart];
			}
			
			/**
			 * @brief Get a current element in the vector
			 * @param[in] pos Desired position read
			 * @return Reference on the Element
			 */
			int8_t& Get(int32_t pos)
			{
				
				TK_ASSERT(0 <= pos || pos < Size(), "try to read an element non existing");
				if (pos < m_gapStart) {
					return m_data[pos];
				}
				return m_data[pos + m_gapEnd-m_gapStart];
			}
			/**
			 * @brief 
			 * @param[in,out] ---
			 */
			void Get(int32_t pos, int32_t nbElement, etk::Vector<int8_t> &tmpBuffer)
			{
				tmpBuffer.Clear();
				if (pos < m_gapStart) {
					if (pos + nbElement < m_gapStart) {
						tmpBuffer.PushBack(&m_data[pos], nbElement);
					} else {
						tmpBuffer.PushBack(&m_data[pos], m_gapStart - pos);
						tmpBuffer.PushBack(&m_data[m_gapEnd], nbElement - (m_gapStart - pos) );
					}
				} else {
					tmpBuffer.PushBack(&m_data[pos+(m_gapEnd-m_gapStart)], nbElement);
				}
			}
			// insert functions
			/**
			 * @brief Add at the Last position of the Vector
			 * @param[in] item	Element to add at the end of vector
			 */
			void PushBack(const int8_t& item)
			{
				Insert( Size(), item);
			}
			/**
			 * @brief 
			 * 
			 * @param[in,out] ---
			 * 
			 * @return ---
			 * 
			 */
			void Insert(int32_t pos, const int8_t& item)
			{
				if(		pos > Size()
					||	pos < 0 ) {
					TK_ERROR("Request higher than buffer size : pos="<<pos<< " bufferSize="<<Size());
					return;
				}
				if( 0 == GapSize() ) {
					if (false == GapResize(pos, GAP_SIZE_MIN + 1) ) {
						return;
					}
				} else if(		pos == m_gapStart
							&&	pos == m_gapEnd-1 )
				{
					// mothing to do ...
				} else {
					if (false == GapMove(pos)) {
						return;
					}
				}
				if(pos == m_gapStart) {
					m_data[m_gapStart] = item;
					m_gapStart++;
				} else {
					m_data[m_gapEnd-1] = item;
					m_gapEnd--;
				}
			}
			/**
			 * @brief 
			 * 
			 * @param[in,out] ---
			 * 
			 * @return ---
			 * 
			 */
			void Insert(int32_t pos, etk::Vector<int8_t>& items)
			{
				if(		pos > Size()
					||	pos < 0 ) {
					TK_ERROR("Request higher than buffer size : pos="<<pos<< " bufferSize="<<Size());
					return;
				}
				if( items.Size() > GapSize() ) {
					if (false == GapResize(pos, GAP_SIZE_MIN + items.Size()) ) {
						return;
					}
				} else {
					if (false == GapMove(pos) ) {
						return;
					}
				}
				int32_t i;
				for(i=0; i<items.Size(); i++) {
					m_data[m_gapStart+i] = items[i];
				}
				m_gapStart += items.Size();
			}
			// Remove and insert functions
			/**
			 * @brief 
			 * 
			 * @param[in,out] ---
			 * 
			 * @return ---
			 * 
			 */
			void Replace(int32_t pos, const int8_t& item)
			{
				if(		pos > Size()
					||	pos < 0 ) {
					TK_ERROR("Request higher than buffer size : pos="<<pos<< " bufferSize="<<Size());
					return;
				}
				// just replace the element, not update Gap position
				if (pos < m_gapStart) {
					m_data[pos] = item;
				} else {
					m_data[pos+GapSize()] = item;
				}
				
			}
			/**
			 * @brief 
			 * 
			 * @param[in,out] ---
			 * 
			 * @return ---
			 * 
			 */
			void Replace(int32_t pos, int32_t nbRemoveElement, etk::Vector<int8_t>& items)
			{
				if(		pos > Size()
					||	pos < 0 ) {
					TK_ERROR("Request higher than buffer size : pos="<<pos<< " bufferSize="<<Size());
					return;
				}
				if( pos+nbRemoveElement > Size() ) {
					TK_ERROR("Request remove more element than expected in the buffer pos+nbRemoveElement="<<pos+nbRemoveElement<< " bufferSize="<<Size());
					return;
				}
				if (false == GapMove(pos)) {
					return;
				}
				// Remove elements :
				m_gapEnd += nbRemoveElement;
				//Display();
				// insert elements
				Insert(pos, items);
				// Resize buffer if needed...
				GapCheckMaxSize();
			}
			// Revove fonctions
			/**
			 * @brief Remove data in the buffer
			 * 
			 * @param[in] 
			 * 
			 * @return ---
			 * 
			 */
			void Remove(int32_t pos, int32_t nbRemoveElement = 1)
			{
				
				if(		pos > Size()
					||	pos < 0 ) {
					TK_ERROR("Request higher than buffer size : pos="<<pos<< " bufferSize="<<Size());
					return;
				}
				if( pos+nbRemoveElement > Size() ) {
					TK_ERROR("Request remove more element than expected in the buffer pos+nbRemoveElement="<<pos+nbRemoveElement<< " bufferSize="<<Size());
					return;
				}
				if (false == GapMove(pos) ) {
					return;
				}
				// Remove elements :
				if (m_allocated==m_gapEnd) {
					m_gapStart -= nbRemoveElement;
				} else {
					m_gapEnd += nbRemoveElement;
				}
				// Resize buffer if needed...
				GapCheckMaxSize();
			}
			/**
			 * @brief Remove the last element of the vector
			 * 
			 * @param ---
			 * 
			 * @return ---
			 * 
			 */
			void PopBack(void)
			{
				if (Size()>0) {
					Remove( Size() );
				}
			}
			/**
			 * @brief Change the current allocation to the corect one (depend on the current size)
			 * 
			 * @param[in] newSize Minimum number of element needed
			 * 
			 * @return ---
			 * 
			 */
			void Clear(void)
			{
				
				// Remove all element in the buffer
				Remove(0, Size() );
			}
			
			
			void Fit(void)
			{
				
			}
			
			void Display(void)
			{
				TK_INFO(" Display Buffer : Size="<<Size()<<" m_allocated="<<m_allocated<<" m_gapStart="<<m_gapStart<<" m_gapEnd="<<m_gapEnd);
				for(int32_t i=0; i<m_allocated; i++) {
					if (i>= m_gapStart && i< m_gapEnd) {
						TK_INFO( "Element " << i << " : GAP");
					} else {
						TK_INFO( "Element " << i << " : " << m_data[i]);
					}
				}
			}
			
			/**
			 * @brief Get a current element in the vector (iterator system)
			 * @param[in] RealElementPosition Real position in the buffer (only use in the ITERATOR)
			 * @return Reference on the Element
			 */
			int8_t& GetDirect(int32_t RealElementPosition)
			{
				return m_data[RealElementPosition];
			};
			/**
			 * @brief Get the number of element in the vector
			 * @return The number requested
			 */
			int32_t Size(void)
			{
				return m_allocated - GapSize();
			};
		private:
			/**
			 * @brief Change the current allocation to the corect one (depend on the current size)
			 * 
			 * @param[in] newSize Minimum number of element needed
			 * 
			 * @return ---
			 * 
			 */
			void ChangeAllocation(int32_t newSize)
			{
				// set the minimal size to 1
				if(newSize <= 0) {
					newSize = 1;
				}
				// set the size with the corect chose type : 
				if (newSize == m_allocated) {
					return;
				}
				TK_DEBUG("Change Allocation : " << m_allocated << " ==> " << newSize);
				// check if something is allocated : 
				if (NULL == m_data) {
					// no data allocated ==> request an allocation (might be the first)
					m_data = (int8_t *)malloc( newSize * sizeof(int8_t) );
				} else {
					// move datas
					m_data = (int8_t *)realloc( m_data, newSize* sizeof(int8_t) );
				}
				// Check result with assert : 
				TK_ASSERT(NULL!=m_data, "Error in data allocation");
				// set the new allocation size
				m_allocated = newSize;
			}
			/**
			 * @brief 
			 * 
			 * @param[in,out] ---
			 * 
			 * @return ---
			 * 
			 */
			bool GapMove(int32_t pos)
			{
				if(		pos > Size()
					||	pos < 0 ) {
					TK_ERROR("Request higher than buffer size : pos="<<pos<< " bufferSize="<<Size());
					return false;
				}
				int32_t gapLen = m_gapEnd - m_gapStart;
				if (pos > m_gapStart) {
					memmove(&m_data[m_gapStart], &m_data[m_gapEnd], pos - m_gapStart);
				} else {
					memmove(&m_data[pos + gapLen], &m_data[pos], m_gapStart - pos);
				}
				m_gapEnd += pos - m_gapStart;
				m_gapStart += pos - m_gapStart;
				return true;
			}
			/**
			 * @brief 
			 * 
			 * @param[in,out] ---
			 * 
			 * @return ---
			 * 
			 */
			bool GapResize(int32_t pos, int32_t newGapLen)
			{
				if(		pos > Size()
					||	pos < 0 ) {
					TK_ERROR("Request higher than buffer size : pos="<<pos<< " bufferSize="<<Size());
					return false;
				}
				int32_t previousSize = Size();
				if (newGapLen == GapSize() ) {
					// nothing to do ...
					return true;
				} else {
					if (newGapLen > GapSize() ) {
						// reallocation
						ChangeAllocation( previousSize + newGapLen);
					}
					// move Data
					if (pos <= m_gapStart) {
						// just move the end of the gap
						memmove(&m_data[m_gapStart + newGapLen], &m_data[m_gapEnd], previousSize - m_gapStart);
						// update gap end position
						m_gapEnd = m_gapStart + newGapLen;
						if (pos < m_gapStart) {
							if (false == GapMove(pos)) {
								return false;
							}
						}
						// no else
					} else {
						if (false == GapMove(pos) ) {
							return false;
						}
						memmove(&m_data[m_gapStart + newGapLen], &m_data[m_gapEnd], previousSize - m_gapStart);
					}
					if (newGapLen < GapSize() ) {
						// rellocation
						ChangeAllocation(previousSize + newGapLen);
					}
				}
				// update gap position
				m_gapStart = pos;
				m_gapEnd = pos + newGapLen;
				return true;
			}
			// get current gap Size
			int32_t GapSize(void)
			{
				return m_gapEnd - m_gapStart;
			}
			/**
			 * @brief 
			 * 
			 * @param[in,out] ---
			 * 
			 * @return ---
			 * 
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
