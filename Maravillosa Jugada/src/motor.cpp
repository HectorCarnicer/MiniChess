#include "motor.h"

// Función para verificar si la posición está ocupada por otra pieza
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

// Función para "comer" la pieza en la posición dada
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
// Función para verificar si el camino está libre para el movimiento de la pieza
bool caminoLibre(const std::vector<Pieza*>& piezas, Pieza* pieza, int xFinal, int yFinal) {
    // Implementar la lógica específica para cada tipo de pieza
    // Por ejemplo, para un peón, solo necesitas verificar la casilla final
    // Para piezas como la torre, alfil o reina, necesitas verificar todas las casillas en el camino
    // ...

    return true; // Por defecto, asumimos que el camino está libre
}
