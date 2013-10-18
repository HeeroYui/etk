/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __UNICODE_H__
#define __UNICODE_H__

#include <etk/types.h>
#include <etk/Vector.h>

namespace unicode {
	typedef enum {
		EDN_CHARSET_UTF8,
		EDN_CHARSET_ISO_8859_1,
		EDN_CHARSET_ISO_8859_2,
		EDN_CHARSET_ISO_8859_3,
		EDN_CHARSET_ISO_8859_4,
		EDN_CHARSET_ISO_8859_5,
		EDN_CHARSET_ISO_8859_6,
		EDN_CHARSET_ISO_8859_7,
		EDN_CHARSET_ISO_8859_8,
		EDN_CHARSET_ISO_8859_9,
		EDN_CHARSET_ISO_8859_10,
		EDN_CHARSET_ISO_8859_11,
		EDN_CHARSET_ISO_8859_13,
		EDN_CHARSET_ISO_8859_14,
		EDN_CHARSET_ISO_8859_15
	} charset_te;
	
	// transform ISO <==> Unicode
	void    convertIsoToUnicode(charset_te _inputCharset, const char                        _input_ISO,     etk::UChar &               _output_Unicode);
	void    convertUnicodeToIso(charset_te _inputCharset, const etk::UChar                   _input_Unicode, char &                    _output_ISO);
	int32_t convertIsoToUnicode(charset_te _inputCharset, const etk::Vector<char>&          _input_ISO,     etk::Vector<etk::UChar>&   _output_Unicode);
	int32_t convertIsoToUnicode(charset_te _inputCharset, const etk::Vector<int8_t>&        _input_ISO,     etk::Vector<etk::UChar>&   _output_Unicode);
	int32_t convertUnicodeToIso(charset_te _inputCharset, const etk::Vector<etk::UChar>&     _input_Unicode, etk::Vector<char>&        _output_ISO);
	int32_t convertUnicodeToIso(charset_te _inputCharset, const etk::Vector<etk::UChar>&     _input_Unicode, etk::Vector<int8_t>&      _output_ISO);
	// Transform UTF-8 <==> Unicode
	int32_t convertUnicodeToUtf8(                        const etk::Vector<etk::UChar>& _input_Unicode, etk::Vector<char>&      _output_UTF8);
	int32_t convertUnicodeToUtf8(                        const etk::Vector<etk::UChar>& _input_Unicode, etk::Vector<int8_t>&    _output_UTF8);
	int32_t convertUtf8ToUnicode(                        const etk::Vector<char>&            _input_UTF8,    etk::Vector<etk::UChar>& _output_Unicode);
	int32_t convertUtf8ToUnicode(                        const etk::Vector<int8_t>&          _input_UTF8,    etk::Vector<etk::UChar>& _output_Unicode);
	int32_t convertUtf8ToUnicode(                        const char *                        _input_UTF8,    etk::Vector<etk::UChar>& _output_Unicode);
	// Transform ISO <==> UTF-8
	void    convertIsoToUtf8(  charset_te _inputCharset,  const char                  _input_ISO,     char *                _output_UTF8);
	void    convertUtf8ToIso(  charset_te _inputCharset,  const char *                _input_UTF8,    char &                _output_ISO);
	int32_t convertIsoToUtf8(  charset_te _inputCharset,  const etk::Vector<char>&    _input_ISO,     etk::Vector<char>&    _output_UTF8);
	int32_t convertUtf8ToIso(  charset_te _inputCharset,  const etk::Vector<char>&    _input_UTF8,    etk::Vector<char>&    _output_ISO);
	
	void    utf8_SizeElement(const char * _data, int32_t _lenMax , uint8_t &_size, bool &_baseValid);
	int32_t strUtf8Len(const char *_input_UTF8);
}

#endif

