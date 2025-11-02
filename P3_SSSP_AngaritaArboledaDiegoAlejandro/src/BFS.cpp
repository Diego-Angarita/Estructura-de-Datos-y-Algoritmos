#include <vector>
#include "Grafo.cpp"
#include <queue>
#include <algorithm>
using namespace std;

//Implementación del algoritmo BFS para encontrar el camino más cortoen grafos no ponderados.

bool encontrarElCaminoMasCortoBFSGrafoNoDirigido(Grafo& grafo, int origen, int destino, vector<int>& visitados, vector<int>& distancia, vector<int>& camino) {
  int cantidadVertices = visitados.size();
  
  //Inicializar visitados, distancias y padres
  vector<int> padres(cantidadVertices, -1); // Para reconstruir el camino
  for(int i = 0; i < cantidadVertices; i++) {
    visitados[i] = false;
    distancia[i] = -1; // -1 indica que no hay camino
  }
  
  queue<int> cola;
  cola.push(origen);
  visitados[origen] = true;
  distancia[origen] = 0;
  padres[origen] = -1; // El origen no tiene padre
  
  while(!cola.empty()) {
    int vertice = cola.front();
    cola.pop();
    
    //Si encontramos el destino, reconstruimos el camino y terminamos
    if(vertice == destino) {
      //Reconstruir el camino desde el destino hasta el origen
      camino.clear();
      int actual = destino;
      while(actual != -1) {
        camino.push_back(actual);
        actual = padres[actual];
      }
      reverse(camino.begin(), camino.end());
      return true; // Existe un camino
    }
    
    vector<int> vecinos;
    grafo.getVecinos(vertice, vecinos);
    
    for(int vecino : vecinos) {
      if(!visitados[vecino]) {
        visitados[vecino] = true;
        distancia[vecino] = distancia[vertice] + 1;
        padres[vecino] = vertice; // Guardamos el padre del vecino
        cola.push(vecino);
      }
    }
  }

  //Si llegamos aquí, no hay camino al destino por lo tanto se vacia el vector camino
  camino.clear(); 
  return false;
}

bool encontrarElCaminoMasCortoBFSGrafoDirigido(GrafoDirigido& grafo, int origen, int destino, vector<int>& visitados, vector<int>& distancia, vector<int>& camino) {
  int cantidadVertices = visitados.size();
  
  //Inicializar visitados, distancias y padres
  vector<int> padres(cantidadVertices, -1); // Para reconstruir el camino
  for(int i = 0; i < cantidadVertices; i++) {
    visitados[i] = false;
    distancia[i] = -1; // -1 indica que no hay camino
  }
  
  queue<int> cola;
  cola.push(origen);
  visitados[origen] = true;
  distancia[origen] = 0;
  padres[origen] = -1; // El origen no tiene padre
  
  while(!cola.empty()) {
    int vertice = cola.front();
    cola.pop();
    
    //Si encontramos el destino, reconstruimos el camino y terminamos
    if(vertice == destino) {
      // Reconstruir el camino desde el destino hasta el origen
      camino.clear();
      int actual = destino;
      while(actual != -1) {
        camino.push_back(actual);
        actual = padres[actual];
      }
      reverse(camino.begin(), camino.end());
      return true;
    }
    
    vector<int> vecinos;
    grafo.getVecinos(vertice, vecinos);
    
    for(int vecino : vecinos) {
      if(!visitados[vecino]) {
        visitados[vecino] = true;
        distancia[vecino] = distancia[vertice] + 1;
        padres[vecino] = vertice;
        cola.push(vecino);
      }
    }
  }

  //Si llegamos aquí, no hay camino al destino por lo tanto se vacia el vector camino
  camino.clear();
  return false;
}
