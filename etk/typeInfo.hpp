/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/types.hpp>
#include <etk/Vector.hpp>

#pragma once

namespace etk {
	template<typename ETK_TYPE>
	class TypeTraitInfo {
		public:
			// Name of the type
			static const char* m_name;
			// Size of the type
			static const size_t m_size;
			// Dynamic unique ID of the Type
			static const size_t m_id;
	};
	/**
	 * @brief Get list of all type declared in this software.
	 * @return A static list of all register type in the system.
	 */
	etk::Vector<const char*> getListDeclaredType();
	/**
	 * @brief Add an element declared type in the system database.
	 * @param[in] Name of the type
	 * @return The Id of the Object (new unique ID)
	 */
	size_t addType(const char* _name);
}

#define ETK_DECLARE_TYPE(...) template<> \
	const char* etk::TypeTraitInfo<__VA_ARGS__>::m_name = #__VA_ARGS__; \
	template<> const size_t etk::TypeTraitInfo<__VA_ARGS__>::m_size = sizeof(__VA_ARGS__); \
	template<> const size_t etk::TypeTraitInfo<__VA_ARGS__>::m_id = etk::addType(#__VA_ARGS__);

#define ETK_GET_TYPE_NAME(...) etk::TypeTraitInfo<__VA_ARGS__>::m_name
#define ETK_GET_TYPE_SIZE(...) etk::TypeTraitInfo<__VA_ARGS__>::m_size
#define ETK_GET_TYPE_ID(...) etk::TypeTraitInfo<__VA_ARGS__>::m_id

