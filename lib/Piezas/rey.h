#include "pieza.h"

class rey : pieza
{
public:

	void updatePosPosibles(Tablero Tablero);


};

void rey::updatePosPosibles(Tablero tab) {

	int y = 2, x = 2;
	int id = REY_B;
	int movimientospos[8][2] = { {1,0}, {1,1}, {1,-1}, {0,1}
							,{0,-1}, {-1,0}, {-1,1}, {-1,-1} };

	for (int i = 0; i < 8; i++) {
		//recorre las L del caballo posibles
		int posposiblex = x + movimientospos[i][0];
		int posposibley = y + movimientospos[i][1];

		if (posposiblex >= 0 && posposiblex < tab.dim_x && posposibley >= 0 && posposibley < tab.dim_y) {
			//comprueba que este vacía
			if (tab.defTablero[posposiblex][posposibley] <= 0) {
				tab.printPosibles(posposiblex, posposibley, x ,y, REY_B);
			}
			
		}

	}
}



