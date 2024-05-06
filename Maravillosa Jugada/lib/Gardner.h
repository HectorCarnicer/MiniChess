#ifndef _GARDNER_H_
#define _GARDNER_H_

#include "mundo.h"
class Gardner : public Mundo
{

public:
	Gardner(std::vector<Pieza*>& piezas) : Mundo(piezas) {}
	void inicializa() override {}
	void imprimirTablero() override;
	//bool caminoLibre(Pieza* pieza, int xFinal, int yFinal);
	int getTam() { return TAMANO_TABLERO; }
private: 
	static const int TAMANO_TABLERO = 5;
};

#endif

