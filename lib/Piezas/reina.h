//#include "pieza.h"
//
//class reina : pieza
//{
//public:
//	void updatePosPosibles(Tablero Tablero);
//};
//
//void reina::updatePosPosibles(Tablero tab) {
//		int x = 3, y = 3, id = REINA_B;
//		bool foundEnemy = false;
//		for (int i = x + 1; i < tab.dim_x; i++) {
//			// si las posiciones posibles estan vacias o son distintas de 1,
//			//es decir, del oponente osea que comibles las muestra al usuario
//			if (tab.defTablero[i][y] == 0) {
//				//necesita una función de print especial que destaque en verde
//				//los movimientos posibles
//				tab.printPosibles(i, y, x, y, id);
//
//			}
//			else if (tab.defTablero[i][y] < 0 && !foundEnemy) {
//				tab.defTablero[i][y] = 9;
//				foundEnemy = true;
//			}
//		}
//		foundEnemy = false;
//
//		for (int i = x - 1; i >= 0; i--) {
//			if (tab.defTablero[i][y] == 0) {
//				tab.printPosibles(i, y, x, y, id);
//			}
//			else if (tab.defTablero[i][y] < 0 && !foundEnemy) {
//				tab.defTablero[i][y] = 9;
//				foundEnemy = true;
//			}
//		}
//		foundEnemy = false;
//		for (int i = y - 1; i >= 0; i--) {
//			if (tab.defTablero[x][i] == 0) {
//				tab.printPosibles(x, i, x, y, id);
//
//			}
//			else if (tab.defTablero[x][i] < 0 && !foundEnemy) {
//				tab.defTablero[x][i] = 9;
//				foundEnemy = true;
//			}
//		}
//		foundEnemy = false;
//		for (int i = y + 1; i < tab.dim_y; i++) {
//			if (tab.defTablero[x][i] == 0) {
//				tab.printPosibles(x, i, x, y, id);
//
//			}
//			else if (tab.defTablero[x][i] < 0 && !foundEnemy) {
//				tab.defTablero[x][i] = 9;
//				foundEnemy = true;
//			}
//		}
//		foundEnemy = false;
//		//HASTA AQUI TORRE
//		for (int i = x + 1, j = y + 1; i < 8 && j < 8; i++, j++) {
//
//			if (tab.defTablero[i][j] == 0) {
//				tab.printPosibles(i, j, x, y, id);
//			}
//
//			else if (tab.defTablero[i][j] < 0 && !foundEnemy) {
//				tab.defTablero[i][j] = 9; // cambia la primera pieza enemiga encontrada a '9'
//				foundEnemy = true; // actualiza la bandera para indicar que se encontró una pieza enemiga
//			}
//		}
//		foundEnemy = false;
//		for (int i = x + 1, j = y - 1; i < 8 && j >= 0; i++, j--) {
//			if (tab.defTablero[i][j] == 0) {
//				tab.printPosibles(i, j, x, y, id);
//			}
//			else if (tab.defTablero[i][j] < 0 && !foundEnemy) {
//				tab.defTablero[i][j] = 9; // cambia la primera pieza enemiga encontrada a '9'
//				foundEnemy = true; // actualiza la bandera para indicar que se encontró una pieza enemiga
//			}
//
//		}
//		foundEnemy = false;
//		for (int i = x - 1, j = y + 1; i >= 0 && j < 8; i--, j++) {
//			if (tab.defTablero[i][j] == 0) {
//
//				tab.printPosibles(i, j, x, y, id);
//			}
//			else if (tab.defTablero[i][j] < 0 && !foundEnemy) {
//				tab.defTablero[i][j] = 9; // cambia la primera pieza enemiga encontrada a '9'
//				foundEnemy = true; // actualiza la bandera para indicar que se encontró una pieza enemiga
//			}
//		}
//		foundEnemy = false;
//		for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--) {
//			if (tab.defTablero[i][j] == 0) {
//				tab.printPosibles(i, j, x, y, id);
//			}
//			else if (tab.defTablero[i][j] < 0 && !foundEnemy) {
//				tab.defTablero[i][j] = 9; // cambia la primera pieza enemiga encontrada a '9'
//				foundEnemy = true; // actualiza la bandera para indicar que se encontró una pieza enemiga
//			}
//		}
//		foundEnemy = false;
//}
//
//
//
