#include <stdio.h>
#include <stdlib.h>
#include "game.h"


int main(int argc, char* argv[]) {
	game *a = new game(argc, argv);
	a->init();
	a->start();
	
	return 0;
}