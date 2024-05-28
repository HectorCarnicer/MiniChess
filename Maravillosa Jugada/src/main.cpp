#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <unordered_map>
#include "../lib/freeglut.h"
#include "../lib/Pieza.h"
#include "../lib/Peon.h"
#include "../lib/Rey.h"
#include "../lib/Reina.h"
#include "../lib/Caballo.h"
#include "../lib/Gardner.h"
#include "../lib/graficos.h"

// Incluye la implementación de stb_image
#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb_image.h"

// Incluye la implementación de miniaudio
#define MINIAUDIO_IMPLEMENTATION
#include "../lib/miniaudio.h"

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

std::unordered_map<std::string, GLuint> pieceTextures;
ma_engine engine;

std::vector<std::vector<std::string>> pintarTablero() {
    std::vector<std::vector<std::string>> tablero(TAMANO_TABLERO, std::vector<std::string>(TAMANO_TABLERO, "."));

    for (const auto& pieza : piezas) {
        int x, y;
        pieza->obtenerPosicion(x, y);
        if (pieza->obtenerColor() == BLANCO) {
            tablero[y][x] = pieza->nombreDeClase()+"b";
        }
        else {
            tablero[y][x] = pieza->nombreDeClase() + "n";
        }

    }

    return tablero;
}

GLuint loadTexture(const char* filename) {
    int width, height, channels;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 4); // Cargar con 4 canales (RGBA)
    if (data == nullptr) {
        std::cerr << "Error loading texture " << filename << std::endl;
        exit(1);
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    return texture;
}


void loadPieceTextures() {
    std::vector<std::string> pieces = { "Reinab", "Reyb", "Peonb", "Torreb", "Alfilb", "Caballob","Reinan", "Reyn", "Peonn", "Torren", "Alfiln", "Caballon" };
    for (const std::string& piece : pieces) {
        pieceTextures[piece] = loadTexture((piece + ".png").c_str());
    }
}

void drawPiece(int row, int col, const std::string& piece) {
    if (pieceTextures.find(piece) == pieceTextures.end()) return;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, pieceTextures[piece]);

    float x1 = -1.0f + col * (2.0f / TAMANO_TABLERO);
    float y1 = 1.0f - row * (2.0f / TAMANO_TABLERO);
    float x2 = x1 + (2.0f / TAMANO_TABLERO);
    float y2 = y1 - (2.0f / TAMANO_TABLERO);

    glColor4f(1.0, 1.0, 1.0, 1.0); // Asegurarse de que el color tenga un alfa de 1.0
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex2f(x1, y1);
    glTexCoord2f(1.0, 0.0); glVertex2f(x2, y1);
    glTexCoord2f(1.0, 1.0); glVertex2f(x2, y2);
    glTexCoord2f(0.0, 1.0); glVertex2f(x1, y2);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}


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
                drawPiece(i, j, tablero[i][j]);
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

        if (row >= 0 && row < TAMANO_TABLERO && col >= 0 && col < TAMANO_TABLERO) {
            Coordenadas clickPos{ col, row };

            if (piezaSeleccionada == nullptr) {
                // Seleccionar una pieza
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
                // Mover la pieza seleccionada
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

void init() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Habilitar blending para transparencia
    loadPieceTextures();

    if (ma_engine_init(NULL, &engine) != MA_SUCCESS) {
        std::cerr << "Failed to initialize audio engine" << std::endl;
        exit(1);
    }
    if (ma_engine_play_sound(&engine, "background_music.mp3", NULL) != MA_SUCCESS) {
        std::cerr << "Failed to play background music" << std::endl;
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

    init();

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMouseFunc(mouseClick);

    tablero = pintarTablero();

    glutMainLoop();

    commandThread.join(); // Espera a que el hilo termine (nunca ocurrirá ya que está en un bucle infinito)

    ma_engine_uninit(&engine);

    delete gardner;
    for (auto pieza : piezas) {
        delete pieza;
    }

    return 0;
}
