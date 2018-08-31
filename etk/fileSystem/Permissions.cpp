/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */


#include <etk/os/FSNodeRight.hpp>
#include <etk/stdTools.hpp>
#include <etk/typeInfo.hpp>


#include <etk/typeInfo.hpp>
ETK_DECLARE_TYPE(etk::filesystem::Permissions);


// Right Flags:
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

ETK_DECLARE_TYPE(etk::filesystem::Permissions);

etk::filesystem::Permissions::Permissions(uint16_t _newRight) :
 m_rights(_newRight&0x01FF) {
	
}

uint16_t etk::filesystem::Permissions::getRight() const {
	return m_rights;
}

etk::filesystem::Permissions& etk::filesystem::Permissions::operator= (const etk::filesystem::Permissions &_obj ) {
	m_rights = _obj.m_rights;
	return *this;
}

etk::filesystem::Permissions& etk::filesystem::Permissions::operator= (const uint32_t _newVal) {
	m_rights = _newVal&0x01FF;
	return *this;
}

void etk::filesystem::Permissions::clear() {
	m_rights = 0;
}

bool etk::filesystem::Permissions::isUserReadable() const {
	return ((m_rights&right_user_read)!=0)?true:false;
}

bool etk::filesystem::Permissions::isUserWritable() const {
	return ((m_rights&right_user_write)!=0)?true:false;
}

bool etk::filesystem::Permissions::isUserRunable() const {
	return ((m_rights&right_user_execute)!=0)?true:false;
}

void etk::filesystem::Permissions::setUserReadable(bool _newStatus) {
	// reset the flag :
	m_rights &= (0xFFFFFFFF - right_user_read);
	if (_newStatus == true) {
		m_rights |= right_user_read;
	}
}

void etk::filesystem::Permissions::setUserWritable(bool _newStatus) {
	// reset the flag :
	m_rights &= (0xFFFFFFFF - right_user_write);
	if (_newStatus == true) {
		m_rights |= right_user_write;
	}
}

void etk::filesystem::Permissions::setUserRunable(bool _newStatus) {
	// reset the flag :
	m_rights &= (0xFFFFFFFF - right_user_execute);
	if (_newStatus == true) {
		m_rights |= right_user_execute;
	}
}

bool etk::filesystem::Permissions::isGroupReadable() const {
	return ((m_rights&right_group_read)!=0)?true:false;
}

bool etk::filesystem::Permissions::isGroupWritable() const {
	return ((m_rights&right_group_write)!=0)?true:false;
}

bool etk::filesystem::Permissions::isGroupRunable() const {
	return ((m_rights&right_group_execute)!=0)?true:false;
}

void etk::filesystem::Permissions::setGroupReadable(bool _newStatus) {
	// reset the flag :
	m_rights &= (0xFFFFFFFF - right_group_read);
	if (true == _newStatus) {
		m_rights |= right_group_read;
	}
}

void etk::filesystem::Permissions::setGroupWritable(bool _newStatus) {
	// reset the flag :
	m_rights &= (0xFFFFFFFF - right_group_write);
	if (true == _newStatus) {
		m_rights |= right_group_write;
	}
}

void etk::filesystem::Permissions::setGroupRunable(bool _newStatus) {
	// reset the flag :
	m_rights &= (0xFFFFFFFF - right_group_execute);
	if (true == _newStatus) {
		m_rights |= right_group_execute;
	}
}

bool etk::filesystem::Permissions::isOtherReadable() const {
	return ((m_rights&right_other_read) != 0)?true:false;
}

bool etk::filesystem::Permissions::isOtherWritable() const {
	return ((m_rights&right_other_write) != 0)?true:false;
}

bool etk::filesystem::Permissions::isOtherRunable() const {
	return ((m_rights&right_other_execute) != 0)?true:false;
}

void etk::filesystem::Permissions::setOtherReadable(bool _newStatus) {
	// reset the flag:
	m_rights &= (0xFFFFFFFF - right_other_read);
	if (_newStatus == true) {
		m_rights |= right_other_read;
	}
}

void etk::filesystem::Permissions::setOtherWritable(bool _newStatus) {
	// reset the flag :
	m_rights &= (0xFFFFFFFF - right_other_write);
	if (_newStatus == true) {
		m_rights |= right_other_write;
	}
}

void etk::filesystem::Permissions::setOtherRunable(bool _newStatus) {
	// reset the flag :
	m_rights &= (0xFFFFFFFF - right_other_execute);
	if (_newStatus == true) {
		m_rights |= right_other_execute;
	}
}

etk::String etk::filesystem::Permissions::getRight() const {
	etk::String tmp;
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


etk::Stream& etk::operator <<(etk::Stream &_os, const etk::filesystem::Permissions &_obj) {
	_os << _obj.getRight();
	return _os;
};

