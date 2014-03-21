#ifndef vector_h
#define vector_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#import <JavaScriptCore/JavaScriptCore.h> 
#import "jsbot.h"

@interface jsGame: NSObject {
	float _x,_y;
	JSVirtualMachine *virtualMachine;
	NSArray *jsBots;
}
- (id) init;
@end
#endif
