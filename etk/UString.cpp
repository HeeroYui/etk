/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/UString.h>
#include <etk/os/Memory.h>
#include <etk/unicode.h>
#include <etk/Debug.h>

int32_t strlen(const etk::UniChar * _data)
{
	if (NULL == _data) {
		return 0;
	}
	int32_t iii=0;
	while (*_data != 0) {
		_data++;
		iii++;
		if (iii > 0x7FFFFFF0) {
			return iii;
		}
	}
	return iii;
}

#undef __class__
#define __class__	"etk::UString"

etk::CCout& etk::operator <<(etk::CCout& _os, const etk::UString& _obj)
{
	etk::Vector<char> output_UTF8;
	unicode::convertUnicodeToUtf8(_obj.m_data, output_UTF8);
	output_UTF8.PushBack('\0');
	_os << &output_UTF8[0];
	return _os;
}

etk::UString::UString(void)
{
	//TK_INFO("new etk::UString()");
	m_data.PushBack('\0');
}


etk::UString::UString(const char* _data, unicode::charset_te _inputCharset)
{
	// TODO : Change this ...
	etk::Vector<char> transformData;
	while (*_data != '\0') {
		transformData.PushBack(*_data);
		_data++;
	}
	m_data.Clear();
	if (unicode::EDN_CHARSET_UTF8==_inputCharset) {
		unicode::convertUtf8ToUnicode(transformData, m_data);
	} else {
		unicode::convertIsoToUnicode(_inputCharset, transformData, m_data);
	}
	if(    0 == m_data.Size()
	    || m_data[m_data.Size()-1]!='\0') {
		m_data.PushBack('\0');
	}
}


// single element adding
etk::UString::UString(const bool _inputData, etk::UString::printMode_te _mode, bool _preset)
{
	m_data.Clear();
	if (_preset==true) {
		switch(_mode) {
			case etk::UString::printModeBinary :
				m_data.PushBack('0');
				m_data.PushBack('b');
				break;
			case etk::UString::printModeOctal :
				m_data.PushBack('0');
				m_data.PushBack('o');
				break;
			case etk::UString::printModeDecimal :
				break;
			case etk::UString::printModeHexadecimal :
				m_data.PushBack('0');
				m_data.PushBack('x');
				break;
			default:
			case etk::UString::printModeString :
				break;
		}
	}
	switch(_mode) {
		case etk::UString::printModeBinary :
		case etk::UString::printModeOctal :
		case etk::UString::printModeDecimal :
		case etk::UString::printModeHexadecimal :
			if (true == _inputData) {
				m_data.PushBack('1');
			} else {
				m_data.PushBack('0');
			}
			break;
		default:
		case etk::UString::printModeString :
			if (true == _inputData) {
				m_data.PushBack('t');
				m_data.PushBack('r');
				m_data.PushBack('u');
				m_data.PushBack('e');
			} else {
				m_data.PushBack('f');
				m_data.PushBack('a');
				m_data.PushBack('l');
				m_data.PushBack('s');
				m_data.PushBack('e');
			}
			break;
	}
	m_data.PushBack('\0');
}

etk::UString::UString(const etk::UString& _obj)
{
	//etk_INFO("Constructeur de recopie");
	m_data = _obj.m_data;
}

etk::UString::UString(const etk::UniChar& _inputData)
{
	m_data.PushBack(_inputData);
	m_data.PushBack('\0');
}

etk::UString::UString(const float _inputData)
{
	// TODO : Rework this ...
	char tmpVal[256];
	// generate the UString : 
	sprintf(tmpVal, "%f", _inputData);
	// set the internal data : 
	Set(tmpVal);
}

etk::UString::UString(const double _inputData)
{
	// TODO : Rework this ...
	char tmpVal[256];
	// generate the UString : 
	sprintf(tmpVal, "%lf", _inputData);
	// set the internal data : 
	Set(tmpVal);
}

void etk::UString::SetNumber(bool _negative, const uint64_t& _inputData, etk::UString::printMode_te _mode, bool _preset)
{
	m_data.Clear();
	if (true==_negative) {
		if (_mode == etk::UString::printModeString) {
			m_data.PushBack('l');
			m_data.PushBack('e');
			m_data.PushBack('s');
			m_data.PushBack('s');
			m_data.PushBack(' ');
		} else {
			m_data.PushBack('-');
		}
	}
	if (_preset==true) {
		switch(_mode) {
			case etk::UString::printModeBinary :
				m_data.PushBack('0');
				m_data.PushBack('b');
				break;
			case etk::UString::printModeOctal :
				m_data.PushBack('0');
				m_data.PushBack('o');
				break;
			case etk::UString::printModeDecimal :
				break;
			case etk::UString::printModeHexadecimal :
				m_data.PushBack('0');
				m_data.PushBack('x');
				break;
			default:
			case etk::UString::printModeString :
				break;
		}
	}
	if (_mode == etk::UString::printModeString) {
		m_data.PushBack('T');
		m_data.PushBack('O');
		m_data.PushBack('D');
		m_data.PushBack('O');
		m_data.PushBack('.');
		m_data.PushBack('.');
		m_data.PushBack('.');
	} else {
		int32_t base=8;
		//char ploppp[256]="";
		switch(_mode) {
			case etk::UString::printModeBinary :
				base=2;
				break;
			case etk::UString::printModeOctal :
				//sprintf(ploppp, "%llo", _inputData);
				base=8;
				break;
			default:
			case etk::UString::printModeDecimal :
				//sprintf(ploppp, "%llu", _inputData);
				base=10;
				break;
			case etk::UString::printModeHexadecimal :
				//sprintf(ploppp, "%llx", _inputData);
				base=16;
				break;
		}
		uint64_t tmpVal = _inputData;
		etk::UString tmpString;
		while (tmpVal>0) {
			uint64_t quotient = tmpVal / base;
			uint64_t rest = tmpVal - quotient*base;
			tmpString.Add(0,(rest+'0'));
			tmpVal = quotient;
		}
		if (tmpString.Size() == 0) {
			m_data.PushBack('0');
		} else {
			*this += tmpString;
		}
		//TK_ERROR ("        " << ploppp);
	}
	if (m_data.Size()==0) {
		m_data.PushBack('\0');
	} else if (m_data[m_data.Size()-1]!='\0') {
		m_data.PushBack('\0');
	}
	//TK_ERROR(" convert : " << _inputData << " in : " << *this << " len=" << m_data.Size());
}

void etk::UString::Set(const int64_t& _inputData, etk::UString::printMode_te _mode, bool _preset)
{
	if (_preset==true && _mode != etk::UString::printModeString) {
		SetNumber(false, (uint64_t)_inputData, _mode, _preset);
		return;
	}
	if (_inputData < 0) {
		uint64_t tmpData = (uint64_t)((int64_t)_inputData * (int64_t)(-1));
		SetNumber(true, (uint64_t)tmpData, _mode, _preset);
	} else {
		SetNumber(false, (uint64_t)_inputData, _mode, _preset);
	}
}

void etk::UString::Set(const uint64_t& _inputData, etk::UString::printMode_te _mode, bool _preset)
{
	SetNumber(false, (uint64_t)_inputData, _mode, _preset);
}

// multiple element add
etk::UString::UString(const etk::UniChar* _inputData, int32_t _len)
{
	Set(_inputData, _len);
}

etk::UString::UString(const char* _inputData, int32_t _len)
{
	Set(_inputData, _len);
}

etk::UString::UString(const etk::Vector<char>& _inputData)
{
	Set(_inputData);
}

etk::UString::UString(const etk::Vector<int8_t>& _inputData)
{
	Set(_inputData);
}

etk::UString::UString(const etk::Vector<etk::UniChar>& _inputData)
{
	Set(_inputData);
}


void etk::UString::Set(const etk::Vector<char>& _inputData)
{
	if (_inputData.Size()==0) {
		Clear();
		return;
	}
	etk::Vector<etk::UniChar> output_Unicode;
	unicode::convertUtf8ToUnicode(_inputData, output_Unicode);
	Set(output_Unicode);
}

void etk::UString::Set(const etk::Vector<int8_t>& _inputData)
{
	if (_inputData.Size()==0) {
		Clear();
		return;
	}
	etk::Vector<etk::UniChar> output_Unicode;
	unicode::convertUtf8ToUnicode(_inputData, output_Unicode);
	Set(output_Unicode);
}


void etk::UString::Set(const etk::Vector<etk::UniChar>& _inputData)
{
	m_data = _inputData;
	if (m_data.Size()>0) {
		if (m_data[m_data.Size()-1] != '\0') {
			m_data.PushBack('\0');
		}
	} else {
		m_data.PushBack('\0');
	}
	//TK_DEBUG("m_dataLen="<<m_dataLen << " m_dataLenUTF8="<<m_dataLenUTF8 << " description=" << m_data);
}

void etk::UString::Set(const char* _inputData, int32_t _len)
{
	// clear all the data
	m_data.Clear();
	if (NULL == _inputData) {
		m_data.PushBack('\0');
		// nothing to add ... ==> just exit
		return;
	}
	// overwrite the len if needed : 
	if ((-1) == _len) {
		_len = strlen(_inputData);
	}
	// convert the string
	etk::Vector<char> tmpChar;
	for (int32_t iii=0; iii<_len; iii++) {
		// clip the string in case of error of len ...
		if (_inputData[iii]=='\0') {
			break;
		}
		tmpChar.PushBack(_inputData[iii]);
	}
	// add it ...
	if (_len != 0) {
		// copy the data ...
		unicode::convertUtf8ToUnicode(tmpChar, m_data);
	}
	if (m_data.Size()==0) {
		m_data.PushBack('\0');
	} else if (m_data[m_data.Size()-1]!='\0') {
		m_data.PushBack('\0');
	}
}

void etk::UString::Set(const etk::UniChar* _inputData, int32_t _len)
{
	// clear all the data
	m_data.Clear();
	if (NULL == _inputData) {
		m_data.PushBack('\0');
		// nothing to add ... ==> just exit
		return;
	}
	// overwrite the len if needed :
	if ((-1) == _len) {
		_len = strlen(_inputData);
	}
	if (_len != 0) {
		// copy the data ...
		m_data.PushBack(_inputData, _len);
	}
	if (m_data.Size()==0) {
		m_data.PushBack('\0');
	} else if (m_data[m_data.Size()-1]!='\0') {
		m_data.PushBack('\0');
	}
}


const etk::UString& etk::UString::operator= (const etk::UString& _obj )
{
	//TK_INFO("OPERATOR de recopie");
	if( this != &_obj ) {
		m_data = _obj.m_data;
	}
	return *this;
}


bool etk::UString::operator> (const etk::UString& _obj) const
{
	if( this != &_obj ) {
		for (int32_t iii=0; iii < m_data.Size() && iii < _obj.m_data.Size(); iii++) {
			//TK_DEBUG("    compare : '" << (char)m_data[iii] << "'>'" << (char)_obj.m_data[iii] << "' ==> " << changeOrder(m_data[iii]) << ">" << changeOrder(_obj.m_data[iii]) << "");
			etk::UniChar elemA = m_data[iii].ChangeOrder();
			etk::UniChar elemB = _obj.m_data[iii].ChangeOrder();
			if (elemA != elemB) {
				if (elemA > elemB) {
					return true;
				}
				return false;
			}
		}
		if (m_data.Size() > _obj.m_data.Size()) {
			return true;
		}
	}
	return false;
}

bool etk::UString::operator>= (const etk::UString& _obj) const
{
	if( this != &_obj ) {
		for (int32_t iii=0; iii < m_data.Size() && iii < _obj.m_data.Size(); iii++) {
			etk::UniChar elemA = m_data[iii].ChangeOrder();
			etk::UniChar elemB = _obj.m_data[iii].ChangeOrder();
			if (elemA != elemB) {
				if (elemA > elemB) {
					return true;
				}
				return false;
			}
		}
		if (m_data.Size() >= _obj.m_data.Size()) {
			return true;
		}
	}
	return false;
}

bool etk::UString::operator< (const etk::UString& _obj) const
{
	if( this != &_obj ) {
		for (int32_t iii=0; iii < m_data.Size() && iii < _obj.m_data.Size(); iii++) {
			etk::UniChar elemA = m_data[iii].ChangeOrder();
			etk::UniChar elemB = _obj.m_data[iii].ChangeOrder();
			if (elemA != elemB) {
				if (elemA < elemB) {
					return true;
				}
				return false;
			}
		}
		if (m_data.Size() < _obj.m_data.Size()) {
			return true;
		}
	}
	return false;
}

bool etk::UString::operator<= (const etk::UString& _obj) const
{
	if( this != &_obj ) {
		for (int32_t iii=0; iii < m_data.Size() && iii < _obj.m_data.Size(); iii++) {
			etk::UniChar elemA = m_data[iii].ChangeOrder();
			etk::UniChar elemB = _obj.m_data[iii].ChangeOrder();
			if (elemA != elemB) {
				if (elemA < elemB) {
					return true;
				}
				return false;
			}
		}
		if (m_data.Size() <= _obj.m_data.Size()) {
			return true;
		}
	}
	return false;
}


bool etk::UString::operator== (const etk::UString& _obj) const
{
	//TK_DEBUG("Compare : \"" << _obj << "\"==\"" << *this << "\"");
	if( this != &_obj ) {
		if (_obj.m_data.Size() != m_data.Size()) {
			/*TK_DEBUG(" not the same size : " << _obj.m_data.Size() << "!=" << m_data.Size());
			for (int32_t iii=0; iii<etk_max(m_data.Size(),_obj.m_data.Size()); iii++) {
				if (iii< m_data.Size() && iii<_obj.m_data.Size()) {
					TK_DEBUG("     element : '" << m_data[iii] << "' !! '" << _obj.m_data[iii] << "'");
				} else if (iii< m_data.Size()) {
					TK_DEBUG("     element : '" << m_data[iii] << "' !! '-'");
				} else {
					TK_DEBUG("     element : '-' !! '" << _obj.m_data[iii] << "'");
				}
			}*/
			return false;
		}
		for (int32_t iii= 0; iii<m_data.Size(); iii++) {
			//TK_DEBUG("     check : " << _obj.m_data[iii] << "!=" << m_data[iii]);
			if (_obj.m_data[iii]!= m_data[iii]){
				return false;
			}
		}
		return true;
	}
	return true;
}

bool etk::UString::CompareNoCase(const etk::UString& _obj) const
{
	if( this != &_obj ) {
		if (_obj.m_data.Size() != m_data.Size()) {
			//TK_DEBUG(" not the same size : " << _obj.m_data.Size() << "!=" << m_data.Size());
			return false;
		}
		for (int32_t iii= 0; iii<m_data.Size(); iii++) {
			//TK_DEBUG("     check : " << _obj.m_data[iii] << "!=" << m_data[iii]);
			if (false==m_data[iii].CompareNoCase(_obj.m_data[iii])){
				return false;
			}
		}
		return true;
	}
	return true;
}


bool etk::UString::operator!= (const etk::UString& _obj) const
{
	return !(*this == _obj);
}


const etk::UString& etk::UString::operator+= (const etk::UString &_obj)
{
	if (0 < _obj.Size()) {
		// remove the last '\0'
		m_data.PopBack();
		// copy the data ...
		m_data += _obj.m_data;
		// This previous include the \0 in case of the 2 UString are different...
		if( this == &_obj ) {
			// add the removed end UString
			m_data.PushBack('\0');
		}
	}
	return *this;
}

/*
const etk::UString& etk::UString::operator+= (const etk::UniChar& _obj)
{
	// remove the last '\0'
	m_data.PopBack();
	// copy the data ...
	m_data.PushBack(_obj);
	// add the last '\0' element
	m_data.PushBack('\0');
	return *this;
}
*/

etk::UString etk::UString::operator+ (const etk::UString &_obj) const
{
	etk::UString temp;
	temp += *this;
	temp += _obj;
	return temp;
}


bool etk::UString::IsEmpty(void) const
{
	if(1 >= m_data.Size() ) {
		return true;
	} else {
		return false;
	}
}


int32_t etk::UString::Size(void) const
{
	if (m_data.Size() == 0) {
		return 0;
	} else {
		return m_data.Size() - 1;
	}
}


void etk::UString::Add(int32_t _currentID, const char* _inputData)
{
	etk::UString tmpString(_inputData);
	Add(_currentID, tmpString.pointer() );
}


void etk::UString::Add(int32_t _currentID, const etk::UniChar* _inputData)
{
	// get the input lenght
	int32_t len = strlen(_inputData);
	if (0 == len) {
		TK_WARNING("no data to add on the current UString");
		return;
	} else if (_currentID < 0) {
		TK_WARNING("Curent ID(" << _currentID << ") < 0   ==> Add at the start");
		_currentID = 0;
	} else if (_currentID > Size() ) {
		TK_ERROR("Curent ID(" << _currentID << ") > maxSize ... (" << Size() << ")  ==> add at the end ...");
		m_data.PushBack(_inputData, len);
		return;
	}
	m_data.Insert(_currentID, _inputData, len);
}


void etk::UString::Add(int32_t _currentID, const etk::UniChar _inputData)
{
	etk::UniChar data[2];
	data[0] = _inputData;
	data[1] = 0;
	Add(_currentID, data);
}

void etk::UString::Append(const etk::UniChar& _inputData)
{
	m_data.PushBack(_inputData);
}


void etk::UString::Remove(int32_t _currentID, int32_t _len)
{
	if (0 >= _len) {
		TK_ERROR("no data to remove on the current UString");
		return;
	}
	// TODO : check the size of the data
	m_data.EraseLen(_currentID, _len);
}


void etk::UString::Clear(void)
{
	m_data.Clear();
	m_data.PushBack('\0');
}

int32_t etk::UString::FindForward(const etk::UniChar _element, int32_t _startPos) const
{
	if (_startPos < 0) {
		_startPos = 0;
	} else if (_startPos >= Size() ) {
		return -1;
	}
	for (int32_t iii=_startPos; iii< Size(); iii++) {
		if (m_data[iii] == _element) {
			return iii;
		}
	}
	return -1;
}

int32_t etk::UString::FindBack(const etk::UniChar _element, int32_t _startPos) const
{
	if (_startPos < 0) {
		return -1;
	} else if (_startPos >= Size() ) {
		_startPos = Size();
	}
	for (int32_t iii=_startPos; iii>=0; iii--) {
		if (m_data[iii] == _element) {
			return iii;
		}
	}
	return -1;
}


etk::UString etk::UString::Extract(int32_t _posStart, int32_t _posEnd) const
{
	etk::UString out;
	if (_posStart < 0) {
		_posStart = 0;
	} else if (_posStart >= Size() ) {
		return out;
	}
	if (_posEnd < 0) {
		return out;
	} else if (_posEnd >= Size() ) {
		_posEnd = Size();
	}
	out.m_data = m_data.Extract(_posStart, _posEnd);
	out.m_data.PushBack('\0');
	return out;
}


etk::Vector<etk::UniChar> etk::UString::GetVector(void)
{
	etk::Vector<etk::UniChar> out = m_data;
	out.PopBack();
	return out;
}


bool etk::UString::StartWith(const etk::UString& _data, bool _caseSensitive) const
{
	if (_data.Size() == 0) {
		return false;
	}
	if (_data.Size() > Size()) {
		return false;
	}
	if (true == _caseSensitive) {
		for (int32_t iii=0; iii<_data.Size(); iii++) {
			if (_data[iii] != m_data[iii]) {
				return false;
			}
		}
	} else {
		for (int32_t iii=0; iii<_data.Size(); iii++) {
			if (false==m_data[iii].CompareNoCase(_data[iii])) {
				return false;
			}
		}
	}
	return true;
}


bool etk::UString::EndWith(const etk::UString& _data, bool _caseSensitive) const
{
	if (_data.Size() == 0) {
		return false;
	}
	if (_data.Size() > Size()) {
		return false;
	}
	if (true == _caseSensitive) {
		for( int32_t iii=Size()-1, jjj=_data.Size()-1;
		     iii>=0 && jjj>=0;
		     iii--, jjj--) {
			if (_data[jjj] != m_data[iii]) {
				return false;
			}
		}
	} else {
		for( int32_t iii=Size()-1, jjj=_data.Size()-1;
		     iii>=0 && jjj>=0;
		     iii--, jjj--) {
			if (false==m_data[iii].CompareNoCase(_data[jjj])) {
				return false;
			}
		}
	}
	return true;
}


etk::Char etk::UString::c_str(void) const
{
	etk::Char tmpVar;
	etk::Vector<char> tmpData;
	// UTF8 generation :
	tmpData.Clear();
	unicode::convertUnicodeToUtf8(m_data, tmpData);
	tmpVar.SetValue(tmpData);
	return tmpVar;
}


void etk::UString::Lower(void)
{
	for( int32_t iii=0 ; iii<m_data.Size() ; iii++) {
		m_data[iii].Lower();
	}
}

etk::UString etk::UString::ToLower(void) const
{
	etk::UString ret = *this;
	ret.Lower();
	return ret;
}

void etk::UString::Upper(void)
{
	for( int32_t iii=0 ; iii<m_data.Size() ; iii++) {
		m_data[iii].Upper();
	}
}

etk::UString etk::UString::ToUpper(void) const
{
	etk::UString ret = *this;
	ret.Upper();
	return ret;
}

bool etk::UString::ToBool(void) const
{
	if(    true == CompareNoCase("true")
	    || true == CompareNoCase("enable")
	    || true == CompareNoCase("yes")
	    || *this == "1") {
		return true;
	}
	return false;
}

int64_t etk::UString::ToInt64(void) const
{
	int64_t ret=0;
	bool isOdd = false;
	for (int32_t iii=0; iii<m_data.Size(); iii++) {
		if(    iii==0
		    && (    m_data[iii] == '-'
		         || m_data[iii] == '+') ) {
			if(m_data[iii] == '-') {
				isOdd = true;
			}
		} else {
			if (true==m_data[iii].IsInteger()) {
				int32_t val = m_data[iii].ToInt32();
				ret = ret*10 + val;
			} else {
				break;
			}
		}
	}
	if (isOdd == true) {
		ret *= -1;
	}
	return ret;
}

uint64_t etk::UString::ToUInt64(void) const
{
	uint64_t ret=0;
	for (int32_t iii=0; iii<m_data.Size(); iii++) {
		if(    iii==0
		    && (    m_data[iii] == '-'
		         || m_data[iii] == '+') ) {
			if(m_data[iii] == '-') {
				return 0;
			}
		} else {
			if (true==m_data[iii].IsInteger()) {
				int32_t val = m_data[iii].ToInt32();
				ret = ret*10 + val;
			} else {
				break;
			}
		}
	}
	return ret;
}

int32_t etk::UString::ToInt32(void) const
{
	int64_t parse = ToInt64();
	return etk_avg((int64_t)INT32_MIN, parse, (int64_t)INT32_MAX);
}
int16_t etk::UString::ToInt16(void) const
{
	int64_t parse = ToInt64();
	return etk_avg((int64_t)INT16_MIN, parse, (int64_t)INT16_MAX);
}
int8_t etk::UString::ToInt8(void) const
{
	int64_t parse = ToInt64();
	return etk_avg((int64_t)INT8_MIN, parse, (int64_t)INT8_MAX);
}

uint32_t etk::UString::ToUInt32(void) const
{
	uint64_t parse = ToUInt64();
	return etk_avg((int64_t)0, parse, (int64_t)UINT32_MAX);
}
uint16_t etk::UString::ToUInt16(void) const
{
	uint64_t parse = ToUInt64();
	return etk_avg((int64_t)0, parse, (int64_t)UINT16_MAX);
}
uint8_t etk::UString::ToUInt8(void) const
{
	uint64_t parse = ToUInt64();
	return etk_avg((int64_t)0, parse, (int64_t)UINT8_MAX);
}

double etk::UString::ToDouble(void) const
{
	double ret=0;
	bool isOdd = false;
	float dotPos = -1;
	for (int32_t iii=0; iii<m_data.Size(); iii++) {
		if(    iii==0
		    && (    m_data[iii] == '-'
		         || m_data[iii] == '+') ) {
			if(m_data[iii] == '-') {
				isOdd = true;
			}
		} else {
			TK_VERBOSE( *this << " curent val " << m_data[iii] << "out=" << ret);
			if (dotPos == -1) {
				if (m_data[iii] == '.') {
					dotPos = 0.1;
					// jump at the next element
					continue;
				}
			}
			if (true==m_data[iii].IsInteger()) {
				int32_t val = m_data[iii].ToInt32();
				double val2 = val;
				if (dotPos>0) {
					ret += val2*dotPos;
					dotPos/=10.0;
				} else {
					ret = ret*10.0 + val2;
				}
			} else {
				break;
			}
		}
	}
	if (isOdd == true) {
		ret *= -1.0;
	}
	TK_VERBOSE( *this << " end =" << ret);
	return ret;
}


float etk::UString::ToFloat(void) const
{
	return (float)ToDouble();
}
