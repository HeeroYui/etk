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
			 * @return true This is not the same color
			 * @return false This is the same color.
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
			/**
			 * @brief Equality comparaison operator.
			 * @param[in] _obj Color object to compare.
			 * @return true This is the same color.
			 * @return false The color are different.
			 */
			bool operator== (const etk::Color<MY_TYPE>& _obj) const {
				if(    m_r != _obj.m_r
				    || m_g != _obj.m_g
				    || m_b != _obj.m_b
				    || m_a != _obj.m_a) {
					return false;
				}
				return true;
			}
			/**
			 * @breif Get the Generic uint32_t value of the color
			 * @return Color in unsigned integer
			 */
			uint32_t get(void) const;
			/**
			 * @brief Set the specified color elements.
			 * @param[in] _r Red color.
			 * @param[in] _g Green color.
			 * @param[in] _b Blue color.
			 * @param[in] _a Alpha blending.
			 */
			void set(float _r, float _g, float _b, float _a=255);
			//! @previous
			void set(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a=255);
			//! @previous
			void set(int _r, int _g, int _b, int _a=255) {
				set((uint8_t)(etk_avg(0,_r,255)),
				    (uint8_t)(etk_avg(0,_g,255)),
				    (uint8_t)(etk_avg(0,_b,255)),
				    (uint8_t)(etk_avg(0,_a,255)) );
			}
			/**
			 * @brief Convert the color in an hexedecimal string ("0xFEDCBA98")
			 * @return The formated string
			 */
			std::string getHexString(void) const {
				std::ostringstream oss;
				oss << "0x" << std::setw(8) << std::setfill('0') << std::hex << get();
				return oss.str();
			};
			/**
			 * @brief Convert the color in an generic string value ("#FEDCBA98")
			 * @return The formated string
			 */
			std::string getString(void) const {
				std::ostringstream oss;
				oss << "#" << std::setw(8) << std::setfill('0') << std::hex << get();
				return oss.str();
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
	//! @not-in-doc
	etk::CCout& operator <<(etk::CCout &_os, const Color<uint8_t>& _obj);
	//! @not-in-doc
	etk::CCout& operator <<(etk::CCout &_os, const Color<float>& _obj);
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

