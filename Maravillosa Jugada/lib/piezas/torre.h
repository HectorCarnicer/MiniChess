
#ifndef TORRE_H
#define TORRE_H

#include "pieza.h"


class Torre : public Pieza
{
public:

    // Constructor que utiliza el constructor de la clase base Pieza
    Torre(Coord pos, Color color, int tam_x, int tam_y) : Pieza(pos, color, TORRE, tam_x, tam_y) {}

    // Método para calcular las posiciones a las que se puede mover una torre
    void calcularPosPosibles(int** posActualesPiezas) override;
};



#endif
