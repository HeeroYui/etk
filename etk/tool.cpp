/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/tool.h>
#include <etk/os/FSNode.h>
// for the rand ...
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

float etk::tool::frand(float _a, float _b)
{
	return ( rand()/(float)RAND_MAX ) * (_b-_a) + _a;
}


int32_t etk::tool::irand(int32_t _a, int32_t _b)
{
	return (int32_t)(( rand()/(float)RAND_MAX ) * ((float)_b-(float)_a) + (float)_a);
}
