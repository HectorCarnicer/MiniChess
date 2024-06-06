
#ifndef reina_h
#define reina_h

#include "pieza.h"
#include "mundo.h"


class Reina : public Pieza
{
public:

    Reina(int posx, int posy, Color color, int tam_tab) : Pieza(posx, posy, color, tam_tab) {}

    bool mover(int nuevox, int nuevoy) override {

      
        for (int i = x; i < 5; i++) {
            if (i == nuevox && y == nuevoy)
                return Pieza::mover(i, y);
        }

        for (int j = y; j < 5; j++) {
            if (j == nuevoy && x == nuevox)
                return Pieza::mover(x, j);
        }

        for (int i = x; i >= 0; i--) {
            if (i == nuevox && y == nuevoy)
                return Pieza::mover(i, y);
        }

        for (int j = y; j >= 0; j--) {
            if (j == nuevoy && x == nuevox)
                return Pieza::mover(x, j);
        }

        for (int i = x, j = y; i < 5 && j < 5; i++, j++) {
            if (i == nuevox && j == nuevoy)
                return Pieza::mover(i, j);
        }

        for (int i = x + 1, j = y - 1; i < 5 && j >= 0; i++, j--) {
            if (i == nuevox && j == nuevoy)
                return Pieza::mover(i, j);
        }

        for (int i = x - 1, j = y + 1; i >= 0 && j < 5; i--, j++) {
            if (i == nuevox && j == nuevoy)
                return Pieza::mover(i, j);
        }

        for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--) {
            if (i == nuevox && j == nuevoy)
                return Pieza::mover(i, j);
        }
        system("cls");

        return false;
    }

    std::string nombreDeClase() const override {
        return "Reina";
    }
};



#endif
