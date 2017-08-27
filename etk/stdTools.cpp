
#include <etk/stdTools.hpp>

namespace std {
	etk::Stream& operator <<(etk::Stream& _os, const std::chrono::system_clock::time_point& _obj) {
		std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(_obj.time_since_epoch());
		int64_t totalSecond = ns.count()/1000000000;
		int64_t millisecond = (ns.count()%1000000000)/1000000;
		int64_t microsecond = (ns.count()%1000000)/1000;
		int64_t nanosecond = ns.count()%1000;
		//_os << totalSecond << "s " << millisecond << "ms " << microsecond << "µs " << nanosecond << "ns";
		int32_t second = totalSecond % 60;
		int32_t minute = (totalSecond/60)%60;
		int32_t hour = (totalSecond/3600)%24;
		int32_t day = (totalSecond/(24*3600))%365;
		int32_t year = totalSecond/(24*3600*365);
		_os << year << "y " << day << "d " << hour << "h" << minute << ":"<< second << "s " << millisecond << "ms " << microsecond << "Âµs " << nanosecond << "ns";
		return _os;
	}
	etk::Stream& operator <<(etk::Stream& _os, const std::chrono::steady_clock::time_point& _obj) {
		std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(_obj.time_since_epoch());
		int64_t totalSecond = ns.count()/1000000000;
		int64_t millisecond = (ns.count()%1000000000)/1000000;
		int64_t microsecond = (ns.count()%1000000)/1000;
		int64_t nanosecond = ns.count()%1000;
		//_os << totalSecond << "s " << millisecond << "ms " << microsecond << "µs " << nanosecond << "ns";
		int32_t second = totalSecond % 60;
		int32_t minute = (totalSecond/60)%60;
		int32_t hour = (totalSecond/3600)%24;
		int32_t day = (totalSecond/(24*3600))%365;
		int32_t year = totalSecond/(24*3600*365);
		_os << year << "y " << day << "d " << hour << "h" << minute << ":"<< second << "s " << millisecond << "ms " << microsecond << "µs " << nanosecond << "ns";
		return _os;
	}
}