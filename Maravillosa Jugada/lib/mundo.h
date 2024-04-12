#ifndef MUNDO_H
#define MUNDO_H

#include <vector>
#include "pieza.h"

class Mundo
{
public:
	// Constructor

	bool posicionOcupada(int x, int y);
	void comerPieza(std::vector<Pieza*>& piezas, int x, int y);
	bool caminoLibre(Pieza* pieza, int xFinal, int yFinal);
	virtual void inicializa();
	void dibuja();
private:
	std::vector<Pieza*>& piezas;
};

#endif MUNDO_H
