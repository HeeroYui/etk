/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL-2 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/Stream.hpp>
#include <etk/Allocator.hpp>
#include <etk/Exception.hpp>

//#define ETK_ARRAY_DEBUG(...) printf(__VA_ARGS__)
#define ETK_ARRAY_DEBUG(...) do {} while (false)

namespace etk {
	class Stream;
	/**
	 * @brief Array class ...
	 *
	 * @param[in] ETK_ARRAY_TYPE class type of the current element.
	 *
	 *              m_data
	 *                 <------------ m_dataSize ------------>
	 *                 ----------------------------------------
	 *                 |    0                                 |
	 *                 |--------------------------------------|
	 *                 |    1                                 |
	 *                 |--------------------------------------|
	 *                 |    2                                 |
	 *                 |--------------------------------------|
	 * m_size          |    3                                 |
	 *                 |--------------------------------------|
	 *                 |    x                                 |
	 *                 |--------------------------------------|
	 *                 |    x                                 |
	 *                 |--------------------------------------|
	 *                 |    x                                 |
	 *                 |--------------------------------------|
	 *                 |    x                                 |
	 *                 |--------------------------------------|
	 *                 |    x                                 |
	 *                 |--------------------------------------|
	 *                 |    x                                 |
	 *                 |--------------------------------------|
	 *                 |    x                                 |
	 *                 |--------------------------------------|
	 * ETK_ARRAY_SIZE  |    x                                 |
	 *                 ----------------------------------------
	 */
	template<class ETK_ARRAY_TYPE, size_t ETK_ARRAY_SIZE=1> class Array {
		public:
			class Iterator {
				private:
					size_t m_current; //!< current Id on the Array
					Array<ETK_ARRAY_TYPE, ETK_ARRAY_SIZE>* m_array; //!< Pointer on the current element of the ArrayBin
				public:
					/**
					 * @brief Basic iterator constructor with no link with an etk::Array
					 */
					Iterator():
					  m_current(0),
					  m_array(nullptr) {
						// nothing to do ...
					}
					/**
					 * @brief Recopy constructor on a specific etkArray.
					 * @param[in] _obj The Iterator that might be copy
					 */
					Iterator(const Iterator & _obj):
					  m_current(_obj.m_current),
					  m_array(_obj.m_array) {
						// nothing to do ...
					}
					/**
					 * @brief Assignation operator.
					 * @param[in] _otherIterator The Iterator that might be copy
					 * @return reference on the current Iterator
					 */
					Iterator& operator=(const Iterator & _otherIterator) {
						m_current = _otherIterator.m_current;
						m_array = _otherIterator.m_array;
						return *this;
					}
					/**
					 * @brief Basic destructor
					 */
					~Iterator() {
						m_current = 0;
						m_array = nullptr;
					}
					/**
					 * @brief basic boolean cast
					 * @return true if the element is present in the etkArray size
					 */
					operator bool () {
						return (m_current < m_array->size());
					}
					/**
					 * @brief != Comparaison operator
					 * @param[in] _obj Object to compare
					 * @return true if the element are different
					 */
					bool operator!= (const Iterator& _obj) {
						if (    m_array != _obj.m_array
						     || m_current != _obj.m_current) {
							return true;
						}
						return false;
					}
					/**
					 * @brief == Comparaison operator.
					 * @param[in] _obj Object to compare.
					 * @return true if the element are identical.
					 */
					bool operator== (const Iterator& _obj) {
						if (    m_array == _obj.m_array
						     && m_current == _obj.m_current) {
							return true;
						}
						return false;
					}
					/**
					 * @brief Incremental operator
					 * @return Reference on the current iterator increment
					 */
					Iterator& operator++ () {
						if (    m_array != nullptr
						     && m_current < m_array->size() )
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
						if (    m_array != nullptr
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
					ETK_ARRAY_TYPE* operator-> () const {
						return &m_array->get(m_current);
					}
					/**
					 * @brief Get reference on the current Element
					 * @return the reference on the current Element 
					 */
					ETK_ARRAY_TYPE& operator* () const {
						return m_array->get(m_current);
					}
				private:
					Iterator(const Array<ETK_ARRAY_TYPE, ETK_ARRAY_SIZE> * _obj, int32_t _pos):
					  m_current(_pos),
					  m_array(const_cast<Array<ETK_ARRAY_TYPE, ETK_ARRAY_SIZE> *>(_obj)) {
						// nothing to do ...
					}
					size_t getCurrent() const {
						return m_current;
					}
					friend class Array;
			};
		private:
			uint8_t m_rawData[ETK_ARRAY_SIZE*sizeof(ETK_ARRAY_TYPE)]; //!< pointer on the current table of Data (static allocated ==> can not change)
			ETK_ARRAY_TYPE* m_data = (ETK_ARRAY_TYPE*)m_rawData; //!< pointer on the current table of Data (static allocated ==> can not change)
			size_t m_size = 0; //!< Number of element in the buffer
			const size_t m_allocated = ETK_ARRAY_SIZE; //!< Current allocated size
		public:
			/**
			 * @brief Create an empty Array
			 */
			Array() {
				
			}
			/**
			 * @brief List initializer (ex: etk::Array<etk::String> plop = {"hello", world"}
			 * @param[in] _element element to add in the Array
			 */
			template<typename... ETK_ARRAY_TYPE_2>
			Array(const ETK_ARRAY_TYPE_2& ... _args) {
				int32_t nbElement = int32_t(sizeof...(ETK_ARRAY_TYPE_2));
				if (nbElement >= m_allocated) {
					throw etk::exception::InvalidArgument("Size too big ...");
					return;
				}
				pushBackN(_args...);
			}
			/**
			 * @brief Re-copy constructor (copy all needed data)
			 * @param[in] _obj Array that might be copy
			 */
			Array(const etk::Array<ETK_ARRAY_TYPE, ETK_ARRAY_SIZE>& _obj) {
				for(size_t iii=0; iii<_obj.m_size; iii++) {
					new ((char*)&m_data[iii]) ETK_ARRAY_TYPE(etk::move(_obj.m_data[iii]));
				}
				m_size = _obj.m_size;
			}
			/**
			 * @brief Move operator of elements
			 * @param[in] _obj Object to move
			 */
			// TODO: This is a little complicated ...
			Array(etk::Array<ETK_ARRAY_TYPE, ETK_ARRAY_SIZE>&& _obj) {
				swap(_obj);
			}
			/**
			 * @brief Destructor of the current class
			 */
			~Array() {
				for(size_t iii=0; iii<m_size; iii++) {
					m_data[iii].~ETK_ARRAY_TYPE();
					#ifdef DEBUG
						// we place bad data to permit to detect stipid thing that is done in C++ code when developement is in progress.
						// Only in debug this is really slow ... and for the real allocation of memory
						for (size_t kkk=iii*sizeof(ETK_ARRAY_TYPE); kkk<sizeof(ETK_ARRAY_TYPE)*(iii+1); ++kkk) {
							((char*)m_data)[kkk] = 0xA5;
						}
					#endif
				}
				m_size = 0;
			}
			/**
			 * @brief Swap the data of 2 Arrays
			 * @param[in] _obj second Array to swap data.
			 */
			void swap(etk::Array<ETK_ARRAY_TYPE, ETK_ARRAY_SIZE>& _obj) {
				// avoid Swap of itself
				if(this != &_obj) {
					if (_obj.size() < size()) {
						_obj.swap(*this);
						return;
					}
					for (size_t iii=0; iii<etk::min(size(), _obj.size()); ++iii) {
						etk::swap(m_data[iii], _obj.m_data[iii]);
					}
					for (size_t iii=size(); iii<_obj.size(); ++iii) {
						// Construc new local object
						new ((char*)&m_data[iii]) ETK_ARRAY_TYPE(etk::move(_obj.m_data[iii]));
						// destruct remote object
						_obj.m_data[iii].~ETK_ARRAY_TYPE();
					}
					for (size_t iii=_obj.size(); iii<size(); ++iii) {
						// Construc new local object
						new ((char*)&_obj.m_data[iii]) ETK_ARRAY_TYPE(etk::move(m_data[iii]));
						// destruct remote object
						m_data[iii].~ETK_ARRAY_TYPE();
					}
					etk::swap(m_size, _obj.m_size);
				}
			}
			/**
			 * @brief Move operator
			 * @param[in] _obj Array that might be copy
			 * @return reference on the current re-copy Array
			 */
			Array& operator=(etk::Array<ETK_ARRAY_TYPE, ETK_ARRAY_SIZE>&& _obj) {
				if(this != &_obj) {
					etk::swap(this, _obj);
				}
				// Return the current pointer
				return *this;
			}
			/**
			 * @brief Re-copy operator
			 * @param[in] _obj Array that might be copy
			 * @return reference on the current re-copy Array
			 */
			Array& operator=(const etk::Array<ETK_ARRAY_TYPE, ETK_ARRAY_SIZE>& _obj) {
				// remove all previous elements
				clear();
				for(size_t iii=0; iii<_obj.m_size; iii++) {
					new ((char*)&m_data[iii]) ETK_ARRAY_TYPE(etk::move(_obj.m_data[iii]));
				}
				m_size = _obj.m_size;
				// Return the current pointer
				return *this;
			}
			/**
			 * @brief Get the number of element in the Array
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
			 * @brief Get the Allocated size in the Array
			 * @return The size of allocation
			 */
			size_t allocatedSize() const {
				return m_allocated;
			}
			/**
			 * @brief Get a current element in the Array
			 * @param[in] _pos Desired position read
			 * @return Reference on the Element
			 */
			ETK_ARRAY_TYPE& get(const size_t _pos) {
				return m_data[_pos];
			}
			/**
			 * @brief Get an copy Element an a special position
			 * @param[in] _pos Position in the Array that might be get [0..Size()]
			 * @return An reference on the copy of selected element
			 */
			ETK_ARRAY_TYPE& operator[] (const size_t _pos) {
				return m_data[_pos];
			}
			/**
			 * @brief Get an Element an a special position
			 * @param[in] _pos Position in the Array that might be get [0..Size()]
			 * @return An reference on the selected element
			 */
			const ETK_ARRAY_TYPE& operator[] (const size_t _pos) const {
				return m_data[_pos];
			}
			/**
			 * @brief Get the last element of the Array
			 * @return An reference on the element
			 */
			ETK_ARRAY_TYPE& back() {
				return m_data[m_size-1];
			}
			const ETK_ARRAY_TYPE& back() const {
				return m_data[m_size-1];
			}
			/**
			 * @brief Get the first element of the Array
			 * @return An reference on the element
			 */
			ETK_ARRAY_TYPE& front() {
				return m_data[0];
			}
			const ETK_ARRAY_TYPE& front() const {
				return m_data[0];
			}
			/**
			 * @brief Add at the First position of the Array
			 * @param[in] _item Element to add at the end of Array
			 */
			void pushFront(const ETK_ARRAY_TYPE& _item) {
				insert(0, &_item, 1);
			}
			/**
			 * @brief Add at the Last position of the Array
			 * @param[in] _item Pointer on a list of Element to add at the start of Array
			 * @param[in] _nbElement Number of element to add.
			 */
			void pushFront(const ETK_ARRAY_TYPE * _item, size_t _nbElement) {
				insert(0, _item, _nbElement);
			}
			/**
			 * @brief Add at the Last position of the Array (move push)
			 * @param[in] _item Element to add at the end of Array
			 */
			void pushBack(ETK_ARRAY_TYPE&& _item) {
				if (m_size == ETK_ARRAY_SIZE) {
					throw etk::exception::OverflowError("try add to much data in array");
				}
				new ((char*)&m_data[m_size]) ETK_ARRAY_TYPE(etk::move(_item));
				m_size += 1;
			}
			/**
			 * @brief Add at the Last position of the Array
			 * @param[in] _item Element to add at the end of Array
			 */
			void pushBack(const ETK_ARRAY_TYPE& _item) {
				if (m_size == ETK_ARRAY_SIZE) {
					throw etk::exception::OverflowError("try add to much data in array");
				}
				new ((char*)&m_data[m_size]) ETK_ARRAY_TYPE(etk::move(_item));
				m_size += 1;
			}
			/**
			 * @brief Add at the Last position of the Array
			 * @param[in] _item Pointer on a list of Element to add at the end of Array
			 * @param[in] _nbElement Number of element to add.
			 */
			void pushBack(const ETK_ARRAY_TYPE * _item, size_t _nbElement) {
				if (_item == nullptr) {
					return;
				}
				if (m_size+_nbElement > ETK_ARRAY_SIZE) {
					throw etk::exception::OverflowError("try add to much data in array");
				}
				for (size_t iii=0; iii<_nbElement; iii++) {
					new ((char*)&m_data[m_size+iii]) ETK_ARRAY_TYPE(_item[iii]);
					m_size += 1;
				}
			}
		private:
			void pushBackN(const ETK_ARRAY_TYPE& _value) {
				pushBack(_value);
			}
			template<typename... ETK_ARRAY_TYPE_2>
			void pushBackN(const ETK_ARRAY_TYPE& _value, const ETK_ARRAY_TYPE_2& ... _args) {
				pushBack(_value);
				pushBackN(_args...);
			}
		public:
			/**
			 * @brief Remove the first element of the Array
			 */
			void popFront() {
				if(m_size>0) {
					eraseLen(0, 1);
				}
			}
			/**
			 * @brief Remove the last element of the Array
			 */
			void popBack() {
				if(m_size>0) {
					resizeDown(m_size-1);
				}
			}
			/**
			 * @brief Remove all element in the current Array
			 */
			void clear() {
				if(m_size>0) {
					resizeDown(0);
				}
			}
			/**
			 * @brief Insert N element in the Array.
			 * @param[in] _pos Position to add the elements.
			 * @param[in] _item Pointer on a table of the elements to add.
			 * @param[in] _nbElement Number of element to add in the Array
			 */
			void insert(size_t _pos, const ETK_ARRAY_TYPE * _item, size_t _nbElement) {
				if (_pos > m_size) {
					//TK_WARNING(" can not insert Element at this position : " << _pos << " > " << m_size << " add it at the end ... ");
					pushBack(_item, _nbElement);
					return;
				}
				// move current data (after the position)
				size_t sizeToMove = (m_size - _pos);
				if (sizeToMove > 0) {
					for (size_t iii=1; iii<=sizeToMove; iii++) {
						// placement allocate of the element
						new ((char*)&m_data[m_size+_nbElement-iii]) ETK_ARRAY_TYPE(etk::move(m_data[m_size-iii]));
						// Remove previous element ==> simplify code.
						m_data[m_size-iii].~ETK_ARRAY_TYPE();
						#ifdef DEBUG
							// we place bad data to permit to detect stipid thing that is done in C++ code when developement is in progress.
							// Only in debug this is really slow ... and for the real allocation of memory
							for (size_t kkk=(m_size-iii)*sizeof(ETK_ARRAY_TYPE); kkk<sizeof(ETK_ARRAY_TYPE)*((m_size-iii)+1); ++kkk) {
								((char*)m_data)[kkk] = 0xA5;
							}
						#endif
					}
					
				}
				// affectation of all input element
				for (size_t iii=0; iii<_nbElement; iii++) {
					new ((char*)&m_data[_pos-iii]) ETK_ARRAY_TYPE(etk::move(_item[iii]));
				}
				m_size += _nbElement;
			}
			/**
			 * @brief Insert one element in the Array at a specific position
			 * @param[in] _pos Position to add the elements.
			 * @param[in] _item Element to add.
			 */
			void insert(size_t _pos, const ETK_ARRAY_TYPE& _item) {
				insert(_pos, &_item, 1);
			}
			/**
			 * @brief Insert one element in the Array at a specific position
			 * @param[in] _pos Position to add the elements.
			 * @param[in] _item Element to add.
			 */
			void insert(const Iterator& _pos, const ETK_ARRAY_TYPE& _item) {
				insert(_pos.getCurrent(), _item);
			}
			/**
			 * @brief Remove N element
			 * @param[in] _pos Position to remove the data
			 * @param[in] _nbElement number of element to remove
			 */
			void eraseLen(size_t _pos, size_t _nbElement) {
				ETK_ARRAY_DEBUG("Erase len %zu %zu\n", _pos, _nbElement);
				if (_pos > m_size) {
					//TK_ERROR(" can not Erase Len Element at this position : " << _pos << " > " << m_size);
					return;
				}
				if (m_size+_nbElement > ETK_ARRAY_SIZE) {
					throw etk::exception::OverflowError("try add to much data in array");
				}
				if (_pos + _nbElement > m_size) {
					_nbElement = m_size - _pos;
				}
				ETK_ARRAY_DEBUG("Erase len %zu %zu\n", _pos, _nbElement);
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
				ETK_ARRAY_DEBUG("Erase IT \n");
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
			 * @brief Get the pointer on the data
			 * @return the type pointer on data
			 */
			ETK_ARRAY_TYPE* dataPointer() {
				return &m_data[0];
			}
			/**
			 * @brief Get an iterator an an specific position
			 * @param[in] _pos Requested position of the iterator in the Array
			 * @return The Iterator
			 */
			Iterator position(size_t _pos) {
				return Iterator(this, _pos);
			}
			const Iterator position(size_t _pos) const {
				return Iterator(this, _pos);
			}
			/**
			 * @brief Get an Iterator on the start position of the Array
			 * @return The Iterator
			 */
			Iterator begin() {
				return position(0);
			}
			const Iterator begin() const {
				return position(0);
			}
			/**
			 * @brief Get an Iterator on the end position of the Array
			 * @return The Iterator
			 */
			Iterator end() {
				return position(size());
			}
			const Iterator end() const {
				return position(size());
			}
			
			/**
			 * @brief Resize the Array with a basic element
			 * @param[in] _newSize New size of the Array
			 */
			void resize(size_t _newSize, const ETK_ARRAY_TYPE& _basicElement) {
				if (_newSize > ETK_ARRAY_SIZE) {
					throw etk::exception::OverflowError("try resize with larger size in array");
				}
				// Reallocate memory
				if (_newSize > m_size) {
					for (size_t iii=m_size; iii<_newSize; ++iii) {
						new ((char*)&m_data[iii]) ETK_ARRAY_TYPE(_basicElement);
					}
					m_size = _newSize;
					return;
				} else if (_newSize == m_size) {
					return;
				}
				for (size_t iii=m_size; iii<_newSize; ++iii) {
					m_data[iii].~ETK_ARRAY_TYPE();
					#ifdef DEBUG
						// we place bad data to permit to detect stipid thing that is done in C++ code when developement is in progress.
						// Only in debug this is really slow ... and for the real allocation of memory
						for (size_t kkk=iii*sizeof(ETK_ARRAY_TYPE); kkk<sizeof(ETK_ARRAY_TYPE)*(iii+1); ++kkk) {
							((char*)m_data)[kkk] = 0xA5;
						}
					#endif
				}
				m_size = _newSize;
			}
			/**
			 * @brief Change the current size of the Array
			 * @param[in] _newSize New requested size of element in the Array
			 */
			void resize(size_t _newSize) {
				ETK_ARRAY_DEBUG("Resize %zu => %zu\n", m_size, _newSize);
				if (_newSize > ETK_ARRAY_SIZE) {
					throw etk::exception::OverflowError("try resize with larger size in array");
				}
				// Reallocate memory
				if (_newSize > m_size) {
					for (size_t iii=m_size; iii<_newSize; ++iii) {
						new ((char*)&m_data[iii]) ETK_ARRAY_TYPE();
					}
				} else if (_newSize == m_size) {
					return;
				}
				ETK_ARRAY_DEBUG("Reduce %zu => %zu\n", m_size, _newSize);
				for (size_t iii=_newSize; iii<m_size; ++iii) {
					m_data[iii].~ETK_ARRAY_TYPE();
					#ifdef DEBUG
						// we place bad data to permit to detect stipid thing that is done in C++ code when developement is in progress.
						// Only in debug this is really slow ... and for the real allocation of memory
						for (size_t kkk=iii*sizeof(ETK_ARRAY_TYPE); kkk<sizeof(ETK_ARRAY_TYPE)*(iii+1); ++kkk) {
							((char*)m_data)[kkk] = 0xA5;
						}
					#endif
				}
				m_size = _newSize;
			}
		private:
			void resizeDown(size_t _newSize) {
				ETK_ARRAY_DEBUG("Resize %zu => %zu\n", m_size, _newSize);
				for (size_t iii=_newSize; iii<m_size; ++iii) {
					m_data[iii].~ETK_ARRAY_TYPE();
					#ifdef DEBUG
						// we place bad data to permit to detect stipid thing that is done in C++ code when developement is in progress.
						// Only in debug this is really slow ... and for the real allocation of memory
						for (size_t kkk=iii*sizeof(ETK_ARRAY_TYPE); kkk<sizeof(ETK_ARRAY_TYPE)*(iii+1); ++kkk) {
							((char*)m_data)[kkk] = 0xA5;
						}
					#endif
				}
				m_size = _newSize;
			}
		public:
			/*****************************************************
			 *    == operator
			 *****************************************************/
			bool operator== (const Array<ETK_ARRAY_TYPE, ETK_ARRAY_SIZE>& _obj) const {
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
			bool operator!= (const Array<ETK_ARRAY_TYPE, ETK_ARRAY_SIZE>& _obj) const {
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
			bool operator>= (const Array<ETK_ARRAY_TYPE, ETK_ARRAY_SIZE>& _obj) const {
				// TODO : Later
				return false;
			}
			/*****************************************************
			 *    > operator
			 *****************************************************/
			bool operator> (const Array<ETK_ARRAY_TYPE, ETK_ARRAY_SIZE>& _obj) const {
				// TODO : Later
				return false;
			}
			/*****************************************************
			 *    <= operator
			 *****************************************************/
			bool operator<= (const Array<ETK_ARRAY_TYPE, ETK_ARRAY_SIZE>& _obj) const {
				// TODO : Later
				return false;
			}
			/*****************************************************
			 *    > operator
			 *****************************************************/
			bool operator< (const Array<ETK_ARRAY_TYPE, ETK_ARRAY_SIZE>& _obj) const {
				// TODO : Later
				return false;
			}
			void sort(size_t _start, size_t _stop, bool (*_comparator)(const ETK_ARRAY_TYPE&, const ETK_ARRAY_TYPE&)) {
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
	template<typename ETK_ARRAY_TYPE_1, typename ETK_ARRAY_TYPE_2, size_t ETK_ARRAY_SIZE>
	bool isIn(const ETK_ARRAY_TYPE_1& _val, const etk::Array<ETK_ARRAY_TYPE_2, ETK_ARRAY_SIZE>& _list) {
		for (size_t iii=0; iii<_list.size(); ++iii) {
			if (_list[iii] == _val) {
				return true;
			}
		}
		return false;
	}
	class Stream;
	//! @not_in_doc
	template<class ETK_ARRAY_TYPE, size_t ETK_ARRAY_SIZE>
	etk::Stream& operator <<(etk::Stream& _os, const etk::Array<ETK_ARRAY_TYPE, ETK_ARRAY_SIZE>& _obj) {
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
