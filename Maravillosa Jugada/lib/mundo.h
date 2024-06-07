// Corrección en la definición del macro de inclusión
#ifndef MUNDO_H
#define MUNDO_H

#include <vector>
#include <algorithm>
#include "pieza.h"

// Interfaz del mundo, de ella heredan los distintos modos de juego
class Mundo {
public:

	// Constructor
	Mundo(std::vector<Pieza*>& piezas) : piezas(piezas){}
	// Métodos globales
	bool posicionOcupada(int x, int y);
	bool posicionOcupadaRey(Color color,int x, int y);
	bool posicionOcupadaMenosRey(Color color, int x, int y);


	void comerPieza(int x, int y);
	void nuevaPieza(Pieza* p) { piezas.push_back(p); }
	bool atacarPieza(Color color,int x, int y, Pieza* piezaSeleccionada);
	bool atacarPiezaRey(Pieza* pieza, int nuevoX, int nuevoY);
	bool atacarPiezaRey2(Pieza* pieza, int nuevoX, int nuevoY);


	bool detectarJaque(Color& turnoActual);
	bool promocion(Color color, int x, int y, Pieza* piezaSeleccionada);
	bool JaqueMate(Color& turnoActual);


	// Métodos que se sobrescriben aguas abajo
	virtual bool caminoLibre(Pieza* pieza, int xFinal, int yFinal);
	virtual bool caminoLibreRey(Pieza* pieza, int xFinal, int yFinal);
	virtual void inicializa() = 0;
	virtual void imprimirTablero() = 0;
	virtual int getTam() = 0;
	virtual ~Mundo() {}
	virtual void nuevaJugada(Color& turnoActual) = 0;


    // Vector que contiene las piezas
    std::vector<Pieza*>& piezas;
};

#endif // MUNDO_H