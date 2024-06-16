
#ifndef _REY_H
#define _REY_H

#include "Pieza.h"

class Rey : public Pieza {
public:
    // Constructor que utiliza el constructor de la clase base Pieza
    Rey(Coord pos, Color color, int tam_x, int tam_y) : Pieza(pos, color, REY, tam_x, tam_y) {}

    // Método para calcular las posiciones a las que se puede mover un peón
    void calcularPosPosibles(int** posActualesPiezas) override;
};


#endif // REY_H

