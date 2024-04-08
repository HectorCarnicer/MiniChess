#include "pieza.h"

class caballo : pieza
{
public:

	void updatePosPosibles(Tablero Tablero); 

};

	void caballo::updatePosPosibles(Tablero tab){
		int movimientospos[8][2] = { {2,1}, {2,-1}, {1,2}, {1,-2}
									,{-1,2}, {-1,-2}, {-2,1}, {-2,-1} };

		for (int i = 0; i < 8; i++) {
			//recorre las L del caballo posibles
			int posposiblex = x + movimientospos[i][0];
			int posposibley = y + movimientospos[i][1];

			//comprueba que no están fuera del tablero

			if (posposiblex >= 0 && posposiblex < tab.dim_x && posposibley >= 0 && posposibley < tab.dim_y) {
				//comprueba que este vacía
				if (tab.mat[posposiblex][posposibley] == 0) {
					tab.printPosibles(posposiblex, posposibley);
				}
			}
		}
	}






