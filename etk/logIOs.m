/**
 * @author Edouard DUPIN
 *
 * @copyright 2011, Edouard DUPIN, all right reserved
 *
 * @license BSD v3 (see license file)
 */


#import <UIKit/UIKit.h>
#include <etk/logIOs.h>

void iosNSLog(const char * _value) {
	NSLog(@"\r%s", _value);
}


