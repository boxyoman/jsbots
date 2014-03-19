#import "vector.h"
#include <math.h>

@implementation jsvector
@synthesize x=_x;
@synthesize y=_y;

- (id) initWithX: (float) x Y: (float) y{
	self =  [super init];
	if(self){
		self.x = x;
		self.y = y;
	}
	return self;
}

+(id) vectorWithX: (float) x Y:(float) y{
	return [[jsvector alloc] initWithX: x Y: y];
}	


-(jsvector *) add: (jsvector*) b{
	return [[jsvector alloc] initWithX: self.x+b.x Y: self.y+b.y];
}

-(float) length{
	return sqrt(_x*_x+_y*_y);
}
-(jsvector *) unitVector{
	float leng = self.length;

	return self;
}
-(jsvector *) dotProduct: (jsvector *) b{
	return self;
}
-(jsvector *) crossProduct: (jsvector *) b{
	return self;
}

@end
