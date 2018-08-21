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
		private:
			etk::Vector<ememory::SharedPtr<etk::TreeNode<ETK_TREENODE_TYPE>>> m_data;
		public:
			FlatTree() {
				
			}
			size_t size() const {
				return m_data.size();
			}
			auto begin() const {
				return m_data.begin();
			}
			auto begin() {
				return m_data.begin();
			}
			auto end() const {
				return m_data.end();
			}
			auto end() {
				return m_data.end();
			}
			auto operator[] (size_t _pos) {
				return m_data[_pos];
			}
			auto operator[] (size_t _pos) const {
				return m_data[_pos];
			}
			void setRoot(const ememory::SharedPtr<etk::TreeNode<ETK_TREENODE_TYPE>>& _root) {
				m_data.clear();
				append(_root);
			}
			void setRoot(const ememory::SharedPtr<etk::TreeNode<ETK_TREENODE_TYPE>>& _root,
			             const etk::Function<bool(const ETK_TREENODE_TYPE&)>& _needAdd,
			             const etk::Function<bool(const ETK_TREENODE_TYPE&)>& _needAddChild) {
				m_data.clear();
				append(_root, _needAdd, _needAddChild);
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
			void append(const ememory::SharedPtr<etk::TreeNode<ETK_TREENODE_TYPE>>& _node,
			            const etk::Function<bool(const ETK_TREENODE_TYPE&)>& _needAdd,
			            const etk::Function<bool(const ETK_TREENODE_TYPE&)>& _needAddChild) {
				if (_node == null) {
					return;
				}
				if (_needAdd(_node->getData()) == true) {
					m_data.pushBack(_node);
				}
				if (_needAddChild(_node->getData()) == true) {
					for (auto& it:_node->getChilds()) {
						append(it, _needAdd, _needAddChild);
					}
				}
			}
	};
}
