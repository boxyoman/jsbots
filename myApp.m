#import "myApp.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

@implementation myApp
@synthesize window=_window;
-(id) initWithArgc: (int) argc Argv: (char**) argv{
	self = [super init];
	if(self){
		
		//Setup NSApplication
		[NSApplication sharedApplication];
		[NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
		id menubar = [NSMenu new];
		id appMenuItem = [NSMenuItem new];
		[menubar addItem:appMenuItem];
		[NSApp setMainMenu:menubar];
		id appMenu = [NSMenu new];
		id appName = [[NSProcessInfo processInfo] processName];
		id quitTitle = [@"Quit " stringByAppendingString:appName];
		id quitMenuItem = [[NSMenuItem alloc] initWithTitle:quitTitle action:@selector(terminate:) keyEquivalent:@"q"];
		[appMenu addItem:quitMenuItem];
		[appMenuItem setSubmenu:appMenu];
		
		//Setup a window
		_window = [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 600, 400) styleMask:NSTitledWindowMask|NSClosableWindowMask backing:NSBackingStoreBuffered defer:NO];
		[_window cascadeTopLeftFromPoint:NSMakePoint(20,20)];
		[_window setTitle:appName];
		[_window setDelegate: self];
		[_window makeKeyAndOrderFront:self];
		
		[NSApp activateIgnoringOtherApps:YES];
		[NSApp run];
	}
	return self;
}

-(int) returnValue{
	return 0;
}

@end