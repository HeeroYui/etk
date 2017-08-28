/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL-2 (see license file)
 */
#pragma once


namespace etk {
	template<class ETK_MOVE_TYPE>
	struct _Remove_reference {
		// remove reference
		typedef ETK_MOVE_TYPE m_type;
	};
	template<class ETK_MOVE_TYPE>
	struct _Remove_reference<ETK_MOVE_TYPE&> {
		// remove reference
		typedef ETK_MOVE_TYPE m_type;
	};
	template<class ETK_MOVE_TYPE>
	struct _Remove_reference<ETK_MOVE_TYPE&&> {
		// remove rvalue reference
		typedef ETK_MOVE_TYPE m_type;
	};
	
	template<class ETK_MOVE_TYPE> inline
	typename etk::_Remove_reference<ETK_MOVE_TYPE>::m_type&& move(ETK_MOVE_TYPE&& _obj) {
		// forward _Arg as movable
		return ((typename etk::_Remove_reference<ETK_MOVE_TYPE>::m_type&&)_obj);
	}

}
