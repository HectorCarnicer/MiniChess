
#ifndef _CABALLO_H_
#define _CABALLO_H_

#include "pieza.h"


class Caballo : public Pieza
{
public:

	// Constructor que utiliza el constructor de la clase base Pieza
	Caballo(Coord pos, Color color, int tam_x, int tam_y) : Pieza(pos, color, CABALLO, tam_x, tam_y) {}

	// Método para calcular las posiciones a las que se puede mover una torre
	void calcularPosPosibles(int** posActualesPiezas) override;
};



#endif
