#include "motor.h"

// Funci�n para verificar si la posici�n est� ocupada por otra pieza
bool posicionOcupada(const std::vector<Pieza*>& piezas, int x, int y) {
    for (const auto& pieza : piezas) {
        int posX, posY;
        pieza->obtenerPosicion(posX, posY);
        if (posX == x && posY == y) {
            return true;
        }
    }
    return false;
}

// Funci�n para "comer" la pieza en la posici�n dada
void comerPieza(std::vector<Pieza*>& piezas, int x, int y) {
    for (auto it = piezas.begin(); it != piezas.end(); ) {
        int posX, posY;
        (*it)->obtenerPosicion(posX, posY);
        if (posX == x && posY == y) {
            delete* it; // Liberar la memoria de la pieza comida
            it = piezas.erase(it); // Eliminar la pieza del vector y actualizar el iterador
        }
        else {
            ++it; // Mover al siguiente elemento si no hay coincidencia
        }
    }
}
// Funci�n para verificar si el camino est� libre para el movimiento de la pieza
bool caminoLibre(const std::vector<Pieza*>& piezas, Pieza* pieza, int xFinal, int yFinal) {
    // Implementar la l�gica espec�fica para cada tipo de pieza
    // Por ejemplo, para un pe�n, solo necesitas verificar la casilla final
    // Para piezas como la torre, alfil o reina, necesitas verificar todas las casillas en el camino
    // ...

    return true; // Por defecto, asumimos que el camino est� libre
}
