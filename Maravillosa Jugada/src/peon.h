#ifndef PEON_H
#define PEON_H

#include "Pieza.h"

class Peon : public Pieza {
public:
    // Constructor que utiliza el constructor de la clase base Pieza
    Peon(int posX, int posY, Color color) : Pieza(posX, posY, color) {}

    // M�todo para mover el pe�n con validaci�n de movimiento
    bool mover(int nuevoX, int nuevoY) override {
        // El pe�n solo puede moverse hacia adelante una casilla
        // y capturar en diagonal una casilla
        int deltaX = nuevoX - x;
        int deltaY = nuevoY - y;

        // Mover hacia adelante
        if (color == BLANCO && deltaY == 1 && deltaX == 0) {
            return Pieza::mover(nuevoX, nuevoY);
        }
        else if (color == NEGRO && deltaY == -1 && deltaX == 0) {
            return Pieza::mover(nuevoX, nuevoY);
        }

        // Capturar en diagonal
        if ((color == BLANCO && deltaY == 1 && abs(deltaX) == 1) ||
            (color == NEGRO && deltaY == -1 && abs(deltaX) == 1)) {
            // Aqu� deber�as verificar si hay una pieza enemiga en la nueva posici�n
            // Si es as�, puedes capturar
            return Pieza::mover(nuevoX, nuevoY);
        }

        // Si no es ninguno de los movimientos v�lidos, retorna falso
        return false;
    }

    std::string nombreDeClase() const override {
        return "Peon";
    }
};

#endif // PEON_H
