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
    gardner.inicializa();
    //Primer turno es blanco
    Color turnoActual = BLANCO; // Comenzar con el turno de las piezas blancas

    // Bucle que genera nuevas jugadas
    while (true) {
        gardner.imprimirTablero();
        gardner.nuevaJugada(turnoActual);
    }
    return 0;
}

    