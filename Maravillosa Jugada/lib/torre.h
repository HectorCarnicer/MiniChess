
#ifndef TORRE_H
#define TORRE_H

#include "pieza.h"
#include "mundo.h"


class Torre : public Pieza
{
public:

    Torre(int posX, int posY, Color color, int TAM_TAB) : Pieza(posX, posY, color, TAM_TAB) {}

    bool mover(int nuevoX, int nuevoY) override {

        for (int i = x; i < 5; i++) {
            if (i == nuevoX && y==nuevoY)
                return Pieza::mover(i, y);
        }

        for (int j = y; j < 5; j++) {
            if (j == nuevoY && x==nuevoX)
                return Pieza::mover(x, j);
        }

        for (int i = x; i >= 0; i--) {
            if (i == nuevoX && y == nuevoY)
                return Pieza::mover(i, y);
        }

        for (int j = y; j >=0 ; j--) {
            if (j == nuevoY && x==nuevoX)
                return Pieza::mover(x, j);
        }
        system("cls");

        return false;
    }


    std::string nombreDeClase() const override {
        return "Torre";
    }
};



#endif
