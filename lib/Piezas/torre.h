#include "pieza.h"
class torre : pieza
{
public:
	void updatePosPosibles(Tablero tab);
};

void torre::updatePosPosibles(Tablero tab){
	int x = 4, y = 4;
	int id = TORRE_B;
	bool foundEnemy = false;
		//recorre el tablero
		for (int i = x + 1; i<tab.dim_x; i++) {
			// si las posiciones posibles estan vacias o son distintas de 1,
			//es decir, del oponente osea que comibles las muestra al usuario
			if (tab.defTablero[i][y] == 0) {
				//necesita una función de print especial que destaque en verde
				//los movimientos posibles
				tab.printPosibles(i, y,x,y,id);

			}
			else if (tab.defTablero[i][y] < 0 && !foundEnemy) {
				tab.defTablero[i][y] = 9; 
				foundEnemy = true; 
			}
		}
		foundEnemy = false;

		for (int i = x - 1; i >= 0; i--) {
			if (tab.defTablero[i][y] == 0) {
				tab.printPosibles(i, y, x, y, id);


			}
			else if (tab.defTablero[i][y] < 0 && !foundEnemy) {
				tab.defTablero[i][y] = 9; 
				foundEnemy = true;
			}
		}
		foundEnemy = false;
		for (int i = y - 1; i>=0; i--) {
			if (tab.defTablero[x][i] == 0) {
				tab.printPosibles(x, i, x, y, id);

			}
			else if (tab.defTablero[x][i] < 0 && !foundEnemy) {
				tab.defTablero[x][i] = 9; 
				foundEnemy = true;
			}
		}
		foundEnemy = false;
		for (int i = y + 1; i < tab.dim_y; i++) {
			if (tab.defTablero[x][i] == 0) {
				tab.printPosibles(x, i, x, y, id);

			}
			else if (tab.defTablero[x][i] < 0 && !foundEnemy) {
				tab.defTablero[x][i] = 9; 
				foundEnemy = true;
			}
		}
		foundEnemy = false;
}

