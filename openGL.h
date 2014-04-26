#ifndef openGL_h
#define openGL_h
#import <Cocoa/Cocoa.h>
#include <OpenGL/gl.h>
#import "game.h"

enum{
    ATTRIB_VERTEX,
    ATTRIB_COLOR,
    ATTRIB_TEXTURE,
    NUM_ATTRIBUTES
};

enum{
    UNIFORM_POSITION,
	UNIFORM_SCALE,
    NUM_UNIFORMS
};


@interface MyOpenGLView : NSOpenGLView{
	CVDisplayLinkRef displayLink;
	GLuint shaderProgram;
	GLint uniforms[NUM_UNIFORMS];
}

@property (nonatomic, weak) jsGame *game;

- (void) drawBots;
- (void) drawRect: (NSRect) bounds;


- (id) initWithFrame: (NSRect) contentRect;
- (CVReturn) getFrameForTime: (const CVTimeStamp*) outputTime;
@end
#endif