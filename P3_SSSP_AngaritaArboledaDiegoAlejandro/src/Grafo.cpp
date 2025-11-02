#ifndef GRAFO_CPP
#define GRAFO_CPP

#include <vector>
#include <list>
#include <tuple>
using namespace std;

class Grafo{
protected:
    int cantidadVertices;
    int cantidadAristas;
    int tipo;
    int fuente;
    vector<list<int>> listaAdyacencia;
    vector<tuple<int, int, int>> aristas; // (origen, destino, peso)
public:
    Grafo(int cantidadVertices){
        this->cantidadVertices = cantidadVertices;
        this->cantidadAristas = 0;
        this->tipo = 0;
        this->fuente = -1;
        listaAdyacencia.resize(cantidadVertices);
    }

    virtual ~Grafo() {} //Destructor virtual para liberar memoria de los grafos derivados

    int getCantidadVertices(){
        return cantidadVertices;
    }

    int getCantidadAristas(){
        return cantidadAristas;
    }

    int getTipo(){
        return tipo;
    }

    int getFuente(){
        return fuente;
    }

    void setFuente(int fuente){
        this->fuente = fuente;
    }

    void setTipo(int tipo){
        this->tipo = tipo;
    }

    void setCantidadAristas(int cantidadAristas){
        this->cantidadAristas = cantidadAristas;
    }

    void setCantidadVertices(int cantidadVertices){
        this->cantidadVertices = cantidadVertices;
    }

    vector<tuple<int, int, int>> getAristas(){
        return aristas;
    }
    
    virtual void agregarArista(int origen, int destino, int peso = 1){
        listaAdyacencia[origen].push_back(destino);
        listaAdyacencia[destino].push_back(origen);
        aristas.push_back(make_tuple(origen, destino, peso));
        this->cantidadAristas++;
    }

    void getVecinos(int vertice, vector<int>& vecinos){
        vecinos = vector<int>(listaAdyacencia[vertice].begin(), listaAdyacencia[vertice].end());
    }
    
    int getPeso(int origen, int destino){
        for(auto arista: aristas){
            if((get<0>(arista) == origen && get<1>(arista) == destino) ||
            (get<0>(arista) == destino && get<1>(arista) == origen)){
                return get<2>(arista);
            }
        }
        return -1; // No existe la arista
    }

    bool pesoNegativo(){
        for(tuple<int,int,int> arista : aristas){
            if(get<2>(arista) < 0){
                return true;
            }
        }
        return false;
    }
};

class GrafoDirigido : public Grafo{
public:
    GrafoDirigido(int cantidadVertices) : Grafo(cantidadVertices){}

    void agregarArista(int origen, int destino, int peso = 1) override {
        listaAdyacencia[origen].push_back(destino);
        aristas.push_back(make_tuple(origen, destino, peso));
        this->cantidadAristas++;
    }

    int getPeso(int origen, int destino){
        for(const auto& arista : aristas){
            if(get<0>(arista) == origen && get<1>(arista) == destino){
                return get<2>(arista);
            }
        }
        return -1; // No existe la arista
    }
};

#endif // GRAFO_CPP