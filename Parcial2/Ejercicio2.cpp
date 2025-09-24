#include <iostream>
#include <vector>
using namespace std;

class BST{
    private:
        struct Nodo{
            int key;
            Nodo* left;
            Nodo* right;
            int contador;

            Nodo(int k) : key(k), left(nullptr), right(nullptr), contador(1) {};
        };

        Nodo* raiz;

        Nodo* insert(Nodo* raiz, int key) {
            if (raiz == nullptr) {
                return new Nodo(key);
            }

            if (key == raiz->key) {
                raiz->contador++;
                return raiz;
            }

            if(key < raiz->key) {
                raiz->left = insert(raiz->left, key);
            } else {
                raiz->right = insert(raiz->right, key);

            }

            return raiz;
        }

        bool find(Nodo* raiz, int key, vector<int>& camino) {
            if (raiz == nullptr) {
                return false;
            }

            camino.push_back(raiz->key);

            if(key == raiz->key) {
              return true;  
            }

            if(key < raiz->key) {
                return find(raiz->left, key, camino);
            } else {
                return find(raiz->right, key, camino);
            }

        }
        
        void recorridoPreOrder(Nodo* raiz){
            if(raiz != nullptr){
                cout << raiz->key << " ";
                recorridoPreOrder(raiz->left);
                recorridoPreOrder(raiz->right);
            }
        }
        
        void recorridoInOrder(Nodo* raiz){
            if(raiz != nullptr){
                recorridoInOrder(raiz->left);
                cout << raiz->key << " ";
                recorridoInOrder(raiz->right);
            }
        }


        void recorridoPostOrder(Nodo* raiz){
            if(raiz != nullptr){
                recorridoPostOrder(raiz->left);
                recorridoPostOrder(raiz->right);
                cout << raiz->key << " ";
            }
        }
};