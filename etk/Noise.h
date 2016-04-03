/** @file
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
	/**
	 * @brief BaseNoise Noise basic data.
	 * @todo Validate it, this is a !!! PROTOTYPE !!!
	 * @todo Remove this from ETK
	 */
	class BaseNoise {
		private:
			std::vector<float> m_data; //!< basic interface date
			ivec2 m_size; //!< Size of the noise data
		public:
			/**
			 * @brief basic constructor with randon settings
			 * @param[in] _size Size of the basic noise
			 * @param[in] _min Minimum value of the random
			 * @param[in] _max Maximum value of the random
			 */
			BaseNoise(const ivec2& _size, float _min, float _max);
			/**
			 * @brief Get value at a specific position.
			 * @param[in] _x X position
			 * @param[in] _y Y position
			 * @return random noise value
			 */
			float get(int32_t _x, int32_t _y) const;
	};
	/**
	 * @brief List of noise type supported
	 * @todo Remove this from ETK
	 */
	enum noiseType {
		noiseType_base, //!< basic random noise
		noiseType_smooth, //!< Noise smoothed
		noiseType_turbulence, //!< Noise in turbulence mode
		noiseType_turbulence_no_smooth, //!< Noise Turbulence with no smooth apply
		noiseType_cloud, //!< Noise like a cloud
		noiseType_marble, //!< Noise like marble
		noiseType_wood //!< Noise like wood
	};
	/**
	 * @brief Noise basic interface.
	 * @todo Validate it, this is a !!! PROTOTYPE !!!
	 * @todo Remove this from ETK
	 */
	class Noise {
		private:
			std::vector<float> m_data; //!< Internal data generated
			ivec2 m_size; //!< Size of the noise
			enum noiseType m_type; //!< Type of the noise
			/**
			 * @brief Calculate the Smooth noise at a specific position
			 * @param[in] _x X position
			 * @param[in] _y Y position
			 * @param[in] _noise Type of noise
			 * @return Value calculated
			 */
			float smoothNoise(float _x, float _y, const etk::BaseNoise& _noise);
			/**
			 * @brief Calculate the Tubulence noise at a specific position
			 * @param[in] _x X position
			 * @param[in] _y Y position
			 * @param[in] _size Turbulence ratio value
			 * @param[in] _noise Type of noise
			 * @return Value calculated
			 */
			float turbulence(float _x, float _y, float _size, const etk::BaseNoise& _noise);
			/**
			 * @brief Calculate the Tubulence Not Smooth noise at a specific position
			 * @param[in] _x X position
			 * @param[in] _y Y position
			 * @param[in] _size Turbulence ratio value
			 * @param[in] _noise Type of noise
			 * @return Value calculated
			 */
			float turbulenceNoSmooth(float _x, float _y, float _size, const etk::BaseNoise& _noise);
		public:
			/**
			 * @brief Contructor of a noise specific
			 * @param[in] _type Type of noise
			 * @param[in] _size Size of the image output
			 * @param[in] _depth Depth calculation
			 */
			Noise(enum noiseType _type, ivec2 _size, int32_t _depth);
			/**
			 * @brief Get value at a specific position
			 * @param[in] _x X position
			 * @param[in] _y Y position
			 * @return Value calculated at this position
			 */
			float get(int32_t _x, int32_t _y) const;
	};
}

