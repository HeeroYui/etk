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

double etk::random::frand(double _a, double _b) {
	return (float)(( (double)rand()/(double)RAND_MAX ) * ((double)_b-(double)_a) + (double)_a);
}

int32_t etk::random::irand(int32_t _a, int32_t _b) {
	return (int32_t)(( rand()/(double)RAND_MAX ) * ((double)_b-(double)_a) + (double)_a);
}
uint32_t etk::random::urand(uint32_t _a, uint32_t _b) {
	return (uint32_t)(( rand()/(double)RAND_MAX ) * ((double)_b-(double)_a) + (double)_a);
}

void etk::random::reset() {
	srand(time(0));
}

void etk::random::resetSeed(int32_t _val) {
	srand(_val);
}


etk::String etk::random::generateString(uint_t _size) {
	static etk::String value = "AZERTYUIOPQSDFGHJKLMWXCVBNazertyuiopqsdfghjklmwxcvbn1234567890_";
	etk::String out;
	for (uint_t iii=0; iii< _size; ++iii) {
		out += value[etk::random::irand(0,value.size()-1)];
	}
	return out;
}

