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
    // TODO: Añadir piezas que faltan

    // Creación de piezas blancas
    this->nuevaPieza(new Rey(2, 4, BLANCO, TAMANO_TABLERO));
    //for (int i = 0; i < TAMANO_TABLERO; ++i) {
    //   this->nuevaPieza(new Peon(i, 1, BLANCO, TAMANO_TABLERO));
    //}
    //// Creación de piezas negras
    this->nuevaPieza(new Rey(2, 0, NEGRO, TAMANO_TABLERO));
    //for (int i = 0; i < 5; ++i) {
    //    this->nuevaPieza(new Peon(i, 3, NEGRO, TAMANO_TABLERO));
    //}
    //this->nuevaPieza(new Alfil(1, 4, BLANCO, TAMANO_TABLERO));
    //this->nuevaPieza(new Reina(3, 2, BLANCO, TAMANO_TABLERO));
    //this->nuevaPieza(new Torre(3, 2, BLANCO, TAMANO_TABLERO));
    //this->nuevaPieza(new Reina(0, 0, BLANCO, TAMANO_TABLERO));
    this->nuevaPieza(new Peon(0, 4, BLANCO, TAMANO_TABLERO));
    this->nuevaPieza(new Caballo(1, 1, NEGRO, TAMANO_TABLERO));
    this->nuevaPieza(new Peon(0, 0, NEGRO, TAMANO_TABLERO));
    this->nuevaPieza(new Caballo(1, 3, BLANCO, TAMANO_TABLERO));


}

// Nueva Jugada
void Gardner::nuevaJugada(Color& turnoActual)
{
    int eleccion, nuevoX, nuevoY;
    // Mostrar las piezas y pedir al usuario que elija una
    if (detectarJaque(turnoActual)) {
        std::cout << "-----JACQUE AL REY " << (turnoActual == BLANCO ? "BLANCO" : "NEGRO")<< "-----\n";
    }

    std::cout << "Turno de " << (turnoActual == BLANCO ? "Blanco" : "Negro") << ". Seleccione una pieza para mover:\n";
    for (int i = 0; i < piezas.size(); ++i) {
        if (piezas[i]->obtenerColor() == turnoActual) {
            std::cout << i + 1 << ". " << piezas[i]->nombreDeClase() << " en posicion ";
            piezas[i]->mostrarPosicion();
        }
    }
    std::cin >> eleccion;

    // Verificar que la elección es válida y corresponde al color del turno
    if (eleccion > 0 && eleccion <= piezas.size() && piezas[eleccion - 1]->obtenerColor() == turnoActual) {
        Pieza* piezaSeleccionada = piezas[eleccion - 1];
        std::cout << "Ingrese la nueva posicion X (0 a 7): ";
        std::cin >> nuevoX;
        std::cout << "Ingrese la nueva posicion Y (0 a 7): ";
        std::cin >> nuevoY;

        // Verificar si la posición está ocupada antes de mover la pieza
       
        if (!posicionOcupada(nuevoX, nuevoY) && caminoLibre(piezaSeleccionada, nuevoX, nuevoY)) {
            if (piezaSeleccionada->mover(nuevoX, nuevoY)) {
                turnoActual = (turnoActual == BLANCO) ? NEGRO : BLANCO;
                system("cls");
            }
        }
        else if (atacarPieza(piezaSeleccionada->obtenerColor(), nuevoX, nuevoY)) {
            piezaSeleccionada->mover(nuevoX, nuevoY);
            turnoActual = (turnoActual == BLANCO) ? NEGRO : BLANCO;
            system("cls");
        }
        else {
            system("cls");
            std::cout << "-----Movimiento invalido o posicion ocupada-----\n";
        }
    }
    else {
        system("cls");
        std::cout << "Eleccion invalida o no es el turno de esa pieza.\n";
    }
}