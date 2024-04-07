/*

Librería para trabajar con posiciones en una matriz y dobrecarga de operadores
para mayor eficiencia

*/

// Probablemente no vale la pena usarla

class Posicion
{
public: 
	Posicion(int x, int y) : y(y), x(x) {}
	int x, y;
	void operator= (Posicion pos);
};

void Posicion::operator= (Posicion pos)
{
	x = pos.x;
	y = pos.y;
}

bool operator== (Posicion pos1, Posicion pos2)
{
	return (pos1.x == pos2.x && pos1.y == pos2.y);
}
