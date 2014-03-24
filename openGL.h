#ifndef openGL_h
#define openGL_h
#import <Cocoa/Cocoa.h>
#import "game.h"

@interface MyOpenGLView : NSOpenGLView{
	CVDisplayLinkRef displayLink;
}

@property (nonatomic, weak) jsGame *game;
- (id) initWithFrame: (NSRect) contentRect;
- (CVReturn) getFrameForTime: (const CVTimeStamp*) outputTime;
- (void) drawRect: (NSRect) bounds;
@end
#endif