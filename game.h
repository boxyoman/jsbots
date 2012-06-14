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
	private:
		static void loop();
		static void changeSize(int, int);
		static void idle();
		int numBots;
		jsbot **bots;
		
};

#endif