#include <iostream>
#include <vector>
#include "Pieza.h"
#include "Peon.h"
#include "Rey.h"
#include "tablero.h"
int main() {
    // Crear un vector para almacenar las piezas
    std::vector<Pieza*> piezas;

    // Agregar piezas al vector
    piezas.push_back(new Peon(0, 1));
    piezas.push_back(new Peon(1, 1));
    piezas.push_back(new Rey(4, 0));
    // ... agregar más piezas según sea necesario

    // Variable para almacenar la elección del usuario
    int eleccion;
    imprimirTablero(piezas);
    // Mostrar las piezas y pedir al usuario que elija una
    std::cout << "Seleccione una pieza para mover:\n";
    for (int i = 0; i < piezas.size(); ++i) {
        std::cout << i + 1 << ". " << piezas[i]->nombreDeClase() << " en posición ";
        piezas[i]->mostrarPosicion();
    }
    std::cin >> eleccion;

    // Verificar que la elección es válida
    if (eleccion > 0 && eleccion <= piezas.size()) {
        // Mover la pieza elegida
        piezas[eleccion - 1]->moverPiezaUsuario();
    }
    else {
        std::cout << "Elección inválida.\n";
    }

    // Limpiar el vector de piezas
    for (Pieza* pieza : piezas) {
        delete pieza;
    }
    piezas.clear();

    return 0;
}