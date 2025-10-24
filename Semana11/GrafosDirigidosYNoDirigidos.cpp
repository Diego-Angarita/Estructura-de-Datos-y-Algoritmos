#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Grafo {
protected:
    int numVertices;
    vector<list<int>> listaAdyacencia;
    bool esDirigido;

public:
    // Constructor
    Grafo(int vertices, bool dirigido = false) 
        : numVertices(vertices), esDirigido(dirigido) {
        listaAdyacencia.resize(numVertices);
    }

    // Agregar arista
    virtual void agregarArista(int origen, int destino) {
        // Verificar que los vértices sean válidos
        if (origen >= 0 && origen < numVertices && destino >= 0 && destino < numVertices) {
            listaAdyacencia[origen].push_back(destino);
            
            // Si no es dirigido, agregar la arista en ambas direcciones
            if (!esDirigido && origen != destino) {
                listaAdyacencia[destino].push_back(origen);
            }
        }
    }

    // Eliminar arista
    virtual void eliminarArista(int origen, int destino) {
        if (origen >= 0 && origen < numVertices && destino >= 0 && destino < numVertices) {
            listaAdyacencia[origen].remove(destino);
            
            if (!esDirigido) {
                listaAdyacencia[destino].remove(origen);
            }
        }
    }

    // Mostrar el grafo
    void mostrarGrafo() {
        cout << "Grafo " << (esDirigido ? "Dirigido:" : "No Dirigido:") << endl;
        for (int i = 0; i < numVertices; i++) {
            cout << "Vértice " << i << ": ";
            for (int vecino : listaAdyacencia[i]) {
                cout << vecino << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    // Recorrido DFS (Búsqueda en Profundidad) LIFO 
    void DFS(int verticeInicio) {
        vector<bool> visitado(numVertices, false);
        stack<int> pila;
        
        cout << "DFS desde vértice " << verticeInicio << ": ";
        
        pila.push(verticeInicio);
        
        while (!pila.empty()) {
            int vertice = pila.top();
            pila.pop();
            
            if (!visitado[vertice]) {
                visitado[vertice] = true;
                cout << vertice << " ";
                
                // Agregar vecinos a la pila
                for (int vecino : listaAdyacencia[vertice]) {
                    if (!visitado[vecino]) {
                        pila.push(vecino);
                    }
                }
            }
        }
        cout << endl;
    }

    // Recorrido BFS (Búsqueda en Anchura) FIFO
    void BFS(int verticeInicio) {
        vector<bool> visitado(numVertices, false);
        queue<int> cola;
        
        cout << "BFS desde vértice " << verticeInicio << ": ";
        
        visitado[verticeInicio] = true;
        cola.push(verticeInicio);
        
        while (!cola.empty()) {
            int vertice = cola.front();
            cola.pop();
            cout << vertice << " ";
            
            // Agregar vecinos no visitados a la cola
            for (int vecino : listaAdyacencia[vertice]) {
                if (!visitado[vecino]) {
                    visitado[vecino] = true;
                    cola.push(vecino);
                }
            }
        }
        cout << endl;
    }

    // Verificar si existe una arista
    bool existeArista(int origen, int destino) {
        if (origen >= 0 && origen < numVertices && destino >= 0 && destino < numVertices) {
            return find(listaAdyacencia[origen].begin(), 
                       listaAdyacencia[origen].end(), destino) 
                   != listaAdyacencia[origen].end();
        }
        return false;
    }

    // Obtener el grado de un vértice
    int obtenerGrado(int vertice) {
        if (vertice >= 0 && vertice < numVertices) {
            if (esDirigido) {
                // En grafos dirigidos, calcular grado de entrada + grado de salida
                int gradoSalida = listaAdyacencia[vertice].size();
                int gradoEntrada = 0;
                
                for (int i = 0; i < numVertices; i++) {
                    if (existeArista(i, vertice)) {
                        gradoEntrada++;
                    }
                }
                return gradoSalida + gradoEntrada;
            } else {
                return listaAdyacencia[vertice].size();
            }
        }
        return -1;
    }

    // Obtener número de vértices
    int obtenerNumVertices() const {
        return numVertices;
    }

    // Verificar si el grafo es dirigido
    bool esDirigidoGrafo() const {
        return esDirigido;
    }
};

// Clase específica para grafos dirigidos
class GrafoDirigido : public Grafo {
public:
    GrafoDirigido(int vertices) : Grafo(vertices, true) {}

    // Obtener grado de salida
    int gradoSalida(int vertice) {
        if (vertice >= 0 && vertice < numVertices) {
            return listaAdyacencia[vertice].size();
        }
        return -1;
    }

    // Obtener grado de entrada
    int gradoEntrada(int vertice) {
        if (vertice >= 0 && vertice < numVertices) {
            int grado = 0;
            for (int i = 0; i < numVertices; i++) {
                if (existeArista(i, vertice)) {
                    grado++;
                }
            }
            return grado;
        }
        return -1;
    }

    // Verificar si hay un ciclo (algoritmo DFS)
    bool tieneCiclo() {
        vector<int> color(numVertices, 0); // 0: blanco, 1: gris, 2: negro
        
        for (int i = 0; i < numVertices; i++) {
            if (color[i] == 0) {
                if (tieneCicloDFS(i, color)) {
                    return true;
                }
            }
        }
        return false;
    }

private:
    bool tieneCicloDFS(int vertice, vector<int>& color) {
        color[vertice] = 1; // Marcar como gris
        
        for (int vecino : listaAdyacencia[vertice]) {
            if (color[vecino] == 1) { // Back edge encontrado
                return true;
            }
            if (color[vecino] == 0 && tieneCicloDFS(vecino, color)) {
                return true;
            }
        }
        
        color[vertice] = 2; // Marcar como negro
        return false;
    }
};

// Clase específica para grafos no dirigidos
class GrafoNoDirigido : public Grafo {
public:
    GrafoNoDirigido(int vertices) : Grafo(vertices, false) {}

    // Verificar si el grafo es conexo
    bool esConexo() {
        vector<bool> visitado(numVertices, false);
        queue<int> cola;
        
        // Empezar DFS desde el vértice 0
        cola.push(0);
        visitado[0] = true;
        int verticesVisitados = 1;
        
        while (!cola.empty()) {
            int vertice = cola.front();
            cola.pop();
            
            for (int vecino : listaAdyacencia[vertice]) {
                if (!visitado[vecino]) {
                    visitado[vecino] = true;
                    cola.push(vecino);
                    verticesVisitados++;
                }
            }
        }
        
        return verticesVisitados == numVertices;
    }

    // Verificar si hay un ciclo
    bool tieneCiclo() {
        vector<bool> visitado(numVertices, false);
        
        for (int i = 0; i < numVertices; i++) {
            if (!visitado[i]) {
                if (tieneCicloDFS(i, -1, visitado)) {
                    return true;
                }
            }
        }
        return false;
    }

private:
    bool tieneCicloDFS(int vertice, int padre, vector<bool>& visitado) {
        visitado[vertice] = true;
        
        for (int vecino : listaAdyacencia[vertice]) {
            if (!visitado[vecino]) {
                if (tieneCicloDFS(vecino, vertice, visitado)) {
                    return true;
                }
            } else if (vecino != padre) {
                return true; // Ciclo encontrado
            }
        }
        return false;
    }
};

// Función de demostración
