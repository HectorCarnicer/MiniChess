#ifndef _GARDNER_H_
#define _GARDNER_H_

#include "../lib/rey.h"
#include "../lib/pieza.h"
#include "../lib/peon.h"

#include "mundo.h"
class Gardner : public Mundo
{

public:
	Gardner(std::vector<Pieza*>& piezas) : Mundo(piezas) {}
	~Gardner();
	void inicializa() override;
	void imprimirTablero() override;
	//bool caminoLibre(Pieza* pieza, int xFinal, int yFinal);
	int getTam() { return TAMANO_TABLERO; }
private: 
	static const int TAMANO_TABLERO = 5;
};

#endif

