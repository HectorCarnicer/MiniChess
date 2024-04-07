#include <iostream>

template <class T> class matrix
{
public:
	matrix <class T>(int dim_x, int dim_y) : dim_x(dim_x), dim_y (dim_y)
	{
		mat = new T*[dim_x];
		for (int i=0; i<dim_x; i++)
		{
			mat[i] = new T[dim_y];
		}
	}
	T** mat const;
    template <class U> void operator=(const matrix<U>& m2)
	int dim_x const;
	int dim_y const;
}; 
template <class T> std::ostream& operator<< (std::ostream & o, matrix<T> mat)
{
	std::ostream a;
	for (int i = 0; i < mat.dim_x; i++)
	{
		for (int j = 0; i < mat.dim_x; i++)
		{
			a << mat.mat[i][j] << " ";
		}
		a << std:endl;
	}
	return o << a;
}
template <class T> template <class U> void matrix<T>::operator=(const matrix<U>& m2)
{
}
