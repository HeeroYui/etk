/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL-2 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/Stream.hpp>
#include <etk/Allocator.hpp>

namespace etk {
	namespace algorithm {
		namespace detail {
			template<class ETK_VECTOR_TYPE>
			int64_t quickSortPartition (etk::Vector<ETK_VECTOR_TYPE>& _data,
			                          int64_t _low,
			                          int64_t _high,
			                          bool (*_comparator)(const ETK_VECTOR_TYPE&, const ETK_VECTOR_TYPE&)) {
				int64_t iii = (_low - 1);
				for (int64_t jjj = _low; jjj < _high; ++jjj) {
					if (_comparator(_data[jjj], _data[_high]) == true) {
						iii++;
						etk::swap(_data[iii], _data[jjj]);
					}
				}
				etk::swap(_data[iii + 1], _data[_high]);
				return (iii + 1);
			}
			template<class ETK_VECTOR_TYPE>
			void quickSort(etk::Vector<ETK_VECTOR_TYPE>& _data,
			               int64_t _low,
			               int64_t _high,
			               bool (*_comparator)(const ETK_VECTOR_TYPE&, const ETK_VECTOR_TYPE&)) {
				if (_low >= _high) {
					return;
				}
				// pi is partitioning index, arr[p] is now at right place
				int64_t pi = detail::quickSortPartition(_data, _low, _high, _comparator);
				// Separately sort elements before partition and after partition
				//if (pi != 0) {
					detail::quickSort(_data, _low, pi - 1, _comparator);
				//}
				detail::quickSort(_data, pi + 1, _high, _comparator);
			}
		}
		/**
		 * @brief: QuickSort implementation of sorting vector.
		 * @param[in,out] _data Vector to sort.
		 * @param[in] _low Lowest element to sort.
		 * @param[in] _high Highest element to sort.
		 * @param[in] _high Comparator function of this element.
		 */
		template<class ETK_VECTOR_TYPE>
		void quickSort(etk::Vector<ETK_VECTOR_TYPE>& _data,
		               size_t _low,
		               size_t _high,
		               bool (*_comparator)(ETK_VECTOR_TYPE const &, ETK_VECTOR_TYPE const &)) {
			if (_high >= _data.size()) {
				_high = _data.size()-1;
			}
			/*if (_low >= _data.size()) {
				_low = _data.size()-1;
			}*/
			detail::quickSort(_data, _low, _high, _comparator);
		}
		/**
		 * @brief: QuickSort implementation of sorting vector (all elements.
		 * @param[in,out] _data Vector to sort.
		 * @param[in] _high Comparator function of this element.
		 */
		template<class ETK_VECTOR_TYPE>
		void quickSort(etk::Vector<ETK_VECTOR_TYPE>& _data,
		               bool (*_comparator)(ETK_VECTOR_TYPE const &, ETK_VECTOR_TYPE const &)) {
			detail::quickSort(_data, 0, _data.size()-1, _comparator);
		}
	}
}

