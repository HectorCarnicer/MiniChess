#include <iostream>
#include <string>
//Menu devuelve la opci�n introducida en string siempre y cuando sea gardner o baby
std::string menu() {
    std::string opcion;
    while (true) {
        std::cout << "Por favor, elige una opci�n: gardner o baby: ";
        std::cin >> opcion;
        if (opcion == "gardner" || opcion == "baby") {
            return opcion;
        } else {
            std::cout << "Opci�n inv�lida. Int�ntalo de nuevo.\n";
        }
    }
}
//TEST
/*
int main() {
    std::string eleccion = menu();
    std::cout << "Has elegido: " << eleccion << std::endl;
    return 0;
}
*/
