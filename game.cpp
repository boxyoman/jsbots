#include "game.h"

game* self;
HandleScope scope;
game::game(int argc, char* argv[]){
	
	gameGlobals::setUpGolbals();
	Handle<ObjectTemplate> global = gameGlobals::global;
	
	if(argc > 2){
		numBots = argc-1;
		bots = (jsbot**) malloc(sizeof(jsbot)*numBots);
		for(int i=0;i<numBots; i++){
			bots[i] = new jsbot(argv[i+1]);
			bots[i]->init(global);
			bots[i]->game = this;
		}
		bots[0]->pos.x = 750;
		bots[0]->pos.y = 350;
		
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
	double cTime = (double)glutGet(GLUT_ELAPSED_TIME)/1000;
	gameGlobals::elapsedTime = cTime - gameGlobals::currentTime;
	gameGlobals::currentTime = cTime;
	
	for(int i=0;i<self->numBots;i++){
		self->bots[i]->update();
	}
	
	glClearColor (.5, 0.5,0.5,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
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
//Called when a bot wants to shoot
void game::shoot(double ang, double distance, void* bot){
	
}
//Called when a bot is scanning
double game::scan(double ang, double width, void* bot){
	jsbot *scanBot = reinterpret_cast<jsbot*>(bot);
	for(int i = 0; i<self->numBots; i++){
		if(self->bots[i]!=scanBot){
			double ang2 = scanBot->pos.angle(self->bots[i]->pos);
			while(ang<0){
				ang = ang+2*M_PI;
			}
			while(ang>2*M_PI){
				ang = ang-2*M_PI;
			}
			while(ang2<0){
				ang2 = ang2+2*M_PI;
			}
			printf("%f %f\n", ang2, ang + width/2);
			printf("%f %f\n", ang2, ang - width/2);
			if(ang2 <= ang + width/2 || ang2 >= ang - width/2){
				return scanBot->pos.distance(self->bots[i]->pos);
			}else{
				return 0.0;
			}
		}
	}
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