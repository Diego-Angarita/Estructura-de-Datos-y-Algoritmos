#include<iostream>
using namespace std;

void mayorYMenor(int n){
    int arr[n];

    for (int i = 0; i < n; i++){
        cout << "Ingrese el numero " << i+1 << ": ";
        cin >> arr[i];
    }

    int a = arr[0];
    int b = arr[0];
    for (int i = 1; i < n; i++){
        if (arr[i] > a){
            a = arr[i];
        }

        if (arr[i] < b){
            b = arr[i];
        }
    }
    cout << "El mayor numero es: " << a << endl;
    cout << "El menor numero es: " << b << endl;
}

void invertirArreglo(int n){
    int arr[n];

    for (int i = 0; i < n; i++){
        cout << "Ingrese el numero " << i+1 << ": ";
        cin >> arr[i];
    }

    for (int i = n-1; i >= 0; i--){
        cout << arr[i] << " ";
    }
}

void sumarArreglos(int n){
    int arr1[n];
    int arr2[n];
    int arr3[n];

    for (int i = 0; i < n; i++){
        cout << "Ingrese el numero " << i+1 << " del primer arreglo: ";
        cin >> arr1[i];
    }

    for (int i = 0; i < n; i++){
        cout << "Ingrese el numero " << i+1 << " del segundo arreglo: ";
        cin >> arr2[i];
    }

    for (int i = 0; i < n; i++){
        arr3[i] = arr1[i] + arr2[i];
    }

    for (int i = 0; i < n; i++){
        cout << arr3[i] << " ";
    }
}

// Función para eliminar la primera ocurrencia de un valor específico
int eliminarValor(int arr[], int n, int valor) {
    int posicion = -1;
    
    // Buscar la posición del valor
    for (int i = 0; i < n; i++) {
        if (arr[i] == valor) {
            posicion = i;
            break;
        }
    }
    
    // Si no se encontró el valor
    if (posicion == -1) {
        cout << "Valor " << valor << " no encontrado en el array" << endl;
        return n; // Retorna el tamaño original
    }
    
    // Desplazar elementos hacia la izquierda
    for (int i = posicion; i < n - 1; i++) {
        arr[i] = arr[i + 1];
    }
    
    cout << "Valor " << valor << " eliminado exitosamente" << endl;
    return n - 1; // Retorna el nuevo tamaño
}

// Función para eliminar TODAS las ocurrencias de un valor específico
int eliminarTodasOcurrencias(int arr[], int n, int valor) {
    int nuevoTamano = 0;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] != valor) {
            arr[nuevoTamano] = arr[i];
            nuevoTamano++;
        }
    }
    
    if (nuevoTamano == n) {
        cout << "Valor " << valor << " no encontrado en el array" << endl;
    } else {
        cout << "Se eliminaron " << (n - nuevoTamano) << " ocurrencias del valor " << valor << endl;
    }
    
    return nuevoTamano;
}

// Función para imprimir un array
void imprimirArray(int arr[], int n) {
    cout << "Array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}


int main(){
    //mayorYMenor(5);
    //invertirArreglo(5);
    //sumarArreglos(5);
    
    return 0;
}