/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

// see : http://unicode.org/fr/charts/symbols.html#CombiningDiacriticalMarks

#include <etk/types.h>
#include <etk/debug.h>
#include <etk/unicodeTable.h>
#include <etk/unicode.h>



void unicode::convertIsoToUnicode(charset_te _inputCharset, const char _input_ISO, etk::UChar & _output_Unicode)
{
	switch(_inputCharset)
	{
		case EDN_CHARSET_ISO_8859_1:  _output_Unicode.set(tableIso8859_1[(uint32_t)_input_ISO&0xFF]); break;
		case EDN_CHARSET_ISO_8859_2:  _output_Unicode.set(tableIso8859_2[(uint32_t)_input_ISO&0xFF]); break;
		case EDN_CHARSET_ISO_8859_3:  _output_Unicode.set(tableIso8859_3[(uint32_t)_input_ISO&0xFF]); break;
		case EDN_CHARSET_ISO_8859_4:  _output_Unicode.set(tableIso8859_4[(uint32_t)_input_ISO&0xFF]); break;
		case EDN_CHARSET_ISO_8859_5:  _output_Unicode.set(tableIso8859_5[(uint32_t)_input_ISO&0xFF]); break;
		case EDN_CHARSET_ISO_8859_6:  _output_Unicode.set(tableIso8859_6[(uint32_t)_input_ISO&0xFF]); break;
		case EDN_CHARSET_ISO_8859_7:  _output_Unicode.set(tableIso8859_7[(uint32_t)_input_ISO&0xFF]); break;
		case EDN_CHARSET_ISO_8859_8:  _output_Unicode.set(tableIso8859_8[(uint32_t)_input_ISO&0xFF]); break;
		case EDN_CHARSET_ISO_8859_9:  _output_Unicode.set(tableIso8859_9[(uint32_t)_input_ISO&0xFF]); break;
		case EDN_CHARSET_ISO_8859_10: _output_Unicode.set(tableIso8859_10[(uint32_t)_input_ISO&0xFF]); break;
		case EDN_CHARSET_ISO_8859_11: _output_Unicode.set(tableIso8859_11[(uint32_t)_input_ISO&0xFF]); break;
		case EDN_CHARSET_ISO_8859_13: _output_Unicode.set(tableIso8859_13[(uint32_t)_input_ISO&0xFF]); break;
		case EDN_CHARSET_ISO_8859_14: _output_Unicode.set(tableIso8859_14[(uint32_t)_input_ISO&0xFF]); break;
		case EDN_CHARSET_ISO_8859_15: _output_Unicode.set(tableIso8859_15[(uint32_t)_input_ISO&0xFF]); break;
		default :
			TK_WARNING("Unknow charset ... " << _inputCharset);
			_output_Unicode = '?';
			break;
	}
}


void unicode::convertUnicodeToIso(charset_te _inputCharset, const etk::UChar _input_Unicode, char & _output_ISO)
{
	const uint32_t *tmpTable = NULL;
	switch(_inputCharset)
	{
		case EDN_CHARSET_ISO_8859_1:		tmpTable = tableIso8859_1;		break;
		case EDN_CHARSET_ISO_8859_2:		tmpTable = tableIso8859_2;		break;
		case EDN_CHARSET_ISO_8859_3:		tmpTable = tableIso8859_3;		break;
		case EDN_CHARSET_ISO_8859_4:		tmpTable = tableIso8859_4;		break;
		case EDN_CHARSET_ISO_8859_5:		tmpTable = tableIso8859_5;		break;
		case EDN_CHARSET_ISO_8859_6:		tmpTable = tableIso8859_6;		break;
		case EDN_CHARSET_ISO_8859_7:		tmpTable = tableIso8859_7;		break;
		case EDN_CHARSET_ISO_8859_8:		tmpTable = tableIso8859_8;		break;
		case EDN_CHARSET_ISO_8859_9:		tmpTable = tableIso8859_9;		break;
		case EDN_CHARSET_ISO_8859_10:		tmpTable = tableIso8859_10;		break;
		case EDN_CHARSET_ISO_8859_11:		tmpTable = tableIso8859_11;		break;
		case EDN_CHARSET_ISO_8859_13:		tmpTable = tableIso8859_13;		break;
		case EDN_CHARSET_ISO_8859_14:		tmpTable = tableIso8859_14;		break;
		case EDN_CHARSET_ISO_8859_15:		tmpTable = tableIso8859_15;		break;
		default :
			TK_WARNING("Unknow charset ... " <<  _inputCharset);
			_output_ISO = '?';
			return;
	}
	int32_t i;
	for (i=0; i<256; i++) {
		if (tmpTable[i] == _input_Unicode.get()) {
			_output_ISO = (char)i;
			return;
		}
	}
}


int32_t unicode::convertIsoToUnicode(charset_te _inputCharset, const etk::Vector<char>& _input_ISO, etk::Vector<etk::UChar>& _output_Unicode)
{
	_output_Unicode.clear();
	etk::UChar output;
	for(int32_t iii=0; iii<_input_ISO.size(); iii++) {
		convertIsoToUnicode(_inputCharset, (char)_input_ISO[iii], output);
		_output_Unicode.pushBack(output);
	}
	if (_output_Unicode.size() == 0) {
		_output_Unicode.pushBack(0);
	} else if (_output_Unicode[_output_Unicode.size()-1] != 0) {
		_output_Unicode.pushBack(0);
	}
	return _output_Unicode.size();
}

int32_t unicode::convertIsoToUnicode(charset_te _inputCharset, const etk::Vector<int8_t>& _input_ISO, etk::Vector<etk::UChar>& _output_Unicode)
{
	_output_Unicode.clear();
	etk::UChar output;
	for(int32_t iii=0; iii<_input_ISO.size(); iii++) {
		convertIsoToUnicode(_inputCharset, (char)_input_ISO[iii], output);
		_output_Unicode.pushBack(output);
	}
	if (_output_Unicode.size() == 0) {
		_output_Unicode.pushBack(0);
	} else if (_output_Unicode[_output_Unicode.size()-1] != 0) {
		_output_Unicode.pushBack(0);
	}
	return _output_Unicode.size();
}


int32_t unicode::convertUnicodeToIso(charset_te _inputCharset, const etk::Vector<etk::UChar>& _input_Unicode, etk::Vector<char>&    _output_ISO)
{
	_output_ISO.clear();
	char output[10];
	for(int32_t iii=0; iii<_input_Unicode.size(); iii++) {
		_input_Unicode[iii].getUtf8(output);
		char * tmp = output;
		while(*tmp != '\0') {
			_output_ISO.pushBack(*tmp);
			tmp++;
		}
	}
	_output_ISO.pushBack(0);
	return _output_ISO.size();
}

int32_t unicode::convertUnicodeToIso(charset_te _inputCharset, const etk::Vector<etk::UChar>& _input_Unicode, etk::Vector<int8_t>&    _output_ISO)
{
	_output_ISO.clear();
	char output[10];
	for(int32_t iii=0; iii<_input_Unicode.size(); iii++) {
		_input_Unicode[iii].getUtf8(output);
		char * tmp = output;
		while(*tmp != '\0') {
			_output_ISO.pushBack(*tmp);
			tmp++;
		}
	}
	_output_ISO.pushBack(0);
	return _output_ISO.size();
}



int32_t unicode::convertUnicodeToUtf8(const etk::Vector<etk::UChar>& _input_Unicode, etk::Vector<char>& _output_UTF8)
{
	char output[10];
	
	for (int32_t iii=0; iii<_input_Unicode.size(); iii++) {
		_input_Unicode[iii].getUtf8(output);
		char * tmp = output ;
		while (*tmp != '\0') {
			_output_UTF8.pushBack(*tmp);
			tmp++;
		}
	}
	_output_UTF8.pushBack('\0');
	return _output_UTF8.size()-1;
}

int32_t unicode::convertUnicodeToUtf8(const etk::Vector<etk::UChar>& _input_Unicode, etk::Vector<int8_t>& _output_UTF8)
{
	char output[10];
	
	for (int32_t iii=0; iii<_input_Unicode.size(); iii++) {
		_input_Unicode[iii].getUtf8(output);
		char * tmp = output ;
		while (*tmp != '\0') {
			_output_UTF8.pushBack((int8_t)*tmp);
			tmp++;
		}
	}
	_output_UTF8.pushBack('\0');
	return _output_UTF8.size()-1;
}


int32_t unicode::convertUtf8ToUnicode(const etk::Vector<char>& _input_UTF8, etk::Vector<etk::UChar>& _output_Unicode)
{
	char tmpData[20];
	int32_t pos = 0;
	while (pos < _input_UTF8.size()) {
		int32_t lenMax = _input_UTF8.size() - pos;
		//4 case
		if (    1<=lenMax
		     && 0x00 == (_input_UTF8[pos+0] & 0x80) )
		{
			tmpData[0] = _input_UTF8[pos+0];
			tmpData[1] = '\0';
			pos += 1;
		} else if (    2<=lenMax
		            && 0xC0 == (_input_UTF8[pos+0] & 0xE0)
		            && 0x80 == (_input_UTF8[pos+1] & 0xC0) ) {
			tmpData[0] = _input_UTF8[pos+0];
			tmpData[1] = _input_UTF8[pos+1];
			tmpData[2] = '\0';
			pos += 2;
		} else if (    3<=lenMax
		            && 0xE0 == (_input_UTF8[pos+0] & 0xF0)
		            && 0x80 == (_input_UTF8[pos+1] & 0xC0)
		            && 0x80 == (_input_UTF8[pos+2] & 0xC0)) {
			tmpData[0] = _input_UTF8[pos+0];
			tmpData[1] = _input_UTF8[pos+1];
			tmpData[2] = _input_UTF8[pos+2];
			tmpData[3] = '\0';
			pos += 3;
		} else if (    4<=lenMax
		            && 0xF0 == (_input_UTF8[pos+0] & 0xF8)
		            && 0x80 == (_input_UTF8[pos+1] & 0xC0)
		            && 0x80 == (_input_UTF8[pos+2] & 0xC0)
		            && 0x80 == (_input_UTF8[pos+3] & 0xC0)) {
			tmpData[0] = _input_UTF8[pos+0];
			tmpData[1] = _input_UTF8[pos+1];
			tmpData[2] = _input_UTF8[pos+2];
			tmpData[3] = _input_UTF8[pos+3];
			tmpData[4] = '\0';
			pos += 4;
		} else {
			tmpData[0] = '\0';
			pos += 1;
		}
		etk::UChar tmpUnicode;
		tmpUnicode.setUtf8(tmpData);
		_output_Unicode.pushBack(tmpUnicode);
	}
	return 0;
}

int32_t unicode::convertUtf8ToUnicode(const etk::Vector<int8_t>& _input_UTF8, etk::Vector<etk::UChar>& _output_Unicode)
{
	char tmpData[20];
	int32_t pos = 0;
	while (pos < _input_UTF8.size()) {
		int32_t lenMax = _input_UTF8.size() - pos;
		//4 case
		if (    1<=lenMax
		     && 0x00 == (_input_UTF8[pos+0] & 0x80) )
		{
			tmpData[0] = _input_UTF8[pos+0];
			tmpData[1] = '\0';
			pos += 1;
		} else if (    2<=lenMax
		            && 0xC0 == (_input_UTF8[pos+0] & 0xE0)
		            && 0x80 == (_input_UTF8[pos+1] & 0xC0) ) {
			tmpData[0] = _input_UTF8[pos+0];
			tmpData[1] = _input_UTF8[pos+1];
			tmpData[2] = '\0';
			pos += 2;
		} else if (    3<=lenMax
		            && 0xE0 == (_input_UTF8[pos+0] & 0xF0)
		            && 0x80 == (_input_UTF8[pos+1] & 0xC0)
		            && 0x80 == (_input_UTF8[pos+2] & 0xC0)) {
			tmpData[0] = _input_UTF8[pos+0];
			tmpData[1] = _input_UTF8[pos+1];
			tmpData[2] = _input_UTF8[pos+2];
			tmpData[3] = '\0';
			pos += 3;
		} else if (    4<=lenMax
		            && 0xF0 == (_input_UTF8[pos+0] & 0xF8)
		            && 0x80 == (_input_UTF8[pos+1] & 0xC0)
		            && 0x80 == (_input_UTF8[pos+2] & 0xC0)
		            && 0x80 == (_input_UTF8[pos+3] & 0xC0)) {
			tmpData[0] = _input_UTF8[pos+0];
			tmpData[1] = _input_UTF8[pos+1];
			tmpData[2] = _input_UTF8[pos+2];
			tmpData[3] = _input_UTF8[pos+3];
			tmpData[4] = '\0';
			pos += 4;
		} else {
			tmpData[0] = '\0';
			pos += 1;
		}
		etk::UChar tmpUnicode;
		tmpUnicode.setUtf8(tmpData);
		_output_Unicode.pushBack(tmpUnicode);
	}
	return 0;
}

int32_t unicode::convertUtf8ToUnicode(const char * _input_UTF8, etk::Vector<etk::UChar>& _output_Unicode)
{
	char tmpData[20];
	int32_t pos = 0;
	if (NULL == _input_UTF8) {
		return 0;
	}
	int32_t len = strlen(_input_UTF8);
	while (pos < len) {
		int32_t lenMax = len - pos;
		//4 case
		if (    1<=lenMax
		     && 0x00 == (_input_UTF8[pos+0] & 0x80) )
		{
			tmpData[0] = _input_UTF8[pos+0];
			tmpData[1] = '\0';
			pos += 1;
		} else if (    2<=lenMax
		            && 0xC0 == (_input_UTF8[pos+0] & 0xE0)
		            && 0x80 == (_input_UTF8[pos+1] & 0xC0) ) {
			tmpData[0] = _input_UTF8[pos+0];
			tmpData[1] = _input_UTF8[pos+1];
			tmpData[2] = '\0';
			pos += 2;
		} else if (    3<=lenMax
		            && 0xE0 == (_input_UTF8[pos+0] & 0xF0)
		            && 0x80 == (_input_UTF8[pos+1] & 0xC0)
		            && 0x80 == (_input_UTF8[pos+2] & 0xC0)) {
			tmpData[0] = _input_UTF8[pos+0];
			tmpData[1] = _input_UTF8[pos+1];
			tmpData[2] = _input_UTF8[pos+2];
			tmpData[3] = '\0';
			pos += 3;
		} else if (    4<=lenMax
		            && 0xF0 == (_input_UTF8[pos+0] & 0xF8)
		            && 0x80 == (_input_UTF8[pos+1] & 0xC0)
		            && 0x80 == (_input_UTF8[pos+2] & 0xC0)
		            && 0x80 == (_input_UTF8[pos+3] & 0xC0)) {
			tmpData[0] = _input_UTF8[pos+0];
			tmpData[1] = _input_UTF8[pos+1];
			tmpData[2] = _input_UTF8[pos+2];
			tmpData[3] = _input_UTF8[pos+3];
			tmpData[4] = '\0';
			pos += 4;
		} else {
			tmpData[0] = '\0';
			pos += 1;
		}
		etk::UChar tmpUnicode;
		tmpUnicode.setUtf8(tmpData);
		_output_Unicode.pushBack(tmpUnicode);
	}
	return 0;
}


// Transform ISO <==> UTF-8
void unicode::convertIsoToUtf8(charset_te _inputCharset, const char _input_ISO, char * _output_UTF8)
{
	etk::UChar tmpUnicode;
	// concert Iso in UniCode
	convertIsoToUnicode(_inputCharset, _input_ISO, tmpUnicode );
	// convert UniCode in Utf-8
	tmpUnicode.getUtf8(_output_UTF8);
}


void unicode::convertUtf8ToIso(charset_te _inputCharset, const char * _input_UTF8, char & _output_ISO)
{
	etk::UChar tmpUnicode;
	// convert Utf-8 in UniCode
	tmpUnicode.setUtf8(_input_UTF8);
	// concert UniCode in Iso
	convertUnicodeToIso(_inputCharset, tmpUnicode, _output_ISO);
}


int32_t unicode::convertIsoToUtf8(charset_te _inputCharset, const etk::Vector<char>& _input_ISO, etk::Vector<char>& _output_UTF8)
{
	TK_WARNING("TODO : not coded...");
	return 0;
}


int32_t unicode::convertUtf8ToIso(charset_te _inputCharset, const etk::Vector<char>& _input_UTF8, etk::Vector<char>& _output_ISO)
{
	TK_WARNING("TODO : not coded...");
	return 0;
}

void unicode::utf8_SizeElement(const char * _data, int32_t _lenMax , uint8_t &_size, bool &_baseValid)
{
	TK_ASSERT(0 <= _lenMax, "size can not be < 0 ...");
	if (0 > _lenMax) {
		_size = 0;
		_baseValid = false;
		return;
	}
	//4 case
	if (	1<=_lenMax
		&&	0x00 == (_data[0] & 0x80) ) {
		// One Char Element
		_size = 1;
		_baseValid = true;
	} else if(		2<=_lenMax
				&&	0xC0 == (_data[0] & 0xE0)
				&&	0x80 == (_data[1] & 0xC0) ) {
		_size = 2;
		_baseValid = true;
	} else if(		3<=_lenMax
				&&	0xE0 == (_data[0] & 0xF0)
				&&	0x80 == (_data[1] & 0xC0)
				&&	0x80 == (_data[2] & 0xC0)) {
		_size = 3;
		_baseValid = true;
	} else if(		4<=_lenMax
				&&	0xF0 == (_data[0] & 0xF8)
				&&	0x80 == (_data[1] & 0xC0)
				&&	0x80 == (_data[2] & 0xC0)
				&&	0x80 == (_data[3] & 0xC0)) {
		_size = 4;
		_baseValid = true;
	} else {
		// return only one error Caracter ...
		_baseValid = false;
		_size = 1;
	}
}

#if 0 // Remove for the moment ...
/**
 * @brief Get the number of element of the previous UTF8 char (in the curent Buffer) 
 *
 * @param[in]			data			pointer on the curent CHAR string (pointer on the allocated buffer) (the curent char is not check)
 * @param[out]			size			Nb of char use in this UTF8 [0..4]
 * @param[out]			baseValid		true : the ase format of the UTF8 is CORRECT
 *
 * @return ---
 *
 */
static void Utf8_SizePreviousElement(const char * data, int32_t lenMax, uint8_t &size, bool &baseValid)
{
	EDN_ASSERT(0 <= lenMax, "size can not be < 0 ...");
	if (0 > lenMax) {
		size = 0;
		baseValid = false;
		return;
	}
	//4 case
	if (	1<=lenMax
		&&	0x00 == (data[-1] & 0x80) ) {
		// One Char Element
		size = 1;
		baseValid = true;
	} else if(		2<=lenMax
				&&	0xC0 == (data[-2] & 0xE0)
				&&	0x80 == (data[-1] & 0xC0) ) {
		size = 2;
		baseValid = true;
	} else if(		3<=lenMax
				&&	0xE0 == (data[-3] & 0xF0)
				&&	0x80 == (data[-2] & 0xC0)
				&&	0x80 == (data[-1] & 0xC0)) {
		size = 3;
		baseValid = true;
	} else if(		4<=lenMax
				&&	0xF0 == (data[-4] & 0xF8)
				&&	0x80 == (data[-3] & 0xC0)
				&&	0x80 == (data[-2] & 0xC0)
				&&	0x80 == (data[-1] & 0xC0)) {
		size = 4;
		baseValid = true;
	} else {
		// return only one error Caracter ...
		baseValid = false;
		size = 1;
	}
}
#endif

/**
 * @brief 
 *
 * @param[in,out] 
 *
 * @return 
 *
 */
 /*
static uint32_t Utf8_GetValue(UTF8Element_ts &Element)
{
	uint32_t value = 0;
	const char * data = m_data + Element.CharPosition;
	//4 case
	switch(Element.CharSize)
	{
		case 1:
			value = data[0] & 0x7F;
			break;
		case 2:
			value  = (data[0] & 0x1F)<< 6;
			value +=  data[1] & 0x3F;
			break;
		case 3:
			value  = (data[0] & 0x0F)<< 12;
			value += (data[1] & 0x3F)<< 6;
			value +=  data[2] & 0x3F;
			break;
		case 4:
			value  = (data[0] & 0x07)<< 18;
			value += (data[1] & 0x3F)<< 12;
			value += (data[2] & 0x3F)<< 6;
			value +=  data[3] & 0x3F;
			break;
		default:
			// return only one error Caracter ...
			EDN_ASSERT(false, "impossible case....");
			break;
	}
	// check the validity of the UTF8 ...
	if(		(		0xD800 <= value 
				&&	0xDFFF >= value )
		||	(		0xFDD0 <= value 
				&&	0xFDEF >= value )
		||	(		0xFFFE <= value 
				&&	0xFFFF >= value )
		||	(		0x1FFFE <= value 
				&&	0x1FFFF >= value )
		||	(		0x2FFFE <= value 
				&&	0xDFFFF >= value )
		||	(		0xEFFFE <= value 
				&&	0xEFFFF >= value )
		||	(		0xFFFFE <= value 
				&&	0xFFFFF >= value )
		||	(		0x10FFFE <= value 
				&&	0x10FFFF >= value ) )
	{
		// overwrite the UTF8 validity ==> this is not a diaplayable element
		Element.ValidUTF8 = false;
		return value;
	}
	
	return value;
}
*/


int32_t unicode::strUtf8Len(const char *input_UTF8)
{
	int32_t count = 0;
	int32_t size = strlen(input_UTF8);
	uint8_t tmpSize;
	bool baseValid;
	while (size > 0) {
		utf8_SizeElement(input_UTF8, size , tmpSize, baseValid);
		input_UTF8 += tmpSize;
		size -= tmpSize;
		count++;
	}
	return count;
}



// **************************************************************************************************************
//       simple convertion optention
// **************************************************************************************************************

#if 0

Procedure de recuperation des charset sans ce casser les ...

// generate the basic file
	FILE * mfile = NULL;
	mfile = fopen("fichierIsoBase", "wb");
	if (NULL == mfile) {
		EDN_ERROR("Error to create file");
		return false;
	}
	char newline = '\n';
	for(int32_t i=0x20; i<0x100; i++) {
		char plop = i;
		fwrite(&plop, sizeof(char), 1, mfile);
		fwrite(&newline, sizeof(char), 1, mfile);
	}
	fclose(mfile);
// console script to convert files :
iconv -c --from-code=ISO-8859-1 --to-code=UTF-8 -o fichierUTF8_iso-1 fichierIsoBase
iconv -c --from-code=ISO-8859-2 --to-code=UTF-8 -o fichierUTF8_iso-2 fichierIsoBase
iconv -c --from-code=ISO-8859-3 --to-code=UTF-8 -o fichierUTF8_iso-3 fichierIsoBase
iconv -c --from-code=ISO-8859-4 --to-code=UTF-8 -o fichierUTF8_iso-4 fichierIsoBase
iconv -c --from-code=ISO-8859-5 --to-code=UTF-8 -o fichierUTF8_iso-5 fichierIsoBase
iconv -c --from-code=ISO-8859-6 --to-code=UTF-8 -o fichierUTF8_iso-6 fichierIsoBase
iconv -c --from-code=ISO-8859-7 --to-code=UTF-8 -o fichierUTF8_iso-7 fichierIsoBase
iconv -c --from-code=ISO-8859-8 --to-code=UTF-8 -o fichierUTF8_iso-8 fichierIsoBase
iconv -c --from-code=ISO-8859-9 --to-code=UTF-8 -o fichierUTF8_iso-9 fichierIsoBase
iconv -c --from-code=ISO-8859-10 --to-code=UTF-8 -o fichierUTF8_iso-10 fichierIsoBase
iconv -c --from-code=ISO-8859-11 --to-code=UTF-8 -o fichierUTF8_iso-11 fichierIsoBase
iconv -c --from-code=ISO-8859-12 --to-code=UTF-8 -o fichierUTF8_iso-12 fichierIsoBase
iconv -c --from-code=ISO-8859-13 --to-code=UTF-8 -o fichierUTF8_iso-13 fichierIsoBase
iconv -c --from-code=ISO-8859-14 --to-code=UTF-8 -o fichierUTF8_iso-14 fichierIsoBase
iconv -c --from-code=ISO-8859-15 --to-code=UTF-8 -o fichierUTF8_iso-15 fichierIsoBase

// NOTE : Le format 12 n'existe pas ...
	FILE * mfileout = NULL;
	mfileout = fopen("outputGeneration.c", "wb");
	if (NULL == mfileout) {
		EDN_ERROR("Error to create file");
		return false;
	}
	
	char * inputFileData[] = {
		"fichierUTF8_iso-1",
		"fichierUTF8_iso-2",
//		"fichierUTF8_iso-3",
		"fichierUTF8_iso-4",
		"fichierUTF8_iso-5",
/*		"fichierUTF8_iso-6",
		"fichierUTF8_iso-7",
		"fichierUTF8_iso-8",
		"fichierUTF8_iso-9",
		"fichierUTF8_iso-10",
		"fichierUTF8_iso-11",
		"fichierUTF8_iso-13",
		"fichierUTF8_iso-14",
*/
		"fichierUTF8_iso-15"
	};
	
	for (int32_t k=0; k<5; k++) {
		FILE * mfile = NULL;
		mfile = fopen(inputFileData[k], "rb");
		if (NULL == mfile) {
			EDN_ERROR("Error to open file");
			return false;
		}
		char data[255] ;
		fprintf(mfileout, "\tTYPESTRUCT_TS  %s[] = {\n\t\t", inputFileData[k]);
		for(int32_t i=0x0; i<0x10; i++) {
			fprintf(mfileout, "0x%08X, ", i);
		}
		fprintf(mfileout, "\n\t\t");
		for(int32_t i=0x10; i<0x20; i++) {
			fprintf(mfileout, "0x%08X, ", i);
		}
		for(int32_t i=0x20; i<0x100; i++) {
			if (0==i%16) {
				fprintf(mfileout, "\n\t\t");
			}
			fgets(data, 25, mfile );
			data[strlen(data)-1] = '\0';
			EDN_INFO("sizeofLine=" << strlen(data) << " data=\"" << data << "\"");
			// convert in int : 
			int32_t valUTF8 = 0;
			int32_t valUnicode = 0;
			switch (strlen(data)) {
				case 1:
					valUTF8 = (uint8_t) (data[0]);
					valUnicode = (uint8_t)(data[0]) & 0x7F;
					break;
				case 2:
					valUTF8  = (uint8_t) (data[0]) << 8;
					valUTF8 += (uint8_t) (data[1]);
					valUnicode  = (((uint8_t)data[0]) & 0x1F)<< 6;
					valUnicode +=  ((uint8_t)data[1]) & 0x3F;
					break;
				case 3:
					valUTF8  = (uint8_t) (data[0]) << 16;
					valUTF8 += (uint8_t) (data[1]) << 8;
					valUTF8 += (uint8_t) (data[2]);
					valUnicode  = (((uint8_t)data[0]) & 0x0F)<< 12;
					valUnicode += (((uint8_t)data[1]) & 0x3F)<< 6;
					valUnicode +=  ((uint8_t)data[2]) & 0x3F;
					break;
				default:
					valUTF8  = (uint8_t) (data[0]) <<24;
					valUTF8 += (uint8_t) (data[1]) << 16;
					valUTF8 += (uint8_t) (data[2]) << 8;
					valUTF8 += (uint8_t) (data[3]);
					valUnicode  = (((uint8_t)data[0]) & 0x07)<< 18;
					valUnicode += (((uint8_t)data[1]) & 0x3F)<< 12;
					valUnicode += (((uint8_t)data[2]) & 0x3F)<< 6;
					valUnicode +=  ((uint8_t)data[3]) & 0x3F;
					break;
			}
			fprintf(mfileout, "0x%08X, ", valUnicode);
		}
		fprintf(mfileout, "\n\t};\n\n");
		fclose(mfile);
	}
	fclose(mfileout);

#endif


