#ifndef PIEZA_H
#define PIEZA_H

#include <iostream>
#include <string>

// Enumeración para los colores de las piezas
enum Color { BLANCO, NEGRO };

/*
* EXLICACIÓN *

Pieza es una clase interfaz que se ocupa únicamente de las comunicaciones 
de las piezas con el resto del código.

EL calificador virtual implica que se usa el enlace dinámico aka que se pueden redefinir las funciones
en las clases derivadas sin problema. EL calificador override en las funciones redefinidas de la clase 
derivada hace que lo compruebe y funcione correctamente. 
El = 0 en las funciones implica que cada clase que herede de Pieza debe redefinir la función mover().
    
*/

class Pieza {
protected:
    int x, y; // Posición de la pieza en un tablero bidimensional
    Color color; // Color de la pieza
    int TAMANO_TABLERO = 8; // Tamaño del tablero

public:
    // Constructor que inicializa la posición de la pieza y el color
    Pieza(int posX, int posY, Color color, int TAM_TABLERO) 
        : x(posX), y(posY), color(color), TAMANO_TABLERO(TAM_TABLERO) {}

    // Método para mover la pieza a una nueva posición
    virtual bool mover(int nuevoX, int nuevoY) = 0; 

    // Método para imprimir la posición actual de la pieza
    void mostrarPosicion();

    // Método virtual puro para obtener el nombre de la clase
    virtual std::string nombreDeClase() const = 0;

    // Método para obtener la posición de la pieza
    void obtenerPosicion(int& posX, int& posY) const {
        posX = x;
        posY = y;
    }

    // Método para obtener el color de la pieza
    Color obtenerColor() const;
    void moverPiezaUsuario();
}
;



#endif // PIEZA_H