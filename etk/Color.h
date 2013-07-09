/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_COLOR_H__
#define __ETK_COLOR_H__

#include <etk/UString.h>

namespace etk {
	template<class MY_TYPE=uint8_t> class Color
	{
		private:
			MY_TYPE m_r;
			MY_TYPE m_g;
			MY_TYPE m_b;
			MY_TYPE m_a;
		public :
			Color(void) { };
			Color(double _r, double _g, double _b, double _a=255) { Set((float)_r, (float)_g, (float)_b, (float)_a); };
			Color(float _r, float _g, float _b, float _a=255) { Set(_r, _g, _b, _a); };
			Color(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a=255) { Set(_r, _g, _b, _a); };
			Color(int _r, int _g, int _b, int _a=255) { Set(_r, _g, _b, _a); };
			Color(uint32_t _input)
			{
				Set((uint8_t)((_input&0xFF000000)>>24),
				    (uint8_t)((_input&0x00FF0000)>>16),
				    (uint8_t)((_input&0x0000FF00)>>8),
				    (uint8_t)((_input&0x000000FF)));
			};
			Color(const etk::Color<float>& _obj) { Set(_obj.r(), _obj.g(), _obj.b(), _obj.a()); };
			Color(const etk::Color<uint8_t>& _obj) { Set(_obj.r(), _obj.g(), _obj.b(), _obj.a()); };
			Color(const etk::UString& _input);
			~Color(void) { };
			Color<MY_TYPE>& operator=(const etk::Color<MY_TYPE>& _input)
			{
				m_r = _input.m_r;
				m_g = _input.m_g;
				m_b = _input.m_b;
				m_a = _input.m_a;
				return *this;
			};
			bool operator!= (const etk::Color<MY_TYPE>& _obj) const
			{
				if(    m_r != _obj.m_r
				    || m_g != _obj.m_g
				    || m_b != _obj.m_b
				    || m_a != _obj.m_a) {
					return true;
				}
				return false;
			}
			bool operator== (const etk::Color<MY_TYPE>& _obj) const
			{
				if(    m_r != _obj.m_r
				    || m_g != _obj.m_g
				    || m_b != _obj.m_b
				    || m_a != _obj.m_a) {
					return false;
				}
				return true;
			}
			uint32_t Get(void) const;
			void Set(float _r, float _g, float _b, float _a=255);
			void Set(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a=255);
			void Set(int _r, int _g, int _b, int _a=255)
			{
				Set((uint8_t)(etk_avg(0,_r,255)),
				    (uint8_t)(etk_avg(0,_g,255)),
				    (uint8_t)(etk_avg(0,_b,255)),
				    (uint8_t)(etk_avg(0,_a,255)) );
			}
			etk::UString GetHexString(void) const { return etk::UString(Get(), etk::UString::printModeHexadecimal, true); };
			etk::UString GetString(void) const { return etk::UString("#") + etk::UString(Get(), etk::UString::printModeHexadecimal); };
			MY_TYPE r(void) const { return m_r; };
			MY_TYPE g(void) const { return m_g; };
			MY_TYPE b(void) const { return m_b; };
			MY_TYPE a(void) const { return m_a; };
			void SetR(MY_TYPE _r) { m_r=_r; };
			void SetG(MY_TYPE _g) { m_g=_g; };
			void SetB(MY_TYPE _b) { m_b=_b; };
			void SetA(MY_TYPE _a) { m_a=_a; };
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

