

#include <etk/String.hpp>


template <>
long double etk::String::to<long double>() {
	long double ret = 0;
	sscanf(c_str(), "%Lf", &ret);
	return ret;
}

template <>
double etk::String::to<double>() {
	double ret = 0;
	sscanf(c_str(), "%lf", &ret);
	return ret;
}

template <>
float etk::String::to<float>() {
	float ret = 0;
	sscanf(c_str(), "%f", &ret);
	return ret;
}

template <>
int8_t etk::String::to<int8_t>() {
	int ret = 0;
	sscanf(c_str(), "%d", &ret);
	return ret;
}

template <>
int16_t etk::String::to<int16_t>() {
	int ret = 0;
	sscanf(c_str(), "%d", &ret);
	return ret;
}

template <>
int32_t etk::String::to<int32_t>() {
	int ret = 0;
	sscanf(c_str(), "%d", &ret);
	return ret;
}

template <>
int64_t etk::String::to<int64_t>() {
	int64_t ret = 0;
	#if (    defined(__TARGET_OS__Android) \
	      || defined(__TARGET_OS__Windows) \
	      || defined(__TARGET_OS__MacOs) \
	      || defined(__TARGET_OS__IOs))
		sscanf(c_str(), "%lld", &ret);
	#else
		sscanf(c_str(), "%ld", &ret);
	#endif
	return ret;
}

template <>
uint8_t etk::String::to<uint8_t>() {
	int ret = 0;
	sscanf(c_str(), "%d", &ret);
	return ret;
}

template <>
uint16_t etk::String::to<uint16_t>() {
	int ret = 0;
	sscanf(c_str(), "%d", &ret);
	return ret;
}

template <>
uint32_t etk::String::to<uint32_t>() {
	int ret = 0;
	sscanf(c_str(), "%d", &ret);
	return ret;
}

template <>
uint64_t etk::String::to<uint64_t>() {
	uint64_t ret = 0;
	#if (    defined(__TARGET_OS__Android) \
	      || defined(__TARGET_OS__Windows) \
	      || defined(__TARGET_OS__MacOs) \
	      || defined(__TARGET_OS__IOs))
		sscanf(c_str(), "%llu", &ret);
	#else
		sscanf(c_str(), "%lu", &ret);
	#endif
	return ret;
}


std::ostream& etk::operator <<(std::ostream& _os, const etk::String& _obj) {
	_os << _obj.c_str();
	return _os;
}

std::ostream& etk::operator <<(std::ostream& _os, const etk::Vector<etk::String>& _obj) {
	_os << "{";
	for (size_t iii=0; iii< _obj.size(); iii++) {
		if (iii>0) {
			_os << " ~ ";
		}
		_os << _obj[iii];
	}
	_os << "}";
	return _os;
}


void etk::sort(etk::Vector<etk::String *> &_list) {
	etk::Vector<etk::String *> tmpList(_list);
	_list.clear();
	for(size_t iii=0; iii<tmpList.size(); iii++) {
		size_t findPos = 0;
		for(size_t jjj=0; jjj<_list.size(); jjj++) {
			//TK_DEBUG("compare : \""<<*tmpList[iii] << "\" and \"" << *m_listDirectory[jjj] << "\"");
			if (*tmpList[iii] > *_list[jjj]) {
				findPos = jjj+1;
			}
		}
		//TK_DEBUG("position="<<findPos);
		_list.insert(_list.begin()+findPos, tmpList[iii]);
	}
}



namespace etk {
	template<> bool from_string<etk::String>(etk::String& _variableRet, const etk::String& _value) {
		_variableRet = _value;
		return true;
	}
	template<> bool from_string<int8_t>(int8_t& _variableRet, const etk::String& _value) {
		_variableRet = string_to_int8_t(_value);
		return true;
	}
	template<> bool from_string<int16_t>(int16_t& _variableRet, const etk::String& _value) {
		_variableRet = string_to_int16_t(_value);
		return true;
	}
	template<> bool from_string<int32_t>(int32_t& _variableRet, const etk::String& _value) {
		_variableRet = string_to_int32_t(_value);
		return true;
	}
	template<> bool from_string<int64_t>(int64_t& _variableRet, const etk::String& _value) {
		_variableRet = string_to_int64_t(_value);
		return true;
	}
	template<> bool from_string<uint8_t>(uint8_t& _variableRet, const etk::String& _value) {
		_variableRet = string_to_uint8_t(_value);
		return true;
	}
	template<> bool from_string<uint16_t>(uint16_t& _variableRet, const etk::String& _value) {
		_variableRet = string_to_uint16_t(_value);
		return true;
	}
	template<> bool from_string<uint32_t>(uint32_t& _variableRet, const etk::String& _value) {
		_variableRet = string_to_uint32_t(_value);
		return true;
	}
	template<> bool from_string<uint64_t>(uint64_t& _variableRet, const etk::String& _value) {
		_variableRet = string_to_uint64_t(_value);
		return true;
	}
	template<> bool from_string<float>(float& _variableRet, const etk::String& _value) {
		_variableRet = string_to_float(_value);
		return true;
	}
	template<> bool from_string<double>(double& _variableRet, const etk::String& _value) {
		_variableRet = string_to_double(_value);
		return true;
	}
	template<> bool from_string<long double>(long double& _variableRet, const etk::String& _value) {
		_variableRet = string_to_long_double(_value);
		return true;
	}
	template<> bool from_string<bool>(bool& _variableRet, const etk::String& _value) {
		_variableRet = string_to_bool(_value);
		return true;
	}
}


	etk::String etk::toString(int _val) {
		char tmpVal[256];
		sprintf(tmpVal, "%d", _val);
		return tmpVal;
	}
	etk::String etk::toString(long _val) {
		char tmpVal[256];
		sprintf(tmpVal, "%ld", _val);
		return tmpVal;
	}
	etk::String etk::toString(long long _val) {
		char tmpVal[256];
		sprintf(tmpVal, "%lld", _val);
		return tmpVal;
	}
	etk::String etk::toString(unsigned _val) {
		char tmpVal[256];
		sprintf(tmpVal, "%u", _val);
		return tmpVal;
	}
	etk::String etk::toString(unsigned long _val) {
		char tmpVal[256];
		sprintf(tmpVal, "%lu", _val);
		return tmpVal;
	}
	etk::String etk::toString(unsigned long long _val) {
		char tmpVal[256];
		sprintf(tmpVal, "%llu", _val);
		return tmpVal;
	}
	etk::String etk::toString(float _val) {
		char tmpVal[256];
		sprintf(tmpVal, "%f", _val);
		return tmpVal;
	}
	etk::String etk::toString(double _val) {
		char tmpVal[256];
		sprintf(tmpVal, "%f", _val);
		return tmpVal;
	}
	etk::String etk::toString(long double _val) {
		char tmpVal[256];
		sprintf(tmpVal, "%Lf", _val);
		return tmpVal;
	}