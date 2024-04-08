#include <iostream>
#include <math.h>
#include <fstream>

/*
La idea de la clase tablero es que contenga la informaci�n del tablero, que luego las piezas puedan leer y escribir
desde la clase juego, que es la que realmente contiene las piezas
*/

using namespace std;

class Tablero
{
public:
	// Matriz del tablero
	int** mat{}; 
	Tablero() {};

	int defTablero[8][8] =
	{ -2,-3,-4,-5,-6,-5,-4,-3,-2
	 - 1,-1,-1,-1,-1,-1,-1,-1,
	  0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0,
	  1, 1, 1, 1, 1, 1, 1, 1,
	  2, 3, 4, 5, 6, 4, 3, 2
	};

	// Par�metros del tablero
	int dim_x, dim_y;

	// Constructor del tablero en forma de matriz
	Tablero(int dim_x, int dim_y, int modo) : dim_x(dim_x), dim_y(dim_y), modo (modo)
	{
		mat = new int* [dim_x];
		for (int i = 0; i < dim_x; i++)
		{
			mat[i] = new int[dim_y];
		}
		switch (modo)
		{
		case 0:
			mat = new int* [dim_x];
			for (int i = 0; i < dim_x; i++)
			{
				mat[i] = new int[dim_y];
			}
		case 1:
			this->dim_x = 8;
			this->dim_y = 8;
			int aux[8][8] =
					{-2,-3,-4,-5,-6,-4,-3,-2,
					-1,-1,-1,-1,-1,-1,-1,-1,
					0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0,
					1, 1, 1, 1, 1, 1, 1, 1,
					2, 3, 4, 5, 6, 4, 3, 2 };
			for (int i = 0; i < dim_x; i++)
			{
				for (int j = 0; j < dim_x; j++)
				{
					mat[i][j] = aux [i][j];
				}
			}
		case 2:

		default:
			break;
		}
	}

	// Constructor del tablero desde un archivo
	// Declara el tablero y lee un archivo.A partir de este inicializa la matriz del tablero.
	// El formato del tablero es (todo separado por espacios) : dim_x, dim_y, valores de la matriz
	// De momento no funciona  pero puede ser útil en el futuro
	Tablero(std::ifstream* file); // TODO: Lectura de archivos

	// Comprobaci�n de que una posici�n es v�lida
	bool posValid(int x, int y);
	
	// Definir el tablero
	void definirTablero(int modo);
	
private:
	int modo;
};

Tablero::Tablero(std::ifstream* file)
{
	int dim_x, dim_y;
	if (!(*file).is_open())
	{
		std::cout << "Error en la apertura del archivo" << std::endl;
	}
	*file >> dim_x;
	*file >> dim_y;
	int** tab = new int* [dim_x];
	for (int i = 0; i < dim_x; i++)
	{
		*(tab + i) = new int[dim_y];
	}
	int prov = 0;
	for (int i = 0; i < dim_x; i++)
	{
		for (int j = 0; j < dim_y; j++)
		{
			*file >> prov;
			mat[i][j] = prov;
		}
	}
	(*file).close();
}

bool Tablero::posValid(int x, int y)
{
	bool x_valid = (x < dim_x && x>0);
	bool y_valid = (y < dim_y && y>0); //Cambio de x>0 por y>0
	return x_valid && y_valid;
}


void Tablero::printTab(int pos_x,int pos_y) {

	for (int i = 0; i < 8; i++) {
		cout << "\n";
		for (int j = 0; j < 8; j++) {
			if (defTablero[i][j] < 0) {
				cout << "|" << defTablero[i][j] << "|";
			}
			else {
				cout << "|" << " " << defTablero[i][j] << "|";


			}
		}
	}


}

void Tablero::printPosibles(int x, int y){

	for (int i = 0; i < dim_x; i++) {
		cout << "\n";
		for (int j = 0; j < dim_y; j++) {
			defTablero[x][y] = 9;
			cout << "|" << defTablero[i][j] << "|";

		}
	}
}


std::ostream& operator << (std::ostream& o, Tablero tab)
{
	for (int i = 0; i < tab.dim_x; i++)
	{
		for (int j = 0; i < tab.dim_x; i++)
		{
			o << tab.mat[i][j] << " ";
		}
		o << std::endl;
	}
	return o;
}