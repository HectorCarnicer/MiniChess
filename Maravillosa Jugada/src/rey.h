#ifndef REY_H
#define REY_H

#include "Pieza.h"

class Rey : public Pieza {
public:
    // Constructor que utiliza el constructor de la clase base Pieza
    Rey(int posX, int posY) : Pieza(posX, posY) {}

    // Puedes agregar m�todos espec�ficos de Rey aqu�
    // Por ejemplo, un movimiento especial para el rey
    bool moverRey(int nuevoX, int nuevoY) {
        // Implementa las reglas de movimiento espec�ficas del rey
        // Por ejemplo, solo permitir mover una casilla en cualquier direcci�n
        // Aseg�rate de llamar al m�todo mover de la clase base para la l�gica com�n
        return true; // Retorna verdadero si el movimiento es v�lido
    }
    std::string nombreDeClase() const override {
        return "Rey";
    }
};
#endif // REY_H
