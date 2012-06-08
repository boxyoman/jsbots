#include "bot.h"
#include "gameTemplate.h"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <OpenGL/glext.h>

#ifndef _GAME_H_
#define _GAME_H_

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