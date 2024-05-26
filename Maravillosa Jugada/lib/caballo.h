
#ifndef CABALLO_H
#define CABALLO_H

#include "pieza.h"
#include "mundo.h"


class Caballo : public Pieza
{
public:

    Caballo(int posX, int posY, Color color, int TAM_TAB) : Pieza(posX, posY, color, TAM_TAB) {}

    bool mover(int nuevoX, int nuevoY) override {
        int movimientospos[8][2] = { {2,1}, {2,-1}, {1,2}, {1,-2}
                                    ,{-1,2}, {-1,-2}, {-2,1}, {-2,-1} };

		for (int i = 0; i < 8; i++) {
			//recorre las L del caballo posibles
			int posposiblex = x + movimientospos[i][0];
			int posposibley = y + movimientospos[i][1];

            if (posposiblex == nuevoX && posposibley == nuevoY) {
                return Pieza::mover(posposiblex, posposibley);
            }
		}
        return false;
    }


    std::string nombreDeClase() const override {
        return "Caballo";
    }
};



#endif
