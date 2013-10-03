/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */


#include <etk/types.h>
#include <etk/DebugInternal.h>
#include <etk/os/FSNodeRight.h>

// Right Flags :
enum {
	RIGHT_OTHER_EXECUTE = 1 << 0,
	RIGHT_OTHER_WRITE   = 1 << 1,
	RIGHT_OTHER_READ    = 1 << 2,
	RIGHT_GROUP_EXECUTE = 1 << 3,
	RIGHT_GROUP_WRITE   = 1 << 4,
	RIGHT_GROUP_READ    = 1 << 5,
	RIGHT_USER_EXECUTE  = 1 << 6,
	RIGHT_USER_WRITE    = 1 << 7,
	RIGHT_USER_READ     = 1 << 8,
};

etk::FSNodeRight::FSNodeRight(void) :
	m_rights(0)
{
	
}
etk::FSNodeRight::FSNodeRight(int16_t _newRight) :
	m_rights(_newRight&0x01FF)
{
	
}
// copy operator :
const etk::FSNodeRight& etk::FSNodeRight::operator= (const etk::FSNodeRight &_obj )
{
	m_rights = _obj.m_rights;
	return *this;
}

// set right :
const etk::FSNodeRight& etk::FSNodeRight::operator= (const int32_t _newVal )
{
	m_rights = _newVal&0x01FF;
	return *this;
}

// User
bool etk::FSNodeRight::isUserReadable(void) const
{
	return ((m_rights&RIGHT_USER_READ)!=0)?true:false;
}

bool etk::FSNodeRight::isUserWritable(void) const
{
	return ((m_rights&RIGHT_USER_WRITE)!=0)?true:false;
}

bool etk::FSNodeRight::isUserRunable(void) const
{
	return ((m_rights&RIGHT_USER_EXECUTE)!=0)?true:false;
}

void etk::FSNodeRight::setUserReadable(bool _newStatus)
{
	// reset the flag :
	m_rights &= (0xFFFFFFFF - RIGHT_USER_READ);
	if (true == _newStatus) {
		m_rights |= RIGHT_USER_READ;
	}
}

void etk::FSNodeRight::setUserWritable(bool _newStatus)
{
	// reset the flag :
	m_rights &= (0xFFFFFFFF - RIGHT_USER_WRITE);
	if (true == _newStatus) {
		m_rights |= RIGHT_USER_WRITE;
	}
}

void etk::FSNodeRight::setUserRunable(bool _newStatus)
{
	// reset the flag :
	m_rights &= (0xFFFFFFFF - RIGHT_USER_EXECUTE);
	if (true == _newStatus) {
		m_rights |= RIGHT_USER_EXECUTE;
	}
}

// group
bool etk::FSNodeRight::isGroupReadable(void) const
{
	return ((m_rights&RIGHT_GROUP_READ)!=0)?true:false;
}

bool etk::FSNodeRight::isGroupWritable(void) const
{
	return ((m_rights&RIGHT_GROUP_WRITE)!=0)?true:false;
}

bool etk::FSNodeRight::isGroupRunable(void) const
{
	return ((m_rights&RIGHT_GROUP_EXECUTE)!=0)?true:false;
}

void etk::FSNodeRight::setGroupReadable(bool _newStatus)
{
	// reset the flag :
	m_rights &= (0xFFFFFFFF - RIGHT_GROUP_READ);
	if (true == _newStatus) {
		m_rights |= RIGHT_GROUP_READ;
	}
}

void etk::FSNodeRight::setGroupWritable(bool _newStatus)
{
	// reset the flag :
	m_rights &= (0xFFFFFFFF - RIGHT_GROUP_WRITE);
	if (true == _newStatus) {
		m_rights |= RIGHT_GROUP_WRITE;
	}
}

void etk::FSNodeRight::setGroupRunable(bool _newStatus)
{
	// reset the flag :
	m_rights &= (0xFFFFFFFF - RIGHT_GROUP_EXECUTE);
	if (true == _newStatus) {
		m_rights |= RIGHT_GROUP_EXECUTE;
	}
}

// other
bool etk::FSNodeRight::isOtherReadable(void) const
{
	return ((m_rights&RIGHT_OTHER_READ) != 0)?true:false;
}

bool etk::FSNodeRight::isOtherWritable(void) const
{
	return ((m_rights&RIGHT_OTHER_WRITE) != 0)?true:false;
}

bool etk::FSNodeRight::isOtherRunable(void) const
{
	return ((m_rights&RIGHT_OTHER_EXECUTE) != 0)?true:false;
}

void etk::FSNodeRight::setOtherReadable(bool _newStatus)
{
	// reset the flag :
	m_rights &= (0xFFFFFFFF - RIGHT_OTHER_READ);
	if (true == _newStatus) {
		m_rights |= RIGHT_OTHER_READ;
	}
}

void etk::FSNodeRight::setOtherWritable(bool _newStatus)
{
	// reset the flag :
	m_rights &= (0xFFFFFFFF - RIGHT_OTHER_WRITE);
	if (true == _newStatus) {
		m_rights |= RIGHT_OTHER_WRITE;
	}
}

void etk::FSNodeRight::setOtherRunable(bool _newStatus)
{
	// reset the flag :
	m_rights &= (0xFFFFFFFF - RIGHT_OTHER_EXECUTE);
	if (true == _newStatus) {
		m_rights |= RIGHT_OTHER_EXECUTE;
	}
}
etk::UString etk::FSNodeRight::getRight(void) const
{
	etk::UString tmp;
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


etk::CCout& etk::operator <<(etk::CCout &_os, const etk::FSNodeRight &_obj)
{
	_os << _obj.getRight();
	return _os;
};

