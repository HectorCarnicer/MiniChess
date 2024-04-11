//#include "pieza.h"
//
//class peon : pieza
//{
//public:
//
//	int color=1;//1 blancas, -1 negras
//	int id = PEON_B;
//	void updatePosPosibles(Tablero tab) {
//		y = (color == 1) ? 6 : 1;
//		cout << y;
//		int direccion = (color == 1) ? 1 : -1;
//
//		//comprueba si es la fila inicial
//
//		if ((color == -1 && tab.dim_y == 1)) {
//			if (y + (direccion * 2) == 0) {
//				tab.printPosibles(x, y, x, y, id);
//				//posiciones_validas[x][y] = true;
//			}
//			else if (y + direccion == 0) {
//				tab.printPosibles(x, y, x, y, id);
//				//posiciones_validas[x][y] = true;
//			}
//		}
//		if (color == 1 && y == 6) {
//			if (y - (direccion * 2) == 0) {
//				tab.printPosibles(x, y, x, y, id);
//				//posiciones_validas[x][y] = true;
//			}
//			else if (y - direccion == 0) {
//				tab.printPosibles(x, y, x, y, id);
//				//posiciones_validas[x][y] = true;
//			}
//		}
//	
//	}
//
//};