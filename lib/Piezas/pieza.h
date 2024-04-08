#include "../tablero.h"
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

	// Operador para igualar piezas, de momento no funciona
	void operator=(pieza p);

	// Función que destruirá la pieza (la convertirá en vacía)
	void destruir();

	// Función de actualización de las posiciones posibles 
	// Cada tipo de pieza la sobrescribe
	void updatePosPosibles(Tablero tab); 

	// Función que cambia la posición de la pieza
	bool moverPosicion(int x, int y); // Mover posicion
};

void pieza::operator=(pieza p)
{
	x = p.x;
	y = p.y;
	identificador = p.identificador;
	posiciones_validas = p.posiciones_validas;
}

bool pieza::moverPosicion(int x_final, int y_final)
{
	if (posiciones_validas[x_final][y_final] == 1)
	{
		x = x_final;
		y = y_final;
		return 1;
	}
	return 0;
}

void pieza::destruir()
{
	pieza vacia;
	vacia.identificador = 0;
	vacia.x = 0;
	vacia.y = 0;
	*this = vacia;
}