#include "../lib/mundo.h"

// Funci�n para verificar si la posici�n est� ocupada por otra pieza
bool Mundo::posicionOcupada(int x, int y) {
    for (const auto& pieza : piezas) {
        int posX, posY;
        pieza->obtenerPosicion(posX, posY);
        if (posX == x && posY == y) {
            return true;
        }
    }
    return false;
}

bool Mundo::atacarPieza(Color color,int x, int y) {
    for (const auto& pieza : piezas) {
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


// Funci�n para "comer" la pieza en la posici�n dada
void Mundo::comerPieza(int x, int y) {
    for (auto it = piezas.begin(); it != piezas.end(); ) {
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



bool Mundo::detectarJaque(Color& turnoActual) {
    int posReyX=0, posReyY=0;
    for (const auto& pieza : piezas) {
        if (pieza->obtenerColor() == turnoActual && pieza->nombreDeClase() == "Rey") {
            pieza->obtenerPosicion(posReyX, posReyY);
            pieza->mostrarPosicion();
            break;
        }
    }
    
    for (const auto& pieza : piezas) {
        if (pieza->obtenerColor() != turnoActual) {
            if (!caminoLibre(pieza, posReyX, posReyY)) {
                return true;
            }
          
        }
    }
    return false;
}


// Funci�n para verificar si el camino est� libre para el movimiento de la pieza
bool Mundo::caminoLibre(Pieza* pieza, int nuevoX, int nuevoY) {
    // Implementar la l�gica espec�fica para cada tipo de pieza
    // Por ejemplo, para un pe�n, solo necesitas verificar la casilla final
    // Para piezas como la torre, alfil o reina, necesitas verificar todas las casillas en el camino
    // ...

    std::string nombre = pieza->nombreDeClase();

    if (nombre == "Peon") {
        int x, y;
        pieza->obtenerPosicion(x, y);
        return true;
    }
    if (nombre == "Alfil") {

            int x, y;
            pieza->obtenerPosicion(x, y);
            // esto seria la diagonal arriba derecha
            if (nuevoX > x && nuevoY > y) {
                for (int i = x + 1, j = y + 1; i <= nuevoX && j <= nuevoY; i++, j++) {
                    if (posicionOcupada(i, j))
                        return false;
                }
            }
            // esto seria la diagonal izq arriba
            else if (nuevoX < x && nuevoY > y) {
                for (int i = x - 1, j = y + 1; i >= nuevoX && j <= nuevoY; i--, j++) {
                    if (posicionOcupada(i, j))
                        return false;
                }
            }
            // esto la diagonal derecha abajo
            else if (nuevoX > x && nuevoY < y) {
                for (int i = x + 1, j = y - 1; i <= nuevoX && j >= nuevoY; i++, j--) {
                    if (posicionOcupada(i, j))
                        return false;
                }
            }
            //esto la diagonal abajo izq
            else if (nuevoX < x && nuevoY < y) {
                for (int i = x - 1, j = y - 1; i >= nuevoX && j >= nuevoY; i--, j--) {
                    if (posicionOcupada(i, j))
                        return false;
                }
            }
            return true;
    }

    if (pieza->nombreDeClase() == "Rey") {
        return true;
    }
    
    if (nombre == "Torre") {
        int x, y;
        pieza->obtenerPosicion(x, y);
        if (nuevoX > x) {
            for (int i = x + 1; i <= nuevoX; i++) {
                if (posicionOcupada(i, y))
                    return false;
            }
        }
        else if (nuevoX < x) {
            for (int i = x - 1; i >= nuevoX; i--) {
                if (posicionOcupada(i, y))
                    return false;
            }
        }
        else if (nuevoY > y) {
            for (int j = y + 1; j <= nuevoY; j++) {
                if (posicionOcupada(x, j))
                    return false;
            }
        }
        else if (nuevoY < y) {
            for (int j = y - 1; j >= nuevoY; j--) {
                if (posicionOcupada(x, j))
                    return false;
            }
        }
        else return true;
    }

    if (nombre == "Reina") {
        int x, y;
        pieza->obtenerPosicion(x, y);

        if (nuevoX > x && nuevoY > y) {
            for (int i = x + 1, j = y + 1; i <= nuevoX && j <= nuevoY; i++, j++) {
                if (posicionOcupada(i, j))
                    return false;
            }
        }
        // esto seria la diagonal izq arriba
        else if (nuevoX < x && nuevoY > y) {
            for (int i = x - 1, j = y + 1; i >= nuevoX && j <= nuevoY; i--, j++) {
                if (posicionOcupada(i, j))
                    return false;
            }
        }
        // esto la diagonal derecha abajo
        else if (nuevoX > x && nuevoY < y) {
            for (int i = x + 1, j = y - 1; i <= nuevoX && j >= nuevoY; i++, j--) {
                if (posicionOcupada(i, j))
                    return false;
            }
        }
        //esto la diagonal abajo izq
        else if (nuevoX < x && nuevoY < y) {
            for (int i = x - 1, j = y - 1; i >= nuevoX && j >= nuevoY; i--, j--) {
                if (posicionOcupada(i, j))
                    return false;
            }
        }
        if (nuevoX > x) {
            for (int i = x + 1; i <= nuevoX; i++) {
                if (posicionOcupada(i, y))
                    return false;
            }
        }
        else if (nuevoX < x) {
            for (int i = x - 1; i >= nuevoX; i--) {
                if (posicionOcupada(i, y))
                    return false;
            }
        }
        else if (nuevoY > y) {
            for (int j = y + 1; j <= nuevoY; j++) {
                if (posicionOcupada(x, j))
                    return false;
            }
        }
        else if (nuevoY < y) {
            for (int j = y - 1; j >= nuevoY; j--) {
                if (posicionOcupada(x, j))
                    return false;
            }
        }
        return true;



    }
    if (nombre == "Caballo") {

    }
    return true; // Por defecto, asumimos que el camino est� libre
}

void Mundo::imprimirTablero()
{
    // Crear un tablero vac�o
    std::string tablero[8][8];
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            tablero[i][j] = ".";
        }
    }

    // Colocar las iniciales de las piezas en el tablero
    for (const auto& pieza : piezas) {
        int x, y;
        pieza->obtenerPosicion(x, y); // Asumiendo que tienes un m�todo para obtener la posici�n
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


