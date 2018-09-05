/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/types.hpp>

#pragma once

namespace etk {
	/**
	 * @brief Some useful random elements
	 */
	namespace random {
		/**
		 * @brief Reset the random system with a random value (time).
		 */
		void reset();
		/**
		 * @brief Reset the random system with The specify value.
		 * @param[in] _val Seek value for the pseudo random system.
		 */
		void resetSeed(int32_t _val);
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
		int32_t irand(int32_t _a=0x80000000, int32_t _b=0x7FFFFFFF);
		uint32_t urand(uint32_t _a=0, uint32_t _b=0xFFFFFFFF);
		
		template<typename ETK_RANDOM_TYPE_1, typename ETK_RANDOM_TYPE_2>
		void shuffle(ETK_RANDOM_TYPE_1 _left, ETK_RANDOM_TYPE_2 _right) {
			int32_t distance = etk::distance(_left, _right);
			while (_left != _right) {
				int64_t randValue = etk::random::urand(0, distance);
				auto it = _left + randValue;
				etk::swap(*_left, *it);
				++_left;
			}
		}
		/**
		 * @brief Generate a random string with the specify size.
		 * @param[in] _size number of char.
		 * @return the generated string.
		 */
		etk::String generateString(uint_t _size);
	}
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
		 * @note DEPRECATED
		 */
		inline double frand(double _a, double _b) {
			return etk::random::frand(_a, _b);
		}
		/**
		 * @brief Get a random value in a specific range in integer.
		 * @param[in] _a Lower value of the random.
		 * @param[in] _b Bigger value of the random.
		 * @return Random Value between [_a and _b]
		 * @note DEPRECATED
		 */
		inline int32_t irand(int32_t _a=0x80000000, int32_t _b=0x7FFFFFFF) {
			return etk::random::irand(_a, _b);
		}
		inline uint32_t urand(uint32_t _a=0, uint32_t _b=0xFFFFFFFF) {
			return etk::random::urand(_a, _b);
		}
		/**
		 * @brief Reset the random system with a random value (time).
		 * @note DEPRECATED
		 */
		inline void resetRandom() {
			etk::random::reset();
		}
		/**
		 * @brief Reset the random system with The specify value.
		 * @param[in] _val Seek value for the pseudo random system.
		 * @note DEPRECATED
		 */
		inline void randSeek(int32_t _val) {
			etk::random::resetSeed(_val);
		}
	}
}

