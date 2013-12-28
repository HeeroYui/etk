/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_COLOR_H__
#define __ETK_COLOR_H__

#include <etk/types.h>

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
	template<class MY_TYPE=uint8_t> class Color {
		private:
			MY_TYPE m_r; //!< Red color value.
			MY_TYPE m_g; //!< Green color value.
			MY_TYPE m_b; //!< Blue color value
			MY_TYPE m_a; //!< Alpha blending value.
		public:
			/**
			 * @brief Constructor. It does not initialise element of class.
			 */
			Color(void) { };
			/**
			 * @brief Contructor with request initialisation.
			 * @param[in] _r Red color.
			 * @param[in] _g Green color.
			 * @param[in] _b Blue color.
			 * @param[in] _a Alpha blending.
			 */
			Color(double _r, double _g, double _b, double _a=255) {
				set((float)_r, (float)_g, (float)_b, (float)_a);
			};
			/**
			 * @previous
			 */
			Color(float _r, float _g, float _b, float _a=255) {
				set(_r, _g, _b, _a);
			};
			/**
			 * @previous
			 */
			Color(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a=255) {
				set(_r, _g, _b, _a);
			};
			/**
			 * @previous
			 */
			Color(int _r, int _g, int _b, int _a=255) {
				set(_r, _g, _b, _a);
			};
			/**
			 * @brief Constructor with the single integer input.
			 * @note Not forger the alpha blending at the end
			 * @param[in] _input rgba integer value : 0xrrggbbaa >> 0x99AF6DFF
			 */
			Color(uint32_t _input) {
				set((uint8_t)((_input&0xFF000000)>>24),
				    (uint8_t)((_input&0x00FF0000)>>16),
				    (uint8_t)((_input&0x0000FF00)>>8),
				    (uint8_t)((_input&0x000000FF)));
			};
			/**
			 * @brief Copy contructor or convert contructor
			 * @param[in] _obj Element to copy in this new color class.
			 */
			Color(const etk::Color<float>& _obj) {
				set(_obj.r(), _obj.g(), _obj.b(), _obj.a());
			};
			/**
			 * @previous
			 */
			Color(const etk::Color<uint8_t>& _obj) {
				set(_obj.r(), _obj.g(), _obj.b(), _obj.a());
			};
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
			Color<MY_TYPE>& operator=(const etk::Color<MY_TYPE>& _input) {
				m_r = _input.m_r;
				m_g = _input.m_g;
				m_b = _input.m_b;
				m_a = _input.m_a;
				return *this;
			};
			/**
			 * @brief Different comparaison operator.
			 * @param[in] _obj Color object to compare.
			 * @return true This is not the same color, false otherwise.
			 */
			bool operator!= (const etk::Color<MY_TYPE>& _obj) const {
				if(    m_r != _obj.m_r
				    || m_g != _obj.m_g
				    || m_b != _obj.m_b
				    || m_a != _obj.m_a) {
					return true;
				}
				return false;
			}
			
			bool operator== (const etk::Color<MY_TYPE>& _obj) const {
				if(    m_r != _obj.m_r
				    || m_g != _obj.m_g
				    || m_b != _obj.m_b
				    || m_a != _obj.m_a) {
					return false;
				}
				return true;
			}
			uint32_t get(void) const;
			void set(float _r, float _g, float _b, float _a=255);
			void set(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a=255);
			void set(int _r, int _g, int _b, int _a=255) {
				set((uint8_t)(etk_avg(0,_r,255)),
				    (uint8_t)(etk_avg(0,_g,255)),
				    (uint8_t)(etk_avg(0,_b,255)),
				    (uint8_t)(etk_avg(0,_a,255)) );
			}
			std::string getHexString(void) const {
				return "0x" + std::to_string<uint32_t>(get(), std::hex);
			};
			std::string getString(void) const {
				return "#"  + std::to_string<uint32_t>(get(), std::hex);
			};
			/**
			 * @brief Get red color.
			 * @return The red color.
			 */
			MY_TYPE r(void) const {
				return m_r;
			};
			/**
			 * @brief Get green color.
			 * @return The green color.
			 */
			MY_TYPE g(void) const {
				return m_g;
			};
			/**
			 * @brief Get blue color.
			 * @return The blue color.
			 */
			MY_TYPE b(void) const {
				return m_b;
			};
			/**
			 * @brief Get alpha blending.
			 * @return The alpha blending.
			 */
			MY_TYPE a(void) const {
				return m_a;
			};
			/**
			 * @brief Set red color.
			 * @param[in] _r The red color to set.
			 */
			void setR(MY_TYPE _r) {
				m_r=_r;
			};
			/**
			 * @brief Set green color.
			 * @param[in] _g The green color to set.
			 */
			void setG(MY_TYPE _g) {
				m_g=_g;
			};
			/**
			 * @brief Set blue color.
			 * @param[in] _b The blue color to set.
			 */
			void setB(MY_TYPE _b) {
				m_b=_b;
			};
			/**
			 * @brief Set alpha blending.
			 * @param[in] _a The alpha blending to set.
			 */
			void setA(MY_TYPE _a) {
				m_a=_a;
			};
	};
	etk::CCout& operator <<(etk::CCout &_os, const Color<uint8_t>& _obj);
	etk::CCout& operator <<(etk::CCout &_os, const Color<float>& _obj);
	
	namespace color {
		extern const Color<> none;
		extern const Color<> aliceBlue;
		extern const Color<> antiqueWhite;
		extern const Color<> aqua;
		extern const Color<> aquamarine;
		extern const Color<> azure;
		extern const Color<> beige;
		extern const Color<> bisque;
		extern const Color<> black;
		extern const Color<> blanchedAlmond;
		extern const Color<> blue;
		extern const Color<> blueViolet;
		extern const Color<> brown;
		extern const Color<> burlyWood;
		extern const Color<> cadetBlue;
		extern const Color<> chartreuse;
		extern const Color<> chocolate;
		extern const Color<> coral;
		extern const Color<> cornflowerBlue;
		extern const Color<> cornsilk;
		extern const Color<> crimson;
		extern const Color<> cyan;
		extern const Color<> darkBlue;
		extern const Color<> darkCyan;
		extern const Color<> darkGoldenRod;
		extern const Color<> darkGray;
		extern const Color<> darkGrey;
		extern const Color<> darkGreen;
		extern const Color<> darkKhaki;
		extern const Color<> darkMagenta;
		extern const Color<> darkOliveGreen;
		extern const Color<> darkorange;
		extern const Color<> darkOrchid;
		extern const Color<> darkRed;
		extern const Color<> darkSalmon;
		extern const Color<> darkSeaGreen;
		extern const Color<> darkSlateBlue;
		extern const Color<> darkSlateGray;
		extern const Color<> darkSlateGrey;
		extern const Color<> darkTurquoise;
		extern const Color<> darkViolet;
		extern const Color<> deepPink;
		extern const Color<> deepSkyBlue;
		extern const Color<> dimGray;
		extern const Color<> dimGrey;
		extern const Color<> dodgerBlue;
		extern const Color<> fireBrick;
		extern const Color<> floralWhite;
		extern const Color<> forestGreen;
		extern const Color<> fuchsia;
		extern const Color<> gainsboro;
		extern const Color<> ghostWhite;
		extern const Color<> gold;
		extern const Color<> goldenRod;
		extern const Color<> gray;
		extern const Color<> grey;
		extern const Color<> green;
		extern const Color<> greenYellow;
		extern const Color<> honeyDew;
		extern const Color<> hotPink;
		extern const Color<> indianRed;
		extern const Color<> indigo;
		extern const Color<> ivory;
		extern const Color<> khaki;
		extern const Color<> lavender;
		extern const Color<> lavenderBlush;
		extern const Color<> lawnGreen;
		extern const Color<> lemonChiffon;
		extern const Color<> lightBlue;
		extern const Color<> lightCoral;
		extern const Color<> lightCyan;
		extern const Color<> lightGoldenRodYellow;
		extern const Color<> lightGray;
		extern const Color<> lightGrey;
		extern const Color<> lightGreen;
		extern const Color<> lightPink;
		extern const Color<> lightSalmon;
		extern const Color<> lightSeaGreen;
		extern const Color<> lightSkyBlue;
		extern const Color<> lightSlateGray;
		extern const Color<> lightSlateGrey;
		extern const Color<> lightSteelBlue;
		extern const Color<> lightYellow;
		extern const Color<> lime;
		extern const Color<> limeGreen;
		extern const Color<> linen;
		extern const Color<> magenta;
		extern const Color<> maroon;
		extern const Color<> mediumAquaMarine;
		extern const Color<> mediumBlue;
		extern const Color<> mediumOrchid;
		extern const Color<> mediumPurple;
		extern const Color<> mediumSeaGreen;
		extern const Color<> mediumSlateBlue;
		extern const Color<> mediumSpringGreen;
		extern const Color<> mediumTurquoise;
		extern const Color<> mediumVioletRed;
		extern const Color<> midnightBlue;
		extern const Color<> mintCream;
		extern const Color<> mistyRose;
		extern const Color<> moccasin;
		extern const Color<> navajoWhite;
		extern const Color<> navy;
		extern const Color<> oldLace;
		extern const Color<> olive;
		extern const Color<> oliveDrab;
		extern const Color<> orange;
		extern const Color<> orangeRed;
		extern const Color<> orchid;
		extern const Color<> paleGoldenRod;
		extern const Color<> paleGreen;
		extern const Color<> paleTurquoise;
		extern const Color<> paleVioletRed;
		extern const Color<> papayaWhip;
		extern const Color<> peachPuff;
		extern const Color<> peru;
		extern const Color<> pink;
		extern const Color<> plum;
		extern const Color<> powderBlue;
		extern const Color<> purple;
		extern const Color<> red;
		extern const Color<> rosyBrown;
		extern const Color<> royalBlue;
		extern const Color<> saddleBrown;
		extern const Color<> salmon;
		extern const Color<> sandyBrown;
		extern const Color<> seaGreen;
		extern const Color<> seaShell;
		extern const Color<> sienna;
		extern const Color<> silver;
		extern const Color<> skyBlue;
		extern const Color<> slateBlue;
		extern const Color<> slateGray;
		extern const Color<> slateGrey;
		extern const Color<> snow;
		extern const Color<> springGreen;
		extern const Color<> steelBlue;
		extern const Color<> tan;
		extern const Color<> teal;
		extern const Color<> thistle;
		extern const Color<> tomato;
		extern const Color<> turquoise;
		extern const Color<> violet;
		extern const Color<> wheat;
		extern const Color<> white;
		extern const Color<> whiteSmoke;
		extern const Color<> yellow;
		extern const Color<> yellowGreen;
	};
};

#endif

