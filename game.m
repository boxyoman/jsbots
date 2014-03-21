#import "vector.h"
#import "game.h"
#include <math.h>

@implementation jsGame
-(id) init{
	self = [super init];
	if(self){
		virtualMachine = [[JSVirtualMachine alloc] init];
		jsVector* test = [[jsVector alloc] initWithX: 3 Y:4];
		NSLog(@"%f", test.length);
		jsBot* bot1 = [[jsBot alloc] initWithFile: @"test.js" VirtualMachine: virtualMachine Position: test];
		jsBots = [NSArray arrayWithObjects: bot1, nil];
	}
	return self;
}

@end