/** @file
 * @author Edouard DUPIN
 * @copyright 2017, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once
//#include <etk/Stream.hpp>

namespace etk {
	inline float cos(float _value) {
		return ::cosf(_value);
	}
	inline float sin(float _value) {
		return ::sinf(_value);
	}
	inline float tan(float _value) {
		return ::tanf(_value);
	}
	inline float acos(float _value) {
		return ::acosf(_value);
	}
	inline float asin(float _value) {
		return ::asinf(_value);
	}
	inline float atan(float _value) {
		return ::atanf(_value);
	}
	inline float atan2(float _value, float _value2) {
		return ::atan2f(_value, _value2);
	}
	inline float sqrt(float _value) {
		return ::sqrtf(_value);
	}
	inline float pow(float _xxx, float _yyy) {
		return ::powf(_xxx, _yyy);
	}
	inline float log(float _value) {
		return ::logf(_value);
	}
	inline float log10(float _value) {
		return ::log10f(_value);
	}
	inline float exp(float _value) {
		return ::expf(_value);
	}
	
	inline double cos(double _value) {
		return ::cos(_value);
	}
	inline double sin(double _value) {
		return ::sin(_value);
	}
	inline double tan(double _value) {
		return ::tan(_value);
	}
	inline double acos(double _value) {
		return ::acos(_value);
	}
	inline double asin(double _value) {
		return ::asin(_value);
	}
	inline double atan(double _value) {
		return ::atan(_value);
	}
	inline double atan2(double _value, double _value2) {
		return ::atan2(_value, _value2);
	}
	inline double sqrt(double _value) {
		return ::sqrt(_value);
	}
	inline double pow(double _xxx, double _yyy) {
		return ::pow(_xxx, _yyy);
	}
	inline double log(double _value) {
		return ::log(_value);
	}
	inline double log10(double _value) {
		return ::log10(_value);
	}
	inline double exp(double _value) {
		return ::exp(_value);
	}
	template <class TYPE> const TYPE& min(const TYPE& _val1, const TYPE& _val2) {
		return (_val1 > _val2) ? _val2 : _val1;
	}
	template <class TYPE> const TYPE& max(const TYPE& _val1, const TYPE& _val2) {
		return (_val1 > _val2) ? _val1 : _val2;
	}
	template <class TYPE> TYPE abs(const TYPE& _value) {
		return (_value >= 0) ? _value : -_value;
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
		ETK_ITERATOR_TYPE tmp2 = _stop;
		while (tmp != tmp2) {
			out++;
			++tmp;
		}
		return out;
	}
	template<class ETK_ITERATOR_TYPE_1, class ETK_ITERATOR_TYPE_2>
	ETK_ITERATOR_TYPE_1 find(ETK_ITERATOR_TYPE_1 _start, ETK_ITERATOR_TYPE_1 _stop, const ETK_ITERATOR_TYPE_2& _value) {
		while (_start != _stop) {
			if (*_start == _value) {
				return _start;
			}
			++_start;
		}
		return _stop;
	}
}