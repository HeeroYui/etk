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

int32_t strlen(const uniChar_t * data)
{
	if (NULL == data) {
		return 0;
	}
	int32_t iii=0;
	while (*data != 0) {
		data++;
		iii++;
		if (iii > 0x7FFFFFF0) {
			return iii;
		}
	}
	return iii;
}

#undef __class__
#define __class__	"etk::UString"

etk::CCout& etk::operator <<(etk::CCout &os, const etk::UString &obj)
{
	etk::Vector<char> output_UTF8;
	unicode::convertUnicodeToUtf8(obj.m_data, output_UTF8);
	output_UTF8.PushBack('\0');
	os << &output_UTF8[0];
	return os;
}

etk::UString::UString(void)
{
	//TK_INFO("new etk::UString()");
	m_data.PushBack('\0');
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

etk::UString::UString(const uniChar_t _inputData)
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

void etk::UString::Set(const int64_t& _inputData, etk::UString::printMode_te _mode, bool _preset)
{
	if (_preset==true && _mode != etk::UString::printModeString) {
		Set((uint64_t)_inputData, _mode, _preset);
		return;
	}
	uint64_t tmpData;
	if (_inputData < 0) {
		tmpData = (uint64_t)((int64_t)_inputData * (int64_t)(-1));
	} else {
		tmpData = _inputData;
	}
	if (_inputData < 0) {
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
	Set((uint64_t)tmpData, _mode, _preset);
	//TK_ERROR(" convert : " << _inputData << " in : " << *this);
}

void etk::UString::Set(const uint64_t& _inputData, etk::UString::printMode_te _mode, bool _preset)
{
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
	m_data.PushBack('\0');
	//TK_ERROR(" convert : " << _inputData << " in : " << *this);
}

// multiple element add
etk::UString::UString(const uniChar_t* _inputData, int32_t len)
{
	Set(_inputData, len);
}

etk::UString::UString(const char* _inputData, int32_t len)
{
	Set(_inputData, len);
}

etk::UString::UString(const etk::Vector<char>& _inputData)
{
	Set(_inputData);
}

etk::UString::UString(const etk::Vector<int8_t>& _inputData)
{
	Set(_inputData);
}

etk::UString::UString(const etk::Vector<uniChar_t>& _inputData)
{
	Set(_inputData);
}


void etk::UString::Set(const etk::Vector<char>& _inputData)
{
	if (_inputData.Size()==0) {
		Clear();
		return;
	}
	etk::Vector<uniChar_t> output_Unicode;
	unicode::convertUtf8ToUnicode(_inputData, output_Unicode);
	Set(output_Unicode);
}

void etk::UString::Set(const etk::Vector<int8_t>& _inputData)
{
	if (_inputData.Size()==0) {
		Clear();
		return;
	}
	etk::Vector<uniChar_t> output_Unicode;
	unicode::convertUtf8ToUnicode(_inputData, output_Unicode);
	Set(output_Unicode);
}


void etk::UString::Set(const etk::Vector<uniChar_t>& inputData)
{
	m_data = inputData;
	if (m_data.Size()>0) {
		if (m_data[m_data.Size()-1] != '\0') {
			m_data.PushBack('\0');
		}
	} else {
		m_data.PushBack('\0');
	}
	//TK_DEBUG("m_dataLen="<<m_dataLen << " m_dataLenUTF8="<<m_dataLenUTF8 << " description=" << m_data);
}

void etk::UString::Set(const char * inputData, int32_t len)
{
	if (NULL == inputData) {
		// nothing to add ... ==> clear all the data ...
		Clear();
		return;
	}
	// overwrite the len if needed : 
	if ((-1) == len) {
		len = strlen(inputData);
	}
	// convert the string
	etk::Vector<char> tmpChar;
	for (int32_t iii=0; iii<len; iii++) {
		tmpChar.PushBack(inputData[iii]);
	}
	// add it ...
	if (len != 0) {
		// remove the last '\0'
		m_data.PopBack();
		// copy the data ...
		unicode::convertUtf8ToUnicode(tmpChar, m_data);
	}
	// add the last '\0'
	m_data.PushBack('\0');
}

void etk::UString::Set(const uniChar_t * inputData, int32_t len)
{
	if (NULL == inputData) {
		// nothing to add ... ==> clear all the data ...
		Clear();
		return;
	}
	// overwrite the len if needed :
	if ((-1) == len) {
		len = strlen(inputData);
	}
	
	if (len != 0) {
		// remove the last '\0'
		m_data.PopBack();
		// copy the data ...
		m_data.PushBack(inputData, len);
	}
	// add the last '\0'
	m_data.PushBack('\0');
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
			uniChar_t elemA = m_data[iii].ChangeOrder();
			uniChar_t elemB = _obj.m_data[iii].ChangeOrder();
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
			uniChar_t elemA = m_data[iii].ChangeOrder();
			uniChar_t elemB = _obj.m_data[iii].ChangeOrder();
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
			uniChar_t elemA = m_data[iii].ChangeOrder();
			uniChar_t elemB = _obj.m_data[iii].ChangeOrder();
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
			uniChar_t elemA = m_data[iii].ChangeOrder();
			uniChar_t elemB = _obj.m_data[iii].ChangeOrder();
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
	if( this != &_obj ) {
		if (_obj.m_data.Size() != m_data.Size()) {
			//TK_DEBUG(" not the same size : " << _obj.m_data.Size() << "!=" << m_data.Size());
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


void etk::UString::Add(int32_t _currentID, const uniChar_t* _inputData)
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


void etk::UString::Add(int32_t _currentID, const uniChar_t _inputData)
{
	uniChar_t data[2];
	data[0] = _inputData;
	data[1] = 0;
	Add(_currentID, data);
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

int32_t etk::UString::FindForward(const uniChar_t _element, int32_t _startPos) const
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

int32_t etk::UString::FindBack(const uniChar_t _element, int32_t _startPos) const
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


etk::Vector<uniChar_t> etk::UString::GetVector(void)
{
	etk::Vector<uniChar_t> out = m_data;
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

bool etk::UString::ToBool(void) const
{
	if(    true == CompareNoCase("true")
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
	int32_t dotPos = -1;
	for (int32_t iii=0; iii<m_data.Size(); iii++) {
		if(    iii==0
		    && (    m_data[iii] == '-'
		         || m_data[iii] == '+') ) {
			if(m_data[iii] == '-') {
				isOdd = true;
			}
		} else {
			if (dotPos == -1) {
				if (m_data[iii] == '.') {
					dotPos = 1;
					// jump at the next element
					continue;
				}
			}
			if (true==m_data[iii].IsInteger()) {
				int32_t val = m_data[iii].ToInt32();
				double val2 = val;
				if (dotPos>=0) {
					ret += (val2*(((double)dotPos)*0.1));
					dotPos++;
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
	return ret;
}


float etk::UString::ToFloat(void) const
{
	return (float)ToDouble();
}
