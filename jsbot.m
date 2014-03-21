#import "vector.h"
#import "jsbot.h"
#include <math.h>

@implementation jsBot
@synthesize jsContext=_jsContext;
@synthesize position=_position;
@synthesize speed = _speed;
@synthesize angle = _angle;

- (id) initWithFile: (NSString *) botFile VirtualMachine: (JSVirtualMachine*) machine Position: (jsVector*) pos{
	self = [[jsBot alloc] init];
	if(self){
		
		_position = pos;
		
		//setup javascript context
		_jsContext = [[JSContext alloc] initWithVirtualMachine: machine];
		NSError *error;
		NSString *jsFile = [NSString stringWithContentsOfFile:botFile encoding:NSUTF8StringEncoding error:&error];
		if(error){
			NSLog(@"Error reading file: %@", error.localizedDescription);
			return nil;
		}
		_jsContext[@"Vector"] = [jsVector class];
		_jsContext[@"mybot"] = self;
		
		
		//Evaluate the script
		JSValue* result = [_jsContext evaluateScript: jsFile];
		NSLog([result toString]);
	}
	return self;
}


-(void) driveSpeed: (int) speed Angle: (int) angle{
	_speed = speed;
	_angle = angle;
}
@end
