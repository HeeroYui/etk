/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/types.h>

#ifndef __ETK_TOOL_H__
#define __ETK_TOOL_H__

namespace etk {
	namespace tool {
		/**
		 * @brief Get a random value in a specific range.
		 * @param[in] _a Lower value of the random.
		 * @param[in] _b Bigger value of the random.
		 * @return Random Value between [_a and _b]
		 */
		double frand(double _a, double _b);
		//! @previous
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
	};
};

#endif
