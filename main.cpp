#include <stdio.h>
#include <stdlib.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <OpenGL/glext.h>

#include "bot.h"
#include "gameTemplate.h"
#include "game.h"


int main(int argc, char* argv[]) {
	game *a = new game(argc, argv);
	a->init();
	a->start();
	
	return 0;
}