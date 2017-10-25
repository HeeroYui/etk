/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL-2 (see license file)
 */

#include <etk/Stream.hpp>
#include <etk/String.hpp>

etk::Stream::Stream(size_t _basicSize) :
  m_data(ETK_NEW(etk::String)) {
	m_data->reserve(_basicSize);
}

etk::Stream::~Stream() {
	ETK_DELETE(etk::String, m_data);
	m_data = nullptr;
}

etk::Stream& etk::Stream::operator<< (const char* _data) {
	*m_data += _data;
	return *this;
}
etk::Stream& etk::Stream::operator<< (const bool& _data) {
	*m_data += etk::toString(_data);
	return *this;
}
etk::Stream& etk::Stream::operator<< (const int8_t& _data) {
	*m_data += etk::toString(_data);
	return *this;
}
etk::Stream& etk::Stream::operator<< (const int16_t& _data) {
	*m_data += etk::toString(_data);
	return *this;
}
etk::Stream& etk::Stream::operator<< (const int32_t& _data) {
	*m_data += etk::toString(_data);
	return *this;
}
etk::Stream& etk::Stream::operator<< (const int64_t& _data) {
	*m_data += etk::toString(_data);
	return *this;
}
etk::Stream& etk::Stream::operator<< (const uint8_t& _data) {
	*m_data += etk::toString(_data);
	return *this;
}
etk::Stream& etk::Stream::operator<< (const uint16_t& _data) {
	*m_data += etk::toString(_data);
	return *this;
}
etk::Stream& etk::Stream::operator<< (const uint32_t& _data) {
	*m_data += etk::toString(_data);
	return *this;
}
etk::Stream& etk::Stream::operator<< (const uint64_t& _data) {
	*m_data += etk::toString(_data);
	return *this;
}
#if    defined(__TARGET_OS__MacOs) \
    || defined(__TARGET_OS__IOs)
	etk::Stream& etk::Stream::operator<< (const size_t& _data) {
		*m_data += etk::toString(_data);
		return *this;
	}
#endif
etk::Stream& etk::Stream::operator<< (const float& _data) {
	*m_data += etk::toString(_data);
	return *this;
}
etk::Stream& etk::Stream::operator<< (const double& _data) {
	*m_data += etk::toString(_data);
	return *this;
}
etk::Stream& etk::Stream::operator<< (const etk::NullPtr& _data) {
	*m_data += "nullptr";
	return *this;
}

const char* etk::Stream::c_str() const {
	return m_data->c_str();
}

const size_t etk::Stream::size() const {
	return m_data->size();
}

const etk::String& etk::Stream::str() const {
	return *m_data;
}
