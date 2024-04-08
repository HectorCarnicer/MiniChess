#include "tablero.h"
#include <cstdlib>

class alfil
{
public:
    void updatePosPosibles(Tablero& tablero) {
        int x = 4, y = 4; // Posición inicial del alfil
        int cont = 1;
        bool foundEnemy = false; // Bandera para seguir si se ha encontrado una pieza enemiga

        // Recorre el tablero en las diagonales
        for (int i = x + 1, j = y + 1; i < 8 && j < 8; i++, j++) {

            if (tablero.mat[i][j] == 0) {
                tablero.printPosibles(i, j);
                system("cls");
            }

            else if (tablero.mat[i][j] < 0 && !foundEnemy) {
                tablero.mat[i][j] = 9; // Cambia la primera pieza enemiga encontrada a '9'
                foundEnemy = true; // Actualiza la bandera para indicar que se encontró una pieza enemiga
            }
        }
        foundEnemy = false;

        for (int i = x + 1, j = y - 1; i < 8 && j >= 0; i++, j--) {
            if (tablero.mat[i][j] == 0) {
                tablero.printPosibles(i, j);
                system("cls");
            }
            else if (tablero.mat[i][j] < 0 && !foundEnemy) {
                tablero.mat[i][j] = 9; // Cambia la primera pieza enemiga encontrada a '9'
                foundEnemy = true; // Actualiza la bandera para indicar que se encontró una pieza enemiga
            }

        }
        foundEnemy = false;
        for (int i = x - 1, j = y + 1; i >= 0 && j < 8; i--, j++) {
            if (tablero.mat[i][j] == 0) {

                tablero.printPosibles(i, j);
                system("cls");
            }
            else if (tablero.mat[i][j] < 0 && !foundEnemy) {
                tablero.mat[i][j] = 9; // Cambia la primera pieza enemiga encontrada a '9'
                foundEnemy = true; // Actualiza la bandera para indicar que se encontró una pieza enemiga
            }
        }
        foundEnemy = false;
        for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--) {
            if (tablero.mat[i][j] == 0) {

                tablero.printPosibles(i, j);
                system("cls");
            }
            else if (tablero.mat[i][j] < 0 && !foundEnemy) {
                tablero.mat[i][j] = 9; // Cambia la primera pieza enemiga encontrada a '9'
                foundEnemy = true; // Actualiza la bandera para indicar que se encontró una pieza enemiga
            }

        }
    }

};
