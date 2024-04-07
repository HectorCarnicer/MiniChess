#include "../tablero.h"
#include "../Basic/posicion.h"
/*
Clase base de todas las piezas, que contiene los métodos y los parámetros comunes a todas
*/


class pieza
{
public:
	// Parámetros que identifican a la pieza
	int x, y;
	bool** posiciones_validas;
	int identificador; // Número que identifica la pieza (el signo dice que color, el valor qué pieza)

	// Operador para iguaalar piezas, puede ser muy útil en otras funciones
	void operator=(pieza p);

	// Función que destruirá la pieza (la convertirá en vacía)
	void destruir();

	// Función de actualización de las posiciones posibles 
	// Cada tipo de pieza la sobrescribe
	void updatePosPosibles(Tablero tab); 

	// Función que cambia la posición de la pieza
	void moverPosicion(int x, int y); // Mover posicion
	};

void pieza::operator=(pieza p)
{
	x = p.x;
	y = p.y;
	identificador = p.identificador;
	posiciones_validas = p.posiciones_validas;
}