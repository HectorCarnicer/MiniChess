#include <iostream>
#include <vector>
#include "../lib/Pieza.h"
#include "../lib/Peon.h"
#include "../lib/Rey.h"
#include "../lib/tablero.h"
#include "../lib/mundo.h"

int main() {
    // Crear un vector para almacenar las pieza

    std::vector<Pieza*> piezas;
    Mundo mundo(piezas);

    // Agregar piezas al vector con su color correspondiente
    // Piezas blancas
    //piezas.push_back(new Torre(0, 0, BLANCO));
    //piezas.push_back(new Caballo(1, 0, BLANCO));
    //piezas.push_back(new Alfil(2, 0, BLANCO));
    //piezas.push_back(new Reina(3, 0, BLANCO));
    mundo.piezas.push_back(new Rey(4, 0, BLANCO));
    //piezas.push_back(new Alfil(5, 0, BLANCO));
    //piezas.push_back(new Caballo(6, 0, BLANCO));
    //piezas.push_back(new Torre(7, 0, BLANCO));
    for (int i = 0; i < 8; ++i) {
        mundo.piezas.push_back(new Peon(i, 1, BLANCO));
    }

    // Piezas negras
    //piezas.push_back(new Torre(0, 7, NEGRO));
    //piezas.push_back(new Caballo(1, 7, NEGRO));
    //piezas.push_back(new Alfil(2, 7, NEGRO));
    //piezas.push_back(new Reina(3, 7, NEGRO));
    mundo.piezas.push_back(new Rey(4, 7, NEGRO));
    //piezas.push_back(new Alfil(5, 7, NEGRO));
    //piezas.push_back(new Caballo(6, 7, NEGRO));
    //piezas.push_back(new Torre(7, 7, NEGRO));
    for (int i = 0; i < 8; ++i) {
       mundo.piezas.push_back(new Peon(i, 6, NEGRO));
    }


    //Primer turno es blanco
    Color turnoActual = BLANCO; // Comenzar con el turno de las piezas blancas

    while (true) {
        imprimirTablero(mundo.piezas);
        mundo.nuevaJugada(turnoActual);
    }

    // Limpiar el vector de piezas
    for (Pieza* pieza : piezas) {
        delete pieza;
    }
    piezas.clear();

    return 0;
}

    