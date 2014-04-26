#ifndef vector_h
#define vector_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#import <JavaScriptCore/JavaScriptCore.h> 

@class jsVector;

@protocol VectorJSExport <JSExport, NSCopying>
	@property (nonatomic) float x;
	@property (nonatomic) float y;
	@property (nonatomic, readonly) float length;
	@property (nonatomic, readonly) float angle;
	+(id) vectorWithX: (float) x Y:(float) y;
	+(id) vectorWithMag: (float) mag angle:(float) ang;
	-(jsVector *) add: (jsVector*) b;
	-(jsVector *) sub: (jsVector*) b;
	-(jsVector *) unit;
	-(jsVector *) dotProduct: (jsVector*) b;
	-(jsVector *) crossProduct: (jsVector*) b;
@end

@interface jsVector: NSObject <VectorJSExport>{
	float _x,_y;
}
- (id) initWithX: (float) x Y: (float) y;

- (id) copyWithZone: (NSZone *) zone;
@end
#endif
