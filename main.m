#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#import <JavaScriptCore/JavaScriptCore.h>
#import "game.h"

int main(int argc, char* argv[]) {
	jsGame* game = [[jsGame alloc] initWithArgc: argc Argv: argv];
	return 0;
}
