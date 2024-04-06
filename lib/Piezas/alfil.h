#include "pieza.h"
#include "tablero.h"

class alfil : pieza
{
public:
	void updatePosPosibles(); // Actualiza posiciones posibles
	void moverPosicion(int x, int y); // Mover posicion

	void updatePosPosibles(Tablero Tablero ) {

		int x, y; //pos inicial del alfil
		int** tab;
		int dim_x, dim_y;

		int* posibles;

		//recorre el tablero
		for (int i = x + 1, int j = y + 1; dim_x && dim_y; i++, j++) {
			// si las posiciones posibles estan vacias o son distintas de 1,
			//es decir, del oponente osea que comibles las muestra al usuario
			if (tab[i][j]==0) {
				//necesita una función de print especial que destaque en verde
				//los movimientos posibles
				Tablero.printPosibles(i, j);
			}
		}

		for (int i = x + 1, int j = y - 1; dim_x && dim_y; i++, j--) {
			if (tab[i][j] == 0) {
				Tablero.printPosibles(i, j);
			}
		}

		for (int i = x -1, int j = y + 1; dim_x && dim_y; i--, j++) {
			if (tab[i][j] == 0) {
				Tablero.printPosibles(i, j);
			}
		}

		for (int i = x - 1, int j = y - 1; dim_x && dim_y; i--, j--) {
			
			if (tab[i][j] == 0) {
				Tablero.printPosibles(i, j);
			}
		}
	}
};
