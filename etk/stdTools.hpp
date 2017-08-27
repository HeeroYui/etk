

#pragma once
#include <etk/types.hpp>
#include <etk/Stream.hpp>
#include <chrono>

namespace etk {
	etk::Stream& operator <<(etk::Stream& _os, const std::chrono::system_clock::time_point& _obj);
	//! @not_in_doc
	etk::Stream& operator <<(etk::Stream& _os, const std::chrono::steady_clock::time_point& _obj);
}