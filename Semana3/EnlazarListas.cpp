#include <iostream>
#include <string>
using namespace std;


//enlazar datos permite que los datos se guarden en cualquier lugar de la memoria(sin necesidad de que esten de manera contigua)
//pero aun asi cada dato esta conectado al siguinte 

struct Nodo{
    int dato;
    Nodo* sig;
    
    // Constructor para facilitar la creación
    Nodo(int valor, Nodo* siguiente = nullptr) : dato(valor), sig(siguiente) {}
};

// Función para imprimir la lista
void imprimirLista(Nodo* inicio) {
    Nodo* cabeza = inicio;
    cout << "Lista: ";
    
    while (cabeza != nullptr) {
        cout << actual->dato;
        if (actual->sig != nullptr) {
            cout << " -> ";
        }
        cabeza = actual->sig;
    }
    cout << " -> NULL" << endl;
}

int main(){
    Nodo* inicio = nullptr;

    // Crear la lista
    Nodo* nuevo = new Nodo(10, nullptr);
    inicio = nuevo;

    nuevo->sig = new Nodo(20, nullptr);
    nuevo->sig->sig = new Nodo(30, nullptr);
    nuevo->sig->sig->sig = new Nodo(40, nullptr);
    nuevo->sig->sig->sig->sig = new Nodo(50, nullptr);
    
    // Imprimir la lista
    imprimirLista(inicio);
    
    // Liberar memoria (buena práctica)
    Nodo* cabeza = inicio;
    while (actual != nullptr) {
        Nodo* temp = actual;
        actual = actual->sig;
        delete temp;
    }

    return 0;
}