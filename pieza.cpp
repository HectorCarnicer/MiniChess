#include <iostream>
#include "Pieza.h"

// Asumiendo que el tamaño del tablero es 8x8
const int TAMANO_TABLERO = 8;

// Implementación del constructor de Pieza
Pieza::Pieza(int posX, int posY) : x(posX), y(posY) {}

// Implementación del método mover de Pieza
void Pieza::mover(int nuevoX, int nuevoY) {
    if (nuevoX >= 0 && nuevoX < TAMANO_TABLERO && nuevoY >= 0 && nuevoY < TAMANO_TABLERO) {
        x = nuevoX;
        y = nuevoY;
    }
    else {
        std::cout << "Movimiento inválido: la pieza debe permanecer dentro del tablero." << std::endl;
    }
}

// Implementación del método mostrarPosicion de Pieza
void Pieza::mostrarPosicion() {
    std::cout << "Posición actual: (" << x << ", " << y << ")" << std::endl;
}

// Función para mover la pieza con entrada del usuario
void Pieza::moverPiezaUsuario() {
    int nuevoX, nuevoY;
    std::cout << "Ingrese la nueva posición X (0 a " << TAMANO_TABLERO - 1 << "): ";
    std::cin >> nuevoX;
    std::cout << "Ingrese la nueva posición Y (0 a " << TAMANO_TABLERO - 1 << "): ";
    std::cin >> nuevoY;

    mover(nuevoX, nuevoY);
}
