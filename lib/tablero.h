#include <iostream>
#include <math.h>
#include <fstream>
#include "Piezas/pieza.h"

#define tam 4
// enum Piezas { VACIO = 0, PEON, TORRE, ALFIL, CABALLO, REY, REINA };

using namespace std;

class Tablero
{
public:
	// Dimensiones del tablero
	int dim_x;
	int dim_y;
	// Matriz del tablero
	int** tab;
	pieza** tablero;
	void printPosibles();

	//Declaración de la matriz del tablero
	Tablero(int x, int y) : dim_x (x), dim_y(y) 
	{
		// Declara el tablero y lo inicializa a cero
		tab = new int*[dim_x];
		for (int i = 0; i < dim_x; i++)
		{
			*(tab + i) = new int[dim_y];
		}
		for (int i = 0; i < dim_x; i++)
		{
			for (int j = 0; j < dim_y; j++)
			{
				tab[i][j] = 0;
			}
		}
	}

	void printPosibles();
	/*
	Tablero(ifstream* file)
	{
		// Declara el tablero y lee un archivo. A partir de este inicializa la matriz del tablero.
		// El formato del tablero es (todo separado por espacios) : dim_x, dim_y, valores de la matriz
		if (!(*file).is_open())
		{
			std::cout << "Error en la apertura del archivo" << std::endl;
		}
		*file >> dim_x;
		*file >> dim_y;
		tab = new int* [dim_x];
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
				tab[i][j] = prov;
			}
		}
		(*file).close();
	}*/
	
	void definirTablero() {
		/*Definir piezas del tablero, de momento con numeros, blancas positivas, negras negativas
			0: vacío
			1: peón
			2: torre
			3: caballo
			4: alfil
			5: reina
			6: rey
		Ojo: la fila vacía ya está inicializada a cero en: (línea 23) Tablero(int x, int y) : dim_x (x), dim_y(y)
		*/
		for (int i = 0; i < dim_x; i++) {
			for (int j = 0; j < dim_y; j++) {			
				if (j < dim_y && i == 0) {
					tab[i][j] = -6 + j;
				}
				else if (j < dim_y && i == 1) {
					tab[i][j] = -1;
				}
				else if (j < dim_y && i == 3) {
					tab[i][j] = 1;
				}
				else if (j < dim_y && i == 4) {
					tab[i][j] = 2 + j;
				}
			}
		}
	}

	/*void print()
	{
		for (int i = 0; i < dim_x; i++)
		{
			for (int j = 0; j < dim_y; j++)
			{
				cout << tab[i][j];
			}
			cout << endl;
		}
		cout << endl;
	}
	*/



void updateTablero(); // Actualiza las posiciones de todas las piezas
private:
	
	// El tablero puede ser una matriz de enteros donde cada valor represente una pieza
	// Por ejemplo, se puede tomar valores negativos para piezas negras y valores positivos para blancas, con 0 como casilla en blanco
};

void Tablero::updateTablero()
{
	// Recorre la matriz de piezas y actualiza la posición de cada una
	for (int i = 0; i < dim_x; i++)
	{
		for (int j = 0; j < dim_y; j++)
		{
			tablero[i][j].updatePosPosibles();
		}
	}
}
 
//tras calcular las posibles movimientos, los muestra en el tablero
//para que el jugador sepa donde es posible arrastra la pieza
void printPosibles() {

	for (int i = 0; i < dim_x; i++)
	{
		for (int j = 0; j < dim_y; j++)
		{
			cout << tab[i][j];
		}
	}



}