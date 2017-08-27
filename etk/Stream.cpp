/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL-2 (see license file)
 */

#include <etk/Stream.hpp>
#include <etk/String.hpp>

etk::Stream::Stream(size_t _basicSize) :
  m_data(new etk::String) {
	
}

etk::Stream::~Stream() {
	delete m_data;
	m_data = nullptr;
}

etk::Stream& etk::Stream::operator<< (const char* _data) {
	*m_data += _data;
	return *this;
}
etk::Stream& etk::Stream::operator<< (const bool _data) {
	*m_data += etk::toString(_data);
	return *this;
}
etk::Stream& etk::Stream::operator<< (const int8_t _data) {
	*m_data += etk::toString(_data);
	return *this;
}
etk::Stream& etk::Stream::operator<< (const int16_t _data) {
	*m_data += etk::toString(_data);
	return *this;
}
etk::Stream& etk::Stream::operator<< (const int32_t _data) {
	*m_data += etk::toString(_data);
	return *this;
}
etk::Stream& etk::Stream::operator<< (const int64_t _data) {
	*m_data += etk::toString(_data);
	return *this;
}
etk::Stream& etk::Stream::operator<< (const uint8_t _data) {
	*m_data += etk::toString(_data);
	return *this;
}
etk::Stream& etk::Stream::operator<< (const uint16_t _data) {
	*m_data += etk::toString(_data);
	return *this;
}
etk::Stream& etk::Stream::operator<< (const uint32_t _data) {
	*m_data += etk::toString(_data);
	return *this;
}
etk::Stream& etk::Stream::operator<< (const uint64_t _data) {
	*m_data += etk::toString(_data);
	return *this;
}
etk::Stream& etk::Stream::operator<< (const float _data) {
	*m_data += etk::toString(_data);
	return *this;
}
etk::Stream& etk::Stream::operator<< (const double _data) {
	*m_data += etk::toString(_data);
	return *this;
}

const char* etk::Stream::c_str() const {
	return m_data->c_str();
}

const size_t etk::Stream::size() const {
	return m_data->size();
}