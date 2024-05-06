
#ifndef REY_H
#define REY_H

#include "Pieza.h"

class Rey : public Pieza {
public:
    // Constructor que utiliza el constructor de la clase base Pieza
    Rey(int posX, int posY, Color color, int TAM_TAB) : Pieza(posX, posY, color, TAM_TAB) {}

    // M�todo para mover el rey con validaci�n de movimiento
    bool mover(int nuevoX, int nuevoY) override {
        // El rey solo puede moverse una casilla en cualquier direcci�n
        int deltaX = nuevoX - x;
        int deltaY = nuevoY - y;

        // Validar movimiento del rey
        if (abs(deltaX) <= 1 && abs(deltaY) <= 1) {
            // Aqu� deber�as verificar si la nueva posici�n est� amenazada por otra pieza
            // Si no est� amenazada, puedes mover
            return Pieza::mover(nuevoX, nuevoY);
        }

        // Si no es un movimiento v�lido, retorna falso
        return false;
    }

    std::string nombreDeClase() const override {
        return "Rey";
    }
};


#endif // REY_H

