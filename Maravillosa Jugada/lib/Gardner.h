#ifndef _GARDNER_H_
#define _GARDNER_H_

#include "../lib/rey.h"
#include "../lib/pieza.h"
#include "../lib/peon.h"
#include "alfil.h"
#include "../lib/alfil.h"
#include "torre.h"
#include "caballo.h"
#include "reina.h"


/*
* Esta clase hereda de mundo e implementa el modo de juego Gardner con sus reglas espec�ficas
*/

class Gardner : public Mundo
{

public:
	// Constructor
	Gardner(std::vector<Pieza*>& piezas) : Mundo(piezas) {}

	// Destructor
	~Gardner();
	
	// Inicializador, es decir, creador de las piezas
	void inicializa() override;

	// Impresor
	void imprimirTablero() override;
	//bool caminoLibre(Pieza* pieza, int xFinal, int yFinal);

	// Getter de tama�o
	int getTam() { return TAMANO_TABLERO; }

	//Nueva Jugada
	void nuevaJugada(Color turnoActual) override;
private: 
	// El tama�o del tablero Gardner
	static const int TAMANO_TABLERO = 5;
};

#endif

