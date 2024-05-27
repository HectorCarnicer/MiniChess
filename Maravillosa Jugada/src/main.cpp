#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include "../lib/freeglut.h"
#include "../lib/Pieza.h"
#include "../lib/Peon.h"
#include "../lib/Rey.h"
#include"../lib/Reina.h"
#include "../lib/Caballo.h"
#include "../lib/Gardner.h"
#include "../lib/graficos.h"

struct Coordenadas {
    int x, y;
    Coordenadas(int x, int y) : x(x), y(y) {}
};

#define TAMANO_TABLERO 5

// Variables globales para el tablero y piezas
std::vector<Pieza*> piezas;
Gardner* gardner;
std::vector<std::vector<std::string>> tablero;
Color turnoActual = BLANCO; // Comienza el turno de las piezas blancas
Pieza* piezaSeleccionada = nullptr;

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
    float cellSize = 2.0f / TAMANO_TABLERO;

    for (int i = 0; i < TAMANO_TABLERO; ++i) {
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

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int squareSize = glutGet(GLUT_WINDOW_WIDTH) / TAMANO_TABLERO;
        int col = x / squareSize;
        int row = y / squareSize;

        if (gardner->detectarJaque(turnoActual)) {
            std::cout << "-----SE ACABO LA PARTIDA WEY-----\n";
            return;
        }

        // Check if the click is within the bounds of the board
        if (row >= 0 && row < TAMANO_TABLERO && col >= 0 && col < TAMANO_TABLERO) {
            Coordenadas clickPos{ col, row };

            if (piezaSeleccionada == nullptr) {
                // Selecting a piece
                for (Pieza* pieza : piezas) {
                    int px, py;
                    pieza->obtenerPosicion(px, py);
                    if (px == col && py == row) {
                        if (pieza->obtenerColor() == turnoActual) {
                            piezaSeleccionada = pieza;
                            std::cout << "Pieza seleccionada en (" << col << ", " << row << ")\n";
                        }
                        break;
                    }
                }
            }
            else {
                // Moving the selected piece
                int nuevoX = col;
                int nuevoY = row;

                if (!gardner->posicionOcupada(nuevoX, nuevoY) && gardner->caminoLibre(piezaSeleccionada, nuevoX, nuevoY)) {
                    if (piezaSeleccionada->mover(nuevoX, nuevoY)) {
                        turnoActual = (turnoActual == BLANCO) ? NEGRO : BLANCO;
                        piezaSeleccionada = nullptr;
                        std::cout << "Pieza movida a (" << nuevoX << ", " << nuevoY << ")\n";
                    }
                }
                else if (gardner->atacarPieza(piezaSeleccionada->obtenerColor(), nuevoX, nuevoY)) {
                    piezaSeleccionada->mover(nuevoX, nuevoY);
                    turnoActual = (turnoActual == BLANCO) ? NEGRO : BLANCO;
                    piezaSeleccionada = nullptr;
                    std::cout << "Pieza atacada en (" << nuevoX << ", " << nuevoY << ")\n";
                }
                else {
                    std::cout << "-----Movimiento inválido o posición ocupada-----\n";
                }
                glutPostRedisplay();
            }
        }
        else {
            std::cout << "Click fuera del tablero\n";
        }
    }
}

int main(int argc, char** argv) {
   
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
    glutMouseFunc(mouseClick);

    tablero = pintarTablero();

    glutMainLoop();

    commandThread.join(); // Espera a que el hilo termine (nunca ocurrirá ya que está en un bucle infinito)

    delete gardner;
    for (auto pieza : piezas) {
        delete pieza;
    }

    return 0;
}
