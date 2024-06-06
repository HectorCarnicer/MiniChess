#include "../lib/mundo.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>


// Función para verificar si la posición está ocupada por otra pieza
bool Mundo::posicionOcupada(int x, int y) {
	for (const auto& pieza : piezas) {
		int posX, posY;
		pieza->obtenerPosicion(posX, posY);
		if (posX == x && posY == y) {
			return true;
		}
	}
	return false;
}

// Función para "comer" la pieza en la posición dada
void Mundo::comerPieza(int x, int y) {
	for (auto it = piezas.begin(); it != piezas.end(); ) {
		int posX, posY;
		(*it)->obtenerPosicion(posX, posY);
		if (posX == x && posY == y) {
			delete* it; // Liberar la memoria de la pieza comida
			it = piezas.erase(it); // Eliminar la pieza del vector y actualizar el iterador
		}
		else {
			++it; // Mover al siguiente elemento si no hay coincidencia
		}
	}
}

//bool Mundo::JaqueMate(Color& turnoActual) {
//
//	int posX = 0, posY = 0;
//	int colorPiezaSeleccionada = 0;
//	for (const auto& pieza : piezas) {
//		if (pieza->obtenerColor() == turnoActual && pieza->nombreDeClase() == "Rey") {
//			pieza->obtenerPosicion(posX, posY);
//			colorPiezaSeleccionada = pieza->obtenerColor();
//			break;
//		}
//	}
//	if (colorPiezaSeleccionada != turnoActual) {
//		return false;
//	}
//
//	int movimientosPosibles[8][2] = {
//	  { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 },
//	  { 1, 1 }, { 1, -1 }, { -1, 1 }, { -1, -1 }
//	};
//	int jaques = 0;
//
//	for (int i = 0; i < 8; ++i) {
//		int nuevoX = posX + movimientosPosibles[i][0];
//		int nuevoY = posY + movimientosPosibles[i][1];
//		if (nuevoX >= 0 && nuevoX < 5 && nuevoY >= 0 && nuevoY < 5) {
//
//			for (const auto& pieza : piezas) {
//				if (pieza->obtenerColor() == turnoActual && pieza->nombreDeClase() == "Rey") {
//					pieza->mover(nuevoX, nuevoY);
//					break;
//				}
//			}
//			if (detectarJaque(turnoActual)) {
//				jaques++;
//			}
//			for (const auto& pieza : piezas) {
//				if (pieza->obtenerColor() == turnoActual && pieza->nombreDeClase() == "Rey") {
//					pieza->mover(posX, posY);
//					break;
//				}
//				
//			}
//
//		}
//	}
//
//
//	if (jaques == 9) {
//		return true;
//	}
//	else return false;
//}
bool Mundo::JaqueMate(Color& turnoActual) {
	int posX = 0, posY = 0;

	for (const auto& pieza : piezas) {
		if (pieza->obtenerColor() == turnoActual && pieza->nombreDeClase() == "Rey") {
			pieza->obtenerPosicion(posX, posY);
			break;
		}
	}

	if (!detectarJaque(turnoActual)) {
		return false;
	}

	int movimientosPosibles[8][2] = {
		{1, 0}, {-1, 0}, {0, 1}, {0, -1},
		{1, 1}, {1, -1}, {-1, 1}, {-1, -1}
	};

	// Verificar si algún movimiento del rey lo saca del jaque
	for (int i = 0; i < 8; ++i) {
		int nuevoX = posX + movimientosPosibles[i][0];
		int nuevoY = posY + movimientosPosibles[i][1];

		if (nuevoX >= 0 && nuevoX < 5 && nuevoY >= 0 && nuevoY < 5) {
			bool ocupada = false;
			for (const auto& pieza : piezas) {
				int x, y;
				pieza->obtenerPosicion(x, y);
				if (x == nuevoX && y == nuevoY && pieza->obtenerColor() == turnoActual) {
					ocupada = true;
					break;
				}
			}
			if (!ocupada) {
				// Mover el rey temporalmente
				for (auto& pieza : piezas) {
					if (pieza->obtenerColor() == turnoActual && pieza->nombreDeClase() == "Rey") {
						pieza->mover(nuevoX, nuevoY);
						break;
					}
				}

				// Verificar si el rey sigue en jaque
				if (!detectarJaque(turnoActual)) {
					// Restaurar la posición del rey y retornar falso ya que el rey puede moverse a un lugar seguro
					for (auto& pieza : piezas) {
						if (pieza->obtenerColor() == turnoActual && pieza->nombreDeClase() == "Rey") {
							pieza->mover(posX, posY);
							break;
						}
					}
					return false;
				}
				// Restaurar la posición del rey
				for (auto& pieza : piezas) {
					if (pieza->obtenerColor() == turnoActual && pieza->nombreDeClase() == "Rey") {
						pieza->mover(posX, posY);
						break;
					}
				}
			}
		}
	}

	// Si el rey no puede moverse a ningún lugar seguro, está en jaque mate
	return true;
}
bool Mundo::promocion(Color color, int x, int y, Pieza* piezaSeleccionada) {
	int posX, posY;
	piezaSeleccionada->obtenerPosicion(posX, posY);
	std::string nombreClase = piezaSeleccionada->nombreDeClase();

	int deltaX = x - posX;
	int deltaY = y - posY;

	if (nombreClase == "Peon") {
		if ((color == BLANCO && deltaY == -1 && abs(deltaX) == 1 && y == 0) ||
			(color == NEGRO && deltaY == 1 && abs(deltaX) == 1 && y == 4)) {
			if (atacarPieza(piezaSeleccionada->obtenerColor(), x, y, piezaSeleccionada) && posicionOcupada(x, y))
				piezaSeleccionada->mover(x, y);
			comerPieza(posX, posY);
			return true;
		}
		else if ((color == BLANCO && deltaY == -1 && deltaX == 0 && y == 0) ||
			(color == NEGRO && deltaY == 1 && deltaX == 0 && y == 4)) {
			if (!posicionOcupada(x, y))
				piezaSeleccionada->mover(x, y);
			comerPieza(posX, posY);
			return true;
		}
	}
	return false;
}

bool Mundo::atacarPieza(Color color, int x, int y, Pieza* piezaSeleccionada) {

	int posX, posY;
	piezaSeleccionada->obtenerPosicion(posX, posY);
	int colorPiezaSeleccionada = piezaSeleccionada->obtenerColor();

	if (colorPiezaSeleccionada != color) {
		return false;
	}

	int deltaX = x - posX;
	int deltaY = y - posY;

	std::string nombreClase = piezaSeleccionada->nombreDeClase();

	// Manejar el caso donde la pieza seleccionada no es un peón
	if (nombreClase != "Peon") {
		for (const auto& pieza : piezas) {
			int posXOponente, posYOponente;
			pieza->obtenerPosicion(posXOponente, posYOponente);
			int colorOponente = pieza->obtenerColor();

			if (posXOponente == x && posYOponente == y && colorOponente != color) {
				comerPieza(x, y);
				return true;
			}
		}
		return false;
	}

	// Manejar el caso donde la pieza seleccionada es un peón
	if (nombreClase == "Peon") {
		if (colorPiezaSeleccionada == BLANCO && deltaY == -1 && abs(deltaX) == 1) {
			for (const auto& pieza : piezas) {
				int posXOponente, posYOponente;
				pieza->obtenerPosicion(posXOponente, posYOponente);
				int colorOponente = pieza->obtenerColor();

				if (posXOponente == x && posYOponente == y && colorOponente != color) {
					comerPieza(x, y);
					return true;
				}
			}
		}
		if (colorPiezaSeleccionada == NEGRO && deltaY == 1 && abs(deltaX) == 1) {
			for (const auto& pieza : piezas) {
				int posXOponente, posYOponente;
				pieza->obtenerPosicion(posXOponente, posYOponente);
				int colorOponente = pieza->obtenerColor();

				if (posXOponente == x && posYOponente == y && colorOponente != color) {
					comerPieza(x, y);
					return true;
				}
			}
		}
	}

	return false;
}

bool Mundo::detectarJaque(Color& turnoActual) {
	int posreyx = 0, posreyy = 0;
	// Obtiene la posicion del rey actual
	for (const auto& pieza : piezas) {
		if (pieza->obtenerColor() == turnoActual && pieza->nombreDeClase() == "Rey") {
			pieza->obtenerPosicion(posreyx, posreyy);
			break;
		}
	}
	// Comprueba que de todas las piezas ninguna toque al rey a traves de caminoLibre
	for (const auto& pieza : piezas) {
		if (pieza->obtenerColor() != turnoActual && pieza->nombreDeClase() != "Peon") {
			if (!caminoLibre(pieza, posreyx, posreyy)) {
				return true;
			}
		}
		else if (pieza->nombreDeClase() == "Peon") {
			int x, y;
			pieza->obtenerPosicion(x, y);

			int deltaX = posreyx - x;
			int deltaY = posreyy - y;
			if (pieza->obtenerColor() != turnoActual && abs(deltaY) == 1 && abs(deltaX) == 1) {
				return true;

			}
		}
	}

	return false;
}

// Función para verificar si el camino está libre para el movimiento de la pieza
bool Mundo::caminoLibre(Pieza* pieza, int nuevoX, int nuevoY) {
	// Implementar la lógica específica para cada tipo de pieza
	// Por ejemplo, para un peón, solo necesitas verificar la casilla final
	// Para piezas como la torre, alfil o reina, necesitas verificar todas las casillas en el camino
	// ...

	std::string nombre = pieza->nombreDeClase();

	if (nombre == "Peon") {
		int x, y;
		pieza->obtenerPosicion(x, y);

		int deltaX = nuevoX - x;
		int deltaY = nuevoY - y;
		if (pieza->obtenerColor() == BLANCO && deltaY == -1 && deltaX == 0) {
			if (posicionOcupada(nuevoX, nuevoY))
				return false;
		}
		if (pieza->obtenerColor() == NEGRO && deltaY == 1 && deltaX == 0) {
			if (posicionOcupada(nuevoX, nuevoY))
				return false;
		}
		if (pieza->obtenerColor() == BLANCO && deltaY == -1 && abs(deltaX) == 1) {
			if (!posicionOcupada(nuevoX, nuevoY))
				return false;
		}
		if (pieza->obtenerColor() == NEGRO && deltaY == 1 && abs(deltaX) == 1) {
			if (!posicionOcupada(nuevoX, nuevoY))
				return false;
		}
		return true;
	}

	if (nombre == "Alfil") {
		int x, y;
		pieza->obtenerPosicion(x, y);
		// esto seria la diagonal arriba derecha
		if (nuevoX > x && nuevoY > y) {
			for (int i = x + 1, j = y + 1; i <= nuevoX && j <= nuevoY; i++, j++) {
				if (posicionOcupada(i, j))
					return false;
			}
		}
		// esto seria la diagonal izq arriba
		else if (nuevoX < x && nuevoY > y) {
			for (int i = x - 1, j = y + 1; i >= nuevoX && j <= nuevoY; i--, j++) {
				if (posicionOcupada(i, j))
					return false;
			}
		}
		// esto la diagonal derecha abajo
		else if (nuevoX > x && nuevoY < y) {
			for (int i = x + 1, j = y - 1; i <= nuevoX && j >= nuevoY; i++, j--) {
				if (posicionOcupada(i, j))
					return false;
			}
		}
		//esto la diagonal abajo izq
		else if (nuevoX < x && nuevoY < y) {
			for (int i = x - 1, j = y - 1; i >= nuevoX && j >= nuevoY; i--, j--) {
				if (posicionOcupada(i, j))
					return false;
			}
		}
		return true;
	}

	if (nombre == "Rey") {
		int x, y;
		pieza->obtenerPosicion(x, y);

		int deltaX = nuevoX - x;
		int deltaY = nuevoY - y;

		if (abs(deltaX) <= 1 && abs(deltaY) <= 1) {
			if (posicionOcupada(nuevoX, nuevoY))
				return false;
		}
		return true;
	}

	if (nombre == "Reina") {
		int x, y;
		pieza->obtenerPosicion(x, y);

		// posiciones a la derecha
		if (nuevoX > x) {
			for (int i = x + 1; i <= nuevoX; i++) {
				if (posicionOcupada(i, y))
					return false;
			}
		}
		// posiciones a la izq
		else if (nuevoX < x) {
			for (int i = x - 1; i >= nuevoX; i--) {
				if (posicionOcupada(i, y))
					return false;
			}
		}
		// posiciones encima
		else if (nuevoY > y) {
			for (int j = y + 1; j <= nuevoY; j++) {
				if (posicionOcupada(x, j))
					return false;
			}
		}
		// posiciones debajo
		else if (nuevoY < y) {
			for (int j = y - 1; j >= nuevoY; j--) {
				if (posicionOcupada(x, j))
					return false;
			}
		}
		if (nuevoX > x && nuevoY > y) {
			for (int i = x + 1, j = y + 1; i <= nuevoX && j <= nuevoY; i++, j++) {
				if (posicionOcupada(i, j))
					return false;
			}
		}
		else if (nuevoX < x && nuevoY > y) {
			for (int i = x - 1, j = y + 1; i >= nuevoX && j <= nuevoY; i--, j++) {
				if (posicionOcupada(i, j))
					return false;
			}
		}
		else if (nuevoX > x && nuevoY < y) {
			for (int i = x + 1, j = y - 1; i <= nuevoX && j >= nuevoY; i++, j--) {
				if (posicionOcupada(i, j))
					return false;
			}
		}
		else if (nuevoX < x && nuevoY < y) {
			for (int i = x - 1, j = y - 1; i >= nuevoX && j >= nuevoY; i--, j--) {
				if (posicionOcupada(i, j))
					return false;
			}
		}

		return true;


	}
	if (nombre == "Torre") {
		int x, y;
		pieza->obtenerPosicion(x, y);
		if (nuevoX > x) {
			for (int i = x + 1; i <= nuevoX; i++) {
				if (posicionOcupada(i, y))
					return false;
			}
		}
		else if (nuevoX < x) {
			for (int i = x - 1; i >= nuevoX; i--) {
				if (posicionOcupada(i, y))
					return false;
			}
		}
		else if (nuevoY > y) {
			for (int j = y + 1; j <= nuevoY; j++) {
				if (posicionOcupada(x, j))
					return false;
			}
		}
		else if (nuevoY < y) {
			for (int j = y - 1; j >= nuevoY; j--) {
				if (posicionOcupada(x, j))
					return false;
			}
		}
		return true;
	}


	if (nombre == "Caballo") {
		int x, y;
		pieza->obtenerPosicion(x, y);

		int movimientospos[8][2] = { {2,1}, {2,-1}, {1,2}, {1,-2}
								  ,{-1,2}, {-1,-2}, {-2,1}, {-2,-1} };

		for (int i = 0; i < 8; i++) {
			//recorre las L del caballo posibles
			int posposiblex = x + movimientospos[i][0];
			int posposibley = y + movimientospos[i][1];

			if (posposiblex == nuevoX && posposibley == nuevoY) {
				if (posicionOcupada(posposiblex, posposibley))
					return false;
			}
		}

	}
	return true; // Por defecto, asumimos que el camino está libre
}

void Mundo::imprimirTablero()
{
	// Crear un tablero vacío
	std::string tablero[8][8];
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			tablero[i][j] = ".";
		}
	}

	// Colocar las iniciales de las piezas en el tablero
	for (const auto& pieza : piezas) {
		int x, y;
		pieza->obtenerPosicion(x, y); // Asumiendo que tienes un método para obtener la posición
		tablero[y][x] = pieza->nombreDeClase().substr(0, 1); // Usa la primera letra del nombre de la clase
	}

	// Imprimir el tablero
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			std::cout << tablero[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
// Función de IA para realizar un movimiento aleatorio
// Corrección en la declaración de la función

/*void Mundo::realizarMovimientoIA(Color colorIA, std::vector<Pieza*>& piezas) {
    if (piezas.empty()) return;
    std::srand(std::time(nullptr));
    std::vector<Pieza*> piezasIA;
    for (auto& pieza : piezas) {
        if (pieza && pieza->obtenerColor() == colorIA) {
            piezasIA.push_back(pieza);
        }
    }
    if (piezasIA.empty()) return;

    while (true) {
        Pieza* piezaSeleccionada = piezasIA[std::rand() % piezasIA.size()];
        if (!piezaSeleccionada) continue;

        int x, y;
        piezaSeleccionada->obtenerPosicion(x, y);

        std::vector<std::pair<int, int>> movimientos = {
            {x + 1, y}, {x - 1, y}, {x, y + 1}, {x, y - 1},
            {x + 1, y + 1}, {x - 1, y + 1}, {x + 1, y - 1}, {x - 1, y - 1}
        };

        std::shuffle(movimientos.begin(), movimientos.end(), std::default_random_engine(std::random_device()()));

        for (const auto& movimiento : movimientos) {
            int nuevoX = movimiento.first;
            int nuevoY = movimiento.second;

            if (nuevoX >= 0 && nuevoX < 8 && nuevoY >= 0 && nuevoY < 8 && caminoLibre(piezaSeleccionada, nuevoX, nuevoY)) {
                if (atacarPieza(colorIA, nuevoX, nuevoY)) {
                    piezaSeleccionada->mover(nuevoX, nuevoY);
                }
                else if (!posicionOcupada(nuevoX, nuevoY)) {
                    piezaSeleccionada->mover(nuevoX, nuevoY);
                }
                return; // La IA ha movido una ficha, salimos de la función
            }
        }
    }
}*/
