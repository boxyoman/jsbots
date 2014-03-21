#ifndef jsbot_h
#define jsbot_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#import <JavaScriptCore/JavaScriptCore.h> 

@class jsBot;

@protocol BotJSExport <JSExport>
	-(void) driveSpeed: (int) speed Angle: (int) angle;
@end

@interface jsBot: NSObject <BotJSExport>{
	JSContext* _jsContext;
	float _x,_y;
}
@property (nonatomic, retain) JSContext* jsContext;
- (id) initWithFile: (NSString *) botFile VirtualMachine: (JSVirtualMachine*) machine;
@end

#endif
