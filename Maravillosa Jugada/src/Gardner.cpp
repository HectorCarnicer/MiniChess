#include "../lib/gardner.h"

// Destructor de objetos Gardner
Gardner::~Gardner()
{
    for (Pieza* pieza : piezas) {
        delete pieza;
    }
    piezas.clear();
}
// Impresor del tablero Gardner
void Gardner::imprimirTablero()
{
    // Crear un tablero vacío
    std::string tablero[TAMANO_TABLERO][TAMANO_TABLERO];
    for (int i = 0; i < TAMANO_TABLERO; ++i) {
        for (int j = 0; j < TAMANO_TABLERO; ++j) {
            tablero[i][j] = ".";
        }
    }

    // Colocar las iniciales de las piezas en el tablero
    for (const auto& pieza : piezas) {
        int x, y;
        pieza->obtenerPosicion(x, y); // Asumiendo que tienes un método para obtener la posición
        tablero[y][x] = pieza->nombreDeClase().substr(0, 1); // Usa la primera letra del nombre de la clase
    }

    // Imprimir el tablero
    for (int i = 0; i < TAMANO_TABLERO; ++i) {
        for (int j = 0; j < TAMANO_TABLERO; ++j) {
            std::cout << tablero[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
// Inicializador del tablero Gardner
void Gardner::inicializa()
{
    // Creación de piezas blancas
    this->nuevaPieza(new Rey(2, 4, BLANCO));
    for (int i = 0; i < TAMANO_TABLERO; ++i) {
        this->nuevaPieza(new Peon(i, 1, BLANCO));
    }
    // Creación de piezas negras
    this->nuevaPieza(new Rey(2, 0, NEGRO));
    for (int i = 0; i < 5; ++i) {
        this->nuevaPieza(new Peon(i, 3, NEGRO));
    }
}