
#ifndef _REINA_H_
#define _REINA_H_

#include "pieza.h"



class Reina : public Pieza
{
public:

    // Constructor que utiliza el constructor de la clase base Pieza
    Reina(Coord pos, Color color, int tam_x, int tam_y) : Pieza(pos, color, REINA, tam_x, tam_y) {}

    // Método para calcular las posiciones a las que se puede mover una reina
    void calcularPosPosibles(int** posActualesPiezas) override;
};



#endif
