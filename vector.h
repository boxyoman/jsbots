#ifndef _VECTOR_H_
#define _VECTOR_H_

template <typename type> class vector{
	public:
		type x;
		type y;
		
		vector();
		vector(type, type);

		void set(type, type);
		
		vector operator + (vector);
		vector operator - (vector);
		
		type dot(vector);
};    
            
#endif