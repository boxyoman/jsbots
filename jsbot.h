#ifndef jsbot_h
#define jsbot_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#import <JavaScriptCore/JavaScriptCore.h> 

@class jsBot, jsVector;

@protocol BotJSExport <JSExport>
	-(void) driveSpeed: (int) speed Angle: (int) angle;
	@property (nonatomic, strong) jsVector* position;
	@property (nonatomic) int speed;
	@property (nonatomic) int angle;
@end

@interface jsBot: NSObject <BotJSExport>{
	JSContext* _jsContext;
	jsVector* _position;
	int _speed;
	int _angle;
	float _x,_y;
}
@property (nonatomic, retain) JSContext* jsContext;
- (id) initWithFile: (NSString *) botFile VirtualMachine: (JSVirtualMachine*) machine Position: (jsVector*) pos;
@end

#endif
