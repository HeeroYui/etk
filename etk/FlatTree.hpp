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
#include <etk/TreeNode.hpp>

namespace etk {
	template<class ETK_TREENODE_TYPE> class FlatTree {
		public:
			# if 0
			//static const size_t npos = size_t(-1);
			class Iterator {
				private:
					size_t m_current; //!< current Id on the vector
					FlatTree<ETK_TREENODE_TYPE>* m_tree; //!< Pointer on the current element of the vectorBin
				public:
					/**
					 * @brief Basic iterator constructor with no link with an etk::Vector
					 */
					Iterator():
					  m_current(0),
					  m_tree(null) {
						// nothing to do ...
					}
					/**
					 * @brief Recopy constructor on a specific etkVector.
					 * @param[in] _obj The Iterator that might be copy
					 */
					Iterator(const Iterator & _obj):
					  m_current(_obj.m_current),
					  m_tree(_obj.m_tree) {
						// nothing to do ...
					}
					/**
					 * @brief Assignation operator.
					 * @param[in] _otherIterator The Iterator that might be copy
					 * @return reference on the current Iterator
					 */
					Iterator& operator=(const Iterator & _otherIterator) {
						m_current = _otherIterator.m_current;
						m_tree = _otherIterator.m_tree;
						return *this;
					}
					/**
					 * @brief Basic destructor
					 */
					~Iterator() {
						m_current = 0;
						m_tree = null;
					}
					/**
					 * @brief basic boolean cast
					 * @return true if the element is present in the etkVector size
					 */
					operator bool () {
						return (m_current < m_tree->size());
					}
					/**
					 * @brief != Comparaison operator
					 * @param[in] _obj Object to compare
					 * @return true if the element are different
					 */
					bool operator!= (const Iterator& _obj) {
						if (    m_tree != _obj.m_tree
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
						if (    m_tree == _obj.m_tree
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
						if (    m_tree != null
						     && m_current < m_tree->size() )
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
						if (    m_tree != null
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
					ETK_TREENODE_TYPE* operator-> () const {
						return &m_tree->get(m_current);
					}
					/**
					 * @brief Get reference on the current Element
					 * @return the reference on the current Element 
					 */
					ETK_TREENODE_TYPE& operator* () const {
						return m_tree->get(m_current);
					}
				private:
					Iterator(const FlatTree<ETK_TREENODE_TYPE> * _obj, int32_t _pos):
					  m_current(_pos),
					  m_tree(const_cast<FlatTree<ETK_TREENODE_TYPE> *>(_obj)) {
						// nothing to do ...
					}
					size_t getCurrent() const {
						return m_current;
					}
					friend class FlatTree;
			};
			#endif
		private:
			etk::Vector<const ememory::SharedPtr<etk::TreeNode<ETK_TREENODE_TYPE>>> m_data;
		public:
			FlatTree() {
				
			}
			void setRoot(const ememory::SharedPtr<etk::TreeNode<ETK_TREENODE_TYPE>>& _root) {
				m_data.clear();
				append(_root);
			}
		private:
			void append(const ememory::SharedPtr<etk::TreeNode<ETK_TREENODE_TYPE>>& _node) {
				if (_node == null) {
					return;
				}
				m_data.pushBack(_node);
				for (auto& it:_node->getChilds()) {
					append(it);
				}
			}
	};
}
