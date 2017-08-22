/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/types.hpp>

#pragma once

namespace etk {
	/**
	 * @brief Some useful tools
	 * @todo Remove all of this use std11 random
	 */
	namespace tool {
		/**
		 * @brief Get a random value in a specific range in float.
		 * @param[in] _a Lower value of the random.
		 * @param[in] _b Bigger value of the random.
		 * @return Random Value between [_a and _b]
		 */
		double frand(double _a, double _b);
		/**
		 * @brief Get a random value in a specific range in integer.
		 * @param[in] _a Lower value of the random.
		 * @param[in] _b Bigger value of the random.
		 * @return Random Value between [_a and _b]
		 */
		int32_t irand(int32_t _a, int32_t _b);
		/**
		 * @brief Reset the random system with a random value (time).
		 */
		void resetRandom();
		/**
		 * @brief Reset the random system with The specify value.
		 * @param[in] _val Seek value for the pseudo random system.
		 */
		void randSeek(int32_t _val);
	}
}

