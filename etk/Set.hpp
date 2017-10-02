/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/Pair.hpp>
#include <etk/Vector.hpp>

namespace etk {
	/**
	 * @brief Set table template is a simple classical "Set" interface.
	 * A Set contain a list of sorted single element
	 *   - 1 2 3 4 19 55 4356345
	 *   - "aaa" "AABB" "ZZ"
	 * 
	 * A simple example of use:
	 * @code{.cpp}
	 * // Create a integer Set table
	 * etk::Set<int> myValue;
	 * // add some element (note add and set is the same function)
	 * myValue.add(98837);
	 * myValue.set(88);
	 * // Display an element:
	 * printf("my value is : %d", myValue[2]);
	 * // Change value of an element:
	 * size_t position = myValue.set(99);
	 * // Remove an element:
	 * myValue.remove(99);
	 * //Clean all the table:
	 * myValue.clear();
	 * // number of elements:
	 * size_t size = myValue.size();
	 * @endcode
	 */
	template<class ETK_SET_TYPE, int STATIC_ALLOCATION_SIZE = -1>
	class Set {
		public:
		class Iterator {
				private:
					size_t m_current; //!< current Id on the vector
					Set<ETK_SET_TYPE>* m_set; //!< Pointer on the current element of the vectorBin
				public:
					/**
					 * @brief Basic iterator constructor with no link with an etk::Vector
					 */
					Iterator():
					  m_current(0),
					  m_set(nullptr) {
						// nothing to do ...
					}
					/**
					 * @brief Recopy constructor on a specific etkVector.
					 * @param[in] _obj The Iterator that might be copy
					 */
					Iterator(const Iterator & _obj):
					  m_current(_obj.m_current),
					  m_set(_obj.m_set) {
						// nothing to do ...
					}
					/**
					 * @brief Assignation operator.
					 * @param[in] _otherIterator The Iterator that might be copy
					 * @return reference on the current Iterator
					 */
					Iterator& operator=(const Iterator & _obj) {
						m_current = _obj.m_current;
						m_set = _obj.m_set;
						return *this;
					}
					/**
					 * @brief Basic destructor
					 */
					~Iterator() {
						m_current = 0;
						m_set = nullptr;
					}
					/**
					 * @brief basic boolean cast
					 * @return true if the element is present in the etkVector size
					 */
					operator bool () {
						return (m_current < m_set->size());
					}
					/**
					 * @brief Incremental operator
					 * @return Reference on the current iterator increment
					 */
					Iterator& operator++ () {
						if (    m_set != nullptr
						     && m_current < m_set->size() )
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
						if (    m_set != nullptr
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
					const ETK_SET_TYPE* operator-> () const {
						//TK_CHECK_INOUT(m_current < m_set->size());
						return &(*m_set)[m_current];
					}
					ETK_SET_TYPE* operator-> () {
						//TK_CHECK_INOUT(m_current < m_set->size());
						return &(*m_set)[m_current];
					}
					/**
					 * @brief Get reference on the current Element
					 * @return the reference on the current Element 
					 */
					const ETK_SET_TYPE& operator* () const {
						//TK_CHECK_INOUT(m_current < m_set->size());
						return (*m_set)[m_current];
					}
					ETK_SET_TYPE& operator* () {
						//TK_CHECK_INOUT(m_current < m_set->size());
						return (*m_set)[m_current];
					}
					bool operator== (const Iterator& _obj) const{
						return    m_set == _obj.m_set
						       && m_current == _obj.m_current;
					}
					bool operator!= (const Iterator& _obj) const {
						return    m_set != _obj.m_set
						       || m_current != _obj.m_current;
					}
				private:
					Iterator(const etk::Set<ETK_SET_TYPE> * _obj, int32_t _pos):
					  m_current(_pos),
					  m_set(const_cast<etk::Set<ETK_SET_TYPE>*>(_obj)) {
						// nothing to do ...
					}
					size_t getCurrent() const {
						return m_current;
					}
					friend class Set;
			};
			typedef bool (*sortFunction)(const ETK_SET_TYPE& _key1, const ETK_SET_TYPE& _key2);
		private:
			etk::Vector<ETK_SET_TYPE> m_data; //!< Data of the Set ==> the Set table is composed of pointer, this permit to have high speed when resize the vector ...
			sortFunction m_comparator;
		public:
			/**
			 * @brief Set the comparator of the set.
			 * @param[in] _comparator comparing function.
			 */
			void setComparator(sortFunction _comparator) {
				m_comparator = _comparator;
				if (m_comparator != nullptr) {
					m_data.sort(0, m_data.size(), m_comparator);
				}
			}
			/**
			 * @brief Constructor of the Set table.
			 * @param[in] _count Number of basic element (pre-allocated) in the table.
			 */
			Set(int32_t _count = 0) :
			  m_data(_count),
			  m_comparator([](const ETK_SET_TYPE& _key1, const ETK_SET_TYPE& _key2) { return _key1 < _key2; }) {
				// nothing to do
			}
			
			/**
			 * @brief List initializer (ex: etk::Vector<etk::String> plop = {"hello", world"}
			 * @param[in] _element element to add in the vector
			 */
			template<typename... ETK_SET_TYPE_2>
			Set(const ETK_SET_TYPE_2& ... _args):
			  m_data(0),
			  m_comparator([](const ETK_SET_TYPE& _key1, const ETK_SET_TYPE& _key2) { return _key1 < _key2; }) {
				add(_args...);
			}
			
			/**
			 * @brief Destructor of the Set table (clear all element in the table)
			 */
			~Set() {
				clear();
			}
			/**
			 * @brief Remove the first element of the vector
			 */
			void popFront() {
				m_data.popFront();
			}
			/**
			 * @brief Remove the last element of the vector
			 */
			void popBack() {
				m_data.popBack();
			}
			/**
			 * @brief Remove all entry in the Set table.
			 * @note It does not delete pointer if your value is a pointer type...
			 */
			void clear() {
				m_data.clear();
			}
			/**
			 * @brief Check if an element exist or not
			 * @param[in] _key Name of the Set requested
			 * @return true if the element exist
			 */
			bool exist(const ETK_SET_TYPE& _key) const {
				Iterator it = find(_key);
				if (it == end()) {
					return false;
				}
				return true;
			}
			/**
			 * @brief Get Element an a special position
			 * @param[in] _position Position in the Set
			 * @return An reference on the selected element
			 */
			ETK_SET_TYPE& operator[] (size_t _position) {
				return m_data[_position];
			}
			/**
			 * @brief Get Element an a special position
			 * @param[in] _position Position in the Set
			 * @return An reference on the selected element
			 */
			const ETK_SET_TYPE& operator[] (size_t _position) const {
				return m_data[_position];
			}
		private:
			template<typename... ETK_SET_TYPE_2>
			void add(const ETK_SET_TYPE& _value, const ETK_SET_TYPE_2& ... _args) {
				add(_value);
				add(_args...);
			}
		public:
			/**
			 * @brief Add an element OR set an element value
			 * @note add and set is the same function.
			 * @param[in] _key Name of the value to set in the Set table.
			 * @param[in] _value Value to set in the Set table.
			 */
			void add(const ETK_SET_TYPE& _key) {
				if (m_comparator != nullptr) {
					for (size_t iii=0; iii<m_data.size(); ++iii) {
						if (_key == m_data[iii]) {
							return;
						}
						if (m_comparator(_key, m_data[iii]) == true) {
							// Find a position
							m_data.insert(iii, etk::move(_key));
							return;
						}
					}
				}
				m_data.pushBack(etk::move(_key));
			}
			/**
			 * @brief Set an element value
			 * @note add and set is the same function.
			 * @param[in] _key Name of the value to set in the Set table.
			 * @param[in] _value Value to set in the Set table.
			 */
			void set(const ETK_SET_TYPE& _key) {
				add(etk::move(_key));
			}
			/**
			 * @brief Remove an element in the Set table.
			 * @param[in] _key Name of the element to remove.
			 */
			/*
			// TODO: this is dangerous ...
			void erase(const ETK_SET_TYPE& _key) {
				Iterator it = find(_key);
				if (it == end()) {
					return;
				}
				m_data.erase(m_data.begin() + it.getCurrent());
			}
			*/
			/**
			 * @brief Remove an element in the Set table.
			 * @param[in] _it Iterator on the element.
			 */
			Iterator erase(const Iterator& _it) {
				if (_it != end()) {
					m_data.erase(m_data.begin() + _it.getCurrent());
					return position(_it.getCurrent());
				}
				return _it;
			}
			/**
			 * @brief Get the number of element in the Set table
			 * @return number of elements
			 */
			size_t size() const {
				return m_data.size();
			}
			/**
			 * @brief Check if the container have some element
			 * @return true The container is empty
			 * @return famse The container have some element
			 */
			bool empty() const {
				return m_data.size() == 0;
			}
			/**
			 * @brief Swap generic function
			 * @param[in,out] _obj Object to swap data & control...
			 */
			void swap(Set& _obj) {
				etk::swap(m_data, _obj.m_data);
				etk::swap(m_comparator, _obj.m_comparator);
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
			 * @brief Find an element position the the Set table
			 * @param[in] _key Name of the element to find
			 * @return Iterator on the element find or end()
			 */
			const Iterator find(const ETK_SET_TYPE& _key) const {
				// TODO: search in a dichotomic way.
				for (size_t iii=0; iii<m_data.size(); iii++) {
					if (m_data[iii] == _key) {
						return position(iii);
					}
				}
				return end();
			}
			Iterator find(const ETK_SET_TYPE& _key) {
				// TODO: search in a dichotomic way.
				for (size_t iii=0; iii<m_data.size(); iii++) {
					if (m_data[iii] == _key) {
						return position(iii);
					}
				}
				return end();
			}
			
			/**
			 * @brief Count the number of occurence of a specific element.
			 * @param[in] _key Name of the element to count iterence
			 * @return 0 No element was found
			 * @return 1 One element was found
			 */
			size_t count(const ETK_SET_TYPE& _key) const {
				// TODO: search in a dichotomic way.
				for (size_t iii=0; iii<m_data.size(); iii++) {
					if (m_data[iii] == _key) {
						return 1;
					}
				}
				return 0;
			}
	};
}

