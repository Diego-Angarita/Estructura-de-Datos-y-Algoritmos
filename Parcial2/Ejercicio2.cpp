#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iomanip>
#include <string>
#include <stdexcept>
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

        int getAltura(Nodo* raiz) {
            if (raiz == nullptr) {
                return 0;
            }
            int alturaIzq = getAltura(raiz->left);
            int alturaDer = getAltura(raiz->right);
            return 1 + max(alturaIzq, alturaDer);
        }

        int getGradoMax(Nodo* raiz) {
            if (raiz == nullptr) {
                return 0;
            }
            int grado = 0;
            if (raiz->left != nullptr) grado++;
            if (raiz->right != nullptr) grado++;
            int gradoIzq = getGradoMax(raiz->left);
            int gradoDer = getGradoMax(raiz->right);
            return max(grado, max(gradoIzq, gradoDer));
        }

        void borrarArbol(Nodo* raiz){
            if(raiz != nullptr){
                borrarArbol(raiz->left);
                borrarArbol(raiz->right);
                delete raiz;
            }
        }

    public:
        BST() : raiz(nullptr) {}
        ~BST() { borrarArbol(raiz); }

        void insert(int key) {
            raiz = insert(raiz, key);
        }

        bool find(int key, vector<int>& camino) {
            camino.clear();
            return find(raiz, key, camino);
        }

        void preorder() {
            recorridoPreOrder(raiz);
            cout << endl;
        }

        void inorder() {
            recorridoInOrder(raiz);
            cout << endl;
        }

        void postorder() {
            recorridoPostOrder(raiz);
            cout << endl;
        }

        int height() {
            return getAltura(raiz);
        }

        int gradoMax() {
            return getGradoMax(raiz);
        }

        void limpiar() {
            borrarArbol(raiz);
            raiz = nullptr;
        }



        bool estaVacio() {
            return raiz == nullptr;
        }

        // Crear BST con inserciones ordenadas (caso degenerado)
        void crearCasoDegenerado(int n) {
            limpiar();
            cout << "Creando BST degenerado con " << n << " elementos ordenados..." << endl;
            for (int i = 1; i <= n; i++) {
                insert(i);
            }
            cout << "BST degenerado creado. Altura: " << height() << endl;

        }

        // Crear BST con inserciones aleatorias
        void crearCasoAleatorio(int n) {
            limpiar();
            cout << "Creando BST aleatorio con " << n << " elementos..." << endl;
            
            // Crear vector con números del 1 al n
            vector<int> numeros;
            for (int i = 1; i <= n; i++) {
                numeros.push_back(i);
            }
            
            // Mezclar aleatoriamente
            random_device rd;
            mt19937 gen(rd());
            shuffle(numeros.begin(), numeros.end(), gen);
            
            // Insertar en orden aleatorio
            for (int num : numeros) {
                insert(num);
            }
            cout << "BST aleatorio creado. Altura: " << height() << endl;
            cout << "Grado maximo del BST>" << gradoMax() << endl;
        }
};

void borrarBST(BST& arbol) {
    arbol.limpiar();
}

void imprimirVisitados(const vector<int>& path) {
    for (size_t i = 0; i < path.size(); ++i) {
        if (i) cout << " -> ";
        cout << path[i];
    }
    cout << "\n";
}

void compararAlturas() {
    cout << "\nComparacion de alturas" << endl;
    cout << "Ingrese el numero de elementos para la comparacion: ";
    int n;
    cin >> n;
    
    if (n <= 0) {
        cout << "El numero debe ser positivo." << endl;
        return;
    }
    
    BST arbolDegenerado, arbolAleatorio;
    
    // Crear caso degenerado
    cout << "\nCreando caso degenerado..." << endl;
    arbolDegenerado.crearCasoDegenerado(n);
    int alturaDegenerada = arbolDegenerado.height();
    
    // Crear caso aleatorio
    cout << "Creando caso aleatorio..." << endl;
    arbolAleatorio.crearCasoAleatorio(n);
    int alturaAleatoria = arbolAleatorio.height();
    
    // Mostrar comparacion
    cout << "\nResultados de comparacion" << endl;
    cout << "Numero de elementos: " << n << endl;
    cout << "Altura del BST degenerado (ordenado): " << alturaDegenerada << endl;
    cout << "Altura del BST aleatorio: " << alturaAleatoria << endl;
    cout << "Diferencia de altura: " << (alturaDegenerada - alturaAleatoria) << endl;
    cout << "Altura teorica minima (log2n): " << (int)ceil(log2(n + 1)) << endl;
    cout << "Altura teorica maxima: " << n << endl;

    borrarBST(arbolDegenerado);
    borrarBST(arbolAleatorio);
}

int main(){
    cout << "Programa de creacion y analis de BST" << endl;
    BST arbol;
    vector<int> path;
    int opcion, valor;
    string entrada;

    do {
        cout << "\nmenu interactivo" << endl;
        cout << "1.  Insertar elementos" << endl;
        cout << "2.  Buscar elemento" << endl;
        cout << "3.  Recorrido Preorden" << endl;
        cout << "4.  Recorrido Inorden" << endl;
        cout << "5.  Recorrido Postorden" << endl;
        cout << "6.  Obtener altura del arbol" << endl;
        cout << "7.  Obtener grado maximo del arbol" << endl;
        cout << "8.  Crear caso degenerado (ordenado)" << endl;
        cout << "9.  Crear caso aleatorio" << endl;
        cout << "10. Comparar alturas (degenerado vs aleatorio)" << endl;
        cout << "11. Salir" << endl;
        cout << "========================================" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

         switch (opcion) {
            case 1:
                cout << "Ingrese valores a insertar (presione 'e' para terminar):" << endl;
                while (true) {
                    cout << "Valor: ";
                    cin >> entrada;
                    
                    if (entrada == "e" || entrada == "E") {
                        break;
                    }
                    
                    try {
                        valor = stoi(entrada);
                        arbol.insert(valor);
                        cout << "Valor " << valor << " insertado." << endl;
                    } catch (const invalid_argument& e) {
                        cout << "Entrada invalida. Ingrese un numero o 'e' para terminar." << endl;
                    } catch (const out_of_range& e) {
                        cout << "Numero fuera de rango. Ingrese un numero valido o 'e' para terminar." << endl;
                    }
                }
                cout << "Insercion completada. Altura actual: " << arbol.height() << endl;
                break;
                
            case 2:
                if (arbol.estaVacio()) {
                    cout << "El arbol esta vacio." << endl;
                    break;
                }
                cout << "Ingrese el valor a buscar: ";
                cin >> valor;
                if (arbol.find(valor, path)) {
                    cout << "Valor " << valor << " encontrado. Camino: ";
                    imprimirVisitados(path);
                } else {
                    cout << "Valor " << valor << " no encontrado. Camino de busqueda: ";
                    imprimirVisitados(path);
                }
                break;
                
            case 3:
                if (arbol.estaVacio()) {
                    cout << "El arbol esta vacio." << endl;
                } else {
                    cout << "Recorrido Preorden: ";
                    arbol.preorder();
                }
                break;
                
            case 4:
                if (arbol.estaVacio()) {
                    cout << "El arbol esta vacio." << endl;
                } else {
                    cout << "Recorrido Inorden: ";
                    arbol.inorder();
                }
                break;
                
            case 5:
                if (arbol.estaVacio()) {
                    cout << "El arbol esta vacio." << endl;
                } else {
                    cout << "Recorrido Postorden: ";
                    arbol.postorder();
                }
                break;
                
            case 6:
                cout << "Altura del arbol: " << arbol.height() << endl;
                break;
                
            case 7:
                cout << "Grado maximo del arbol: " << arbol.gradoMax() << endl;
                break;
                
            case 8:
                cout << "Ingrese el numero de elementos para el caso degenerado: ";
                cin >> valor;
                if (valor > 0) {
                    arbol.crearCasoDegenerado(valor);
                } else {
                    cout << "El numero debe ser positivo." << endl;
                }
                break;
                
            case 9:
                cout << "Ingrese el numero de elementos para el caso aleatorio: ";
                cin >> valor;
                if (valor > 0) {
                    arbol.crearCasoAleatorio(valor);
                } else {
                    cout << "El numero debe ser positivo." << endl;
                }
                break;
                
            case 10:
                compararAlturas();
                break;
                
            case 11:
                cout << "Saliendo del sistema..." << endl;
                break;
                
            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
        }
        
        if (opcion != 11) {
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
        
    } while (opcion != 11);

    borrarBST(arbol);
    return 0;
}