#ifndef PIEZA_H
#define PIEZA_H

#include <iostream>
#include <string>



// Enumeración para los colores de las piezas
enum Color { BLANCO = 1, NEGRO  = -1};

// Enumeración de tipos de clase
enum ClaseP { PEON, REY, REINA, ALFIL, TORRE, CABALLO };

// Struct para manejar las posiciones: ayuda a no repetir código
struct Coord
{
    // Constructor
    Coord(int x, int y) : x(x), y(y) {}

    // Constructor copia
    Coord(const Coord& pos) : x(pos.x), y(pos.y) {}

    // Asignación
    Coord& operator=(const Coord& pos)
    {
        this->x = pos.x;
        this->y = pos.y;
        return *this;
    }

    // Función que devuelve si la coordenada está dentro de unos límites
    bool coordValid(int tam_x, int tam_y) 
    {
        // Devuelve si las coordenadas están dentro de los límites partiendo de 0
        return (x >= 0 && x < tam_x && y >= 0 && y < tam_y);
    }

    // Parámetros
    int x, y;
};

// Operador == en coordenadas
inline bool operator==(Coord c1, Coord c2)
{
    return (c1.x == c2.x && c1.y == c2.y);
}  
inline std::ostream& operator<< (std::ostream& o, const Coord c)
{
    o << "( " << c.x << ", " << c.y << " )";
    return o;
}

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


public:
    /*
    * CONSTRUCTOR
    */

    // Constructor que inicializa la posición de la pieza, el color y el tablero de posiciones posibles
    Pieza(Coord pos, Color color, ClaseP clase, int tam_x, int tam_y) 
        : pos(pos), color(color), clase (clase), tam_x(tam_x), tam_y(tam_y)
    {
        Color color_contrario = (color == BLANCO) ? NEGRO : BLANCO;
        pos_posibles = new bool* [tam_x];
        for (int i = 0; i < tam_x; i++)
        {
            pos_posibles[i] = new bool[tam_y];
        }
    }
     //TODO: Destructor
    ~Pieza()
    {
        for (int i = 0; i < tam_x; i++)
        {
            delete pos_posibles[i];
        }
        delete pos_posibles;
    }

    /*
    * MOVIMIENTO Y POSICIONES POSIBLES
    */

    // Método para mover la pieza a una nueva posición
    virtual bool mover(Coord nueva_pos); 

    // Método que calcula las posiciones 
    virtual void calcularPosPosibles(int** posActualesPiezas) = 0;

    /*
    * GETTERS
    */

    // Método para obtener la posición de la pieza
    Coord obtenerPosicion() const { return pos; }

    // Método para obtener el color de la pieza
    Color obtenerColor() const { return color; }

    //Método para obtener el tipo de clase
    ClaseP obtenerClase() const { return clase; }

    // Método para obtener si una coordenada está en las pos_posibles
    bool posPosible(Coord _pos)
    {
        return pos_posibles[_pos.x][_pos.y];
    }

    // Método para devolver un string con el tipo
    std::string obtenerNomClase() const
    {
        switch (clase)
        {
        case PEON: return "PEON";
        case REY: return "REY";
        case REINA: return "REINA";
        case ALFIL: return "ALFIL";
        case TORRE: return "TORRE";
        case CABALLO:return "CABALLO";
        }
    }
    void moverPiezaUsuario();
protected:
    // Posición de la pieza en un tablero bidimensional
    Coord pos;
    // Color de la pieza
    Color color = BLANCO; // Por defecto, se cambia en el constructor
    // Color contrario de la pieza para evaular casos
    Color color_contrario = NEGRO; // Por defecto, se cambia en el constructor
    // Tipo de pieza
    ClaseP clase;
    // Matriz con las posiciones posibles a las que se puede mover la pieza
    bool** pos_posibles;
    // Dimensiones del tablero en el cual está contenida
    int tam_x;
    int tam_y;
};

// Operador inserción al flujo de Pieza
inline std::ostream& operator<< (std::ostream& o, const Pieza& p)
{
    std::string col = (p.obtenerColor() == BLANCO) ? "BLANCO" : "NEGRO";
    o << p.obtenerNomClase() << " " << col << " " << p.obtenerPosicion();
    return o;
}



#endif // PIEZA_H