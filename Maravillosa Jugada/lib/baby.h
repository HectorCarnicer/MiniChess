#ifndef _BABY_H_
#define _BABY_H_

#include "mundo.h"

class Baby : public Mundo
{

public:
	// Constructor
	Baby(std::vector<Pieza*>& piezas) : Mundo(piezas) {}

	// Destructor
	~Baby();

	// Inicializador, es decir, creador de las piezas
	void inicializa() override;

	// Impresor
	void imprimirTablero() override;
	//bool caminoLibre(Pieza* pieza, int xFinal, int yFinal);

	// Getter de tamaño
	int getTam() { return TAMANO_TABLERO; }

	//Nueva Jugada
	void nuevaJugada(Color turnoActual) override;
private:
	// El tamaño del tablero Baby
	static const int TAMANO_TABLERO = 5;
};
#endif


