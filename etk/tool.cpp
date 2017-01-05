/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/tool.hpp>
#include <etk/os/FSNode.hpp>
// for the rand ...
#include <time.h>
#include <cmath>

#include <cstdlib>

double etk::tool::frand(double _a, double _b) {
	return (float)(( (double)rand()/(double)RAND_MAX ) * ((double)_b-(double)_a) + (double)_a);
}

int32_t etk::tool::irand(int32_t _a, int32_t _b) {
	return (int32_t)(( rand()/(double)RAND_MAX ) * ((double)_b-(double)_a) + (double)_a);
}

void etk::tool::resetRandom() {
	srand(time(NULL));
}

void etk::tool::randSeek(int32_t _val) {
	srand(_val);
}
