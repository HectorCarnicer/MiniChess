#include "Piezas/pieza.h"
#include "tablero.h"
#include <iostream>

// La idea de esta clase es que contiene el vector de fichas que consituyen el juego
// 
// De este modo, no hay conflicto con los #include: todas las clases obtienen información de tablero.h
// y la usan como parámetro

class juego
{
public:
	void updatePosPosibles();
	bool moverPieza(int x1, int y1, int x2, int y2);
	void crearPiezas();
private:
	pieza** piezas;
	Tablero tab;
};

void juego::updatePosPosibles()
{
	int dim_x = tab.mat.dim_x;
	int dim_y = tab.mat.dim_y;
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
	// Mueve una ficah a otra posición
	// Devuelve 0 si la posición es in
	if (tab.mat.mat[x1][y1] == 0)
	{
		std:cout << "No hay ficha que mover" << std::endl;
		return 0;
	}
	piezas[x2][y2].destruir();

	piezas[x1][y1].moverPosicion(x2, y2);

	piezas[x1][y1].destruir();
}