/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */


#include <etk/os/FSNodeRight.hpp>

// Right Flags :
enum {
	right_other_execute = 1 << 0,
	right_other_write   = 1 << 1,
	right_other_read    = 1 << 2,
	right_group_execute = 1 << 3,
	right_group_write   = 1 << 4,
	right_group_read    = 1 << 5,
	right_user_execute  = 1 << 6,
	right_user_write    = 1 << 7,
	right_user_read     = 1 << 8,
};

etk::FSNodeRight::FSNodeRight(int16_t _newRight) :
 m_rights(_newRight&0x01FF) {
	
}

etk::FSNodeRight& etk::FSNodeRight::operator= (const etk::FSNodeRight &_obj ) {
	m_rights = _obj.m_rights;
	return *this;
}

etk::FSNodeRight& etk::FSNodeRight::operator= (const int32_t _newVal) {
	m_rights = _newVal&0x01FF;
	return *this;
}

void etk::FSNodeRight::clear() {
	m_rights = 0;
}

bool etk::FSNodeRight::isUserReadable() const {
	return ((m_rights&right_user_read)!=0)?true:false;
}

bool etk::FSNodeRight::isUserWritable() const {
	return ((m_rights&right_user_write)!=0)?true:false;
}

bool etk::FSNodeRight::isUserRunable() const {
	return ((m_rights&right_user_execute)!=0)?true:false;
}

void etk::FSNodeRight::setUserReadable(bool _newStatus) {
	// reset the flag :
	m_rights &= (0xFFFFFFFF - right_user_read);
	if (_newStatus == true) {
		m_rights |= right_user_read;
	}
}

void etk::FSNodeRight::setUserWritable(bool _newStatus) {
	// reset the flag :
	m_rights &= (0xFFFFFFFF - right_user_write);
	if (_newStatus == true) {
		m_rights |= right_user_write;
	}
}

void etk::FSNodeRight::setUserRunable(bool _newStatus) {
	// reset the flag :
	m_rights &= (0xFFFFFFFF - right_user_execute);
	if (_newStatus == true) {
		m_rights |= right_user_execute;
	}
}

bool etk::FSNodeRight::isGroupReadable() const {
	return ((m_rights&right_group_read)!=0)?true:false;
}

bool etk::FSNodeRight::isGroupWritable() const {
	return ((m_rights&right_group_write)!=0)?true:false;
}

bool etk::FSNodeRight::isGroupRunable() const {
	return ((m_rights&right_group_execute)!=0)?true:false;
}

void etk::FSNodeRight::setGroupReadable(bool _newStatus) {
	// reset the flag :
	m_rights &= (0xFFFFFFFF - right_group_read);
	if (true == _newStatus) {
		m_rights |= right_group_read;
	}
}

void etk::FSNodeRight::setGroupWritable(bool _newStatus) {
	// reset the flag :
	m_rights &= (0xFFFFFFFF - right_group_write);
	if (true == _newStatus) {
		m_rights |= right_group_write;
	}
}

void etk::FSNodeRight::setGroupRunable(bool _newStatus) {
	// reset the flag :
	m_rights &= (0xFFFFFFFF - right_group_execute);
	if (true == _newStatus) {
		m_rights |= right_group_execute;
	}
}

bool etk::FSNodeRight::isOtherReadable() const {
	return ((m_rights&right_other_read) != 0)?true:false;
}

bool etk::FSNodeRight::isOtherWritable() const {
	return ((m_rights&right_other_write) != 0)?true:false;
}

bool etk::FSNodeRight::isOtherRunable() const {
	return ((m_rights&right_other_execute) != 0)?true:false;
}

void etk::FSNodeRight::setOtherReadable(bool _newStatus) {
	// reset the flag:
	m_rights &= (0xFFFFFFFF - right_other_read);
	if (_newStatus == true) {
		m_rights |= right_other_read;
	}
}

void etk::FSNodeRight::setOtherWritable(bool _newStatus) {
	// reset the flag :
	m_rights &= (0xFFFFFFFF - right_other_write);
	if (_newStatus == true) {
		m_rights |= right_other_write;
	}
}

void etk::FSNodeRight::setOtherRunable(bool _newStatus) {
	// reset the flag :
	m_rights &= (0xFFFFFFFF - right_other_execute);
	if (_newStatus == true) {
		m_rights |= right_other_execute;
	}
}
#if __CPP_VERSION__ >= 2011
	std::u32string etk::FSNodeRight::getURight() const {
		return etk::to_u32string(getRight());
	}
#endif

std::string etk::FSNodeRight::getRight() const {
	std::string tmp;
	if (isUserReadable() == true) {
		tmp += "r";
	} else {
		tmp += "-";
	}
	if (isUserWritable() == true) {
		tmp += "w";
	} else {
		tmp += "-";
	}
	if (isUserRunable() == true) {
		tmp += "x";
	} else {
		tmp += "-";
	}
	if (isGroupReadable() == true) {
		tmp += "r";
	} else {
		tmp += "-";
	}
	if (isGroupWritable() == true) {
		tmp += "w";
	} else {
		tmp += "-";
	}
	if (isGroupRunable() == true) {
		tmp += "x";
	} else {
		tmp += "-";
	}
	if (isOtherReadable() == true) {
		tmp += "r";
	} else {
		tmp += "-";
	}
	if (isOtherWritable() == true) {
		tmp += "w";
	} else {
		tmp += "-";
	}
	if (isOtherRunable() == true) {
		tmp += "x";
	} else {
		tmp += "-";
	}
	return tmp;
}


std::ostream& etk::operator <<(std::ostream &_os, const etk::FSNodeRight &_obj) {
	_os << _obj.getRight();
	return _os;
};

