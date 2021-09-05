/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL-2 (see license file)
 */
#pragma once

#include <etk/types.hpp>

namespace test {

	class ConstructDestruct {
		private:
			uint32_t m_addValue;
		public:
			ConstructDestruct(uint32_t _addValue);
			ConstructDestruct(ConstructDestruct&& _obj);
			ConstructDestruct(const ConstructDestruct& _obj);
			virtual ~ConstructDestruct();
			ConstructDestruct& operator= (ConstructDestruct&& _obj);
			ConstructDestruct& operator= (const ConstructDestruct& _obj);
	};
	int32_t getIsDestroy();
	void resetIsDestroy();
}
