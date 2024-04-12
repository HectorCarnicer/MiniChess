#ifndef REY_H
#define REY_H

#include "Pieza.h"

class Rey : public Pieza {
public:
    // Constructor que utiliza el constructor de la clase base Pieza
    Rey(int posX, int posY) : Pieza(posX, posY) {}

    // Puedes agregar métodos específicos de Rey aquí
    // Por ejemplo, un movimiento especial para el rey
    bool moverRey(int nuevoX, int nuevoY) {
        // Implementa las reglas de movimiento específicas del rey
        // Por ejemplo, solo permitir mover una casilla en cualquier dirección
        // Asegúrate de llamar al método mover de la clase base para la lógica común
        return true; // Retorna verdadero si el movimiento es válido
    }
    std::string nombreDeClase() const override {
        return "Rey";
    }
};
#endif // REY_H
