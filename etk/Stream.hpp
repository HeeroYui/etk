/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL-2 (see license file)
 */
#pragma once

#include <etk/types.hpp>

namespace etk {
	class String;
	/**
	 * @brief string class ...
	 */
	class Stream {
		private:
			// remove dependency of std::string and vector
			etk::String* m_data;
		public:
			Stream(size_t _basicSize=0);
			~Stream();
			Stream& operator<< (const char* _data);
			Stream& operator<< (bool _data);
			Stream& operator<< (int8_t _data);
			Stream& operator<< (int16_t _data);
			Stream& operator<< (int32_t _data);
			Stream& operator<< (int64_t _data);
			Stream& operator<< (uint8_t _data);
			Stream& operator<< (uint16_t _data);
			Stream& operator<< (uint32_t _data);
			Stream& operator<< (uint64_t _data);
			Stream& operator<< (float _data);
			Stream& operator<< (double _data);
			const char* c_str() const;
			const size_t size() const;
	};
	// TODO: This is not a good place ...
	/*
	//! @not_in_doc
	template<class ETK_VECTOR_TYPE>
	etk::Stream& operator <<(etk::Stream& _os, const etk::Vector<ETK_VECTOR_TYPE>& _obj) {
		_os << "{";
		for (size_t iii=0; iii< _obj.size(); iii++) {
			if (iii>0) {
				_os << ";";
			}
			_os << _obj[iii];
		}
		_os << "}";
		return _os;
	}
	*/
}

