

#include <etk/UString.hpp>
#include <etk/Number.hpp>

etk::UString::UString():
  m_data() {
	m_data.resize(1, '\0');
}

etk::UString::UString(const etk::UString& _obj) {
	m_data = _obj.m_data;
}

etk::UString::UString(const etk::UString& _obj, size_t _pos, size_t _size) {
	if (_pos + _size >= _obj.size()) {
		_size = etk::UString::npos;
	}
	if (_size != etk::UString::npos) {
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

etk::UString::UString(const char32_t* _obj) {
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

etk::UString::UString(const char32_t* _obj, size_t _size) {
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

etk::UString::UString(size_t _size, char32_t _val) {
	resize(_size);
	for (size_t iii=0; iii<_size; ++iii) {
		m_data[iii] = _val;
	}
}

etk::UString::UString(Iterator _start, Iterator _stop) {
	size_t size = etk::distance(_start, _stop);
	resize(size);
	Iterator it = begin();
	while (_start != _stop) {
		*it++ = *_start++;
	}
}

etk::UString::UString(etk::UString&& _obj) noexcept {
	m_data = std::move(_obj.m_data);
}

etk::UString::UString(char32_t _value) {
	resize(1);
	m_data[0] = _value;
}

etk::UString::~UString() {
	// nothing to do...
}

void etk::UString::swap(etk::UString& _obj) {
	// avoid Swap of itself
	if(this != &_obj) {
		m_data.swap(_obj.m_data);
	}
}

etk::UString& etk::UString::operator=(const etk::UString& _obj) {
	if (this != &_obj) {
		m_data = _obj.m_data;
	}
	// Return the current pointer
	return *this;
}

etk::UString& etk::UString::operator=(const char32_t* _obj) {
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

etk::UString& etk::UString::operator=(char32_t _value) {
	resize(1);
	m_data[0] = _value;
	// Return the current pointer
	return *this;
}

etk::UString& etk::UString::operator+= (const etk::UString& _obj) {
	size_t numberElement = _obj.size();
	size_t idElement = size();
	resize(size()+_obj.size());
	for (size_t iii=0; iii<_obj.size(); ++iii) {
		m_data[idElement+iii] = _obj[iii];
	}
	// Return the current pointer
	return *this;
}

etk::UString& etk::UString::operator+= (const char32_t* _obj) {
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

etk::UString& etk::UString::operator+= (char32_t _value) {
	pushBack(_value);
	// Return the current pointer
	return *this;
}
size_t etk::UString::size() const {
	return m_data.size() - 1; // remove '\0'
}

void etk::UString::pushFront(char32_t _item) {
	insert(0, &_item, 1);
}

void etk::UString::pushFront(const char32_t * _item, size_t _nbElement) {
	insert(0, _item, _nbElement);
}

void etk::UString::pushBack(const char32_t _item) {
	size_t idElement = size();
	resize(size()+1);
	if (idElement < size()) {
		m_data[idElement] = _item;
	} else {
		TK_ERROR("Resize does not work correctly ... not added item");
	}
}

void etk::UString::pushBack(const char32_t* _item, size_t _nbElement) {
	if (_item == nullptr) {
		return;
	}
	size_t idElement = size();
	resize(size()+_nbElement);
	if (idElement > size()) {
		TK_ERROR("Resize does not work correctly ... not added item");
		return;
	}
	for (size_t iii=0; iii<_nbElement; iii++) {
		m_data[idElement+iii] = _item[iii];
	}
}

void etk::UString::popBack() {
	if(size()>0) {
		resize(size()-1);
	}
}

void etk::UString::clear() {
	resize(0);
}

void etk::UString::insert(size_t _pos, const char32_t* _item, size_t _nbElement) {
	if (_pos>size()) {
		TK_WARNING(" can not insert Element at this position : " << _pos << " > " << size() << " add it at the end ... ");
		pushBack(_item, _nbElement);
		return;
	}
	size_t idElement = size();
	// Request resize of the current buffer
	resize(size()+_nbElement);
	if (idElement>=size()) {
		TK_ERROR("Resize does not work correctly ... not added item");
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

void etk::UString::insert(size_t _pos, const char32_t _item) {
	insert(_pos, &_item, 1);
}

void etk::UString::insert(size_t _pos, const etk::UString& _value) {
	insert(_pos, &_value[0], _value.size());
}

void etk::UString::erase(size_t _pos, size_t _nbElement) {
	if (_pos>size()) {
		TK_ERROR(" can not Erase Len Element at this position : " << _pos << " > " << size());
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

void etk::UString::eraseRange(size_t _pos, size_t _posEnd) {
	if (_pos>size()) {
		TK_ERROR(" can not Erase Element at this position : " << _pos << " > " << size());
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

etk::UString etk::UString::extract(size_t _posStart, size_t _posEnd) const {
	etk::UString out;
	if (_posStart >= size() ) {
		return out;
	}
	if (_posEnd >= size() ) {
		_posEnd = size();
	}
	out.pushBack(&m_data[_posStart], _posEnd-_posStart);
	return out;
}

const char32_t* etk::UString::c_str() const {
	return &m_data[0];
}

etk::UString::Iterator etk::UString::position(size_t _pos) {
	return etk::UString::Iterator(this, _pos);
}

const etk::UString::Iterator etk::UString::position(size_t _pos) const {
	return etk::UString::Iterator(this, _pos);
}

etk::UString::Iterator etk::UString::begin() {
	return position(0);
}

const etk::UString::Iterator etk::UString::begin() const {
	return position(0);
}

etk::UString::Iterator etk::UString::end() {
	return position( size()-1 );
}

const etk::UString::Iterator etk::UString::end() const {
	return position( size()-1 );
}

void etk::UString::resize(size_t _newSize, char32_t _value) {
	size_t oldSize = m_data.size();
	m_data[m_data.size()-1] = _value;
	m_data.resize(_newSize + 1, _value);
	// in all case ==> we have the last element that is '\0'
	m_data[_newSize] = '\0';
}

bool etk::UString::operator== (const etk::UString& _obj) const {
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

bool etk::UString::operator!= (const etk::UString& _obj) const {
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


char32_t etk::toLower(char32_t _value) {
	if (    _value >= 'A'
	     && _value <= 'Z') {
		return _value + ('a' - 'A');
	}
	return _value;
}

char32_t etk::toUpper(char32_t _value) {
	if (    _value >= 'a'
	     && _value <= 'z') {
		return _value + ('A' - 'z');
	}
	return _value;
}

etk::UString etk::UString::toLower() const {
	etk::UString tmp(*this);
	for (auto &it: tmp) {
		it = etk::toLower(it);
	}
	return tmp;
}

etk::UString& etk::UString::lower() {
	for (auto &it: m_data) {
		it = etk::toLower(it);
	}
	return *this;
}

etk::UString etk::UString::toUpper() const {
	etk::UString tmp(*this);
	for (auto &it: tmp) {
		it = etk::toUpper(it);
	}
	return tmp;
}

etk::UString& etk::UString::upper() {
	for (auto &it: m_data) {
		it = etk::toUpper(it);
	}
	return *this;
}

bool etk::UString::endWith(const etk::UString& _val, bool _caseSensitive) const {
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

bool etk::UString::startWith(const etk::UString& _val, bool _caseSensitive) const {
	if (_val.size() == 0) {
		return false;
	}
	if (_val.size() > size()) {
		return false;
	}
	if (_caseSensitive == true) {
		for( size_t iii = 0;
		     iii < size();
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
long double etk::UString::to<long double>() const {
	etk::Number value(*this);
	return value.getDouble();
}

template <>
double etk::UString::to<double>() const {
	etk::Number value(*this);
	return value.getDouble();
}

template <>
float etk::UString::to<float>() const {
	etk::Number value(*this);
	return value.getDouble();
}

template <>
int8_t etk::UString::to<int8_t>() const {
	etk::Number value(*this);
	return value.getI64();
}

template <>
int16_t etk::UString::to<int16_t>() const {
	etk::Number value(*this);
	return value.getI64();
}

template <>
int32_t etk::UString::to<int32_t>() const {
	etk::Number value(*this);
	return value.getI64();
}

template <>
int64_t etk::UString::to<int64_t>() const {
	etk::Number value(*this);
	return value.getI64();
}

template <>
uint8_t etk::UString::to<uint8_t>() const {
	etk::Number value(*this);
	return value.getU64();
}

template <>
uint16_t etk::UString::to<uint16_t>() const {
	etk::Number value(*this);
	return value.getU64();
}

template <>
uint32_t etk::UString::to<uint32_t>() const {
	etk::Number value(*this);
	return value.getU64();
}

template <>
uint64_t etk::UString::to<uint64_t>() const {
	etk::Number value(*this);
	return value.getU64();
}

template <>
bool etk::UString::to<bool>() const {
	if(    compare(U"true", false) == true
	    || compare(U"enable", false) == true
	    || compare(U"yes", false) == true
	    || compare(U"1") == true) {
		return true;
	}
	return false;
}

std::ostream& etk::operator <<(std::ostream& _os, const etk::UString& _obj) {
	_os << _obj.c_str();
	return _os;
}

void etk::sort(etk::Vector<etk::UString *> &_list) {
	etk::Vector<etk::UString *> tmpList(_list);
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

void etk::sort(etk::Vector<etk::UString> &_list) {
	etk::Vector<etk::UString> tmpList(_list);
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
	template<> bool from_string<etk::UString>(etk::UString& _variableRet, const etk::UString& _value) {
		_variableRet = _value;
		return true;
	}
	template<> bool from_string<int8_t>(int8_t& _variableRet, const etk::UString& _value) {
		_variableRet = _value.to<int8_t>();
		return true;
	}
	template<> bool from_string<int16_t>(int16_t& _variableRet, const etk::UString& _value) {
		_variableRet = _value.to<int16_t>();
		return true;
	}
	template<> bool from_string<int32_t>(int32_t& _variableRet, const etk::UString& _value) {
		_variableRet = _value.to<int32_t>();
		return true;
	}
	template<> bool from_string<int64_t>(int64_t& _variableRet, const etk::UString& _value) {
		_variableRet = _value.to<int64_t>();
		return true;
	}
	template<> bool from_string<uint8_t>(uint8_t& _variableRet, const etk::UString& _value) {
		_variableRet = _value.to<uint8_t>();
		return true;
	}
	template<> bool from_string<uint16_t>(uint16_t& _variableRet, const etk::UString& _value) {
		_variableRet = _value.to<uint16_t>();
		return true;
	}
	template<> bool from_string<uint32_t>(uint32_t& _variableRet, const etk::UString& _value) {
		_variableRet = _value.to<uint32_t>();
		return true;
	}
	template<> bool from_string<uint64_t>(uint64_t& _variableRet, const etk::UString& _value) {
		_variableRet = _value.to<uint64_t>();
		return true;
	}
	template<> bool from_string<float>(float& _variableRet, const etk::UString& _value) {
		_variableRet = _value.to<float>();
		return true;
	}
	template<> bool from_string<double>(double& _variableRet, const etk::UString& _value) {
		_variableRet = _value.to<double>();
		return true;
	}
	template<> bool from_string<long double>(long double& _variableRet, const etk::UString& _value) {
		_variableRet = _value.to<long double>();
		return true;
	}
	template<> bool from_string<bool>(bool& _variableRet, const etk::UString& _value) {
		_variableRet = _value.to<bool>();
		return true;
	}
}

template<>
etk::UString etk::toUString(const bool& _val) {
	return utf8::convertUnicode(etk::toString(_val));
}
template<>
etk::UString etk::toUString(const int8_t& _val) {
	return utf8::convertUnicode(etk::toString(_val));
}
template<>
etk::UString etk::toUString(const int16_t& _val) {
	return utf8::convertUnicode(etk::toString(_val));
}
template<>
etk::UString etk::toUString(const int32_t& _val) {
	return utf8::convertUnicode(etk::toString(_val));
}
template<>
etk::UString etk::toUString(const int64_t& _val) {
	return utf8::convertUnicode(etk::toString(_val));
}
template<>
etk::UString etk::toUString(const uint8_t& _val) {
	return utf8::convertUnicode(etk::toString(_val));
}
template<>
etk::UString etk::toUString(const uint16_t& _val) {
	return utf8::convertUnicode(etk::toString(_val));
}
template<>
etk::UString etk::toUString(const uint32_t& _val) {
	return utf8::convertUnicode(etk::toString(_val));
}
template<>
etk::UString etk::toUString(const uint64_t& _val) {
	return utf8::convertUnicode(etk::toString(_val));
}
template<>
etk::UString etk::toUString(const size_t& _val) {
	return utf8::convertUnicode(etk::toString(_val));
}

template<>
etk::UString etk::toUString(const float& _val) {
	return utf8::convertUnicode(etk::toString(_val));
}
template<>
etk::UString etk::toUString(const double& _val) {
	return utf8::convertUnicode(etk::toString(_val));
}
template<>
etk::UString etk::toUString(const long double& _val) {
	return utf8::convertUnicode(etk::toString(_val));
}

size_t etk::UString::find(char32_t _value, size_t _pos) const {
	for (size_t iii=_pos; iii<m_data.size(); ++iii) {
		if (_value == m_data[iii]) {
			return iii;
		}
	}
	return etk::UString::npos;
}

size_t etk::UString::find(const etk::UString& _value, size_t _pos) const {
	for (size_t iii=_pos; iii<m_data.size(); ++iii) {
		bool check = true;
		for (size_t jjj=0; jjj<_value.size(); ++jjj) {
			if (iii+jjj >= m_data.size()) {
				return etk::UString::npos;
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
	return etk::UString::npos;
}

size_t etk::UString::rfind(char32_t _value, size_t _pos) const {
	if (_pos >= m_data.size()) {
		_pos = m_data.size()-1;
	}
	for (int64_t iii=_pos; iii>=0; --iii) {
		if (_value == m_data[iii]) {
			return iii;
		}
	}
	return etk::UString::npos;
}

size_t etk::UString::rfind(const etk::UString& _value, size_t _pos) const {
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
	return etk::UString::npos;
}

etk::UString& etk::UString::replace(size_t _pos, size_t _len, char32_t _replace) {
	erase(_pos, _len);
	insert(_pos, _replace);
	return *this;
}

etk::UString& etk::UString::replace(size_t _pos, size_t _len, const etk::UString& _replace) {
	erase(_pos, _len);
	insert(_pos, _replace);
	return *this;
}

etk::UString& etk::UString::replace(char32_t _val, char32_t _replace) {
	size_t pos = 0;
	while ((pos = find(_val, pos)) != etk::UString::npos) {
		replace(pos, 1, _replace);
		pos += 1;
	}
	return *this;
}

etk::UString& etk::UString::replace(const etk::UString& _val, const etk::UString& _replace) {
	size_t pos = 0;
	while ((pos = find(_val, pos)) != etk::UString::npos) {
		replace(pos, _val.size(), _replace);
		pos += _replace.size();
	}
	return *this;
}

etk::UString etk::UString::getLine(int32_t _pos) const {
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
	if (startPos == etk::UString::npos) {
		startPos = 0;
	} else if (startPos >= size() ) {
		return U"";
	}
	if (stopPos == etk::UString::npos) {
		return U"";
	} else if (stopPos >= size() ) {
		stopPos = size();
	}
	return etk::UString(*this, startPos, stopPos - startPos);
}

bool etk::UString::compare(const etk::UString& _val, bool _caseSensitive) const {
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

etk::Vector<etk::UString> etk::UString::split(char32_t _val) const {
	etk::Vector<etk::UString> list;
	size_t lastStartPos = 0;
	for(size_t iii=0; iii<size(); iii++) {
		if (m_data[iii] == _val) {
			list.pushBack(etk::UString(*this, lastStartPos, iii - lastStartPos));
			lastStartPos = iii+1;
		}
	}
	if (lastStartPos < size()) {
		list.pushBack(etk::UString(*this, lastStartPos));
	}
	return list;
}

etk::Vector<etk::UString> etk::UString::split(etk::UString _val) const {
	etk::Vector<etk::UString> list;
	size_t lastStartPos = 0;
	for(size_t iii=0; iii<size()-_val.size(); iii++) {
		if (etk::UString(begin()+iii, begin()+iii+_val.size()) ==_val) {
			list.pushBack(etk::UString(*this, lastStartPos, iii - lastStartPos));
			lastStartPos = iii+_val.size();
			iii += _val.size()-1;
		}
	}
	if (lastStartPos < size()) {
		list.pushBack(etk::UString(*this, lastStartPos));
	}
	return list;
}

namespace etk {
	long double string_to_long_double(const etk::UString& _obj) {
		return _obj.to<long double>();
	}
	double string_to_double(const etk::UString& _obj) {
		return _obj.to<double>();
	}
	float string_to_float(const etk::UString& _obj) {
		return _obj.to<float>();
	}
	int8_t string_to_int8_t(const etk::UString& _obj) {
		return _obj.to<int8_t>();
	}
	int16_t string_to_int16_t(const etk::UString& _obj) {
		return _obj.to<int16_t>();
	}
	int32_t string_to_int32_t(const etk::UString& _obj) {
		return _obj.to<int32_t>();
	}
	int64_t string_to_int64_t(const etk::UString& _obj) {
		return _obj.to<int64_t>();
	}
	uint8_t string_to_uint8_t(const etk::UString& _obj) {
		return _obj.to<uint8_t>();
	}
	uint16_t string_to_uint16_t(const etk::UString& _obj) {
		return _obj.to<uint16_t>();
	}
	uint32_t string_to_uint32_t(const etk::UString& _obj) {
		return _obj.to<uint32_t>();
	}
	uint64_t string_to_uint64_t(const etk::UString& _obj) {
		return _obj.to<uint64_t>();
	}
	bool string_to_bool(const etk::UString& _obj) {
		return _obj.to<bool>();
	}
	etk::UString tolower(etk::UString _obj) {
		return _obj.toLower();
	}
	etk::UString toupper(etk::UString _obj) {
		return _obj.toUpper();
	}
	bool compare_no_case(const etk::UString& _obj, const etk::UString& _val) {
		return _obj.compare(_val, false);
	}
	bool end_with(const etk::UString& _obj, const etk::UString& _val, bool _caseSensitive) {
		return _obj.endWith(_val, _caseSensitive);
	}
	bool start_with(const etk::UString& _obj, const etk::UString& _val, bool _caseSensitive) {
		return _obj.startWith(_val, _caseSensitive);
	}
	etk::UString replace(const etk::UString& _obj, char32_t _val, char32_t _replace) {
		etk::UString tmp = _obj;
		tmp.replace(_val, _replace);
		return tmp;
	}
	etk::UString extract_line(const etk::UString& _obj, int32_t _pos) {
		return _obj.getLine(_pos);
	}
	etk::Vector<etk::UString> split(const etk::UString& _obj, char32_t _val) {
		return _obj.split(_val);
	}
}




bool etk::operator> (const etk::UString& _left, const etk::UString& _right) {
	for (size_t iii=0; iii<_left.size() && iii<_right.size(); ++iii) {
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
bool etk::operator>= (const etk::UString& _left, const etk::UString& _right) {
	for (size_t iii=0; iii<_left.size() && iii<_right.size(); ++iii) {
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
bool etk::operator< (const etk::UString& _left, const etk::UString& _right) {
	for (size_t iii=0; iii<_left.size() && iii<_right.size(); ++iii) {
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
bool etk::operator<= (const etk::UString& _left, const etk::UString& _right) {
	for (size_t iii=0; iii<_left.size() && iii<_right.size(); ++iii) {
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
etk::UString etk::operator+ (const etk::UString& _left, const etk::UString& _right) {
	etk::UString tmp = _left;
	tmp += _right;
	return tmp;
}
etk::UString etk::operator+ (const etk::UString& _left, const char32_t* _right) {
	etk::UString tmp = _left;
	tmp += _right;
	return tmp;
}
etk::UString etk::operator+ (const char32_t* _left, const etk::UString& _right) {
	etk::UString tmp = _left;
	tmp += _right;
	return tmp;
}
etk::UString etk::operator+ (const etk::UString& _left, char32_t _right) {
	etk::UString tmp = _left;
	tmp.pushBack(_right);
	return tmp;
}
etk::UString etk::operator+ (char32_t _left, const etk::UString& _right) {
	etk::UString tmp = _left;
	tmp += _right;
	return tmp;
}


