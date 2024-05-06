#ifndef MUNDO_H
#define MUNDO_H

#include <vector>
#include "pieza.h"

// Interfaz del mundo, de ella heredan los distintos modos de juego
class Mundo
{
public:
	// Constructor
	Mundo(std::vector<Pieza*>& piezas) : piezas(piezas){}

	bool posicionOcupada(int x, int y);
	void comerPieza(int x, int y);
	void nuevaJugada(Color turnoActual);
	void nuevaPieza(Pieza* p) { piezas.push_back(p); }

	// Métodos que se sobrescriben aguas abajo
	virtual bool caminoLibre(Pieza* pieza, int xFinal, int yFinal);
	virtual void inicializa() = 0;
	virtual void imprimirTablero() = 0;
	virtual int getTam() = 0;
	std::vector<Pieza*>& piezas;
};

#endif MUNDO_H
