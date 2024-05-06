#ifndef PIEZA_H
#define PIEZA_H

#include <iostream>
#include <string>

// Enumeraci�n para los colores de las piezas
enum Color { BLANCO, NEGRO };

/*
* EXLICACI�N *

Pieza es una clase interfaz que se ocupa �nicamente de las comunicaciones 
de las piezas con el resto del c�digo.

EL calificador virtual implica que se usa el enlace din�mico aka que se pueden redefinir las funciones
en las clases derivadas sin problema. EL calificador override en las funciones redefinidas de la clase 
derivada hace que lo compruebe y funcione correctamente. 
El = 0 en las funciones implica que cada clase que herede de Pieza debe redefinir la funci�n mover().
    
*/

class Pieza {
protected:
    int x, y; // Posici�n de la pieza en un tablero bidimensional
    Color color; // Color de la pieza
    int TAMANO_TABLERO = 8; // Tama�o del tablero

public:
    // Constructor que inicializa la posici�n de la pieza y el color
    Pieza(int posX, int posY, Color color, int TAM_TABLERO) 
        : x(posX), y(posY), color(color), TAMANO_TABLERO(TAM_TABLERO) {}

    // M�todo para mover la pieza a una nueva posici�n
    virtual bool mover(int nuevoX, int nuevoY) = 0; 

    // M�todo para imprimir la posici�n actual de la pieza
    void mostrarPosicion();

    // M�todo virtual puro para obtener el nombre de la clase
    virtual std::string nombreDeClase() const = 0;

    // M�todo para obtener la posici�n de la pieza
    void obtenerPosicion(int& posX, int& posY) const {
        posX = x;
        posY = y;
    }

    // M�todo para obtener el color de la pieza
    Color obtenerColor() const;
    void moverPiezaUsuario();
}
;



#endif // PIEZA_H