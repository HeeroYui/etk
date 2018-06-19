/** @file
 * @author Edouard DUPIN
 * @copyright 2017, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

namespace etk {
	class NullPtr {
		public:
			template<class T>
			operator T*() const {
				return 0;
			}
			template<class C, class T>
			operator T C::*() const {
				return 0;
			}
			typedef void* (etk::NullPtr::*bool_)() const;
			template <typename ETK_TYPE_FUNCTION_RETURN, typename... ETK_TYPE_FUNCTION_ARGS>
			ETK_TYPE_FUNCTION_RETURN operator()(ETK_TYPE_FUNCTION_ARGS... _args) {
				throw;
			}
	};
	inline NullPtr getNullPointer() {
		// etk::nullptr exists.
		NullPtr n = { };
		return n;
	}
}
// We does not use nullptr ==> specific STD, can not be overload, and this permit to have a compatibility with STD
#if !defined(null)
	#define null etk::getNullPointer()
#endif

template<class T>
inline bool operator==(T* p, const etk::NullPtr) {
	return p == 0;
}

template<class T>
inline bool operator==(const etk::NullPtr, T* p) {
	return p == 0;
}

template<class T, class U>
inline bool operator==(T U::* p, const etk::NullPtr) {
  return p == 0;
}

template<class T, class U>
inline bool operator==(const etk::NullPtr, T U::* p) {
	return p == 0;
}

inline bool operator==(const etk::NullPtr, const etk::NullPtr) {
	return true;
}

inline bool operator!=(const etk::NullPtr, const etk::NullPtr) {
	return false;
}

inline bool operator<(const etk::NullPtr, const etk::NullPtr) {
	return false;
}

inline bool operator>(const etk::NullPtr, const etk::NullPtr) {
	return false;
}

inline bool operator<=(const etk::NullPtr, const etk::NullPtr) {
	return true;
}

inline bool operator>=(const etk::NullPtr, const etk::NullPtr) {
	return true;
}

