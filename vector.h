#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <math.h>

template <typename type> class vector{
	public:
		type x;
		type y;
		
		vector();
		vector(type, type);

		void set(type, type);
		
		double angle(vector);
		double distance(vector);
		double mag();
		
		vector sign();
		
		vector operator + (vector);
		vector operator - (vector);
		vector operator * (double);
		vector operator * (vector);
		
		type dot(vector);
};    
            
#endif