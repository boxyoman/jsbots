#ifndef jsbot_h
#define jsbot_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#import <JavaScriptCore/JavaScriptCore.h> 

@class jsBot, jsVector, jsConsole;

@protocol BotJSExport <JSExport>
	-(void) driveSpeed: (int) speed Angle: (int) angle;
	-(int) scanInDirection: (int) direction WithResolution: (int) resolution;
	@property (strong, readonly) jsVector* position;
	@property (readonly) int speed;
	@property (readonly) int angle;
	@property (nonatomic, copy) NSString* name;
@end

@interface jsBot: NSObject <BotJSExport>{
	jsConsole* _console;
	JSContext* _jsContext;
	jsVector* _position;
	NSString* _name;
	int _speed;
	int _angle;
	float _x,_y;
}
@property (nonatomic, retain) JSContext* jsContext;
@property (strong) NSThread *thread;
- (void) update;
- (id) initWithFile: (NSString *) botFile Position: (jsVector*) pos;
- (void) main;
@end

#endif
