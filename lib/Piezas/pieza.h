#include "../tablero.h"

#define PEON_B 1
#define PEON_N -1
#define TORRE_B 2
#define TORRE_N -2
#define CABALLO_B 3
#define CABALLO_N -3
#define ALFIL_B 4
#define ALFIL_N -4
#define REINA_B 5
#define REINA_N -5
#define REY_B 6
#define REY_N -6

/*
Clase base de todas las piezas, que contiene los m�todos y los par�metros comunes a todas
*/


class pieza
{
public:
	// Par�metros que identifican a la pieza
	int x, y;
	bool** posiciones_validas;
	int identificador; // N�mero que identifica la pieza (el signo dice que color, el valor qu� pieza)

	// Operador para igualar piezas, de momento no funciona
	void operator=(pieza p);

	// Funci�n que destruir� la pieza (la convertir� en vac�a)
	void destruir();

	// Funci�n de actualizaci�n de las posiciones posibles 
	// Cada tipo de pieza la sobrescribe
	void updatePosPosibles(Tablero tab); 

	// Funci�n que cambia la posici�n de la pieza
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