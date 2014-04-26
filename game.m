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
			//Get the file name
			NSString* botFileName = [NSString stringWithCString:argv[i] encoding:NSUTF8StringEncoding];
			
			//set the initial position
			jsVector* position = [[jsVector alloc] initWithX: 20 Y:20];
			//make the bot
			jsBot* bot = [[jsBot alloc] initWithFile: botFileName Position: position];
			bot.game = self;
			//add bot to array
			jsBots = [jsBots arrayByAddingObject: bot];
		}
		
		//start the bots threads
		for(int i=0; i<numberOfBots; i++){
			jsBot* bot = [jsBots objectAtIndex:i];
			bot.thread = [[NSThread alloc] initWithTarget:bot  selector:@selector(main) object:nil];
			[bot.thread start];
			
		}
	}
	return self;
}
//issue will come up when scan are around 0 and 360
- (void) scan: (jsBot*) bot{
	bot.returnValues = 0;
	for(int i=0; i<numberOfBots; i++){
		jsBot* boti = [jsBots objectAtIndex:i];
		if(boti != bot){
			jsVector* diff = [boti.position sub:bot.position];
			int angleOfBot = (int)round(diff.angle*180/M_PI);
			if(angleOfBot < bot.scanAngle + bot.scanResolution && angleOfBot > bot.scanAngle - bot.scanResolution){
				int length = (int)round(diff.length);
				if(bot.returnValues > length || bot.returnValues == 0){
					bot.returnValues = length;
				}
			} 
		}
	}
}

- (void) update{
	for(int i=0; i<numberOfBots; i++){
		jsBot* bot = [jsBots objectAtIndex:i];
		[bot update];
	}
}

@end