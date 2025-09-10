//reccorrido pre-order de un arbol binario (raiz, izquierda, derecha)
//reccorrido in-order de un arbol binario (izquierda, raiz, derecha)
//reccorrido post-order de un arbol binario (izquierda, derecha, raiz)

#include <iostream>
#include <stack>
#include <queue>
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
    Nodo* izquierda;
    Nodo* derecha;

    Nodo(int valor) : dato(valor), izquierda(nullptr), derecha(nullptr) {}
};