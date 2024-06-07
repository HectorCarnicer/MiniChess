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
#include "../lib/Baby.h"
#include "../lib/graficos.h"
#include "../lib/mundo.h"

// Incluye la implementación de stb_image
#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb_image.h"

// Incluye la implementación de miniaudio
#define MINIAUDIO_IMPLEMENTATION
#include "../lib/miniaudio.h"

//--------------------------------
//      Variables globales
//-------------------------------- 

bool musicPaused = false;
bool bizarreMode = false;
struct Coordenadas {
    int x, y;
    Coordenadas(int x, int y) : x(x), y(y) {}
};

#define TAMANO_TABLERO 5

//variables globales para menu
GLuint backgroundTexture;
int selectedOption = 0; // 0: ninguno, 1: Gardner, 2: Baby
ma_engine menu;

// Variables globales para el tablero y piezas
std::vector<Pieza*> piezas;
Gardner* gardner;
Baby* baby;
std::vector<std::vector<std::string>> tablero;
Color turnoActual = BLANCO; // Comienza el turno de las piezas blancas
Pieza* piezaSeleccionada = nullptr;

std::unordered_map<std::string, GLuint> pieceTextures;
ma_engine engine;
ma_engine bizarro;

bool jaque = 0;
bool clic = 0;

//--------------------------------
//          Funciones GLUT
//-------------------------------- 

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
    std::vector<std::string> pieces = { "Reinab", "Reyb", "Peonb", "Torreb", "Alfilb", "Caballob","Reinan", "Reyn", "Peonn", "Torren", "Alfiln", "Caballon" };
    for (const std::string& piece : pieces) {
        if (bizarreMode) {
            pieceTextures[piece] = loadTexture((piece + "s" + ".png").c_str());
        }
        else {
            pieceTextures[piece] = loadTexture((piece + ".png").c_str());
        }
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

    float cellWidth = 2.0f / (TAMANO_TABLERO + 1); // +1 para la columna de botones
    float cellHeight = 2.0f / TAMANO_TABLERO;

    float x1 = -1.0f + col * cellWidth;
    float y1 = 1.0f - row * cellHeight;
    float x2 = x1 + cellWidth;
    float y2 = y1 - cellHeight;

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
    float cellWidth = 2.0f / (TAMANO_TABLERO + 1); // +1 para la columna de botones
    float cellHeight = 2.0f / TAMANO_TABLERO;

    for (int i = 0; i < TAMANO_TABLERO; i++) {
        for (int j = 0; j < TAMANO_TABLERO + 1; ++j) { // +1 para la columna de botones
            // Casillas
            float x1 = -1.0f + j * cellWidth;
            float y1 = 1.0f - i * cellHeight;
            float x2 = x1 + cellWidth;
            float y2 = y1 - cellHeight;

            glBegin(GL_QUADS);
            if (j == TAMANO_TABLERO) { // Columna de botones
                if (i == 0) {
                    glColor3f(1.0f, 0.0f, 0.0f); // Rojo oscuro para el primer botón (Pause)
                }
                else if (i == 1) {
                    glColor3f(0.5f, 0.0f, 1.0f); // Verde oscuro para el segundo botón
                }
                else {
                    glColor3f(0.5f, 0.5f, 0.5f); // Azul oscuro para otros botones
                }
            }
            else if (bizarreMode) {
                // Parte superior: territorio hacker
                if (i < TAMANO_TABLERO / 2) {
                    if ((i + j) % 2 == 0) {
                        glColor3f(0.0f, 1.0f, 0.0f); // Verde para casillas claras
                    }
                    else {
                        glColor3f(0.0f, 0.5f, 0.0f); // Verde oscuro para casillas oscuras
                    }
                }
                else {
                    // Parte inferior: territorio servidor
                    if ((i + j) % 2 == 0) {
                        glColor3f(0.0f, 0.0f, 1.0f); // Azul para casillas claras
                    }
                    else {
                        glColor3f(0.0f, 0.0f, 0.5f); // Azul oscuro para casillas oscuras
                    }
                }
            }
            else {
                // Modo normal
                if ((i + j) % 2 == 0) {
                    glColor3f(1.0f, 1.0f, 1.0f); // Blanco
                }
                else {
                    glColor3f(0.5f, 0.5f, 0.5f); // Negro
                }
            }
            glVertex2f(x1, y1);
            glVertex2f(x2, y1);
            glVertex2f(x2, y2);
            glVertex2f(x1, y2);
            glEnd();

            // Piezas
            if (j < TAMANO_TABLERO && tablero[i][j] != ".") {
                drawPiece(i, j, tablero[i][j]);
            }
        }
    }

    // Dibujar el texto "Pause" en el primer botón
    // Dibujar el texto "Bizarro" en el segundo botón
    glColor3f(1.0f, 1.0f, 1.0f); // Color blanco para el texto
    renderBitmapString(-1.0f + TAMANO_TABLERO * cellWidth + cellWidth / 5, 1.0f - cellHeight / 2, GLUT_BITMAP_TIMES_ROMAN_24, "Pause");
    renderBitmapString(-1.0f + TAMANO_TABLERO * cellWidth + cellWidth / 5, 1.0f - 3 * cellHeight / 2, GLUT_BITMAP_TIMES_ROMAN_24, "Bizarro");

    // Dibujar turno actual debajo de los botones
    renderBitmapString(-1.0f + TAMANO_TABLERO * cellWidth + cellWidth / 5, 1.0f - 5.5 * cellHeight / 2, GLUT_BITMAP_TIMES_ROMAN_24, "Turno");
    if (turnoActual == BLANCO)
    {
        glColor3f(1.0f, 1.0f, 1.0f);
        renderBitmapString(-1.0f + TAMANO_TABLERO * cellWidth + cellWidth / 5, 1.0f - 6 * cellHeight / 2, GLUT_BITMAP_TIMES_ROMAN_24, "Blanco");
    }
    else
    {
        glColor3f(0.0f, 0.0f, 0.0f);
        renderBitmapString(-1.0f + TAMANO_TABLERO * cellWidth + cellWidth / 5, 1.0f - 6 * cellHeight / 2, GLUT_BITMAP_TIMES_ROMAN_24, "Negro");
    }

    // Dibujar Movimiento invalido o Moviento fuera de tablero
    if (clic == 1) {

        glColor3f(1.0f, 0.0f, 0.0f);
        renderBitmapString(-1.0f + TAMANO_TABLERO * cellWidth + cellWidth / 8, 1.0f - 7 * cellHeight / 2, GLUT_BITMAP_TIMES_ROMAN_24, "Mov Inv");
        
    }
    else {
        glColor3f(1.0f, 0.0f, 0.0f);
        renderBitmapString(-1.0f + TAMANO_TABLERO * cellWidth + cellWidth / 5, 1.0f - 7 * cellHeight / 2, GLUT_BITMAP_TIMES_ROMAN_24, "---");
        
    }
    

    // Dibujar GAME OVER si ocurre Jaque Mate
    if (jaque == 1) {

        glColor3f(1.0f,0.0f,0.0f);
        renderBitmapString(-1.0f + TAMANO_TABLERO * cellWidth*cellWidth, 1.0f - 5 * cellHeight / 2, GLUT_BITMAP_TIMES_ROMAN_24, "GAME OVER");
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
    if (selectedOption == 0) {
        drawButton(-0.4f, 0.3f, 0.8f, 0.2f, "Gardner");
        drawButton(-0.4f, -0.1f, 0.8f, 0.2f, "Baby");
    }
    if (selectedOption == 1) {
        drawButton(-0.4f, 0.3f, 0.8f, 0.2f, "Gardner");
    }
    if (selectedOption == 2) {
        drawButton(-0.4f, -0.1f, 0.8f, 0.2f, "Baby");
    }

    glutSwapBuffers();
}

void idle() {
    // Actualizar el tablero y redibujar
    tablero = pintarTablero();
    switch (selectedOption)
    {
    case 1:
        if (gardner->JaqueMate(turnoActual)) {

            std::cout << "ACABO EL JUEGO MANIN";
            jaque = 1;
            display();
            std::this_thread::sleep_for(std::chrono::seconds(10));
            exit(0);
        }
        if (gardner->detectarJaque(turnoActual)) {
            std::cout << "-----JACQUE AL REY " << (turnoActual == BLANCO ? "BLANCO" : "NEGRO") << "-----\n";
        }
        break;
    case 2:
        if (baby->JaqueMate(turnoActual)) {

            std::cout << "ACABO EL JUEGO MANIN";
            jaque = 1;
            display();
            std::this_thread::sleep_for(std::chrono::seconds(10));
            exit(0);
        }
        if (baby->detectarJaque(turnoActual)) {
            std::cout << "-----JACQUE AL REY " << (turnoActual == BLANCO ? "BLANCO" : "NEGRO") << "-----\n";
        }
        break;
    }
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
        if (selectedOption == 1) {

            gardner->nuevaJugada(turnoActual);
        }
        else if (selectedOption == 2) {

            baby->nuevaJugada(turnoActual);

        }
    }
}

void handleButtonClick(int row) {
    switch (row) {
    case 0:
        // Función del primer botón: pausar/reanudar la música
        if (musicPaused) {
            ma_engine_start(&engine);
            musicPaused = false;
            std::cout << "Música reanudada\n";
        }
        else {
            ma_engine_stop(&engine);
            musicPaused = true;
            std::cout << "Música pausada\n";
        }
        break;
    case 1:
        // Función del segundo botón: cambiar diseño de casillas y piezas
        std::cout << "\nBIZARRO ANTES=" << bizarreMode;
        bizarreMode = !bizarreMode;
        std::cout << "\nBIZARRO DESPUES=" << bizarreMode;
        loadPieceTextures();
        // Inicializar el motor de audio y la música
        if (bizarreMode == 1) {
            ma_engine_uninit(&engine);
            if (ma_engine_init(NULL, &bizarro) != MA_SUCCESS) {
                std::cerr << "Failed to initialize audio engine" << std::endl;
                exit(1);
            }
            if (ma_engine_play_sound(&bizarro, "musica_tablero1.mp3", NULL) != MA_SUCCESS) {
                std::cerr << "Failed to play background music" << std::endl;
            }
        }
        else  {
            ma_engine_uninit(&bizarro);
            if (ma_engine_init(NULL, &engine) != MA_SUCCESS) {
                std::cerr << "Failed to initialize audio engine" << std::endl;
                exit(1);
            }
            if (ma_engine_play_sound(&engine, "musica_tablero2.mp3", NULL) != MA_SUCCESS) {
                std::cerr << "Failed to play background music" << std::endl;
            }
        }
        std::cout << "Modo bizarro activado\n";
        glutPostRedisplay();
        break;
        // Añadir más casos según el número de botones
    default:
        std::cout << "Botón desconocido\n";
        break;
    }
}

void mouseClick(int button, int state, int x, int y) {
    if (!(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)) { return; }
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    int squareWidth = windowWidth / (TAMANO_TABLERO + 1); // +1 para la columna de botones
    int squareHeight = windowHeight / TAMANO_TABLERO;
    int col = x / squareWidth;
    int row = y / squareHeight;

    // Switch basado en la opción seleccionada
    switch (selectedOption) {
    case 0:
    case 1:
        // Lógica para el jugador humano
        if (row >= 0 && row < TAMANO_TABLERO) {
            if (col >= 0 && col < TAMANO_TABLERO) {
                // Logica para seleccionar y mover piezas en el tablero


                Coordenadas clickPos{ col, row };
                if (piezaSeleccionada == nullptr) {
                    // Seleccionar una pieza
                    for (Pieza* pieza : piezas) {
                        if (!pieza) continue;
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
               /* if (gardner->detectarJaque(turnoActual) && piezaSeleccionada->nombreDeClase() != "Rey") {
                    return;
                }*/
                else {
                    // Mover la pieza seleccionada
                    int nuevoX = col;
                    int nuevoY = row;

                   

                    if (piezaSeleccionada->nombreDeClase() == "Rey") {
                        int posX = 0, posY = 0;
                        piezaSeleccionada->obtenerPosicion(posX, posY);
                        piezaSeleccionada->mover(nuevoX, nuevoY);
                        bool jaque = gardner->detectarJaque(turnoActual);
                        piezaSeleccionada->mover(posX, posY);

                        if (jaque) {
                            system("cls");
                            std::cout << "MOVIMIENTO ILEGAL\n";
                            return;
                        }
                        piezaSeleccionada->mover(posX, posY);
                    }



                    if (gardner->promocion(piezaSeleccionada->obtenerColor(), nuevoX, nuevoY, piezaSeleccionada)) {
                        gardner->nuevaPieza(new Reina(nuevoX, nuevoY, turnoActual, TAMANO_TABLERO));
                        turnoActual = (turnoActual == BLANCO) ? NEGRO : BLANCO;
                        system("cls");
                        return;
                    }

                    if (gardner && !gardner->posicionOcupada(nuevoX, nuevoY) && gardner->caminoLibre(piezaSeleccionada, nuevoX, nuevoY)) {
                        if (piezaSeleccionada->mover(nuevoX, nuevoY)) {
                            turnoActual = (turnoActual == BLANCO) ? NEGRO : BLANCO;
                            piezaSeleccionada = nullptr;
                            std::cout << "Pieza movida a (" << nuevoX << ", " << nuevoY << ")\n";
                            clic = 0;
                            display();
                        }
                    }
                   
                    else if (gardner && gardner->atacarPieza(piezaSeleccionada->obtenerColor(), nuevoX, nuevoY, piezaSeleccionada)) {
                        piezaSeleccionada->mover(nuevoX, nuevoY);
                        turnoActual = (turnoActual == BLANCO) ? NEGRO : BLANCO;
                        piezaSeleccionada = nullptr;
                        std::cout << "Pieza atacada en (" << nuevoX << ", " << nuevoY << ")\n";
                        clic = 0;
                        display();
                    }
                    else {
                        std::cout << "-----Movimiento inválido o posición ocupada-----\n";
                        clickPos = { 0,0 };
                        piezaSeleccionada = nullptr;
                        clic = 1;
                        display();

                    }
                   
                    glutPostRedisplay();
                }
            }
            else if (col == TAMANO_TABLERO) {
                // Logica para manejar los clics en la columna de botones
                handleButtonClick(row);
            }
            else {
                std::cout << "Click fuera del tablero\n";
            }
        }
        break;

    case 2:
        
        /*if (baby->detectarJaque(turnoActual)) {
            std::cout << "-----SE ACABO LA PARTIDA WEY-----\n";
            jaque = 1;
            display();
            return;
        }*/

        if (row >= 0 && row < TAMANO_TABLERO) {
            if (col >= 0 && col < TAMANO_TABLERO) {
                // Logica para seleccionar y mover piezas en el tablero
                Coordenadas clickPos{ col, row };

                if (piezaSeleccionada == nullptr) {
                    // Seleccionar una pieza
                    for (Pieza* pieza : piezas) {
                        if (!pieza) continue;
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


                    if (piezaSeleccionada->nombreDeClase() == "Rey") {
                        int posX = 0, posY = 0;
                        piezaSeleccionada->obtenerPosicion(posX, posY);
                        piezaSeleccionada->mover(nuevoX, nuevoY);
                        bool jaque = baby->detectarJaque(turnoActual);
                        piezaSeleccionada->mover(posX, posY);

                        if (jaque) {
                            system("cls");
                            std::cout << "MOVIMIENTO ILEGAL\n";
                            return;
                        }
                        piezaSeleccionada->mover(posX, posY);
                    }



                    if (baby->promocion(piezaSeleccionada->obtenerColor(), nuevoX, nuevoY, piezaSeleccionada)) {
                        baby->nuevaPieza(new Reina(nuevoX, nuevoY, turnoActual, TAMANO_TABLERO));
                        turnoActual = (turnoActual == BLANCO) ? NEGRO : BLANCO;
                        system("cls");
                        return;
                    }

                    if (baby && !baby->posicionOcupada(nuevoX, nuevoY) && baby->caminoLibre(piezaSeleccionada, nuevoX, nuevoY)) {
                        if (piezaSeleccionada->mover(nuevoX, nuevoY)) {
                            turnoActual = (turnoActual == BLANCO) ? NEGRO : BLANCO;
                            piezaSeleccionada = nullptr;
                            std::cout << "Pieza movida a (" << nuevoX << ", " << nuevoY << ")\n";
                            clic = 0;
                            display();
                        }
                    }
                    else if (baby && baby->atacarPieza(piezaSeleccionada->obtenerColor(), nuevoX, nuevoY, piezaSeleccionada)) {
                        piezaSeleccionada->mover(nuevoX, nuevoY);
                        turnoActual = (turnoActual == BLANCO) ? NEGRO : BLANCO;
                        piezaSeleccionada = nullptr;
                        std::cout << "Pieza atacada en (" << nuevoX << ", " << nuevoY << ")\n";
                        clic = 0;
                        display();
                    }
                    else {
                        std::cout << "-----Movimiento inválido o posición ocupada-----\n";
                        clic = 1;
                        display();
                    }
                    glutPostRedisplay();
                }
            }
            else if (col == TAMANO_TABLERO) {
                // Logica para manejar los clics en la columna de botones
                handleButtonClick(row);
            }
            else {
                std::cout << "Click fuera del tablero\n";
            }
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
        baby = new Baby(piezas);
        baby->inicializa();
    }
}

//solo para que lo reconozca mouseClickMenu, está definido más abajo
void cambiarValor(int x);

void esperaPostSeleccion() {
    displayMenu(); //para poner a verde el botón
    std::this_thread::sleep_for(std::chrono::seconds(2));
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
    // Inicializar el tablero con las fichas
    inicializarJuego();
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Habilitar blending para transparencia
    loadPieceTextures();

    // Inicializar el motor de audio y la música
    if (ma_engine_init(NULL, &engine) != MA_SUCCESS) {
        std::cerr << "Failed to initialize audio engine" << std::endl;
        exit(1);
    }
    if (ma_engine_play_sound(&engine, "musica_tablero2.mp3", NULL) != MA_SUCCESS) {
        std::cerr << "Failed to play background music" << std::endl;
    }
    
    
}

void initMenu() {
    //carga del fondo 
    backgroundTexture = loadTextureMenu("fondo5.png");
    if (backgroundTexture == 0) {
        printf("Error loading background texture\n");
        exit(EXIT_FAILURE);
    }

    //musica_menu
    if (ma_engine_init(NULL, &menu) != MA_SUCCESS) {
        std::cerr << "Failed to initialize audio engine" << std::endl;
        exit(1);
    }
    if (ma_engine_play_sound(&menu, "musica_menu.mp3", NULL) != MA_SUCCESS) {
        std::cerr << "Failed to play background music" << std::endl;
    }
}

void cambiarValor(int x) {
    std::cout << "valor de selectedOption antes de cambiar valor= " << selectedOption << "\n";
    selectedOption = x;
    std::cout << "valor de selectedOption despues de cambiar valor= " << selectedOption << "\n";

    //quitar la musica de menu
    ma_engine_uninit(&menu);

    //esperar 1s para pasar a tablero y poner boton verde
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

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'f':
    case 'F':
        glutFullScreen();
        break;
    case 27: // Esc key
        glutReshapeWindow(600, 600);
        glutPositionWindow((glutGet(GLUT_SCREEN_WIDTH) - 640) / 2,
            (glutGet(GLUT_SCREEN_HEIGHT) - 480) / 2);
        break;
    default:
        break;
    }
}

int main(int argc, char** argv) {
   
    //std::thread commandThread(ejecutarComandoMovimiento); // Ejecuta los comandos de movimiento en un hilo separado

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Chess");

 
    std::cout << "MENU: valor de selectedOption antes de inicilaizaJuego: " << selectedOption << "\n";
    initMenu();
    glutDisplayFunc(displayMenu);
    glutReshapeFunc(reshapeMenu);
    glutMouseFunc(mouseClickMenu);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    

    //commandThread.join(); // Espera a que el hilo termine (nunca ocurrirá ya que está en un bucle infinito)

    
    


    // Limpieza de memoria
    delete gardner;
    delete baby;
    for (auto pieza : piezas) {
        delete pieza;
    }
    return 0;
}
