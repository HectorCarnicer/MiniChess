#ifndef PIEZA_H
#define PIEZA_H

#include <iostream>
#include <string>

// Enumeraci�n para los colores de las piezas
enum Color { BLANCO, NEGRO };

class Pieza {
protected:
    int x, y; // Posici�n de la pieza en un tablero bidimensional
    Color color; // Color de la pieza
    static const int TAMANO_TABLERO = 8; // Tama�o del tablero

public:
    // Constructor que inicializa la posici�n de la pieza y el color
    Pieza(int posX, int posY, Color color) : x(posX), y(posY), color(color) {}

    // M�todo para mover la pieza a una nueva posici�n
    virtual bool mover(int nuevoX, int nuevoY) = 0;

    // M�todo para imprimir la posici�n actual de la pieza
    void mostrarPosicion();

    // M�todo virtual puro para obtener el nombre de la clase
    virtual std::string nombreDeClase() const = 0;

    // M�todo para obtener la posici�n de la pieza
    void obtenerPosicion(int& posX, int& posY) const {
        posX = x;
        posY = y;
    }

    // M�todo para obtener el color de la pieza
    Color obtenerColor() const;
    void moverPiezaUsuario();
};
#endif // PIEZA_H