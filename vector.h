#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#import <JavaScriptCore/JavaScriptCore.h> 

@class jsvector;

@protocol VectorJSExport <JSExport>
	@property (nonatomic) float x;
	@property (nonatomic) float y;
	@property (nonatomic, readonly) float length;
	+(id) vectorWithX: (float) x Y:(float) y; 
	-(jsvector *) add: (jsvector*) b;
	-(jsvector *) unit;
	-(jsvector *) dotProduct: (jsvector *) b;
	-(jsvector *) crossProduct: (jsvector *) b;
@end

@interface jsvector: NSObject <VectorJSExport>{
	float _x,_y;
}
- (id) initWithX: (float) x Y: (float) y;
@end
