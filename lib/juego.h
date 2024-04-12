#include "Piezas/pieza.h"
#include <iostream>

/*
La idea de esta clase es que contiene el vector de fichas que consituyen el juego y el tablero con la
información de sus posiciones
*/

class juego
{
public:

	juego();

	// Funci�n que recorre todas las piezas y actualiza sus posiciones posibles
	void updatePosJuego();

	// Nueva jugada: 1 si se termina el juego, 0 si continua
	bool nuevaJugada();
	// llamará a updatePosJuego y después moverPieza

	// Funci�n que iimplementa un primer intento de movimento de piezas
	// TODO: Rehcaer la funci�n
	bool moverPieza(int x1, int y1, int x2, int y2);

private:

	// Vector que contiene todas las piezas del juego
	pieza** piezas;

	// Tablero que contiene la informaci�n de donde est� cada pieza para que se puedan comunicar
	// Se le pasa a cada pieza para actualizar sus posibles posiciones y se actualiza en cada movimiento
	Tablero tab;

	bool jugador;

};

void juego::updatePosJuego()
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
	// La comprobación se hace con bool** posiciones_validas de la pieza

	if (tab.mat[x1][y1] == 0 || (jugador && (tab.mat[x1][y1] < 0) ) || (!jugador && (tab.mat[x1][y1] > 0)))
	{
		std::cout << "No hay pieza que mover" << std::endl;
	}
	
	// Cambiamos la posición interna de la pieza
	bool valido = piezas[x1][y1].moverPosicion(x2, y2);

	// Actualizamos el tablero numérico
	tab.mat[x2][y2] = tab.mat[x1][y1];
	tab.mat[x1][y1] = 0;
	

	// La pieza en la matriz que estaba en x2, y2 pasa a ser la pieza que estaba en x1, y1
	piezas[x2][y2] = piezas[x1][y1];
	
	
	// Hacemos pos inicial vacía
	piezas[x1][y1].destruir();
	
	
	return valido;
}

bool juego::nuevaJugada()
{
	/*
	* 
	* Pide coordenadas al jugadar
	* Llamará a updatePosJuego
	* Llamará a moverPieza con las coords
	std::cin << 
	*/
}
