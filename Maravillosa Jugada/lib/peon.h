#ifndef PEON_H
#define PEON_H

#include "Pieza.h"
#include "Gardner.h"

class Peon : public Pieza {
public:
    // Constructor que utiliza el constructor de la clase base Pieza
    Peon(int posX, int posY, Color color, int TAM_TAB) : Pieza(posX, posY, color, TAM_TAB) {}
    // Método para mover el peón con validación de movimiento
    bool mover(int nuevoX, int nuevoY) override {
        // El peón solo puede moverse hacia adelante una casilla
        // y capturar en diagonal una casilla
        int deltaX = nuevoX - x;
        int deltaY = nuevoY - y;

        // Mover hacia adelante
        if (color == BLANCO && deltaY == -1 && deltaX == 0) {
            return Pieza::mover(nuevoX, nuevoY);
        }
        else if (color == NEGRO && deltaY == 1 && deltaX == 0) {
            return Pieza::mover(nuevoX, nuevoY);
        }


        // Capturar en diagonal

        if ((color == BLANCO && deltaY == -1 && abs(deltaX) == 1) ||
            (color == NEGRO && deltaY == 1 && abs(deltaX) == 1)) {
            return Pieza::mover(nuevoX, nuevoY);
        }
        system("cls");
        // Si no es ninguno de los movimientos válidos, retorna falso
        return false;
    }

    std::string nombreDeClase() const override {
        return "Peon";
    }
};

#endif // PEON_H
