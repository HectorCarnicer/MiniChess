#include "pieza.h"
#include "tablero.h"

class peon : pieza
{
public:

	int x, y; //pos inicial del peon
	int** tab;
	int dim_x, dim_y;
	int color;//1 blancas, -1 negras

	void updatePosPosibles(Tablero Tablero) {

		int direccion = (color == 1) ? 1 : -1;

		//comprueba si es la fila inicial

		if (color == 1 && y == 1 || color == -1 && dim_y == 6) {
			if (y + (direccion * 2) == 0) {
					Tablero::printPosibles(x, y);
				}
			
		}else if (y + direccion == 0) {
			Tablero::printPosible(x, y);
		}

	}

};