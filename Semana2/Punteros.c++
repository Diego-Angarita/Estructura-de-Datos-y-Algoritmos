#include<iostream>
using namespace std;

void compararMemoria(int n){
    int arrStack[5] = {1,2,3,4,5};

    int*  arrHeap = new int[n];
    for(int i = 0; i < n; i++){
        arrHeap[i] = i + 1;
    }

    //Direcciones de  memoria
    cout << "Direccion de arrStack: " << static_cast<void*>(arrStack) << endl;
    cout << "Direccion de arrStack[0]: " << &arrStack[0] << endl;
    cout << "Direccion de arrStack[4]: " << &arrStack[4] << endl;

     cout << "Direccion de arrHeap: " << static_cast<void*>(arrHeap) << endl;
    cout << "Direccion de arrHeap[0]: " << &arrHeap[0] << endl;
    cout << "Direccion de arrHeap[n-1]: " << &arrHeap[n-1] << endl;

    //liberar memoria
    delete[] arrHeap;
}

int main(){
    compararMemoria(100);
    return 0;
}