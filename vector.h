template <typename type>
class vector{
	public:
		type _x;
		type _y;
		void init(type, type);
		vector operator + (vector);
		vector operator - (vector);
		type dot(vector);
};

template <typename type> void vector<type>::init(type x, type y){
	_x = x;
	_y = y;
}

template <typename type> type vector<type>::dot(vector<type> a){
	return _x*a._x + _y*a._y;
};

template <typename type> vector<type> vector<type>::operator + (vector<type> a){
	vector<type> temp;
	temp._x = _x+a._x;
	temp._y = _y+a._y;
	return temp;
};