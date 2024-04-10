#ifndef PEON_H
#define PEON_H

#include "Pieza.h"

class Peon : public Pieza {
public:
    // Constructor que utiliza el constructor de la clase base Pieza
    Peon(int posX, int posY) : Pieza(posX, posY) {}

    // Puedes agregar m�todos espec�ficos de Peon aqu�
    // Por ejemplo, un movimiento especial para el pe�n
    bool moverPeon(int nuevoX, int nuevoY) {
        // Implementa las reglas de movimiento espec�ficas del pe�n
        // Por ejemplo, solo permitir mover hacia adelante y capturar en diagonal
        // Aseg�rate de llamar al m�todo mover de la clase base para la l�gica com�n
        return true; // Retorna verdadero si el movimiento es v�lido
    }
    std::string nombreDeClase() const override {
        return "Peon";
    }
};

#endif // PEON_H