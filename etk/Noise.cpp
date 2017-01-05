/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */


#include <etk/types.hpp>
#include <etk/debug.hpp>
#include <etk/tool.hpp>
#include <etk/Noise.hpp>
// for the rand ...
#include <time.h>
#include <cmath>

#include <cstdlib>

etk::BaseNoise::BaseNoise(const ivec2& _size, float _min, float _max) :
  m_data(_size.x()*_size.y()),
  m_size(_size) {
	m_data.resize(_size.x()*_size.y(), 0);
	for(int32_t iii=0; iii<m_size.x()*m_size.y(); iii++) {
		m_data[iii] = etk::tool::frand(_min, _max);
	}
}

float etk::BaseNoise::get(int32_t _x, int32_t _y) const {
	// We increment of the size to prevent the <0 result due to the "%" methode ...
	_x += m_size.x();
	_y += m_size.y();
	_x %= m_size.x();
	_y %= m_size.y();
	return m_data[_x + _y*m_size.x()];
}

float etk::Noise::smoothNoise(float _x, float _y, const etk::BaseNoise& _noise) {
	//get fractional part of x and y
	float fractX = _x - (int32_t)_x;
	float fractY = _y - (int32_t)_y;
	
	//wrap around
	int32_t x1 = (int32_t)_x;
	int32_t y1 = (int32_t)_y;
	
	//neighbor values
	int32_t x2 = x1 - 1;
	int32_t y2 = y1 - 1;
	
	//smooth the noise with bilinear interpolation
	float value = 0.0f;
	value += fractX       * fractY       * _noise.get(x1,y1);
	value += fractX       * (1 - fractY) * _noise.get(x1,y2);
	value += (1 - fractX) * fractY       * _noise.get(x2,y1);
	value += (1 - fractX) * (1 - fractY) * _noise.get(x2,y2);
	
	return value;
}


float etk::Noise::turbulence(float _x, float _y, float _size, const etk::BaseNoise& _noise) {
	float value = 0.0f;
	float initialSize = _size;
	while(1<=_size) {
		value += smoothNoise(_x / _size, _y / _size, _noise) * _size;
		_size *= 0.5f;
	}
	return(0.5f * value / initialSize);
	// NOTE : with 128 here, we have wood ...
}

float etk::Noise::turbulenceNoSmooth(float _x, float _y, float _size, const etk::BaseNoise& _noise) {
	float value = 0.0f;
	float initialSize = _size;
	while(1<=_size) {
		value += _noise.get(_x / _size, _y / _size) * _size;
		_size *= 0.5f;
	}
	return(0.5f * value / initialSize);
	// NOTE : with 128 here, we have wood ...
}


etk::Noise::Noise(enum etk::noiseType _type, ivec2 _size, int32_t _depth) :
  m_data(_size.x()*_size.y()),
  m_size(_size),
  m_type(_type) {
	m_data.resize(_size.x()*_size.y(), 0);
	switch(m_type) {
		default:
		case etk::noiseType_base:
			{
				etk::BaseNoise myNoise(ivec2(m_size.x()/_depth,m_size.y()/_depth),0.0f,1.0f);
				for(int32_t iii=0; iii<m_size.y(); iii++) {
					for(int32_t jjj=0; jjj<m_size.x(); jjj++) {
						m_data[iii+jjj*m_size.x()] = myNoise.get(iii,jjj);
					}
				}
			}
			break;
		case etk::noiseType_smooth:
			{
				etk::BaseNoise myNoise(ivec2(m_size.x()/_depth,m_size.y()/_depth),0.0f,1.0f);
				for(int32_t iii=0; iii<m_size.y(); iii++) {
					for(int32_t jjj=0; jjj<m_size.x(); jjj++) {
						m_data[iii+jjj*m_size.x()] = smoothNoise((float)iii/(float)_depth,(float)jjj/(float)_depth, myNoise);
					}
				}
			}
			break;
		case etk::noiseType_turbulence:
			{
				etk::BaseNoise myNoise(ivec2(m_size.x()/_depth,m_size.y()/_depth),0.0f,1.0f);
				for(int32_t iii=0; iii<m_size.y(); iii++) {
					for(int32_t jjj=0; jjj<m_size.x(); jjj++) {
						m_data[iii+jjj*m_size.x()] = turbulence(iii,jjj,_depth,myNoise);
					}
				}
			}
			break;
		case etk::noiseType_turbulenceNoSmooth:
			{
				etk::BaseNoise myNoise(ivec2(m_size.x()/_depth,m_size.y()/_depth),0.0f,1.0f);
				for(int32_t iii=0; iii<m_size.y(); iii++) {
					for(int32_t jjj=0; jjj<m_size.x(); jjj++) {
						m_data[iii+jjj*m_size.x()] = turbulenceNoSmooth(iii,jjj,_depth,myNoise);
					}
				}
			}
			break;
		case etk::noiseType_cloud:
			
			break;
		case etk::noiseType_marble:
			
			break;
		case etk::noiseType_wood:
			
			break;
	}
	
}

float etk::Noise::get(int32_t _x, int32_t _y) const
{
	// We increment of the size to prevent the <0 result due to the "%" methode ...
	_x += m_size.x();
	_y += m_size.y();
	_x %= m_size.x();
	_y %= m_size.y();
	return m_data[_x + _y*m_size.x()];
}

