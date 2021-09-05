/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL-2 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/debug.hpp>

namespace etk {
	/**
	 * @brief List class ...
	 *
	 * @param[in] T The type of objects to store.
	 *
	 * m_first
	 *    |         o-----------------------o                                           
	 *    *-------->|  Element              |<-----------------------------------+      
	 *              |-----------------------|                                    |      
	 *              | m_previous            |       o-----------------------o    |      
	 *              | m_next                |--+--->|  Element              |    |      
	 *              | m_data                |  |    |-----------------------|    |      
	 *              o-----------------------o  |    | m_previous            |----+      
	 *                                         |    | m_next                |           
	 * m_last ---------------------------------+    | m_data                |           
	 *                                              o-----------------------o           
	 *                                                                                  
	 */
	template<class ETK_LIST_TYPE> class List {
		private:
			class Element {
				List<ETK_LIST_TYPE>::Element* m_previous;
				List<ETK_LIST_TYPE>::Element* m_next;
				ETK_LIST_TYPE m_data;
			};
			List<ETK_LIST_TYPE>::Element* m_first;
			List<ETK_LIST_TYPE>::Element* m_last;
		public:
			const ETK_LIST_TYPE& front() const;
			ETK_LIST_TYPE& front();
			const ETK_LIST_TYPE& back() const;
			ETK_LIST_TYPE& back();
			
			List<ETK_LIST_TYPE>::Iterator begin();
			List<ETK_LIST_TYPE>::Iterator end();
			
			List<ETK_LIST_TYPE>::ReverseIterator rbegin();
			List<ETK_LIST_TYPE>::ReverseIterator rend();
			bool empty() const;
			size_t size() const;
			
			void clear();
			
			void insert(List<ETK_LIST_TYPE>::Iterator _itPrevious, ETK_LIST_TYPE _element);
			List<ETK_LIST_TYPE>::Iterator erase(List<ETK_LIST_TYPE>::Iterator _itRemove);
			
			void pushBack(ETK_LIST_TYPE _element);
			
			void popBack();
			
			void push_front(ETK_LIST_TYPE _element);
			void pop_front();
			void resize(size_t _size);
			void swap(List<ETK_LIST_TYPE>& _other);
			void merge(List<ETK_LIST_TYPE>& _other);
			
			void reverse()
			
			
			bool operator== (const List<ETK_LIST_TYPE>& _other);
			bool operator!= (const List<ETK_LIST_TYPE>& _other);
			bool operator< (const List<ETK_LIST_TYPE>& _other);
			bool operator<= (const List<ETK_LIST_TYPE>& _other);
			bool operator> (const List<ETK_LIST_TYPE>& _other);
			bool operator>= (const List<ETK_LIST_TYPE>& _other);

	};
}
