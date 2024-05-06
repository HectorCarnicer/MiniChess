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
	//virtual void inicializa();
	virtual void imprimirTablero();
	void nuevaJugada(Color turnoActual);
	void nuevaPieza(Pieza* p);
	std::vector<Pieza*>& piezas;
private:
	const int TAMANO_TABLERO = 8;
};

#endif MUNDO_H
