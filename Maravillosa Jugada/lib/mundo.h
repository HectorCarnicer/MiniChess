#ifndef _MUNDO_H
#define _MUNDO_H

#include <vector>
#include <algorithm>
#include "./piezas/pieza.h"
#include "./piezas/reina.h"

// Interfaz del mundo, de ella heredan los distintos modos de juego
class Mundo {
public:

	// Constructor
	Mundo(std::vector<Pieza*>& piezas,int tam_x, int tam_y) : piezas(piezas), 
		tam_x(tam_x), tam_y(tam_y)
	{
		// Iniciar el tablero de posiciones actuales
		pos_actuales = new int* [tam_x];
		for (int i = 0; i < tam_x; i++)
		{
			pos_actuales[i] = new int[tam_y];
		}
		// Inicializar el tablero de strings para impresión
		tab_imp = new std::string * [tam_x];
		for (int i = 0; i < tam_x; i++)
		{
			tab_imp[i] = new std::string[tam_y];
		}
	}
	
	// Destructor
	virtual ~Mundo()
	{
		for (auto p : piezas)
		{
			delete p;
		}
		piezas.clear();
	}

	// Función que comienza una nueva jugada
	bool nuevaJugada(Pieza* piezaSeleccionada, Coord pos);

	// Función que come una pieza
	void comerPieza(const Coord pos);

	// Función que añade una pieza (push_back)
	void nuevaPieza(Pieza* p) { piezas.push_back(p); }

	// Función que detecta si hay alguna pieza que pueda comer al rey
	bool detectarJaque(const Color col_actual); 

	// Función que implementa la promoción de un peon
	void promocion();

	// Función que actualiza las posiciones actuales
	void actualizarPosActuales(); 

	// Función que actualiza las posiciones posibles de cada pieza
	void actualizarPosPosibles();


	// Función que inicializa el tablero y sus piezas dependiendo del tipo de juego
	virtual void inicializa() = 0;
	virtual void imprimirTablero() = 0;

	// Getters de tamaño de tablero
	int getTamX() { return tam_x; }
	int getTamY() { return tam_y; }

protected:

    // Vector que contiene las piezas
    std::vector<Pieza*>& piezas;

	/*
	* Matriz que contiene información de las casillas que están ocupadas y cual es el color de estas casillas
	* No contiene información de una pieza determinada. Se pasa a cada pieza para que puedan saber qué tienen
	* a su alrededor para poder saber a qué posiciones se pueden mover.
	*/
	int** pos_actuales;

	// Tamaño del tablero
	int tam_x, tam_y;

	// Tablero de strings para imprimir en consola
	std::string** tab_imp;

};

#endif // MUNDO_H