#include<iostream>
#include<random>
#include<limits>
using namespace std;

int generarIntRandom(int min, int max) {
    // Genera un número entero aleatorio entre min y max
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

void llenarArray(int arr[], int n) {
    // Llena el array con números aleatorios entre 1 y 200
    for (int i = 0; i < n; i++) {
        arr[i] = generarIntRandom(1, 200);
    }
}

void imprimirArray(int arr[], int n) {
    // Imprime el contenido del array
    cout << "Array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    } 
}

void invertirArreglo(int arr[], int n) {
    // Invierte el contenido del array y lo imprime
    cout << "Array invertido: ";
    for (int i = n - 1; i >= 0; i--) {
        cout << arr[i] << " ";
    }
}

int main() 
{
    int n;
    while (true)//ciclo para validar la entrada del usuario
    {
        cout << "Ingrese el tamaño del array: "; 
        cin >> n;

        if (cin.fail()) {
            // Si la entrada no es un número
            cin.clear(); // Limpia el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta la entrada incorrecta
            cout << "Debe ingresar un número entero." << endl;
        }

        if (n > 0) {
            int arr[n];
            llenarArray(arr, n);
            imprimirArray(arr, n);
            cout << endl;
            invertirArreglo(arr, n);
            break;
        } else {
            cout << "El tamaño del array debe ser un numero positivo." << endl;
        }
    }
    return 0;
}