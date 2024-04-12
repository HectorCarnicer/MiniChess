#include <iostream>
#include <vector>
#include "../lib/Pieza.h"
#include "../lib/Peon.h"
#include "../lib/Rey.h"
#include "../lib/tablero.h"
#include "../lib/motor.h"

int main() {
    // Crear un vector para almacenar las piezas
    std::vector<Pieza*> piezas;

    // Agregar piezas al vector con su color correspondiente
    // Piezas blancas
    //piezas.push_back(new Torre(0, 0, BLANCO));
    //piezas.push_back(new Caballo(1, 0, BLANCO));
    //piezas.push_back(new Alfil(2, 0, BLANCO));
    //piezas.push_back(new Reina(3, 0, BLANCO));
    piezas.push_back(new Rey(4, 0, BLANCO));
    //piezas.push_back(new Alfil(5, 0, BLANCO));
    //piezas.push_back(new Caballo(6, 0, BLANCO));
    //piezas.push_back(new Torre(7, 0, BLANCO));
    for (int i = 0; i < 8; ++i) {
        piezas.push_back(new Peon(i, 1, BLANCO));
    }

    // Piezas negras
    //piezas.push_back(new Torre(0, 7, NEGRO));
    //piezas.push_back(new Caballo(1, 7, NEGRO));
    //piezas.push_back(new Alfil(2, 7, NEGRO));
    //piezas.push_back(new Reina(3, 7, NEGRO));
    piezas.push_back(new Rey(4, 7, NEGRO));
    //piezas.push_back(new Alfil(5, 7, NEGRO));
    //piezas.push_back(new Caballo(6, 7, NEGRO));
    //piezas.push_back(new Torre(7, 7, NEGRO));
    for (int i = 0; i < 8; ++i) {
        piezas.push_back(new Peon(i, 6, NEGRO));
    }


    // Variable para almacenar la elección del usuario y el turno actual
    int eleccion, nuevoX, nuevoY;
    Color turnoActual = BLANCO; // Comenzar con el turno de las piezas blancas

    while (true) {
        imprimirTablero(piezas);
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
            if (!posicionOcupada(piezas, nuevoX, nuevoY) && caminoLibre(piezas, piezaSeleccionada, nuevoX, nuevoY)) {
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

    // Limpiar el vector de piezas
    for (Pieza* pieza : piezas) {
        delete pieza;
    }
    piezas.clear();

    return 0;
}

    