// tablero.cpp

#include "../lib/tablero.h"
#include <iostream>
#include <vector>
#include <iomanip>

// Implementación de la función imprimirTablero
void imprimirTablero(const std::vector<Pieza*>& piezas) {
    // Crear un tablero vacío
    std::string tablero[8][8];
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
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
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            std::cout << tablero[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
