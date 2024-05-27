
#/*ifndef REINA_H
#define REINA_h

#include "pieza.h"
#include "mundo.h"


class Reina : public Pieza
{
public:

    Reina(int posX, int posY, Color color, int TAM_TAB) : Pieza(posX, posY, color, TAM_TAB) {}

    bool mover(int nuevoX, int nuevoY) override {

      
        for (int i = x; i < 5; i++) {
            if (i == nuevoX && y == nuevoY)
                return Pieza::mover(i, y);
        }

        for (int j = y; j < 5; j++) {
            if (j == nuevoY && x == nuevoX)
                return Pieza::mover(x, j);
        }

        for (int i = x; i >= 0; i--) {
            if (i == nuevoX && y == nuevoY)
                return Pieza::mover(i, y);
        }

        for (int j = y; j >= 0; j--) {
            if (j == nuevoY && x == nuevoX)
                return Pieza::mover(x, j);
        }

        for (int i = x, j = y; i < 5 && j < 5; i++, j++) {
            if (i == nuevoX && j == nuevoY)
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
        return "Reina";
    }
};



#endif*/
