#ifndef _GAME_H_
#define _GAME_H_

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <OpenGL/glext.h>
#include "bot.h"
#include "gameTemplate.h"


using namespace v8;
using namespace std;

typedef struct{
	vector<double> pos;
	vector<double> dest;
	double explodeTime;
	int ison;
}bullet;

class game: public gamePrototype{
	public:
		game(int argc, char* argv[]);
		void init();
		void start();
		int numBots;
		jsbot **bots;
		
		bullet bullets[4];
		
		double scan(double ang, double width, void* bot);
		int shoot(double ang, double distance, void* bot);
	private:
		static void loop();
		static void changeSize(int, int);
		static void idle();
};

#endif