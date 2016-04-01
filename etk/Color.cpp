/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <etk/types.h>
#include <etk/tool.h>
#include <etk/Color.h>
#include <etk/debug.h>
#include <etk/stdTools.h>
#include <string>
#include <sstream>
#include <stdexcept>

#undef __class__
#define __class__ "Color"

typedef struct {
	const char * colorName;
	etk::Color<> color;
} colorList_ts;

static int32_t getColorSize();
static const colorList_ts* getColorList();

etk::Color<uint8_t, 4> etk::parseStringStartWithSharp(const std::string& _input) {
	TK_VERBOSE("parseStringStartWithSharp('" << _input << "'");
	size_t len = _input.size();
	etk::Color<uint8_t, 4> outputValue(0,0,0,0);
	if(len == 3) {
		uint32_t red=0, green=0, blue=0;
		if (sscanf(_input.c_str(), "%1x%1x%1x", &red, &green, &blue) == 3) {
			outputValue.setR(red | red << 4);
			outputValue.setG(green | green << 4);
			outputValue.setB(blue | blue << 4);
			outputValue.setA(0xFF);
		} else {
			TK_ERROR(" pb in parsing the color : '" << _input << "'");
		}
	} else if (len==4) {
		uint32_t red=0, green=0, blue=0, alpha=0;
		if (sscanf(_input.c_str(), "%1x%1x%1x%1x", &red, &green, &blue, &alpha) == 4) {
			outputValue.setR(red | red << 4);
			outputValue.setG(green | green << 4);
			outputValue.setB(blue | blue << 4);
			outputValue.setA(alpha | alpha << 4);
		} else {
			TK_ERROR(" pb in parsing the color : '" << _input << "'");
		}
	} else if (len == 6) {
		uint32_t red=0, green=0, blue=0;
		if (sscanf(_input.c_str(), "%2x%2x%2x", &red, &green, &blue) == 3) {
			outputValue.setR(red);
			outputValue.setG(green);
			outputValue.setB(blue);
			outputValue.setA(0xFF);
		} else {
			TK_ERROR(" pb in parsing the color : '" << _input << "'");
		}
	} else if (len == 8) {
		uint32_t red=0, green=0, blue=0, alpha=0;
		if (sscanf(_input.c_str(), "%2x%2x%2x%2x", &red, &green, &blue, &alpha) == 4) {
			outputValue.setR(red);
			outputValue.setG(green);
			outputValue.setB(blue);
			outputValue.setA(alpha);
		} else {
			TK_ERROR(" pb in parsing the color : '" << _input << "'");
		}
	} else {
		TK_ERROR(" pb in parsing the color : '" << _input << "' ==> unknown methode ...");
	}
	TK_VERBOSE("  result: '" << outputValue << "'");
	return outputValue;
}

etk::Color<uint8_t, 4> etk::parseStringStartWithRGBGen(const std::string& _input) {
	TK_VERBOSE("parseStringStartWithRGB('" << _input << "'");
	etk::Color<uint8_t, 4> outputValue(0,0,0,0);
	int32_t red=0, green=0, blue=0, alpha=0;
	float   fred=0, fgreen=0, fblue=0, falpha=0;
	if (sscanf(_input.c_str(), "%u,%u,%u,%u", &red, &green, &blue, &alpha) == 4) {
		outputValue.setR(std::min(0xFF, red));
		outputValue.setG(std::min(0xFF, green));
		outputValue.setB(std::min(0xFF, blue));
		outputValue.setA(std::min(0xFF, alpha));
	} else if (sscanf(_input.c_str(), "%u,%u,%u", &red, &green, &blue) == 3) {
		outputValue.setR(std::min(0xFF, red));
		outputValue.setG(std::min(0xFF, green));
		outputValue.setB(std::min(0xFF, blue));
	} else if (sscanf(_input.c_str(), "%X,%X,%X,%X", &red, &green, &blue, &alpha) == 4) {
		outputValue.setR(std::min(0xFF, red));
		outputValue.setG(std::min(0xFF, green));
		outputValue.setB(std::min(0xFF, blue));
		outputValue.setA(std::min(0xFF, alpha));
	} else if (sscanf(_input.c_str(), "%X,%X,%X", &red, &green, &blue) == 3) {
		outputValue.setR(std::min(0xFF, red));
		outputValue.setG(std::min(0xFF, green));
		outputValue.setB(std::min(0xFF, blue));
	} else if (sscanf(_input.c_str(), "%f,%f,%f,%f", &fred, &fgreen, &fblue, &falpha) == 4) {
		fred   = std::avg(0.0f, fred, 1.0f);
		fgreen = std::avg(0.0f, fgreen, 1.0f);
		fblue  = std::avg(0.0f, fblue, 1.0f);
		falpha = std::avg(0.0f, falpha, 1.0f);
		outputValue.setR((uint8_t)(fred * 255.f));
		outputValue.setG((uint8_t)(fgreen * 255.f));
		outputValue.setB((uint8_t)(fblue * 255.f));
		outputValue.setR((uint8_t)(falpha * 255.f));
	} else if (sscanf(_input.c_str(), "%f,%f,%f", &fred, &fgreen, &fblue) == 3) {
		fred  = std::avg(0.0f, fred, 1.0f);
		fgreen= std::avg(0.0f, fgreen, 1.0f);
		fblue = std::avg(0.0f, fblue, 1.0f);
		outputValue.setR((uint8_t)(fred * 255.f));
		outputValue.setG((uint8_t)(fgreen * 255.f));
		outputValue.setB((uint8_t)(fblue * 255.f));
	} else {
		TK_ERROR(" pb in parsing the color : '" << _input << "' ==> unknown methode ...");
	}
	return outputValue;
}

etk::Color<double, 4> etk::parseStringStartWithRGB(const std::string& _input) {
	TK_VERBOSE("parseStringStartWithRGB('" << _input << "')");
	etk::Color<double, 4> outputValue(0,0,0,0);
	double fred=0, fgreen=0, fblue=0, falpha=0;
	int32_t red=0, green=0, blue=0, alpha=0;
	if (sscanf(_input.c_str(), "%lf,%lf,%lf,%lf", &fred, &fgreen, &fblue, &falpha) == 4) {
		outputValue.setR(fred);
		outputValue.setG(fgreen);
		outputValue.setB(fblue);
		outputValue.setA(falpha);
	} else if (sscanf(_input.c_str(), "%lf,%lf,%lf", &fred, &fgreen, &fblue) == 3) {
		outputValue.setR(fred);
		outputValue.setG(fgreen);
		outputValue.setB(fblue);
	} else if (sscanf(_input.c_str(), "%u,%u,%u,%u", &red, &green, &blue, &alpha) == 4) {
		outputValue.setR(std::min(0xFF, red)/255.0);
		outputValue.setG(std::min(0xFF, green)/255.0);
		outputValue.setB(std::min(0xFF, blue)/255.0);
		outputValue.setA(std::min(0xFF, alpha)/255.0);
	} else if (sscanf(_input.c_str(), "%u,%u,%u", &red, &green, &blue) == 3) {
		outputValue.setR(std::min(0xFF, red)/255.0);
		outputValue.setG(std::min(0xFF, green)/255.0);
		outputValue.setB(std::min(0xFF, blue)/255.0);
	} else if (sscanf(_input.c_str(), "%X,%X,%X,%X", &red, &green, &blue, &alpha) == 4) {
		outputValue.setR(std::min(0xFF, red)/255.0);
		outputValue.setG(std::min(0xFF, green)/255.0);
		outputValue.setB(std::min(0xFF, blue)/255.0);
		outputValue.setA(std::min(0xFF, alpha)/255.0);
	} else if (sscanf(_input.c_str(), "%X,%X,%X", &red, &green, &blue) == 3) {
		outputValue.setR(std::min(0xFF, red)/255.0);
		outputValue.setG(std::min(0xFF, green)/255.0);
		outputValue.setB(std::min(0xFF, blue)/255.0);
	} else {
		TK_ERROR(" pb in parsing the color : '" << _input << "' ==> unknown methode ...");
	}
	return outputValue;
}
etk::Color<uint32_t, 4> etk::parseStringStartWithRGBUnsigned32(const std::string& _input) {
	etk::Color<uint32_t, 4> outputValue(0,0,0,0);
	int32_t red=0, green=0, blue=0, alpha=0;
	double fred=0, fgreen=0, fblue=0, falpha=0;
	if (sscanf(_input.c_str(), "%u,%u,%u,%u", &red, &green, &blue, &alpha) == 4) {
		outputValue.setR(red);
		outputValue.setG(green);
		outputValue.setB(blue);
		outputValue.setA(alpha);
	} else if (sscanf(_input.c_str(), "%u,%u,%u", &red, &green, &blue) == 3) {
		outputValue.setR(red);
		outputValue.setG(green);
		outputValue.setB(blue);
	} else if (sscanf(_input.c_str(), "%X,%X,%X,%X", &red, &green, &blue, &alpha) == 4) {
		outputValue.setR(red);
		outputValue.setG(green);
		outputValue.setB(blue);
		outputValue.setA(alpha);
	} else if (sscanf(_input.c_str(), "%X,%X,%X", &red, &green, &blue) == 3) {
		outputValue.setR(red);
		outputValue.setG(green);
		outputValue.setB(blue);
	} else if (sscanf(_input.c_str(), "%lf,%lf,%lf,%lf", &fred, &fgreen, &fblue, &falpha) == 4) {
		outputValue.setR((uint32_t)(std::min(1.0, fred)*0xFFFFFFFF));
		outputValue.setG((uint32_t)(std::min(1.0, fgreen)*0xFFFFFFFF));
		outputValue.setB((uint32_t)(std::min(1.0, fblue)*0xFFFFFFFF));
		outputValue.setA((uint32_t)(std::min(1.0, falpha)*0xFFFFFFFF));
	} else if (sscanf(_input.c_str(), "%lf,%lf,%lf", &fred, &fgreen, &fblue) == 3) {
		outputValue.setR((uint32_t)(std::min(1.0, fred)*0xFFFFFFFF));
		outputValue.setG((uint32_t)(std::min(1.0, fgreen)*0xFFFFFFFF));
		outputValue.setB((uint32_t)(std::min(1.0, fblue)*0xFFFFFFFF));
	} else {
		TK_ERROR(" pb in parsing the color : '" << _input << "' ==> unknown methode ...");
	}
	return outputValue;
}

etk::Color<uint16_t, 4> etk::parseStringStartWithRGBUnsigned16(const std::string& _input) {
	etk::Color<uint16_t, 4> outputValue(0,0,0,0);
	int32_t red=0, green=0, blue=0, alpha=0;
	double fred=0, fgreen=0, fblue=0, falpha=0;
	if (sscanf(_input.c_str(), "%u,%u,%u,%u", &red, &green, &blue, &alpha) == 4) {
		outputValue.setR(std::min(0xFFFF, red));
		outputValue.setG(std::min(0xFFFF, green));
		outputValue.setB(std::min(0xFFFF, blue));
		outputValue.setA(std::min(0xFFFF, alpha));
	} else if (sscanf(_input.c_str(), "%u,%u,%u", &red, &green, &blue) == 3) {
		outputValue.setR(std::min(0xFFFF, red));
		outputValue.setG(std::min(0xFFFF, green));
		outputValue.setB(std::min(0xFFFF, blue));
	} else if (sscanf(_input.c_str(), "%X,%X,%X,%X", &red, &green, &blue, &alpha) == 4) {
		outputValue.setR(std::min(0xFFFF, red));
		outputValue.setG(std::min(0xFFFF, green));
		outputValue.setB(std::min(0xFFFF, blue));
		outputValue.setA(std::min(0xFFFF, alpha));
	} else if (sscanf(_input.c_str(), "%X,%X,%X", &red, &green, &blue) == 3) {
		outputValue.setR(std::min(0xFFFF, red));
		outputValue.setG(std::min(0xFFFF, green));
		outputValue.setB(std::min(0xFFFF, blue));
	} else if (sscanf(_input.c_str(), "%lf,%lf,%lf,%lf", &fred, &fgreen, &fblue, &falpha) == 4) {
		outputValue.setR((uint16_t)(std::min(1.0, fred)*0xFFFF));
		outputValue.setG((uint16_t)(std::min(1.0, fgreen)*0xFFFF));
		outputValue.setB((uint16_t)(std::min(1.0, fblue)*0xFFFF));
		outputValue.setA((uint16_t)(std::min(1.0, falpha)*0xFFFF));
	} else if (sscanf(_input.c_str(), "%lf,%lf,%lf", &fred, &fgreen, &fblue) == 3) {
		outputValue.setR((uint16_t)(std::min(1.0, fred)*0xFFFF));
		outputValue.setG((uint16_t)(std::min(1.0, fgreen)*0xFFFF));
		outputValue.setB((uint16_t)(std::min(1.0, fblue)*0xFFFF));
	} else {
		TK_ERROR(" pb in parsing the color : '" << _input << "' ==> unknown methode ...");
	}
	return outputValue;
}

etk::Color<uint8_t, 4> etk::parseStringStartWithRGBUnsigned8(const std::string& _input) {
	etk::Color<uint8_t, 4> outputValue(0,0,0,0);
	int32_t red=0, green=0, blue=0, alpha=0;
	double fred=0, fgreen=0, fblue=0, falpha=0;
	if (sscanf(_input.c_str(), "%u,%u,%u,%u", &red, &green, &blue, &alpha) == 4) {
		outputValue.setR(std::min(0xFF, red));
		outputValue.setG(std::min(0xFF, green));
		outputValue.setB(std::min(0xFF, blue));
		outputValue.setA(std::min(0xFF, alpha));
	} else if (sscanf(_input.c_str(), "%u,%u,%u", &red, &green, &blue) == 3) {
		outputValue.setR(std::min(0xFF, red));
		outputValue.setG(std::min(0xFF, green));
		outputValue.setB(std::min(0xFF, blue));
	} else if (sscanf(_input.c_str(), "%X,%X,%X,%X", &red, &green, &blue, &alpha) == 4) {
		outputValue.setR(std::min(0xFF, red));
		outputValue.setG(std::min(0xFF, green));
		outputValue.setB(std::min(0xFF, blue));
		outputValue.setA(std::min(0xFF, alpha));
	} else if (sscanf(_input.c_str(), "%X,%X,%X", &red, &green, &blue) == 3) {
		outputValue.setR(std::min(0xFF, red));
		outputValue.setG(std::min(0xFF, green));
		outputValue.setB(std::min(0xFF, blue));
	} else if (sscanf(_input.c_str(), "%lf,%lf,%lf,%lf", &fred, &fgreen, &fblue, &falpha) == 4) {
		outputValue.setR((uint8_t)(std::min(1.0, fred)*0xFF));
		outputValue.setG((uint8_t)(std::min(1.0, fgreen)*0xFF));
		outputValue.setB((uint8_t)(std::min(1.0, fblue)*0xFF));
		outputValue.setA((uint8_t)(std::min(1.0, falpha)*0xFF));
	} else if (sscanf(_input.c_str(), "%lf,%lf,%lf", &fred, &fgreen, &fblue) == 3) {
		outputValue.setR((uint8_t)(std::min(1.0, fred)*0xFF));
		outputValue.setG((uint8_t)(std::min(1.0, fgreen)*0xFF));
		outputValue.setB((uint8_t)(std::min(1.0, fblue)*0xFF));
	} else {
		TK_ERROR(" pb in parsing the color : '" << _input << "' ==> unknown methode ...");
	}
	return outputValue;
}

etk::Color<uint8_t, 4> etk::parseStringColorNamed(const std::string& _input) {
	// direct named color ...
	for (int32_t iii=0; iii<getColorSize(); iii++) {
		if (etk::compare_no_case(getColorList()[iii].colorName, _input) == true) {
			return getColorList()[iii].color;
		}
	}
	TK_ERROR(" pb in parsing the color : '" << _input << "' not find ...");
	return etk::Color<uint8_t, 4>(0,0,0,0);
}

template<> uint32_t etk::Color<uint8_t, 4>::get() const {
	return   (((uint32_t)m_element[0])<<24)
	       + (((uint32_t)m_element[1])<<16)
	       + (((uint32_t)m_element[2])<<8)
	       + (uint32_t)m_element[3];
}

const etk::Color<> etk::color::none(0x00, 0x00, 0x00, 0x00);
const etk::Color<> etk::color::aliceBlue(0xF0, 0xF8, 0xFF, 0xFF);
const etk::Color<> etk::color::antiqueWhite(0xFA, 0xEB, 0xD7, 0xFF);
const etk::Color<> etk::color::aqua(0x00, 0xFF, 0xFF, 0xFF);
const etk::Color<> etk::color::aquamarine(0x7F, 0xFF, 0xD4, 0xFF);
const etk::Color<> etk::color::azure(0xF0, 0xFF, 0xFF, 0xFF);
const etk::Color<> etk::color::beige(0xF5, 0xF5, 0xDC, 0xFF);
const etk::Color<> etk::color::bisque(0xFF, 0xE4, 0xC4, 0xFF);
const etk::Color<> etk::color::black(0x00, 0x00, 0x00, 0xFF);
const etk::Color<> etk::color::blanchedAlmond(0xFF, 0xEB, 0xCD, 0xFF);
const etk::Color<> etk::color::blue(0x00, 0x00, 0xFF, 0xFF);
const etk::Color<> etk::color::blueViolet(0x8A, 0x2B, 0xE2, 0xFF);
const etk::Color<> etk::color::brown(0xA5, 0x2A, 0x2A, 0xFF);
const etk::Color<> etk::color::burlyWood(0xDE, 0xB8, 0x87, 0xFF);
const etk::Color<> etk::color::cadetBlue(0x5F, 0x9E, 0xA0, 0xFF);
const etk::Color<> etk::color::chartreuse(0x7F, 0xFF, 0x00, 0xFF);
const etk::Color<> etk::color::chocolate(0xD2, 0x69, 0x1E, 0xFF);
const etk::Color<> etk::color::coral(0xFF, 0x7F, 0x50, 0xFF);
const etk::Color<> etk::color::cornflowerBlue(0x64, 0x95, 0xED, 0xFF);
const etk::Color<> etk::color::cornsilk(0xFF, 0xF8, 0xDC, 0xFF);
const etk::Color<> etk::color::crimson(0xDC, 0x14, 0x3C, 0xFF);
const etk::Color<> etk::color::cyan(0x00, 0xFF, 0xFF, 0xFF);
const etk::Color<> etk::color::darkBlue(0x00, 0x00, 0x8B, 0xFF);
const etk::Color<> etk::color::darkCyan(0x00, 0x8B, 0x8B, 0xFF);
const etk::Color<> etk::color::darkGoldenRod(0xB8, 0x86, 0x0B, 0xFF);
const etk::Color<> etk::color::darkGray(0xA9, 0xA9, 0xA9, 0xFF);
const etk::Color<> etk::color::darkGrey(0xA9, 0xA9, 0xA9, 0xFF);
const etk::Color<> etk::color::darkGreen(0x00, 0x64, 0x00, 0xFF);
const etk::Color<> etk::color::darkKhaki(0xBD, 0xB7, 0x6B, 0xFF);
const etk::Color<> etk::color::darkMagenta(0x8B, 0x00, 0x8B, 0xFF);
const etk::Color<> etk::color::darkOliveGreen(0x55, 0x6B, 0x2F, 0xFF);
const etk::Color<> etk::color::darkorange(0xFF, 0x8C, 0x00, 0xFF);
const etk::Color<> etk::color::darkOrchid(0x99, 0x32, 0xCC, 0xFF);
const etk::Color<> etk::color::darkRed(0x8B, 0x00, 0x00, 0xFF);
const etk::Color<> etk::color::darkSalmon(0xE9, 0x96, 0x7A, 0xFF);
const etk::Color<> etk::color::darkSeaGreen(0x8F, 0xBC, 0x8F, 0xFF);
const etk::Color<> etk::color::darkSlateBlue(0x48, 0x3D, 0x8B, 0xFF);
const etk::Color<> etk::color::darkSlateGray(0x2F, 0x4F, 0x4F, 0xFF);
const etk::Color<> etk::color::darkSlateGrey(0x2F, 0x4F, 0x4F, 0xFF);
const etk::Color<> etk::color::darkTurquoise(0x00, 0xCE, 0xD1, 0xFF);
const etk::Color<> etk::color::darkViolet(0x94, 0x00, 0xD3, 0xFF);
const etk::Color<> etk::color::deepPink(0xFF, 0x14, 0x93, 0xFF);
const etk::Color<> etk::color::deepSkyBlue(0x00, 0xBF, 0xFF, 0xFF);
const etk::Color<> etk::color::dimGray(0x69, 0x69, 0x69, 0xFF);
const etk::Color<> etk::color::dimGrey(0x69, 0x69, 0x69, 0xFF);
const etk::Color<> etk::color::dodgerBlue(0x1E, 0x90, 0xFF, 0xFF);
const etk::Color<> etk::color::fireBrick(0xB2, 0x22, 0x22, 0xFF);
const etk::Color<> etk::color::floralWhite(0xFF, 0xFA, 0xF0, 0xFF);
const etk::Color<> etk::color::forestGreen(0x22, 0x8B, 0x22, 0xFF);
const etk::Color<> etk::color::fuchsia(0xFF, 0x00, 0xFF, 0xFF);
const etk::Color<> etk::color::gainsboro(0xDC, 0xDC, 0xDC, 0xFF);
const etk::Color<> etk::color::ghostWhite(0xF8, 0xF8, 0xFF, 0xFF);
const etk::Color<> etk::color::gold(0xFF, 0xD7, 0x00, 0xFF);
const etk::Color<> etk::color::goldenRod(0xDA, 0xA5, 0x20, 0xFF);
const etk::Color<> etk::color::gray(0x80, 0x80, 0x80, 0xFF);
const etk::Color<> etk::color::grey(0x80, 0x80, 0x80, 0xFF);
const etk::Color<> etk::color::green(0x00, 0x80, 0x00, 0xFF);
const etk::Color<> etk::color::greenYellow(0xAD, 0xFF, 0x2F, 0xFF);
const etk::Color<> etk::color::honeyDew(0xF0, 0xFF, 0xF0, 0xFF);
const etk::Color<> etk::color::hotPink(0xFF, 0x69, 0xB4, 0xFF);
const etk::Color<> etk::color::indianRed (0xCD, 0x5C, 0x5C, 0xFF);
const etk::Color<> etk::color::indigo (0x4B, 0x00, 0x82, 0xFF);
const etk::Color<> etk::color::ivory(0xFF, 0xFF, 0xF0, 0xFF);
const etk::Color<> etk::color::khaki(0xF0, 0xE6, 0x8C, 0xFF);
const etk::Color<> etk::color::lavender(0xE6, 0xE6, 0xFA, 0xFF);
const etk::Color<> etk::color::lavenderBlush(0xFF, 0xF0, 0xF5, 0xFF);
const etk::Color<> etk::color::lawnGreen(0x7C, 0xFC, 0x00, 0xFF);
const etk::Color<> etk::color::lemonChiffon(0xFF, 0xFA, 0xCD, 0xFF);
const etk::Color<> etk::color::lightBlue(0xAD, 0xD8, 0xE6, 0xFF);
const etk::Color<> etk::color::lightCoral(0xF0, 0x80, 0x80, 0xFF);
const etk::Color<> etk::color::lightCyan(0xE0, 0xFF, 0xFF, 0xFF);
const etk::Color<> etk::color::lightGoldenRodYellow(0xFA, 0xFA, 0xD2, 0xFF);
const etk::Color<> etk::color::lightGray(0xD3, 0xD3, 0xD3, 0xFF);
const etk::Color<> etk::color::lightGrey(0xD3, 0xD3, 0xD3, 0xFF);
const etk::Color<> etk::color::lightGreen(0x90, 0xEE, 0x90, 0xFF);
const etk::Color<> etk::color::lightPink(0xFF, 0xB6, 0xC1, 0xFF);
const etk::Color<> etk::color::lightSalmon(0xFF, 0xA0, 0x7A, 0xFF);
const etk::Color<> etk::color::lightSeaGreen(0x20, 0xB2, 0xAA, 0xFF);
const etk::Color<> etk::color::lightSkyBlue(0x87, 0xCE, 0xFA, 0xFF);
const etk::Color<> etk::color::lightSlateGray(0x77, 0x88, 0x99, 0xFF);
const etk::Color<> etk::color::lightSlateGrey(0x77, 0x88, 0x99, 0xFF);
const etk::Color<> etk::color::lightSteelBlue(0xB0, 0xC4, 0xDE, 0xFF);
const etk::Color<> etk::color::lightYellow(0xFF, 0xFF, 0xE0, 0xFF);
const etk::Color<> etk::color::lime(0x00, 0xFF, 0x00, 0xFF);
const etk::Color<> etk::color::limeGreen(0x32, 0xCD, 0x32, 0xFF);
const etk::Color<> etk::color::linen(0xFA, 0xF0, 0xE6, 0xFF);
const etk::Color<> etk::color::magenta(0xFF, 0x00, 0xFF, 0xFF);
const etk::Color<> etk::color::maroon(0x80, 0x00, 0x00, 0xFF);
const etk::Color<> etk::color::mediumAquaMarine(0x66, 0xCD, 0xAA, 0xFF);
const etk::Color<> etk::color::mediumBlue(0x00, 0x00, 0xCD, 0xFF);
const etk::Color<> etk::color::mediumOrchid(0xBA, 0x55, 0xD3, 0xFF);
const etk::Color<> etk::color::mediumPurple(0x93, 0x70, 0xD8, 0xFF);
const etk::Color<> etk::color::mediumSeaGreen(0x3C, 0xB3, 0x71, 0xFF);
const etk::Color<> etk::color::mediumSlateBlue(0x7B, 0x68, 0xEE, 0xFF);
const etk::Color<> etk::color::mediumSpringGreen(0x00, 0xFA, 0x9A, 0xFF);
const etk::Color<> etk::color::mediumTurquoise(0x48, 0xD1, 0xCC, 0xFF);
const etk::Color<> etk::color::mediumVioletRed(0xC7, 0x15, 0x85, 0xFF);
const etk::Color<> etk::color::midnightBlue(0x19, 0x19, 0x70, 0xFF);
const etk::Color<> etk::color::mintCream(0xF5, 0xFF, 0xFA, 0xFF);
const etk::Color<> etk::color::mistyRose(0xFF, 0xE4, 0xE1, 0xFF);
const etk::Color<> etk::color::moccasin(0xFF, 0xE4, 0xB5, 0xFF);
const etk::Color<> etk::color::navajoWhite(0xFF, 0xDE, 0xAD, 0xFF);
const etk::Color<> etk::color::navy(0x00, 0x00, 0x80, 0xFF);
const etk::Color<> etk::color::oldLace(0xFD, 0xF5, 0xE6, 0xFF);
const etk::Color<> etk::color::olive(0x80, 0x80, 0x00, 0xFF);
const etk::Color<> etk::color::oliveDrab(0x6B, 0x8E, 0x23, 0xFF);
const etk::Color<> etk::color::orange(0xFF, 0xA5, 0x00, 0xFF);
const etk::Color<> etk::color::orangeRed(0xFF, 0x45, 0x00, 0xFF);
const etk::Color<> etk::color::orchid(0xDA, 0x70, 0xD6, 0xFF);
const etk::Color<> etk::color::paleGoldenRod(0xEE, 0xE8, 0xAA, 0xFF);
const etk::Color<> etk::color::paleGreen(0x98, 0xFB, 0x98, 0xFF);
const etk::Color<> etk::color::paleTurquoise(0xAF, 0xEE, 0xEE, 0xFF);
const etk::Color<> etk::color::paleVioletRed(0xD8, 0x70, 0x93, 0xFF);
const etk::Color<> etk::color::papayaWhip(0xFF, 0xEF, 0xD5, 0xFF);
const etk::Color<> etk::color::peachPuff(0xFF, 0xDA, 0xB9, 0xFF);
const etk::Color<> etk::color::peru(0xCD, 0x85, 0x3F, 0xFF);
const etk::Color<> etk::color::pink(0xFF, 0xC0, 0xCB, 0xFF);
const etk::Color<> etk::color::plum(0xDD, 0xA0, 0xDD, 0xFF);
const etk::Color<> etk::color::powderBlue(0xB0, 0xE0, 0xE6, 0xFF);
const etk::Color<> etk::color::purple(0x80, 0x00, 0x80, 0xFF);
const etk::Color<> etk::color::red(0xFF, 0x00, 0x00, 0xFF);
const etk::Color<> etk::color::rosyBrown(0xBC, 0x8F, 0x8F, 0xFF);
const etk::Color<> etk::color::royalBlue(0x41, 0x69, 0xE1, 0xFF);
const etk::Color<> etk::color::saddleBrown(0x8B, 0x45, 0x13, 0xFF);
const etk::Color<> etk::color::salmon(0xFA, 0x80, 0x72, 0xFF);
const etk::Color<> etk::color::sandyBrown(0xF4, 0xA4, 0x60, 0xFF);
const etk::Color<> etk::color::seaGreen(0x2E, 0x8B, 0x57, 0xFF);
const etk::Color<> etk::color::seaShell(0xFF, 0xF5, 0xEE, 0xFF);
const etk::Color<> etk::color::sienna(0xA0, 0x52, 0x2D, 0xFF);
const etk::Color<> etk::color::silver(0xC0, 0xC0, 0xC0, 0xFF);
const etk::Color<> etk::color::skyBlue(0x87, 0xCE, 0xEB, 0xFF);
const etk::Color<> etk::color::slateBlue(0x6A, 0x5A, 0xCD, 0xFF);
const etk::Color<> etk::color::slateGray(0x70, 0x80, 0x90, 0xFF);
const etk::Color<> etk::color::slateGrey(0x70, 0x80, 0x90, 0xFF);
const etk::Color<> etk::color::snow(0xFF, 0xFA, 0xFA, 0xFF);
const etk::Color<> etk::color::springGreen(0x00, 0xFF, 0x7F, 0xFF);
const etk::Color<> etk::color::steelBlue(0x46, 0x82, 0xB4, 0xFF);
const etk::Color<> etk::color::tan(0xD2, 0xB4, 0x8C, 0xFF);
const etk::Color<> etk::color::teal(0x00, 0x80, 0x80, 0xFF);
const etk::Color<> etk::color::thistle(0xD8, 0xBF, 0xD8, 0xFF);
const etk::Color<> etk::color::tomato(0xFF, 0x63, 0x47, 0xFF);
const etk::Color<> etk::color::turquoise(0x40, 0xE0, 0xD0, 0xFF);
const etk::Color<> etk::color::violet(0xEE, 0x82, 0xEE, 0xFF);
const etk::Color<> etk::color::wheat(0xF5, 0xDE, 0xB3, 0xFF);
const etk::Color<> etk::color::white(0xFF, 0xFF, 0xFF, 0xFF);
const etk::Color<> etk::color::whiteSmoke(0xF5, 0xF5, 0xF5, 0xFF);
const etk::Color<> etk::color::yellow(0xFF, 0xFF, 0x00, 0xFF);
const etk::Color<> etk::color::yellowGreen(0x9A, 0xCD, 0x32, 0xFF);

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

static const colorList_ts* getColorList()
{
	return listOfColor;
}

static int32_t getColorSize()
{
	static const int32_t tmpp = sizeof(listOfColor) / sizeof(colorList_ts);
	return tmpp;
}

namespace etk {
	#include "Color_8_bits.cxx"
	#include "Color_16_bits.cxx"
	#include "Color_32_bits.cxx"
	#include "Color_float.cxx"
	#include "Color_double.cxx"
};

