#ifndef PEON_H
#define PEON_H

#include "Pieza.h"

class Peon : public Pieza {
public:
    // Constructor que utiliza el constructor de la clase base Pieza
    Peon(int posX, int posY) : Pieza(posX, posY) {}

    // Puedes agregar métodos específicos de Peon aquí
    // Por ejemplo, un movimiento especial para el peón
    bool moverPeon(int nuevoX, int nuevoY) {
        // Implementa las reglas de movimiento específicas del peón
        // Por ejemplo, solo permitir mover hacia adelante y capturar en diagonal
        // Asegúrate de llamar al método mover de la clase base para la lógica común
        return true; // Retorna verdadero si el movimiento es válido
    }
    std::string nombreDeClase() const override {
        return "Peon";
    }
};

#endif // PEON_H