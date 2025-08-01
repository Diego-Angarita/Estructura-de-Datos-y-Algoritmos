#include <iostream>
using namespace std;

struct Nodo{
    int dato;
    Nodo *siguiente;

    Nodo(int valor, Nodo *sig = nullptr): dato(valor), siguiente(sig){}
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

void agregarAlInicio(Nodo*& inicio, int valor){
    Nodo* nuevo = new Nodo(valor, inicio);
    inicio = nuevo;
}

void agrearAlFinal(Nodo*& inicio, int valor){
    Nodo* nuevo = new Nodo(valor, nullptr);
    if (inicio == nullptr) {
        inicio = nuevo;
        return;
    }
    Nodo* actual = inicio;
    while (actual->siguiente != nullptr) {
        actual = actual->siguiente;
    }
    actual->siguiente = nuevo;
}

int buscarMaximo(Nodo* inicio) {
    if (inicio == nullptr) {
        cout << "Lista vacía" << endl;
        return -1;
    }
    
    int maximo = inicio->dato;
    Nodo* actual = inicio->siguiente;
    
    while (actual != nullptr) {
        if (actual->dato > maximo) {
            maximo = actual->dato;
        }
        actual = actual->siguiente;
    }
    
    return maximo;
}

int buscarMinimo(Nodo* inicio) {
    if (inicio == nullptr) {
        cout << "Lista vacía" << endl;
        return -1;
    }
    
    int minimo = inicio->dato;
    Nodo* actual = inicio->siguiente;
    
    while (actual != nullptr) {
        if (actual->dato < minimo) {
            minimo = actual->dato;
        }
        actual = actual->siguiente;
    }
    
    return minimo;
}

bool buscarValor(Nodo* inicio, int valor) {
    Nodo* actual = inicio;
    while (actual != nullptr) {
        if (actual->dato == valor) {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

void eliminarNodo(Nodo*& inicio, int valor) {
    if (inicio == nullptr) {
        cout << "Lista vacía, no se puede eliminar el nodo." << endl;
        return;
    }

    if (inicio->dato == valor) {
        Nodo* temp = inicio;
        inicio = inicio->siguiente;
        delete temp;
        cout << "Nodo con valor " << valor << " eliminado." << endl;
        return;
    }
    
    if (buscarValor(inicio, valor) == false) {
        cout << "El valor " << valor << " no se encuentra en la lista." << endl;
        return;
    }else{
        Nodo* actual = inicio;
        while (actual->siguiente != nullptr) {
            if (actual->siguiente->dato == valor) {
                Nodo* temp = actual->siguiente;
                actual->siguiente = temp->siguiente;
                delete temp;
                cout << "Nodo con valor " << valor << " eliminado." << endl;
            }
            actual = actual->siguiente;
        }
    }    
}

int contarNodos(Nodo* inicio) {
    int contador = 0;
    Nodo* actual = inicio;

    while (actual != nullptr) {
        contador++;

        actual = actual -> siguiente;
    }

    return contador;
}

int main(){
    Nodo* inicio = nullptr;

    agregarAlInicio(inicio, 40);
    agregarAlInicio(inicio, 30);
    agregarAlInicio(inicio, 20);
    agregarAlInicio(inicio, 10);
    agregarAlInicio(inicio, 5);
    agrearAlFinal(inicio, 20);
    agrearAlFinal(inicio, 50);
    
    cout << "Lista creada: "<<endl;
    imprimirLista(inicio);
    cout << "Cantidad de nodos: " << contarNodos(inicio) << endl;
    cout << "-------------------------" << endl;
    
    eliminarNodo(inicio, 20);
    eliminarNodo(inicio, 100);
    cout << "--------------------------" << endl;
    cout << "Lista despues de eliminar el nodo con valor 20: "<<endl;
    imprimirLista(inicio);
    
    cout << "Cantidad de nodos: " << contarNodos(inicio) << endl;
    cout << "-------------------------" << endl;
    

    while (inicio != nullptr) {
        Nodo* temp = inicio;
        inicio = inicio->siguiente;
        delete temp;
    }
    
    return 0;
}