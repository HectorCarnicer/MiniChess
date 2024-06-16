#ifndef _CABALLO_CPP_
#define _CABALLO_CPP_
#include "./lib/piezas/caballo.h"
void Caballo::calcularPosPosibles(int** posActualesPiezas)
{
	// Actualiza pos_posibles del caballo
	// Iniciamos a 0 el tablero
	for (int i = 0; i < tam_x; i++)
	{
		for (int j = 0; j < tam_y; j++)
		{
			pos_posibles[i][j] = 0;
		}
	}

	// Movimientos que puede hacer un caballo
	int movimientospos[8][2] = { {2,1}, {2,-1}, {1,2}, {1,-2}, {-1,2}, {-1,-2}, {-2,1}, {-2,-1} };
	for (int i = 0; i < 8; i++) 
	{
		//Recorre las L del caballo posibles
		int nuevo_pos_x = pos.x + movimientospos[i][0];
		int nuevo_pos_y = pos.y + movimientospos[i][1];
		Coord nuevaCoord = { nuevo_pos_x, nuevo_pos_y };
		if (nuevaCoord.coordValid(tam_x, tam_y)) // Compruba que esté dentro del tablero
		{
			if (posActualesPiezas[nuevo_pos_x][nuevo_pos_y] == 0) // Caso de casilla vacía
			{
				pos_posibles[nuevo_pos_x][nuevo_pos_y] = 1; // La casilla es una posición posible
			}
			if (posActualesPiezas[nuevo_pos_x][nuevo_pos_y] == color) // Caso del mismo color
			{
				pos_posibles[nuevo_pos_x][nuevo_pos_y] = 0; // La casilla no es una posición posible
			}
			if (posActualesPiezas[nuevo_pos_x][nuevo_pos_y] == color_contrario) // Caso de color contrario
			{
				pos_posibles[i][pos.y] = 1; // La casilla es una posición posible (comiendo)
			}
		}
	}
}
#endif // !_CABALLO_CPP_
