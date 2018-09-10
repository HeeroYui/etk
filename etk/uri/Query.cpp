/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#include <etk/uri/Query.hpp>
#include <etk/debug.hpp>

static const etk::String hexData = "0123456789ABCDEF";

static etk::String pourcentEncode(const etk::String& _data) {
	etk::String out;
	for (auto &it : _data) {
		if (    (it >= 'a' && it <= 'z')
		     || (it >= 'A' && it <= 'Z')
		     || (it >= '0' && it <= '9')
		     || it == '-'
		     || it == '_'
		     || it == '.'
		     || it == '~') {
			out += it;
		} else {
			out += "%";
			out += hexData[(uint32_t(it)>>4)&0x0F];
			out += hexData[uint32_t(it)&0x0F];
		}
	}
	return out;
}

static int32_t convertStringHexToInt(const char _value) {
	if (_value >= 'a' && _value <= 'z') {
		return int32_t(_value) - int32_t('a') + 10;
	}
	if (_value >= 'A' && _value <= 'Z') {
		return int32_t(_value) - int32_t('A') + 10;
	}
	if (_value >= '0' && _value <= '9') {
		return int32_t(_value) - int32_t('0');
	}
	TK_ERROR("Not a hexadecimal Value: '" << _value << "'");
	return 0;
}

static etk::String pourcentDecode(const etk::String& _data) {
	etk::String out;
	for (size_t iii=0; iii<_data.size(); ++iii) {
		auto it = _data[iii];
		if (it == '%') {
			if (iii+2 < _data.size()) {
				auto val1 = convertStringHexToInt(_data[iii+1])<<4;
				val1 += convertStringHexToInt(_data[iii+2]);
				out += char(val1);
				iii += 2;
			} else {
				TK_ERROR("can not convert pourcent ==> input size error: '" << _data << "'");
				return out;
			}
		} else {
			out += it;
		}
	}
	return out;
}

etk::uri::Query::Query() {
	
}

etk::uri::Query::Query(const etk::String& _value) {
	setEncoded(_value);
}

void etk::uri::Query::setEncoded(const etk::String& _value) {
	m_data.clear();
	auto listElements = etk::split(_value, '&');
	for (auto &it : listElements) {
		if (it.size() == 0) {
			continue;
		}
		auto offset = it.find('=');
		if (offset == etk::String::npos) {
			m_data.set(pourcentDecode(it), "");
			continue;
		}
		m_data.set(pourcentDecode(it.extract(0, offset)),
		           pourcentDecode(it.extract(offset+1, etk::String::npos)));
	}
}

etk::String etk::uri::Query::getEncoded() const {
	etk::String out;
	for (auto &it: m_data) {
		if (out.empty() == false) {
			out += "&";
		}
		out += pourcentEncode(it.first);
		if (it.second.empty() == false) {
			out += "=";
			out += pourcentEncode(it.second);
		}
	}
	return out;
}

etk::String etk::uri::Query::getNotEncoded() const {
	etk::String out;
	for (auto &it: m_data) {
		if (out.empty() == false) {
			out += "&";
		}
		out += it.first;
		if (it.second.empty() == false) {
			out += "=";
			out += it.second;
		}
	}
	return out;
}

void etk::uri::Query::set(const etk::String& _key, const etk::String& _value) {
	m_data.set(_key, _value);
}

bool etk::uri::Query::exist(const etk::String& _key) {
	return m_data.exist(_key);
}

void etk::uri::Query::erase(const etk::String& _key) {
	m_data.erase(_key);
}

etk::String etk::uri::Query::get(const etk::String& _key) {
	return m_data[_key];
}

void etk::uri::Query::clear() {
	m_data.clear();
}

etk::Stream& etk::operator <<(etk::Stream& _os, const etk::uri::Query& _obj) {
	_os << "Query{";
	_os << _obj.getNotEncoded();
	_os << "}";
	return _os;
}

bool etk::uri::Query::isEmpty() const {
	return m_data.size() == 0;
}

bool etk::uri::Query::operator== (const etk::uri::Query& _obj) const {
	return getEncoded() == _obj.getEncoded();
}

bool etk::uri::Query::operator!= (const etk::uri::Query& _obj) const {
	return getEncoded() != _obj.getEncoded();
}

bool etk::uri::Query::operator< (const etk::uri::Query& _obj) const {
	return getEncoded() < _obj.getEncoded();
}

bool etk::uri::Query::operator> (const etk::uri::Query& _obj) const {
	return getEncoded() > _obj.getEncoded();
}
