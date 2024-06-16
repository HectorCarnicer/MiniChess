#ifndef _REINA_CPP_
#define _REINA_CPP_
#include "./lib/piezas/reina.h"


void Reina::calcularPosPosibles(int** posActualesPiezas)
{
	// Actualiza pos_posibles de la reina
	// Iniciamos a 0 el tablero
	for (int i = 0; i < tam_x; i++)
	{
		for (int j = 0; j < tam_y; j++)
		{
			pos_posibles[i][j] = 0;
		}
	}

	/*
	* En torre, alfil y reina no es necesario comprobar que las posciones de los bucles
	* est�n dentro de los l�mites, ya que los l�mites del tablero ya est�n impuestos en
	* los propios bucles
	*/

	/*
	* LINEAS RECTAS
	*/

	/*
	* EJE X
	*/
	bool aux_linea_x = 1; // Indica si se ha colisionado con una pieza antes
	for (int i = pos.x + 1; i < tam_x; i++)
	{
		if (aux_linea_x == 0) break; // Si ya se ha colisionado, dejar las casillas restantes no accesibles
		if (posActualesPiezas[i][pos.y] == 0) // Caso de casilla vac�a
		{
			pos_posibles[i][pos.y] = 1; // La casilla es una posici�n posible
		}
		if (posActualesPiezas[i][pos.y] == color)
		{
			pos_posibles[i][pos.y] = 0; // La casilla no es una posici�n posible
			aux_linea_x = 0; // No continuar con las dem�s: colisi�n
		}
		if (posActualesPiezas[i][pos.y] == color_contrario)
		{
			pos_posibles[i][pos.y] = 1; // La casilla es una posici�n posible (comiendo)
			aux_linea_x = 0; // No continuar con las dem�s: colisi�n
		}
	}
	aux_linea_x = 1; // Reseteo de variable auxiliar
	for (int i = pos.x - 1; i >= 0; i--)
	{
		if (aux_linea_x == 0) break; // Si ya se ha colisionado, dejar las casillas restantes no accesibles
		if (posActualesPiezas[i][pos.y] == 0) // Caso de casilla vac�a
		{
			pos_posibles[i][pos.y] = 1; // La casilla es una posici�n posible
		}
		if (posActualesPiezas[i][pos.y] == color)
		{
			pos_posibles[i][pos.y] = 0; // La casilla no es una posici�n posible
			aux_linea_x = 0; // No continuar con las dem�s: colisi�n
		}
		if (posActualesPiezas[i][pos.y] == color_contrario)
		{
			pos_posibles[i][pos.y] = 1; // La casilla es una posici�n posible (comiendo)
			aux_linea_x = 0; // No continuar con las dem�s: colisi�n
		}
	}

	/*
	* EJE Y
	*/
	bool aux_linea_y = 1; // Indica si se ha colisionado con una pieza antes
	for (int i = pos.y + 1; i < tam_y; i++)
	{
		if (aux_linea_x == 0) break; // Si ya se ha colisionado, dejar las casillas restantes no accesibles
		if (posActualesPiezas[pos.x][i] == 0) // Caso de casilla vac�a
		{
			pos_posibles[pos.x][i] = 1; // La casilla es una posici�n posible
		}
		if (posActualesPiezas[pos.x][i] == color)
		{
			pos_posibles[i][pos.y] = 0; // La casilla no es una posici�n posible
			aux_linea_x = 0; // No continuar con las dem�s: colisi�n
		}
		if (posActualesPiezas[pos.x][i] == color_contrario)
		{
			pos_posibles[pos.x][i] = 1; // La casilla es una posici�n posible (comiendo)
			aux_linea_x = 0; // No continuar con las dem�s: colisi�n
		}
	}
	aux_linea_y = 1; // Reseteo de variable auxiliar
	for (int i = pos.y - 1; i >= 0; i--)
	{
		if (aux_linea_x == 0) break; // Si ya se ha colisionado, dejar las casillas restantes no accesibles
		if (posActualesPiezas[pos.x][i] == 0) // Caso de casilla vac�a
		{
			pos_posibles[pos.x][i] = 1; // La casilla es una posici�n posible
		}
		if (posActualesPiezas[pos.x][i] == color)
		{
			pos_posibles[pos.x][i] = 0; // La casilla no es una posici�n posible
			aux_linea_x = 0; // No continuar con las dem�s: colisi�n
		}
		if (posActualesPiezas[pos.x][i] == color_contrario)
		{
			pos_posibles[pos.x][i] = 1; // La casilla es una posici�n posible (comiendo)
			aux_linea_x = 0; // No continuar con las dem�s: colisi�n
		}
	}

	/*
	* DIAGONALES
	*/

	/*
	* EJE +X+Y
	*/
	bool aux_lineas = 1; // Variable auxiliar para la colisi�n
	for (int i = pos.x + 1, j = pos.y + 1; i < tam_x && j < tam_y; i++, j++)
	{
		if (aux_lineas == 0) break; // Si ya se ha colisionado, dejar las casillas restantes no accesibles
		if (posActualesPiezas[i][j] == 0) // Caso de casilla vac�a
		{
			pos_posibles[i][j] = 1; // La casilla es una posici�n posible
		}
		if (posActualesPiezas[i][j] == color)
		{
			pos_posibles[i][j] = 0; // La casilla no es una posici�n posible
			aux_lineas = 0; // No continuar con las dem�s: colisi�n
		}
		if (posActualesPiezas[i][j] == color_contrario)
		{
			pos_posibles[i][j] = 1; // La casilla es una posici�n posible (comiendo)
			aux_lineas = 0; // No continuar con las dem�s: colisi�n
		}
	}
	/*
	* EJE +X-Y
	*/
	aux_lineas = 1;
	for (int i = pos.x + 1, j = pos.y - 1; i < 5 && j >= 0; i++, j--)
	{
		if (aux_lineas == 0) break; // Si ya se ha colisionado, dejar las casillas restantes no accesibles
		if (posActualesPiezas[i][j] == 0) // Caso de casilla vac�a
		{
			pos_posibles[i][j] = 1; // La casilla es una posici�n posible
		}
		if (posActualesPiezas[i][j] == color)
		{
			pos_posibles[i][j] = 0; // La casilla no es una posici�n posible
			aux_lineas = 0; // No continuar con las dem�s: colisi�n
		}
		if (posActualesPiezas[i][j] == color_contrario)
		{
			pos_posibles[i][j] = 1; // La casilla es una posici�n posible (comiendo)
			aux_lineas = 0; // No continuar con las dem�s: colisi�n
		}
	}
	/*
	* EJE +X-Y
	*/
	aux_lineas = 1;
	for (int i = pos.x - 1, j = pos.y + 1; i >= 0 && j < 5; i--, j++)
	{
		if (aux_lineas == 0) break; // Si ya se ha colisionado, dejar las casillas restantes no accesibles
		if (posActualesPiezas[i][j] == 0) // Caso de casilla vac�a
		{
			pos_posibles[i][j] = 1; // La casilla es una posici�n posible
		}
		if (posActualesPiezas[i][j] = color)
		{
			pos_posibles[i][j] = 0; // La casilla no es una posici�n posible
			aux_lineas = 0; // No continuar con las dem�s: colisi�n
		}
		if (posActualesPiezas[i][j] == color_contrario)
		{
			pos_posibles[i][j] = 1; // La casilla es una posici�n posible (comiendo)
			aux_lineas = 0; // No continuar con las dem�s: colisi�n
		}
	}
	/*
	* EJE -X-Y
	*/
	aux_lineas = 1;
	for (int i = pos.x - 1, j = pos.y - 1; i >= 0 && j >= 0; i--, j--)
	{
		if (aux_lineas == 0) break; // Si ya se ha colisionado, dejar las casillas restantes no accesibles
		if (posActualesPiezas[i][j] == 0) // Caso de casilla vac�a
		{
			pos_posibles[i][j] = 1; // La casilla es una posici�n posible
		}
		if (posActualesPiezas[i][j] = color)
		{
			pos_posibles[i][j] = 0; // La casilla no es una posici�n posible
			aux_lineas = 0; // No continuar con las dem�s: colisi�n
		}
		if (posActualesPiezas[i][j] == color_contrario)
		{
			pos_posibles[i][j] = 1; // La casilla es una posici�n posible (comiendo)
			aux_lineas = 0; // No continuar con las dem�s: colisi�n
		}
	}
}
#endif