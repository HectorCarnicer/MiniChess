 
#ifndef ALFIL_H
#define ALFIL_H

#include "pieza.h"
#include "mundo.h"


class Alfil : public Pieza
{
public:

	Alfil(int posX, int posY, Color color, int TAM_TAB) : Pieza(posX, posY, color, TAM_TAB) {}

    bool mover(int nuevoX, int nuevoY) override {

        for (int i = x, j = y; i < 5 && j < 5; i++, j++) {
            if(i==nuevoX && j==nuevoY)
            return Pieza::mover(i, j);
        }

        for (int i = x + 1, j = y - 1; i < 5 && j >= 0; i++, j--) {
            if (i == nuevoX && j == nuevoY)
            return Pieza::mover(i, j);
        }

        for (int i = x - 1, j = y + 1; i >= 0 && j < 5; i--, j++) {
            if (i == nuevoX && j == nuevoY)
            return Pieza::mover(i, j);
        }

        for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--) {
            if (i == nuevoX && j == nuevoY)
            return Pieza::mover(i, j);
        }
        return false;
    }


    std::string nombreDeClase() const override {
        return "Alfil";
    }
};



#endif
