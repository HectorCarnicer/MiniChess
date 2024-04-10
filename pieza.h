#ifndef PIEZA_H
#define PIEZA_H

#include <iostream>

class Pieza {
private:
    int x, y; // Posici�n de la pieza en un tablero bidimensional
    static const int TAMANO_TABLERO = 8; // Tama�o del tablero

public:
    // Constructor que inicializa la posici�n de la pieza
    Pieza(int posX, int posY);

    // M�todo para mover la pieza a una nueva posici�n
    void mover(int nuevoX, int nuevoY);

    // M�todo para imprimir la posici�n actual de la pieza
    void mostrarPosicion();

    // M�todo para mover la pieza con entrada del usuario
    void moverPiezaUsuario();
    virtual std::string nombreDeClase() const = 0;
    void obtenerPosicion(int& posX, int& posY) const {
        posX = x;
        posY = y;
    }
};
#endif // PIEZA_H