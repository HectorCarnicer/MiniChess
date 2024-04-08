#include "pieza.h"

class rey : pieza
{
public:

	void updatePosPosibles(Tablero Tablero);


};

void rey::updatePosPosibles(Tablero tab){
		int movimientospos[8][2] = { {1,0}, {1,1}, {1,-1}, {0,1}
								,{0,-1}, {-1,0}, {-1,1}, {-1,-1} };

		for (int i = 0; i < 8; i++) {
			//recorre las L del caballo posibles
			int posposiblex = x + movimientospos[i][0];
			int posposibley = y + movimientospos[i][1];
			
			if (posposiblex >= 0 && posposiblex < tab.dim_x && posposibley >= 0 && posposibley < dim_y) {
				//comprueba que este vacía
				if (tab.defTablero[posposiblex][posposibley] == 0) {				
					tab.printPosibles(posposiblex, posposibley);
					posiciones_validas[posposiblex][posposibley] = true;

					}
			}

		}

	}

