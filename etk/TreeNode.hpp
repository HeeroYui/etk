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
#include <etk/Function.hpp>
#include <ememory/SharedPtr.hpp>
#include <ememory/EnableSharedFromThis.hpp>

namespace etk {
	template<class ETK_TREENODE_TYPE> class TreeNode : public ememory::EnableSharedFromThis<TreeNode<ETK_TREENODE_TYPE>> {
		public:
			TreeNode(ETK_TREENODE_TYPE&& _data):
			  m_data(_data) {
				
			}
			ETK_CONSTRUCTOR_MOVE_DELETE(TreeNode);
			ETK_CONSTRUCTOR_COPY_DELETE(TreeNode);
			static ememory::SharedPtr<TreeNode> create(ETK_TREENODE_TYPE&& _data) {
				return ememory::makeShared<TreeNode>(etk::forward<ETK_TREENODE_TYPE>(_data));
			}
		private:
			ememory::WeakPtr<TreeNode<ETK_TREENODE_TYPE>> m_parent;
		public:
			ememory::SharedPtr<TreeNode<ETK_TREENODE_TYPE>> getParent() const {
				return m_parent.lock();
			}
			void setParent(const ememory::SharedPtr<TreeNode<ETK_TREENODE_TYPE>>& _parent) {
				if (_parent == m_parent.lock()) {
					return;
				}
				if (m_parent != null) {
					ETK_THROW_EXCEPTION(etk::exception::RuntimeError("Set a treeNode parrent on an already used treeNode"));
				}
				m_parent = _parent;
			}
			bool haveParent() const {
				if (getParent() == null) {
					return false;
				}
				return true;
			}
		public:
			using Childs = etk::Vector<ememory::SharedPtr<TreeNode>>;
		private:
			Childs m_childs; //!< List of child in this node
		public:
			/**
			 * @brief Get child list.
			 * @return The child inteface.
			 */
			const Childs& getChilds() const {
				return m_childs;
			}
			Childs& getChilds() {
				return m_childs;
			}
			void addChild(ememory::SharedPtr<TreeNode> _child) {
				if (_child == null) {
					return;
				}
				for (auto& it: m_childs) {
					if (it == _child) {
						return;
					}
				}
				_child->setParent(ememory::EnableSharedFromThis<TreeNode<ETK_TREENODE_TYPE>>::sharedFromThis());
				m_childs.pushBack(_child);
			}
			void rmChild(ememory::SharedPtr<TreeNode> _child) {
				if (_child == null) {
					return;
				}
				auto it = m_childs.begin();
				while (it != m_childs.end()) {
					if (*it == _child) {
						it->setParent(null);
						m_childs.erase(it);
						return;
					}
					++it;
				}
				ETK_THROW_EXCEPTION(etk::exception::RuntimeError("Remove treeNode child that does not exist"));
			}
			void clear() {
				for (auto& it: m_childs) {
					it.setParent(null);
				}
				m_childs.clear();
			}
			bool haveChild() const {
				return m_childs.size() != 0;
			}
			size_t countChild() const {
				return m_childs.size();
			}
		private:
			ETK_TREENODE_TYPE m_data;
		public:
			const ETK_TREENODE_TYPE& getData() const {
				return m_data;
			}
			ETK_TREENODE_TYPE& getData() {
				return m_data;
			}
		public:
			using ConditionFunction = etk::Function<bool(const TreeNode&)>;
			etk::Vector<ememory::SharedPtr<TreeNode>> findIf(const ConditionFunction& findCondition) const {
				etk::Vector<ememory::SharedPtr<TreeNode>> out;
				if (findCondition(*this) == true) {
					out.pushBack(ememory::EnableSharedFromThis<TreeNode<ETK_TREENODE_TYPE>>::sharedFromThis());
				}
				for (auto& it: m_childs) {
					auto ret = it->findIf(findCondition);
					for (auto& element: ret) {
						out.pushBack(element);
					}
				}
				return out;
			}
			size_t countToRoot() {
				auto parent = m_parent.lock();
				if (parent == null) {
					return 0;
				}
				return parent->countToRoot() + 1;
			}
	};
}

