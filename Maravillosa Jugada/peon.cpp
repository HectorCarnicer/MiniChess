#ifndef _PEON_CPP_
#define _PEON_CPP_

#include "./lib/piezas/peon.h"
void Peon::calcularPosPosibles(int** posActualesPiezas)
{
	// Actualiza pos_posibles del peon
	// Iniciamos a 0 el tablero
	for (int i = 0; i < tam_x; i++)
	{
		for (int j = 0; j < tam_y; j++)
		{
			pos_posibles[i][j] = 0;
		}
	}
	if (color == BLANCO) // Si el color es blanco, se mueve hacia arriba
	{
		// Si la posición de delante está vacía, se puede mover
		if (posActualesPiezas[pos.x][pos.y + 1] == 0) pos_posibles[pos.x][pos.y + 1] = 1;
		// Si las diagonales tienen enemigos, se puede mover
		if (posActualesPiezas[pos.x + 1][pos.y + 1] == color_contrario) pos_posibles[pos.x + 1][pos.y + 1] = 1;
		if (posActualesPiezas[pos.x - 1][pos.y + 1] == color_contrario) pos_posibles[pos.x - 1][pos.y + 1] = 1;
	}
	if (color == NEGRO) // Si el color es negro, se mueve ahacia abajo
	{
		// Si la posición de delante está vacía, se puede mover
		if (posActualesPiezas[pos.x][pos.y - 1] == 0) pos_posibles[pos.x][pos.y + 1] = 1;
		// Si las diagonales tienen enemigos, se puede mover
		if (posActualesPiezas[pos.x + 1][pos.y - 1] == color_contrario) pos_posibles[pos.x + 1][pos.y - 1] = 1;
		if (posActualesPiezas[pos.x - 1][pos.y - 1] == color_contrario) pos_posibles[pos.x - 1][pos.y - 1] = 1;
	}
}
#endif 