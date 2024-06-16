 
#ifndef _ALFIL_H_
#define _ALFIL_H_

#include "pieza.h"

class Alfil : public Pieza
{
public:

    // Constructor que utiliza el constructor de la clase base Pieza
    Alfil(Coord pos, Color color, int tam_x, int tam_y) : Pieza(pos, color, ALFIL, tam_x, tam_y) {}

    // Método para calcular las posiciones a las que se puede mover un alfil
    void calcularPosPosibles(int** posActualesPiezas) override;
};

#endif
