#include "../tablero.h"
#include "../Basic/posicion.h"
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

	// Operador para iguaalar piezas, puede ser muy �til en otras funciones
	void operator=(pieza p);

	// Funci�n que destruir� la pieza (la convertir� en vac�a)
	void destruir();

	// Funci�n de actualizaci�n de las posiciones posibles 
	// Cada tipo de pieza la sobrescribe
	void updatePosPosibles(Tablero tab); 

	// Funci�n que cambia la posici�n de la pieza
	void moverPosicion(int x, int y); // Mover posicion
	};

void pieza::operator=(pieza p)
{
	x = p.x;
	y = p.y;
	identificador = p.identificador;
	posiciones_validas = p.posiciones_validas;
}