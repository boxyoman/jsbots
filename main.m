#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#import <JavaScriptCore/JavaScriptCore.h>
#import <Cocoa/Cocoa.h>
#import "game.h"

int main(int argc, char* argv[]) {
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
	id window = [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 200, 200) styleMask:NSTitledWindowMask|NSClosableWindowMask backing:NSBackingStoreBuffered defer:NO];
	[window cascadeTopLeftFromPoint:NSMakePoint(20,20)];
	[window setTitle:appName];
	[window makeKeyAndOrderFront:nil];
	[NSApp activateIgnoringOtherApps:YES];
	[NSApp run];
	return 0;
}
