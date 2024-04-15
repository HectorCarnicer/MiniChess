#ifndef MUNDO_H
#define MUNDO_H

#include <vector>
#include "pieza.h"

class Mundo
{
public:
	// Constructor
	Mundo(std::vector<Pieza*>& piezas) : piezas(piezas){}

	bool posicionOcupada(int x, int y);
	void comerPieza(int x, int y);
	bool caminoLibre(Pieza* pieza, int xFinal, int yFinal);
	// virtual void inicializa();
	void imprimirTablero();
	void nuevaJugada(Color turnoActual);
	std::vector<Pieza*>& piezas;
};

#endif MUNDO_H
