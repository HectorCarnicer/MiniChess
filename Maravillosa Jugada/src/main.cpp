#include "../lib/freeglut.h"
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include "../lib/Pieza.h"
#include "../lib/Peon.h"
#include "../lib/Rey.h"
#include "../lib/Gardner.h"
#define TAMANO_TABLERO 5
// Variables globales para el tablero y piezas
std::vector<Pieza*> piezas;
Gardner* gardner;
std::vector<std::vector<std::string>> tablero;
Color turnoActual = BLANCO; // Comienza el turno de las piezas blancas

// Función para pintar el tablero
std::vector<std::vector<std::string>> pintarTablero() {
    std::vector<std::vector<std::string>> tablero(TAMANO_TABLERO, std::vector<std::string>(TAMANO_TABLERO, "."));

    for (const auto& pieza : piezas) {
        int x, y;
        pieza->obtenerPosicion(x, y);
        tablero[y][x] = pieza->nombreDeClase().substr(0, 1);
    }

    return tablero;
}

// Función de dibujo de FreeGLUT
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    float cellSize = 2.0f /TAMANO_TABLERO;

    for (int i = 0; i <TAMANO_TABLERO; ++i) {
        for (int j = 0; j < TAMANO_TABLERO; ++j) {
            float x1 = -1.0f + j * cellSize;
            float y1 = 1.0f - i * cellSize;
            float x2 = x1 + cellSize;
            float y2 = y1 - cellSize;

            glBegin(GL_QUADS);
            if ((i + j) % 2 == 0) {
                glColor3f(1.0f, 1.0f, 1.0f); // Blanco
            }
            else {
                glColor3f(0.0f, 0.0f, 0.0f); // Negro
            }
            glVertex2f(x1, y1);
            glVertex2f(x2, y1);
            glVertex2f(x2, y2);
            glVertex2f(x1, y2);
            glEnd();

            if (tablero[i][j] != ".") {
                glColor3f(1.0f, 0.0f, 0.0f); // Rojo para las piezas
                glRasterPos2f((x1 + x2) / 2, (y1 + y2) / 2);
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, tablero[i][j][0]);
            }
        }
    }

    glutSwapBuffers();
}

void idle() {
    // Actualizar el tablero y redibujar
    tablero = pintarTablero();
    glutPostRedisplay();
}

void ejecutarComandoMovimiento() {
    while (true) {
        gardner->nuevaJugada(turnoActual);
    }
}

int main(int argc, char** argv) {
    piezas = {
        // Inicializar tus piezas aquí
        // new Peon(...),
        // new Rey(...)
    };
    gardner = new Gardner(piezas);
    gardner->inicializa();

    std::thread commandThread(ejecutarComandoMovimiento); // Ejecuta los comandos de movimiento en un hilo separado

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Chess");
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    glutDisplayFunc(display);
    glutIdleFunc(idle);

    tablero = pintarTablero();

    glutMainLoop();

    commandThread.join(); // Espera a que el hilo termine (nunca ocurrirá ya que está en un bucle infinito)

    delete gardner;
    for (auto pieza : piezas) {
        delete pieza;
    }

    return 0;
}
