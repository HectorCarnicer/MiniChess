#include <iostream>
#include <iostream>

/*
Esta clase es una librería para trabajar con matrices. Esto sirve para que puedas igualar matrices, imprimirlas con un cout y tal automáticamente

De momento no tiene uso, pero puede ser útil e un futuro

*/



template <class T> class matrix
{
public:
	// Constructor de una matriz genérica
	matrix <class T>(int dim_x, int dim_y) : dim_x(dim_x), dim_y (dim_y)
	{
		mat = new T*[dim_x];
		for (int i=0; i<dim_x; i++)
		{
			mat[i] = new T[dim_y];
		}
	}
	// Sobercarga de la igualadad para igualar matrices
	template <class U> void operator=(const matrix<U>& m2);
private:
	// Parámetros básicos de la matriz: array y dimensiones
	T** mat const;
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
