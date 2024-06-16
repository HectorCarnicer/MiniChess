#ifndef _BABY_CPP_
#define _BABY_CPP_

#include "../lib/baby.h"
#include "../lib/piezas/peon.h"
#include "../lib/piezas/rey.h"


// Destructor de objetos Gardner
Baby::~Baby()
{
    for (Pieza* pieza : piezas) {
        delete pieza;
    }
    piezas.clear();
}

// Impresor del tablero Gardner
void Baby::imprimirTablero()
{
    // Crear un tablero vacío
    for (int i = 0; i < tam_x; ++i) {
        for (int j = 0; j < tam_y; ++j) {
            tab_imp[i][j] = ".";
        }
    }

    // Colocar las iniciales de las piezas en el tablero
    Coord aux = { 0,0 };
    for (const auto& pieza : piezas) {
        aux = pieza->obtenerPosicion(); // Asumiendo que tienes un método para obtener la posición
        tab_imp[aux.x][aux.y] = pieza->obtenerNomClase().substr(0, 1); // Usa la primera letra del nombre de la clase
    }

    // Imprimir el tablero
    for (int i = 0; i < tam_x; ++i) {
        for (int j = 0; j < tam_y; ++j) {
            std::cout << tab_imp[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Inicializador del tablero Gardner
void Baby::inicializa()
{
    // Creación de piezas blancas
    this->nuevaPieza(new Rey({ 4, 4 }, BLANCO, tam_x, tam_y));
    this->nuevaPieza(new Reina({ 3, 4 }, BLANCO, tam_x, tam_y));
    this->nuevaPieza(new Alfil({ 2, 4 }, BLANCO, tam_x, tam_y));
    this->nuevaPieza(new Caballo({ 1, 4 }, BLANCO, tam_x, tam_y));
    this->nuevaPieza(new Torre({ 0, 4 }, BLANCO, tam_x, tam_y));
    for (int i = 0; i < tam_x; ++i) {
        this->nuevaPieza(new Peon({ i, 3 }, BLANCO, tam_x, tam_y));
    }

    // Creación de piezas negras
    this->nuevaPieza(new Rey({ 0, 0 }, NEGRO, tam_x, tam_y));
    this->nuevaPieza(new Reina({ 1, 0 }, NEGRO, tam_x, tam_y));
    this->nuevaPieza(new Alfil({ 2, 0 }, NEGRO, tam_x, tam_y));
    this->nuevaPieza(new Caballo({ 3, 0 }, NEGRO, tam_x, tam_y));
    this->nuevaPieza(new Torre({ 4, 0 }, NEGRO, tam_x, tam_y));
    for (int i = 0; i < tam_x; i++) {
        this->nuevaPieza(new Peon({ i, 1 }, NEGRO, tam_x, tam_y));
    }

}
#endif