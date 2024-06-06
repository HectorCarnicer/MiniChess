#include "../lib/mundo.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Función para verificar si la posición está ocupada por otra pieza
bool Mundo::posicionOcupada(int x, int y) {
    if (!this) return false;
    for (const auto& pieza : piezas) {
        if (!pieza) continue;
        int posX, posY;
        pieza->obtenerPosicion(posX, posY);
        if (posX == x && posY == y) {
            return true;
        }
    }
    return false;
}

// Función para atacar una pieza enemiga en una posición dada
bool Mundo::atacarPieza(Color color, int x, int y) {
    if (!this) return false;
    for (const auto& pieza : piezas) {
        if (!pieza) continue;
        int posX, posY;
        pieza->obtenerPosicion(posX, posY);
        int color2 = pieza->obtenerColor();
        if (posX == x && posY == y && color2 != color) {
            comerPieza(x, y);
            return true;
        }
    }
    return false;
}

// Función para "comer" la pieza en la posición dada
void Mundo::comerPieza(int x, int y) {
    if (!this) return;
    for (auto it = piezas.begin(); it != piezas.end(); ) {
        if (!(*it)) {
            it = piezas.erase(it);
            continue;
        }
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

// Función para detectar si el rey está en jaque
bool Mundo::detectarJaque(Color& turnoActual) {
    if (!this) return false;
    int posReyX = 0, posReyY = 0;
    for (const auto& pieza : piezas) {
        if (!pieza) continue;
        if (pieza->obtenerColor() == turnoActual && pieza->nombreDeClase() == "Rey") {
            pieza->obtenerPosicion(posReyX, posReyY);
            break;
        }
    }
    for (const auto& pieza : piezas) {
        if (!pieza) continue;
        if (pieza->obtenerColor() != turnoActual) {
            if (!caminoLibre(pieza, posReyX, posReyY)) {
                return true;
            }
        }
    }
    return false;
}

// Función para verificar si el camino está libre para el movimiento de la pieza
bool Mundo::caminoLibre(Pieza* pieza, int nuevoX, int nuevoY) {
    if (!this || !pieza) return false;
    std::string nombre = pieza->nombreDeClase();
    if (nombre == "Peon") {
        return true;
    }
    else if (nombre == "Alfil") {
        int x, y;
        pieza->obtenerPosicion(x, y);
        if (nuevoX > x && nuevoY > y) {
            for (int i = x + 1, j = y + 1; i <= nuevoX && j <= nuevoY; ++i, ++j) {
                if (posicionOcupada(i, j)) return false;
            }
        }
        else if (nuevoX < x && nuevoY > y) {
            for (int i = x - 1, j = y + 1; i >= nuevoX && j <= nuevoY; --i, ++j) {
                if (posicionOcupada(i, j)) return false;
            }
        }
        else if (nuevoX > x && nuevoY < y) {
            for (int i = x + 1, j = y - 1; i <= nuevoX && j >= nuevoY; ++i, --j) {
                if (posicionOcupada(i, j)) return false;
            }
        }
        else if (nuevoX < x && nuevoY < y) {
            for (int i = x - 1, j = y - 1; i >= nuevoX && j >= nuevoY; --i, --j) {
                if (posicionOcupada(i, j)) return false;
            }
        }
        return true;
    }
    else if (nombre == "Rey") {
        int x, y;
        pieza->obtenerPosicion(x, y);
        int deltaX = nuevoX - x;
        int deltaY = nuevoY - y;
        if (abs(deltaX) <= 1 && abs(deltaY) <= 1) {
            if (posicionOcupada(nuevoX, nuevoY)) return false;
        }
        return true;
    }
    else if (nombre == "Reina") {
        int x, y;
        pieza->obtenerPosicion(x, y);
        if (nuevoX > x) {
            for (int i = x + 1; i <= nuevoX; ++i) {
                if (posicionOcupada(i, y)) return false;
            }
        }
        else if (nuevoX < x) {
            for (int i = x - 1; i >= nuevoX; --i) {
                if (posicionOcupada(i, y)) return false;
            }
        }
        else if (nuevoY > y) {
            for (int j = y + 1; j <= nuevoY; ++j) {
                if (posicionOcupada(x, j)) return false;
            }
        }
        else if (nuevoY < y) {
            for (int j = y - 1; j >= nuevoY; --j) {
                if (posicionOcupada(x, j)) return false;
            }
        }
        else if (nuevoX > x && nuevoY > y) {
            for (int i = x + 1, j = y + 1; i <= nuevoX && j <= nuevoY; ++i, ++j) {
                if (posicionOcupada(i, j)) return false;
            }
        }
        else if (nuevoX < x && nuevoY > y) {
            for (int i = x - 1, j = y + 1; i >= nuevoX && j <= nuevoY; --i, ++j) {
                if (posicionOcupada(i, j)) return false;
            }
        }
        else if (nuevoX > x && nuevoY < y) {
            for (int i = x + 1, j = y - 1; i <= nuevoX && j >= nuevoY; ++i, --j) {
                if (posicionOcupada(i, j)) return false;
            }
        }
        else if (nuevoX < x && nuevoY < y) {
            for (int i = x - 1, j = y - 1; i >= nuevoX && j >= nuevoY; --i, --j) {
                if (posicionOcupada(i, j)) return false;
            }
        }
        return true;
    }
    else if (nombre == "Torre") {
        int x, y;
        pieza->obtenerPosicion(x, y);
        if (nuevoX > x) {
            for (int i = x + 1; i <= nuevoX; ++i) {
                if (posicionOcupada(i, y)) return false;
            }
        }
        else if (nuevoX < x) {
            for (int i = x - 1; i >= nuevoX; --i) {
                if (posicionOcupada(i, y)) return false;
            }
        }
        else if (nuevoY > y) {
            for (int j = y + 1; j <= nuevoY; ++j) {
                if (posicionOcupada(x, j)) return false;
            }
        }
        else if (nuevoY < y) {
            for (int j = y - 1; j >= nuevoY; --j) {
                if (posicionOcupada(x, j)) return false;
            }
        }
        return true;
    }
    else if (nombre == "Caballo") {
        int x, y;
        pieza->obtenerPosicion(x, y);
        int movimientosPos[8][2] = { {2, 1}, {2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {-2, 1}, {-2, -1} };
        for (int i = 0; i < 8; ++i) {
            int posPosibleX = x + movimientosPos[i][0];
            int posPosibleY = y + movimientosPos[i][1];
            if (posPosibleX == nuevoX && posPosibleY == nuevoY) {
                if (posicionOcupada(posPosibleX, posPosibleY)) return false;
            }
        }
    }
    return true;
}

// Función para imprimir el tablero
void Mundo::imprimirTablero() {
    if (!this) return;
    std::string tablero[8][8];
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            tablero[i][j] = ".";
        }
    }
    for (const auto& pieza : piezas) {
        if (!pieza) continue;
        int x, y;
        pieza->obtenerPosicion(x, y);
        tablero[y][x] = pieza->nombreDeClase().substr(0, 1);
    }
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            std::cout << tablero[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Función de IA para realizar un movimiento aleatorio
void Mundo::realizarMovimientoIA(Color colorIA) {
    if (!this) return;
    std::srand(std::time(nullptr));
    std::vector<Pieza*> piezasIA;
    for (auto& pieza : piezas) {
        if (pieza && pieza->obtenerColor() == colorIA) {
            piezasIA.push_back(pieza);
        }
    }
    if (piezasIA.empty()) return;

    Pieza* piezaSeleccionada = piezasIA[std::rand() % piezasIA.size()];
    if (!piezaSeleccionada) return;

    int x, y;
    piezaSeleccionada->obtenerPosicion(x, y);

    std::vector<std::pair<int, int>> movimientos = {
        {x + 1, y}, {x - 1, y}, {x, y + 1}, {x, y - 1},
        {x + 1, y + 1}, {x - 1, y + 1}, {x + 1, y - 1}, {x - 1, y - 1}
    };

    std::pair<int, int> movimientoSeleccionado = movimientos[std::rand() % movimientos.size()];
    int nuevoX = movimientoSeleccionado.first;
    int nuevoY = movimientoSeleccionado.second;

    if (nuevoX >= 0 && nuevoX < 8 && nuevoY >= 0 && nuevoY < 8 && caminoLibre(piezaSeleccionada, nuevoX, nuevoY)) {
        if (atacarPieza(colorIA, nuevoX, nuevoY)) {
            piezaSeleccionada->mover(nuevoX, nuevoY);
        }
        else if (!posicionOcupada(nuevoX, nuevoY)) {
            piezaSeleccionada->mover(nuevoX, nuevoY);
        }
    }
}
