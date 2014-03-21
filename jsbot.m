#import "jsbot.h"
#import "vector.h"
#include <math.h>

@implementation jsBot
@synthesize jsContext=_jsContext;

- (id) initWithFile: (NSString *) botFile VirtualMachine: (JSVirtualMachine*) machine{
	self = [[jsBot alloc] init];
	if(self){
		_jsContext = [[JSContext alloc] initWithVirtualMachine: machine];
		NSError *error;
		NSString *jsFile = [NSString stringWithContentsOfFile:botFile encoding:NSUTF8StringEncoding error:&error];
		if(error){
			NSLog(@"Error reading file: %@", error.localizedDescription);
			return nil;
		}
		_jsContext[@"Vector"] = [jsVector class];
		JSValue* result = [_jsContext evaluateScript: jsFile];
		NSLog(@"%d", [result toInt32]);
	}
	return self;
}
-(void) driveSpeed: (int) speed Angle: (int) angle{
	
}
@end
