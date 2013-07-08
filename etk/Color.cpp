/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/types.h>
#include <etk/tool.h>
#include <etk/Color.h>
#include <etk/DebugInternal.h>

static bool strnCmpNoCase(const char * input1, const char * input2, int32_t maxLen)
{
	int32_t iii=0;
	while ('\0' != *input1 && '\0' != *input2 && iii < maxLen) {
		char in1 = *input1;
		char in2 = *input2;
		if (in1 != in2) {
			if (in1 <= 'Z' && in1 >= 'A') {
				in1 = in1 - 'A' + 'a';
			}
			if (in2 <= 'Z' && in2 >= 'A') {
				in2 = in2 - 'A' + 'a';
			}
			if (in1 != in2) {
				return false;
			}
		}
		iii++;
		input1++;
		input2++;
	}
	return true;
}

typedef struct {
	const char * colorName;
	etk::Color<> color;
} colorList_ts;

static esize_t GetColorSize(void);
static const colorList_ts* GetColorList(void);

namespace etk
{
	template<> void Color<uint8_t>::Set(float _r, float _g, float _b, float _a)
	{
		m_r = (uint8_t)(_r*255.0f);
		m_g = (uint8_t)(_g*255.0f);
		m_b = (uint8_t)(_b*255.0f);
		m_a = (uint8_t)(_a*255.0f);
	}
	
	template<> void Color<float>::Set(float _r, float _g, float _b, float _a)
	{
		m_r = _r;
		m_g = _g;
		m_b = _b;
		m_a = _a;
	}
	
	template<> void Color<uint8_t>::Set(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a)
	{
		m_r = _r;
		m_g = _g;
		m_b = _b;
		m_a = _a;
	}
	
	template<> void Color<float>::Set(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a)
	{
		m_r = ((float)_r)/255.0f;
		m_g = ((float)_g)/255.0f;
		m_b = ((float)_b)/255.0f;
		m_a = ((float)_a)/255.0f;
	}
	
	template<> uint32_t Color<uint8_t>::Get(void) const
	{
		return   (((uint32_t)m_r)<<24)
		       + (((uint32_t)m_g)<<16)
		       + (((uint32_t)m_b)<<8)
		       + (uint32_t)m_a;
	}
	
	template<> uint32_t Color<float>::Get(void) const
	{
		return Color<uint8_t>(*this).Get();
	}
	
	template<> Color<uint8_t>::Color(const etk::UString& _input) :
		m_r(255),
		m_g(255),
		m_b(255),
		m_a(255)
	{
		etk::Char input = _input.c_str();
		const char* inputData = input;
		size_t len = strlen(input);
		if(    len >=1
		    && inputData[0] == '#') {
			if(len == 4) {
				int32_t red=0, green=0, blue=0;
				if (sscanf(inputData + 1, "%1x%1x%1x", &red, &green, &blue) == 3) {
					m_r = (red | red << 4);
					m_g = (green | green << 4);
					m_b = (blue | blue << 4);
				} else {
					TK_ERROR(" pb in parsing the color : \"" << inputData << "\"");
				}
			} else if (len==5) {
				int32_t red=0, green=0, blue=0, alpha=0;
				if (sscanf(inputData + 1, "%1x%1x%1x%1x", &red, &green, &blue, &alpha) == 4) {
					m_r = (red | red << 4);
					m_g = (green | green << 4);
					m_b = (blue | blue << 4);
					m_a = (alpha | alpha << 4);
				} else {
					TK_ERROR(" pb in parsing the color : \"" << inputData << "\"");
				}
			} else if (len == 7) {
				int32_t red=0, green=0, blue=0;
				if (sscanf(inputData + 1, "%2x%2x%2x", &red, &green, &blue) == 3) {
					m_r = red;
					m_g = green;
					m_b = blue;
				} else {
					TK_ERROR(" pb in parsing the color : \"" << inputData << "\"");
				}
			} else if (len == 9) {
				int32_t red=0, green=0, blue=0, alpha=0;
				if (sscanf(inputData + 1, "%2x%2x%2x%2x", &red, &green, &blue, &alpha) == 4) {
					m_r = red;
					m_g = green;
					m_b = blue;
					m_a = alpha;
				} else {
					TK_ERROR(" pb in parsing the color : \"" << inputData << "\"");
				}
			} else {
				TK_ERROR(" pb in parsing the color : \"" << inputData << "\" ==> unknown methode ...");
			}
		} else if(    4 <= len
		           && inputData[0] == 'r'
		           && inputData[1] == 'g'
		           && inputData[2] == 'b'
		           && inputData[3] == '(' ) {
			int32_t _red=0, _green=0, _blue=0, _alpha=0;
			float   fred=0, fgreen=0, fblue=0, falpha=0;
			if (sscanf(inputData + 4, "%u,%u,%u,%u", &_red, &_green, &_blue, &_alpha) == 4) {
				m_r = etk_min(0xFF, _red);
				m_g = etk_min(0xFF, _green);
				m_b = etk_min(0xFF, _blue);
				m_a = etk_min(0xFF, _alpha);
			} else if (sscanf(inputData + 4, "%u,%u,%u", &_red, &_green, &_blue) == 3) {
				m_r = etk_min(0xFF, _red);
				m_g = etk_min(0xFF, _green);
				m_b = etk_min(0xFF, _blue);
			} else if (sscanf(inputData + 4, "%f%%,%f%%,%f%%,%f%%", &fred, &fgreen, &fblue, &falpha) == 4) {
				fred   = etk_avg(0.0, fred, 1.0);
				fgreen = etk_avg(0.0, fgreen, 1.0);
				fblue  = etk_avg(0.0, fblue, 1.0);
				falpha = etk_avg(0.0, falpha, 1.0);
				m_r = (uint8_t)(fred * 255.);
				m_g = (uint8_t)(fgreen * 255.);
				m_b = (uint8_t)(fblue * 255.);
				m_a = (uint8_t)(falpha * 255.);
			} else if (sscanf(inputData + 4, "%f%%,%f%%,%f%%", &fred, &fgreen, &fblue) == 3) {
				fred  = etk_avg(0.0, fred, 1.0);
				fgreen= etk_avg(0.0, fgreen, 1.0);
				fblue = etk_avg(0.0, fblue, 1.0);
				m_r = (uint8_t)(fred * 255.);
				m_g = (uint8_t)(fgreen * 255.);
				m_b = (uint8_t)(fblue * 255.);
			} else {
				TK_ERROR(" pb in parsing the color : \"" << inputData << "\" ==> unknown methode ...");
			}
		} else {
			bool findIt = false;
			// direct named color ...
			for (esize_t iii=0; iii<GetColorSize(); iii++) {
				if (strnCmpNoCase(GetColorList()[iii].colorName, inputData, strlen(GetColorList()[iii].colorName)) == true) {
					findIt = true;
					*this = GetColorList()[iii].color;
					// stop searching
					break;
				}
			}
			// not find color ...
			if (findIt == false) {
				TK_ERROR(" pb in parsing the color : \"" << inputData << "\" not find ...");
			}
		}
		TK_VERBOSE("Parse color : \"" << inputData << "\" ==> " << *this);
	}
	
	template<> Color<float>::Color(const etk::UString& _input)
	{
		etk::Color<uint8_t> tmpColor(_input);
		*this = tmpColor;
	}
};

etk::CCout& etk::operator <<(etk::CCout &_os, const etk::Color<uint8_t>& _obj)
{
	_os << _obj.GetString();
	return _os;
}
etk::CCout& etk::operator <<(etk::CCout &_os, const etk::Color<float>& _obj)
{
	_os << "rgba(";
	_os << _obj.r();
	_os << ",";
	_os << _obj.g();
	_os << ",";
	_os << _obj.b();
	_os << ",";
	_os << _obj.a();
	_os << ")";
	return _os;
}





const etk::Color<> etk::color::none((uint32_t)0x00000000);
const etk::Color<> etk::color::aliceBlue((uint32_t)0xF0F8FFFF);
const etk::Color<> etk::color::antiqueWhite((uint32_t)0xFAEBD7FF);
const etk::Color<> etk::color::aqua((uint32_t)0x00FFFFFF);
const etk::Color<> etk::color::aquamarine((uint32_t)0x7FFFD4FF);
const etk::Color<> etk::color::azure((uint32_t)0xF0FFFFFF);
const etk::Color<> etk::color::beige((uint32_t)0xF5F5DCFF);
const etk::Color<> etk::color::bisque((uint32_t)0xFFE4C4FF);
const etk::Color<> etk::color::black((uint32_t)0x000000FF);
const etk::Color<> etk::color::blanchedAlmond((uint32_t)0xFFEBCDFF);
const etk::Color<> etk::color::blue((uint32_t)0x0000FFFF);
const etk::Color<> etk::color::blueViolet((uint32_t)0x8A2BE2FF);
const etk::Color<> etk::color::brown((uint32_t)0xA52A2AFF);
const etk::Color<> etk::color::burlyWood((uint32_t)0xDEB887FF);
const etk::Color<> etk::color::cadetBlue((uint32_t)0x5F9EA0FF);
const etk::Color<> etk::color::chartreuse((uint32_t)0x7FFF00FF);
const etk::Color<> etk::color::chocolate((uint32_t)0xD2691EFF);
const etk::Color<> etk::color::coral((uint32_t)0xFF7F50FF);
const etk::Color<> etk::color::cornflowerBlue((uint32_t)0x6495EDFF);
const etk::Color<> etk::color::cornsilk((uint32_t)0xFFF8DCFF);
const etk::Color<> etk::color::crimson((uint32_t)0xDC143CFF);
const etk::Color<> etk::color::cyan((uint32_t)0x00FFFFFF);
const etk::Color<> etk::color::darkBlue((uint32_t)0x00008BFF);
const etk::Color<> etk::color::darkCyan((uint32_t)0x008B8BFF);
const etk::Color<> etk::color::darkGoldenRod((uint32_t)0xB8860BFF);
const etk::Color<> etk::color::darkGray((uint32_t)0xA9A9A9FF);
const etk::Color<> etk::color::darkGrey((uint32_t)0xA9A9A9FF);
const etk::Color<> etk::color::darkGreen((uint32_t)0x006400FF);
const etk::Color<> etk::color::darkKhaki((uint32_t)0xBDB76BFF);
const etk::Color<> etk::color::darkMagenta((uint32_t)0x8B008BFF);
const etk::Color<> etk::color::darkOliveGreen((uint32_t)0x556B2FFF);
const etk::Color<> etk::color::darkorange((uint32_t)0xFF8C00FF);
const etk::Color<> etk::color::darkOrchid((uint32_t)0x9932CCFF);
const etk::Color<> etk::color::darkRed((uint32_t)0x8B0000FF);
const etk::Color<> etk::color::darkSalmon((uint32_t)0xE9967AFF);
const etk::Color<> etk::color::darkSeaGreen((uint32_t)0x8FBC8FFF);
const etk::Color<> etk::color::darkSlateBlue((uint32_t)0x483D8BFF);
const etk::Color<> etk::color::darkSlateGray((uint32_t)0x2F4F4FFF);
const etk::Color<> etk::color::darkSlateGrey((uint32_t)0x2F4F4FFF);
const etk::Color<> etk::color::darkTurquoise((uint32_t)0x00CED1FF);
const etk::Color<> etk::color::darkViolet((uint32_t)0x9400D3FF);
const etk::Color<> etk::color::deepPink((uint32_t)0xFF1493FF);
const etk::Color<> etk::color::deepSkyBlue((uint32_t)0x00BFFFFF);
const etk::Color<> etk::color::dimGray((uint32_t)0x696969FF);
const etk::Color<> etk::color::dimGrey((uint32_t)0x696969FF);
const etk::Color<> etk::color::dodgerBlue((uint32_t)0x1E90FFFF);
const etk::Color<> etk::color::fireBrick((uint32_t)0xB22222FF);
const etk::Color<> etk::color::floralWhite((uint32_t)0xFFFAF0FF);
const etk::Color<> etk::color::forestGreen((uint32_t)0x228B22FF);
const etk::Color<> etk::color::fuchsia((uint32_t)0xFF00FFFF);
const etk::Color<> etk::color::gainsboro((uint32_t)0xDCDCDCFF);
const etk::Color<> etk::color::ghostWhite((uint32_t)0xF8F8FFFF);
const etk::Color<> etk::color::gold((uint32_t)0xFFD700FF);
const etk::Color<> etk::color::goldenRod((uint32_t)0xDAA520FF);
const etk::Color<> etk::color::gray((uint32_t)0x808080FF);
const etk::Color<> etk::color::grey((uint32_t)0x808080FF);
const etk::Color<> etk::color::green((uint32_t)0x008000FF);
const etk::Color<> etk::color::greenYellow((uint32_t)0xADFF2FFF);
const etk::Color<> etk::color::honeyDew((uint32_t)0xF0FFF0FF);
const etk::Color<> etk::color::hotPink((uint32_t)0xFF69B4FF);
const etk::Color<> etk::color::indianRed ((uint32_t)0xCD5C5CFF);
const etk::Color<> etk::color::indigo ((uint32_t)0x4B0082FF);
const etk::Color<> etk::color::ivory((uint32_t)0xFFFFF0FF);
const etk::Color<> etk::color::khaki((uint32_t)0xF0E68CFF);
const etk::Color<> etk::color::lavender((uint32_t)0xE6E6FAFF);
const etk::Color<> etk::color::lavenderBlush((uint32_t)0xFFF0F5FF);
const etk::Color<> etk::color::lawnGreen((uint32_t)0x7CFC00FF);
const etk::Color<> etk::color::lemonChiffon((uint32_t)0xFFFACDFF);
const etk::Color<> etk::color::lightBlue((uint32_t)0xADD8E6FF);
const etk::Color<> etk::color::lightCoral((uint32_t)0xF08080FF);
const etk::Color<> etk::color::lightCyan((uint32_t)0xE0FFFFFF);
const etk::Color<> etk::color::lightGoldenRodYellow((uint32_t)0xFAFAD2FF);
const etk::Color<> etk::color::lightGray((uint32_t)0xD3D3D3FF);
const etk::Color<> etk::color::lightGrey((uint32_t)0xD3D3D3FF);
const etk::Color<> etk::color::lightGreen((uint32_t)0x90EE90FF);
const etk::Color<> etk::color::lightPink((uint32_t)0xFFB6C1FF);
const etk::Color<> etk::color::lightSalmon((uint32_t)0xFFA07AFF);
const etk::Color<> etk::color::lightSeaGreen((uint32_t)0x20B2AAFF);
const etk::Color<> etk::color::lightSkyBlue((uint32_t)0x87CEFAFF);
const etk::Color<> etk::color::lightSlateGray((uint32_t)0x778899FF);
const etk::Color<> etk::color::lightSlateGrey((uint32_t)0x778899FF);
const etk::Color<> etk::color::lightSteelBlue((uint32_t)0xB0C4DEFF);
const etk::Color<> etk::color::lightYellow((uint32_t)0xFFFFE0FF);
const etk::Color<> etk::color::lime((uint32_t)0x00FF00FF);
const etk::Color<> etk::color::limeGreen((uint32_t)0x32CD32FF);
const etk::Color<> etk::color::linen((uint32_t)0xFAF0E6FF);
const etk::Color<> etk::color::magenta((uint32_t)0xFF00FFFF);
const etk::Color<> etk::color::maroon((uint32_t)0x800000FF);
const etk::Color<> etk::color::mediumAquaMarine((uint32_t)0x66CDAAFF);
const etk::Color<> etk::color::mediumBlue((uint32_t)0x0000CDFF);
const etk::Color<> etk::color::mediumOrchid((uint32_t)0xBA55D3FF);
const etk::Color<> etk::color::mediumPurple((uint32_t)0x9370D8FF);
const etk::Color<> etk::color::mediumSeaGreen((uint32_t)0x3CB371FF);
const etk::Color<> etk::color::mediumSlateBlue((uint32_t)0x7B68EEFF);
const etk::Color<> etk::color::mediumSpringGreen((uint32_t)0x00FA9AFF);
const etk::Color<> etk::color::mediumTurquoise((uint32_t)0x48D1CCFF);
const etk::Color<> etk::color::mediumVioletRed((uint32_t)0xC71585FF);
const etk::Color<> etk::color::midnightBlue((uint32_t)0x191970FF);
const etk::Color<> etk::color::mintCream((uint32_t)0xF5FFFAFF);
const etk::Color<> etk::color::mistyRose((uint32_t)0xFFE4E1FF);
const etk::Color<> etk::color::moccasin((uint32_t)0xFFE4B5FF);
const etk::Color<> etk::color::navajoWhite((uint32_t)0xFFDEADFF);
const etk::Color<> etk::color::navy((uint32_t)0x000080FF);
const etk::Color<> etk::color::oldLace((uint32_t)0xFDF5E6FF);
const etk::Color<> etk::color::olive((uint32_t)0x808000FF);
const etk::Color<> etk::color::oliveDrab((uint32_t)0x6B8E23FF);
const etk::Color<> etk::color::orange((uint32_t)0xFFA500FF);
const etk::Color<> etk::color::orangeRed((uint32_t)0xFF4500FF);
const etk::Color<> etk::color::orchid((uint32_t)0xDA70D6FF);
const etk::Color<> etk::color::paleGoldenRod((uint32_t)0xEEE8AAFF);
const etk::Color<> etk::color::paleGreen((uint32_t)0x98FB98FF);
const etk::Color<> etk::color::paleTurquoise((uint32_t)0xAFEEEEFF);
const etk::Color<> etk::color::paleVioletRed((uint32_t)0xD87093FF);
const etk::Color<> etk::color::papayaWhip((uint32_t)0xFFEFD5FF);
const etk::Color<> etk::color::peachPuff((uint32_t)0xFFDAB9FF);
const etk::Color<> etk::color::peru((uint32_t)0xCD853FFF);
const etk::Color<> etk::color::pink((uint32_t)0xFFC0CBFF);
const etk::Color<> etk::color::plum((uint32_t)0xDDA0DDFF);
const etk::Color<> etk::color::powderBlue((uint32_t)0xB0E0E6FF);
const etk::Color<> etk::color::purple((uint32_t)0x800080FF);
const etk::Color<> etk::color::red((uint32_t)0xFF0000FF);
const etk::Color<> etk::color::rosyBrown((uint32_t)0xBC8F8FFF);
const etk::Color<> etk::color::royalBlue((uint32_t)0x4169E1FF);
const etk::Color<> etk::color::saddleBrown((uint32_t)0x8B4513FF);
const etk::Color<> etk::color::salmon((uint32_t)0xFA8072FF);
const etk::Color<> etk::color::sandyBrown((uint32_t)0xF4A460FF);
const etk::Color<> etk::color::seaGreen((uint32_t)0x2E8B57FF);
const etk::Color<> etk::color::seaShell((uint32_t)0xFFF5EEFF);
const etk::Color<> etk::color::sienna((uint32_t)0xA0522DFF);
const etk::Color<> etk::color::silver((uint32_t)0xC0C0C0FF);
const etk::Color<> etk::color::skyBlue((uint32_t)0x87CEEBFF);
const etk::Color<> etk::color::slateBlue((uint32_t)0x6A5ACDFF);
const etk::Color<> etk::color::slateGray((uint32_t)0x708090FF);
const etk::Color<> etk::color::slateGrey((uint32_t)0x708090FF);
const etk::Color<> etk::color::snow((uint32_t)0xFFFAFAFF);
const etk::Color<> etk::color::springGreen((uint32_t)0x00FF7FFF);
const etk::Color<> etk::color::steelBlue((uint32_t)0x4682B4FF);
const etk::Color<> etk::color::tan((uint32_t)0xD2B48CFF);
const etk::Color<> etk::color::teal((uint32_t)0x008080FF);
const etk::Color<> etk::color::thistle((uint32_t)0xD8BFD8FF);
const etk::Color<> etk::color::tomato((uint32_t)0xFF6347FF);
const etk::Color<> etk::color::turquoise((uint32_t)0x40E0D0FF);
const etk::Color<> etk::color::violet((uint32_t)0xEE82EEFF);
const etk::Color<> etk::color::wheat((uint32_t)0xF5DEB3FF);
const etk::Color<> etk::color::white((uint32_t)0xFFFFFFFF);
const etk::Color<> etk::color::whiteSmoke((uint32_t)0xF5F5F5FF);
const etk::Color<> etk::color::yellow((uint32_t)0xFFFF00FF);
const etk::Color<> etk::color::yellowGreen((uint32_t)0x9ACD32FF);

static const colorList_ts listOfColor[] = {
	{ "none",				etk::color::none},
	{ "AliceBlue",			etk::color::aliceBlue},
	{ "AntiqueWhite",		etk::color::antiqueWhite},
	{ "Aqua",				etk::color::aqua},
	{ "Aquamarine",			etk::color::aquamarine},
	{ "Azure",				etk::color::azure},
	{ "Beige",				etk::color::beige},
	{ "Bisque",				etk::color::bisque},
	{ "Black",				etk::color::black},
	{ "BlanchedAlmond",		etk::color::blanchedAlmond},
	{ "Blue",				etk::color::blue},
	{ "BlueViolet",			etk::color::blueViolet},
	{ "Brown",				etk::color::brown},
	{ "BurlyWood",			etk::color::burlyWood},
	{ "CadetBlue",			etk::color::cadetBlue},
	{ "Chartreuse",			etk::color::chartreuse},
	{ "Chocolate",			etk::color::chocolate},
	{ "Coral",				etk::color::coral},
	{ "CornflowerBlue",		etk::color::cornflowerBlue},
	{ "Cornsilk",			etk::color::cornsilk},
	{ "Crimson",			etk::color::crimson},
	{ "Cyan",				etk::color::cyan},
	{ "DarkBlue",			etk::color::darkBlue},
	{ "DarkCyan",			etk::color::darkCyan},
	{ "DarkGoldenRod",		etk::color::darkGoldenRod},
	{ "DarkGray",			etk::color::darkGray},
	{ "DarkGrey",			etk::color::darkGrey},
	{ "DarkGreen",			etk::color::darkGreen},
	{ "DarkKhaki",			etk::color::darkKhaki},
	{ "DarkMagenta",		etk::color::darkMagenta},
	{ "DarkOliveGreen",		etk::color::darkOliveGreen},
	{ "Darkorange",			etk::color::darkorange},
	{ "DarkOrchid",			etk::color::darkOrchid},
	{ "DarkRed",			etk::color::darkRed},
	{ "DarkSalmon",			etk::color::darkSalmon},
	{ "DarkSeaGreen",		etk::color::darkSeaGreen},
	{ "DarkSlateBlue",		etk::color::darkSlateBlue},
	{ "DarkSlateGray",		etk::color::darkSlateGray},
	{ "DarkSlateGrey",		etk::color::darkSlateGrey},
	{ "DarkTurquoise",		etk::color::darkTurquoise},
	{ "DarkViolet",			etk::color::darkViolet},
	{ "DeepPink",			etk::color::deepPink},
	{ "DeepSkyBlue",		etk::color::deepSkyBlue},
	{ "DimGray",			etk::color::dimGray},
	{ "DimGrey",			etk::color::dimGrey},
	{ "DodgerBlue",			etk::color::dodgerBlue},
	{ "FireBrick",			etk::color::fireBrick},
	{ "FloralWhite",		etk::color::floralWhite},
	{ "ForestGreen",		etk::color::forestGreen},
	{ "Fuchsia",			etk::color::fuchsia},
	{ "Gainsboro",			etk::color::gainsboro},
	{ "GhostWhite",			etk::color::ghostWhite},
	{ "Gold",				etk::color::gold},
	{ "GoldenRod",			etk::color::goldenRod},
	{ "Gray",				etk::color::gray},
	{ "Grey",				etk::color::grey},
	{ "Green",				etk::color::green},
	{ "GreenYellow",		etk::color::greenYellow},
	{ "HoneyDew",			etk::color::honeyDew},
	{ "HotPink",			etk::color::hotPink},
	{ "IndianRed",			etk::color::indianRed},
	{ "Indigo",				etk::color::indigo},
	{ "Ivory",				etk::color::ivory},
	{ "Khaki",				etk::color::khaki},
	{ "Lavender",			etk::color::lavender},
	{ "LavenderBlush",		etk::color::lavenderBlush},
	{ "LawnGreen",			etk::color::lawnGreen},
	{ "LemonChiffon",		etk::color::lemonChiffon},
	{ "LightBlue",			etk::color::lightBlue},
	{ "LightCoral",			etk::color::lightCoral},
	{ "LightCyan",			etk::color::lightCyan},
	{ "LightGoldenRodYellow",	etk::color::lightGoldenRodYellow},
	{ "LightGray",			etk::color::lightGray},
	{ "LightGrey",			etk::color::lightGrey},
	{ "LightGreen",			etk::color::lightGreen},
	{ "LightPink",			etk::color::lightPink},
	{ "LightSalmon",		etk::color::lightSalmon},
	{ "LightSeaGreen",		etk::color::lightSeaGreen},
	{ "LightSkyBlue",		etk::color::lightSkyBlue},
	{ "LightSlateGray",		etk::color::lightSlateGray},
	{ "LightSlateGrey",		etk::color::lightSlateGrey},
	{ "LightSteelBlue",		etk::color::lightSteelBlue},
	{ "LightYellow",		etk::color::lightYellow},
	{ "Lime",				etk::color::lime},
	{ "LimeGreen",			etk::color::limeGreen},
	{ "Linen",				etk::color::linen},
	{ "Magenta",			etk::color::magenta},
	{ "Maroon",				etk::color::maroon},
	{ "MediumAquaMarine",	etk::color::mediumAquaMarine},
	{ "MediumBlue",			etk::color::mediumBlue},
	{ "MediumOrchid",		etk::color::mediumOrchid},
	{ "MediumPurple",		etk::color::mediumPurple},
	{ "MediumSeaGreen",		etk::color::mediumSeaGreen},
	{ "MediumSlateBlue",	etk::color::mediumSlateBlue},
	{ "MediumSpringGreen",	etk::color::mediumSpringGreen},
	{ "MediumTurquoise",	etk::color::mediumTurquoise},
	{ "MediumVioletRed",	etk::color::mediumVioletRed},
	{ "MidnightBlue",		etk::color::midnightBlue},
	{ "MintCream",			etk::color::mintCream},
	{ "MistyRose",			etk::color::mistyRose},
	{ "Moccasin",			etk::color::moccasin},
	{ "NavajoWhite",		etk::color::navajoWhite},
	{ "Navy",				etk::color::navy},
	{ "OldLace",			etk::color::oldLace},
	{ "Olive",				etk::color::olive},
	{ "OliveDrab",			etk::color::oliveDrab},
	{ "Orange",				etk::color::orange},
	{ "OrangeRed",			etk::color::orangeRed},
	{ "Orchid",				etk::color::orchid},
	{ "PaleGoldenRod",		etk::color::paleGoldenRod},
	{ "PaleGreen",			etk::color::paleGreen},
	{ "PaleTurquoise",		etk::color::paleTurquoise},
	{ "PaleVioletRed",		etk::color::paleVioletRed},
	{ "PapayaWhip",			etk::color::papayaWhip},
	{ "PeachPuff",			etk::color::peachPuff},
	{ "Peru",				etk::color::peru},
	{ "Pink",				etk::color::pink},
	{ "Plum",				etk::color::plum},
	{ "PowderBlue",			etk::color::powderBlue},
	{ "Purple",				etk::color::purple},
	{ "Red",				etk::color::red},
	{ "RosyBrown",			etk::color::rosyBrown},
	{ "RoyalBlue",			etk::color::royalBlue},
	{ "SaddleBrown",		etk::color::saddleBrown},
	{ "Salmon",				etk::color::salmon},
	{ "SandyBrown",			etk::color::sandyBrown},
	{ "SeaGreen",			etk::color::seaGreen},
	{ "SeaShell",			etk::color::seaShell},
	{ "Sienna",				etk::color::sienna},
	{ "Silver",				etk::color::silver},
	{ "SkyBlue",			etk::color::skyBlue},
	{ "SlateBlue",			etk::color::slateBlue},
	{ "SlateGray",			etk::color::slateGray},
	{ "SlateGrey",			etk::color::slateGrey},
	{ "Snow",				etk::color::snow},
	{ "SpringGreen",		etk::color::springGreen},
	{ "SteelBlue",			etk::color::steelBlue},
	{ "Tan",				etk::color::tan},
	{ "Teal",				etk::color::teal},
	{ "Thistle",			etk::color::thistle},
	{ "Tomato",				etk::color::tomato},
	{ "Turquoise",			etk::color::turquoise},
	{ "Violet",				etk::color::violet},
	{ "Wheat",				etk::color::wheat},
	{ "White",				etk::color::white},
	{ "WhiteSmoke",			etk::color::whiteSmoke},
	{ "Yellow",				etk::color::yellow},
	{ "YellowGreen",		etk::color::yellowGreen}
};

static const colorList_ts* GetColorList(void)
{
	return listOfColor;
}

static esize_t GetColorSize(void)
{
	static const esize_t tmpp = sizeof(listOfColor) / sizeof(colorList_ts);
	return tmpp;
}
