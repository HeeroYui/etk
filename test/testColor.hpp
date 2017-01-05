/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */

#include <gtest/gtest.h>
#undef NAME
#define NAME "Color"

TEST(TestEtkColor, RGBA8) {
	etk::Color<uint8_t, 4> colorRGBA8(0x52,0x0F, 0x65, 0x44);
	EXPECT_EQ(colorRGBA8.r(), 0x52);
	EXPECT_EQ(colorRGBA8.g(), 0x0F);
	EXPECT_EQ(colorRGBA8.b(), 0x65);
	EXPECT_EQ(colorRGBA8.a(), 0x44);
}


void testColor() {
	TEST_INFO("==> test of COLOR (START)");
	etk::Color<uint8_t, 4> colorRGBA8(0x52,0x0F, 0x65, 0x44);
	etk::Color<uint16_t, 4> colorRGBA16(0x52,0x0F, 0x65, 0x44);
	etk::Color<uint32_t, 4> colorRGBA32(0x52,0x0F, 0x65, 0x44);
	etk::Color<float, 4> colorRGBAF(0.1,0.2, 0.8, 1.0);
	etk::Color<uint8_t, 3> colorRGB8(0x52,0x0F, 0x65);
	etk::Color<uint16_t, 3> colorRGB16(0x52,0x0F, 0x65);
	etk::Color<uint32_t, 3> colorRGB32(0x52,0x0F, 0x65);
	etk::Color<float, 3> colorRGBF(0.1,0.2, 0.8);
	etk::Color<uint8_t, 1> colorMono8(0x52);
	etk::Color<uint16_t, 1> colorMono16(0x52);
	etk::Color<uint32_t, 1> colorMono32(0x52);
	etk::Color<float, 1> colorMonoF(5200.22);
	etk::Color<double, 1> colorMonoD(520000.22);

	etk::Color<uint8_t, 4> colorRGBA8__("#520F6544");
	etk::Color<uint16_t, 4> colorRGBA16__("rgba[U16](0x52, 0x0F, 0x65, 0x44)");
	etk::Color<uint32_t, 4> colorRGBA32__("rgba[U32](0x52,0x0F, 0x65, 0x44)");
	etk::Color<float, 4> colorRGBAF__("rgba[FLOAT](0.1,0.2,0.8,1.0)");
	etk::Color<uint8_t, 3> colorRGB8__("rgba[U8](0x52,0x0F, 0x65)");
	etk::Color<uint16_t, 3> colorRGB16__("rgba[U16](0x52,0x0F, 0x65)");
	etk::Color<uint32_t, 3> colorRGB32__("rgba[U32](0x52,0x0F, 0x65)");
	etk::Color<float, 3> colorRGBF__("rgba[FLOAT](0.1,0.2, 0.8)");
	/*
	etk::Color<uint8_t, 1> colorMono8__("mono[U8](0x52)");
	etk::Color<uint16_t, 1> colorMono16__("mono[U16](0x52)");
	etk::Color<uint32_t, 1> colorMono32__("mono[U32](0x52)");
	etk::Color<float, 1> colorMonoF__("mono[FLOAT](5200.22)");
	etk::Color<double, 1> colorMonoD__("mono[DOUBLE](520000.22)");
	*/
	etk::Color<float, 4> colorRGBAf__(colorRGBA8);
	etk::Color<uint32_t, 2> colorXX332__(colorRGBA8);
	
	TEST_INFO("Create a color : RGBA 8 : " << colorRGBA8);
	TEST_INFO("Create a color : RGBA 8 : " << colorRGBAf__ << " (converted)");
	TEST_INFO("Create a color : XX 32 : " << colorXX332__ << " (converted)");
	TEST_INFO("Create a color : RGBA 16 : " << colorRGBA16);
	TEST_INFO("Create a color : RGBA 32 : " << colorRGBA32);
	TEST_INFO("Create a color : RGBA float : " << colorRGBAF);
	TEST_INFO("Create a color : RGB 8 : " << colorRGB8);
	TEST_INFO("Create a color : RGB 16 : " << colorRGB16);
	TEST_INFO("Create a color : RGB 32 : " << colorRGB32);
	TEST_INFO("Create a color : RGB float : " << colorRGBF);
	TEST_INFO("Create a color : MONO 8 : " << colorMono8);
	TEST_INFO("Create a color : MONO 16 : " << colorMono16);
	TEST_INFO("Create a color : MONO 32 : " << colorMono32);
	TEST_INFO("Create a color : MONO float : " << colorMonoF);
	TEST_INFO("Create a color : MONO double : " << colorMonoD);
	TEST_INFO("==> test of Color (STOP)");
}