#include "pieza.h"

class alfil : pieza
{
public:
	void updatePosPosibles(); // Actualiza posiciones posibles
	void moverPosicion(int x, int y); // Mover posicion

	void updatePosPosibles(Tablero tab) {

		//recorre el tablero
		for (int i = x + 1, int j = y + 1; tab.dim_x && tab.dim_y; i++, j++) {
			// si las posiciones posibles estan vacias o son distintas de 1,
			//es decir, del oponente osea que comibles las muestra al usuario
			if (tab.mat[i][j]==0) {
				// Si la posici�n es v�lida, pone esa posici�n en la matris de posicones v�lidas a 1
				posiciones_validas.mat[i][j] = true;
			}
		}

		for (int i = x + 1, int j = y - 1; tab.dim_x && tab.dim_y; i++, j--) {
			if (tab.mat[i][j] == 0) {
				posiciones_validas.mat[i][j] = true;
			}
		}

		for (int i = x -1, int j = y + 1; tab.dim_x && tab.dim_y; i--, j++) {
			if (tab.mat[i][j] == 0) {
				posiciones_validas.mat[i][j] = true;
			}
		}

		for (int i = x - 1, int j = y - 1; tab.dim_x && tab.dim_y; i--, j--) {
			
			if (tab.mat[i][j] == 0) {
				posiciones_validas.mat[i][j] = true;
			}
		}
	}
};
