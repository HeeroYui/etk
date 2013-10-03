/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_VECTOR_H__
#define __ETK_VECTOR_H__

#include <etk/types.h>
#include <etk/DebugInternal.h>

#undef __class__
#define __class__	"etk::Vector"


namespace etk
{
	/**
	 * @brief Vector classes ...
	 *
	 * @tparam[in] MY_TYPE class type of the current element.
	 *
	 *              m_data
	 *               <------------ m_dataSize ------------>
	 *              ----------------------------------------
	 *              |    0                                 |
	 *              |--------------------------------------|
	 *              |    1                                 |
	 *              |--------------------------------------|
	 *              |    2                                 |
	 *              |--------------------------------------|
	 * m_size       |    3                                 |
	 *              |--------------------------------------|
	 *              |    x                                 |
	 *              |--------------------------------------|
	 *              |    x                                 |
	 *              |--------------------------------------|
	 *              |    x                                 |
	 *              |--------------------------------------|
	 *              |    x                                 |
	 *              |--------------------------------------|
	 *              |    x                                 |
	 *              |--------------------------------------|
	 *              |    x                                 |
	 *              |--------------------------------------|
	 * m_allocated  |    x                                 |
	 *              ----------------------------------------
	 *
	 */
	template<class MY_TYPE=int32_t> class Vector
	{
		public:
			class Iterator
			{
				// Private data :
				private:
					esize_t m_current; //!< curent Id on the vector
					Vector<MY_TYPE>* m_vector; //!< Pointer on the curent element of the vectorBin
				public:
					/**
					 * @brief Basic itarator constructor with no link with an etkVector
					 */
					Iterator(void):
						m_current(0),
						m_vector(NULL)
					{
						// nothing to do ...
					}
					/**
					 * @brief Recopy constructor on a specific etkVector.
					 * @param[in] _otherIterator The Iterator that might be copy
					 */
					Iterator(const Iterator & _otherIterator):
						m_current(_otherIterator.m_current),
						m_vector(_otherIterator.m_vector)
					{
						// nothing to do ...
					}
					/**
					 * @brief Asignation operator.
					 * @param[in] _otherIterator The Iterator that might be copy
					 * @return reference on the curent Iterator
					 */
					Iterator& operator=(const Iterator & _otherIterator)
					{
						m_current = _otherIterator.m_current;
						m_vector = _otherIterator.m_vector;
						return *this;
					}
					/**
					 * @brief Basic destructor
					 */
					~Iterator(void)
					{
						m_current = 0;
						m_vector = NULL;
					}
					/**
					 * @brief basic boolean cast
					 * @return true if the element is present in the etkVector size
					 */
					operator bool (void)
					{
						return (m_current < m_vector->Size());
					}
					/**
					 * @brief Incremental operator
					 * @return Reference on the current iterator incremented
					 */
					Iterator& operator++ (void)
					{
						if(    NULL != m_vector
						    && m_current < m_vector->Size() )
						{
							m_current++;
						}
						return *this;
					}
					/**
					 * @brief Decremental operator
					 * @return Reference on the current iterator decremented
					 */
					Iterator& operator-- (void)
					{
						if (m_current > 0) {
							m_current--;
						}
						return *this;
					}
					/**
					 * @brief Incremental operator
					 * @return Reference on a new iterator and increment the other one
					 */
					Iterator operator++ (int32_t)
					{
						Iterator it(*this);
						++(*this);
						return it;
					}
					/**
					 * @brief Decremental operator
					 * @return Reference on a new iterator and decrement the other one
					 */
					Iterator operator-- (int32_t)
					{
						Iterator it(*this);
						--(*this);
						return it;
					}
					/**
					 * @brief Get reference on the current Element
					 * @return the reference on the current Element 
					 */
					MY_TYPE & operator-> (void) const
					{
						TK_CHECK_INOUT(m_current < m_vector->Size());
						return &m_vector->Get(m_current);
					}
					/**
					 * @brief Get reference on the current Element
					 * @return the reference on the current Element 
					 */
					MY_TYPE & operator* (void) const
					{
						TK_CHECK_INOUT(m_current < m_vector->Size());
						return m_vector->Get(m_current);
					}
				private:
					Iterator(Vector<MY_TYPE> * _obj, int32_t _pos):
						m_current(_pos),
						m_vector(_obj)
					{
						// nothing to do ...
					}
					friend class Vector;
			};
	
		private:
			MY_TYPE* m_data; //!< pointer on the curetn table of Data
			esize_t m_size; //!< nb Element in the buffer
			esize_t m_allocated; //!< Current allocated size
		public:
			/**
			 * @brief Create an empty vector
			 * @param[in] _count Minimum request size of the Buffer
			 */
			Vector(int32_t _count = 0):
				m_data(NULL),
				m_size(0),
				m_allocated(0)
			{
				changeAllocation(_count);
			}
			/**
			 * @brief Re-copy constructor (copy all needed data)
			 * @param[in] _obj Vector that might be copy
			 */
			Vector(const etk::Vector<MY_TYPE>& _obj)
			{
				m_allocated = _obj.m_allocated;
				m_size      = _obj.m_size;
				m_data      = NULL;
				//TK_DEBUG("USE Specific vector allocator ... Evb.m_size=" << Evb.m_size << " Evb.m_increment=" << Evb.m_increment);
				// allocate all same data
				m_data = new MY_TYPE[m_allocated];
				if (NULL==m_data) {
					TK_CRITICAL("Vector : Error in data allocation ... might nor work corectly anymore");
					return;
				}
				// Copy all data ...
				for(esize_t iii=0; iii<m_allocated; iii++) {
					// copy operator ...
					m_data[iii] = _obj.m_data[iii];
				}
			}
			/**
			 * @brief Destructor of the current Class
			 */
			~Vector(void)
			{
				if (NULL!=m_data) {
					delete [] m_data;
					m_data = NULL;
				}
				m_allocated = 0;
				m_size = 0;
			}
			/**
			 * @brief Swap the data of 2 Vectors
			 * @param[in] _obj second vector to swap data.
			 */
			void wwap(etk::Vector<MY_TYPE>& _obj)
			{
				// avoid Swap of itself
				if(this != &_obj) {
					MY_TYPE* tmpData = m_data;
					esize_t tmpAllocated = m_allocated;
					esize_t tmpSize = m_size;
					m_data = _obj.m_data;
					m_allocated = _obj.m_allocated;
					m_size = _obj.m_size;
					_obj.m_data = tmpData;
					_obj.m_allocated = tmpAllocated;
					_obj.m_size = tmpSize;
				}
			}
			/**
			 * @brief Re-copy operator
			 * @param[in] _obj Vector that might be copy
			 * @return reference on the curent re-copy vector
			 */
			Vector& operator=(const etk::Vector<MY_TYPE> & _obj)
			{
				//TK_DEBUG("USE RECOPY vector ... Evb.m_size=" << Evb.m_size << " Evb.m_increment=" << Evb.m_increment);
				if( this != &_obj ) // avoid copy to itself
				{
					if (NULL!=m_data) {
						delete[] m_data;
						m_data = NULL;
					}
					// Set the new value
					m_allocated = _obj.m_allocated;
					m_size      = _obj.m_size;
					// allocate all same data
					m_data = new MY_TYPE[m_allocated];
					if (NULL==m_data) {
						TK_CRITICAL("Vector : Error in data allocation ... might nor work corectly anymore");
						return *this;
					}
					for(esize_t iii=0; iii<m_allocated; iii++) {
						// copy operator ...
						m_data[iii] = _obj.m_data[iii];
					}
				}
				// Return the curent pointer
				return *this;
			}
			
			/**
			 * @brief Add at the Last position of the Vector
			 * @param[in] _obj Element to add at the end of vector
			 */
			Vector& operator+= (const etk::Vector<MY_TYPE> & _obj)
			{
				esize_t nbElememt = _obj.size();
				esize_t idx = m_size;
				resize(m_size+nbElememt);
				if (m_size<=idx) {
					TK_CRITICAL("allocation error");
					return *this;
				}
				for(esize_t iii=0; iii<nbElememt; iii++) {
					// copy operator ...
					m_data[idx+iii] = _obj.m_data[iii];
				}
				// Return the curent pointer
				return *this;
			}
			/**
			 * @brief Get the number of element in the vector
			 * @return The number requested
			 */
			esize_t size(void) const
			{
				return m_size;
			}
			/**
			 * @brief Get the number of element in the vector
			 * @return The number requested
			 */
			void reSize(esize_t _newSize, const MY_TYPE& _basicElement)
			{
				esize_t idx = m_size;
				resize(_newSize);
				if (m_size != _newSize) {
					TK_CRITICAL("error to resize vector");
					return;
				}
				if (_newSize > idx) {
					// initialize data ...
					for(esize_t iii=idx; iii<_newSize; iii++) {
						m_data[iii] = _basicElement;
					}
				}
			}
			/**
			 * @brief Get the Allocated size in the vector
			 * @return The size of allocation
			 */
			esize_t allocatedSize(void) const
			{
				return m_allocated;
			}
			/**
			 * @brief Get a current element in the vector
			 * @param[in] _pos Desired position read
			 * @return Reference on the Element
			 */
			MY_TYPE& get(esize_t _pos)
			{
				// NOTE :Do not change log level, this generate error only in debug mode
				#if DEBUG_LEVEL > 2
					if(_pos>m_size){
						TK_CRITICAL("[CRITICAL] Access to an unexistant data in vector : " << _pos << "/ " << m_size);
					}
				#endif
				return m_data[_pos];
			}
			/**
			 * @brief Get an copy Element an a special position
			 * @param[in] _pos Position in the vector that might be get [0..Size()]
			 * @return An reference on the copy of selected element
			 */
			MY_TYPE& operator[] (esize_t _pos)
			{
				return get(_pos);
			}
			/**
			 * @brief Get an Element an a special position
			 * @param[in] _pos Position in the vector that might be get [0..Size()]
			 * @return An reference on the selected element
			 */
			const MY_TYPE& operator[] (esize_t _pos) const
			{
				// NOTE :Do not change log level, this generate error only in debug mode
				#if DEBUG_LEVEL > 2
					if(_pos>m_size){
						TK_CRITICAL("[CRITICAL] Access to an unexistant data in vector : " << _pos << "/ " << m_size);
					}
				#endif
				return m_data[_pos];
			}
			/**
			 * @brief Add at the First position of the Vector
			 * @param[in] _item Element to add at the end of vector
			 */
			void pushFront(const MY_TYPE& _item)
			{
				insert(0, &_item, 1);
			}
			/**
			 * @brief Add at the Last position of the Vector
			 * @param[in] _item Pointer on a list of Element to add at the start of vector
			 * @param[in] _nbElement Number of element to add.
			 */
			void pushFront(const MY_TYPE * _item, esize_t _nbElement)
			{
				insert(0, _item, _nbElement);
			}
			/**
			 * @brief Add at the Last position of the Vector
			 * @param[in] _item Element to add at the end of vector
			 */
			void pushBack(const MY_TYPE& _item)
			{
				esize_t idx = m_size;
				resize(m_size+1);
				if (idx < m_size) {
					m_data[idx] = _item;
				} else {
					TK_ERROR("Resize does not work corectly ... not added item");
				}
			}
			/**
			 * @brief Add at the Last position of the Vector
			 * @param[in] _item Pointer on a list of Element to add at the end of vector
			 * @param[in] _nbElement Number of element to add.
			 */
			void pushBack(const MY_TYPE * _item, esize_t _nbElement)
			{
				if (NULL == _item) {
					return;
				}
				esize_t idx = m_size;
				resize(m_size+_nbElement);
				if (idx > m_size) {
					TK_ERROR("Resize does not work corectly ... not added item");
					return;
				}
				for (esize_t iii=0; iii<_nbElement; iii++) {
					m_data[idx+iii] = _item[iii];
				}
			}
			/**
			 * @brief Remove the last element of the vector
			 */
			void popBack(void)
			{
				if(m_size>0) {
					resize(m_size-1);
				}
			}
			/**
			 * @brief Remove all alement in the current vector
			 */
			void clear(void)
			{
				if(m_size>0) {
					resize(0);
				}
			}
			/**
			 * @brief Insert N element in the Vector.
			 * @param[in] _pos Position to add the elements.
			 * @param[in] _item Pointer on a table of the elements to add.
			 * @param[in] _nbElement Number of element to add in the Vector
			 */
			void insert(esize_t _pos, const MY_TYPE * _item, esize_t _nbElement)
			{
				if (_pos>m_size) {
					TK_WARNING(" can not insert Element at this position : " << _pos << " > " << m_size << " add it at the end ... ");
					pushBack(_item, _nbElement);
					return;
				}
				esize_t idx = m_size;
				// Request resize of the current buffer
				resize(m_size+_nbElement);
				if (idx>=m_size) {
					TK_ERROR("Resize does not work corectly ... not added item");
					return;
				}
				// move curent data (after the position)
				esize_t sizeToMove = (idx - _pos);
				if ( 0 < sizeToMove) {
					for (esize_t iii=1; iii<=sizeToMove; iii++) {
						m_data[m_size-iii] = m_data[idx-iii];
					}
				}
				// affectation of all input element
				for (esize_t iii=0; iii<_nbElement; iii++) {
					m_data[_pos+iii] = _item[iii];
				}
			}
			/**
			 * @brief Insert one element in the Vector at a specific position
			 * @param[in] _pos Position to add the elements.
			 * @param[in] _item Element to add.
			 */
			void insert(esize_t _pos, const MY_TYPE& _item)
			{
				insert(_pos, &_item, 1);
			}
			/**
			 * @brief Remove N element
			 * @param[in] _pos Position to remove the data
			 * @param[in] _nbElement number of element to remove
			 */
			void eraseLen(esize_t _pos, esize_t _nbElement)
			{
				if (_pos>m_size) {
					TK_ERROR(" can not Erase Len Element at this position : " << _pos << " > " << m_size);
					return;
				}
				if (_pos+_nbElement>m_size) {
					_nbElement = m_size - _pos;
				}
				esize_t idx = m_size;
				// move curent data
				esize_t sizeToMove = (idx - (_pos+_nbElement));
				if ( 0 < sizeToMove) {
					for (esize_t iii=0; iii<sizeToMove; iii++) {
						m_data[_pos+iii] = m_data[_pos+_nbElement+iii];
					}
				}
				// Request resize of the current buffer
				resize(m_size-_nbElement);
			}
			/**
			 * @brief Remove one element
			 * @param[in] _pos Position to remove the data
			 */
			inline void erase(esize_t _pos)
			{
				eraseLen(_pos, 1);
			}
			/**
			 * @brief Remove one element
			 * @param[in] _pos Position to remove the data
			 */
			inline void remove(esize_t _pos)
			{
				eraseLen(_pos, 1);
			}
			/**
			 * @brief Remove N elements
			 * @param[in] _pos Position to remove the data
			 * @param[in] _posEnd Last position number
			 */
			void erase(esize_t _pos, esize_t _posEnd)
			{
				if (_pos>m_size) {
					TK_ERROR(" can not Erase Element at this position : " << _pos << " > " << m_size);
					return;
				}
				if (_posEnd>m_size) {
					_posEnd = m_size;
				}
				esize_t nbElement = m_size - _pos;
				esize_t tmpSize = m_size;
				// move curent data
				esize_t sizeToMove = (tmpSize - (_pos+nbElement));
				if ( 0 < sizeToMove) {
					for (esize_t iii=0; iii<sizeToMove; iii++) {
						m_data[_pos+iii] = m_data[_pos+nbElement+iii];
					}
				}
				// Request resize of the current buffer
				resize(m_size-nbElement);
			}
			/**
			 * @brief extract data between two point : 
			 * @param[in] _posStart start position to extract data
			 * @param[in] _posEnd End position to extract data
			 * @return the extracted vector
			 */
			Vector<MY_TYPE> extract(esize_t _posStart = 0, esize_t _posEnd=0x7FFFFFFF) const
			{
				Vector<MY_TYPE> out;
				if (_posStart >= size() ) {
					return out;
				}
				if (_posEnd >= size() ) {
					_posEnd = size();
				}
				out.pushBack(&m_data[_posStart], _posEnd-_posStart);
				return out;
			}
			/**
			 * @brief Get the pointer on the sata
			 * @return the type pointer on data
			 */
			MY_TYPE* dataPointer(void)
			{
				return &m_data[0];
			}
			/**
			 * @brief Get an iterator an an specific position
			 * @param[in] _pos Requested position of the iterator in the vector
			 * @return The Iterator
			 */
			Iterator position(esize_t _pos)
			{
				return iterator(this, _pos);
			}
			/**
			 * @brief Get an Iterator on the start position of the Vector
			 * @return The Iterator
			 */
			Iterator begin(void)
			{
				return position(0);
			}
			/**
			 * @brief Get an Iterator on the end position of the Vector
			 * @return The Iterator
			 */
			Iterator end(void)
			{
				return position( size()-1 );
			}
		private:
			/**
			 * @brief Change the current size of the vector
			 * @param[in] _newSize New requested size of element in the vector
			 */
			void resize(esize_t _newSize)
			{
				// Reallocate memory
				if (_newSize > m_allocated) {
					changeAllocation(_newSize);
				}
				m_size = _newSize;
			}
			/**
			 * @brief Change the current allocation to the corect one (depend on the current size)
			 * @param[in] _newSize Minimum number of element needed
			 */
			void changeAllocation(esize_t _newSize)
			{
				// set the minimal size to 1
				if(_newSize == 0) {
					_newSize = 1;
				}
				esize_t requestSize = m_allocated;
				// set the size with the corect chose type : 
				if (_newSize == requestSize) {
					return;
				} else if (_newSize < requestSize) {
					// we did not remove data ???
				} else {
					while(_newSize > requestSize) {
						if (0 == requestSize) {
							requestSize = 1;
						} else {
							requestSize = requestSize * 2;
						}
					}
				}
				// No reallocation needed :
				if (requestSize <= m_allocated) {
					return;
				}
				//TK_INFO("Change vector allocation : " << m_allocated << "==>" << requestSize);
				// check if something is allocated : 
				if (NULL == m_data) {
					// no data allocated ==> request an allocation (might be the first)
					m_data = new MY_TYPE[requestSize];
					if (NULL==m_data) {
						TK_CRITICAL("Vector : Error in data allocation request allocation:" << requestSize << "*" << (int32_t)(sizeof(MY_TYPE)) << "bytes" );
						m_allocated = 0;
						return;
					}
					// no data to copy
				} else {
					// allocate a new pool of data:
					MY_TYPE* m_dataTmp = new MY_TYPE[requestSize];
					if (NULL==m_dataTmp) {
						TK_CRITICAL("Vector : Error in data allocation request allocation:" << requestSize << "*" << (int32_t)(sizeof(MY_TYPE)) << "bytes" );
						m_allocated = 0;
						return;
					}
					// copy data in the new pool
					esize_t nbElements = etk_min(requestSize, m_allocated);
					for(esize_t iii=0; iii<nbElements; iii++) {
						m_dataTmp[iii] = m_data[iii];
					}
					// switch pointer:
					MY_TYPE* m_dataTmp2 = m_data;
					m_data = m_dataTmp;
					// remove old pool
					if (m_dataTmp2!= NULL) {
						delete [] m_dataTmp2;
					}
				}
				// set the new allocation size
				m_allocated = requestSize;
			}
		public :
			/*****************************************************
			 *    == operator
			 *****************************************************/
			bool operator== (const Vector<MY_TYPE>& _obj) const
			{
				// check if it was the same pointer
				if( this == &_obj ) {
					return true;
				}
				// fiist step : check the size ...
				if (m_size!=_obj.m_size) {
					return false;
				}
				if(    NULL==m_data
				    || NULL==_obj.m_data) {
					return false;
				}
				for (esize_t iii=0; iii<m_size; iii++) {
					if (m_data[iii]!=_obj.m_data[iii]) {
						return false;
					}
				}
				return true;
			}
			/*****************************************************
			 *    != operator
			 *****************************************************/
			bool operator!= (const Vector<MY_TYPE>& _obj) const
			{
				// check if it was the same pointer
				if( this == &_obj ) {
					return false;
				}
				// fiist step : check the size ...
				if (m_size!=_obj.m_size) {
					return true;
				}
				if(    NULL==m_data
				    || NULL==_obj.m_data) {
					return false;
				}
				for (esize_t iii=0; iii<m_size; iii++) {
					if (m_data[iii]!=_obj.m_data[iii]) {
						return true;
					}
				}
				return false;
			}
	};

	/**
	 * @brief List classes ...
	 *
	 * @tparam[in] T The type of objects to store.
	 *
	 *          m_data
	 *         ----------         |-----------------------|                             
	 *         |    0   |-------->|  Class Data           |                             
	 *         |--------|         |-----------------------|                             
	 *         |    1   |----|                                                          
	 *         |--------|    |                                                          
	 *         |    2   |====|==============|   |-----------------------|               
	 *         |--------|    |              --->|  Class Data           |               
	 * m_count |    3   |-|  |                  |-----------------------|               
	 *         |--------| |  |                                                          
	 *         |    x   | |  |        |-----------------------|                         
	 *         |--------| |  -------->|  Class Data           |                         
	 *         |    x   | |           |-----------------------|                         
	 *         |--------| |                                                             
	 *         |    x   | |                                                             
	 *         |--------| |                     |-----------------------|               
	 *         |    x   | --------------------->|  Class Data           |               
	 *         |--------|                       |-----------------------|               
	 *         |    x   |                                                               
	 *         |--------|                                                               
	 *         |    x   |                                                               
	 *         |--------|                                                               
	 * m_size  |    x   |                                                               
	 *         ----------                                                               
	 *
	 */
	/*
	template<class MY_CLASS> class List
	{
		
	};
	*/
}

#undef __class__
#define __class__	NULL

#endif

