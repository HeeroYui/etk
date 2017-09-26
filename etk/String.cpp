

#include <etk/String.hpp>
#include <etk/UString.hpp>

etk::String::String():
  m_data() {
	m_data.resize(1, '\0');
}

etk::String::String(const etk::String& _obj) {
	m_data = _obj.m_data;
}

etk::String::String(const etk::String& _obj, size_t _pos, size_t _size) {
	if (_pos + _size >= _obj.size()) {
		_size = etk::String::npos;
	}
	if (_size != etk::String::npos) {
		resize(_size);
		for (size_t iii=0; iii<_size; ++iii) {
			m_data[iii] = _obj.m_data[_pos+iii];
		}
		return;
	}
	resize(_obj.size()-_pos);
	for (size_t iii=0; iii<_obj.size()-_pos; ++iii) {
		m_data[iii] = _obj.m_data[_pos+iii];
	}
}

etk::String::String(const char* _obj) {
	if (_obj == nullptr) {
		resize(0);
		return;
	}
	uint32_t size = strlen(_obj);
	resize(size);
	for (size_t iii=0; iii<size; ++iii) {
		m_data[iii] = _obj[iii];
	}
}
/*
etk::String::String(const etk::String _obj) {
	resize(_obj.size());
	for (size_t iii=0; iii<_obj.size(); ++iii) {
		m_data[iii] = _obj[iii];
	}
}
*/

etk::String::String(const char* _obj, size_t _size) {
	if (    _obj == nullptr
	     || _size == 0) {
		resize(0);
		return;
	}
	uint32_t size = strlen(_obj);
	if (_size < size) {
		size = _size;
	}
	resize(size);
	for (size_t iii=0; iii<size; ++iii) {
		m_data[iii] = _obj[iii];
	}
}

etk::String::String(size_t _size, char _val) {
	resize(_size);
	for (size_t iii=0; iii<_size; ++iii) {
		m_data[iii] = _val;
	}
}

etk::String::String(Iterator _start, Iterator _stop) {
	size_t size = etk::distance(_start, _stop);
	resize(size);
	Iterator it = begin();
	while (_start != _stop) {
		*it++ = *_start++;
	}
}

etk::String::String(etk::String&& _obj) noexcept {
	resize(0);
	m_data.swap(_obj.m_data);
}

etk::String::String(char _value) {
	resize(1);
	m_data[0] = _value;
}

etk::String::~String() {
	// nothing to do...
}

void etk::String::swap(etk::String& _obj) {
	// avoid Swap of itself
	if(this != &_obj) {
		m_data.swap(_obj.m_data);
	}
}

etk::String& etk::String::operator=(const etk::String& _obj) {
	if (this != &_obj) {
		m_data = _obj.m_data;
	}
	// Return the current pointer
	return *this;
}

etk::String& etk::String::operator=(const char* _obj) {
	clear();
	if (_obj == nullptr) {
		return *this;
	}
	size_t numberElement = strlen(_obj);
	resize(numberElement);
	for (size_t iii=0; iii<numberElement; ++iii) {
		m_data[iii] = _obj[iii];
	}
	// Return the current pointer
	return *this;
}

etk::String& etk::String::operator=(char _value) {
	resize(1);
	m_data[0] = _value;
	// Return the current pointer
	return *this;
}

etk::String& etk::String::operator+= (const etk::String& _obj) {
	size_t numberElement = _obj.size();
	size_t idElement = size();
	resize(size()+_obj.size());
	for (size_t iii=0; iii<_obj.size(); ++iii) {
		m_data[idElement+iii] = _obj[iii];
	}
	// Return the current pointer
	return *this;
}

etk::String& etk::String::operator+= (const char* _obj) {
	if (_obj == nullptr) {
		return *this;
	}
	size_t numberElement = strlen(_obj);
	size_t idElement = size();
	resize(size() + numberElement);
	for (size_t iii=0; iii<numberElement; ++iii) {
		m_data[idElement+iii] = _obj[iii];
	}
	// Return the current pointer
	return *this;
}

etk::String& etk::String::operator+= (char _value) {
	pushBack(_value);
	// Return the current pointer
	return *this;
}
size_t etk::String::size() const {
	return m_data.size() - 1; // remove '\0'
}

void etk::String::pushFront(char _item) {
	insert(0, &_item, 1);
}

void etk::String::pushFront(const char * _item, size_t _nbElement) {
	insert(0, _item, _nbElement);
}

void etk::String::pushBack(const char _item) {
	size_t idElement = size();
	resize(size()+1);
	if (idElement < size()) {
		m_data[idElement] = _item;
	} else {
		//TK_ERROR("Resize does not work correctly ... not added item");
	}
}

void etk::String::pushBack(const char* _item, size_t _nbElement) {
	if (_item == nullptr) {
		return;
	}
	size_t idElement = size();
	resize(size()+_nbElement);
	if (idElement > size()) {
		//TK_ERROR("Resize does not work correctly ... not added item");
		return;
	}
	for (size_t iii=0; iii<_nbElement; iii++) {
		m_data[idElement+iii] = _item[iii];
	}
}

void etk::String::popBack() {
	if(size()>0) {
		resize(size()-1);
	}
}

void etk::String::reserve(size_t _size) {
	m_data.reserve(_size+1);
}

void etk::String::clear() {
	resize(0);
}

void etk::String::insert(size_t _pos, const char* _item, size_t _nbElement) {
	if (_pos>size()) {
		//TK_WARNING(" can not insert Element at this position : " << _pos << " > " << size() << " add it at the end ... ");
		pushBack(_item, _nbElement);
		return;
	}
	size_t idElement = size();
	// Request resize of the current buffer
	resize(size()+_nbElement);
	if (idElement>=size()) {
		//TK_ERROR("Resize does not work correctly ... not added item");
		return;
	}
	// move current data (after the position)
	size_t sizeToMove = (idElement - _pos);
	if ( 0 < sizeToMove) {
		for (size_t iii=1; iii<=sizeToMove; iii++) {
			m_data[size()-iii] = m_data[idElement-iii];
		}
	}
	// affectation of all input element
	for (size_t iii=0; iii<_nbElement; iii++) {
		m_data[_pos+iii] = _item[iii];
	}
}

void etk::String::insert(size_t _pos, const char _item) {
	insert(_pos, &_item, 1);
}

void etk::String::insert(size_t _pos, const etk::String& _value) {
	insert(_pos, &_value[0], _value.size());
}

void etk::String::erase(size_t _pos, size_t _nbElement) {
	if (_pos>size()) {
		//TK_ERROR(" can not Erase Len Element at this position : " << _pos << " > " << size());
		return;
	}
	if (_pos+_nbElement>size()) {
		_nbElement = size() - _pos;
	}
	size_t idElement = size();
	// move current data
	size_t sizeToMove = (idElement - (_pos+_nbElement));
	if ( 0 < sizeToMove) {
		for (size_t iii=0; iii<sizeToMove; iii++) {
			m_data[_pos+iii] = m_data[_pos+_nbElement+iii];
		}
	}
	// Request resize of the current buffer
	resize(size() - _nbElement);
}

void etk::String::eraseRange(size_t _pos, size_t _posEnd) {
	if (_pos>size()) {
		//TK_ERROR(" can not Erase Element at this position : " << _pos << " > " << size());
		return;
	}
	if (_posEnd > size()) {
		_posEnd = size();
	}
	size_t nbElement = size() - _pos;
	size_t tmpSize = size();
	// move current data
	size_t sizeToMove = (tmpSize - (_pos+nbElement));
	if ( 0 < sizeToMove) {
		for (size_t iii=0; iii<sizeToMove; iii++) {
			m_data[_pos+iii] = m_data[_pos+nbElement+iii];
		}
	}
	// Request resize of the current buffer
	resize(size()-nbElement);
}

etk::String etk::String::extract(size_t _posStart, size_t _posEnd) const {
	etk::String out;
	if (_posStart >= size() ) {
		return out;
	}
	if (_posEnd >= size() ) {
		_posEnd = size();
	}
	out.pushBack(&m_data[_posStart], _posEnd-_posStart);
	return out;
}

const char* etk::String::c_str() const {
	return &m_data[0];
}

etk::String::Iterator etk::String::position(size_t _pos) {
	return etk::String::Iterator(this, _pos);
}

const etk::String::Iterator etk::String::position(size_t _pos) const {
	return etk::String::Iterator(this, _pos);
}

etk::String::Iterator etk::String::begin() {
	return position(0);
}

const etk::String::Iterator etk::String::begin() const {
	return position(0);
}

etk::String::Iterator etk::String::end() {
	return position( size() );
}

const etk::String::Iterator etk::String::end() const {
	return position( size() );
}

void etk::String::resize(size_t _newSize, char _value) {
	size_t oldSize = m_data.size();
	if (oldSize != 0) {
		m_data[m_data.size()-1] = _value;
	}
	m_data.resize(_newSize + 1, _value);
	// in all case ==> we have the last element that is '\0'
	m_data[_newSize] = '\0';
}

bool etk::String::operator== (const etk::String& _obj) const {
	// check if it was the same pointer
	if( this == &_obj ) {
		return true;
	}
	// first step : check the size ...
	if (m_data.size() != _obj.m_data.size()) {
		return false;
	}
	for (size_t iii=0; iii<m_data.size(); ++iii) {
		if (m_data[iii] != _obj.m_data[iii]) {
			return false;
		}
	}
	return true;
}

bool etk::String::operator!= (const etk::String& _obj) const {
	// check if it was the same pointer
	if( this == &_obj ) {
		return false;
	}
	// first step : check the size ...
	if (m_data.size() != _obj.m_data.size()) {
		return true;
	}
	for (size_t iii=0; iii<m_data.size(); ++iii) {
		if (m_data[iii] != _obj.m_data[iii]) {
			return true;
		}
	}
	return false;
}


char etk::toLower(char _value) {
	if (    _value >= 'A'
	     && _value <= 'Z') {
		return _value + ('a' - 'A');
	}
	return _value;
}

char etk::toUpper(char _value) {
	if (    _value >= 'a'
	     && _value <= 'z') {
		return _value + ('A' - 'z');
	}
	return _value;
}

etk::String etk::String::toLower() const {
	etk::String tmp(*this);
	for (auto &it: tmp) {
		it = etk::toLower(it);
	}
	return tmp;
}

etk::String& etk::String::lower() {
	for (auto &it: m_data) {
		it = etk::toLower(it);
	}
	return *this;
}

etk::String etk::String::toUpper() const {
	etk::String tmp(*this);
	for (auto &it: tmp) {
		it = etk::toUpper(it);
	}
	return tmp;
}

etk::String& etk::String::upper() {
	for (auto &it: m_data) {
		it = etk::toUpper(it);
	}
	return *this;
}

bool etk::String::endWith(const etk::String& _val, bool _caseSensitive) const {
	if (_val.size() == 0) {
		return false;
	}
	if (_val.size() > size()) {
		return false;
	}
	if (_caseSensitive == true) {
		for( int64_t iii=_val.size()-1, jjj=size()-1;
		     iii>=0 && jjj>=0;
		     iii--, jjj--) {
			if (m_data[jjj] != _val[iii]) {
				return false;
			}
		}
		return true;
	}
	for( int64_t iii=_val.size()-1, jjj=size()-1;
	     iii>=0 && jjj>=0;
	     iii--, jjj--) {
		if (etk::toLower(_val[iii]) != etk::toLower(m_data[jjj])) {
			return false;
		}
	}
	return true;
}

bool etk::String::startWith(const etk::String& _val, bool _caseSensitive) const {
	if (_val.size() == 0) {
		return false;
	}
	if (_val.size() > size()) {
		return false;
	}
	if (_caseSensitive == true) {
		for( size_t iii = 0;
		     iii < _val.size();
		     iii++) {
			if (m_data[iii] != _val[iii]) {
				return false;
			}
		}
		return true;
	}
	for( size_t iii = 0;
	     iii < _val.size();
	     iii++) {
		if (etk::toLower(_val[iii]) != etk::toLower(m_data[iii])) {
			return false;
		}
	}
	return true;
}
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
#if    defined(__TARGET_OS__MacOs) \
    || defined(__TARGET_OS__IOs)
	template <>
	size_t etk::String::to<size_t>() const {
		int ret = 0;
		sscanf(c_str(), "%u", &ret);
		return ret;
	}
#endif
template <>
bool etk::String::to<bool>() const {
	if(    compare("true", false) == true
	    || compare("enable", false) == true
	    || compare("yes", false) == true
	    || compare("1") == true) {
		return true;
	}
	return false;
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

void etk::sort(etk::Vector<etk::String> &_list) {
	etk::Vector<etk::String> tmpList(_list);
	_list.clear();
	for(size_t iii=0; iii<tmpList.size(); iii++) {
		size_t findPos = 0;
		for(size_t jjj=0; jjj<_list.size(); jjj++) {
			//TK_DEBUG("compare : \""<<*tmpList[iii] << "\" and \"" << *m_listDirectory[jjj] << "\"");
			if (tmpList[iii] > _list[jjj]) {
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
	#if    defined(__TARGET_OS__MacOs) \
	    || defined(__TARGET_OS__IOs)
		template<> bool from_string<size_t>(size_t& _variableRet, const etk::String& _value) {
			_variableRet = _value.to<size_t>();
			return true;
		}
	#endif
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
etk::String etk::toString(const int8_t& _val) {
	char tmpVal[256];
	sprintf(tmpVal, "%d", _val);
	return tmpVal;
}
template<>
etk::String etk::toString(const int16_t& _val) {
	char tmpVal[256];
	sprintf(tmpVal, "%d", _val);
	return tmpVal;
}
template<>
etk::String etk::toString(const int32_t& _val) {
	char tmpVal[256];
	sprintf(tmpVal, "%d", _val);
	return tmpVal;
}
template<>
etk::String etk::toString(const int64_t& _val) {
	char tmpVal[256];
	#if (    defined(__TARGET_OS__Android) \
	      || defined(__TARGET_OS__Windows) \
	      || defined(__TARGET_OS__MacOs) \
	      || defined(__TARGET_OS__IOs))
		sprintf(tmpVal, "%lld", _val);
	#else
		sprintf(tmpVal, "%ld", _val);
	#endif
	return tmpVal;
}
template<>
etk::String etk::toString(const uint8_t& _val) {
	char tmpVal[256];
	sprintf(tmpVal, "%u", _val);
	return tmpVal;
}
template<>
etk::String etk::toString(const uint16_t& _val) {
	char tmpVal[256];
	sprintf(tmpVal, "%u", _val);
	return tmpVal;
}
template<>
etk::String etk::toString(const uint32_t& _val) {
	char tmpVal[256];
	sprintf(tmpVal, "%u", _val);
	return tmpVal;
}
template<>
etk::String etk::toString(const uint64_t& _val) {
	char tmpVal[256];
	#if (    defined(__TARGET_OS__Android) \
	      || defined(__TARGET_OS__Windows) \
	      || defined(__TARGET_OS__MacOs) \
	      || defined(__TARGET_OS__IOs))
		sprintf(tmpVal, "%llu", _val);
	#else
		sprintf(tmpVal, "%lu", _val);
	#endif
	return tmpVal;
}
#if    defined(__TARGET_OS__MacOs) \
    || defined(__TARGET_OS__IOs)
template<>
etk::String etk::toString(const size_t& _val) {
	char tmpVal[256];
	sprintf(tmpVal, "%zu", _val);
	return tmpVal;
}
#endif

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

template<> etk::String etk::toString(const etk::UString& _input) {
	etk::String out;
	for (size_t iii=0; iii<_input.size(); ++iii) {
		char output[10];
		u32char::convertUtf8(_input[iii], output);
		out += output;
	}
	return out;
}
template<> etk::String etk::toString(const char32_t& _input) {
	etk::String out;
	char output[10];
	u32char::convertUtf8(_input, output);
	out += output;
	return out;
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

bool etk::String::compare(const etk::String& _val, bool _caseSensitive) const {
	if (_val.size() != size()) {
		return false;
	}
	if (_caseSensitive == true) {
		for(size_t iii=0; iii<_val.size(); ++iii) {
			if (_val[iii] != m_data[iii]) {
				return false;
			}
		}
		return true;
	}
	for(size_t iii=0; iii<_val.size(); ++iii) {
		if (etk::toLower(_val[iii]) != etk::toLower(m_data[iii])) {
			return false;
		}
	}
	return true;
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

void etk::String::append(Iterator _start, Iterator _stop) {
	while (_stop != _start) {
		pushBack(*_start);
		++_start;
	}
}

namespace etk {
	long double string_to_long_double(const etk::String& _obj) {
		return _obj.to<long double>();
	}
	double string_to_double(const etk::String& _obj) {
		return _obj.to<double>();
	}
	float string_to_float(const etk::String& _obj) {
		return _obj.to<float>();
	}
	int8_t string_to_int8_t(const etk::String& _obj) {
		return _obj.to<int8_t>();
	}
	int16_t string_to_int16_t(const etk::String& _obj) {
		return _obj.to<int16_t>();
	}
	int32_t string_to_int32_t(const etk::String& _obj) {
		return _obj.to<int32_t>();
	}
	int64_t string_to_int64_t(const etk::String& _obj) {
		return _obj.to<int64_t>();
	}
	uint8_t string_to_uint8_t(const etk::String& _obj) {
		return _obj.to<uint8_t>();
	}
	uint16_t string_to_uint16_t(const etk::String& _obj) {
		return _obj.to<uint16_t>();
	}
	uint32_t string_to_uint32_t(const etk::String& _obj) {
		return _obj.to<uint32_t>();
	}
	uint64_t string_to_uint64_t(const etk::String& _obj) {
		return _obj.to<uint64_t>();
	}
	bool string_to_bool(const etk::String& _obj) {
		return _obj.to<bool>();
	}
	etk::String tolower(etk::String _obj) {
		return _obj.toLower();
	}
	etk::String toupper(etk::String _obj) {
		return _obj.toUpper();
	}
	bool compare_no_case(const etk::String& _obj, const etk::String& _val) {
		return _obj.compare(_val, false);
	}
	bool end_with(const etk::String& _obj, const etk::String& _val, bool _caseSensitive) {
		return _obj.endWith(_val, _caseSensitive);
	}
	bool start_with(const etk::String& _obj, const etk::String& _val, bool _caseSensitive) {
		return _obj.startWith(_val, _caseSensitive);
	}
	etk::String replace(const etk::String& _obj, char _val, char _replace) {
		etk::String tmp = _obj;
		tmp.replace(_val, _replace);
		return tmp;
	}
	etk::String extract_line(const etk::String& _obj, int32_t _pos) {
		return _obj.getLine(_pos);
	}
	etk::Vector<etk::String> split(const etk::String& _obj, char _val) {
		return _obj.split(_val);
	}
}

bool etk::operator> (const etk::String& _left, const etk::String& _right) {
	for (size_t iii=0;
	     iii<_left.size() && iii<_right.size();
	     ++iii) {
		if (_left[iii] > _right[iii]) {
			return true;
		}
		if (_left[iii] < _right[iii]) {
			return false;
		}
	}
	if (_left.size() > _right.size()) {
		return true;
	}
	return false;
}
bool etk::operator>= (const etk::String& _left, const etk::String& _right) {
	for (size_t iii=0;
	     iii<_left.size() && iii<_right.size();
	     ++iii) {
		if (_left[iii] > _right[iii]) {
			return true;
		}
		if (_left[iii] < _right[iii]) {
			return false;
		}
	}
	if (_left.size() >= _right.size()) {
		return true;
	}
	return false;
}
bool etk::operator< (const etk::String& _left, const etk::String& _right) {
	for (size_t iii=0;
	     iii<_left.size() && iii<_right.size();
	     ++iii) {
		if (_left[iii] < _right[iii]) {
			return true;
		}
		if (_left[iii] > _right[iii]) {
			return false;
		}
	}
	if (_left.size() < _right.size()) {
		return true;
	}
	return false;
}
bool etk::operator<= (const etk::String& _left, const etk::String& _right) {
	for (size_t iii=0;
	     iii<_left.size() && iii<_right.size();
	     ++iii) {
		if (_left[iii] < _right[iii]) {
			return true;
		}
		if (_left[iii] > _right[iii]) {
			return false;
		}
	}
	if (_left.size() <= _right.size()) {
		return true;
	}
	return false;
}
etk::String etk::operator+ (const etk::String& _left, const etk::String& _right) {
	etk::String tmp = _left;
	tmp += _right;
	return tmp;
}
etk::String etk::operator+ (const etk::String& _left, const char* _right) {
	etk::String tmp = _left;
	tmp += _right;
	return tmp;
}
etk::String etk::operator+ (const char* _left, const etk::String& _right) {
	etk::String tmp = _left;
	tmp += _right;
	return tmp;
}
etk::String etk::operator+ (const etk::String& _left, char _right) {
	etk::String tmp = _left;
	tmp.pushBack(_right);
	return tmp;
}
etk::String etk::operator+ (char _left, const etk::String& _right) {
	etk::String tmp = _left;
	tmp += _right;
	return tmp;
}



namespace etk {
	template<> etk::String toString<etk::String>(const etk::String& _val) {
		return _val;
	}
	template<> bool from_string<etk::String>(etk::String& _variableRet, const etk::UString& _value) {
		_variableRet = u32char::convertToUtf8(_value);
		return true;
	}
}



char etk::toHexChar(uint8_t _value) {
	char out;
	if (_value < 10) {
		return _value + '0';
	}
	return _value - 10 + 'A';
}

etk::String etk::toHex(uint64_t _value, uint32_t _size) {
	etk::String out;
	for (int32_t iii = 15; iii >=0; --iii) {
		if (    _size >= iii
		     || _value >= uint64_t(1)<<iii) {
			out += etk::toHexChar((_value>>(iii*4)) & 0x0F);
		}
	}
	return out;
}


etk::String etk::toBin(uint64_t _value, uint32_t _size) {
	etk::String out;
	for (int32_t iii = 63; iii >=0; --iii) {
		if (    _size >= iii
		     || _value >= uint64_t(1)<<iii) {
			out += etk::toHexChar((_value>>(iii)) & 0x01);
		}
	}
	return out;
}

