#include "Piezas/pieza.h"
#include "tablero.h"
#include <iostream>

/*
La idea de esta clase es que contiene el vector de fichas que consituyen el juego
De este modo, no hay conflicto con los #include: todas las clases obtienen informaci�n de tablero.h
y la usan como par�metro
*/

class juego
{
public:

	// Funci�n que recorre todas las piezas y actualiza sus posiciones posibles
	void updatePosPosibles();

	// Funci�n que iimplementa un primer intento de movimento de piezas
	// TODO: Rehcaer la funci�n
	bool moverPieza(int x1, int y1, int x2, int y2);

private:

	// Vector que contiene todas las piezas del juego
	pieza** piezas;

	// Tablero que contiene la informaci�n de donde est� cada pieza para que se puedan comunicar
	// Se le pasa a cada pieza para actualizar sus posibles posiciones y se actualiza en cada movimiento
	Tablero tab;

};

void juego::updatePosPosibles()
{
	int dim_x = tab.dim_x;
	int dim_y = tab.dim_y;
	for (int i = 0; i < dim_x; i++)
	{
		for (int j = 0; j < dim_x; j++)
		{
			piezas[i][j].updatePosPosibles(tab);
		}
	}
}

bool juego::moverPieza(int x1, int y1, int x2, int y2)
{
	// Mueve una ficha a otra posici�n
	// Devuelve 0 si la posici�n es in
	if (tab.mat[x1][y1] == 0)
	{
		std::cout << "No hay ficha que mover" << std::endl;
		return 0;
	}
	piezas[x2][y2].destruir();

	piezas[x1][y1].moverPosicion(x2, y2);

	piezas[x1][y1].destruir();
}