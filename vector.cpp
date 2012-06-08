#include "vector.h"

template <typename type> vector<type>::vector(){ x = 0; y = 0;};

template <typename type> vector<type>::vector(type _x, type _y){ x = _x; y = _y;};

template <typename type> void vector<type>::set(type _x, type _y){ x = _x; y = _y;};

template <typename type> type vector<type>::dot(vector<type> a){ return x*a.x + y*a.y; };

template <typename type> vector<type> vector<type>::operator + (vector<type> a){
	vector<type> temp(x+a.x, y+a.y);
	return temp;
};

template <typename type> vector<type> vector<type>::operator - (vector<type> a){
	vector<type> temp(x - a.x, y - a.y);
	return temp;
};

template class vector<int>;
template class vector<double>;
template class vector<float>;