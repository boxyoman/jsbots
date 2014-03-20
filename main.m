#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#import <JavaScriptCore/JavaScriptCore.h> 
#import "vector.h"

int main(int argc, char* argv[]) {
	JSContext *context = [[JSContext alloc] init];
	context[@"Vector"] = [jsvector class];
	JSValue *result = [context evaluateScript: @"var test= Vector.vectorWithXY(3,4); test.unit().length"];
	printf("%d\n\r", [result toInt32]);
	return 0;
}
