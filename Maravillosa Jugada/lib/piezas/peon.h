#ifndef PEON_H
#define PEON_H

#include "Pieza.h"

class Peon : public Pieza {
public:
    // Constructor que utiliza el constructor de la clase base Pieza
    Peon(Coord pos, Color color, int tam_x, int tam_y) : Pieza(pos, color, PEON, tam_x, tam_y) {}

    // Método para calcular las posiciones a las que se puede mover un peón
    void calcularPosPosibles(int** posActualesPiezas) override;
};

#endif // PEON_H
