#ifndef _GARDNER_H_
#define _GARDNER_H_

#include "mundo.h"
class Gardner : public Mundo
{

public:
	void inicializa() override {}
	void imprimirTablero() override;
private: 
	static const int TAMANO_TABLERO = 5;
};

#endif

