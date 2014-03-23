#ifndef myApp_h
#define myApp_h

#import <Cocoa/Cocoa.h>
#import "game.h"

@class MyOpenGLView;

@interface myApp: NSObject <NSWindowDelegate> {
	
}
@property (strong) jsGame* game;
@property (nonatomic, strong) MyOpenGLView *view;
@property (nonatomic, strong) NSWindow* window;
- (id) initWithArgc: (int) argc Argv: (char**) argv;
- (int) returnValue;
@end
#endif