#include "game.h"

game* self;

game::game(int argc, char* argv[]){
	HandleScope scope;
	gameGlobals::setUpGolbals();
	Handle<ObjectTemplate> global = gameGlobals::global;
	
	if(argc > 2){
		numBots = argc-1;
		bots = (jsbot**) malloc(sizeof(jsbot)*numBots);
		for(int i=0;i<numBots; i++){
			bots[i] = new jsbot(argv[i+1]);
			bots[i]->init(global);
		}

		glutInit(&argc, argv);
	}else{
		printf("Need at least 2 bots");
		exit(1);
	}
};
void game::init(){
	glutInitWindowPosition(-1, -1);
    glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    
    glutCreateWindow("JS Bots");
	
	glEnable(GL_DEPTH_TEST);
	self = this;
	glutDisplayFunc(game::loop);
	glutReshapeFunc(game::changeSize);
	glutIdleFunc(game::idle);
	
};
void game::start(){
	glutMainLoop();
};
void game::loop(){
	
	glClearColor (.5, 0.5,0.5,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	self->bots[0]->pos.x = 100;
	self->bots[0]->pos.y = 100;
	
	for(int i=0;i<self->numBots;i++){
		glPushMatrix();
		glTranslatef(self->bots[i]->pos.x, self->bots[i]->pos.y, 0.0);

		glBegin(GL_POLYGON);
			glVertex3f(-10.0,-10.0,0.0);
			glVertex3f(-10.0,10,0.0);
			glVertex3f(10,10.0,0.0);
			glVertex3f(10.0,-10,0.0);
		glEnd();
		glPopMatrix();
	}
	glutSwapBuffers();
};

void game::changeSize(int width, int height){
	glViewport(0, 0, width, height);
	
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
};

void game::idle(){
	glutPostRedisplay();
}