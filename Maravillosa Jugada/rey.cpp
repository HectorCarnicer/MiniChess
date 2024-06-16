#ifndef _REY_CPP_
#define _REY_CPP_
#include "./lib/piezas/rey.h"

void Rey::calcularPosPosibles(int** posActualesPiezas)
{
	// Actualiza pos_posibles del rey
	// Iniciamos a 0 el tablero
	for (int i = 0; i < tam_x; i++)
	{
		for (int j = 0; j < tam_y; j++)
		{
			pos_posibles[i][j] = 0;
		}
	}
	// Bucle alrededor del rey
	for (int i = pos.x - 1, j = pos.y - 1; i <= pos.x + 1 && j <= pos.y + 1; i++, j++)
	{
		Coord _pos = { i,j };
		if (_pos == pos) continue; // Obviar posición propia del rey
		if (posActualesPiezas[i][j] == 0) // Caso de casilla vacía
		{
			pos_posibles[i][j] = 1; // La casilla es una posición posible
		}
		if (posActualesPiezas[i][pos.y] == color) // Caso mismo color
		{
			pos_posibles[i][j] = 0; // La casilla no es una posición posible
		}
		if (posActualesPiezas[i][j] == color_contrario) // Caso color contrario
		{
			pos_posibles[i][j] = 1; // La casilla es una posición posible (comiendo)
		}
	}
}
#endif