#import "openGL.h"
#include <OpenGL/gl.h>

typedef struct _vertexStruct
{
    GLfloat position[2];
    GLubyte color[4];
} vertexStruct;

@implementation MyOpenGLView
@synthesize game = _game;

- (id) initWithFrame: (NSRect) contentRect{
	self = [super initWithFrame:contentRect pixelFormat:[NSOpenGLView defaultPixelFormat]];
	return self;
}

-(void) drawRect: (NSRect) bounds{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	
	glColor3f(1.0f, 0.85f, 0.35f);
	
	glBegin(GL_TRIANGLES);
	{
		glVertex3f(  0.1f,  0.1f, 0.0);
		glVertex3f( -0.1f, -0.1f, 0.0);
		glVertex3f(  0.1f, -0.1f ,0.0);
	}
	glBegin(GL_TRIANGLES);
	{
		glVertex3f(  -0.1f,  0.1f, 0.0);
		glVertex3f( 0.1f, 0.1f, 0.0);
		glVertex3f(  -0.1f, -0.1f ,0.0);
	}
	glEnd();
	glFlush();
}



@end