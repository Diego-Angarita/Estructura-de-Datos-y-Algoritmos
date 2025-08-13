#include<stack>
#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
using namespace std;

void imprimirPila(stack<int> pila) {
    while(!pila.empty()) {
        cout << pila.top() << " ";
        pila.pop();
    }
}

void menuPila(stack<int>& pila) {
    int opcion, valor;
    do {
        cout << "1. insertar un elemento en la pila\n2. quitar elemto de la pila\n3. imprimir pila \n4. tamaño de la pila\n5. salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

            switch(opcion) {
        case 1:
            cout << "Ingrese el valor a insertar: ";
            cin >> valor;
            pila.push(valor);
            cout << "Valor " << valor << " insertado en la pila." << endl;
            break;

        case 2:
            if (!pila.empty()) {
                cout << "Valor " << pila.top() << " eliminado de la pila." << endl;
                pila.pop();
            } else {
                cout << "La pila está vacía, no se puede eliminar un elemento." << endl;
            }
            break;
        case 3:
            if (!pila.empty()) {
                cout << "Elementos en la pila: ";
                imprimirPila(pila);
                cout << endl;
            }
            break;
        case 4:
            cout << "el tamaño de la pila es: " << pila.size() << endl;
            break;
        case 5:
            cout << "Saliendo del programa." << endl;
            break;
            default:
            cout << "Opción no válida. Por favor, intente de nuevo." << endl;
            break;
        }
    } while (opcion != 5);
     
}

int main() {
    stack<int> pila;
    string expresion;
    cout << "Ingrese una expresión matemática: ";
    getline(cin, expresion);
    stack<string> expresionPila;

    int division = ceil(1/1);//redondeo hacia arriba de la división
        cout << "Resultado de la división: " << division << endl;
    return 0;
}