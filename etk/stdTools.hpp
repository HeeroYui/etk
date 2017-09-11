/** @file
 * @author Edouard DUPIN
 * @copyright 2017, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

namespace etk {
	template <class TYPE> const TYPE& min(const TYPE& _val1, const TYPE& _val2) {
		return (_val1 > _val2) ? _val2 : _val1;
	}
	template <class TYPE> const TYPE& max(const TYPE& _val1, const TYPE& _val2) {
		return (_val1 > _val2) ? _val1 : _val2;
	}
	/**
	 * @brief in std, we have min, max but not avg ==> it is missing... the Define of avg template.
	 * @param[in] _min Minimum value of the range
	 * @param[in] _val The value that we want a min/max
	 * @param[in] _max Maximum value of the range
	 * @return Value that min/max applied
	 */
	template <class TYPE> const TYPE& avg(const TYPE& _min, const TYPE& _val, const TYPE& _max) {
		return etk::min(etk::max(_min,_val),_max);
	}
	template<class ETK_ITERATOR_TYPE>
	size_t distance(const ETK_ITERATOR_TYPE& _start, const ETK_ITERATOR_TYPE& _stop) {
		size_t out = 0;
		ETK_ITERATOR_TYPE tmp = _start;
		while (tmp != _stop) {
			out++;
			++tmp;
		}
		return out;
	}
}