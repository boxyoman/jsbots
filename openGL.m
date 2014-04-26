#import "openGL.h"
#import "vector.h"

typedef struct _vertexStruct
{
    GLfloat position[2];
} vertexStruct;

const vertexStruct vertices[] = {
	{{ 10,  10}},
	{{ 10, -10}},
	{{-10, -10}},
	{{-10,  10}}
};
const GLubyte indices[] = {
	0,1,2,
	0,2,3
};

@implementation MyOpenGLView
@synthesize game = _game;

- (void) drawBots{
	for(int i=0; i<_game.numberOfBots; i++){
		
		glColor3f(1.0f, 0.85f, 0.35f);
		
		jsBot *bot = [[_game jsBots] objectAtIndex:i];
		
		jsVector *vector = bot.position;
		glUniform2f(uniforms[UNIFORM_POSITION], vector.x, vector.y);
	
	
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, sizeof(vertexStruct), &vertices[0].position);
 
		glDrawElements(GL_TRIANGLE_STRIP, sizeof(indices)/sizeof(GLubyte), GL_UNSIGNED_BYTE, indices);
	}
}

-(void) drawRect: (NSRect) bounds{
	glClearColor(0.3, 0.3, 0.3, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0,0,600,600);
	
	[self drawBots];
	
	
	glFlush();
	
	
	[_game update];
}


- (void) prepareOpenGL{
	GLint swapInt = 1;
	[[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
	
	[self makeShaders];
	
	
	//Setup display loop function. Updates with every screen refresh.
	CVDisplayLinkCreateWithActiveCGDisplays(&displayLink);
	CVDisplayLinkSetOutputCallback(displayLink, &MyDisplayLinkCallback, (__bridge void *)self);
	
	CGLContextObj cglContext = [[self openGLContext] CGLContextObj];
	CGLPixelFormatObj cglPixelFormat = [[self pixelFormat] CGLPixelFormatObj];
	CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink, cglContext, cglPixelFormat);

	// Activate the display link
	CVDisplayLinkStart(displayLink);
}

- (BOOL) makeShaders{
	//Variables for my shaders
	GLuint vertexShader, fragmentShader;
	
	shaderProgram = glCreateProgram();
	
	//Complie the shader
	[self compileShader: &vertexShader type:GL_VERTEX_SHADER file:@"shaders/shader.vsh"];
	[self compileShader: &fragmentShader type:GL_FRAGMENT_SHADER file:@"shaders/shader.fsh"];
	
	//Attach the shader
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	
	
	if (![self linkProgram:shaderProgram]) {
        NSLog(@"Failed to link program: %d", shaderProgram);
    
        if (vertexShader) {
            glDeleteShader(vertexShader);
            vertexShader = 0;
        }
        if (fragmentShader) {
            glDeleteShader(fragmentShader);
            vertexShader = 0;
        }
        if (shaderProgram) {
            glDeleteProgram(shaderProgram);
            shaderProgram = 0;
        }
        return NO;
    }
	
	uniforms[UNIFORM_SCALE] = glGetUniformLocation(shaderProgram, "scale");
	uniforms[UNIFORM_POSITION] = glGetUniformLocation(shaderProgram, "realPosition");
	
	//check to make sure the location were found
	if(uniforms[UNIFORM_SCALE] == -1){
		NSLog(@"location scale doesn't exist in vertex shader.");
	}
	
	if(uniforms[UNIFORM_POSITION] == -1){
		NSLog(@"location realPosition doesn't exist in vertex shader.");
	}
	
	//Set the shaderProgram
	glUseProgram(shaderProgram);
	
	//set up the scale of the play feild
	glUniform1f(uniforms[UNIFORM_SCALE], 1.0/500.0);
	
	
	if (vertexShader) {
		glDetachShader(shaderProgram, vertexShader);
		glDeleteShader(vertexShader);
	}
	if (fragmentShader) {
		glDetachShader(shaderProgram, fragmentShader);
		glDeleteShader(fragmentShader);
	}

    return YES;
}

- (BOOL)linkProgram:(GLuint)prog{
    GLint status;
    glLinkProgram(prog);
    
#if defined(DEBUG)
    GLint logLength;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        NSLog(@"Program link log:\n%s", log);
        free(log);
    }
#endif
    
    glGetProgramiv(prog, GL_LINK_STATUS, &status);
    if (status == 0) {
        return FALSE;
    }
    
    return TRUE;
}

- (BOOL)compileShader:(GLuint *)shader type:(GLenum)type file:(NSString *)file{
    GLint status;
    const GLchar *source;
    
    source = (GLchar *)[[NSString stringWithContentsOfFile:file encoding:NSUTF8StringEncoding error:nil] UTF8String];
    if (!source) {
        NSLog(@"Failed to load vertex shader. Source not found.");
        return NO;
    }
    
    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &source, NULL);
    glCompileShader(*shader);
    
#if defined(DEBUG)
    GLint logLength;
    glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetShaderInfoLog(*shader, logLength, &logLength, log);
        NSLog(@"Shader compile log:\n%s", log);
        free(log);
    }
#endif
    
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
    if (status == 0) {
        glDeleteShader(*shader);
        return NO;
    }
    
    return YES;
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




@end