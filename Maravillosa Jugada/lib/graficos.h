#include "freeglut.h"
#include <vector>
#include <string>
#include "pieza.h"

// Suponiendo que TAMANO_TABLERO es una constante global o un miembro de la clase Gardner
const int TAMANO_TABLERO = 8;
std::vector<Pieza*>& piezas;

std::vector<std::vector<std::string>> pintarTablero() {
    // Crear un tablero vacío
    std::vector<std::vector<std::string>> tablero(TAMANO_TABLERO, std::vector<std::string>(TAMANO_TABLERO, "."));

    // Colocar las iniciales de las piezas en el tablero
    for (const auto& pieza : piezas) {
        int x, y;
        pieza->obtenerPosicion(x, y); // Asumiendo que tienes un método para obtener la posición
        tablero[y][x] = pieza->nombreDeClase().substr(0, 1); // Usa la primera letra del nombre de la clase
    }

    // Devolver el tablero
    return tablero;
}

// Variables globales para el tablero
std::vector<std::vector<std::string>> tablero;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Tamaño de las celdas
    float cellSize = 2.0f / TAMANO_TABLERO;

    // Dibujar el tablero
    for (int i = 0; i < TAMANO_TABLERO; ++i) {
        for (int j = 0; j < TAMANO_TABLERO; ++j) {
            // Calcular las coordenadas de las esquinas de la celda
            float x1 = -1.0f + j * cellSize;
            float y1 = 1.0f - i * cellSize;
            float x2 = x1 + cellSize;
            float y2 = y1 - cellSize;

            // Dibujar la celda
            glBegin(GL_QUADS);
            if ((i + j) % 2 == 0) {
                glColor3f(1.0f, 1.0f, 1.0f); // Color blanco para las celdas
            }
            else {
                glColor3f(0.0f, 0.0f, 0.0f); // Color negro para las celdas
            }
            glVertex2f(x1, y1);
            glVertex2f(x2, y1);
            glVertex2f(x2, y2);
            glVertex2f(x1, y2);
            glEnd();

            // Dibujar la pieza si existe
            if (tablero[i][j] != ".") {
                // Establecer el color de la pieza (puedes personalizar esto)
                glColor3f(1.0f, 0.0f, 0.0f); // Rojo para las piezas

                // Dibujar la inicial de la pieza
                glRasterPos2f((x1 + x2) / 2, (y1 + y2) / 2);
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, tablero[i][j][0]);
            }
        }
    }

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    // Obtener el tablero
    tablero = pintarTablero();

    // Inicializar GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Tablero de Juego");

    // Establecer la función de dibujo
    glutDisplayFunc(display);

    // Establecer el color de fondo
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    // Iniciar el bucle principal de GLUT
    glutMainLoop();

    return 0;
}
