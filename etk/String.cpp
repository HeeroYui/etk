

#include <etk/String.hpp>


template <>
long double etk::String::to<long double>() const {
	long double ret = 0;
	sscanf(c_str(), "%Lf", &ret);
	return ret;
}

template <>
double etk::String::to<double>() const {
	double ret = 0;
	sscanf(c_str(), "%lf", &ret);
	return ret;
}

template <>
float etk::String::to<float>() const {
	float ret = 0;
	sscanf(c_str(), "%f", &ret);
	return ret;
}

template <>
int8_t etk::String::to<int8_t>() const {
	int ret = 0;
	sscanf(c_str(), "%d", &ret);
	return ret;
}

template <>
int16_t etk::String::to<int16_t>() const {
	int ret = 0;
	sscanf(c_str(), "%d", &ret);
	return ret;
}

template <>
int32_t etk::String::to<int32_t>() const {
	int ret = 0;
	sscanf(c_str(), "%d", &ret);
	return ret;
}

template <>
int64_t etk::String::to<int64_t>() const {
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
uint8_t etk::String::to<uint8_t>() const {
	int ret = 0;
	sscanf(c_str(), "%d", &ret);
	return ret;
}

template <>
uint16_t etk::String::to<uint16_t>() const {
	int ret = 0;
	sscanf(c_str(), "%d", &ret);
	return ret;
}

template <>
uint32_t etk::String::to<uint32_t>() const {
	int ret = 0;
	sscanf(c_str(), "%d", &ret);
	return ret;
}

template <>
uint64_t etk::String::to<uint64_t>() const {
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
		_variableRet = _value.to<int8_t>();
		return true;
	}
	template<> bool from_string<int16_t>(int16_t& _variableRet, const etk::String& _value) {
		_variableRet = _value.to<int16_t>();
		return true;
	}
	template<> bool from_string<int32_t>(int32_t& _variableRet, const etk::String& _value) {
		_variableRet = _value.to<int32_t>();
		return true;
	}
	template<> bool from_string<int64_t>(int64_t& _variableRet, const etk::String& _value) {
		_variableRet = _value.to<int64_t>();
		return true;
	}
	template<> bool from_string<uint8_t>(uint8_t& _variableRet, const etk::String& _value) {
		_variableRet = _value.to<uint8_t>();
		return true;
	}
	template<> bool from_string<uint16_t>(uint16_t& _variableRet, const etk::String& _value) {
		_variableRet = _value.to<uint16_t>();
		return true;
	}
	template<> bool from_string<uint32_t>(uint32_t& _variableRet, const etk::String& _value) {
		_variableRet = _value.to<uint32_t>();
		return true;
	}
	template<> bool from_string<uint64_t>(uint64_t& _variableRet, const etk::String& _value) {
		_variableRet = _value.to<uint64_t>();
		return true;
	}
	template<> bool from_string<float>(float& _variableRet, const etk::String& _value) {
		_variableRet = _value.to<float>();
		return true;
	}
	template<> bool from_string<double>(double& _variableRet, const etk::String& _value) {
		_variableRet = _value.to<double>();
		return true;
	}
	template<> bool from_string<long double>(long double& _variableRet, const etk::String& _value) {
		_variableRet = _value.to<long double>();
		return true;
	}
	template<> bool from_string<bool>(bool& _variableRet, const etk::String& _value) {
		_variableRet = _value.to<bool>();
		return true;
	}
}

template<>
etk::String etk::toString(const bool& _val) {
	if (_val == true) {
		return "true";
	}
	return "false";
}
template<>
etk::String etk::toString(const int& _val) {
	char tmpVal[256];
	sprintf(tmpVal, "%d", _val);
	return tmpVal;
}
template<>
etk::String etk::toString(const long& _val) {
	char tmpVal[256];
	sprintf(tmpVal, "%ld", _val);
	return tmpVal;
}
template<>
etk::String etk::toString(const long long& _val) {
	char tmpVal[256];
	sprintf(tmpVal, "%lld", _val);
	return tmpVal;
}
template<>
etk::String etk::toString(const unsigned& _val) {
	char tmpVal[256];
	sprintf(tmpVal, "%u", _val);
	return tmpVal;
}
template<>
etk::String etk::toString(const unsigned long& _val) {
	char tmpVal[256];
	sprintf(tmpVal, "%lu", _val);
	return tmpVal;
}
template<>
etk::String etk::toString(const unsigned long long& _val) {
	char tmpVal[256];
	sprintf(tmpVal, "%llu", _val);
	return tmpVal;
}
template<>
etk::String etk::toString(const float& _val) {
	char tmpVal[256];
	sprintf(tmpVal, "%f", _val);
	return tmpVal;
}
template<>
etk::String etk::toString(const double& _val) {
	char tmpVal[256];
	sprintf(tmpVal, "%f", _val);
	return tmpVal;
}
template<>
etk::String etk::toString(const long double& _val) {
	char tmpVal[256];
	sprintf(tmpVal, "%Lf", _val);
	return tmpVal;
}

size_t etk::String::find(char _value, size_t _pos) const {
	for (size_t iii=_pos; iii<m_data.size(); ++iii) {
		if (_value == m_data[iii]) {
			return iii;
		}
	}
	return etk::String::npos;
}

size_t etk::String::find(const etk::String& _value, size_t _pos) const {
	for (size_t iii=_pos; iii<m_data.size(); ++iii) {
		bool check = true;
		for (size_t jjj=0; jjj<_value.size(); ++jjj) {
			if (iii+jjj >= m_data.size()) {
				return etk::String::npos;
			}
			if (_value[jjj] != m_data[iii+jjj]) {
				check = false;
				break;
			}
		}
		if (check == true) {
			return iii;
		}
	}
	return etk::String::npos;
}

size_t etk::String::rfind(char _value, size_t _pos) const {
	if (_pos >= m_data.size()) {
		_pos = m_data.size()-1;
	}
	for (int64_t iii=_pos; iii>=0; --iii) {
		if (_value == m_data[iii]) {
			return iii;
		}
	}
	return etk::String::npos;
}

size_t etk::String::rfind(const etk::String& _value, size_t _pos) const {
	if (_pos >= m_data.size()) {
		_pos = m_data.size()-1;
	}
	for (int64_t iii=_pos; iii>=0; --iii) {
		bool check = true;
		for (size_t jjj=0; jjj<_value.size(); ++jjj) {
			if (iii+jjj >= m_data.size()) {
				check = false;
				break;
			}
			if (_value[jjj] != m_data[iii+jjj]) {
				check = false;
				break;
			}
		}
		if (check == true) {
			return iii;
		}
	}
	return etk::String::npos;
}

etk::String& etk::String::replace(size_t _pos, size_t _len, char _replace) {
	erase(_pos, _len);
	insert(_pos, _replace);
	return *this;
}

etk::String& etk::String::replace(size_t _pos, size_t _len, const etk::String& _replace) {
	erase(_pos, _len);
	insert(_pos, _replace);
	return *this;
}

etk::String& etk::String::replace(char _val, char _replace) {
	size_t pos = 0;
	while ((pos = find(_val, pos)) != etk::String::npos) {
		replace(pos, 1, _replace);
		pos += 1;
	}
	return *this;
}

etk::String& etk::String::replace(const etk::String& _val, const etk::String& _replace) {
	size_t pos = 0;
	while ((pos = find(_val, pos)) != etk::String::npos) {
		replace(pos, _val.size(), _replace);
		pos += _replace.size();
	}
	return *this;
}

etk::String etk::String::getLine(int32_t _pos) const {
	// search back : '\n'
	size_t startPos = rfind('\n', _pos);
	if ((int64_t)startPos == (int64_t)_pos) {
		startPos = 0;
	} else {
		startPos++;
	}
	// search forward : '\n'
	size_t stopPos = _pos;
	if (m_data[_pos] != '\n') {
		stopPos = find('\n', _pos);
		if ((int64_t)stopPos == _pos) {
			stopPos = size();
		}
	}
	if (startPos == etk::String::npos) {
		startPos = 0;
	} else if (startPos >= size() ) {
		return "";
	}
	if (stopPos == etk::String::npos) {
		return "";
	} else if (stopPos >= size() ) {
		stopPos = size();
	}
	return etk::String(*this, startPos, stopPos - startPos);
}


etk::Vector<etk::String> etk::String::split(char _val) const {
	etk::Vector<etk::String> list;
	size_t lastStartPos = 0;
	for(size_t iii=0; iii<size(); iii++) {
		if (m_data[iii] == _val) {
			list.pushBack(etk::String(*this, lastStartPos, iii - lastStartPos));
			lastStartPos = iii+1;
		}
	}
	if (lastStartPos < size()) {
		list.pushBack(etk::String(*this, lastStartPos));
	}
	return list;
}

etk::Vector<etk::String> etk::String::split(etk::String _val) const {
	etk::Vector<etk::String> list;
	size_t lastStartPos = 0;
	for(size_t iii=0; iii<size()-_val.size(); iii++) {
		if (etk::String(begin()+iii, begin()+iii+_val.size()) ==_val) {
			list.pushBack(etk::String(*this, lastStartPos, iii - lastStartPos));
			lastStartPos = iii+_val.size();
			iii += _val.size()-1;
		}
	}
	if (lastStartPos < size()) {
		list.pushBack(etk::String(*this, lastStartPos));
	}
	return list;
}

