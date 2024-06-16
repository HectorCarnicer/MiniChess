#include <iostream>
#include "../lib/piezas/Pieza.h"



// Implementación del método mover de Pieza
bool Pieza::mover(Coord nueva_pos) {
    if (nueva_pos.coordValid(tam_x, tam_y)) {
        if (pos_posibles[nueva_pos.x, nueva_pos.y])
        {
            this->pos = nueva_pos;
            return true;
        }
        else
        {
            std::cout << "Movimiento invalido: la posicion no esta en pos_posibles" << std::endl;
            return false;
        }
    }
    else {
        system("cls");
        std::cout << "Movimiento invalido: la pieza debe permanecer dentro del tablero." << std::endl;
        return false;
    }
}

// Función para mover la pieza con entrada del usuario
void Pieza::moverPiezaUsuario() {}

