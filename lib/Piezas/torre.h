#include "pieza.h"

class torre : pieza
{
public:
	void updatePosPosibles(Tablero tab);
};

void torre::updatePosPosibles(Tablero tab){

		//recorre el tablero
		for (int i = x + 1; tab.dim_x; i++) {
			// si las posiciones posibles estan vacias o son distintas de 1,
			//es decir, del oponente osea que comibles las muestra al usuario
			if (tab.defTablero[i][y] == 0) {
				//necesita una función de print especial que destaque en verde
				//los movimientos posibles
				tab.printPosibles(i, y);
				posiciones_validas[i][y] = true;
			}
		}

		for (int i = x - 1; tab.dim_x; i--) {
			if (tab.defTablero[i][y] == 0) {
				tab.printPosibles(i, y);
				posiciones_validas[i][y] = true;

			}
		}

		for (int i = y - 1; tab.dim_y; i--) {
			if (tab.defTablero[x][i] == 0) {
				tab.printPosibles(x, i);
				posiciones_validas[x][i] = true;


			}
		}

		for (int i = y + 1; tab.dim_y; i++) {
			if (tab.defTablero[x][i] == 0) {
				tab.printPosibles(x, i);
				posiciones_validas[x][i] = true;
			}
		}
}

