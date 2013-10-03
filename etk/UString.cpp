/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/UString.h>
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
	output_UTF8.pushBack('\0');
	_os << &output_UTF8[0];
	return _os;
}

etk::CCout& etk::operator <<(etk::CCout& _os, const etk::Vector<etk::UString>& _obj)
{
	_os << "{";
	for (int32_t iii=0; iii< _obj.size(); iii++) {
		if (iii>0) {
			_os << " ~ ";
		}
		_os << _obj[iii];
	}
	_os << "}";
	return _os;
}

etk::UString::UString(void)
{
	//TK_INFO("new etk::UString()");
	m_data.pushBack(etk::UniChar::Null);
}


etk::UString::UString(const char* _data, unicode::charset_te _inputCharset)
{
	// TODO : Change this ...
	etk::Vector<char> transformData;
	while (*_data != '\0') {
		transformData.pushBack(*_data);
		_data++;
	}
	m_data.clear();
	if (unicode::EDN_CHARSET_UTF8==_inputCharset) {
		unicode::convertUtf8ToUnicode(transformData, m_data);
	} else {
		unicode::convertIsoToUnicode(_inputCharset, transformData, m_data);
	}
	if(    0 == m_data.size()
	    || m_data[m_data.size()-1]!=etk::UniChar::Null) {
		m_data.pushBack(etk::UniChar::Null);
	}
}


// single element adding
etk::UString::UString(const bool _inputData, etk::UString::printMode_te _mode, bool _preset)
{
	m_data.clear();
	if (_preset==true) {
		switch(_mode) {
			case etk::UString::printModeBinary :
				m_data.pushBack('0');
				m_data.pushBack('b');
				break;
			case etk::UString::printModeOctal :
				m_data.pushBack('0');
				m_data.pushBack('o');
				break;
			case etk::UString::printModeDecimal :
				break;
			case etk::UString::printModeHexadecimal :
				m_data.pushBack('0');
				m_data.pushBack('x');
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
				m_data.pushBack('1');
			} else {
				m_data.pushBack('0');
			}
			break;
		default:
		case etk::UString::printModeString :
			if (true == _inputData) {
				m_data.pushBack('t');
				m_data.pushBack('r');
				m_data.pushBack('u');
				m_data.pushBack('e');
			} else {
				m_data.pushBack('f');
				m_data.pushBack('a');
				m_data.pushBack('l');
				m_data.pushBack('s');
				m_data.pushBack('e');
			}
			break;
	}
	m_data.pushBack(etk::UniChar::Null);
}

etk::UString::UString(const etk::UString& _obj)
{
	//etk_INFO("Constructeur de recopie");
	m_data = _obj.m_data;
}

etk::UString::UString(const etk::UniChar& _inputData)
{
	m_data.pushBack(_inputData);
	m_data.pushBack(etk::UniChar::Null);
}

etk::UString::UString(const float _inputData)
{
	// TODO : Rework this ...
	char tmpVal[256];
	// generate the UString : 
	sprintf(tmpVal, "%f", _inputData);
	// set the internal data : 
	set(tmpVal);
}

etk::UString::UString(const double _inputData)
{
	// TODO : Rework this ...
	char tmpVal[256];
	// generate the UString : 
	sprintf(tmpVal, "%lf", _inputData);
	int32_t len=strlen(tmpVal);
	if (NULL!=strchr(tmpVal, '.')) {
		//have a '.'
		// remove the .000000000 at the end of the string
		for (int32_t iii=len-1; iii>=0 ; --iii) {
			if (tmpVal[iii] == '0') {
				tmpVal[iii] = '\0';
			} else {
				if (tmpVal[iii] == '.') {
					tmpVal[iii] = '\0';
				}
				break;
			}
		}
	}
	// set the internal data : 
	set(tmpVal);
}

// TODO : Does not work at all ...
/*
etk::UString etk::UString::WrapHidenChar(void) const
{
	etk::UString out;
	for (int32_t iii=0; iii<Size(); iii++) {
		if (m_data[iii]=='\r') {
			out += "\r";
		} else if (m_data[iii]=='\t') {
			out += "\t";
		} else {
			out += m_data[iii];
		}
	}
	return out;
}
*/


void etk::UString::setNumber(bool _negative, const uint64_t& _inputData, etk::UString::printMode_te _mode, bool _preset, int32_t _leadingZero)
{
	m_data.clear();
	if (true==_negative) {
		if (_mode == etk::UString::printModeString) {
			m_data.pushBack('l');
			m_data.pushBack('e');
			m_data.pushBack('s');
			m_data.pushBack('s');
			m_data.pushBack(' ');
		} else {
			m_data.pushBack('-');
		}
	}
	if (_preset==true) {
		switch(_mode) {
			case etk::UString::printModeBinary :
				m_data.pushBack('0');
				m_data.pushBack('b');
				break;
			case etk::UString::printModeOctal :
				m_data.pushBack('0');
				m_data.pushBack('o');
				break;
			case etk::UString::printModeDecimal :
				break;
			case etk::UString::printModeHexadecimal :
				m_data.pushBack('0');
				m_data.pushBack('x');
				break;
			default:
			case etk::UString::printModeString :
				break;
		}
	}
	if (_mode == etk::UString::printModeString) {
		m_data.pushBack('T');
		m_data.pushBack('O');
		m_data.pushBack('D');
		m_data.pushBack('O');
		m_data.pushBack('.');
		m_data.pushBack('.');
		m_data.pushBack('.');
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
		//printf("lmkmlj %llX\n", _inputData);
		//printf("lmkmlk %s\n", ploppp);
		uint64_t tmpVal = _inputData;
		etk::UString tmpString;
		while (tmpVal>0) {
			uint64_t quotient = tmpVal / base;
			uint64_t rest = tmpVal - quotient*base;
			if (rest<=9) {
				tmpString.add(0,(char)(rest+'0'));
			} else {
				tmpString.add(0,(char)(rest-10+'A'));
			}
			tmpVal = quotient;
		}
		if (tmpString.size() == 0) {
			tmpString = "0";
		}
		for (int32_t iii=tmpString.size(); iii<_leadingZero; iii++){
			tmpString.add(0,'0');
		}
		*this += tmpString;
		
		//TK_ERROR ("        " << ploppp);
	}
	if (m_data.size()==0) {
		m_data.pushBack(etk::UniChar::Null);
	} else if (m_data[m_data.size()-1]!=etk::UniChar::Null) {
		m_data.pushBack(etk::UniChar::Null);
	}
	//TK_ERROR(" convert : " << _inputData << " in : " << *this << " len=" << m_data.Size());
}

void etk::UString::set(const int64_t& _inputData, etk::UString::printMode_te _mode, bool _preset, int32_t _leadingZero)
{
	if (_preset==true && _mode != etk::UString::printModeString) {
		setNumber(false, (uint64_t)_inputData, _mode, _preset, _leadingZero);
		return;
	}
	if (_inputData < 0) {
		uint64_t tmpData = (uint64_t)((int64_t)_inputData * (int64_t)(-1));
		setNumber(true, (uint64_t)tmpData, _mode, _preset, _leadingZero);
	} else {
		setNumber(false, (uint64_t)_inputData, _mode, _preset, _leadingZero);
	}
}

void etk::UString::set(const uint64_t& _inputData, etk::UString::printMode_te _mode, bool _preset, int32_t _leadingZero)
{
	setNumber(false, (uint64_t)_inputData, _mode, _preset, _leadingZero);
}

// multiple element add
etk::UString::UString(const etk::UniChar* _inputData, int32_t _len)
{
	set(_inputData, _len);
}

etk::UString::UString(const char* _inputData, int32_t _len)
{
	set(_inputData, _len);
}

etk::UString::UString(const etk::Vector<char>& _inputData)
{
	set(_inputData);
}

etk::UString::UString(const etk::Vector<int8_t>& _inputData)
{
	set(_inputData);
}

etk::UString::UString(const etk::Vector<etk::UniChar>& _inputData)
{
	set(_inputData);
}


void etk::UString::set(const etk::Vector<char>& _inputData)
{
	if (_inputData.size()==0) {
		clear();
		return;
	}
	etk::Vector<etk::UniChar> output_Unicode;
	unicode::convertUtf8ToUnicode(_inputData, output_Unicode);
	set(output_Unicode);
}

void etk::UString::set(const etk::Vector<int8_t>& _inputData)
{
	if (_inputData.size()==0) {
		clear();
		return;
	}
	etk::Vector<etk::UniChar> output_Unicode;
	unicode::convertUtf8ToUnicode(_inputData, output_Unicode);
	set(output_Unicode);
}


void etk::UString::set(const etk::Vector<etk::UniChar>& _inputData)
{
	m_data = _inputData;
	if (m_data.size()>0) {
		if (m_data[m_data.size()-1] != etk::UniChar::Null) {
			m_data.pushBack(etk::UniChar::Null);
		}
	} else {
		m_data.pushBack(etk::UniChar::Null);
	}
	//TK_DEBUG("m_dataLen="<<m_dataLen << " m_dataLenUTF8="<<m_dataLenUTF8 << " description=" << m_data);
}

void etk::UString::set(const char* _inputData, int32_t _len)
{
	// clear all the data
	m_data.clear();
	if (NULL == _inputData) {
		m_data.pushBack(etk::UniChar::Null);
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
		tmpChar.pushBack(_inputData[iii]);
	}
	// add it ...
	if (_len != 0) {
		// copy the data ...
		unicode::convertUtf8ToUnicode(tmpChar, m_data);
	}
	if (m_data.size()==0) {
		m_data.pushBack(etk::UniChar::Null);
	} else if (m_data[m_data.size()-1]!=etk::UniChar::Null) {
		m_data.pushBack(etk::UniChar::Null);
	}
}

void etk::UString::set(const etk::UniChar* _inputData, int32_t _len)
{
	// clear all the data
	m_data.clear();
	if (NULL == _inputData) {
		m_data.pushBack(etk::UniChar::Null);
		// nothing to add ... ==> just exit
		return;
	}
	// overwrite the len if needed :
	if ((-1) == _len) {
		_len = strlen(_inputData);
	}
	if (_len != 0) {
		// copy the data ...
		m_data.pushBack(_inputData, _len);
	}
	if (m_data.size()==0) {
		m_data.pushBack(etk::UniChar::Null);
	} else if (m_data[m_data.size()-1]!=etk::UniChar::Null) {
		m_data.pushBack(etk::UniChar::Null);
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
		for (int32_t iii=0; iii < m_data.size() && iii < _obj.m_data.size(); iii++) {
			//TK_DEBUG("    compare : '" << (char)m_data[iii] << "'>'" << (char)_obj.m_data[iii] << "' ==> " << changeOrder(m_data[iii]) << ">" << changeOrder(_obj.m_data[iii]) << "");
			etk::UniChar elemA = m_data[iii].changeOrder();
			etk::UniChar elemB = _obj.m_data[iii].changeOrder();
			if (elemA != elemB) {
				if (elemA > elemB) {
					return true;
				}
				return false;
			}
		}
		if (m_data.size() > _obj.m_data.size()) {
			return true;
		}
	}
	return false;
}

bool etk::UString::operator>= (const etk::UString& _obj) const
{
	if( this != &_obj ) {
		for (int32_t iii=0; iii < m_data.size() && iii < _obj.m_data.size(); iii++) {
			etk::UniChar elemA = m_data[iii].changeOrder();
			etk::UniChar elemB = _obj.m_data[iii].changeOrder();
			if (elemA != elemB) {
				if (elemA > elemB) {
					return true;
				}
				return false;
			}
		}
		if (m_data.size() >= _obj.m_data.size()) {
			return true;
		}
	}
	return false;
}

bool etk::UString::operator< (const etk::UString& _obj) const
{
	if( this != &_obj ) {
		for (int32_t iii=0; iii < m_data.size() && iii < _obj.m_data.size(); iii++) {
			etk::UniChar elemA = m_data[iii].changeOrder();
			etk::UniChar elemB = _obj.m_data[iii].changeOrder();
			if (elemA != elemB) {
				if (elemA < elemB) {
					return true;
				}
				return false;
			}
		}
		if (m_data.size() < _obj.m_data.size()) {
			return true;
		}
	}
	return false;
}

bool etk::UString::operator<= (const etk::UString& _obj) const
{
	if( this != &_obj ) {
		for (int32_t iii=0; iii < m_data.size() && iii < _obj.m_data.size(); iii++) {
			etk::UniChar elemA = m_data[iii].changeOrder();
			etk::UniChar elemB = _obj.m_data[iii].changeOrder();
			if (elemA != elemB) {
				if (elemA < elemB) {
					return true;
				}
				return false;
			}
		}
		if (m_data.size() <= _obj.m_data.size()) {
			return true;
		}
	}
	return false;
}


bool etk::UString::operator== (const etk::UString& _obj) const
{
	if( this != &_obj ) {
		if (_obj.m_data.size() != m_data.size()) {
			return false;
		}
		for (int32_t iii= 0; iii<m_data.size(); iii++) {
			if (_obj.m_data[iii]!= m_data[iii]){
				return false;
			}
		}
		return true;
	}
	return true;
}

bool etk::UString::compareNoCase(const etk::UString& _obj) const
{
	if( this != &_obj ) {
		if (_obj.m_data.size() != m_data.size()) {
			return false;
		}
		for (int32_t iii= 0; iii<m_data.size(); iii++) {
			if (false==m_data[iii].compareNoCase(_obj.m_data[iii])){
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
	if (0 < _obj.size()) {
		// remove the last '\0'
		m_data.popBack();
		// copy the data ...
		m_data += _obj.m_data;
		// This previous include the \0 in case of the 2 UString are different...
		if( this == &_obj ) {
			// add the removed end UString
			m_data.pushBack(etk::UniChar::Null);
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


bool etk::UString::isEmpty(void) const
{
	if(1 >= m_data.size() ) {
		return true;
	} else {
		return false;
	}
}


int32_t etk::UString::size(void) const
{
	if (m_data.size() == 0) {
		return 0;
	} else {
		return m_data.size() - 1;
	}
}


void etk::UString::add(int32_t _currentID, const char* _inputData)
{
	etk::UString tmpString(_inputData);
	add(_currentID, tmpString.pointer() );
}


void etk::UString::add(int32_t _currentID, const etk::UniChar* _inputData)
{
	// get the input lenght
	int32_t len = strlen(_inputData);
	if (0 == len) {
		TK_WARNING("no data to add on the current UString");
		return;
	} else if (_currentID < 0) {
		TK_WARNING("Curent ID(" << _currentID << ") < 0   ==> Add at the start");
		_currentID = 0;
	} else if (_currentID > size() ) {
		TK_ERROR("Curent ID(" << _currentID << ") > maxSize ... (" << size() << ")  ==> add at the end ...");
		m_data.pushBack(_inputData, len);
		return;
	}
	m_data.insert(_currentID, _inputData, len);
}


void etk::UString::add(int32_t _currentID, const etk::UniChar _inputData)
{
	etk::UniChar data[2];
	data[0] = _inputData;
	data[1] = etk::UniChar::Null;
	add(_currentID, data);
}

void etk::UString::append(const etk::UniChar& _inputData)
{
	m_data.popBack();
	m_data.pushBack(_inputData);
	m_data.pushBack(etk::UniChar::Null);
}


void etk::UString::remove(int32_t _currentID, int32_t _len)
{
	if (0 >= _len) {
		TK_ERROR("no data to remove on the current UString");
		return;
	}
	// TODO : check the size of the data
	m_data.eraseLen(_currentID, _len);
}


void etk::UString::clear(void)
{
	m_data.clear();
	m_data.pushBack(etk::UniChar::Null);
}

int32_t etk::UString::findForward(const etk::UniChar _element, int32_t _startPos) const
{
	if (_startPos < 0) {
		_startPos = 0;
	} else if (_startPos >= size() ) {
		return -1;
	}
	for (int32_t iii=_startPos; iii< size(); iii++) {
		if (m_data[iii] == _element) {
			return iii;
		}
	}
	return -1;
}

int32_t etk::UString::findBack(const etk::UniChar _element, int32_t _startPos) const
{
	if (_startPos < 0) {
		return -1;
	} else if (_startPos >= size() ) {
		_startPos = size();
	}
	for (int32_t iii=_startPos; iii>=0; iii--) {
		if (m_data[iii] == _element) {
			return iii;
		}
	}
	return -1;
}


etk::UString etk::UString::extract(int32_t _posStart, int32_t _posEnd) const
{
	etk::UString out;
	if (_posStart < 0) {
		_posStart = 0;
	} else if (_posStart >= size() ) {
		return out;
	}
	if (_posEnd < 0) {
		return out;
	} else if (_posEnd >= size() ) {
		_posEnd = size();
	}
	out.m_data = m_data.extract(_posStart, _posEnd);
	out.m_data.pushBack(etk::UniChar::Null);
	return out;
}

etk::UString etk::UString::extractLine(int32_t _pos) const
{
	// search back : '\n'
	int32_t startPos = findBack('\n', _pos);
	if (startPos == _pos) {
		startPos = 0;
	} else {
		startPos++;
	}
	// search forward : '\n'
	int32_t stopPos = _pos;
	if (m_data[_pos] != '\n') {
		stopPos = findForward('\n', _pos);
		if (stopPos == _pos) {
			stopPos = size();
		}
	}
	etk::UString out;
	if (startPos < 0) {
		startPos = 0;
	} else if (startPos >= size() ) {
		return out;
	}
	if (stopPos < 0) {
		return out;
	} else if (stopPos >= size() ) {
		stopPos = size();
	}
	out.m_data = m_data.extract(startPos, stopPos);
	out.m_data.pushBack(etk::UniChar::Null);
	return out;
}

etk::Vector<etk::UniChar> etk::UString::getVector(void)
{
	etk::Vector<etk::UniChar> out = m_data;
	out.popBack();
	return out;
}


bool etk::UString::startWith(const etk::UString& _data, bool _caseSensitive) const
{
	if (_data.size() == 0) {
		return false;
	}
	if (_data.size() > size()) {
		return false;
	}
	if (true == _caseSensitive) {
		for (int32_t iii=0; iii<_data.size(); iii++) {
			if (_data[iii] != m_data[iii]) {
				return false;
			}
		}
	} else {
		for (int32_t iii=0; iii<_data.size(); iii++) {
			if (false==m_data[iii].compareNoCase(_data[iii])) {
				return false;
			}
		}
	}
	return true;
}


bool etk::UString::endWith(const etk::UString& _data, bool _caseSensitive) const
{
	if (_data.size() == 0) {
		return false;
	}
	if (_data.size() > size()) {
		return false;
	}
	if (true == _caseSensitive) {
		for( int32_t iii=size()-1, jjj=_data.size()-1;
		     iii>=0 && jjj>=0;
		     iii--, jjj--) {
			if (_data[jjj] != m_data[iii]) {
				return false;
			}
		}
	} else {
		for( int32_t iii=size()-1, jjj=_data.size()-1;
		     iii>=0 && jjj>=0;
		     iii--, jjj--) {
			if (false==m_data[iii].compareNoCase(_data[jjj])) {
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
	tmpData.clear();
	unicode::convertUnicodeToUtf8(m_data, tmpData);
	tmpVar.setValue(tmpData);
	return tmpVar;
}

etk::Vector<etk::UString> etk::UString::split(const etk::UniChar& _val)
{
	etk::Vector<etk::UString> list;
	int32_t lastStartPos=0;
	for(int32_t iii=0; iii<size(); iii++) {
		if (m_data[iii]==_val) {
			list.pushBack(extract(lastStartPos, iii));
			lastStartPos = iii+1;
		}
	}
	if (lastStartPos<size()) {
		list.pushBack(extract(lastStartPos));
	}
	return list;
}


void etk::UString::replace(const etk::UniChar& _out, const etk::UniChar& _in)
{
	for(int32_t iii=0 ; iii<m_data.size() ; iii++) {
		if (m_data[iii]==_out) {
			m_data[iii]=_in;
		}
	}
}

void etk::UString::lower(void)
{
	for( int32_t iii=0 ; iii<m_data.size() ; iii++) {
		m_data[iii].lower();
	}
}

etk::UString etk::UString::toLower(void) const
{
	etk::UString ret = *this;
	ret.lower();
	return ret;
}

void etk::UString::upper(void)
{
	for( int32_t iii=0 ; iii<m_data.size() ; iii++) {
		m_data[iii].upper();
	}
}

etk::UString etk::UString::toUpper(void) const
{
	etk::UString ret = *this;
	ret.upper();
	return ret;
}

bool etk::UString::toBool(void) const
{
	if(    true == compareNoCase("true")
	    || true == compareNoCase("enable")
	    || true == compareNoCase("yes")
	    || *this == "1") {
		return true;
	}
	return false;
}

int64_t etk::UString::toInt64(void) const
{
	int64_t ret=0;
	bool isOdd = false;
	for (int32_t iii=0; iii<m_data.size(); iii++) {
		if(    iii==0
		    && (    m_data[iii] == '-'
		         || m_data[iii] == '+') ) {
			if(m_data[iii] == '-') {
				isOdd = true;
			}
		} else {
			if (true==m_data[iii].isInteger()) {
				int32_t val = m_data[iii].toInt32();
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

uint64_t etk::UString::toUInt64(void) const
{
	uint64_t ret=0;
	for (int32_t iii=0; iii<m_data.size(); iii++) {
		if(    iii==0
		    && (    m_data[iii] == '-'
		         || m_data[iii] == '+') ) {
			if(m_data[iii] == '-') {
				return 0;
			}
		} else {
			if (true==m_data[iii].isInteger()) {
				int32_t val = m_data[iii].toInt32();
				ret = ret*10 + val;
			} else {
				break;
			}
		}
	}
	return ret;
}

int32_t etk::UString::toInt32(void) const
{
	int64_t parse = toInt64();
	return etk_avg((int64_t)INT32_MIN, parse, (int64_t)INT32_MAX);
}
int16_t etk::UString::toInt16(void) const
{
	int64_t parse = toInt64();
	return etk_avg((int64_t)INT16_MIN, parse, (int64_t)INT16_MAX);
}
int8_t etk::UString::toInt8(void) const
{
	int64_t parse = toInt64();
	return etk_avg((int64_t)INT8_MIN, parse, (int64_t)INT8_MAX);
}

uint32_t etk::UString::toUInt32(void) const
{
	uint64_t parse = toUInt64();
	return etk_avg((int64_t)0, parse, (int64_t)UINT32_MAX);
}
uint16_t etk::UString::toUInt16(void) const
{
	uint64_t parse = toUInt64();
	return etk_avg((int64_t)0, parse, (int64_t)UINT16_MAX);
}
uint8_t etk::UString::toUInt8(void) const
{
	uint64_t parse = toUInt64();
	return etk_avg((int64_t)0, parse, (int64_t)UINT8_MAX);
}

double etk::UString::toDouble(void) const
{
	double ret=0;
	bool isOdd = false;
	float dotPos = -1;
	for (int32_t iii=0; iii<m_data.size(); iii++) {
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
			if (true==m_data[iii].isInteger()) {
				int32_t val = m_data[iii].toInt32();
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


float etk::UString::toFloat(void) const
{
	return (float)toDouble();
}
