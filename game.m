#import "vector.h"
#import "game.h"
#include <math.h>

@implementation jsGame
-(id) initWithArgc: (int) argc Argv: (char**) argv{
	self = [super init];
	if(self){
		virtualMachine = [[JSVirtualMachine alloc] init];
		NSLog(@"For some odd reason I need this here...");
	
		//make bots based off of arguments to the program
		numberOfBots = argc;
		jsBots = [NSArray arrayWithObjects: nil];
		for(int i = 1; i<numberOfBots && i <= 4; i++){
		
			NSString* botFileName = [NSString stringWithCString:argv[i] encoding:NSUTF8StringEncoding];
		
			jsVector* position = [[jsVector alloc] initWithX: 3 Y:4];
			jsBot* bot = [[jsBot alloc] initWithFile: botFileName VirtualMachine: virtualMachine Position: position];
		
			jsBots = [jsBots arrayByAddingObject: bot];
		}
	}
	return self;
}

@end
