#include <iostream>
#include "c:/Users/diego/Estruc.Datos y Algoritmos/Estructura-de-Datos-y-Algoritmos/Semana11/GrafosDirigidosYNoDirigidos.cpp"

using namespace std;

class GrafoComplementario : public Grafo {
};

int main() {
    cout << "=== DEMOSTRACIÓN DE GRAFOS ===" << endl;
        
// Crear un grafo no dirigido
    cout << "\n--- Grafo No Dirigido ---" << endl;
    GrafoNoDirigido grafoND(5);
    
    // Agregar aristas
    grafoND.agregarArista(0, 1);
    grafoND.agregarArista(0, 2);
    grafoND.agregarArista(1, 3);
    grafoND.agregarArista(2, 4);
    grafoND.agregarArista(3, 4);
    
    grafoND.mostrarGrafo();
    grafoND.DFS(0);
    grafoND.BFS(0);
    
    cout << "¿Es conexo? " << (grafoND.esConexo() ? "Sí" : "No") << endl;
    cout << "¿Tiene ciclo? " << (grafoND.tieneCiclo() ? "Sí" : "No") << endl;
    cout << "Grado del vértice 1: " << grafoND.obtenerGrado(1) << endl;
    
    // Crear un grafo dirigido
    cout << "\n--- Grafo Dirigido ---" << endl;
    GrafoDirigido grafoD(4);
    
    // Agregar aristas dirigidas
    grafoD.agregarArista(0, 1);
    grafoD.agregarArista(1, 2);
    grafoD.agregarArista(2, 3);
    grafoD.agregarArista(3, 1); // Esto crea un ciclo
    
    grafoD.mostrarGrafo();
    grafoD.DFS(0);
    grafoD.BFS(0);
    
    cout << "¿Tiene ciclo? " << (grafoD.tieneCiclo() ? "Sí" : "No") << endl;
    cout << "Grado de salida del vértice 1: " << grafoD.gradoSalida(1) << endl;
    cout << "Grado de entrada del vértice 1: " << grafoD.gradoEntrada(1) << endl;
    
    return 0;
}