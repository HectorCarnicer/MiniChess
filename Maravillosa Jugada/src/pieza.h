#ifndef PIEZA_H
#define PIEZA_H

#include <iostream>
#include <string>

// Enumeración para los colores de las piezas
enum Color { BLANCO, NEGRO };

class Pieza {
protected:
    int x, y; // Posición de la pieza en un tablero bidimensional
    Color color; // Color de la pieza
    static const int TAMANO_TABLERO = 8; // Tamaño del tablero

public:
    // Constructor que inicializa la posición de la pieza y el color
    Pieza(int posX, int posY, Color color) : x(posX), y(posY), color(color) {}

    // Método para mover la pieza a una nueva posición
    virtual bool mover(int nuevoX, int nuevoY) = 0;

    // Método para imprimir la posición actual de la pieza
    void mostrarPosicion();

    // Método virtual puro para obtener el nombre de la clase
    virtual std::string nombreDeClase() const = 0;

    // Método para obtener la posición de la pieza
    void obtenerPosicion(int& posX, int& posY) const {
        posX = x;
        posY = y;
    }

    // Método para obtener el color de la pieza
    Color obtenerColor() const;
    void moverPiezaUsuario();
};
#endif // PIEZA_H