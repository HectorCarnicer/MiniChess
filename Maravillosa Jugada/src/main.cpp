#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <unordered_map>
#include "../lib/freeglut.h"
#include "../lib/ETSIDI.h"
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

//variables globales para menu
GLuint backgroundTexture;
//valores temporales
int selectedOption = 0; // 0: ninguno, 1: Gardner, 2: Baby


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
            //std::cout<< pieza->nombreDeClase()<< std::endl;
        }
        else if(pieza->obtenerColor() == NEGRO) {
            tablero[y][x] = pieza->nombreDeClase()+"n";
            //std::cout << pieza->nombreDeClase() << std::endl;
        }

    }

    return tablero;
}

void clearWindow() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Limpiar el buffer de color y profundidad
    glLoadIdentity(); // Restablecer la matriz de modelo-vista
   // glutSwapBuffers(); // Intercambiar los buffers (si estás usando doble buffer)

}

GLuint loadTextureMenu(const char* filename) {
    int width, height, channels;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);
    if (data == nullptr) {
        return 0;
    }

    // Voltear la imagen verticalmente
    int widthInBytes = width * channels;
    unsigned char* top = nullptr;
    unsigned char* bottom = nullptr;
    unsigned char temp = 0;
    int halfHeight = height / 2;

    for (int row = 0; row < halfHeight; row++) {
        top = data + row * widthInBytes;
        bottom = data + (height - row - 1) * widthInBytes;
        for (int col = 0; col < widthInBytes; col++) {
            temp = *top;
            *top = *bottom;
            *bottom = temp;
            top++;
            bottom++;
        }
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, (channels == 4) ? GL_RGBA : GL_RGB, width, height, 0, (channels == 4) ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    return texture;
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
    std::vector<std::string> pieces = { "reinab", "Reyb", "Peonb", "Torreb", "Alfilb", "Caballob","reinan", "Reyn", "Peonn", "Torren", "Alfiln", "Caballon" };
    for (const std::string& piece : pieces) {
        pieceTextures[piece] = loadTexture((piece + ".png").c_str());
    }
}

// Función para dibujar texto
void renderBitmapString(float x, float y, void* font, const char* string) {
    const char* c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

// Función para dibujar el fondo
void drawBackground() {
    glEnable(GL_TEXTURE_2D);
    glClearColor(1.0, 1.0, 1.0, 1.0); // Fondo blanco
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, backgroundTexture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, 1.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

// Función para dibujar botones
void drawButton(float x, float y, float width, float height ,const char* label ) {

    std::cout << "DRAW_BUTTON\n";

    // Dibujar el botón
    if (selectedOption == 1 || selectedOption == 2) {
        glClearColor(1.0f, 1.0f, 1.0f,1.0f);
        std::cout << "ha entrado para poner a VERDE\n";
        glColor3f(0.0f, 1.0f, 0.0f); //Verde
    }
    else {
        std::cout << "ha entrado para ponera BLANCO\n";
        glColor3f(1.0f, 1.0f, 1.0f); // Blanco 
    }
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y - height);
    glVertex2f(x, y - height);
    glEnd();

    //Dibujar contorno del botón
    glColor3f(0.0f, 0.0f, 0.0f); // Negro 
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y - height);
    glVertex2f(x, y - height);
    glEnd();

    // Dibujar el texto del botón
    glColor3f(0.0f, 0.0f, 0.0f); // Negro para el texto
    renderBitmapString(x + width / 3, y - height / 2, GLUT_BITMAP_TIMES_ROMAN_24, label);

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
            //casillas
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

            //piezas
            if (tablero[i][j] != ".") {
                drawPiece(i, j, tablero[i][j]);
            }
        }
    }

    glutSwapBuffers();
}

void displayMenu() {

    //limpiar ventana
    clearWindow();

    // Habilitar y configurar la textura del fondo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, backgroundTexture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // Asegúrate de que la textura reemplace el color del fondo

    
    // Dibujar el fondo
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, 1.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D); // Deshabilitar la textura después de usarla

    // Dibujar botones
    drawButton(-0.4f, 0.3f, 0.8f, 0.2f, "Gardner");
    drawButton(-0.4f, -0.1f, 0.8f, 0.2f, "Baby");
   
    glutSwapBuffers();
}

void idle() {
    // Actualizar el tablero y redibujar
    tablero = pintarTablero();
    glutPostRedisplay();
}

void reshapeMenu(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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

//cuando pulsas boton correctamente, vas aquí e inicializas juego, actualizando variable mainMenuTablero==1
void inicializarJuego() {
    if (selectedOption == 1) {
        std::cout << "ha entrado en inicializaJuego gardner\n";
        gardner = new Gardner(piezas);
        gardner->inicializa();
    }
    else if (selectedOption == 2) {
        std::cout << "ha entrado en inicializaJuego baby\n";
        //meter baby
    }
}

//solo para que lo reconozca mouseClickMenu, está definido más abajo
void cambiarValor(int x);

void esperaPostSeleccion() {
    
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void mouseClickMenu(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Convertir coordenadas de ventana a coordenadas de OpenGL
        float fx = (float)x / (glutGet(GLUT_WINDOW_WIDTH) / 2) - 1.0f;
        float fy = 1.0f - (float)y / (glutGet(GLUT_WINDOW_HEIGHT) / 2);

        // Verificar si se hizo clic en algún botón
        if (fx >= -0.4f && fx <= 0.4f) {
            if (fy <= 0.3f && fy >= 0.1f) {
                std::cout << "gardner\n";
                //esperaPostSeleccion();
                cambiarValor(1);           
            }
            else if (fy <= -0.1f && fy >= -0.3f) {
                std::cout << "baby\n";
                cambiarValor(2);
            }
        }
    }
}

void init() {
    inicializarJuego();
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Habilitar blending para transparencia
    loadPieceTextures();

    if (ma_engine_init(NULL, &engine) != MA_SUCCESS) {
        std::cerr << "Failed to initialize audio engine" << std::endl;
        exit(1);
    }
    /*if (ma_engine_play_sound(&engine, "background_music.mp3", NULL) != MA_SUCCESS) {
        std::cerr << "Failed to play background music" << std::endl;
    }*/
}

void initMenu() {
    //carga del fondo 
    backgroundTexture = loadTextureMenu("fondo5.png");
    if (backgroundTexture == 0) {
        printf("Error loading background texture\n");
        exit(EXIT_FAILURE);
    }

    //?¿cambiar musica
    if (ma_engine_init(NULL, &engine) != MA_SUCCESS) {
        std::cerr << "Failed to initialize audio engine" << std::endl;
        exit(1);
    }
    if (ma_engine_play_sound(&engine, "background_music.mp3", NULL) != MA_SUCCESS) {
        std::cerr << "Failed to play background music" << std::endl;
    }
}

void cambiarValor(int x) {
    std::cout << "valor de selectedOption antes de cambiar valor= " << selectedOption << "\n";
    selectedOption = x;
    std::cout << "valor de selectedOption despues de cambiar valor= " << selectedOption << "\n";

    esperaPostSeleccion();

    // Reconfigurar las funciones de GLUT según el nuevo estado
    switch (selectedOption) {
    case 0:
        std::cout << "MENU: valor de selectedOption antes de inicilaizaJuego= " << selectedOption << "\n";
        initMenu();
        glutDisplayFunc(displayMenu);
        glutReshapeFunc(reshapeMenu);
        glutMouseFunc(mouseClickMenu);
        break;
    case 1:
        std::cout << "MENU: valor de selectedOption despues de inicilaizaJuego= " << selectedOption << "\n";
        init();
        glutDisplayFunc(display);
        glutIdleFunc(idle);
        glutMouseFunc(mouseClick);
        tablero=pintarTablero();
        break;
    case 2:
        std::cout << "MENU: valor de selectedOption despues de inicilaizaJuego= " << selectedOption << "\n";
        init();
        glutDisplayFunc(display);
        glutIdleFunc(idle);
        glutMouseFunc(mouseClick);
        tablero=pintarTablero();
        break;
    }

    // Forzar redibujado
    glutPostRedisplay();
}

int main(int argc, char** argv) {
   
   // std::thread commandThread(ejecutarComandoMovimiento); // Ejecuta los comandos de movimiento en un hilo separado

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Chess");

 
    std::cout << "MENU: valor de selectedOption antes de inicilaizaJuego= " << selectedOption << "\n";
    initMenu();
    glutDisplayFunc(displayMenu);
    glutReshapeFunc(reshapeMenu);
    glutMouseFunc(mouseClickMenu);
        
    glutMainLoop();
    

   // commandThread.join(); // Espera a que el hilo termine (nunca ocurrirá ya que está en un bucle infinito)

    ma_engine_uninit(&engine);

    delete gardner;
    for (auto pieza : piezas) {
        delete pieza;
    }

    return 0;
}
