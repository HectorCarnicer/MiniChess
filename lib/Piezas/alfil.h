#include "pieza.h"
class alfil : pieza
{
public:
	void updatePosPosibles(); // Actualiza posiciones posibles
	void moverPosicion(int x, int y); // Mover posicion
};