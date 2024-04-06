#include "pieza.h"
#include "tablero.h"

class rey : pieza
{
public:

	int x, y; //pos inicial del peon
	int** tab;
	int dim_x, dim_y;

	void updatePosPosibles(Tablero Tablero) {

		int movimientospos[8][2] = { {1,0}, {1,1}, {1,-1}, {0,1}
								,{0,-1}, {-1,0}, {-1,1}, {-1,-1} };

		for (int i = 0; i < 8; i++) {
			//recorre las L del caballo posibles
			int posposiblex = x + movimientospos[i][0];
			int posposibley = y + movimientospos[i][1];
			
			if (posposiblex >= 0 && posposiblex < dim_x && posposibley >= 0 && posposibley < dim_y) {
				//comprueba que este vacía
				if (tab[posposiblex][posposibley] == 0) {				
					Tablero.printPosibles(posposiblex, posposibley);
					}
			}

		}

	}

};