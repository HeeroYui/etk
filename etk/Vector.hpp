/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL-2 (see license file)
 */
#pragma once

#include <etk/types.hpp>
//#include <etk/debug.hpp>
#include <etk/Stream.hpp>
#include <etk/Allocator.hpp>

//#define ETK_VECTOR_DEBUG(...) printf(__VA_ARGS__)
#define ETK_VECTOR_DEBUG(...) do {} while (false)

namespace etk {
	class Stream;
	/**
	 * @brief Vector class ...
	 *
	 * @param[in] ETK_VECTOR_TYPE class type of the current element.
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
	 */
	template<class ETK_VECTOR_TYPE> class Vector {
		public:
			//static const size_t npos = size_t(-1);
			class Iterator {
				private:
					size_t m_current; //!< current Id on the vector
					Vector<ETK_VECTOR_TYPE>* m_vector; //!< Pointer on the current element of the vectorBin
				public:
					/**
					 * @brief Basic iterator constructor with no link with an etk::Vector
					 */
					Iterator():
					  m_current(0),
					  m_vector(nullptr) {
						// nothing to do ...
					}
					/**
					 * @brief Recopy constructor on a specific etkVector.
					 * @param[in] _obj The Iterator that might be copy
					 */
					Iterator(const Iterator & _obj):
					  m_current(_obj.m_current),
					  m_vector(_obj.m_vector) {
						// nothing to do ...
					}
					/**
					 * @brief Assignation operator.
					 * @param[in] _otherIterator The Iterator that might be copy
					 * @return reference on the current Iterator
					 */
					Iterator& operator=(const Iterator & _otherIterator) {
						m_current = _otherIterator.m_current;
						m_vector = _otherIterator.m_vector;
						return *this;
					}
					/**
					 * @brief Basic destructor
					 */
					~Iterator() {
						m_current = 0;
						m_vector = nullptr;
					}
					/**
					 * @brief basic boolean cast
					 * @return true if the element is present in the etkVector size
					 */
					operator bool () {
						return (m_current < m_vector->size());
					}
					/**
					 * @brief Incremental operator
					 * @return Reference on the current iterator increment
					 */
					Iterator& operator++ () {
						if (    m_vector != nullptr
						     && m_current < m_vector->size() )
						{
							m_current++;
						}
						return *this;
					}
					/**
					 * @brief Decremental operator
					 * @return Reference on the current iterator decrement
					 */
					Iterator& operator-- () {
						if (    m_vector != nullptr
						     && m_current > 0) {
							m_current--;
						}
						return *this;
					}
					/**
					 * @brief Incremental operator
					 * @return Reference on a new iterator and increment the other one
					 */
					Iterator operator++ (int32_t) {
						Iterator it(*this);
						++(*this);
						return it;
					}
					/**
					 * @brief Decremental operator
					 * @return Reference on a new iterator and decrement the other one
					 */
					Iterator operator-- (int32_t) {
						Iterator it(*this);
						--(*this);
						return it;
					}
					Iterator& operator-= (size_t _offset) {
						m_current -= _offset;
						return *this;
					}
					Iterator operator- (size_t _offset) const {
						Iterator tmp(*this);
						tmp -= _offset;
						return tmp;
					}
					Iterator& operator-= (int _offset) {
						m_current -= _offset;
						return *this;
					}
					Iterator operator- (int _offset) const {
						Iterator tmp(*this);
						tmp -= _offset;
						return tmp;
					}
					Iterator& operator-= (int64_t _offset) {
						m_current -= _offset;
						return *this;
					}
					Iterator operator- (int64_t _offset) const {
						Iterator tmp(*this);
						tmp -= _offset;
						return tmp;
					}
					Iterator& operator+= (size_t _offset) {
						m_current += _offset;
						return *this;
					}
					Iterator operator+ (size_t _offset) const {
						Iterator tmp(*this);
						tmp += _offset;
						return tmp;
					}
					Iterator& operator+= (int _offset) {
						m_current += _offset;
						return *this;
					}
					Iterator operator+ (int _offset) const {
						Iterator tmp(*this);
						tmp += _offset;
						return tmp;
					}
					Iterator& operator+= (int64_t _offset) {
						m_current += _offset;
						return *this;
					}
					Iterator operator+ (int64_t _offset) const {
						Iterator tmp(*this);
						tmp += _offset;
						return tmp;
					}
					/**
					 * @brief Get reference on the current Element
					 * @return the reference on the current Element 
					 */
					ETK_VECTOR_TYPE* operator-> () const {
						return &m_vector->get(m_current);
					}
					/**
					 * @brief Get reference on the current Element
					 * @return the reference on the current Element 
					 */
					ETK_VECTOR_TYPE& operator* () const {
						return m_vector->get(m_current);
					}
				private:
					Iterator(const Vector<ETK_VECTOR_TYPE> * _obj, int32_t _pos):
					  m_current(_pos),
					  m_vector(const_cast<Vector<ETK_VECTOR_TYPE> *>(_obj)) {
						// nothing to do ...
					}
					size_t getCurrent() const {
						return m_current;
					}
					friend class Vector;
			};
		private:
			ETK_VECTOR_TYPE* m_data; //!< pointer on the current table of Data
			size_t m_size; //!< Number of element in the buffer
			size_t m_allocated; //!< Current allocated size
		public:
			/**
			 * @brief Create an empty vector
			 */
			Vector():
			  m_data(nullptr),
			  m_size(0),
			  m_allocated(0) {
				
			}
			#if 0
			/**
			 * @brief Create an empty vector
			 * @param[in] _count Minimum request size of the Buffer
			 */
			Vector(size_t _count):
			  m_data(nullptr),
			  m_size(0),
			  m_allocated(0) {
				changeAllocation(_count);
				// instanciate all objects
				for (size_t iii=0; iii<_count; ++iii) {
					new ((char*)&m_data[iii]) ETK_VECTOR_TYPE();
				}
				m_size = _count;
			}
			#endif
			/**
			 * @brief List initializer (ex: etk::Vector<etk::String> plop = {"hello", world"}
			 * @param[in] _element element to add in the vector
			 */
			template<typename... ETK_VECTOR_TYPE_2>
			Vector(const ETK_VECTOR_TYPE_2& ... _args):
			  m_data(nullptr),
			  m_size(0),
			  m_allocated(0) {
				changeAllocation(int32_t(sizeof...(ETK_VECTOR_TYPE_2)));
				pushBackN(_args...);
			}
			/**
			 * @brief Re-copy constructor (copy all needed data)
			 * @param[in] _obj Vector that might be copy
			 */
			Vector(const etk::Vector<ETK_VECTOR_TYPE>& _obj):
			  m_data(nullptr),
			  m_size(0),
			  m_allocated(0) {
				reserve(_obj.m_size);
				for(size_t iii=0; iii<_obj.m_size; iii++) {
					new ((char*)&m_data[iii]) ETK_VECTOR_TYPE(etk::move(_obj.m_data[iii]));
				}
				m_size = _obj.m_size;
			}
			/**
			 * @brief Move operator of elements
			 * @param[in] _obj Object to move
			 */
			Vector(etk::Vector<ETK_VECTOR_TYPE>&& _obj):
			  m_data(_obj.m_data),
			  m_size(_obj.m_size),
			  m_allocated(_obj.m_allocated) {
				_obj.m_data = nullptr;
				_obj.m_size = 0;
				_obj.m_allocated = 0;
			}
			/**
			 * @brief Destructor of the current class
			 */
			~Vector() {
				if (m_data != nullptr) {
					for(size_t iii=0; iii<m_size; iii++) {
						m_data[iii].~ETK_VECTOR_TYPE();
						#ifdef DEBUG
							// we place bad data to permit to detect stipid thing that is done in C++ code when developement is in progress.
							// Only in debug this is really slow ... and for the real allocation of memory
							for (size_t kkk=iii*sizeof(ETK_VECTOR_TYPE); kkk<sizeof(ETK_VECTOR_TYPE)*(iii+1); ++kkk) {
								((char*)m_data)[kkk] = 0xA5;
							}
						#endif
					}
					ETK_FREE(char, m_data);
					m_data = nullptr;
				}
				m_allocated = 0;
				m_size = 0;
			}
			/**
			 * @brief Swap the data of 2 Vectors
			 * @param[in] _obj second vector to swap data.
			 */
			void swap(etk::Vector<ETK_VECTOR_TYPE>& _obj) {
				// avoid Swap of itself
				if(this != &_obj) {
					etk::swap(m_data, _obj.m_data);
					etk::swap(m_allocated, _obj.m_allocated);
					etk::swap(m_size, _obj.m_size);
				}
			}
			/**
			 * @brief Move operator
			 * @param[in] _obj Vector that might be copy
			 * @return reference on the current re-copy vector
			 */
			Vector& operator=(etk::Vector<ETK_VECTOR_TYPE>&& _obj) {
				if(this != &_obj) {
					etk::swap(m_data, _obj.m_data);
					etk::swap(m_allocated, _obj.m_allocated);
					etk::swap(m_size, _obj.m_size);
				}
				// Return the current pointer
				return *this;
			}
			/**
			 * @brief Re-copy operator
			 * @param[in] _obj Vector that might be copy
			 * @return reference on the current re-copy vector
			 */
			Vector& operator=(const etk::Vector<ETK_VECTOR_TYPE>& _obj) {
				// remove all previous elements
				clear();
				// Force a specicfic size
				reserve(_obj.m_size);
				for(size_t iii=0; iii<_obj.m_size; iii++) {
					new ((char*)&m_data[iii]) ETK_VECTOR_TYPE(etk::move(_obj.m_data[iii]));
				}
				m_size = _obj.m_size;
				// Return the current pointer
				return *this;
			}
			/**
			 * @brief Add at the Last position of the Vector
			 * @param[in] _obj Element to add at the end of vector
			 */
			Vector& operator+= (const etk::Vector<ETK_VECTOR_TYPE>& _obj) {
				reserve(m_size + _obj.size());
				for(size_t iii=0; iii<_obj.size(); iii++) {
					// copy operator ...
					new ((char*)&m_data[m_size+iii]) ETK_VECTOR_TYPE(etk::move(_obj.m_data[iii]));
				}
				m_size += _obj.size();
				// Return the current pointer
				return *this;
			}
			/**
			 * @brief Get the number of element in the vector
			 * @return The number requested
			 */
			size_t size() const {
				return m_size;
			}
			/**
			 * @brief Check if the container have some element
			 * @return true The container is empty
			 * @return famse The container have some element
			 */
			bool empty() const {
				return m_size == 0;
			}
			/**
			 * @brief Get the Allocated size in the vector
			 * @return The size of allocation
			 */
			size_t allocatedSize() const {
				return m_allocated;
			}
			/**
			 * @brief Get a current element in the vector
			 * @param[in] _pos Desired position read
			 * @return Reference on the Element
			 */
			ETK_VECTOR_TYPE& get(const size_t _pos) {
				return m_data[_pos];
			}
			/**
			 * @brief Get an copy Element an a special position
			 * @param[in] _pos Position in the vector that might be get [0..Size()]
			 * @return An reference on the copy of selected element
			 */
			ETK_VECTOR_TYPE& operator[] (const size_t _pos) {
				return m_data[_pos];
			}
			/**
			 * @brief Get an Element an a special position
			 * @param[in] _pos Position in the vector that might be get [0..Size()]
			 * @return An reference on the selected element
			 */
			const ETK_VECTOR_TYPE& operator[] (const size_t _pos) const {
				return m_data[_pos];
			}
			/**
			 * @brief Get the last element of the vector
			 * @return An reference on the element
			 */
			ETK_VECTOR_TYPE& back() {
				return m_data[m_size-1];
			}
			const ETK_VECTOR_TYPE& back() const {
				return m_data[m_size-1];
			}
			/**
			 * @brief Get the first element of the vector
			 * @return An reference on the element
			 */
			ETK_VECTOR_TYPE& front() {
				return m_data[0];
			}
			const ETK_VECTOR_TYPE& front() const {
				return m_data[0];
			}
			/**
			 * @brief Add at the First position of the Vector
			 * @param[in] _item Element to add at the end of vector
			 */
			void pushFront(const ETK_VECTOR_TYPE& _item) {
				insert(0, &_item, 1);
			}
			/**
			 * @brief Add at the Last position of the Vector
			 * @param[in] _item Pointer on a list of Element to add at the start of vector
			 * @param[in] _nbElement Number of element to add.
			 */
			void pushFront(const ETK_VECTOR_TYPE * _item, size_t _nbElement) {
				insert(0, _item, _nbElement);
			}
			/**
			 * @brief Add at the Last position of the Vector (move push)
			 * @param[in] _item Element to add at the end of vector
			 */
			void pushBack(ETK_VECTOR_TYPE&& _item) {
				reserve(m_size+1);
				new ((char*)&m_data[m_size]) ETK_VECTOR_TYPE(etk::move(_item));
				m_size += 1;
			}
			/**
			 * @brief Add at the Last position of the Vector
			 * @param[in] _item Element to add at the end of vector
			 */
			void pushBack(const ETK_VECTOR_TYPE& _item) {
				reserve(m_size+1);
				new ((char*)&m_data[m_size]) ETK_VECTOR_TYPE(etk::move(_item));
				m_size += 1;
			}
			/**
			 * @brief Add at the Last position of the Vector
			 * @param[in] _item Pointer on a list of Element to add at the end of vector
			 * @param[in] _nbElement Number of element to add.
			 */
			void pushBack(const ETK_VECTOR_TYPE * _item, size_t _nbElement) {
				if (_item == nullptr) {
					return;
				}
				reserve(m_size+_nbElement);
				if (m_size > m_allocated) {
					//TK_ERROR("Resize does not work correctly ... not added item");
					return;
				}
				for (size_t iii=0; iii<_nbElement; iii++) {
					new ((char*)&m_data[m_size+iii]) ETK_VECTOR_TYPE(_item[iii]);
					m_size += 1;
				}
			}
		private:
			void pushBackN(const ETK_VECTOR_TYPE& _value) {
				pushBack(_value);
			}
			template<typename... ETK_VECTOR_TYPE_2>
			void pushBackN(const ETK_VECTOR_TYPE& _value, const ETK_VECTOR_TYPE_2& ... _args) {
				pushBack(_value);
				pushBackN(_args...);
			}
		public:
			/**
			 * @brief Remove the first element of the vector
			 */
			void popFront() {
				if(m_size>0) {
					eraseLen(0, 1);
				}
			}
			/**
			 * @brief Remove the last element of the vector
			 */
			void popBack() {
				if(m_size>0) {
					resizeDown(m_size-1);
				}
			}
			/**
			 * @brief Remove all element in the current vector
			 */
			void clear() {
				if(m_size>0) {
					resizeDown(0);
				}
			}
			/**
			 * @brief Insert N element in the Vector.
			 * @param[in] _pos Position to add the elements.
			 * @param[in] _item Pointer on a table of the elements to add.
			 * @param[in] _nbElement Number of element to add in the Vector
			 */
			void insert(size_t _pos, const ETK_VECTOR_TYPE * _item, size_t _nbElement) {
				if (_pos > m_size) {
					//TK_WARNING(" can not insert Element at this position : " << _pos << " > " << m_size << " add it at the end ... ");
					pushBack(_item, _nbElement);
					return;
				}
				// move current data (after the position)
				size_t sizeToMove = (m_size - _pos);
				// Request resize of the current buffer
				reserve(m_size+_nbElement);
				if (sizeToMove > 0) {
					for (size_t iii=1; iii<=sizeToMove; iii++) {
						// placement allocate of the element
						new ((char*)&m_data[m_size+_nbElement-iii]) ETK_VECTOR_TYPE(etk::move(m_data[m_size-iii]));
						// Remove previous element ==> simplify code.
						m_data[m_size-iii].~ETK_VECTOR_TYPE();
						#ifdef DEBUG
							// we place bad data to permit to detect stipid thing that is done in C++ code when developement is in progress.
							// Only in debug this is really slow ... and for the real allocation of memory
							for (size_t kkk=(m_size-iii)*sizeof(ETK_VECTOR_TYPE); kkk<sizeof(ETK_VECTOR_TYPE)*((m_size-iii)+1); ++kkk) {
								((char*)m_data)[kkk] = 0xA5;
							}
						#endif
					}
					
				}
				// affectation of all input element
				for (size_t iii=0; iii<_nbElement; iii++) {
					new ((char*)&m_data[_pos-iii]) ETK_VECTOR_TYPE(etk::move(_item[iii]));
				}
				m_size += _nbElement;
			}
			/**
			 * @brief Insert one element in the Vector at a specific position
			 * @param[in] _pos Position to add the elements.
			 * @param[in] _item Element to add.
			 */
			void insert(size_t _pos, const ETK_VECTOR_TYPE& _item) {
				insert(_pos, &_item, 1);
			}
			/**
			 * @brief Insert one element in the Vector at a specific position
			 * @param[in] _pos Position to add the elements.
			 * @param[in] _item Element to add.
			 */
			void insert(const Iterator& _pos, const ETK_VECTOR_TYPE& _item) {
				insert(_pos.getCurrent(), _item);
			}
			/**
			 * @brief Remove N element
			 * @param[in] _pos Position to remove the data
			 * @param[in] _nbElement number of element to remove
			 */
			void eraseLen(size_t _pos, size_t _nbElement) {
				ETK_VECTOR_DEBUG("Erase len %zu %zu\n", _pos, _nbElement);
				if (_pos > m_size) {
					//TK_ERROR(" can not Erase Len Element at this position : " << _pos << " > " << m_size);
					return;
				}
				if (_pos + _nbElement > m_size) {
					_nbElement = m_size - _pos;
				}
				ETK_VECTOR_DEBUG("Erase len %zu %zu\n", _pos, _nbElement);
				size_t idElement = m_size;
				// move current data
				size_t sizeToMove = (idElement - (_pos+_nbElement));
				if ( 0 < sizeToMove) {
					for (size_t iii=0; iii<sizeToMove; iii++) {
						etk::swap(m_data[_pos+iii], m_data[_pos+_nbElement+iii]);
					}
				}
				// Request resize of the current buffer
				resizeDown(m_size-_nbElement);
			}
			/**
			 * @brief Remove one element
			 * @param[in] _pos Position to remove the data
			 */
			inline void erase(size_t _pos) {
				eraseLen(_pos, 1);
			}
			/**
			 * @brief Remove one element
			 * @param[in] _it Iterator on the element to remove
			 * @return An iterator on the new element at this position.
			 */
			Iterator erase(const Iterator& _it) {
				ETK_VECTOR_DEBUG("Erase IT \n");
				eraseLen(_it.getCurrent(), 1);
				return position(_it.getCurrent());
			}
			/**
			 * @brief Remove one element
			 * @param[in] _pos Position to remove the data
			 */
			inline void remove(size_t _pos) {
				eraseLen(_pos, 1);
			}
			/**
			 * @brief Remove N elements
			 * @param[in] _pos Position to remove the data
			 * @param[in] _posEnd Last position number
			 */
			void erase(size_t _pos, size_t _posEnd) {
				if (_pos > m_size) {
					//TK_ERROR(" can not Erase Element at this position : " << _pos << " > " << m_size);
					return;
				}
				if (_posEnd > m_size) {
					_posEnd = m_size;
				}
				size_t nbElement = m_size - _pos;
				size_t tmpSize = m_size;
				// move current data (to the end) ==> auto removed by the resize()
				size_t sizeToMove = (tmpSize - (_pos+nbElement));
				if ( 0 < sizeToMove) {
					for (size_t iii=0; iii<sizeToMove; iii++) {
						etk::swap(m_data[_pos+iii], m_data[_pos+nbElement+iii]);
					}
				}
				// Request resize of the current buffer
				resizeDown(m_size-nbElement);
			}
			void erase(const Iterator& _pos, const Iterator& _posEnd) {
				erase(_pos.getCurrent(), _posEnd.getCurrent());
			}
			/**
			 * @brief extract data between two point : 
			 * @param[in] _posStart start position to extract data
			 * @param[in] _posEnd End position to extract data
			 * @return the extracted vector
			 */
			Vector<ETK_VECTOR_TYPE> extract(size_t _posStart = 0, size_t _posEnd=0x7FFFFFFF) const {
				Vector<ETK_VECTOR_TYPE> out;
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
			 * @brief Get the pointer on the data
			 * @return the type pointer on data
			 */
			ETK_VECTOR_TYPE* dataPointer() {
				return &m_data[0];
			}
			/**
			 * @brief Get an iterator an an specific position
			 * @param[in] _pos Requested position of the iterator in the vector
			 * @return The Iterator
			 */
			Iterator position(size_t _pos) {
				return Iterator(this, _pos);
			}
			const Iterator position(size_t _pos) const {
				return Iterator(this, _pos);
			}
			/**
			 * @brief Get an Iterator on the start position of the Vector
			 * @return The Iterator
			 */
			Iterator begin() {
				return position(0);
			}
			const Iterator begin() const {
				return position(0);
			}
			/**
			 * @brief Get an Iterator on the end position of the Vector
			 * @return The Iterator
			 */
			Iterator end() {
				return position(size());
			}
			const Iterator end() const {
				return position(size());
			}
			
			/**
			 * @brief Resize the vector with a basic element
			 * @param[in] _newSize New size of the vector
			 */
			void resize(size_t _newSize, const ETK_VECTOR_TYPE& _basicElement) {
				// Reallocate memory
				if (_newSize > m_size) {
					if (_newSize > m_allocated) {
						changeAllocation(_newSize);
					}
					for (size_t iii=m_size; iii<_newSize; ++iii) {
						new ((char*)&m_data[iii]) ETK_VECTOR_TYPE(_basicElement);
					}
					m_size = _newSize;
					return;
				} else if (_newSize == m_size) {
					return;
				}
				for (size_t iii=m_size; iii<_newSize; ++iii) {
					m_data[iii].~ETK_VECTOR_TYPE();
					#ifdef DEBUG
						// we place bad data to permit to detect stipid thing that is done in C++ code when developement is in progress.
						// Only in debug this is really slow ... and for the real allocation of memory
						for (size_t kkk=iii*sizeof(ETK_VECTOR_TYPE); kkk<sizeof(ETK_VECTOR_TYPE)*(iii+1); ++kkk) {
							((char*)m_data)[kkk] = 0xA5;
						}
					#endif
				}
				m_size = _newSize;
			}
			/**
			 * @brief Change the current size of the vector
			 * @param[in] _newSize New requested size of element in the vector
			 */
			void resize(size_t _newSize) {
				ETK_VECTOR_DEBUG("Resize %zu => %zu\n", m_size, _newSize);
				// Reallocate memory
				if (_newSize > m_size) {
					if (_newSize > m_allocated) {
						changeAllocation(_newSize);
					}
					for (size_t iii=m_size; iii<_newSize; ++iii) {
						new ((char*)&m_data[iii]) ETK_VECTOR_TYPE();
					}
				} else if (_newSize == m_size) {
					return;
				}
				ETK_VECTOR_DEBUG("Reduce %zu => %zu\n", m_size, _newSize);
				for (size_t iii=_newSize; iii<m_size; ++iii) {
					m_data[iii].~ETK_VECTOR_TYPE();
					#ifdef DEBUG
						// we place bad data to permit to detect stipid thing that is done in C++ code when developement is in progress.
						// Only in debug this is really slow ... and for the real allocation of memory
						for (size_t kkk=iii*sizeof(ETK_VECTOR_TYPE); kkk<sizeof(ETK_VECTOR_TYPE)*(iii+1); ++kkk) {
							((char*)m_data)[kkk] = 0xA5;
						}
					#endif
				}
				m_size = _newSize;
			}
		private:
			void resizeDown(size_t _newSize) {
				ETK_VECTOR_DEBUG("Resize %zu => %zu\n", m_size, _newSize);
				// Reallocate memory
				if (_newSize > m_allocated) {
					ETK_VECTOR_DEBUG("Resize Down %zu => %zu\n", m_size, _newSize);
					return;
				} else if (_newSize == m_allocated) {
					return;
				}
				ETK_VECTOR_DEBUG("Reduce %zu => %zu\n", m_size, _newSize);
				for (size_t iii=_newSize; iii<m_size; ++iii) {
					m_data[iii].~ETK_VECTOR_TYPE();
					#ifdef DEBUG
						// we place bad data to permit to detect stipid thing that is done in C++ code when developement is in progress.
						// Only in debug this is really slow ... and for the real allocation of memory
						for (size_t kkk=iii*sizeof(ETK_VECTOR_TYPE); kkk<sizeof(ETK_VECTOR_TYPE)*(iii+1); ++kkk) {
							((char*)m_data)[kkk] = 0xA5;
						}
					#endif
				}
				m_size = _newSize;
			}
		public:
			/**
			 * @brief Force the container to have a minimum size in memory allocation
			 * @param[in] _size Size in byte that is requested.
			 */
			void reserve(size_t _size) {
				if (_size <= m_allocated) {
					return;
				}
				changeAllocation(_size);
			}
		private:
			/**
			 * @brief Change the current allocation to the correct one (depend on the current size)
			 * @param[in] _newSize Minimum number of element needed
			 */
			void changeAllocation(size_t _newSize) {
				size_t requestSize = m_allocated;
				// set the size with the correct chose type:
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
				if (m_data == nullptr) {
					// no data allocated ==> request an allocation (might be the first)
					m_data = (ETK_VECTOR_TYPE*)ETK_MALLOC(char, sizeof(ETK_VECTOR_TYPE)*requestSize);
					if (m_data == nullptr) {
						//TK_CRITICAL("Vector : Error in data allocation request allocation:" << requestSize << "*" << (int32_t)(sizeof(ETK_VECTOR_TYPE)) << "bytes" );
						m_allocated = 0;
						return;
					}
					#ifdef DEBUG
						// we place bad data to permit to detect stipid thing that is done in C++ code when developement is in progress.
						// Only in debug this is really slow ... and for the real allocation of memory
						for (size_t kkk=0; kkk<sizeof(ETK_VECTOR_TYPE)*requestSize; ++kkk) {
							((char*)m_data)[kkk] = 0x5A;
						}
					#endif
				} else {
					// allocate a new pool of data:
					ETK_VECTOR_TYPE* dataTmp = (ETK_VECTOR_TYPE*)ETK_MALLOC(char, sizeof(ETK_VECTOR_TYPE)*requestSize);;
					if (dataTmp == nullptr) {
						//TK_CRITICAL("Vector : Error in data allocation request allocation:" << requestSize << "*" << (int32_t)(sizeof(ETK_VECTOR_TYPE)) << "bytes" );
						return;
					}
					#ifdef DEBUG
						// we place bad data to permit to detect stipid thing that is done in C++ code when developement is in progress.
						// Only in debug this is really slow ... and for the real allocation of memory
						for (size_t kkk=0; kkk<sizeof(ETK_VECTOR_TYPE)*requestSize; ++kkk) {
							((char*)dataTmp)[kkk] = 0x5A;
						}
					#endif
					// copy data in the new pool
					size_t nbElements = etk::min(requestSize, m_allocated);
					for(size_t iii=0; iii<nbElements; iii++) {
						// Move in the new element
						new ((char*)&dataTmp[iii]) ETK_VECTOR_TYPE(etk::move(m_data[iii]));
						// Remove the old one.
						m_data[iii].~ETK_VECTOR_TYPE();
						#ifdef DEBUG
							// we place bad data to permit to detect stipid thing that is done in C++ code when developement is in progress.
							// Only in debug this is really slow ... and for the real allocation of memory
							for (size_t kkk=iii*sizeof(ETK_VECTOR_TYPE); kkk<sizeof(ETK_VECTOR_TYPE)*(iii+1); ++kkk) {
								((char*)m_data)[kkk] = 0xA5;
							}
						#endif
					}
					// switch pointer:
					ETK_VECTOR_TYPE* dataTmp2 = m_data;
					m_data = dataTmp;
					// remove old pool
					if (dataTmp2 != nullptr) {
						ETK_FREE(char, dataTmp2);
					}
				}
				// set the new allocation size
				m_allocated = requestSize;
			}
		public :
			/*****************************************************
			 *    == operator
			 *****************************************************/
			bool operator== (const Vector<ETK_VECTOR_TYPE>& _obj) const {
				// check if it was the same pointer
				if( this == &_obj ) {
					return true;
				}
				// first step : check the size ...
				if (m_size != _obj.m_size) {
					return false;
				}
				if(    m_data == nullptr
				    || _obj.m_data == nullptr) {
					return false;
				}
				for (size_t iii=0; iii<m_size; iii++) {
					if (m_data[iii]!=_obj.m_data[iii]) {
						return false;
					}
				}
				return true;
			}
			/*****************************************************
			 *    != operator
			 *****************************************************/
			bool operator!= (const Vector<ETK_VECTOR_TYPE>& _obj) const {
				// check if it was the same pointer
				if( this == &_obj ) {
					return false;
				}
				// first step : check the size ...
				if (m_size != _obj.m_size) {
					return true;
				}
				if(    m_data == nullptr
				    || _obj.m_data == nullptr) {
					return false;
				}
				for (size_t iii=0; iii<m_size; iii++) {
					if (m_data[iii]!=_obj.m_data[iii]) {
						return true;
					}
				}
				return false;
			}
			/*****************************************************
			 *    >= operator
			 *****************************************************/
			bool operator>= (const Vector<ETK_VECTOR_TYPE>& _obj) const {
				// TODO : Later
				return false;
			}
			/*****************************************************
			 *    > operator
			 *****************************************************/
			bool operator> (const Vector<ETK_VECTOR_TYPE>& _obj) const {
				// TODO : Later
				return false;
			}
			/*****************************************************
			 *    <= operator
			 *****************************************************/
			bool operator<= (const Vector<ETK_VECTOR_TYPE>& _obj) const {
				// TODO : Later
				return false;
			}
			/*****************************************************
			 *    > operator
			 *****************************************************/
			bool operator< (const Vector<ETK_VECTOR_TYPE>& _obj) const {
				// TODO : Later
				return false;
			}
			void sort(size_t _start, size_t _stop, bool (*_comparator)(const ETK_VECTOR_TYPE&, const ETK_VECTOR_TYPE&)) {
				if (_stop > m_size) {
					_stop = m_size;
				}
				if (_start > m_size) {
					_start = m_size;
				}
				if (_start > _stop) {
					size_t start = _start;
					_start = _stop;
					_stop = start;
				}
				for (size_t iii=_start; iii<_stop; ++iii) {
					bool swapped = false;
					for (size_t jjj=_start; jjj<_stop - (iii+1); ++jjj) {
						if (_comparator(m_data[jjj], m_data[jjj+1]) == false) {
							etk::swap(m_data[jjj], m_data[jjj+1]);
							swapped = true;
						}
					}
					if (swapped == false) {
						break;
					}
				}
			}
	};
	//! @not_in_doc
	template<typename ETK_VECTOR_TYPE_1, typename ETK_VECTOR_TYPE_2>
	bool isIn(const ETK_VECTOR_TYPE_1& _val, const etk::Vector<ETK_VECTOR_TYPE_2>& _list) {
		for (size_t iii=0; iii<_list.size(); ++iii) {
			if (_list[iii] == _val) {
				return true;
			}
		}
		return false;
	}
	class Stream;
	//! @not_in_doc
	template<class ETK_VECTOR_TYPE>
	etk::Stream& operator <<(etk::Stream& _os, const etk::Vector<ETK_VECTOR_TYPE>& _obj) {
		_os << "{";
		for (size_t iii=0; iii< _obj.size(); iii++) {
			if (iii>0) {
				_os << ";";
			}
			_os << _obj[iii];
		}
		_os << "}";
		return _os;
	}
}
