#import "game.h"
#include <math.h>

@implementation jsGame
-(id) init{
	self = [super init];
	if(self){
		virtualMachine = [[JSVirtualMachine alloc] init];
		jsBots = [NSArray arrayWithObjects: [[jsBot alloc] initWithFile: @"test.js" VirtualMachine: virtualMachine], nil];
	}
	return self;
}

@end
