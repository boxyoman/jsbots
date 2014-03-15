#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#import <JavaScriptCore/JavaScriptCore.h> 
int main(int argc, char* argv[]) {
	JSContext *context = [[JSContext alloc] init];
	JSValue *result = [context evaluateScript: @"8+2"];
	printf("8 + 2 = %d\n\r", [result toInt32]);
	return 0;
}
