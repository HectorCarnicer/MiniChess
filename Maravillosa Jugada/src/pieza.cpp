#include <iostream>
#include "Pieza.h"

// Asumiendo que el tama�o del tablero es 8x8
const int TAMANO_TABLERO = 8;


// Implementaci�n del m�todo mover de Pieza
bool Pieza::mover(int nuevoX, int nuevoY) {
    if (nuevoX >= 0 && nuevoX < TAMANO_TABLERO && nuevoY >= 0 && nuevoY < TAMANO_TABLERO) {
        x = nuevoX;
        y = nuevoY;
        return true;
    }
    else {
        std::cout << "Movimiento inv�lido: la pieza debe permanecer dentro del tablero." << std::endl;
        return false;
    }
}

// Implementaci�n del m�todo mostrarPosicion de Pieza
void Pieza::mostrarPosicion() {
    std::cout << "Posici�n actual: (" << x << ", " << y << ")" << std::endl;
}

// Funci�n para mover la pieza con entrada del usuario
void Pieza::moverPiezaUsuario() {
    int nuevoX, nuevoY;
    std::cout << "Ingrese la nueva posici�n X (0 a " << TAMANO_TABLERO - 1 << "): ";
    std::cin >> nuevoX;
    std::cout << "Ingrese la nueva posici�n Y (0 a " << TAMANO_TABLERO - 1 << "): ";
    std::cin >> nuevoY;

    if (!mover(nuevoX, nuevoY)) {
        std::cout << "Movimiento no realizado. Intente de nuevo." << std::endl;
    }
}

// M�todo para obtener el color de la pieza
Color Pieza::obtenerColor() const {
    return color;
}
