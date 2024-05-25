
#ifndef CABALLO_H
#define CABALLO_H

#include "pieza.h"
#include "mundo.h"


class Caballo : public Pieza
{
public:

    Caballo(int posX, int posY, Color color, int TAM_TAB) : Pieza(posX, posY, color, TAM_TAB) {}

    bool mover(int nuevoX, int nuevoY) override {

        return false;
    }


    std::string nombreDeClase() const override {
        return "Caballo";
    }
};



#endif
