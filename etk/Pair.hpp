/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL-2 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/move.hpp>

namespace etk {

	template<class ETK_PAIR_TYPE_1, class ETK_PAIR_TYPE_2>
	class Pair {
		public:
			// this is bad for coding rules, but an idiom of c++ pair imposed by the STL
			ETK_PAIR_TYPE_1 first;
			ETK_PAIR_TYPE_2 second;
			Pair():
			  first(),
			  second() {
				
			}
			Pair(ETK_PAIR_TYPE_1&& _obj1, ETK_PAIR_TYPE_2&& _obj2):
			  first(),
			  second() {
				etk::swap(first, _obj1);
				etk::swap(second, _obj2);
			}
			Pair(const ETK_PAIR_TYPE_1& _obj1, const ETK_PAIR_TYPE_2& _obj2):
			  first(_obj1),
			  second(_obj2) {
				
			}
			Pair(const Pair<ETK_PAIR_TYPE_1, ETK_PAIR_TYPE_2>& _obj):
			  first(_obj.first),
			  second(_obj.second) {
				
			}
			Pair(Pair<ETK_PAIR_TYPE_1, ETK_PAIR_TYPE_2>&& _obj):
			  first(),
			  second() {
				_obj.swap(*this);
			}
			template<class ETK_PAIR_UNDER_TYPE_1, class ETK_PAIR_UNDER_TYPE_2>
			Pair(const Pair<ETK_PAIR_UNDER_TYPE_1, ETK_PAIR_UNDER_TYPE_2>& _pair):
			  first(_pair.first),
			  second(_pair.second) {
				
			}
			bool operator== (const Pair<ETK_PAIR_TYPE_1, ETK_PAIR_TYPE_2>& _obj) const{
				return    first == _obj.first
				       && second == _obj.second;
			}
			bool operator!= (const Pair<ETK_PAIR_TYPE_1, ETK_PAIR_TYPE_2>& _obj) const{
				return    first != _obj.first
				       || second != _obj.second;
			}
			void swap(Pair<ETK_PAIR_TYPE_1, ETK_PAIR_TYPE_2>& _obj) {
				etk::swap(first, _obj.first);
				etk::swap(second, _obj.second);
			}
			
			Pair& operator=(const Pair<ETK_PAIR_TYPE_1, ETK_PAIR_TYPE_2>& _obj) {
				Pair<ETK_PAIR_TYPE_1, ETK_PAIR_TYPE_2>(_obj).swap(*this);
				return *this;
			}
			Pair& operator=(Pair<ETK_PAIR_TYPE_1, ETK_PAIR_TYPE_2>&& _obj) {
				Pair<ETK_PAIR_TYPE_1, ETK_PAIR_TYPE_2>(etk::move(_obj)).swap(*this);
				return *this;
			}/*
			template<class ETK_PAIR_UNDER_TYPE_1, class ETK_PAIR_UNDER_TYPE_2>
			Pair& operator=(Pair<ETK_PAIR_UNDER_TYPE_1, ETK_PAIR_UNDER_TYPE_2>&& _obj) {
				Pair<ETK_PAIR_TYPE_1, ETK_PAIR_TYPE_2>(etk::move(_obj)).swap(*this);
				return *this;
			}*/
	};
	template<class ETK_PAIR_TYPE_1, class ETK_PAIR_TYPE_2>
	Pair<ETK_PAIR_TYPE_1, ETK_PAIR_TYPE_2> makePair(ETK_PAIR_TYPE_1 _obj1, ETK_PAIR_TYPE_2 _obj2) {
		return etk::move(etk::Pair<ETK_PAIR_TYPE_1, ETK_PAIR_TYPE_2>(etk::forward<ETK_PAIR_TYPE_1>(_obj1), etk::forward<ETK_PAIR_TYPE_2>(_obj2)));
	}
	template<class ETK_PAIR_TYPE_1, class ETK_PAIR_TYPE_2>
	etk::Stream& operator <<(etk::Stream& _os, const etk::Pair<ETK_PAIR_TYPE_1, ETK_PAIR_TYPE_2>& _obj) {
		_os << "(";
		_os << _obj.first;
		_os << ";";
		_os << _obj.second;
		_os << ")";
		return _os;
	}
};
