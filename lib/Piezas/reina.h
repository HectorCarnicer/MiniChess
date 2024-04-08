#include "pieza.h"

class reina : pieza
{
public:
	void updatePosPosibles(Tablero Tablero);
};

void reina::updatePosPosibles(Tablero tab) {

	//recorre el tablero
		for (int i = x + 1; tab.dim_x; i++) {
			// si las posiciones posibles estan vacias o son distintas de 1,
			//es decir, del oponente osea que comibles las muestra al usuario
			if (tab.defTablero[i][y] == 0) {
				//necesita una función de print especial que destaque en verde
				//los movimientos posibles
				tab.printPosibles(i, y);
			}
		}

		for (int i = x - 1; tab.dim_x; i--) {
			if (tab.defTablero[i][y] == 0) {
				tab.printPosibles(i, y);
			}
		}

		for (int i = y - 1;  tab.dim_y; i--) {
			if (tab.defTablero[x][i] == 0) {
				tab.printPosibles(x, i);
			}
		}

		for (int i = y + 1; tab.dim_y; i++) {
			if (tab.defTablero[x][i] == 0) {
				tab.printPosibles(x, i);
			}
		}
		for (int i = x + 1, int j = y + 1; tab.dim_x && tab.dim_y; i++, j++) {
			// si las posiciones posibles estan vacias o son distintas de 1,
			//es decir, del oponente osea que comibles las muestra al usuario
			if (tab.defTablero[i][j] == 0) {
				//necesita una función de print especial que destaque en verde
				//los movimientos posibles
				tab.printPosibles(i, j);
			}
		}

		for (int i = x + 1, int j = y - 1; tab.dim_x && tab.dim_y; i++, j--) {
			if (tab.defTablero[i][j] == 0) {
				tab.printPosibles(i, j);
			}
		}

		for (int i = x - 1, int j = y + 1; tab.dim_x && tab.dim_y; i--, j++) {
			if (tab.defTablero[i][j] == 0) {
				tab.printPosibles(i, j);
			}
		}

		for (int i = x - 1, int j = y - 1; tab.dim_x && tab.dim_y; i--, j--) {

			if (tab.defTablero[i][j] == 0) {
				tab.printPosibles(i, j);
			}
		}
	}

