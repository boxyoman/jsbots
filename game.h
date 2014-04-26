#ifndef game_h
#define game_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#import <JavaScriptCore/JavaScriptCore.h> 
#import "jsbot.h"

@interface jsGame: NSObject {
	float _x,_y;
	JSVirtualMachine *virtualMachine;
	jsBullet *bullets[4];
	NSArray *jsBots;
	int numberOfBots;
}
@property (nonatomic, readonly) NSArray *jsBots;
@property (nonatomic, readonly) int numberOfBots;

- (jsBullet *)getBullet: (int) index;
- (void) update;
- (void) scan: (id) bot;
- (void) shoot: (id) bot;
- (id) initWithArgc: (int) argc Argv: (char**) argv;
@end
#endif