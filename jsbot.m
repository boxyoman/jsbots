#import "vector.h"
#import "jsbot.h"
#import "console.h"
#import "game.h"
#include <math.h>

@implementation jsBot
@synthesize jsContext=_jsContext;
@synthesize position=_position;
@synthesize speed = _speed;
@synthesize angle = _angle;
@synthesize name = _name;
@synthesize thread, game;
@synthesize returnValues, scanAngle, scanResolution, index, shootArguments;

- (id) initWithFile: (NSString *) botFile Position: (jsVector*) pos{
	self = [[jsBot alloc] init];
	if(self){
		//set up some initial variables
		_position = pos;
		_console = [[jsConsole alloc] init];
		_name = botFile;
		returnValues = 0;
	}
	return self;
}

- (void) update{
	_position = [_position add:[jsVector vectorWithMag: _speed/30 angle: _angle*M_PI/180]];
}

-(void) driveSpeed: (int) speed Angle: (int) angle{
	if(_speed <= 50){
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
	if(resolution < 0) resolution *= -1;
	if(resolution > 10){
		resolution = 10;
	}
	while(direction < 0 || direction > 359){
		if(direction < 0){
			direction += 360;
		}
		if(direction > 359){
			direction = direction % 360;
		}
	}
	scanResolution = resolution;
	scanAngle = direction;
	[game performSelectorOnMainThread:@selector(scan:) withObject:self waitUntilDone:YES];
	return returnValues;
}

-(int) shootInDirection: (int) direction atDistance: (int) distance{
	shootArguments.direction = direction;
	shootArguments.distance = distance;
	[game performSelectorOnMainThread:@selector(shoot:) withObject:self waitUntilDone:YES];
	return self.returnValues;
}

- (void) makeSimpleFunction {
	_jsContext[@"shoot"] = ^(int direction, int distance){
		jsBot *bot = [[JSContext currentContext][@"mybot"] toObjectOfClass: [jsBot class]];
		[bot shootInDirection: direction atDistance: distance];
		return 1;
	};
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
	
	[self makeSimpleFunction];
	
	//Evaluate the script
	[_jsContext evaluateScript: jsFile];
	
	JSValue *main = _jsContext[@"main"];
	[main callWithArguments: nil];
}

@end


@implementation jsBullet
@synthesize fromBot, startPosition, position, shootArguments;
@end