#include <iostream>
using namespace std;

struct Nodo{
    int dato;
    Nodo *siguiente;

    Nodo(int valor, Nodo *sig = nullptr): dato(valor), siguiente(sig){}// Constructor para inicializar el nodo
};

void imprimirLista(Nodo *lista){
    Nodo *actual = lista;
    while(actual != nullptr){
        cout<<actual->dato<<" -> ";
        actual = actual->siguiente;
    }
    if (actual == nullptr) {
        cout << "null" << endl;
    }   
}

void insertarOrdenado(Nodo*& inicio, int valor) {
    Nodo* nuevo = new Nodo(valor);
    if (inicio == nullptr || valor <= inicio->dato) {
        nuevo->siguiente = inicio;
        inicio = nuevo;
    }
    else {
        // Buscar la posición correcta para insertar
        Nodo* actual = inicio;
        while (actual->siguiente != nullptr && valor > actual->siguiente->dato) {
            actual = actual->siguiente;
        }
        nuevo->siguiente = actual->siguiente;// Enlazar el nuevo nodo
        actual->siguiente = nuevo;// Enlazar el nodo anterior al nuevo
    }
}

int main() {
    Nodo* inicio = nullptr; // Inicializar la lista vacía
    imprimirLista(inicio); // Imprimir lista vacía
    insertarOrdenado(inicio, 5);
    imprimirLista(inicio);
    insertarOrdenado(inicio, 3);
    imprimirLista(inicio);
    insertarOrdenado(inicio, 8);
    imprimirLista(inicio);
    insertarOrdenado(inicio, 1);
    imprimirLista(inicio);
    insertarOrdenado(inicio, 7);
    imprimirLista(inicio);

    //liberar memoria
    Nodo* actual = inicio;
    while (actual != nullptr) {
        Nodo* temp = actual;
        actual = actual->siguiente;
        delete temp; // Liberar memoria del nodo actual
    }
    return 0;
}