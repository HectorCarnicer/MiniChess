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

bool Mundo::atacarPieza(Color color, int x, int y, Pieza* piezaSeleccionada) {

    int posX, posY;
    piezaSeleccionada->obtenerPosicion(posX, posY);
    int colorPiezaSeleccionada = piezaSeleccionada->obtenerColor();

    if (colorPiezaSeleccionada != color) {
        return false; 
    }

    int deltaX = x - posX;
    int deltaY = y - posY;

    std::string nombreClase = piezaSeleccionada->nombreDeClase();

    // Manejar el caso donde la pieza seleccionada no es un pe�n
    if (nombreClase != "Peon") {
        for (const auto& pieza : piezas) {
            int posXOponente, posYOponente;
            pieza->obtenerPosicion(posXOponente, posYOponente);
            int colorOponente = pieza->obtenerColor();

            if (posXOponente == x && posYOponente == y && colorOponente != color) {
                comerPieza(x, y);
                return true;
            }
        }
        return false;
    }

    // Manejar el caso donde la pieza seleccionada es un pe�n
    if (nombreClase == "Peon") {
        if (colorPiezaSeleccionada == BLANCO && deltaY == -1 && abs(deltaX) == 1) {
            for (const auto& pieza : piezas) {
                int posXOponente, posYOponente;
                pieza->obtenerPosicion(posXOponente, posYOponente);
                int colorOponente = pieza->obtenerColor();

                if (posXOponente == x && posYOponente == y && colorOponente != color) {
                    comerPieza(x, y);
                    return true;
                }
            }
        }
        if (colorPiezaSeleccionada == NEGRO && deltaY == 1 && abs(deltaX) == 1) {
            for (const auto& pieza : piezas) {
                int posXOponente, posYOponente;
                pieza->obtenerPosicion(posXOponente, posYOponente);
                int colorOponente = pieza->obtenerColor();

                if (posXOponente == x && posYOponente == y && colorOponente != color) {
                    comerPieza(x, y);
                    return true;
                }
            }
        }
    }

    return false; 
}

bool Mundo::detectarJaque(Color& turnoActual) {
    int posreyx=0, posreyy=0;

   for (const auto& pieza : piezas) {
        if (pieza->obtenerColor() == turnoActual && pieza->nombreDeClase() == "Rey") {
            pieza->obtenerPosicion(posreyx, posreyy);
            break;
        }
   }
   for (const auto& pieza : piezas) {
        if (pieza->obtenerColor() != turnoActual) {
            if (!caminoLibre(pieza, posreyx, posreyy)) {
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

        int deltaX = nuevoX - x;
        int deltaY = nuevoY - y;
        if (pieza->obtenerColor() == BLANCO && deltaY == -1 && deltaX == 0) {
            if (posicionOcupada(nuevoX, nuevoY))
                return false;
        }
        if (pieza->obtenerColor() == NEGRO && deltaY == 1 && deltaX == 0) {
            if (posicionOcupada(nuevoX, nuevoY))
                return false;
        }

        if (pieza->obtenerColor() == BLANCO && deltaY == -1 && abs(deltaX) == 1) {
            if (!posicionOcupada(nuevoX, nuevoY))
                return false;
        }
        if (pieza->obtenerColor() == NEGRO && deltaY == 1 && abs(deltaX) == 1) {
            if (!posicionOcupada(nuevoX, nuevoY))       
                return false;
        }
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

    if (nombre == "Rey") {
        int x, y;
        pieza->obtenerPosicion(x, y);
        
        int deltaX = nuevoX - x;
        int deltaY = nuevoY - y;

        if (abs(deltaX) <= 1 && abs(deltaY) <= 1) {
            if (posicionOcupada(nuevoX, nuevoY))
                return false;
        }
        return true;
    }

    if (nombre == "Reina") {
        int x, y;
        pieza->obtenerPosicion(x, y);

        // posiciones a la derecha
        if (nuevoX > x) {
            for (int i = x + 1; i <= nuevoX; i++) {
                if (posicionOcupada(i, y))
                    return false;
            }
        }
        // posiciones a la izq
        else if (nuevoX < x) {
            for (int i = x - 1; i >= nuevoX; i--) {
                if (posicionOcupada(i, y))
                    return false;
            }
        }
        // posiciones encima
        else if (nuevoY > y) {
            for (int j = y + 1; j <= nuevoY; j++) {
                if (posicionOcupada(x, j))
                    return false;
            }
        }        
        // posiciones debajo
        else if (nuevoY < y) {
            for (int j = y - 1; j >= nuevoY; j--) {
                if (posicionOcupada(x, j))
                    return false;
            }
        }
        if (nuevoX > x && nuevoY > y) {
            for (int i = x + 1, j = y + 1; i <= nuevoX && j <= nuevoY; i++, j++) {
                if (posicionOcupada(i, j))
                    return false;
            }
        }
        else if (nuevoX < x && nuevoY > y) {
            for (int i = x - 1, j = y + 1; i >= nuevoX && j <= nuevoY; i--, j++) {
                if (posicionOcupada(i, j))
                    return false;
            }
        }
        else if (nuevoX > x && nuevoY < y) {
            for (int i = x + 1, j = y - 1; i <= nuevoX && j >= nuevoY; i++, j--) {
                if (posicionOcupada(i, j))
                    return false;
            }
        }
        else if (nuevoX < x && nuevoY < y) {
            for (int i = x - 1, j = y - 1; i >= nuevoX && j >= nuevoY; i--, j--) {
                if (posicionOcupada(i, j))
                    return false;
            }
        }
        
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
        return true;
    }


    if (nombre == "Caballo") {
        int x, y;
        pieza->obtenerPosicion(x, y);

        int movimientospos[8][2] = { {2,1}, {2,-1}, {1,2}, {1,-2}
                                  ,{-1,2}, {-1,-2}, {-2,1}, {-2,-1} };

        for (int i = 0; i < 8; i++) {
            //recorre las L del caballo posibles
            int posposiblex = x + movimientospos[i][0];
            int posposibley = y + movimientospos[i][1];

            if (posposiblex == nuevoX && posposibley == nuevoY) {
                if (posicionOcupada(posposiblex, posposibley))
                    return false;
            }
        }

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


