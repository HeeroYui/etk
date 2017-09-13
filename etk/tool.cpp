/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/tool.hpp>
#include <etk/os/FSNode.hpp>
extern "C" {
	#include <time.h>
	#include <math.h>
	#include <stdlib.h>
}

double etk::tool::frand(double _a, double _b) {
	return (float)(( (double)rand()/(double)RAND_MAX ) * ((double)_b-(double)_a) + (double)_a);
}

int32_t etk::tool::irand(int32_t _a, int32_t _b) {
	return (int32_t)(( rand()/(double)RAND_MAX ) * ((double)_b-(double)_a) + (double)_a);
}
uint32_t etk::tool::urand(uint32_t _a, uint32_t _b) {
	return (uint32_t)(( rand()/(double)RAND_MAX ) * ((double)_b-(double)_a) + (double)_a);
}

void etk::tool::resetRandom() {
	srand(time(NULL));
}

void etk::tool::randSeek(int32_t _val) {
	srand(_val);
}
