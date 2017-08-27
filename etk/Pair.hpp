/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL-2 (see license file)
 */
#pragma once

#include <etk/types.hpp>

namespace etk {

	template<class ETK_PAIR_TYPE_1, class ETK_PAIR_TYPE_2>
	class Pair {
		public:
			ETK_PAIR_TYPE_1 first;
			ETK_PAIR_TYPE_1 second;
			Pair():
			  first(),
			  second() {
				
			}
			Pair(const ETK_PAIR_TYPE_1& _obj1, const ETK_PAIR_TYPE_2& _obj2):
			  first(_obj1),
			  second(_obj2) {
				
			}
			template<class ETK_PAIR_UNDER_TYPE_1, class ETK_PAIR_UNDER_TYPE_2>
			Pair(const Pair<ETK_PAIR_UNDER_TYPE_1, ETK_PAIR_UNDER_TYPE_2>& _pair):
			  first(_pair.first),
			  second(_pair.second) {
				
			}
	};
	template<class ETK_PAIR_TYPE_1, class ETK_PAIR_TYPE_2>
	Pair<ETK_PAIR_TYPE_1, ETK_PAIR_TYPE_2> makePair(ETK_PAIR_TYPE_1 _obj1, ETK_PAIR_TYPE_2 _obj2) {
		return etk::Pair<ETK_PAIR_TYPE_1, ETK_PAIR_TYPE_2>(_obj1, _obj2);
	}
};
