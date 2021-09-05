/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/String.hpp>
#include <etk/UString.hpp>


namespace etk {
	struct Number {
		protected:
			bool m_negative;
			uint64_t m_unit;
			uint64_t m_lessZero;
			uint64_t m_numberLessZero;
			uint32_t m_exponent;
		public:
			enum class type {
				numberDecimal,
				numberBinary,
				numberHexadecimal,
				numberLessZero,
				numberExponent,
			};
			Number();
			Number(int8_t _value);
			Number(int16_t _value);
			Number(int32_t _value);
			Number(int64_t _value);
			Number(uint8_t _value);
			Number(uint16_t _value);
			Number(uint32_t _value);
			Number(uint64_t _value);
			Number(float _value);
			Number(double _value);
			Number(long double _value);
			Number(bool _value);
			Number(const etk::UString& _value);
			void clear();
			bool isDigit(char32_t _value, enum type _type);
			// Format:
			//   51651
			//   -455465
			//   +54654
			//   51651.545
			//   -455465.4845
			//   +54654.485424
			//   51651e12
			//   -455465e12
			//   +54654e12
			//   51651.545e12
			//   -455465.4845e12
			//   +54654.485424e12
			//   0x123456789ABCDEF
			//   0b10101110101010
			bool parse(const etk::UString& _value);
			long double getDouble();
			uint64_t getU64();
			int64_t getI64();
	};
}