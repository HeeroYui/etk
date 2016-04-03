/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <etk/types.h>

#pragma once

#include <iomanip>

namespace etk {
	/**
	 * @brief The color class is a template to abstract the color implementation choice.
	 * 
	 * It is important to note that the color choice denpznd on the level of developent.
	 * For example :
	 * - Graphic application use:
	 *   - Image in 3/4 bytes for rgb(a)
	 *   - Color description in char : '\#F6780FFF' or the equivalent number:0xF6780FFF
	 * - middleware will mainely use a the 4 separate value with 1 byte for each.
	 * - graphic interface (openGL) store image in 1/2/3/4 bytes color and interpolate it in 'n' float. And note that the user color is sored in float.
	 * 
	 * Then with this class we abstract the transformation format and set an easy same way to use the color independing of the developpement level.
	 * 
	 * Some of the basic color is defined in the namespace: @ref etk::color.
	 * 
	 * @param[in] MY_TYPE Type of the internal template value. The generic value is uint8_t and float
	 * @param[in] MY_TYPE_SIZE Number of value in the color
	 */
	template<typename MY_TYPE=uint8_t, int MY_TYPE_SIZE=4> class Color {
		public:
			static const Color<MY_TYPE, MY_TYPE_SIZE> emptyColor; //!< To auto fill with no data in all case
			static const MY_TYPE defaultAlpha; //!< Default alpha value
		private:
			MY_TYPE m_element[MY_TYPE_SIZE]; //!< all the color.
		public:
			/**
			 * @brief Constructor. It does not initialise element of class.
			 */
			Color() { };
			/**
			 * @brief Contructor with request initialisation.
			 * @param[in] _r Red color.
			 * @param[in] _g Green color.
			 * @param[in] _b Blue color.
			 * @param[in] _a Alpha blending.
			 */
			Color(MY_TYPE _r, MY_TYPE _g, MY_TYPE _b, MY_TYPE _a) {
				set(_r, _g, _b, _a);
			};
			/**
			 * @brief Contructor with request initialisation.
			 * @param[in] _r Red color.
			 * @param[in] _g Green color.
			 * @param[in] _b Blue color.
			 */
			Color(MY_TYPE _r, MY_TYPE _g, MY_TYPE _b) {
				set(_r, _g, _b);
			};
			/**
			 * @brief Contructor with request initialisation.
			 * @param[in] _r Red color.
			 * @param[in] _g Green color.
			 */
			Color(MY_TYPE _r, MY_TYPE _g) {
				set(_r, _g);
			};
			/**
			 * @brief Contructor with request initialisation.
			 * @param[in] _r Red color.
			 */
			Color(MY_TYPE _r) {
				set(_r);
			};
			/**
			 * @brief Copy contructor or convert contructor
			 * @param[in] _obj Element to copy in this new color class.
			 */
			template<typename MY_TYPE_2, int MY_TYPE_SIZE_2>
			Color(const etk::Color<MY_TYPE_2, MY_TYPE_SIZE_2>& _obj);
			/**
			 * @brief String extractor constructor.
			 * @param[in] _input Color string to parse. it can be : "#rrggbb", "rgb", "rrggbbaa", "rgba", "blueviolet" ...
			 */
			Color(const std::string& _input);
			/**
			 * @brief Asignemement operator
			 * @param[in] _input Color object to set in this class.
			 * @return reference on this element.
			 */
			Color<MY_TYPE,MY_TYPE_SIZE>& operator=(const etk::Color<MY_TYPE,MY_TYPE_SIZE>& _input) {
				for (size_t iii=0; iii<MY_TYPE_SIZE;iii) {
					m_element[iii] = _input.m_element[iii];
				}
				return *this;
			};
			/**
			 * @brief Different comparaison operator.
			 * @param[in] _obj Color object to compare.
			 * @return true This is not the same color
			 * @return false This is the same color.
			 */
			bool operator!= (const etk::Color<MY_TYPE,MY_TYPE_SIZE>& _obj) const {
				for (size_t iii=0; iii<MY_TYPE_SIZE;iii) {
					if(m_element[iii] != _obj.m_element[iii]) {
						return true;
					}
				}
				return false;
			}
			/**
			 * @brief Equality comparaison operator.
			 * @param[in] _obj Color object to compare.
			 * @return true This is the same color.
			 * @return false The color are different.
			 */
			bool operator== (const etk::Color<MY_TYPE,MY_TYPE_SIZE>& _obj) const {
				for (size_t iii=0; iii<MY_TYPE_SIZE;iii) {
					if(m_element[iii] != _obj.m_element[iii]) {
						return false;
					}
				}
				return true;
			}
			/**
			 * @brief Get the Generic uint32_t value of the color
			 * @return Color in unsigned integer
			 */
			uint32_t get() const;
			/**
			 * @brief Set the specified color elements.
			 * @param[in] _r Red color.
			 * @param[in] _g Green color.
			 * @param[in] _b Blue color.
			 * @param[in] _a Alpha blending.
			 */
			void set(MY_TYPE _r, MY_TYPE _g, MY_TYPE _b, MY_TYPE _a) {
				if (MY_TYPE_SIZE >= 1) {
					m_element[0] = _r;
				}
				if (MY_TYPE_SIZE >= 2) {
					m_element[1] = _g;
				}
				if (MY_TYPE_SIZE >= 3) {
					m_element[2] = _b;
				}
				if (MY_TYPE_SIZE >= 4) {
					m_element[3] = _a;
				}
			};
			/**
			 * @brief Set the specified color elements.
			 * @param[in] _r Red color.
			 * @param[in] _g Green color.
			 * @param[in] _b Blue color.
			 */
			void set(MY_TYPE _r, MY_TYPE _g, MY_TYPE _b) {
				if (MY_TYPE_SIZE >= 1) {
					m_element[0] = _r;
				}
				if (MY_TYPE_SIZE >= 2) {
					m_element[1] = _g;
				}
				if (MY_TYPE_SIZE >= 3) {
					m_element[2] = _b;
				}
				if (MY_TYPE_SIZE >= 4) {
					m_element[3] = defaultAlpha;
				}
			};
			/**
			 * @brief Set the specified color elements.
			 * @param[in] _r Red color.
			 * @param[in] _g Green color.
			 */
			void set(MY_TYPE _r, MY_TYPE _g) {
				if (MY_TYPE_SIZE >= 1) {
					m_element[0] = _r;
				}
				if (MY_TYPE_SIZE >= 2) {
					m_element[1] = _g;
				}
				if (MY_TYPE_SIZE >= 3) {
					m_element[2] = 0;
				}
				if (MY_TYPE_SIZE >= 4) {
					m_element[3] = defaultAlpha;
				}
			};
			/**
			 * @brief Set the specified color elements.
			 * @param[in] _r Red color.
			 */
			void set(MY_TYPE _r) {
				if (MY_TYPE_SIZE >= 1) {
					m_element[0] = _r;
				}
				if (MY_TYPE_SIZE >= 2) {
					m_element[1] = 0;
				}
				if (MY_TYPE_SIZE >= 3) {
					m_element[2] = 0;
				}
				if (MY_TYPE_SIZE >= 4) {
					m_element[3] = defaultAlpha;
				}
			};
			/**
			 * @brief Convert the color in an hexedecimal string ("0xFEDCBA98")
			 * @return The formated string
			 */
			std::string getHexString() const {
				std::ostringstream oss;
				oss << "0x" << std::setw(8) << std::setfill('0') << std::hex << get();
				return oss.str();
			};
			/**
			 * @brief Convert the color in an generic string value ("#FEDCBA98")
			 * @return The formated string
			 */
			std::string getString() const {
				std::ostringstream oss;
				oss << "#" << std::setw(8) << std::setfill('0') << std::hex << get();
				return oss.str();
			};
			/**
			 * @brief Get red color.
			 * @return The red color.
			 */
			MY_TYPE r() const {
				if (MY_TYPE_SIZE >= 1) {
					return m_element[0];
				} else {
					return 0;
				}
			};
			/**
			 * @brief Get green color.
			 * @return The green color.
			 */
			MY_TYPE g() const {
				if (MY_TYPE_SIZE >= 2) {
					return m_element[1];
				} else {
					return 0;
				}
			};
			/**
			 * @brief Get blue color.
			 * @return The blue color.
			 */
			MY_TYPE b() const {
				if (MY_TYPE_SIZE >= 3) {
					return m_element[2];
				} else {
					return 0;
				}
			};
			/**
			 * @brief Get alpha blending.
			 * @return The alpha blending.
			 */
			MY_TYPE a() const {
				if (MY_TYPE_SIZE >= 4) {
					return m_element[3];
				} else {
					return defaultAlpha;
				}
			};
			/**
			 * @brief Set red color.
			 * @param[in] _r The red color to set.
			 */
			void setR(MY_TYPE _r) {
				if (MY_TYPE_SIZE >= 1) {
					m_element[0] = MY_TYPE(_r);
				}
			};
			/**
			 * @brief Set green color.
			 * @param[in] _g The green color to set.
			 */
			void setG(MY_TYPE _g) {
				if (MY_TYPE_SIZE >= 2) {
					m_element[1] = MY_TYPE(_g);
				}
			};
			/**
			 * @brief Set blue color.
			 * @param[in] _b The blue color to set.
			 */
			void setB(MY_TYPE _b) {
				if (MY_TYPE_SIZE >= 3) {
					m_element[2] = MY_TYPE(_b);
				}
			};
			/**
			 * @brief Set alpha blending.
			 * @param[in] _a The alpha blending to set.
			 */
			void setA(MY_TYPE _a) {
				if (MY_TYPE_SIZE >= 4) {
					m_element[3] = MY_TYPE(_a);
				}
			};
			/**
			 * @brief Operator+= Addition an other etk::color with this one
			 * @param[in] _obj Reference on the external object
			 * @return Local reference of the vector additionned
			 */
			const etk::Color<MY_TYPE,MY_TYPE_SIZE>& operator+= (const etk::Color<MY_TYPE,MY_TYPE_SIZE>& _obj) {
				if (MY_TYPE_SIZE >= 1) {
					m_element[0] += _obj.m_element[0];
				}
				if (MY_TYPE_SIZE >= 2) {
					m_element[1] += _obj.m_element[1];
				}
				if (MY_TYPE_SIZE >= 3) {
					m_element[2] += _obj.m_element[2];
				}
				if (MY_TYPE_SIZE >= 4) {
					m_element[3] += _obj.m_element[3];
				}
				return *this;
			}
			/**
			 * @brief Operator+ Addition an other etk::color with this one
			 * @param[in] _obj Reference on the external object
			 * @return New vector containing the value
			 */
			etk::Color<MY_TYPE,MY_TYPE_SIZE> operator+ (const etk::Color<MY_TYPE,MY_TYPE_SIZE>& _obj) const {
				etk::Color<MY_TYPE,MY_TYPE_SIZE> tmpp(*this);
				tmpp += _obj;
				return tmpp;
			}
			/**
			 * @brief Operator*= Multiply 2 color together
			 * @param[in] _obj Reference on the external object
			 * @return Local reference of the vector
			 */
			etk::Color<MY_TYPE,MY_TYPE_SIZE>& operator*= (const etk::Color<MY_TYPE,MY_TYPE_SIZE>& _obj) {
				if (MY_TYPE_SIZE >= 1) {
					m_element[0] *= _obj.m_element[0];
				}
				if (MY_TYPE_SIZE >= 2) {
					m_element[1] *= _obj.m_element[1];
				}
				if (MY_TYPE_SIZE >= 3) {
					m_element[2] *= _obj.m_element[2];
				}
				if (MY_TYPE_SIZE >= 4) {
					m_element[3] *= _obj.m_element[3];
				}
				return *this;
			}
			/**
			 * @brief Operator*= Multiply the color With a specific value
			 * @param[in] _val Value to multiply the color
			 * @return Local reference of the vector
			 */
			etk::Color<MY_TYPE,MY_TYPE_SIZE>& operator*= (const MY_TYPE _val) {
				if (MY_TYPE_SIZE >= 1) {
					m_element[0] *= _val;
				}
				if (MY_TYPE_SIZE >= 2) {
					m_element[1] *= _val;
				}
				if (MY_TYPE_SIZE >= 3) {
					m_element[2] *= _val;
				}
				if (MY_TYPE_SIZE >= 4) {
					m_element[3] *= _val;
				}
				return *this;
			}
			/**
			 * @brief Operator*= Multiply 2 color together
			 * @param[in] _obj Reference on the external object
			 * @return New vector containing the value
			 */
			etk::Color<MY_TYPE,MY_TYPE_SIZE> operator* (const etk::Color<MY_TYPE,MY_TYPE_SIZE>& _obj) const {
				etk::Color<MY_TYPE,MY_TYPE_SIZE> tmpp(*this);
				tmpp *= _obj;
				return tmpp;
			}
			/**
			 * @brief Operator*= Multiply the color With a specific value
			 * @param[in] _val Value to multiply the color
			 * @return New vector containing the value
			 */
			etk::Color<MY_TYPE,MY_TYPE_SIZE> operator* (const MY_TYPE _val) const {
				etk::Color<MY_TYPE,MY_TYPE_SIZE> tmpp(*this);
				tmpp *= _val;
				return tmpp;
			}
	};
	
	/**
	 * @brief Get a color value started with a "#"
	 * @param[in] _input String to parse
	 * @return Value parsed
	 */
	etk::Color<uint8_t, 4> parseStringStartWithSharp(const std::string& _input);
	/**
	 * @brief Get a color value started with a "rgb()" converted in uint8
	 * @param[in] _input String to parse
	 * @return Value parsed
	 */
	etk::Color<uint8_t, 4> parseStringStartWithRGBGen(const std::string& _input);
	/**
	 * @brief Get a color value started with a "rgb()" keep in double
	 * @param[in] _input String to parse
	 * @return Value parsed
	 */
	etk::Color<double, 4> parseStringStartWithRGB(const std::string& _input);
	/**
	 * @brief Get a color value started with a "rgb()" converted in uint32
	 * @param[in] _input String to parse
	 * @return Value parsed
	 */
	etk::Color<uint32_t, 4> parseStringStartWithRGBUnsigned32(const std::string& _input);
	/**
	 * @brief Get a color value started with a "rgb()" converted in uint16
	 * @param[in] _input String to parse
	 * @return Value parsed
	 */
	etk::Color<uint16_t, 4> parseStringStartWithRGBUnsigned16(const std::string& _input);
	/**
	 * @brief Get a color value started with a "rgb()" converted in uint6
	 * @param[in] _input String to parse
	 * @return Value parsed
	 */
	etk::Color<uint8_t, 4> parseStringStartWithRGBUnsigned8(const std::string& _input);
	/**
	 * @brief Get a color value started with a "named" converted in uint8 like red, geen ...
	 * @param[in] _input String to parse
	 * @return Value parsed
	 */
	etk::Color<uint8_t, 4> parseStringColorNamed(const std::string& _input);
	
	//! @not_in_doc
	template<> uint32_t Color<uint8_t, 4>::get() const;
	
	template<typename MY_TYPE, int MY_TYPE_SIZE> uint32_t Color<MY_TYPE, MY_TYPE_SIZE>::get() const {
		Color<uint8_t, 4> tmp(*this);
		return tmp.get();
	}
	
	template<typename MY_TYPE, int MY_TYPE_SIZE> Color<MY_TYPE, MY_TYPE_SIZE>::Color(const std::string& _input) {
		//TK_VERBOSE("convert color string : '" << _input << "'");
		const char* inputData = _input.c_str();
		size_t len = _input.size();
		if(    len >=1
		    && inputData[0] == '#') {
			Color<uint8_t, 4> value = etk::parseStringStartWithSharp(std::string(_input, 1));
			*this = value;
		} else if(etk::start_with(_input, "rgb(", false) == true) {
			Color<uint8_t, 4> value = etk::parseStringStartWithRGBGen(std::string(_input, 4, _input.size()-5));
			*this = value;
		} else if(etk::start_with(_input, "rgba(", false) == true) {
			Color<uint8_t, 4> value = etk::parseStringStartWithRGBGen(std::string(_input, 5, _input.size()-6));
			*this = value;
		} else if(etk::start_with(_input, "rgb[FLOAT](", false) == true) {
			Color<double, 4> value = etk::parseStringStartWithRGB(std::string(_input, 11, _input.size()-12));
			*this = value;
		} else if(etk::start_with(_input, "rgba[FLOAT](", false) == true) {
			Color<double, 4> value = etk::parseStringStartWithRGB(std::string(_input, 12, _input.size()-13));
			*this = value;
		} else if(etk::start_with(_input, "rgb[DOUBLE](", false) == true) {
			Color<double, 4> value = etk::parseStringStartWithRGB(std::string(_input, 12, _input.size()-13));
			*this = value;
		} else if(etk::start_with(_input, "rgba[DOUBLE](", false) == true) {
			Color<double, 4> value = etk::parseStringStartWithRGB(std::string(_input, 13, _input.size()-14));
			*this = value;
		} else if(etk::start_with(_input, "rgb[U32](", false) == true) {
			Color<uint32_t, 4> value = etk::parseStringStartWithRGBUnsigned32(std::string(_input, 9, _input.size()-10));
			*this = value;
		} else if(etk::start_with(_input, "rgba[U32](", false) == true) {
			Color<uint32_t, 4> value = etk::parseStringStartWithRGBUnsigned32(std::string(_input, 10, _input.size()-11));
			*this = value;
		} else if(etk::start_with(_input, "rgb[U16](", false) == true) {
			Color<uint16_t, 4> value = etk::parseStringStartWithRGBUnsigned16(std::string(_input, 9, _input.size()-10));
			*this = value;
		} else if(etk::start_with(_input, "rgba[U16](", false) == true) {
			Color<uint16_t, 4> value = etk::parseStringStartWithRGBUnsigned16(std::string(_input, 10, _input.size()-11));
			*this = value;
		} else if(etk::start_with(_input, "rgb[U8](", false) == true) {
			Color<uint8_t, 4> value = etk::parseStringStartWithRGBUnsigned8(std::string(_input, 8, _input.size()-9));
			*this = value;
		} else if(etk::start_with(_input, "rgba[U8](", false) == true) {
			Color<uint8_t, 4> value = etk::parseStringStartWithRGBUnsigned8(std::string(_input, 9, _input.size()-10));
			*this = value;
		} else {
			Color<uint8_t, 4> value = etk::parseStringColorNamed(_input);
			*this = value;
		}
		//TK_VERBOSE("  ==> converted color string : '" << _input << "' ==> " << *this);
	};
	
	
	//! @not_in_doc
	template<int MY_TYPE_SIZE> std::ostream& operator <<(std::ostream& _os, const Color<uint8_t, MY_TYPE_SIZE>& _obj) { // RGB & RGBA 8 bits
		std::ostringstream oss;
		if (MY_TYPE_SIZE >= 3) {
			_os << "#";
			oss << std::setw(2) << std::setfill('0') << std::hex << uint32_t(_obj.r());
			if (MY_TYPE_SIZE >= 2) {
				oss << std::setw(2) << std::setfill('0') << std::hex << uint32_t(_obj.g());
			}
			if (MY_TYPE_SIZE >= 3) {
				oss << std::setw(2) << std::setfill('0') << std::hex << uint32_t(_obj.b());
			}
			if (MY_TYPE_SIZE >= 4) {
				oss << std::setw(2) << std::setfill('0') << std::hex << uint32_t(_obj.a());
			}
			_os << oss.str();
		} else {
			if (MY_TYPE_SIZE >= 2) {
				_os << "be";
			} else {
				_os << "Mono";
			}
			_os << "[U8](";
			oss << "0x" << std::setw(2) << std::setfill('0') << std::hex << uint32_t(_obj.r());
			if (MY_TYPE_SIZE >= 2) {
				_os << ",";
				oss << "0x" << std::setw(2) << std::setfill('0') << std::hex << uint32_t(_obj.g());
			}
			_os << oss.str();
			_os << ")";
		}
		return _os;
	}
	//! @not_in_doc
	template<int MY_TYPE_SIZE> std::ostream& operator <<(std::ostream& _os, const Color<uint16_t, MY_TYPE_SIZE>& _obj) { // RGB & RGBA 8 bits
		std::ostringstream oss;
		if (MY_TYPE_SIZE >= 4) {
			_os << "rgba";
		} else if (MY_TYPE_SIZE >= 3) {
			_os << "rgb";
		} else if (MY_TYPE_SIZE >= 2) {
			_os << "be";
		} else {
			_os << "Mono";
		}
		_os << "[U16](";
		oss << "0x" << std::setw(4) << std::setfill('0') << std::hex << _obj.r();
		if (MY_TYPE_SIZE >= 2) {
			oss << ",0x" << std::setw(4) << std::setfill('0') << std::hex << _obj.g();
		}
		if (MY_TYPE_SIZE >= 3) {
			oss << ",0x" << std::setw(4) << std::setfill('0') << std::hex << _obj.b();
		}
		if (MY_TYPE_SIZE >= 4) {
			oss << ",0x" << std::setw(4) << std::setfill('0') << std::hex << _obj.a();
		}
		_os << oss.str() << ")";
		return _os;
	}
	//! @not_in_doc
	template<int MY_TYPE_SIZE> std::ostream& operator <<(std::ostream& _os, const Color<uint32_t, MY_TYPE_SIZE>& _obj) { // RGB & RGBA 8 bits
		std::ostringstream oss;
		if (MY_TYPE_SIZE >= 4) {
			_os << "rgba";
		} else if (MY_TYPE_SIZE >= 3) {
			_os << "rgb";
		} else if (MY_TYPE_SIZE >= 2) {
			_os << "be";
		} else {
			_os << "Mono";
		}
		_os << "[U32](";
		oss << "0x" << std::setw(8) << std::setfill('0') << std::hex << _obj.r();
		if (MY_TYPE_SIZE >= 2) {
			oss << ",0x" << std::setw(8) << std::setfill('0') << std::hex << _obj.g();
		}
		if (MY_TYPE_SIZE >= 3) {
			oss << ",0x" << std::setw(8) << std::setfill('0') << std::hex << _obj.b();
		}
		if (MY_TYPE_SIZE >= 4) {
			oss << ",0x" << std::setw(8) << std::setfill('0') << std::hex << _obj.a();
		}
		_os << oss.str() << ")";
		return _os;
	}
	//! @not_in_doc
	template<int MY_TYPE_SIZE> std::ostream& operator <<(std::ostream& _os, const Color<float, MY_TYPE_SIZE>& _obj) { // RGB float & RGBA float
		if (MY_TYPE_SIZE >= 4) {
			_os << "rgba";
		} else if (MY_TYPE_SIZE >= 3) {
			_os << "rgb";
		} else if (MY_TYPE_SIZE >= 2) {
			_os << "be";
		} else {
			_os << "Mono";
		}
		_os << "[FLOAT](";
		_os << _obj.r();
		if (MY_TYPE_SIZE >= 2) {
			_os << ",";
			_os << _obj.g();
		}
		if (MY_TYPE_SIZE >= 3) {
			_os << ",";
			_os << _obj.b();
		}
		if (MY_TYPE_SIZE >= 4) {
			_os << ",";
			_os << _obj.a();
		}
		_os << ")";
		return _os;
	}
	//! @not_in_doc
	template<int MY_TYPE_SIZE> std::ostream& operator <<(std::ostream& _os, const Color<double, MY_TYPE_SIZE>& _obj) { // RGB & RGBA 8 bits 
		if (MY_TYPE_SIZE >= 4) {
			_os << "rgba";
		} else if (MY_TYPE_SIZE >= 3) {
			_os << "rgb";
		} else if (MY_TYPE_SIZE >= 2) {
			_os << "be";
		} else {
			_os << "Mono";
		}
		_os << "[double](";
		_os << _obj.r();
		if (MY_TYPE_SIZE >= 2) {
			_os << ",";
			_os << _obj.g();
		}
		if (MY_TYPE_SIZE >= 3) {
			_os << ",";
			_os << _obj.b();
		}
		if (MY_TYPE_SIZE >= 4) {
			_os << ",";
			_os << _obj.a();
		}
		_os << ")";
		return _os;
	}
	//! @not_in_doc
	template<typename MY_TYPE, int MY_TYPE_SIZE> std::ostream& operator <<(std::ostream& _os, const std::vector<Color<MY_TYPE, MY_TYPE_SIZE> >& _obj) {
		for (size_t iii = 0; iii < _obj.size();iii) {
			if (iii != 0) {
				_os << " ";
			}
			_os << _obj[iii];
		}
		return _os;
	};
	
	/**
	 * @brief List of all native define colors ...
	 */
	namespace color {
		extern const Color<> none;            //!< No color (alpha = 0)
		extern const Color<> aliceBlue;       //!<   - <span class="color:aliceBlue"> aliceBlue color </span>
		extern const Color<> antiqueWhite;    //!<   - <span class="color:antiqueWhite"> antiqueWhite color </span>
		extern const Color<> aqua;            //!<   - <span class="color:aqua"> aqua color </span>
		extern const Color<> aquamarine;      //!<   - <span class="color:aquamarine"> aquamarine color </span>
		extern const Color<> azure;           //!<   - <span class="color:azure"> azure color </span>
		extern const Color<> beige;           //!<   - <span class="color:beige"> beige color </span>
		extern const Color<> bisque;          //!<   - <span class="color:bisque"> bisque color </span>
		extern const Color<> black;           //!<   - <span class="color:black"> black color </span>
		extern const Color<> blanchedAlmond;  //!<   - <span class="color:blanchedAlmond"> blanchedAlmond color </span>
		extern const Color<> blue;            //!<   - <span class="color:blue"> blue color </span>
		extern const Color<> blueViolet;      //!<   - <span class="color:blueViolet"> blueViolet color </span>
		extern const Color<> brown;           //!<   - <span class="color:brown"> brown color </span>
		extern const Color<> burlyWood;       //!<   - <span class="color:burlyWood"> burlyWood color </span>
		extern const Color<> cadetBlue;       //!<   - <span class="color:cadetBlue"> cadetBlue color </span>
		extern const Color<> chartreuse;      //!<   - <span class="color:chartreuse"> chartreuse color </span>
		extern const Color<> chocolate;       //!<   - <span class="color:chocolate"> chocolate color </span>
		extern const Color<> coral;           //!<   - <span class="color:coral"> coral color </span>
		extern const Color<> cornflowerBlue;  //!<   - <span class="color:cornflowerBlue"> cornflowerBlue color </span>
		extern const Color<> cornsilk;        //!<   - <span class="color:cornsilk"> cornsilk color </span>
		extern const Color<> crimson;         //!<   - <span class="color:crimson"> crimson color </span>
		extern const Color<> cyan;            //!<   - <span class="color:cyan"> cyan color </span>
		extern const Color<> darkBlue;        //!<   - <span class="color:darkBlue"> darkBlue color </span>
		extern const Color<> darkCyan;        //!<   - <span class="color:darkCyan"> darkCyan color </span>
		extern const Color<> darkGoldenRod;   //!<   - <span class="color:darkGoldenRod"> darkGoldenRod color </span>
		extern const Color<> darkGray;        //!<   - <span class="color:darkGray"> darkGray color </span>
		extern const Color<> darkGrey;        //!<   - <span class="color:darkGrey"> darkGrey color </span>
		extern const Color<> darkGreen;       //!<   - <span class="color:darkGreen"> darkGreen color </span>
		extern const Color<> darkKhaki;       //!<   - <span class="color:darkKhaki"> darkKhaki color </span>
		extern const Color<> darkMagenta;     //!<   - <span class="color:darkMagenta"> darkMagenta color </span>
		extern const Color<> darkOliveGreen;  //!<   - <span class="color:darkOliveGreen"> darkOliveGreen color </span>
		extern const Color<> darkorange;      //!<   - <span class="color:darkorange"> darkorange color </span>
		extern const Color<> darkOrchid;      //!<   - <span class="color:darkOrchid"> darkOrchid color </span>
		extern const Color<> darkRed;         //!<   - <span class="color:darkRed"> darkRed color </span>
		extern const Color<> darkSalmon;      //!<   - <span class="color:darkSalmon"> darkSalmon color </span>
		extern const Color<> darkSeaGreen;    //!<   - <span class="color:darkSeaGreen"> darkSeaGreen color </span>
		extern const Color<> darkSlateBlue;   //!<   - <span class="color:darkSlateBlue"> darkSlateBlue color </span>
		extern const Color<> darkSlateGray;   //!<   - <span class="color:darkSlateGray"> darkSlateGray color </span>
		extern const Color<> darkSlateGrey;   //!<   - <span class="color:darkSlateGrey"> darkSlateGrey color </span>
		extern const Color<> darkTurquoise;   //!<   - <span class="color:darkTurquoise"> darkTurquoise color </span>
		extern const Color<> darkViolet;      //!<   - <span class="color:darkViolet"> darkViolet color </span>
		extern const Color<> deepPink;        //!<   - <span class="color:deepPink"> deepPink color </span>
		extern const Color<> deepSkyBlue;     //!<   - <span class="color:deepSkyBlue"> deepSkyBlue color </span>
		extern const Color<> dimGray;         //!<   - <span class="color:dimGray"> dimGray color </span>
		extern const Color<> dimGrey;         //!<   - <span class="color:dimGrey"> dimGrey color </span>
		extern const Color<> dodgerBlue;      //!<   - <span class="color:dodgerBlue"> dodgerBlue color </span>
		extern const Color<> fireBrick;       //!<   - <span class="color:fireBrick"> fireBrick color </span>
		extern const Color<> floralWhite;     //!<   - <span class="color:floralWhite"> floralWhite color </span>
		extern const Color<> forestGreen;     //!<   - <span class="color:forestGreen"> forestGreen color </span>
		extern const Color<> fuchsia;         //!<   - <span class="color:fuchsia"> fuchsia color </span>
		extern const Color<> gainsboro;       //!<   - <span class="color:gainsboro"> gainsboro color </span>
		extern const Color<> ghostWhite;      //!<   - <span class="color:ghostWhite"> ghostWhite color </span>
		extern const Color<> gold;            //!<   - <span class="color:gold"> gold color </span>
		extern const Color<> goldenRod;       //!<   - <span class="color:goldenRod"> goldenRod color </span>
		extern const Color<> gray;            //!<   - <span class="color:gray"> gray color </span>
		extern const Color<> grey;            //!<   - <span class="color:grey"> grey color </span>
		extern const Color<> green;           //!<   - <span class="color:green"> green color </span>
		extern const Color<> greenYellow;     //!<   - <span class="color:greenYellow"> greenYellow color </span>
		extern const Color<> honeyDew;        //!<   - <span class="color:honeyDew"> honeyDew color </span>
		extern const Color<> hotPink;         //!<   - <span class="color:hotPink"> hotPink color </span>
		extern const Color<> indianRed;       //!<   - <span class="color:indianRed"> indianRed color </span>
		extern const Color<> indigo;          //!<   - <span class="color:indigo"> indigo color </span>
		extern const Color<> ivory;           //!<   - <span class="color:ivory"> ivory color </span>
		extern const Color<> khaki;           //!<   - <span class="color:khaki"> khaki color </span>
		extern const Color<> lavender;        //!<   - <span class="color:lavender"> lavender color </span>
		extern const Color<> lavenderBlush;   //!<   - <span class="color:lavenderBlush"> lavenderBlush color </span>
		extern const Color<> lawnGreen;       //!<   - <span class="color:lawnGreen"> lawnGreen color </span>
		extern const Color<> lemonChiffon;    //!<   - <span class="color:lemonChiffon"> lemonChiffon color </span>
		extern const Color<> lightBlue;       //!<   - <span class="color:lightBlue"> lightBlue color </span>
		extern const Color<> lightCoral;      //!<   - <span class="color:lightCoral"> lightCoral color </span>
		extern const Color<> lightCyan;       //!<   - <span class="color:lightCyan"> lightCyan color </span>
		extern const Color<> lightGoldenRodYellow; //!<   - <span class="color:lightGoldenRodYellow"> lightGoldenRodYellow color </span>
		extern const Color<> lightGray;       //!<   - <span class="color:lightGray"> lightGray color </span>
		extern const Color<> lightGrey;       //!<   - <span class="color:lightGrey"> lightGrey color </span>
		extern const Color<> lightGreen;      //!<   - <span class="color:lightGreen"> lightGreen color </span>
		extern const Color<> lightPink;       //!<   - <span class="color:lightPink"> lightPink color </span>
		extern const Color<> lightSalmon;     //!<   - <span class="color:lightSalmon"> lightSalmon color </span>
		extern const Color<> lightSeaGreen;   //!<   - <span class="color:lightSeaGreen"> lightSeaGreen color </span>
		extern const Color<> lightSkyBlue;    //!<   - <span class="color:lightSkyBlue"> lightSkyBlue color </span>
		extern const Color<> lightSlateGray;  //!<   - <span class="color:lightSlateGray"> lightSlateGray color </span>
		extern const Color<> lightSlateGrey;  //!<   - <span class="color:lightSlateGrey"> lightSlateGrey color </span>
		extern const Color<> lightSteelBlue;  //!<   - <span class="color:lightSteelBlue"> lightSteelBlue color </span>
		extern const Color<> lightYellow;     //!<   - <span class="color:lightYellow"> lightYellow color </span>
		extern const Color<> lime;            //!<   - <span class="color:lime"> lime color </span>
		extern const Color<> limeGreen;       //!<   - <span class="color:limeGreen"> limeGreen color </span>
		extern const Color<> linen;           //!<   - <span class="color:linen"> linen color </span>
		extern const Color<> magenta;         //!<   - <span class="color:magenta"> magenta color </span>
		extern const Color<> maroon;          //!<   - <span class="color:maroon"> maroon color </span>
		extern const Color<> mediumAquaMarine; //!<   - <span class="color:mediumAquaMarine"> mediumAquaMarine color </span>
		extern const Color<> mediumBlue;      //!<   - <span class="color:mediumBlue"> mediumBlue color </span>
		extern const Color<> mediumOrchid;    //!<   - <span class="color:mediumOrchid"> mediumOrchid color </span>
		extern const Color<> mediumPurple;    //!<   - <span class="color:mediumPurple"> mediumPurple color </span>
		extern const Color<> mediumSeaGreen;  //!<   - <span class="color:mediumSeaGreen"> mediumSeaGreen color </span>
		extern const Color<> mediumSlateBlue; //!<   - <span class="color:mediumSlateBlue"> mediumSlateBlue color </span>
		extern const Color<> mediumSpringGreen; //!<   - <span class="color:mediumSpringGreen"> mediumSpringGreen color </span>
		extern const Color<> mediumTurquoise; //!<   - <span class="color:mediumTurquoise"> mediumTurquoise color </span>
		extern const Color<> mediumVioletRed; //!<   - <span class="color:mediumVioletRed"> mediumVioletRed color </span>
		extern const Color<> midnightBlue;    //!<   - <span class="color:midnightBlue"> midnightBlue color </span>
		extern const Color<> mintCream;       //!<   - <span class="color:mintCream"> mintCream color </span>
		extern const Color<> mistyRose;       //!<   - <span class="color:mistyRose"> mistyRose color </span>
		extern const Color<> moccasin;        //!<   - <span class="color:moccasin"> moccasin color </span>
		extern const Color<> navajoWhite;     //!<   - <span class="color:navajoWhite"> navajoWhite color </span>
		extern const Color<> navy;            //!<   - <span class="color:navy"> navy color </span>
		extern const Color<> oldLace;         //!<   - <span class="color:oldLace"> oldLace color </span>
		extern const Color<> olive;           //!<   - <span class="color:olive"> olive color </span>
		extern const Color<> oliveDrab;       //!<   - <span class="color:oliveDrab"> oliveDrab color </span>
		extern const Color<> orange;          //!<   - <span class="color:orange"> orange color </span>
		extern const Color<> orangeRed;       //!<   - <span class="color:orangeRed"> orangeRed color </span>
		extern const Color<> orchid;          //!<   - <span class="color:orchid"> orchid color </span>
		extern const Color<> paleGoldenRod;   //!<   - <span class="color:paleGoldenRod"> paleGoldenRod color </span>
		extern const Color<> paleGreen;       //!<   - <span class="color:paleGreen"> paleGreen color </span>
		extern const Color<> paleTurquoise;   //!<   - <span class="color:paleTurquoise"> paleTurquoise color </span>
		extern const Color<> paleVioletRed;   //!<   - <span class="color:paleVioletRed"> paleVioletRed color </span>
		extern const Color<> papayaWhip;      //!<   - <span class="color:papayaWhip"> papayaWhip color </span>
		extern const Color<> peachPuff;       //!<   - <span class="color:peachPuff"> peachPuff color </span>
		extern const Color<> peru;            //!<   - <span class="color:peru"> peru color </span>
		extern const Color<> pink;            //!<   - <span class="color:pink"> pink color </span>
		extern const Color<> plum;            //!<   - <span class="color:plum"> plum color </span>
		extern const Color<> powderBlue;      //!<   - <span class="color:powderBlue"> powderBlue color </span>
		extern const Color<> purple;          //!<   - <span class="color:purple"> purple color </span>
		extern const Color<> red;             //!<   - <span class="color:red"> red color </span>
		extern const Color<> rosyBrown;       //!<   - <span class="color:rosyBrown"> rosyBrown color </span>
		extern const Color<> royalBlue;       //!<   - <span class="color:royalBlue"> royalBlue color </span>
		extern const Color<> saddleBrown;     //!<   - <span class="color:saddleBrown"> saddleBrown color </span>
		extern const Color<> salmon;          //!<   - <span class="color:salmon"> salmon color </span>
		extern const Color<> sandyBrown;      //!<   - <span class="color:sandyBrown"> sandyBrown color </span>
		extern const Color<> seaGreen;        //!<   - <span class="color:seaGreen"> seaGreen color </span>
		extern const Color<> seaShell;        //!<   - <span class="color:seaShell"> seaShell color </span>
		extern const Color<> sienna;          //!<   - <span class="color:sienna"> sienna color </span>
		extern const Color<> silver;          //!<   - <span class="color:silver"> silver color </span>
		extern const Color<> skyBlue;         //!<   - <span class="color:skyBlue"> skyBlue color </span>
		extern const Color<> slateBlue;       //!<   - <span class="color:slateBlue"> slateBlue color </span>
		extern const Color<> slateGray;       //!<   - <span class="color:slateGray"> slateGray color </span>
		extern const Color<> slateGrey;       //!<   - <span class="color:slateGrey"> slateGrey color </span>
		extern const Color<> snow;            //!<   - <span class="color:snow"> snow color </span>
		extern const Color<> springGreen;     //!<   - <span class="color:springGreen"> springGreen color </span>
		extern const Color<> steelBlue;       //!<   - <span class="color:steelBlue"> steelBlue color </span>
		extern const Color<> tan;             //!<   - <span class="color:tan"> tan color </span>
		extern const Color<> teal;            //!<   - <span class="color:teal"> teal color </span>
		extern const Color<> thistle;         //!<   - <span class="color:thistle"> thistle color </span>
		extern const Color<> tomato;          //!<   - <span class="color:tomato"> tomato color </span>
		extern const Color<> turquoise;       //!<   - <span class="color:turquoise"> turquoise color </span>
		extern const Color<> violet;          //!<   - <span class="color:violet"> violet color </span>
		extern const Color<> wheat;           //!<   - <span class="color:wheat"> wheat color </span>
		extern const Color<> white;           //!<   - <span class="color:white"> white color </span>
		extern const Color<> whiteSmoke;      //!<   - <span class="color:whiteSmoke"> whiteSmoke color </span>
		extern const Color<> yellow;          //!<   - <span class="color:yellow"> yellow color </span>
		extern const Color<> yellowGreen;     //!<   - <span class="color:yellowGreen"> yellowGreen color </span>
	};
};


