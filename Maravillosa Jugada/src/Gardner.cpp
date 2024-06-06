#include "../lib/gardner.h"

// Destructor de objetos Gardner
Gardner::~Gardner()
{
	for (Pieza* pieza : piezas) {
		delete pieza;
	}
	piezas.clear();
}

// Impresor del tablero Gardner en consola
void Gardner::imprimirTablero()
{
	// Crear un tablero vacío
	std::string tablero[TAMANO_TABLERO][TAMANO_TABLERO];
	for (int i = 0; i < TAMANO_TABLERO; ++i) {
		for (int j = 0; j < TAMANO_TABLERO; ++j) {
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
	for (int i = 0; i < TAMANO_TABLERO; ++i) {
		for (int j = 0; j < TAMANO_TABLERO; ++j) {
			std::cout << tablero[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

// Inicializador de las piezas del tablero Gardner
void Gardner::inicializa()
{
	// TODO: Añadir piezas que faltan

	// Creación de piezas blancas
	//this->nuevaPieza(new Rey(2, 4, BLANCO, TAMANO_TABLERO));
	//for (int i = 0; i < TAMANO_TABLERO; ++i) {
	//   this->nuevaPieza(new Peon(i, 1, BLANCO, TAMANO_TABLERO));
	//}
	//// Creación de piezas negras
	//this->nuevaPieza(new Rey(3, 0, NEGRO, TAMANO_TABLERO));
	//for (int i = 0; i < 5; ++i) {
	//    this->nuevaPieza(new Peon(i, 3, NEGRO, TAMANO_TABLERO));
	//}
	//this->nuevaPieza(new Reina(3, 2, BLANCO, TAMANO_TABLERO));
	//this->nuevaPieza(new Torre(3, 2, BLANCO, TAMANO_TABLERO));
	//this->nuevaPieza(new Reina(2, 2, BLANCO, TAMANO_TABLERO));
	this->nuevaPieza(new Rey(0, 0, NEGRO, TAMANO_TABLERO));
	this->nuevaPieza(new Rey(4, 4, BLANCO, TAMANO_TABLERO));

	this->nuevaPieza(new Caballo(2, 3, BLANCO, TAMANO_TABLERO));
	this->nuevaPieza(new Reina(3, 3, BLANCO, TAMANO_TABLERO));
	this->nuevaPieza(new Caballo(2, 2, BLANCO, TAMANO_TABLERO));
	//this->nuevaPieza(new Torre(0, 3, BLANCO, TAMANO_TABLERO));

	//this->nuevaPieza(new Alfil(0, 2, BLANCO, TAMANO_TABLERO));
	//this->nuevaPieza(new Reina(3, 4, BLANCO, TAMANO_TABLERO));

}
// Nueva Jugada
void Gardner::nuevaJugada(Color& turnoActual)
{
	int eleccion, nuevoX, nuevoY;

	if (JaqueMate(turnoActual)) {
		std::cout << "ACABO EL JUEGO MANIN";
		exit(0);
	}
	if (detectarJaque(turnoActual)) {
		std::cout << "-----JACQUE AL REY " << (turnoActual == BLANCO ? "BLANCO" : "NEGRO") << "-----\n";
	}


	std::cout << "Turno de " << (turnoActual == BLANCO ? "Blanco" : "Negro") << ". Seleccione una pieza para mover:\n";

	for (int i = 0; i < piezas.size(); ++i) {
		if (piezas[i]->obtenerColor() == turnoActual) {
			std::cout << i + 1 << ". " << piezas[i]->nombreDeClase() << " en posicion ";
			piezas[i]->mostrarPosicion();
		}
	}

	std::cin >> eleccion;

	// Verificar que la elección es válida y corresponde al color del turno

	if (eleccion > 0 && eleccion <= piezas.size() && piezas[eleccion - 1]->obtenerColor() == turnoActual) {

		Pieza* piezaSeleccionada = piezas[eleccion - 1];

		if (detectarJaque(turnoActual) && piezaSeleccionada->nombreDeClase() != "Rey") {
			system("cls");
			std::cout << "Eleccion invalida ESTAS EN JAQUE.\n";
			return;
		}
		std::cout << "Ingrese la nueva posicion X (0 a 7): ";
		std::cin >> nuevoX;
		std::cout << "Ingrese la nueva posicion Y (0 a 7): ";
		std::cin >> nuevoY;


		//detecta movimiento ilegal
		if (piezaSeleccionada->nombreDeClase() == "Rey") {
			int posX = 0, posY = 0;
			piezaSeleccionada->obtenerPosicion(posX, posY);
			piezaSeleccionada->mover(nuevoX, nuevoY);
			bool jaque = detectarJaque(turnoActual);
			piezaSeleccionada->mover(posX, posY);

			if (jaque) {
				system("cls");
				std::cout << "MOVIMIENTO ILEGAL\n";
				return;
			}
			piezaSeleccionada->mover(posX, posY);
		}



		//POR ORDEN DE PRIORIDAD

		if (promocion(piezaSeleccionada->obtenerColor(), nuevoX, nuevoY, piezaSeleccionada)) {
			this->nuevaPieza(new Reina(nuevoX, nuevoY, turnoActual, TAMANO_TABLERO));
			turnoActual = (turnoActual == BLANCO) ? NEGRO : BLANCO;
			system("cls");
			return;
		}

		else if (!posicionOcupada(nuevoX, nuevoY) && caminoLibre(piezaSeleccionada, nuevoX, nuevoY)) {
			if (piezaSeleccionada->mover(nuevoX, nuevoY)) {
				turnoActual = (turnoActual == BLANCO) ? NEGRO : BLANCO;
				system("cls");
			}
			else {
				system("cls");
				std::cout << "-----Movimiento invalido o posicion ocupada-----\n";
			}
		}

		else if (atacarPieza(piezaSeleccionada->obtenerColor(), nuevoX, nuevoY, piezaSeleccionada)) {
			piezaSeleccionada->mover(nuevoX, nuevoY);
			turnoActual = (turnoActual == BLANCO) ? NEGRO : BLANCO;
			system("cls");
		}



	}
	else {
		system("cls");
		std::cout << "Eleccion invalida o no es el turno de esa pieza.\n";
	}


}