/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/types.h>

#ifndef __ETK_COLOR_H__
#define __ETK_COLOR_H__

#include <iomanip>

namespace etk {
	/**
	 * @brief The color class is a template to abstract the color implementation choice.
	 * 
	 * It is important to note that the color choice denpznd on the level of developent.
	 * For example :
	 * :** Graphic application use:
	 * ::** Image in 3/4 bytes for rgb(a)
	 * ::** Color description in char : '#F6780FFF' or the equivalent number:0xF6780FFF
	 * :** middleware will mainely use a the 4 separate value with 1 byte for each.
	 * :** graphic interface (openGL) store image in 1/2/3/4 bytes color and interpolate it in 'n' float. And note that the user color is sored in float.
	 * 
	 * Then with this class we abstract the transformation format and set an easy same way to use the color independing of the developpement level.
	 * 
	 * Some of the basic color is defined in the namespace: [namespace[etk::color]].
	 * 
	 * @template-param MY_TYPE Type of the internal template value. The generic value is uint8_t and float
	 */
	template<typename MY_TYPE=uint8_t, int MY_TYPE_SIZE=4> class Color {
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
			//! @previous
			Color(MY_TYPE _r, MY_TYPE _g, MY_TYPE _b) {
				set(_r, _g, _b);
			};
			//! @previous
			Color(MY_TYPE _r, MY_TYPE _g) {
				set(_r, _g);
			};
			//! @previous
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
				for (size_t iii=0; iii<MY_TYPE_SIZE; ++iii) {
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
				for (size_t iii=0; iii<MY_TYPE_SIZE; ++iii) {
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
				for (size_t iii=0; iii<MY_TYPE_SIZE; ++iii) {
					if(m_element[iii] != _obj.m_element[iii]) {
						return false;
					}
				}
				return true;
			}
			/**
			 * @breif Get the Generic uint32_t value of the color
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
			//! @previous
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
					m_element[3] = 0;
				}
			};
			//! @previous
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
					m_element[3] = 0;
				}
			};
			//! @previous
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
					m_element[3] = 0;
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
					return 0;
				}
			};
			/**
			 * @brief Set red color.
			 * @param[in] _r The red color to set.
			 */
			void setR(MY_TYPE _r) {
				if (MY_TYPE_SIZE >= 1) {
					m_element[0] = _r;
				}
			};
			/**
			 * @brief Set green color.
			 * @param[in] _g The green color to set.
			 */
			void setG(MY_TYPE _g) {
				if (MY_TYPE_SIZE >= 2) {
					m_element[1] = _g;
				}
			};
			/**
			 * @brief Set blue color.
			 * @param[in] _b The blue color to set.
			 */
			void setB(MY_TYPE _b) {
				if (MY_TYPE_SIZE >= 3) {
					m_element[2] = _b;
				}
			};
			/**
			 * @brief Set alpha blending.
			 * @param[in] _a The alpha blending to set.
			 */
			void setA(MY_TYPE _a) {
				if (MY_TYPE_SIZE >= 4) {
					m_element[3] = _a;
				}
			};
	};
	etk::Color<uint8_t, 4> parseStringStartWithSharp(const std::string& _input);
	etk::Color<uint8_t, 4> parseStringStartWithRGBGen(const std::string& _input);
	etk::Color<double, 4> parseStringStartWithRGB(const std::string& _input);
	etk::Color<uint32_t, 4> parseStringStartWithRGBUnsigned32(const std::string& _input);
	etk::Color<uint16_t, 4> parseStringStartWithRGBUnsigned16(const std::string& _input);
	etk::Color<uint8_t, 4> parseStringStartWithRGBUnsigned8(const std::string& _input);
	etk::Color<uint8_t, 4> parseStringColorNamed(const std::string& _input);
	
	template<> uint32_t Color<uint8_t, 4>::get() const;
	
	template<typename MY_TYPE, int MY_TYPE_SIZE> uint32_t Color<MY_TYPE, MY_TYPE_SIZE>::get() const {
		Color<uint8_t, 4> tmp(*this);
		return tmp.get();
	}
	
	template<typename MY_TYPE, int MY_TYPE_SIZE> Color<MY_TYPE, MY_TYPE_SIZE>::Color(const std::string& _input) {
		const char* inputData = _input.c_str();
		size_t len = _input.size();
		if(    len >=1
		    && inputData[0] == '#') {
			Color<uint8_t, 4> value = etk::parseStringStartWithSharp(std::string(_input, 1));
			*this = value;
		} else if(std::start_with(_input, "rgb(", false) == true) {
			Color<uint8_t, 4> value = etk::parseStringStartWithRGBGen(std::string(_input, 4, _input.size()-1));
			*this = value;
		} else if(std::start_with(_input, "rgb[FLOAT](", false) == true) {
			Color<double, 4> value = etk::parseStringStartWithRGB(std::string(_input, 11, _input.size()-1));
			*this = value;
		} else if(std::start_with(_input, "rgb[DOUBLE](", false) == true) {
			Color<double, 4> value = etk::parseStringStartWithRGB(std::string(_input, 12, _input.size()-1));
			*this = value;
		} else if(std::start_with(_input, "rgb[U32](", false) == true) {
			Color<uint32_t, 4> value = etk::parseStringStartWithRGBUnsigned32(std::string(_input, 9, _input.size()-1));
			*this = value;
		} else if(std::start_with(_input, "rgb[U16](", false) == true) {
			Color<uint16_t, 4> value = etk::parseStringStartWithRGBUnsigned16(std::string(_input, 9, _input.size()-1));
			*this = value;
		} else if(std::start_with(_input, "rgb[U8](", false) == true) {
			Color<uint8_t, 4> value = etk::parseStringStartWithRGBUnsigned8(std::string(_input, 8, _input.size()-1));
			*this = value;
		} else {
			Color<uint8_t, 4> value = etk::parseStringColorNamed(_input);
			*this = value;
		}
	};
	
	
	//! @not-in-doc
	template<int MY_TYPE_SIZE> std::ostream& operator <<(std::ostream& _os, const Color<uint8_t, MY_TYPE_SIZE>& _obj) { // RGB & RGBA 8 bits 
		if (MY_TYPE_SIZE >= 3) {
			_os << "#";
			_os << (std::to_string<uint32_t, 2>(_obj.r(), std::hex)).c_str();
			if (MY_TYPE_SIZE >= 2) {
				_os << (std::to_string<uint32_t, 2>(_obj.g(), std::hex)).c_str();
			}
			if (MY_TYPE_SIZE >= 3) {
				_os << (std::to_string<uint32_t, 2>(_obj.b(), std::hex)).c_str();
			}
			if (MY_TYPE_SIZE >= 4) {
				_os << (std::to_string<uint32_t, 2>(_obj.a(), std::hex)).c_str();
			}
		} else {
			if (MY_TYPE_SIZE >= 2) {
				_os << "be";
			} else {
				_os << "Mono";
			}
			_os << "[U8](";
			_os << "0x" << (std::to_string<uint32_t, 2>(_obj.r(), std::hex)).c_str();
			if (MY_TYPE_SIZE >= 2) {
				_os << ",";
				_os << "0x" << (std::to_string<uint32_t, 2>(_obj.g(), std::hex)).c_str();
			}
			_os << ")";
		}
		return _os;
	}
	//! @not-in-doc
	template<int MY_TYPE_SIZE> std::ostream& operator <<(std::ostream& _os, const Color<uint16_t, MY_TYPE_SIZE>& _obj) { // RGB & RGBA 8 bits 
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
		_os << "0x" << (std::to_string<uint32_t, 4>(_obj.r(), std::hex)).c_str();
		if (MY_TYPE_SIZE >= 2) {
			_os << ",";
			_os << "0x" << (std::to_string<uint32_t, 4>(_obj.g(), std::hex)).c_str();
		}
		if (MY_TYPE_SIZE >= 3) {
			_os << ",";
			_os << "0x" << (std::to_string<uint32_t, 4>(_obj.b(), std::hex)).c_str();
		}
		if (MY_TYPE_SIZE >= 4) {
			_os << ",";
			_os << "0x" << (std::to_string<uint32_t, 4>(_obj.a(), std::hex)).c_str();
		}
		_os << ")";
		return _os;
	}
	//! @not-in-doc
	template<int MY_TYPE_SIZE> std::ostream& operator <<(std::ostream& _os, const Color<uint32_t, MY_TYPE_SIZE>& _obj) { // RGB & RGBA 8 bits 
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
		_os << "0x" << (std::to_string<uint32_t, 8>(_obj.r(), std::hex)).c_str();
		if (MY_TYPE_SIZE >= 2) {
			_os << ",";
			_os << "0x" << (std::to_string<uint32_t, 8>(_obj.g(), std::hex)).c_str();
		}
		if (MY_TYPE_SIZE >= 3) {
			_os << ",";
			_os << "0x" << (std::to_string<uint32_t, 8>(_obj.b(), std::hex)).c_str();
		}
		if (MY_TYPE_SIZE >= 4) {
			_os << ",";
			_os << "0x" << (std::to_string<uint32_t, 8>(_obj.a(), std::hex)).c_str();
		}
		_os << ")";
		return _os;
	}
	//! @not-in-doc
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
	//! @not-in-doc
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
	//! @not-in-doc
	template<typename MY_TYPE, int MY_TYPE_SIZE> std::ostream& operator <<(std::ostream& _os, const std::vector<Color<MY_TYPE, MY_TYPE_SIZE> >& _obj) {
		for (size_t iii = 0; iii < _obj.size(); ++iii) {
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
		extern const Color<> aliceBlue;       //!< ++ [color=aliceBlue] aliceBlue color [/color] ++
		extern const Color<> antiqueWhite;    //!< ++ [color=antiqueWhite] antiqueWhite color [/color] ++
		extern const Color<> aqua;            //!< ++ [color=aqua] aqua color [/color] ++
		extern const Color<> aquamarine;      //!< ++ [color=aquamarine] aquamarine color [/color] ++
		extern const Color<> azure;           //!< ++ [color=azure] azure color [/color] ++
		extern const Color<> beige;           //!< ++ [color=beige] beige color [/color] ++
		extern const Color<> bisque;          //!< ++ [color=bisque] bisque color [/color] ++
		extern const Color<> black;           //!< ++ [color=black] black color [/color] ++
		extern const Color<> blanchedAlmond;  //!< ++ [color=blanchedAlmond] blanchedAlmond color [/color] ++
		extern const Color<> blue;            //!< ++ [color=blue] blue color [/color] ++
		extern const Color<> blueViolet;      //!< ++ [color=blueViolet] blueViolet color [/color] ++
		extern const Color<> brown;           //!< ++ [color=brown] brown color [/color] ++
		extern const Color<> burlyWood;       //!< ++ [color=burlyWood] burlyWood color [/color] ++
		extern const Color<> cadetBlue;       //!< ++ [color=cadetBlue] cadetBlue color [/color] ++
		extern const Color<> chartreuse;      //!< ++ [color=chartreuse] chartreuse color [/color] ++
		extern const Color<> chocolate;       //!< ++ [color=chocolate] chocolate color [/color] ++
		extern const Color<> coral;           //!< ++ [color=coral] coral color [/color] ++
		extern const Color<> cornflowerBlue;  //!< ++ [color=cornflowerBlue] cornflowerBlue color [/color] ++
		extern const Color<> cornsilk;        //!< ++ [color=cornsilk] cornsilk color [/color] ++
		extern const Color<> crimson;         //!< ++ [color=crimson] crimson color [/color] ++
		extern const Color<> cyan;            //!< ++ [color=cyan] cyan color [/color] ++
		extern const Color<> darkBlue;        //!< ++ [color=darkBlue] darkBlue color [/color] ++
		extern const Color<> darkCyan;        //!< ++ [color=darkCyan] darkCyan color [/color] ++
		extern const Color<> darkGoldenRod;   //!< ++ [color=darkGoldenRod] darkGoldenRod color [/color] ++
		extern const Color<> darkGray;        //!< ++ [color=darkGray] darkGray color [/color] ++
		extern const Color<> darkGrey;        //!< ++ [color=darkGrey] darkGrey color [/color] ++
		extern const Color<> darkGreen;       //!< ++ [color=darkGreen] darkGreen color [/color] ++
		extern const Color<> darkKhaki;       //!< ++ [color=darkKhaki] darkKhaki color [/color] ++
		extern const Color<> darkMagenta;     //!< ++ [color=darkMagenta] darkMagenta color [/color] ++
		extern const Color<> darkOliveGreen;  //!< ++ [color=darkOliveGreen] darkOliveGreen color [/color] ++
		extern const Color<> darkorange;      //!< ++ [color=darkorange] darkorange color [/color] ++
		extern const Color<> darkOrchid;      //!< ++ [color=darkOrchid] darkOrchid color [/color] ++
		extern const Color<> darkRed;         //!< ++ [color=darkRed] darkRed color [/color] ++
		extern const Color<> darkSalmon;      //!< ++ [color=darkSalmon] darkSalmon color [/color] ++
		extern const Color<> darkSeaGreen;    //!< ++ [color=darkSeaGreen] darkSeaGreen color [/color] ++
		extern const Color<> darkSlateBlue;   //!< ++ [color=darkSlateBlue] darkSlateBlue color [/color] ++
		extern const Color<> darkSlateGray;   //!< ++ [color=darkSlateGray] darkSlateGray color [/color] ++
		extern const Color<> darkSlateGrey;   //!< ++ [color=darkSlateGrey] darkSlateGrey color [/color] ++
		extern const Color<> darkTurquoise;   //!< ++ [color=darkTurquoise] darkTurquoise color [/color] ++
		extern const Color<> darkViolet;      //!< ++ [color=darkViolet] darkViolet color [/color] ++
		extern const Color<> deepPink;        //!< ++ [color=deepPink] deepPink color [/color] ++
		extern const Color<> deepSkyBlue;     //!< ++ [color=deepSkyBlue] deepSkyBlue color [/color] ++
		extern const Color<> dimGray;         //!< ++ [color=dimGray] dimGray color [/color] ++
		extern const Color<> dimGrey;         //!< ++ [color=dimGrey] dimGrey color [/color] ++
		extern const Color<> dodgerBlue;      //!< ++ [color=dodgerBlue] dodgerBlue color [/color] ++
		extern const Color<> fireBrick;       //!< ++ [color=fireBrick] fireBrick color [/color] ++
		extern const Color<> floralWhite;     //!< ++ [color=floralWhite] floralWhite color [/color] ++
		extern const Color<> forestGreen;     //!< ++ [color=forestGreen] forestGreen color [/color] ++
		extern const Color<> fuchsia;         //!< ++ [color=fuchsia] fuchsia color [/color] ++
		extern const Color<> gainsboro;       //!< ++ [color=gainsboro] gainsboro color [/color] ++
		extern const Color<> ghostWhite;      //!< ++ [color=ghostWhite] ghostWhite color [/color] ++
		extern const Color<> gold;            //!< ++ [color=gold] gold color [/color] ++
		extern const Color<> goldenRod;       //!< ++ [color=goldenRod] goldenRod color [/color] ++
		extern const Color<> gray;            //!< ++ [color=gray] gray color [/color] ++
		extern const Color<> grey;            //!< ++ [color=grey] grey color [/color] ++
		extern const Color<> green;           //!< ++ [color=green] green color [/color] ++
		extern const Color<> greenYellow;     //!< ++ [color=greenYellow] greenYellow color [/color] ++
		extern const Color<> honeyDew;        //!< ++ [color=honeyDew] honeyDew color [/color] ++
		extern const Color<> hotPink;         //!< ++ [color=hotPink] hotPink color [/color] ++
		extern const Color<> indianRed;       //!< ++ [color=indianRed] indianRed color [/color] ++
		extern const Color<> indigo;          //!< ++ [color=indigo] indigo color [/color] ++
		extern const Color<> ivory;           //!< ++ [color=ivory] ivory color [/color] ++
		extern const Color<> khaki;           //!< ++ [color=khaki] khaki color [/color] ++
		extern const Color<> lavender;        //!< ++ [color=lavender] lavender color [/color] ++
		extern const Color<> lavenderBlush;   //!< ++ [color=lavenderBlush] lavenderBlush color [/color] ++
		extern const Color<> lawnGreen;       //!< ++ [color=lawnGreen] lawnGreen color [/color] ++
		extern const Color<> lemonChiffon;    //!< ++ [color=lemonChiffon] lemonChiffon color [/color] ++
		extern const Color<> lightBlue;       //!< ++ [color=lightBlue] lightBlue color [/color] ++
		extern const Color<> lightCoral;      //!< ++ [color=lightCoral] lightCoral color [/color] ++
		extern const Color<> lightCyan;       //!< ++ [color=lightCyan] lightCyan color [/color] ++
		extern const Color<> lightGoldenRodYellow; //!< ++ [color=lightGoldenRodYellow] lightGoldenRodYellow color [/color] ++
		extern const Color<> lightGray;       //!< ++ [color=lightGray] lightGray color [/color] ++
		extern const Color<> lightGrey;       //!< ++ [color=lightGrey] lightGrey color [/color] ++
		extern const Color<> lightGreen;      //!< ++ [color=lightGreen] lightGreen color [/color] ++
		extern const Color<> lightPink;       //!< ++ [color=lightPink] lightPink color [/color] ++
		extern const Color<> lightSalmon;     //!< ++ [color=lightSalmon] lightSalmon color [/color] ++
		extern const Color<> lightSeaGreen;   //!< ++ [color=lightSeaGreen] lightSeaGreen color [/color] ++
		extern const Color<> lightSkyBlue;    //!< ++ [color=lightSkyBlue] lightSkyBlue color [/color] ++
		extern const Color<> lightSlateGray;  //!< ++ [color=lightSlateGray] lightSlateGray color [/color] ++
		extern const Color<> lightSlateGrey;  //!< ++ [color=lightSlateGrey] lightSlateGrey color [/color] ++
		extern const Color<> lightSteelBlue;  //!< ++ [color=lightSteelBlue] lightSteelBlue color [/color] ++
		extern const Color<> lightYellow;     //!< ++ [color=lightYellow] lightYellow color [/color] ++
		extern const Color<> lime;            //!< ++ [color=lime] lime color [/color] ++
		extern const Color<> limeGreen;       //!< ++ [color=limeGreen] limeGreen color [/color] ++
		extern const Color<> linen;           //!< ++ [color=linen] linen color [/color] ++
		extern const Color<> magenta;         //!< ++ [color=magenta] magenta color [/color] ++
		extern const Color<> maroon;          //!< ++ [color=maroon] maroon color [/color] ++
		extern const Color<> mediumAquaMarine; //!< ++ [color=mediumAquaMarine] mediumAquaMarine color [/color] ++
		extern const Color<> mediumBlue;      //!< ++ [color=mediumBlue] mediumBlue color [/color] ++
		extern const Color<> mediumOrchid;    //!< ++ [color=mediumOrchid] mediumOrchid color [/color] ++
		extern const Color<> mediumPurple;    //!< ++ [color=mediumPurple] mediumPurple color [/color] ++
		extern const Color<> mediumSeaGreen;  //!< ++ [color=mediumSeaGreen] mediumSeaGreen color [/color] ++
		extern const Color<> mediumSlateBlue; //!< ++ [color=mediumSlateBlue] mediumSlateBlue color [/color] ++
		extern const Color<> mediumSpringGreen; //!< ++ [color=mediumSpringGreen] mediumSpringGreen color [/color] ++
		extern const Color<> mediumTurquoise; //!< ++ [color=mediumTurquoise] mediumTurquoise color [/color] ++
		extern const Color<> mediumVioletRed; //!< ++ [color=mediumVioletRed] mediumVioletRed color [/color] ++
		extern const Color<> midnightBlue;    //!< ++ [color=midnightBlue] midnightBlue color [/color] ++
		extern const Color<> mintCream;       //!< ++ [color=mintCream] mintCream color [/color] ++
		extern const Color<> mistyRose;       //!< ++ [color=mistyRose] mistyRose color [/color] ++
		extern const Color<> moccasin;        //!< ++ [color=moccasin] moccasin color [/color] ++
		extern const Color<> navajoWhite;     //!< ++ [color=navajoWhite] navajoWhite color [/color] ++
		extern const Color<> navy;            //!< ++ [color=navy] navy color [/color] ++
		extern const Color<> oldLace;         //!< ++ [color=oldLace] oldLace color [/color] ++
		extern const Color<> olive;           //!< ++ [color=olive] olive color [/color] ++
		extern const Color<> oliveDrab;       //!< ++ [color=oliveDrab] oliveDrab color [/color] ++
		extern const Color<> orange;          //!< ++ [color=orange] orange color [/color] ++
		extern const Color<> orangeRed;       //!< ++ [color=orangeRed] orangeRed color [/color] ++
		extern const Color<> orchid;          //!< ++ [color=orchid] orchid color [/color] ++
		extern const Color<> paleGoldenRod;   //!< ++ [color=paleGoldenRod] paleGoldenRod color [/color] ++
		extern const Color<> paleGreen;       //!< ++ [color=paleGreen] paleGreen color [/color] ++
		extern const Color<> paleTurquoise;   //!< ++ [color=paleTurquoise] paleTurquoise color [/color] ++
		extern const Color<> paleVioletRed;   //!< ++ [color=paleVioletRed] paleVioletRed color [/color] ++
		extern const Color<> papayaWhip;      //!< ++ [color=papayaWhip] papayaWhip color [/color] ++
		extern const Color<> peachPuff;       //!< ++ [color=peachPuff] peachPuff color [/color] ++
		extern const Color<> peru;            //!< ++ [color=peru] peru color [/color] ++
		extern const Color<> pink;            //!< ++ [color=pink] pink color [/color] ++
		extern const Color<> plum;            //!< ++ [color=plum] plum color [/color] ++
		extern const Color<> powderBlue;      //!< ++ [color=powderBlue] powderBlue color [/color] ++
		extern const Color<> purple;          //!< ++ [color=purple] purple color [/color] ++
		extern const Color<> red;             //!< ++ [color=red] red color [/color] ++
		extern const Color<> rosyBrown;       //!< ++ [color=rosyBrown] rosyBrown color [/color] ++
		extern const Color<> royalBlue;       //!< ++ [color=royalBlue] royalBlue color [/color] ++
		extern const Color<> saddleBrown;     //!< ++ [color=saddleBrown] saddleBrown color [/color] ++
		extern const Color<> salmon;          //!< ++ [color=salmon] salmon color [/color] ++
		extern const Color<> sandyBrown;      //!< ++ [color=sandyBrown] sandyBrown color [/color] ++
		extern const Color<> seaGreen;        //!< ++ [color=seaGreen] seaGreen color [/color] ++
		extern const Color<> seaShell;        //!< ++ [color=seaShell] seaShell color [/color] ++
		extern const Color<> sienna;          //!< ++ [color=sienna] sienna color [/color] ++
		extern const Color<> silver;          //!< ++ [color=silver] silver color [/color] ++
		extern const Color<> skyBlue;         //!< ++ [color=skyBlue] skyBlue color [/color] ++
		extern const Color<> slateBlue;       //!< ++ [color=slateBlue] slateBlue color [/color] ++
		extern const Color<> slateGray;       //!< ++ [color=slateGray] slateGray color [/color] ++
		extern const Color<> slateGrey;       //!< ++ [color=slateGrey] slateGrey color [/color] ++
		extern const Color<> snow;            //!< ++ [color=snow] snow color [/color] ++
		extern const Color<> springGreen;     //!< ++ [color=springGreen] springGreen color [/color] ++
		extern const Color<> steelBlue;       //!< ++ [color=steelBlue] steelBlue color [/color] ++
		extern const Color<> tan;             //!< ++ [color=tan] tan color [/color] ++
		extern const Color<> teal;            //!< ++ [color=teal] teal color [/color] ++
		extern const Color<> thistle;         //!< ++ [color=thistle] thistle color [/color] ++
		extern const Color<> tomato;          //!< ++ [color=tomato] tomato color [/color] ++
		extern const Color<> turquoise;       //!< ++ [color=turquoise] turquoise color [/color] ++
		extern const Color<> violet;          //!< ++ [color=violet] violet color [/color] ++
		extern const Color<> wheat;           //!< ++ [color=wheat] wheat color [/color] ++
		extern const Color<> white;           //!< ++ [color=white] white color [/color] ++
		extern const Color<> whiteSmoke;      //!< ++ [color=whiteSmoke] whiteSmoke color [/color] ++
		extern const Color<> yellow;          //!< ++ [color=yellow] yellow color [/color] ++
		extern const Color<> yellowGreen;     //!< ++ [color=yellowGreen] yellowGreen color [/color] ++
	};
};

#endif

