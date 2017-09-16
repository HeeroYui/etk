/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/typeInfo.hpp>
#include <etk/String.hpp>
#include <etk/UString.hpp>
#include <etk/Stream.hpp>

static etk::Vector<const char*>& getListType() {
	static etk::Vector<const char*> s_list;
	return s_list;
}

const etk::Vector<const char*>& etk::getListDeclaredType() {
	return getListType();
}

size_t etk::addType(const char* _name) {
	getListType().pushBack(_name);
	return getListType().size();
}


// declare all type of etk-base ...
ETK_DECLARE_TYPE(int8_t);
ETK_DECLARE_TYPE(int16_t);
ETK_DECLARE_TYPE(int32_t);
ETK_DECLARE_TYPE(int64_t);
ETK_DECLARE_TYPE(uint8_t);
ETK_DECLARE_TYPE(uint16_t);
ETK_DECLARE_TYPE(uint32_t);
ETK_DECLARE_TYPE(uint64_t);

ETK_DECLARE_TYPE(char32_t);
ETK_DECLARE_TYPE(bool);
ETK_DECLARE_TYPE(float);
ETK_DECLARE_TYPE(double);

ETK_DECLARE_TYPE(etk::String);
ETK_DECLARE_TYPE(etk::UString);
ETK_DECLARE_TYPE(etk::Stream);
ETK_DECLARE_TYPE(etk::NullPtr);

