

#pragma once
#include <etk/types.hpp>
#include <etk/Vector.hpp>

namespace etk {
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

namespace std {
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const etk::Vector<float>& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const etk::Vector<double>& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const etk::Vector<int64_t>& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const etk::Vector<uint64_t>& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const etk::Vector<int32_t>& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const etk::Vector<uint32_t>& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const etk::Vector<int16_t>& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const etk::Vector<uint16_t>& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const etk::Vector<int8_t>& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const etk::Vector<uint8_t>& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const std::chrono::system_clock::time_point& _obj);
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const std::chrono::steady_clock::time_point& _obj);
}


