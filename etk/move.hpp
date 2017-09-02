/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL-2 (see license file)
 */
#pragma once


namespace etk {
	template<class ETK_MOVE_TYPE>
	struct RemoveReference {
		// remove reference
		typedef ETK_MOVE_TYPE m_type;
	};
	template<class ETK_MOVE_TYPE>
	struct RemoveReference<ETK_MOVE_TYPE&> {
		// remove reference
		typedef ETK_MOVE_TYPE m_type;
	};
	template<class ETK_MOVE_TYPE>
	struct RemoveReference<ETK_MOVE_TYPE&&> {
		// remove rvalue reference
		typedef ETK_MOVE_TYPE m_type;
	};
	
	template<class ETK_MOVE_TYPE> inline
	typename etk::RemoveReference<ETK_MOVE_TYPE>::m_type&& move(ETK_MOVE_TYPE&& _obj) {
		// forward _Arg as movable
		return ((typename etk::RemoveReference<ETK_MOVE_TYPE>::m_type&&)_obj);
	}
	template<typename ETK_SWAP_TYPE>
	inline void swap(ETK_SWAP_TYPE& _obj1, ETK_SWAP_TYPE& _obj2) {
		ETK_SWAP_TYPE tmp = etk::move(_obj1);
		_obj1 = etk::move(_obj2);
		_obj2 = etk::move(tmp);
	}
	
	template<class ETK_TYPE, ETK_TYPE v>
	struct integralConstant {
		static constexpr ETK_TYPE value = v;
		typedef ETK_TYPE typeValue;
		// using injected-class-name
		typedef integralConstant type;
		constexpr operator typeValue() const noexcept {
			return value;
		}
		constexpr typeValue operator()() const noexcept {
			return value;
		}
	};
	
	typedef	etk::integralConstant<bool, true> typeTrue;
	typedef	etk::integralConstant<bool, false> typeFalse;
	
	template<class ETK_TYPE>
	struct isLeftValueReference : etk::typeFalse {};
	template<class ETK_TYPE>
	struct isLeftValueReference<ETK_TYPE&> : etk::typeTrue {};
	
	template <class ETK_FORWARD_TYPE>
	inline ETK_FORWARD_TYPE&& forward(typename etk::RemoveReference<ETK_FORWARD_TYPE>::m_type& _obj) noexcept {
		return static_cast<ETK_FORWARD_TYPE&&>(_obj);
	}
	template <class ETK_FORWARD_TYPE>
	inline ETK_FORWARD_TYPE&& forward(typename etk::RemoveReference<ETK_FORWARD_TYPE>::m_type&& _obj) noexcept {
		static_assert(!etk::isLeftValueReference<ETK_FORWARD_TYPE>::type, "Can not forward an rvalue as an lvalue.");
		return static_cast<ETK_FORWARD_TYPE&&>(_obj);
	}
}
