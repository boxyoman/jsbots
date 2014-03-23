#import "myApp.h"

int main(int argc, char* argv[]) {
	return [[[myApp alloc] initWithArgc: argc Argv: argv] returnValue];
}