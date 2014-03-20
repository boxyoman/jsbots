#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#import <JavaScriptCore/JavaScriptCore.h> 

@class jsBot;

@protocol BotJSExport <JSExport>
	-(void) driveSpeed: (int) speed Angle: (float) angle;
@end

@interface jsBot: NSObject <BotJSExport>{
	JSContext *_jscontext;
	float _x,_y;
}
@property (nonatomic) JSContext* jscontext;
- (id) initWithX: (float) x Y: (float) y;
@end
