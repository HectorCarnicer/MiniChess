#include "../lib/mundo.h"

// Función para verificar si la posición está ocupada por otra pieza
bool Mundo::posicionOcupada(int x, int y) {
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
void Mundo::comerPieza(int x, int y) {
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
bool Mundo::caminoLibre(Pieza* pieza, int xFinal, int yFinal) {
    // Implementar la lógica específica para cada tipo de pieza
    // Por ejemplo, para un peón, solo necesitas verificar la casilla final
    // Para piezas como la torre, alfil o reina, necesitas verificar todas las casillas en el camino
    // ...

    return true; // Por defecto, asumimos que el camino está libre
}

void Mundo::nuevaJugada(Color turnoActual)
{
    int eleccion, nuevoX, nuevoY;
    // Mostrar las piezas y pedir al usuario que elija una
    std::cout << "Turno de " << (turnoActual == BLANCO ? "Blanco" : "Negro") << ". Seleccione una pieza para mover:\n";
    for (int i = 0; i < piezas.size(); ++i) {
        if (piezas[i]->obtenerColor() == turnoActual) {
            std::cout << i + 1 << ". " << piezas[i]->nombreDeClase() << " en posición ";
            piezas[i]->mostrarPosicion();
        }
    }
    std::cin >> eleccion;

    // Verificar que la elección es válida y corresponde al color del turno
    if (eleccion > 0 && eleccion <= piezas.size() && piezas[eleccion - 1]->obtenerColor() == turnoActual) {
        Pieza* piezaSeleccionada = piezas[eleccion - 1];
        std::cout << "Ingrese la nueva posición X (0 a 7): ";
        std::cin >> nuevoX;
        std::cout << "Ingrese la nueva posición Y (0 a 7): ";
        std::cin >> nuevoY;

        // Verificar si la posición está ocupada antes de mover la pieza
        if (!posicionOcupada(nuevoX, nuevoY) && caminoLibre(piezaSeleccionada, nuevoX, nuevoY)) {
            if (piezaSeleccionada->mover(nuevoX, nuevoY)) {
                // Cambiar el turno si el movimiento es exitoso
                turnoActual = (turnoActual == BLANCO) ? NEGRO : BLANCO;
            }
        }
        else {
            std::cout << "Movimiento inválido o posición ocupada.\n";
        }
    }
    else {
        std::cout << "Elección inválida o no es el turno de esa pieza.\n";
    }
}
