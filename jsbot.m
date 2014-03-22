#import "vector.h"
#import "jsbot.h"
#import "console.h"
#include <math.h>

@implementation jsBot
@synthesize jsContext=_jsContext;
@synthesize position=_position;
@synthesize speed = _speed;
@synthesize angle = _angle;
@synthesize name = _name;

- (id) initWithFile: (NSString *) botFile VirtualMachine: (JSVirtualMachine*) machine Position: (jsVector*) pos{
	self = [[jsBot alloc] init];
	if(self){
		
		//set up some initial variables
		_position = pos;
		_console = [[jsConsole alloc] init];
		_name = botFile;
		
		//setup javascript context
		_jsContext = [[JSContext alloc] initWithVirtualMachine: machine];
		NSError *error;
		NSString *jsFile = [NSString stringWithContentsOfFile:botFile encoding:NSUTF8StringEncoding error:&error];
		if(error){
			NSLog(@"Error reading file: %@", error.localizedDescription);
			return nil;
		}
		
		//Setup variables on the global object in the context
		_jsContext[@"Vector"] = [jsVector class];
		_jsContext[@"mybot"] = self;
		_jsContext[@"console"] = _console;
		
		
		//Evaluate the script
		[_jsContext evaluateScript: jsFile];
		//NSLog([result toString]);
	}
	return self;
}


-(void) driveSpeed: (int) speed Angle: (int) angle{
	_speed = speed;
	_angle = angle;
}
@end
