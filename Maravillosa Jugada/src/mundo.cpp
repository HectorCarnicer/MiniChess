#include "../lib/mundo.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>



// Función para "comer" la pieza en la posición dada
void Mundo::comerPieza(const Coord pos) 
{
	for (auto it = piezas.begin(); it != piezas.end(); ) {
		Coord pos_pieza = (*it)->obtenerPosicion();
		if (pos_pieza == pos) {
			delete* it; // Liberar la memoria de la pieza comida
			it = piezas.erase(it); // Eliminar la pieza del vector y actualizar el iterador
		}
		else {
			it++; // Mover al siguiente elemento si no hay coincidencia
		}
	}
	// Si no hay ninguna pieza en pos, no hace nada
}

// Función que implementa la promoción de un peon
void Mundo::promocion() 
{
	// Recorre todas las piezas
	for (auto p : piezas)
	{
		if (p->obtenerClase() == PEON)
		{
			if (p->obtenerPosicion().y == 0 || p->obtenerPosicion().y == tam_y - 1)
			{
				// Si existe un peon en un limite del tablero
				// Eliminar el peon
				comerPieza(p->obtenerPosicion());
				// Añadir una reina con los mismos parámetros 
				Reina nueva_reina{ p->obtenerPosicion(), p->obtenerColor(), tam_x, tam_y };
				nuevaPieza(&nueva_reina);
			}
		}
	}
}

// Función que detecta si el rey de col_actual está en jaque
bool Mundo::detectarJaque(const Color col_actual)
{
	// Devuelve 1 si hay jaque al rey col_actual, si no 0
	bool jaque = 0;
	Coord pos_rey = { 0,0 };

	// Recorre todas las piezas y obtiene la posición del rey
	for (auto p : piezas)
	{
		// Si es de color distinto ignorar la pieza
		if (p->obtenerColor() != col_actual) continue;
		// Obtener la posicion del color col_actual
		if (p->obtenerClase() == REY) pos_rey = p->obtenerPosicion();
	}
	for (auto p : piezas)
	{
		// Si es del mismo color ignorar la pieza
		if (p->obtenerColor() == col_actual) continue;
		// Si cualquier pieza del otro color puede moverse donde el rey, hay jaque
		jaque = jaque || p->posPosible(pos_rey);
	}
	return jaque;
}

// Función para actualizar las pos_actuales
void Mundo::actualizarPosActuales()
{
	// Variable de coordenadas auxiliar
	Coord aux = { 0,0 };
	// Limpiar pos_actuales
	for (int i = 0; i < tam_x; i++)
	{
		for (int j = 0; j < tam_y; j++)
		{
			pos_actuales[i][j] = 0;
		}
	}
	// Establecer pos_actuales
	for (auto p : piezas)
	{
		aux = p->obtenerPosicion();
		pos_actuales[aux.x][aux.y] = p->obtenerColor();
	}
}

// Función de una nueva jugada, intenta mover una pieza a una nueva posición
bool Mundo::nuevaJugada(Pieza* piezaSeleccionada, Coord pos)
{
	// Devuelve si el movimiento por parte de la pieza ha sido correcto

	bool mov_correcto = piezaSeleccionada->mover(pos);
	// Si se ha conseguido mover a la posición indicada
	if (mov_correcto == true)
	{
		// Recorre las piezas y comete la que esté en esa posición
		comerPieza(pos);
	}
	else std::cout << "Movimiento invalido: " << *piezaSeleccionada << std::endl;

	// Actualiza las posiciones actuales tras el movimiento
	actualizarPosActuales();
	// Actualiza las matrices de pos_posibles de las piezas
	actualizarPosPosibles();

	return mov_correcto;
}

// Función que actualiza las pos_posibles de las piezas
void Mundo::actualizarPosPosibles()
{
	for (auto p : piezas)
	{
		p->calcularPosPosibles(pos_actuales);
	}
}
