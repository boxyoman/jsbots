#ifndef myApp_h
#define myApp_h

#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl3.h>

@interface myApp: NSObject <NSWindowDelegate> {
}

@property (nonatomic, strong) NSWindow* window;
- (id) initWithArgc: (int) argc Argv: (char**) argv;
- (int) returnValue;
@end
#endif