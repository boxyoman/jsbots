#import "openGL.h"
#include <OpenGL/gl.h>

typedef struct _vertexStruct
{
    GLfloat position[2];
} vertexStruct;

@implementation MyOpenGLView
@synthesize game = _game;

- (void) prepareOpenGL{
	GLint swapInt = 1;
	[[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
	
	CVDisplayLinkCreateWithActiveCGDisplays(&displayLink);
	CVDisplayLinkSetOutputCallback(displayLink, &MyDisplayLinkCallback, (__bridge void *)self);
	
	CGLContextObj cglContext = [[self openGLContext] CGLContextObj];
	CGLPixelFormatObj cglPixelFormat = [[self pixelFormat] CGLPixelFormatObj];
	CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink, cglContext, cglPixelFormat);

	// Activate the display link
	CVDisplayLinkStart(displayLink);
	
}

- (id) initWithFrame: (NSRect) contentRect{
	self = [super initWithFrame:contentRect pixelFormat:[NSOpenGLView defaultPixelFormat]];
	return self;
}

static CVReturn MyDisplayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp* now, const CVTimeStamp* outputTime, CVOptionFlags flagsIn, CVOptionFlags* flagsOut, void* displayLinkContext){
    CVReturn result = [(__bridge MyOpenGLView*)displayLinkContext getFrameForTime:outputTime];
    return result;
}

- (CVReturn) getFrameForTime: (const CVTimeStamp*) outputTime{
	[self setNeedsDisplay:YES];
	return kCVReturnSuccess;
}

-(void) drawBot: (jsBot*) bot{
	
}

-(void) drawRect: (NSRect) bounds{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	const vertexStruct vertices[] = {
		{0.1,  0.1},
		{0.1, -0.1},
		{-0.1,-0.1},
		{-0.1, 0.1}
	};
	const GLubyte indices[] = {
		0,1,2,
		0,2,3
	};
	
	glColor3f(1.0f, 0.85f, 0.35f);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, sizeof(vertexStruct), &vertices[0].position);
 
	glDrawElements(GL_TRIANGLE_STRIP, sizeof(indices)/sizeof(GLubyte), GL_UNSIGNED_BYTE, indices);
	
	
	
	glFlush();
}



@end