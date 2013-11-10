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
	enum charset {
		charsetUTF8,
		charsetIso8859_1,
		charsetIso8859_2,
		charsetIso8859_3,
		charsetIso8859_4,
		charsetIso8859_5,
		charsetIso8859_6,
		charsetIso8859_7,
		charsetIso8859_8,
		charsetIso8859_9,
		charsetIso8859_10,
		charsetIso8859_11,
		charsetIso8859_13,
		charsetIso8859_14,
		charsetIso8859_15
	};
	
	// transform ISO <==> Unicode
	void    convertIsoToUnicode(enum charset _inputCharset, const char                        _input_ISO,     etk::UChar &              _output_Unicode);
	void    convertUnicodeToIso(enum charset _inputCharset, const etk::UChar                  _input_Unicode, char &                    _output_ISO);
	int32_t convertIsoToUnicode(enum charset _inputCharset, const etk::Vector<char>&          _input_ISO,     etk::Vector<etk::UChar>&  _output_Unicode);
	int32_t convertIsoToUnicode(enum charset _inputCharset, const etk::Vector<int8_t>&        _input_ISO,     etk::Vector<etk::UChar>&  _output_Unicode);
	int32_t convertUnicodeToIso(enum charset _inputCharset, const etk::Vector<etk::UChar>&    _input_Unicode, etk::Vector<char>&        _output_ISO);
	int32_t convertUnicodeToIso(enum charset _inputCharset, const etk::Vector<etk::UChar>&    _input_Unicode, etk::Vector<int8_t>&      _output_ISO);
	// Transform UTF-8 <==> Unicode
	int32_t convertUnicodeToUtf8(                        const etk::Vector<etk::UChar>& _input_Unicode, etk::Vector<char>&      _output_UTF8);
	int32_t convertUnicodeToUtf8(                        const etk::Vector<etk::UChar>& _input_Unicode, etk::Vector<int8_t>&    _output_UTF8);
	int32_t convertUtf8ToUnicode(                        const etk::Vector<char>&            _input_UTF8,    etk::Vector<etk::UChar>& _output_Unicode);
	int32_t convertUtf8ToUnicode(                        const etk::Vector<int8_t>&          _input_UTF8,    etk::Vector<etk::UChar>& _output_Unicode);
	int32_t convertUtf8ToUnicode(                        const char *                        _input_UTF8,    etk::Vector<etk::UChar>& _output_Unicode);
	// Transform ISO <==> UTF-8
	void    convertIsoToUtf8(  enum charset _inputCharset,  const char                  _input_ISO,     char *                _output_UTF8);
	void    convertUtf8ToIso(  enum charset _inputCharset,  const char *                _input_UTF8,    char &                _output_ISO);
	int32_t convertIsoToUtf8(  enum charset _inputCharset,  const etk::Vector<char>&    _input_ISO,     etk::Vector<char>&    _output_UTF8);
	int32_t convertUtf8ToIso(  enum charset _inputCharset,  const etk::Vector<char>&    _input_UTF8,    etk::Vector<char>&    _output_ISO);
	
	void    utf8_SizeElement(const char * _data, int32_t _lenMax , uint8_t &_size, bool &_baseValid);
	int32_t strUtf8Len(const char *_input_UTF8);
}

#endif

