#include "pieza.h"

class alfil : pieza
{
public:

	// Función que encuentra las posiciones específicas para el alfil
	void updatePosPosibles(Tablero tab);
};

void alfil::updatePosPosibles(Tablero tab)
{
	//recorre el tablero
	for (int i = x + 1, int j = y + 1; tab.dim_x && tab.dim_y; i++, j++) {
		if (tab.mat[i][j] == 0) {
			// Si la posición es válida, pone esa posición en la matris de posicones válidas a 1
			posiciones_validas[i][j] = true;
			tab.printPosibles(x, y);

		}
	}

	for (int i = x + 1, int j = y - 1; tab.dim_x && tab.dim_y; i++, j--) {
		if (tab.mat[i][j] == 0) {
			posiciones_validas[i][j] = true;
			tab.printPosibles(x, y);

		}
	}

	for (int i = x - 1, int j = y + 1; tab.dim_x && tab.dim_y; i--, j++) {
		if (tab.mat[i][j] == 0) {
			posiciones_validas[i][j] = true;
			tab.printPosibles(x, y);

		}
	}

	for (int i = x - 1, int j = y - 1; tab.dim_x && tab.dim_y; i--, j--) {

		if (tab.mat[i][j] == 0) {
			posiciones_validas[i][j] = true;
			tab.printPosibles(x, y);

		}
	}
}