 
#ifndef ALFIL_H
#define ALFIL_H

#include "pieza.h"


class Alfil : public Pieza
{
public:

	Alfil(int posX, int posY, Color color, int TAM_TAB) : Pieza(posX, posY, color, TAM_TAB) {}

    bool  mover(int x, int y) override {
        // Recorre el tablero en las diagonales
        for (int i = x + 1, j = y + 1; i < 8 && j < 8; i++, j++) {
            return Pieza::mover(i, j);
        }

        for (int i = x + 1, j = y - 1; i < 8 && j >= 0; i++, j--) {
            return Pieza::mover(i, j);

        }

        for (int i = x - 1, j = y + 1; i >= 0 && j < 8; i--, j++) {
            return Pieza::mover(i, j);

        }

        for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--) {
            return Pieza::mover(i, j);

        }


        return false;
    }


    std::string nombreDeClase() const override {
        return "Alfil";
    }
};



#endif
