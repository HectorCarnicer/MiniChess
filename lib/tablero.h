#include <iostream>
#include <math.h>
#include <fstream>
#include "Basic/matrix.h"

/*
La idea de la clase tablero es que contenga la informaci�n del tablero, que luego las piezas puedan leer y escribir
desde la clase juego, que es la que realmente contiene las piezas
*/

class Tablero
{
public:
	// Matriz del tablero
	int** mat;

	// Par�metros del tablero
	int dim_x, dim_y;

	// Constructor del tablero en forma de matriz
	Tablero(int dim_x, int dim_y); /*: dim_x(dim_x), dim_y(dim_y)
	{
		mat = new int * [dim_x];
		for (int i = 0; i < dim_x; i++)
		{
			mat[i] = new int[dim_y];
		}
	}

	// Constructor del tablero desde un archivo
	// Declara el tablero y lee un archivo.A partir de este inicializa la matriz del tablero.
	// El formato del tablero es (todo separado por espacios) : dim_x, dim_y, valores de la matriz
	// De momento no funciona
	Tablero(std::ifstream* file); // TODO: Lectura de archivos

	// Comprobaci�n de que una posici�n es v�lida
	bool posValid(int x, int y);
	
	// Definici�n del tablero inicial en funci�n del modo de juego
	void definirTablero() {
		/*Definir piezas del tablero, de momento con numeros, blancas positivas, negras negativas
			0: vac�o
			1: pe�n
			2: torre
			3: caballo
			4: alfil
			5: reina
			6: rey
		Ojo: la fila vac�a ya est� inicializada a cero en: (l�nea 23) Tablero(int x, int y) : dim_x (x), dim_y(y)
		*/
		for (int i = 0; i < dim_x; i++) {
			for (int j = 0; j < dim_y; j++) {			
				if (j < dim_y && i == 0){
					if (modo == "baby") {
						mat[i][j] = -6 + j;
					}
					else if (modo == "gardner") {
						mat[i][j] = -2 - j;
					}
				}
				else if (j < dim_y && i == 1) {
					mat[i][j] = -1;
				}
				else if (j < dim_y && i == 3) {
					mat[i][j] = 1;
				}
				else if (j < dim_y && i == 4) {
					mat[i][j] = 2 + j;
				}
			}
		}
	}
	
private:
	std::string modo;
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
	bool y_valid = (y < dim_y && x>0);
	return x_valid && y_valid;
}

void Tablero::definirTablero() {
	for (int i = 0; i < dim_x; i++) {
		for (int j = 0; j < dim_y; j++) {
			if (j < dim_y && i == 0) {
				if (modo == "baby") {
					mat[i][j] = -6 + j;
				}
				else if (modo == "gardner") {
					mat[i][j] = -2 - j;
				}
			}
			else if (j < dim_y && i == 1) {
				mat[i][j] = -1;
			}
			else if (j < dim_y && i == 2) {
				mat[i][j] = 0;
			}
			else if (j < dim_y && i == 3) {
				mat[i][j] = 1;
			}
			else if (j < dim_y && i == 4) {
				mat[i][j] = 2 + j;
			}
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