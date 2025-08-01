#include <iostream>
#include "Perro.h"

int main() {
    Perro miPerro("Bobby", 3);
    miPerro.ladrar();
    std::cout << "Nombre: " << miPerro.getNombre() << ", Edad: " << miPerro.getEdad() << " años" << std::endl;
    return 0;
}
