#import "vector.h"
#import "game.h"
#include <math.h>

@implementation jsGame

@synthesize jsBots, numberOfBots;

-(id) initWithArgc: (int) argc Argv: (char**) argv{
	self = [super init];
	if(self){
		
	
		//make bots based off of arguments to the program
		numberOfBots = argc-1;
		jsBots = [NSArray arrayWithObjects: nil];
		for(int i = 1; i<=numberOfBots && i <= 4; i++){
		
			NSString* botFileName = [NSString stringWithCString:argv[i] encoding:NSUTF8StringEncoding];
		
			jsVector* position = [[jsVector alloc] initWithX: 20 Y:20];
			jsBot* bot = [[jsBot alloc] initWithFile: botFileName Position: position];
		
			jsBots = [jsBots arrayByAddingObject: bot];
		}
		
		for(int i=0; i<numberOfBots; i++){
			jsBot* bot = [jsBots objectAtIndex:i];
			//[bot main];
			bot.thread = [[NSThread alloc] initWithTarget:bot  selector:@selector(main) object:nil];
			[bot.thread start];
			
		}
	}
	return self;
}

- (void) update{
	for(int i=0; i<numberOfBots; i++){
		jsBot* bot = [jsBots objectAtIndex:i];
		[bot update];
	}
}

@end