/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <etk/types.h>

#pragma once

#include <etk/math/Vector2D.h>

namespace etk {
	class BaseNoise
	{
		private:
			std::vector<float> m_data;
			ivec2    m_size;
		public:
			BaseNoise(ivec2 _size, float _min, float _max);
			~BaseNoise();
			float get(int32_t _x, int32_t _y) const;
	};
	class Noise {
		public:
			enum noise {
				NOISE_BASE,
				NOISE_SMOOTH,
				NOISE_TURBULENCE,
				NOISE_TURBULENCE_NO_SMOOTH,
				NOISE_CLOUD,
				NOISE_MARBLE,
				NOISE_WOOD
			};
		private:
			std::vector<float> m_data;
			ivec2 m_size;
			enum noise m_type;
			float smoothNoise(float _x, float _y, const etk::BaseNoise& _noise);
			float turbulence(float _x, float _y, float _size, const etk::BaseNoise& _noise);
			float turbulenceNoSmooth(float _x, float _y, float _size, const etk::BaseNoise& _noise);
		public:
			Noise(enum noise _type, ivec2 _size, int32_t _depth);
			~Noise();
			float get(int32_t _x, int32_t _y) const;
	};
}

