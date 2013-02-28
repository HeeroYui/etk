/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_NOISE_H__
#define __ETK_NOISE_H__

#include <etk/types.h>
#include <etk/UString.h>
#include <etk/math/Vector2D.h>

namespace etk {
	class BaseNoise
	{
		private:
			etk::Vector<float> m_data;
			ivec2    m_size;
		public:
			BaseNoise(ivec2 size, float min, float max);
			~BaseNoise(void);
			float Get(int32_t x, int32_t y) const;
	};
	class Noise
	{
		public:
			typedef enum {
				NOISE_BASE,
				NOISE_SMOOTH,
				NOISE_TURBULENCE,
				NOISE_TURBULENCE_NO_SMOOTH,
				NOISE_CLOUD,
				NOISE_MARBLE,
				NOISE_WOOD
			} noise_te;
		private:
			etk::Vector<float> m_data;
			ivec2    m_size;
			noise_te m_type;
			float smoothNoise(float x, float y, const etk::BaseNoise& noise);
			float turbulence(float x, float y, float size, const etk::BaseNoise& noise);
			float turbulenceNoSmooth(float x, float y, float size, const etk::BaseNoise& noise);
		public:
			Noise(noise_te type, ivec2 size, int32_t depth);
			~Noise(void);
			float Get(int32_t x, int32_t y) const;
	};
};

#endif
