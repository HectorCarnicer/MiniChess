#ifndef _BABY_H_
#define _BABY_H_

#include "mundo.h"
#include "../lib/piezas/rey.h"
#include "../lib/piezas/pieza.h"
#include "../lib/piezas/peon.h"
#include "../lib/piezas/alfil.h"
#include "../lib/piezas/torre.h"
#include "../lib/piezas/caballo.h"
#include "../lib/piezas/reina.h"

// Tamaño del baby
#define TAM_X 5
#define TAM_Y 5


class Baby : public Mundo
{

public:
	// Constructor
	Baby(std::vector<Pieza*>& piezas) : Mundo(piezas, TAM_X, TAM_Y) {}

	// Destructor
	~Baby();

	// Inicializador, es decir, creador de las piezas
	void inicializa() override;

	// Impresor
	void imprimirTablero() override;
};

#endif


