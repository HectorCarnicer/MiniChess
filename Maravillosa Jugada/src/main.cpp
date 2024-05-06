#include <iostream>
#include <vector>
#include "../lib/Pieza.h"
#include "../lib/Peon.h"
#include "../lib/Rey.h"
#include "../lib/gardner.h"
#include "../lib/gardner.h"

int main() {
    // Crear un vector para almacenar las pieza

    std::vector<Pieza*> piezas;
    Gardner gardner(piezas);

    // Agregar piezas al vector con su color correspondiente
    // Piezas blancas
    //piezas.push_back(new Torre(0, 0, BLANCO));
    //piezas.push_back(new Caballo(1, 0, BLANCO));
    //piezas.push_back(new Alfil(2, 0, BLANCO));
    //piezas.push_back(new Reina(3, 0, BLANCO));
    gardner.nuevaPieza(new Rey(2, 4, BLANCO));
    //piezas.push_back(new Alfil(5, 0, BLANCO));
    //piezas.push_back(new Caballo(6, 0, BLANCO));
    //piezas.push_back(new Torre(7, 0, BLANCO));
    for (int i = 0; i < 5; ++i) {
        gardner.nuevaPieza(new Peon(i, 1, BLANCO));
    }

    // Piezas negras
    //piezas.push_back(new Torre(0, 7, NEGRO));
    //piezas.push_back(new Caballo(1, 7, NEGRO));
    //piezas.push_back(new Alfil(2, 7, NEGRO));
    //piezas.push_back(new Reina(3, 7, NEGRO));
    gardner.nuevaPieza(new Rey(2, 0, NEGRO));
    //piezas.push_back(new Alfil(5, 7, NEGRO));
    //piezas.push_back(new Caballo(6, 7, NEGRO));
    //piezas.push_back(new Torre(7, 7, NEGRO));
    for (int i = 0; i < 5; ++i) {
       gardner.nuevaPieza(new Peon(i, 3, NEGRO));
    }


    //Primer turno es blanco
    Color turnoActual = BLANCO; // Comenzar con el turno de las piezas blancas

    // Bucle que genera nuevas jugadas
    while (true) {
        gardner.imprimirTablero();
        gardner.nuevaJugada(turnoActual);
    }

    // Limpiar el vector de piezas
    for (Pieza* pieza : piezas) {
        delete pieza;
    }
    piezas.clear();

    return 0;
}

    