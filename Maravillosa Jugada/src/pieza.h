#ifndef PIEZA_H
#define PIEZA_H

#include <iostream>

class Pieza {
private:
    int x, y; // Posición de la pieza en un tablero bidimensional
    static const int TAMANO_TABLERO = 8; // Tamaño del tablero

public:
    // Constructor que inicializa la posición de la pieza
    Pieza(int posX, int posY);

    // Método para mover la pieza a una nueva posición
    void mover(int nuevoX, int nuevoY);

    // Método para imprimir la posición actual de la pieza
    void mostrarPosicion();

    // Método para mover la pieza con entrada del usuario
    void moverPiezaUsuario();
    virtual std::string nombreDeClase() const = 0;
    void obtenerPosicion(int& posX, int& posY) const {
        posX = x;
        posY = y;
    }
};
#endif // PIEZA_H