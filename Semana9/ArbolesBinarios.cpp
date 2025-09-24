//reccorrido pre-order de un arbol binario (raiz, izquierda, derecha)
//reccorrido in-order de un arbol binario (izquierda, raiz, derecha)
//reccorrido post-order de un arbol binario (izquierda, derecha, raiz)

#include <iostream>
#include <queue>
#include <vector>
#include <ctime>
#include <random>
using namespace std;

int generarIntRandom(int min, int max){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

struct Nodo {
    int dato;
    Nodo* izquierdo;
    Nodo* derecho;

    Nodo(int valor) : dato(valor), izquierdo(nullptr), derecho(nullptr) {}
};

Nodo* crearNodo(int valor){
    Nodo* nuevoNodo = new Nodo(valor);
    nuevoNodo->dato = valor;
    nuevoNodo->izquierdo = nullptr;
    nuevoNodo->derecho = nullptr;
    return nuevoNodo;
}

Nodo* insertarNodo(Nodo* raiz, int valor){
    if (raiz == nullptr) {
        return crearNodo(valor);
    }
    if (valor < raiz->dato) {
        raiz->izquierdo = insertarNodo(raiz->izquierdo, valor);
    } else if (valor > raiz->dato) {
        raiz->derecho = insertarNodo(raiz->derecho, valor);
    }

    return raiz;
}

bool buscarNodo(Nodo* raiz, int valor) {
    if (raiz == nullptr) {
        return false;
    }
    if (valor == raiz->dato) {
        return true;
    } else if (valor < raiz->dato) {
        return buscarNodo(raiz->izquierdo, valor);
    } else {
        return buscarNodo(raiz->derecho, valor);
    }
}

    void recorridoInOrder(Nodo* raiz){
        if(raiz != nullptr){
            recorridoInOrder(raiz->izquierdo);
            cout << raiz->dato << " ";
            recorridoInOrder(raiz->derecho);
        }
    }

void recorridoPreOrder(Nodo* raiz){
    if(raiz != nullptr){
        cout << raiz->dato << " ";
        recorridoPreOrder(raiz->izquierdo);
        recorridoPreOrder(raiz->derecho);
    }
}

void recorridoPostOrder(Nodo* raiz){
    if(raiz != nullptr){
        recorridoPostOrder(raiz->izquierdo);
        recorridoPostOrder(raiz->derecho);
        cout << raiz->dato << " ";
    }
}

void recorridoPorNiveles(Nodo* raiz){
    if(raiz == nullptr){
        cout << "El árbol está vacío." << endl;
        return;
    }

    queue<Nodo*> cola;
    cola.push(raiz);

    while(!cola.empty()){
        Nodo* actual = cola.front();
        cola.pop();
        cout << actual->dato << " ";

        if(actual->izquierdo != nullptr){
            cola.push(actual->izquierdo);
        }
        if(actual->derecho != nullptr){
            cola.push(actual->derecho);
        }
    }
    cout << endl;
    
}

int calcularAltura(Nodo* raiz) {
    if (raiz == nullptr) {
        return 0;
    }
    return 1 + max(calcularAltura(raiz->izquierdo), calcularAltura(raiz->derecho));
}
/*
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// Estructura del nodo del árbol binario
struct Nodo {
    int dato;
    Nodo* izquierdo;
    Nodo* derecho;
    
    Nodo(int valor) : dato(valor), izquierdo(nullptr), derecho(nullptr) {}
};

class ArbolBinario {
private:
    Nodo* raiz;
    
    // Función auxiliar para insertar recursivamente
    Nodo* insertar(Nodo* nodo, int valor) {
        if (nodo == nullptr) {
            return new Nodo(valor);
        }
        
        if (valor < nodo->dato) {
            nodo->izquierdo = insertar(nodo->izquierdo, valor);
        } else if (valor > nodo->dato) {
            nodo->derecho = insertar(nodo->derecho, valor);
        }
        
        return nodo;
    }
    
    // Función auxiliar para recorrido inorden
    void inorden(Nodo* nodo) {
        if (nodo != nullptr) {
            inorden(nodo->izquierdo);
            cout << nodo->dato << " ";
            inorden(nodo->derecho);
        }
    }
    
    // Función auxiliar para recorrido preorden
    void preorden(Nodo* nodo) {
        if (nodo != nullptr) {
            cout << nodo->dato << " ";
            preorden(nodo->izquierdo);
            preorden(nodo->derecho);
        }
    }
    
    // Función auxiliar para recorrido postorden
    void postorden(Nodo* nodo) {
        if (nodo != nullptr) {
            postorden(nodo->izquierdo);
            postorden(nodo->derecho);
            cout << nodo->dato << " ";
        }
    }
    
    // Función auxiliar para obtener la altura del árbol
    int altura(Nodo* nodo) {
        if (nodo == nullptr) {
            return 0;
        }
        return 1 + max(altura(nodo->izquierdo), altura(nodo->derecho));
    }
    
    // Función auxiliar para obtener el factor de balance
    int factorBalance(Nodo* nodo) {
        if (nodo == nullptr) {
            return 0;
        }
        return altura(nodo->izquierdo) - altura(nodo->derecho);
    }
    
    // Rotación a la derecha
    Nodo* rotarDerecha(Nodo* y) {
        Nodo* x = y->izquierdo;
        Nodo* T2 = x->derecho;
        
        // Realizar rotación
        x->derecho = y;
        y->izquierdo = T2;
        
        return x;
    }
    
    // Rotación a la izquierda
    Nodo* rotarIzquierda(Nodo* x) {
        Nodo* y = x->derecho;
        Nodo* T2 = y->izquierdo;
        
        // Realizar rotación
        y->izquierdo = x;
        x->derecho = T2;
        
        return y;
    }
    
    // Función auxiliar para equilibrar el árbol (estilo AVL)
    Nodo* equilibrar(Nodo* nodo) {
        if (nodo == nullptr) {
            return nodo;
        }
        
        // Obtener el factor de balance
        int balance = factorBalance(nodo);
        
        // Caso izquierda-izquierda
        if (balance > 1 && factorBalance(nodo->izquierdo) >= 0) {
            return rotarDerecha(nodo);
        }
        
        // Caso derecha-derecha
        if (balance < -1 && factorBalance(nodo->derecho) <= 0) {
            return rotarIzquierda(nodo);
        }
        
        // Caso izquierda-derecha
        if (balance > 1 && factorBalance(nodo->izquierdo) < 0) {
            nodo->izquierdo = rotarIzquierda(nodo->izquierdo);
            return rotarDerecha(nodo);
        }
        
        // Caso derecha-izquierda
        if (balance < -1 && factorBalance(nodo->derecho) > 0) {
            nodo->derecho = rotarDerecha(nodo->derecho);
            return rotarIzquierda(nodo);
        }
        
        return nodo;
    }
    
    // Función auxiliar para equilibrar todo el árbol
    Nodo* equilibrarArbol(Nodo* nodo) {
        if (nodo == nullptr) {
            return nullptr;
        }
        
        // Equilibrar subárboles primero
        nodo->izquierdo = equilibrarArbol(nodo->izquierdo);
        nodo->derecho = equilibrarArbol(nodo->derecho);
        
        // Equilibrar el nodo actual
        return equilibrar(nodo);
    }
    
    // Función auxiliar para recolectar nodos en orden
    void recolectarInorden(Nodo* nodo, vector<int>& valores) {
        if (nodo != nullptr) {
            recolectarInorden(nodo->izquierdo, valores);
            valores.push_back(nodo->dato);
            recolectarInorden(nodo->derecho, valores);
        }
    }
    
    // Función auxiliar para construir árbol equilibrado desde vector ordenado
    Nodo* construirEquilibrado(vector<int>& valores, int inicio, int fin) {
        if (inicio > fin) {
            return nullptr;
        }
        
        int medio = (inicio + fin) / 2;
        Nodo* nodo = new Nodo(valores[medio]);
        
        nodo->izquierdo = construirEquilibrado(valores, inicio, medio - 1);
        nodo->derecho = construirEquilibrado(valores, medio + 1, fin);
        
        return nodo;
    }
    
    // Función auxiliar para eliminar el árbol
    void eliminarArbol(Nodo* nodo) {
        if (nodo != nullptr) {
            eliminarArbol(nodo->izquierdo);
            eliminarArbol(nodo->derecho);
            delete nodo;
        }
    }

public:
    // Constructor
    ArbolBinario() : raiz(nullptr) {}
    
    // Destructor
    ~ArbolBinario() {
        eliminarArbol(raiz);
    }
    
    // Función pública para insertar
    void insertar(int valor) {
        raiz = insertar(raiz, valor);
    }
    
    // Función pública para recorrido inorden (izquierda-raíz-derecha)
    void recorridoInorden() {
        cout << "Recorrido Inorden: ";
        inorden(raiz);
        cout << endl;
    }
    
    // Función pública para recorrido preorden (raíz-izquierda-derecha)
    void recorridoPreorden() {
        cout << "Recorrido Preorden: ";
        preorden(raiz);
        cout << endl;
    }
    
    // Función pública para recorrido postorden (izquierda-derecha-raíz)
    void recorridoPostorden() {
        cout << "Recorrido Postorden: ";
        postorden(raiz);
        cout << endl;
    }
    
    // Recorrido por niveles (breadth-first)
    void recorridoPorNiveles() {
        if (raiz == nullptr) {
            cout << "Recorrido por Niveles: (árbol vacío)" << endl;
            return;
        }
        
        cout << "Recorrido por Niveles: ";
        queue<Nodo*> cola;
        cola.push(raiz);
        
        while (!cola.empty()) {
            Nodo* actual = cola.front();
            cola.pop();
            cout << actual->dato << " ";
            
            if (actual->izquierdo != nullptr) {
                cola.push(actual->izquierdo);
            }
            if (actual->derecho != nullptr) {
                cola.push(actual->derecho);
            }
        }
        cout << endl;
    }
    
    // Función para obtener la altura del árbol
    int obtenerAltura() {
        return altura(raiz);
    }
    
    // Función para equilibrar el árbol completo
    void equilibrarArbolCompleto() {
        vector<int> valores;
        recolectarInorden(raiz, valores);
        
        eliminarArbol(raiz);
        
        raiz = construirEquilibrado(valores, 0, valores.size() - 1);
        cout << "Árbol equilibrado exitosamente." << endl;
    }
    
    // Función para mostrar la estructura del árbol
    void mostrarEstructura() {
        cout << "\n=== ESTRUCTURA DEL ÁRBOL ===" << endl;
        cout << "Altura del árbol: " << obtenerAltura() << endl;
        recorridoPorNiveles();
        cout << "==============================\n" << endl;
    }
    
    // Función para verificar si el árbol está vacío
    bool estaVacio() {
        return raiz == nullptr;
    }
};

// Función principal de demostración
int main() {
    ArbolBinario arbol;
    
    cout << "=== DEMOSTRACIÓN DE ÁRBOL BINARIO ===" << endl;
    
    // Insertar algunos valores
    vector<int> valores = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    
    cout << "\n1. Insertando valores: ";
    for (int valor : valores) {
        cout << valor << " ";
        arbol.insertar(valor);
    }
    cout << endl;
    
    // Mostrar estructura inicial
    arbol.mostrarEstructura();
    
    // Realizar diferentes tipos de recorridos
    cout << "\n2. RECORRIDOS DEL ÁRBOL:" << endl;
    arbol.recorridoInorden();     // Muestra valores ordenados
    arbol.recorridoPreorden();    // Útil para copiar la estructura
    arbol.recorridoPostorden();   // Útil para eliminar nodos
    arbol.recorridoPorNiveles();  // Muestra nivel por nivel
    
    // Ejemplo con árbol desbalanceado
    cout << "\n3. CREANDO ÁRBOL DESBALANCEADO:" << endl;
    ArbolBinario arbolDesbalanceado;
    
    // Insertar valores en orden ascendente (crea árbol desbalanceado)
    for (int i = 1; i <= 7; i++) {
        arbolDesbalanceado.insertar(i);
    }
    
    cout << "Árbol antes del equilibrio:" << endl;
    arbolDesbalanceado.mostrarEstructura();
    arbolDesbalanceado.recorridoInorden();
    
    // Equilibrar el árbol
    cout << "\n4. EQUILIBRANDO EL ÁRBOL:" << endl;
    arbolDesbalanceado.equilibrarArbolCompleto();
    
    cout << "Árbol después del equilibrio:" << endl;
    arbolDesbalanceado.mostrarEstructura();
    arbolDesbalanceado.recorridoInorden();
    
    cout << "\n=== FIN DE LA DEMOSTRACIÓN ===" << endl;
    
    return 0;
} 
 */