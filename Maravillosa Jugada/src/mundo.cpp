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
bool Mundo::caminoLibre(Pieza* pieza, int x, int y) {
    // Implementar la l�gica espec�fica para cada tipo de pieza
    // Por ejemplo, para un pe�n, solo necesitas verificar la casilla final
    // Para piezas como la torre, alfil o reina, necesitas verificar todas las casillas en el camino
    // ...

    if (pieza->nombreDeClase() == "Peon") {

    }
    if (pieza->nombreDeClase() == "Alfil") {

    }
    if (pieza->nombreDeClase() == "Rey") {

    }
    if (pieza->nombreDeClase() == "Reina") {

    }
    if (pieza->nombreDeClase() == "Torre") {

    }
    if (pieza->nombreDeClase() == "Caballo") {

    }
    return true; // Por defecto, asumimos que el camino est� libre
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
