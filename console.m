#import "jsbot.h"
#import "console.h"
#include <math.h>

@implementation jsConsole

-(void) log: (NSString *) string{
	jsBot *bot = [[JSContext currentContext][@"mybot"] toObjectOfClass: [jsBot class]];
	NSLog(@"%@: %@", bot.name, string);
}

@end