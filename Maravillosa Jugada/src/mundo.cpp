#include "../lib/mundo.h"

// Funci�n para verificar si la posici�n est� ocupada por otra pieza
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

// Funci�n para "comer" la pieza en la posici�n dada
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

// Funci�n para verificar si el camino est� libre para el movimiento de la pieza
bool Mundo::caminoLibre(Pieza* pieza, int xFinal, int yFinal) {
    // Implementar la l�gica espec�fica para cada tipo de pieza
    // Por ejemplo, para un pe�n, solo necesitas verificar la casilla final
    // Para piezas como la torre, alfil o reina, necesitas verificar todas las casillas en el camino
    // ...

    return true; // Por defecto, asumimos que el camino est� libre
}

// Funci�n que genera una nueva jugada en consola
void Mundo::nuevaJugada(Color turnoActual)
{
    int eleccion, nuevoX, nuevoY;
    // Mostrar las piezas y pedir al usuario que elija una
    std::cout << "Turno de " << (turnoActual == BLANCO ? "Blanco" : "Negro") << ". Seleccione una pieza para mover:\n";
    for (int i = 0; i < piezas.size(); ++i) {
        if (piezas[i]->obtenerColor() == turnoActual) {
            std::cout << i + 1 << ". " << piezas[i]->nombreDeClase() << " en posici�n ";
            piezas[i]->mostrarPosicion();
        }
    }
    std::cin >> eleccion;

    // Verificar que la elecci�n es v�lida y corresponde al color del turno
    if (eleccion > 0 && eleccion <= piezas.size() && piezas[eleccion - 1]->obtenerColor() == turnoActual) {
        Pieza* piezaSeleccionada = piezas[eleccion - 1];
        std::cout << "Ingrese la nueva posici�n X (0 a 7): ";
        std::cin >> nuevoX;
        std::cout << "Ingrese la nueva posici�n Y (0 a 7): ";
        std::cin >> nuevoY;

        // Verificar si la posici�n est� ocupada antes de mover la pieza
        if (!posicionOcupada(nuevoX, nuevoY) && caminoLibre(piezaSeleccionada, nuevoX, nuevoY)) {
            if (piezaSeleccionada->mover(nuevoX, nuevoY)) {
                // Cambiar el turno si el movimiento es exitoso
                turnoActual = (turnoActual == BLANCO) ? NEGRO : BLANCO;
            }
        }
        else {
            std::cout << "Movimiento inv�lido o posici�n ocupada.\n";
        }
    }
    else {
        std::cout << "Elecci�n inv�lida o no es el turno de esa pieza.\n";
    }
}

void Mundo::imprimirTablero()
{
    // Crear un tablero vac�o
    std::string tablero[8][8];
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            tablero[i][j] = ".";
        }
    }

    // Colocar las iniciales de las piezas en el tablero
    for (const auto& pieza : piezas) {
        int x, y;
        pieza->obtenerPosicion(x, y); // Asumiendo que tienes un m�todo para obtener la posici�n
        tablero[y][x] = pieza->nombreDeClase().substr(0, 1); // Usa la primera letra del nombre de la clase
    }

    // Imprimir el tablero
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            std::cout << tablero[i][j] << " ";
        }
        std::cout << std::endl;
    }
}