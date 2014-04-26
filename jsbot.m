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
@synthesize thread;

- (id) initWithFile: (NSString *) botFile Position: (jsVector*) pos{
	self = [[jsBot alloc] init];
	if(self){
		//set up some initial variables
		_position = pos;
		_console = [[jsConsole alloc] init];
		_name = botFile;
	}
	return self;
}

-(void) driveSpeed: (int) speed Angle: (int) angle{
	if(_speed < 50){
		if(speed > 100){
			speed = 100;
		}
		_speed = speed;
		while(angle < 0 || angle > 359){
			if(angle < 0){
				angle += 360;
			}
			if(angle > 359){
				angle = angle % 360;
			}
		}
		_angle = angle;
	}
}

-(int) scanInDirection: (int) direction WithResolution: (int) resolution{
	if(resolution > 10){
		resolution = 10;
	}else if(resolution < -10){
		resolution = -10;
	}
	return 0;
}

//This is where the thread for the robot will enter
- (void) main{
	//setup js virtual machine
	JSVirtualMachine* machine = [[JSVirtualMachine alloc] init];
	//setup javascript context
	_jsContext = [[JSContext alloc] initWithVirtualMachine: machine];
	NSError *error;
	NSString *jsFile = [NSString stringWithContentsOfFile:_name encoding:NSUTF8StringEncoding error:&error];
	if(error){
		NSLog(@"Error reading file: %@", error.localizedDescription);
	}
	
	//Setup variables on the global object in the context
	_jsContext[@"Vector"] = [jsVector class];
	_jsContext[@"mybot"] = self;
	_jsContext[@"console"] = _console;
	
	
	//Evaluate the script
	[_jsContext evaluateScript: jsFile];
	
	JSValue *main = _jsContext[@"main"];
	[main callWithArguments: nil];
}

@end
