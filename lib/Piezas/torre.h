#include "pieza.h"
#include "tablero.h"

class torre : pieza
{
public:
	void updatePosPosibles(); // Actualiza posiciones posibles
	void moverPosicion(int x, int y); // Mover posicion

	void updatePosPosibles(Tablero Tablero) {

		int x, y; //pos inicial de la torre
		int** tab;
		int dim_x, dim_y;

		int* posibles;

		//recorre el tablero
		for (int i = x + 1; dim_x; i++) {
			// si las posiciones posibles estan vacias o son distintas de 1,
			//es decir, del oponente osea que comibles las muestra al usuario
			if (tab[i][y] == 0) {
				//necesita una funci�n de print especial que destaque en verde
				//los movimientos posibles
				Tablero.printPosibles(i, j);
			}
		}

		for (int i = x - 1; dim_x; i--) {
			if (tab[i][y] == 0) {
				Tablero.printPosibles(i, j);
			}
		}

		for (int i = y - 1; dim_y; i--) {
			if (tab[x][i] == 0) {
				Tablero.printPosibles(i, j);
			}
		}

		for (int i = y + 1; dim_y; i++) {
			if (tab[x][i] == 0) {
				Tablero.printPosibles(i, j);
			}
		}
	}
};
