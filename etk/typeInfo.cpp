/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/typeInfo.hpp>
#include <etk/String.hpp>
#include <etk/UString.hpp>
#include <etk/Stream.hpp>
#include <etk/Map.hpp>

static etk::Map<const char*, size_t>& getListElement() {
	static etk::Map<const char*, size_t> s_list(0, true, [](etk::Pair<const char*, size_t>* const & _key1,
	                                                        etk::Pair<const char*, size_t>* const & _key2) {
	                                                        	return strcoll(_key1->first, _key2->first) < 0;
	                                                        });
	return s_list;
}

etk::Vector<const char*> etk::getListDeclaredType() {
	return getListElement().getKeys();
}

size_t etk::addType(const char* _name) {
	size_t id = getListElement().size()+1;
	getListElement().set(_name, id);
	return id;
	// return size_t(_name);
	// return getListType().size();
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

#include <etk/Exception.hpp>

ETK_DECLARE_TYPE(etk::Exception);
ETK_DECLARE_TYPE(etk::exception::InvalidArgument);
ETK_DECLARE_TYPE(etk::exception::DomainError);
ETK_DECLARE_TYPE(etk::exception::LengthError);
ETK_DECLARE_TYPE(etk::exception::OutOfRange);
ETK_DECLARE_TYPE(etk::exception::RangeError);
ETK_DECLARE_TYPE(etk::exception::OverflowError);
ETK_DECLARE_TYPE(etk::exception::UnderflowError);
ETK_DECLARE_TYPE(etk::exception::CastError);
ETK_DECLARE_TYPE(etk::exception::AllocationError);
ETK_DECLARE_TYPE(etk::exception::RuntimeError);

