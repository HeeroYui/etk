/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */


#include <etk/types.h>
#include <etk/Debug.h>
#include <etk/tool.h>
#include <etk/Noise.h>
// for the rand ...
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

etk::BaseNoise::BaseNoise(ivec2 size, float min, float max) :
	m_data(size.x()*size.y()),
	m_size(size)
{
	m_data.ReSize(size.x()*size.y(), 0);
	
	for(int32_t iii=0; iii<m_size.x()*m_size.y(); iii++) {
		m_data[iii] = etk::tool::frand(min, max);
	}
}

etk::BaseNoise::~BaseNoise(void)
{
	
}

float etk::BaseNoise::Get(int32_t x, int32_t y) const
{
	// We increment of the size to prevent the <0 result due to the "%" methode ...
	x += m_size.x();
	y += m_size.y();
	x %= m_size.x();
	y %= m_size.y();
	return m_data[x + y*m_size.x()];
}

float etk::Noise::smoothNoise(float x, float y, const etk::BaseNoise& noise)
{
	//get fractional part of x and y
	float fractX = x - (int32_t)x;
	float fractY = y - (int32_t)y;
	
	//wrap around
	int32_t x1 = (int32_t)x;
	int32_t y1 = (int32_t)y;
	
	//neighbor values
	int32_t x2 = x1 - 1;
	int32_t y2 = y1 - 1;
	
	//smooth the noise with bilinear interpolation
	float value = 0.0;
	value += fractX       * fractY       * noise.Get(x1,y1);
	value += fractX       * (1 - fractY) * noise.Get(x1,y2);
	value += (1 - fractX) * fractY       * noise.Get(x2,y1);
	value += (1 - fractX) * (1 - fractY) * noise.Get(x2,y2);
	
	return value;
}


float etk::Noise::turbulence(float x, float y, float size, const etk::BaseNoise& noise)
{
	float value = 0.0f;
	float initialSize = size;
	while(1<=size) {
		value += smoothNoise(x / size, y / size, noise) * size;
		size /= 2.0;
	}
	return(0.5f * value / initialSize);
	// NOTE : with 128 here, we have wood ...
}

float etk::Noise::turbulenceNoSmooth(float x, float y, float size, const etk::BaseNoise& noise)
{
	float value = 0.0f;
	float initialSize = size;
	while(1<=size) {
		value += noise.Get(x / size, y / size) * size;
		size /= 2.0;
	}
	return(0.5f * value / initialSize);
	// NOTE : with 128 here, we have wood ...
}


etk::Noise::Noise(noise_te type, ivec2 size, int32_t depth) :
	m_data(size.x()*size.y()),
	m_size(size),
	m_type(type)
{
	m_data.ReSize(size.x()*size.y(), 0);
	switch(m_type) {
		default:
		case etk::Noise::NOISE_BASE:
			{
				etk::BaseNoise myNoise(ivec2(m_size.x(),m_size.y()),0.0f,1.0f);
				for(int32_t iii=0; iii<m_size.y(); iii++) {
					for(int32_t jjj=0; jjj<m_size.x(); jjj++) {
						m_data[iii+jjj*m_size.x()] = myNoise.Get(iii,jjj);
					}
				}
			}
			break;
		case etk::Noise::NOISE_SMOOTH:
			{
				etk::BaseNoise myNoise(ivec2(m_size.x()/depth,m_size.y()/depth),0.0f,1.0f);
				for(int32_t iii=0; iii<m_size.y(); iii++) {
					for(int32_t jjj=0; jjj<m_size.x(); jjj++) {
						m_data[iii+jjj*m_size.x()] = smoothNoise((float)iii/(float)depth,(float)jjj/(float)depth, myNoise);
					}
				}
			}
			break;
		case etk::Noise::NOISE_TURBULENCE:
			{
				etk::BaseNoise myNoise(ivec2(m_size.x()/depth,m_size.y()/depth),0.0f,1.0f);
				for(int32_t iii=0; iii<m_size.y(); iii++) {
					for(int32_t jjj=0; jjj<m_size.x(); jjj++) {
						m_data[iii+jjj*m_size.x()] = turbulence(iii,jjj,depth,myNoise);
					}
				}
			}
			break;
		case etk::Noise::NOISE_TURBULENCE_NO_SMOOTH:
			{
				etk::BaseNoise myNoise(ivec2(m_size.x()/depth,m_size.y()/depth),0.0f,1.0f);
				for(int32_t iii=0; iii<m_size.y(); iii++) {
					for(int32_t jjj=0; jjj<m_size.x(); jjj++) {
						m_data[iii+jjj*m_size.x()] = turbulenceNoSmooth(iii,jjj,depth,myNoise);
					}
				}
			}
			break;
		case etk::Noise::NOISE_CLOUD:
			
			break;
		case etk::Noise::NOISE_MARBLE:
			
			break;
		case etk::Noise::NOISE_WOOD:
			
			break;
	}
	
}

etk::Noise::~Noise(void)
{
	
}

float etk::Noise::Get(int32_t x, int32_t y) const
{
	// We increment of the size to prevent the <0 result due to the "%" methode ...
	x += m_size.x();
	y += m_size.y();
	x %= m_size.x();
	y %= m_size.y();
	return m_data[x + y*m_size.x()];
}

