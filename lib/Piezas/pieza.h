



class pieza
{
public:
	void destruir();
	void updatePosPosibles(); // Actualiza posiciones posibles
	void moverPosicion(int x, int y); // Mover posicion
	int x, y;
	bool** posiciones_validas;
	bool color;
};