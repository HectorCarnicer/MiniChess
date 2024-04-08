#include "pieza.h"

class peon : pieza
{
public:

	int color;//1 blancas, -1 negras

	void updatePosPosibles(Tablero tab) {

		int direccion = (color == 1) ? 1 : -1;

		//comprueba si es la fila inicial

		if (color == 1 && y == 1 || color == -1 && tab.dim_y == 6) {
			if (y + (direccion * 2) == 0) {
					tab.printPosibles(x, y);
					posiciones_validas[x][y] = true;
				}
			
		}else if (y + direccion == 0) {
			tab.printPosibles(x, y);
			posiciones_validas[x][y] = true;
		}

	}

};