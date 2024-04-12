#ifndef AJEDREZ_FUNCIONES_H
#define AJEDREZ_FUNCIONES_H

#include <vector>
#include "lib/Pieza.h"

// Verifica si la posición está ocupada por otra pieza
bool posicionOcupada(const std::vector<Pieza*>& piezas, int x, int y);

// "Come" la pieza en la posición dada
void comerPieza(std::vector<Pieza*>& piezas, int x, int y);

// Verifica si el camino está libre para el movimiento de la pieza
bool caminoLibre(const std::vector<Pieza*>& piezas, Pieza* pieza, int xFinal, int yFinal);

#endif // AJEDREZ_FUNCIONES_H