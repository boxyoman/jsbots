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
		bots[0]->pos.x = 90;
		bots[0]->pos.y = 90;
		
		bots[1]->pos.x = 10;
		bots[1]->pos.y = 10;
		
		for(int i = 0; i<4; i++){
			bullets[i].ison = 0;
			bullets[i].explodeTime = 0;
			bullets[i].deathCheck = 0;
		}
		
		glutInit(&argc, argv);
	}else{
		printf("Need at least 2 bots");
		exit(1);
	}
};
void game::init(){
	glutInitWindowPosition(-1, -1);
    glutInitWindowSize(500, 500);
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
void game::changeSize(int width, int height){
	glViewport(0, 0, width, height);
	
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 100, 0, 100);
    glMatrixMode(GL_MODELVIEW);
};

void game::idle(){
	glutPostRedisplay();
}

void game::loop(){
	//Get the times
	double cTime = (double)glutGet(GLUT_ELAPSED_TIME)/1000;
	gameGlobals::elapsedTime = cTime - gameGlobals::currentTime;
	gameGlobals::currentTime = cTime;
	
	glClearColor(.5, 0.5,0.5,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Draw and update bots
	static int botsLeft = self->numBots;
	if(botsLeft > 1){
		botsLeft = 0;
		for(int i=0;i<self->numBots;i++){
			if(self->bots[i]->health > 0){

				botsLeft++;
				//Update
				self->bots[i]->update();

				//Draw
				glPushMatrix();
				glTranslatef(self->bots[i]->pos.x, self->bots[i]->pos.y, 0.0);

				glBegin(GL_POLYGON);
					glVertex3f(-0.5, -0.5, 0.0);
					glVertex3f(-0.5, 0.5, 0.0);
					glVertex3f(0.5, 0.5, 0.0);
					glVertex3f(0.5, -0.5, 0.0);
				glEnd();
				glPopMatrix();
			}
		}
		for(int i=0;i<4;i++){
			if(self->bullets[i].ison == 1 && self->bullets[i].explodeTime >= gameGlobals::currentTime){

				//Make it look like the bullets traveling
				vector<double> temp = (self->bullets[i].dest - self->bullets[i].pos).unit();
				temp = temp * 50 *gameGlobals::elapsedTime;
				self->bullets[i].pos = self->bullets[i].pos + temp;

				self->bullets[i].deathCheck = 0;
				//Check to see if it has collided with the wall
				if(self->bullets[i].pos.x <= 0){
					self->bullets[i].pos.x = 0;
					self->bullets[i].dest = self->bullets[i].pos;
					self->bullets[i].explodeTime = gameGlobals::currentTime;
				}
				if(self->bullets[i].pos.x >= 100){
					self->bullets[i].pos.x = 100;
					self->bullets[i].explodeTime = gameGlobals::currentTime;
					self->bullets[i].dest = self->bullets[i].pos;
				}
				if(self->bullets[i].pos.y <= 0){
					self->bullets[i].pos.y = 0;
					self->bullets[i].explodeTime = gameGlobals::currentTime;
					self->bullets[i].dest = self->bullets[i].pos;
				}
				if(self->bullets[i].pos.y >= 100){
					self->bullets[i].pos.y = 100;
					self->bullets[i].explodeTime = gameGlobals::currentTime;
					self->bullets[i].dest = self->bullets[i].pos;
				}

				glPushMatrix();
				glTranslatef(self->bullets[i].pos.x, self->bullets[i].pos.y, 0.0);

				glBegin(GL_POLYGON);
					glVertex3f(-0.2, -0.2, 0.0);
					glVertex3f(-0.2, 0.2, 0.0);
					glVertex3f(0.2, 0.2, 0.0);
					glVertex3f(0.2, -0.2, 0.0);
				glEnd();
				glPopMatrix();
			}else if(self->bullets[i].explodeTime+.5 >= gameGlobals::currentTime && self->bullets[i].ison == 1){

				//Check to see if anyone got hit
				if(self->bullets[i].deathCheck == 0){
					for(int j = 0; j<self->numBots; j++){
						double dist = self->bullets[i].dest.distance(self->bots[j]->pos);
						if(dist <= .5){
							self->bots[j]->health -= 20;
						}else if(dist <= 1){
							self->bots[j]->health -= 10;
						}else if(dist <= 2){
							self->bots[j]->health -= 5;
						}
						printf("%s: %f\n", self->bots[j]->name.c_str(), self->bots[j]->health);
					}
					printf("\n");
					self->bullets[i].deathCheck = 1;
				}

				//Blowing up
				glPushMatrix();
				glTranslatef(self->bullets[i].dest.x, self->bullets[i].dest.y, 0.0);

				glBegin(GL_POLYGON);
					glVertex3f(-2.0, -2.0, 0.0);
					glVertex3f(-2.0, 2.0, 0.0);
					glVertex3f(2.0, 2.0, 0.0);
					glVertex3f(2.0, -2.0, 0.0);
				glEnd();
				glPopMatrix();
			}else if(self->bullets[i].explodeTime+.5 <= gameGlobals::currentTime){
				self->bullets[i].ison = 0;
			}
		}
	}else{
		for(int i=0;i<self->numBots;i++){
			if(self->bots[i]->health > 0){
				printf("\n%s wins!! \n\n", self->bots[i]->name.c_str());
				exit(1);
			}
		}
			
	}
	
	glutSwapBuffers();
};
//Called when a bot wants to shoot
int game::shoot(double ang, double dist, void* bot){
	jsbot *shotBot = reinterpret_cast<jsbot*>(bot);
	for(int i = 0; i<self->numBots; i++){
		if(self->bots[i] == shotBot){
			if(self->bullets[i].ison == 0){
				
				if(dist > 80){
					dist = 80;
				}
				
				self->bullets[i].ison = 1;
				self->bullets[i].pos = self->bots[i]->pos;
				//For what ever reason sin and cos are backwards
				self->bullets[i].dest.x = cos(ang)*dist + self->bots[i]->pos.x;
				self->bullets[i].dest.y = sin(ang)*dist + self->bots[i]->pos.y;
				
				double dist = (self->bullets[i].pos - self->bullets[i].dest).mag();
				
				self->bullets[i].explodeTime = dist/50+gameGlobals::currentTime;
				
				return 1;
			}else{
				return 0;
			}
		}
	}
	return -1;
}
//Called when a bot is scanning
double game::scan(double ang, double width, void* bot){
	jsbot *scanBot = reinterpret_cast<jsbot*>(bot);
	for(int i = 0; i<self->numBots; i++){
		if(self->bots[i]!=scanBot){
			double angMin = ang - width/2;
			double angMax = ang + width/2;
			double angBot = scanBot->pos.angle(self->bots[i]->pos);
			
			//Make sure that the angle that it is between 0 and 2pi
			while(angMin<0){
				angMin = angMin+2*M_PI;
			}
			while(angMin>2*M_PI){
				angMin = angMin-2*M_PI;
			}
			while(angMax<0){
				angMax = angMax+2*M_PI;
			}
			while(angMax>2*M_PI){
				angMax = angMax-2*M_PI;
			}
			while(angBot>2*M_PI){
				angBot = angBot-2*M_PI;
			}
			while(angBot<0){
				angBot = angBot+2*M_PI;
			}
			//Make sure that the min isn't greater than the max
			while(angMin > angMax){
				angMax = angMax+2*M_PI;
			}
			if(angMin <= angBot && angBot <= angMax){
				return scanBot->pos.distance(self->bots[i]->pos);
			}else{
				return 0.0;
			}
		}
	}
};