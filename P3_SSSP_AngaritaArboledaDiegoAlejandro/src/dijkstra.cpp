#include <vector>
#include <queue>
#include <algorithm>
#include "Grafo.cpp"
using namespace std;

//Valor infinito para distancias iniciales
const int INF = 78934;

//Implementación del algoritmo de Dijkstra para encontrar el camino más corto en grafos ponderados sin pesos negativos.

bool encontrarElCaminoMasCortoDijstraNoDirigido(Grafo& grafo, int origen, int destino, vector<int>& visitados, vector<int>& distancia, vector<int>& camino){
  int cantidadVertices = visitados.size();
  
  //Inicializar visitados, distancias y padres
  vector<int> padres(cantidadVertices, -1); // Para reconstruir el camino
  for(int i = 0; i < cantidadVertices; i++) {
    visitados[i] = false;
    distancia[i] = INF; // -1 indica que no hay camino
  }

  //Cola de prioridad para almacenar los vertices que se van visitando, que se ordena por distancia minima al origen

  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> cola; 
  cola.push({0, origen});
  distancia[origen] = 0;

  while(!cola.empty()) {
    int vertice = cola.top().second;
    cola.pop();
    
    //Si encontramos el destino, reconstruimos el camino y terminamos
    if(vertice == destino) {
        // Reconstruir el camino
        int actual = destino;
        while(actual != -1) {
            camino.push_back(actual);
            actual = padres[actual];
        }
        reverse(camino.begin(), camino.end());
        return true;
    }
    
    //si el vertice ya fue visitado (existe un ciclo), el vertice se ignora y el algoritmo continua
    if(visitados[vertice]) {
        continue;
    }
    visitados[vertice] = true;
    
    vector<int> vecinos;
    grafo.getVecinos(vertice, vecinos);
    
    for(int vecino : vecinos) {
      int peso = grafo.getPeso(vertice, vecino);
      if(!visitados[vecino] && distancia[vecino] > distancia[vertice] + peso) {
        distancia[vecino] = distancia[vertice] + peso;
        padres[vecino] = vertice;
        cola.push({distancia[vecino], vecino});

      }
    }
  }

  //Si llegamos aquí, no hay camino al destino por lo tanto se vacia el vector camino
  camino.clear(); 
  return false;
}

bool encontrarElCaminoMasCortoDijstraDirigido(GrafoDirigido& grafo, int origen, int destino, vector<int>& visitados, vector<int>& distancia, vector<int>& camino) {
  int cantidadVertices = visitados.size();
  
  //Inicializar visitados, distancias y padres
  vector<int> padres(cantidadVertices, -1); // Para reconstruir el camino
  for(int i = 0; i < cantidadVertices; i++) {
    visitados[i] = false;
    distancia[i] = INF; // -1 indica que no hay camino
  }
  
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> cola;
  cola.push({0, origen});
  distancia[origen] = 0;
  
  while(!cola.empty()) {
    int vertice = cola.top().second;
    cola.pop();
    
    //Si encontramos el destino, reconstruimos el camino y terminamos
    if(vertice == destino) {
        // Reconstruir el camino
        int actual = destino;
        while(actual != -1) {
            camino.push_back(actual);
            actual = padres[actual];
        }
        reverse(camino.begin(), camino.end());
        return true;
    }
    
    //si el vertice ya fue visitado (existe un ciclo), el vertice se ignora y el algoritmo continua
    if(visitados[vertice]) {
        continue;
    }
    visitados[vertice] = true;
    
    vector<int> vecinos;
    grafo.getVecinos(vertice, vecinos);
    
    for(int vecino : vecinos) {
      int peso = grafo.getPeso(vertice, vecino);
      if(!visitados[vecino] && distancia[vecino] > distancia[vertice] + peso) {
        distancia[vecino] = distancia[vertice] + peso;
        padres[vecino] = vertice;
        cola.push({distancia[vecino], vecino});
      }
    }
  }

  //Si llegamos aquí, no hay camino al destino por lo tanto se vacia el vector camino
  camino.clear(); 
  return false;
}