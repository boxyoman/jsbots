#import "jsbot.h"
#import "console.h"
#include <math.h>

@implementation jsConsole

-(void) log: (NSString *) string{
	jsBot *bot = [[JSContext currentContext][@"mybot"] toObjectOfClass: [jsBot class]];
	
	botName = bot.name;
	message = string;
	
	[self performSelectorOnMainThread:@selector(logMain) withObject:nil waitUntilDone:YES];
}

-(void) logMain{
	NSLog(@"%@: %@", botName, message);
}



@end