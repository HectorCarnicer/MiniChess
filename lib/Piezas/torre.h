#include "pieza.h"

class torre : pieza
{
public:
	void updatePosPosibles(Tablero tab);
};

void torre::updatePosPosibles(Tablero tab){
	bool foundEnemy = false;

		//recorre el tablero
	for (int i = x + 1; i < tab.dim_x; i++) {
		// si las posiciones posibles estan vacias o son distintas de 1,
		//es decir, del oponente osea que comibles las muestra al usuario
		if (tab.mat[i][y] == 0) {
			//necesita una función de print especial que destaque en verde
			//los movimientos posibles
			tab.printPosibles(i, y);
			posiciones_validas[i][y] = true;
		}
		else if (tab.mat[i][y] < 0 && !foundEnemy) {
			tab.mat[i][y] = 9;
			foundEnemy = true;
		}
	}


	for (int i = x - 1; i >= 0; i--) {
		if (tab.mat[i][y] == 0) {
			tab.printPosibles(i, y);
			posiciones_validas[i][y] = true;

		}
		else if (tab.mat[i][y] < 0 && !foundEnemy) {
			tab.mat[i][y] = 9; // Cambia la primera pieza enemiga encontrada a '9'
			foundEnemy = true; // Actualiza la bandera para indicar que se encontró una pieza enemiga
		}
	}


	for (int i = y - 1; i >= 0; i--) {
		if (tab.mat[x][i] == 0) {
			tab.printPosibles(x, i);
			posiciones_validas[x][i] = true;

		}
		else if (tab.mat[x][i] < 0 && !foundEnemy) {
			tab.mat[x][i] = 9; // Cambia la primera pieza enemiga encontrada a '9'
			foundEnemy = true; // Actualiza la bandera para indicar que se encontró una pieza enemiga
		}
	}



	for (int i = y + 1; i < tab.dim_y; i++) {
		if (tab.mat[x][i] == 0) {
			tab.printPosibles(x, i);
			posiciones_validas[x][i] = true;

		}
		else if (tab.mat[x][i] < 0 && !foundEnemy) {
			tab.mat[x][i] = 9; // Cambia la primera pieza enemiga encontrada a '9'
			foundEnemy = true; // Actualiza la bandera para indicar que se encontró una pieza enemiga
		}
	}

}

