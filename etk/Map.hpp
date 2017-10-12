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
	 * @brief Map table template is a simple classical Map interface.
	 * A Map table is a equivalent of the dictionary in python, this is a
	 * simple interface between a name and a value:
	 *   - "name" : 19
	 *   - "name 2" : 99
	 * 
	 * @note The name is unique and the value is what you want
	 * 
	 * @note The index are all time available since they are created. The order is the the one created
	 * 
	 * A simple example of use:
	 * @code{.cpp}
	 * // Create a integer Map table
	 * Map<int> myValue;
	 * // add some element (note add and set is the same function)
	 * myValue.add("example", 98837);
	 * myValue.add("plop", 88);
	 * // Display an element:
	 * printf("my value is : %d", myValue["example"]);
	 * // Change value of an element:
	 * myValue.set("example", 99);
	 * // Remove an element:
	 * myValue.remove("plop");
	 * //Clean all the table:
	 * myValue.clear();
	 * @endcode
	 */
	template<class ETK_MAP_TYPE_KEY, class ETK_MAP_TYPE_DATA> class Map {
		public:
		class Iterator {
				private:
					size_t m_current; //!< current Id on the vector
					Map<ETK_MAP_TYPE_KEY, ETK_MAP_TYPE_DATA>* m_map; //!< Pointer on the current element of the vectorBin
				public:
					/**
					 * @brief Basic iterator constructor with no link with an etk::Vector
					 */
					Iterator():
					  m_current(0),
					  m_map(nullptr) {
						// nothing to do ...
					}
					/**
					 * @brief Recopy constructor on a specific etkVector.
					 * @param[in] _obj The Iterator that might be copy
					 */
					Iterator(const Iterator & _obj):
					  m_current(_obj.m_current),
					  m_map(_obj.m_map) {
						// nothing to do ...
					}
					/**
					 * @brief Assignation operator.
					 * @param[in] _otherIterator The Iterator that might be copy
					 * @return reference on the current Iterator
					 */
					Iterator& operator=(const Iterator & _obj) {
						m_current = _obj.m_current;
						m_map = _obj.m_map;
						return *this;
					}
					/**
					 * @brief Basic destructor
					 */
					~Iterator() {
						m_current = 0;
						m_map = nullptr;
					}
					/**
					 * @brief basic boolean cast
					 * @return true if the element is present in the etkVector size
					 */
					operator bool () {
						return (m_current < m_map->size());
					}
					/**
					 * @brief Incremental operator
					 * @return Reference on the current iterator increment
					 */
					Iterator& operator++ () {
						if (    m_map != nullptr
						     && m_current < m_map->size() )
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
						if (    m_map != nullptr
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
					etk::Pair<ETK_MAP_TYPE_KEY, ETK_MAP_TYPE_DATA>* operator-> () const {
						//TK_CHECK_INOUT(m_current < m_map->size());
						return &m_map->getContent(m_current);
					}
					/**
					 * @brief Get reference on the current Element
					 * @return the reference on the current Element 
					 */
					etk::Pair<ETK_MAP_TYPE_KEY, ETK_MAP_TYPE_DATA>& operator* () const {
						return m_map->getContent(m_current);
					}
					/**
					 * @brief Get Key on the current Element
					 * @return the Key on the current Element 
					 */
					const ETK_MAP_TYPE_KEY& getKey () const {
						return m_map->getKey(m_current);
					}
					/**
					 * @brief Get Key on the current Element
					 * @return the Key on the current Element 
					 */
					const ETK_MAP_TYPE_DATA& getValue () const {
						return m_map->getValue(m_current);
					}
					/**
					 * @brief Get Key on the current Element
					 * @return the Key on the current Element 
					 */
					ETK_MAP_TYPE_DATA& getValue () {
						return m_map->getValue(m_current);
					}
					bool operator== (const Iterator& _obj) const{
						return    m_map == _obj.m_map
						       && m_current == _obj.m_current;
					}
					bool operator!= (const Iterator& _obj) const {
						return    m_map != _obj.m_map
						       || m_current != _obj.m_current;
					}
				private:
					Iterator(const etk::Map<ETK_MAP_TYPE_KEY, ETK_MAP_TYPE_DATA> * _obj, int32_t _pos):
					  m_current(_pos),
					  m_map(const_cast<etk::Map<ETK_MAP_TYPE_KEY, ETK_MAP_TYPE_DATA> *>(_obj)) {
						// nothing to do ...
					}
					friend class Map;
			};
			static bool defaultSort(etk::Pair<ETK_MAP_TYPE_KEY, ETK_MAP_TYPE_DATA>* const & _key1,
			                        etk::Pair<ETK_MAP_TYPE_KEY, ETK_MAP_TYPE_DATA>* const & _key2) {
				return _key1->first < _key2->first;
			}
		private:
			etk::Vector<etk::Pair<ETK_MAP_TYPE_KEY, ETK_MAP_TYPE_DATA>*> m_data; //!< Data of the Map ==> the Map table is composed of pointer, this permit to have high speed when resize the vector ...
			bool m_ordered;
		public:
			/**
			 * @brief Constructor of the Map table.
			 * @param[in] _count Number of basic element in the table.
			 * @param[in] _ordered select an ordered map or an onordered map.
			 */
			Map(size_t _count = 0, bool _ordered=true) :
			  m_data(),
			  m_ordered(_ordered) {
				m_data.reserve(_count);
				// nothing to do
			}
			/**
			 * @brief Move constructor
			 * @param[in] _obj Other Map to move
			 */
			Map(Map&& _obj):
			  m_data(),
			  m_ordered(true) {
				_obj.swap(*this);
			}
			/**
			 * @brief Copy constructor
			 * @param[in] _obj Other Map to copy
			 */
			Map(const Map& _obj) :
			  m_data(),
			  m_ordered(_obj.m_ordered) {
				m_data.reserve(_obj.m_data.size());
				for (auto &it : _obj.m_data) {
					if (it == nullptr) {
						continue;
					}
					m_data.pushBack(new etk::Pair<ETK_MAP_TYPE_KEY, ETK_MAP_TYPE_DATA>(it->first, it->second));
				}
			}
			void setOrdered(bool _ordered) {
				m_ordered = _ordered;
				if (m_ordered == true) {
					m_data.sort(0, m_data.size(), etk::Map<ETK_MAP_TYPE_KEY, ETK_MAP_TYPE_DATA>::defaultSort);
				}
			}
			/**
			 * @brief Destructor of the Map table (clear all element in the table)
			 */
			~Map() {
				clear();
			}
			/**
			 * @brief Swap two map
			 * @param[in] _obj Other Map to swap with
			 */
			void swap(Map& _obj) {
				etk::swap(m_data, _obj.m_data);
				etk::swap(m_ordered, _obj.m_ordered);
			}
			/**
			 * @brief Move operator
			 * @param[in] _obj Other Map to move
			 */
			Map& operator=(Map&& _obj) {
				_obj.swap(*this);
				return *this;
			}
			/**
			 * @brief Copy operator
			 * @param[in] _obj Other Map to copy
			 */
			Map& operator=(const Map& _obj) {
				Map tmp(_obj);
				tmp.swap(*this);
				return *this;
			}
			/**
			 * @brief Remove all entry in the Map table.
			 * @note It does not delete pointer if your value is a pointer type...
			 */
			void clear() {
				for (auto &it : m_data) {
					if (it != nullptr) {
						delete(it);
						it=nullptr;
					}
				}
				m_data.clear();
			}
			/**
			 * @brief Get a current element ID in the Map table
			 * @param[in] _key Name of the Map requested
			 * @return Id of the element in the table or -1 of it does not existed
			 */
			int64_t getId(const ETK_MAP_TYPE_KEY& _key) const {
				if (m_ordered == true) {
					// TODO: search in a dichotomic way.
				}
				for (size_t iii=0; iii<m_data.size(); iii++) {
					if (m_data[iii] != nullptr) {
						if (m_data[iii]->first == _key) {
							return iii;
						}
					}
				}
				return -1;
			}
			/**
			 * @brief Check if an element exist or not
			 * @param[in] _name Name of the Map requested
			 * @return true if the element exist
			 */
			bool exist(const ETK_MAP_TYPE_KEY& _name) const {
				int64_t elementId = getId(_name);
				if (elementId<0) {
					return false;
				}
				return true;
			}
			/**
			 * @brief Get a current element in the Map table, with his name.
			 * @param[in] _key Name of the Map requested
			 * @return Reference on the Element
			 */
			ETK_MAP_TYPE_DATA& get(const ETK_MAP_TYPE_KEY& _key) const {
				static ETK_MAP_TYPE_DATA g_error;
				int64_t elementId = getId(_key);
				if (elementId<0) {
					//TK_ERROR("try to access at an inexistent Map element : " << _key);
					return g_error;
				}
				return m_data[elementId]->second;
			}
			/**
			 * @brief Get an copy Element an a special position
			 * @param[in] _key Name of the Map requested
			 * @return An reference on the copy of selected element
			 */
			ETK_MAP_TYPE_DATA& operator[] (const ETK_MAP_TYPE_KEY& _key) {
				return get(_key);
			}
			/**
			 * @brief Get an copy Element an a special position
			 * @param[in] _key Name of the Map requested
			 * @return An reference on the copy of selected element
			 */
			const ETK_MAP_TYPE_DATA& operator[] (const ETK_MAP_TYPE_KEY& _key) const {
				return get(_key);
			}
			/**
			 * @brief Add an element OR set an element value
			 * @note add and set is the same function.
			 * @param[in] _key Name of the value to set in the Map table.
			 * @param[in] _value Value to set in the Map table.
			 */
			void add(const ETK_MAP_TYPE_KEY& _key, const ETK_MAP_TYPE_DATA& _value) {
				int64_t elementId = getId(_key);
				if (elementId <0) {
					etk::Pair<ETK_MAP_TYPE_KEY, ETK_MAP_TYPE_DATA>* tmp = new etk::Pair<ETK_MAP_TYPE_KEY, ETK_MAP_TYPE_DATA>(etk::move(_key), etk::move(_value));
					if (tmp == nullptr) {
						return;
					}
					m_data.pushBack(tmp);
					// Order data if needed.
					if (m_ordered == true) {
						m_data.sort(0, m_data.size(), etk::Map<ETK_MAP_TYPE_KEY, ETK_MAP_TYPE_DATA>::defaultSort);
					}
					return;
				}
				m_data[elementId]->second = _value;
			}
			/**
			 * @brief Set an element value
			 * @note add and set is the same function.
			 * @param[in] _key Name of the value to set in the Map table.
			 * @param[in] _value Value to set in the Map table.
			 */
			void set(const ETK_MAP_TYPE_KEY& _key, const ETK_MAP_TYPE_DATA& _value) {
				add(etk::move(_key), etk::move(_value));
			}
			/**
			 * @brief Remove an element in the Map table.
			 * @param[in] _key Name of the element to remove.
			 */
			void erase(const ETK_MAP_TYPE_KEY& _key) {
				int64_t elementId = getId(_key);
				if (elementId <0) {
					//nothing to do ==> not existed
					return;
				}
				delete(m_data[elementId]);
				m_data[elementId] = nullptr;
				m_data.erase(m_data.begin()+elementId);
			}
			/**
			 * @brief Remove an element in the Map table.
			 * @param[in] _it Iterator on the element.
			 */
			Iterator erase(const Iterator& _it) {
				int64_t elementId = _it.m_current;
				delete(m_data[elementId]);
				m_data[elementId] = nullptr;
				m_data.erase(m_data.begin()+elementId);
				return position(elementId);
			}
			/**
			 * @brief Get the number of element in the Map table
			 * @return number of elements
			 */
			size_t size() const {
				return m_data.size();
			}
			const etk::Pair<ETK_MAP_TYPE_KEY, ETK_MAP_TYPE_DATA>& getContent(size_t _pos) const {
				return *m_data[_pos];
			}
			etk::Pair<ETK_MAP_TYPE_KEY, ETK_MAP_TYPE_DATA>& getContent(size_t _pos) {
				return *m_data[_pos];
			}
			/**
			 * @brief Get the name of the element at a specific position.
			 * @param[in] _pos Position of the element in the Map table.
			 * @return name of the element (key).
			 */
			const ETK_MAP_TYPE_KEY& getKey(size_t _pos) const {
				return m_data[_pos]->first;
			}
			/**
			 * @brief Get all the element name (keys).
			 * @return a vector of all name (key).
			 */
			etk::Vector<ETK_MAP_TYPE_KEY> getKeys() const {
				etk::Vector<ETK_MAP_TYPE_KEY> keys;
				for (auto &it : m_data) {
					if (it != nullptr) {
						keys.pushBack(it->first);
					}
				}
				return etk::move(keys);
			}
			/**
			 * @brief Get a value of the Map table at a specific position.
			 * @param[in] _pos of the element in the Map table.
			 * @return Value available at this position.
			 */
			const ETK_MAP_TYPE_DATA& getValue(size_t _pos) const {
				return m_data[_pos]->second;
			}
			/**
			 * @copydoc getValue (size_t)
			 */
			ETK_MAP_TYPE_DATA& getValue(size_t _pos) {
				return m_data[_pos]->second;
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
			
			Iterator find(const ETK_MAP_TYPE_KEY& _key) {
				int64_t elementId = getId(_key);
				if (elementId <0) {
					return end();
				}
				return position(elementId);
			}
			const Iterator find(const ETK_MAP_TYPE_KEY& _key) const {
				int64_t elementId = getId(_key);
				if (elementId <0) {
					return end();
				}
				return position(elementId);
			}
			/**
			 * @brief Count the number of occurence of a specific element.
			 * @param[in] _key Name of the element to count iterence
			 * @return 0 No element was found
			 * @return 1 One element was found
			 */
			size_t count(const ETK_MAP_TYPE_KEY& _key) const {
				// TODO: search in a dichotomic way.
				for (size_t iii=0; iii<m_data.size(); iii++) {
					if (m_data[iii] == nullptr) {
						continue;
					}
					if (m_data[iii]->first == _key) {
						return 1;
					}
				}
				return 0;
			}
			
			
	};
}

