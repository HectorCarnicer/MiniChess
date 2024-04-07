#include "../tablero.h"
#include "../Basic/posicion.h"

class pieza
{
public:
	// Constructor de la pieza predeterminada
	pieza(Tablero tab, bool color)
	{

	}

	void operator=(pieza p);

	void destruir();
	void updatePosPosibles(Tablero tab); // Actualiza posiciones posibles
	void moverPosicion(int x, int y); // Mover posicion
	// Par�metros de la pieza
	int x, y;
	bool ** posiciones_validas;
	int identificador; // N�mero que identifica la pieza 
};

void pieza::operator=(pieza p)
{
	x = p.x;
	y = p.y;
	identificador = p.identificador;
	posiciones_validas = p.posiciones_validas;
}