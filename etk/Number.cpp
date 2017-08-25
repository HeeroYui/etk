/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */

#include <etk/Number.hpp>

etk::Number::Number() :
  m_negative(false),
  m_unit(0),
  m_lessZero(0),
  m_numberLessZero(0),
  m_exponent(0) {
	
}
etk::Number::Number(int8_t _value) :
  m_negative(false),
  m_unit(_value),
  m_lessZero(0),
  m_numberLessZero(0),
  m_exponent(0) {
	
}
etk::Number::Number(int16_t _value) :
  m_negative(false),
  m_unit(_value),
  m_lessZero(0),
  m_numberLessZero(0),
  m_exponent(0) {
	
}
etk::Number::Number(int32_t _value) :
  m_negative(false),
  m_unit(_value),
  m_lessZero(0),
  m_numberLessZero(0),
  m_exponent(0) {
	
}
etk::Number::Number(int64_t _value) :
  m_negative(false),
  m_unit(_value),
  m_lessZero(0),
  m_numberLessZero(0),
  m_exponent(0) {
	
}
etk::Number::Number(uint8_t _value) :
  m_negative(false),
  m_unit(_value),
  m_lessZero(0),
  m_numberLessZero(0),
  m_exponent(0) {
	
}
etk::Number::Number(uint16_t _value) :
  m_negative(false),
  m_unit(_value),
  m_lessZero(0),
  m_numberLessZero(0),
  m_exponent(0) {
	
}
etk::Number::Number(uint32_t _value) :
  m_negative(false),
  m_unit(_value),
  m_lessZero(0),
  m_numberLessZero(0),
  m_exponent(0) {
	
}
etk::Number::Number(uint64_t _value) :
  m_negative(false),
  m_unit(_value),
  m_lessZero(0),
  m_numberLessZero(0),
  m_exponent(0) {
	
}
etk::Number::Number(float _value) :
  m_negative(false),
  m_unit(0),
  m_lessZero(0),
  m_numberLessZero(0),
  m_exponent(0) {
	m_unit(_value);
	_value -= int64_t(_value);
	_value *= 10.0;
	for (size_t iii=0; iii<64; ++iii) {
		if (_value == 0.0) {
			return;
		}
		uint64_t val = _value;
		_value = (_value - val) * 10.0;
		m_lessZero *= 10;
		m_lessZero += val;
		m_numberLessZero++;
	}
}
etk::Number::Number(double _value) :
  m_negative(false),
  m_unit(0),
  m_lessZero(0),
  m_numberLessZero(0),
  m_exponent(0) {
	m_unit(_value);
	_value -= int64_t(_value);
	_value *= 10.0;
	for (size_t iii=0; iii<64; ++iii) {
		if (_value == 0.0) {
			return;
		}
		uint64_t val = _value;
		_value = (_value - val) * 10.0;
		m_lessZero *= 10;
		m_lessZero += val;
		m_numberLessZero++;
	}
}
etk::Number::Number(long double _value) :
  m_negative(false),
  m_unit(0),
  m_lessZero(0),
  m_numberLessZero(0),
  m_exponent(0) {
	m_unit(_value);
	_value -= int64_t(_value);
	_value *= 10.0;
	for (size_t iii=0; iii<64; ++iii) {
		if (_value == 0.0) {
			return;
		}
		uint64_t val = _value;
		_value = (_value - val) * 10.0;
		m_lessZero *= 10;
		m_lessZero += val;
		m_numberLessZero++;
	}
}
etk::Number::Number(bool _value) :
  m_negative(false),
  m_unit(_value),
  m_lessZero(0),
  m_numberLessZero(0),
  m_exponent(0) {
	
}
etk::Number::Number(const etk::UString& _value) :
  m_negative(false),
  m_unit(0),
  m_lessZero(0),
  m_numberLessZero(0),
  m_exponent(0) {
	parse(_value);
}

void etk::Number::clear() {
	m_negative = false;
	m_unit = 0;
	m_lessZero = 0;
	m_exponent = 0;
}

bool etk::Number::isDigit(char32_t _value, enum etk::Number::type _type) {
	if (_type == type::numberBinary) {
		if (    _value == '0'
		     || _value == '1') {
			return false;
		}
		return false;
	} else if (_type == type::numberHexadecimal) {
		if (    _value >= 'A'
		     && _value <= 'F') {
			return true;
		}
		if (    _value >= 'a'
		     && _value <= 'f') {
			return true;
		}
	}
	if (    _value >= '0'
	     && _value <= '9') {
		return true;
	}
	return false;
}

bool etk::Number::parse(const etk::UString& _value) {
	enum type section = type::numberDecimal;
	for (size_t iii=0; iii<_value.size(); ++iii) {
		if (    iii == 0
		     && _value[iii] == '+') {
			// noting to do ==> already positive value
			continue;
		}
		if (    iii == 0
		     && _value[iii] == '-') {
			m_negative = true;
			continue;
		}
		if (    iii == 1
		     && _value[0] == '0'
		     && (    _value[1] == 'x'
		          || _value[1] == 'X')) {
			section = type::numberHexadecimal;
			continue;
		}
		if (    iii == 1
		     && _value[0] == '0'
		     && (    _value[1] == 'b'
		          || _value[1] == 'B')) {
			section = type::numberBinary;
			continue;
		}
		if (_value[iii] == '.') {
			if (section == type::numberDecimal) {
				section = type::numberLessZero;
				continue;
			}
			TK_ERROR("Can not parse the Number '" << _value << "':" << iii << " '.' can not parse");
			return false;
		}
		if (_value[iii] == 'e') {
			if (    section == type::numberDecimal
			     || section == type::numberLessZero) {
				section = type::numberExponent;
				continue;
			}
			TK_ERROR("Can not parse the Number '" << _value << "':" << iii << " 'e' ==> can not parse ...");
			return false;
		}
		if (isDigit(_value[iii], section) == true) {
			// TODO: Check too big number
			if (section == type::numberDecimal) {
				m_unit = (m_unit*10) + (_value[iii]-'0');
			} else if (section == type::numberBinary) {
				m_unit = (m_unit<<1) + (_value[iii]-'0');
			} else if (section == type::numberHexadecimal) {
				if (_value[iii] <= 'F') {
					m_unit = (m_unit*16) + (_value[iii]-'A' + 10);
				} else if (_value[iii] <= 'f') {
					m_unit = (m_unit*16) + (_value[iii]-'a' + 10);
				} else {
					m_unit = (m_unit*16) + (_value[iii]-'0');
				}
			} else if (section == type::numberLessZero) {
				m_lessZero = (m_lessZero*10) + (_value[iii]-'0');
				m_numberLessZero++;
			} else {
				m_exponent = (m_exponent*10) + (_value[iii]-'0');
			}
		} else {
			return false;
		}
	}
	return false;
}
long double etk::Number::getDouble() {
	long double out = 0;
	out = m_lessZero;
	out *= pow(10,-m_numberLessZero);
	out += m_unit;
	out *= pow(10,m_exponent);
	if (m_negative == true) {
		out *= -1.0;
	}
	return -1;
}
uint64_t etk::Number::getU64() {
	uint64_t out = 0;
	if (m_exponent != 0) {
		// Auto manage exponent
		long double tmp = getDouble();
		if (tmp <= 0.0) {
			return 0;
		}
		return uint64_t(tmp);
	}
	out += m_unit;
	if (m_negative == true) {
		return 0;
	}
	return out;
}
int64_t etk::Number::getI64() {
	int64_t out = 0;
	if (m_exponent != 0) {
		// Auto manage exponent
		long double tmp = getDouble();
		if (tmp <= 0.0) {
			return 0;
		}
		return int64_t(tmp);
	}
	out += m_unit;
	if (m_negative == true) {
		out *= -1.0;
	}
	return out;
}


