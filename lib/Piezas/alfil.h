//#include <cstdlib>
//#include "pieza.h"
//
//class alfil : pieza
//{
//public:
//	void updatePosPosibles(Tablero tablero) {
//		int x = 3, y = 3; // posición inicial del alfil
//		int id = ALFIL_B;
//		bool foundEnemy = false;
//		bool foundEnemy2 = false;
//		
//			// bandera para seguir si se ha encontrado una pieza enemiga
//		// recorre el tablero en las diagonales
//		for (int i = x + 1, j = y + 1; i < 8 && j < 8; i++, j++) {
//
//			if (tablero.defTablero[i][j] == 0) {
//				tablero.printPosibles(i, j, x, y, id);
//			}
//
//			else if (tablero.defTablero[i][j] < 0 && !foundEnemy) {
//				tablero.defTablero[i][j] = 9; // cambia la primera pieza enemiga encontrada a '9'
//				foundEnemy = true; // actualiza la bandera para indicar que se encontró una pieza enemiga
//			}
//		}
//		foundEnemy = false;
//
//		for (int i = x + 1, j = y - 1; i < 8 && j >= 0; i++, j--) {
//			if (tablero.defTablero[i][j] == 0) {
//				tablero.printPosibles(i, j, x, y, id);
//			}
//			else if (tablero.defTablero[i][j] < 0 && !foundEnemy) {
//				tablero.defTablero[i][j] = 9; // cambia la primera pieza enemiga encontrada a '9'
//				foundEnemy = true; // actualiza la bandera para indicar que se encontró una pieza enemiga
//			}
//
//		}
//		for (int i = x - 1, j = y + 1; i >= 0 && j < 8; i--, j++) {
//			if (tablero.defTablero[i][j] == 0) {
//
//				tablero.printPosibles(i, j, x, y, id);
//			}
//			else if (tablero.defTablero[i][j] < 0 && !foundEnemy2) {
//				tablero.defTablero[i][j] = 9; // cambia la primera pieza enemiga encontrada a '9'
//				foundEnemy2 = true; // actualiza la bandera para indicar que se encontró una pieza enemiga
//			}
//		}
//		for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--) {
//			if (tablero.defTablero[i][j] == 0) {
//				tablero.printPosibles(i, j, x, y, id);
//			}
//			else if (tablero.defTablero[i][j] < 0 && !foundEnemy2) {
//				tablero.defTablero[i][j] = 9; // cambia la primera pieza enemiga encontrada a '9'
//				foundEnemy2 = true; // actualiza la bandera para indicar que se encontró una pieza enemiga
//			}
//		}
//	}
//
//};
