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

class game: public gamePrototype{
	public:
		game(int argc, char* argv[]);
		void init();
		void start();
		int numBots;
		jsbot **bots;
		double scan(double ang, double width, void* bot);
		void shoot(double ang, double distance, void* bot);
	private:
		static void loop();
		static void changeSize(int, int);
		static void idle();
};

#endif