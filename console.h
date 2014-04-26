#ifndef console_h
#define console_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#import <JavaScriptCore/JavaScriptCore.h> 

@protocol ConsoleJSExport <JSExport>
	-(void) log: (NSString *) string;
@end

@interface jsConsole: NSObject <ConsoleJSExport>{
	NSString *botName;
	NSString *message;
}
-(void) logMain;
@end

#endif