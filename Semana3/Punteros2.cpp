#include<iostream>
using namespace std;


int main(){
    int x = 5;
    int* p = &x;

    cout<<"valor de x: " << x << endl;
    cout<<"direccion de x: " << &x << endl;
    cout<<"valor de p: " << p << endl;
    cout<<"contenido al que apunta p: " << *p << endl;

    *p = 10;
    cout<<"valor de x: " << x << endl;
    int y = 10;
    int* p = &y;

    *p = 20;//cambia el valor de la varible mediante el puntero

    int array[5] = {1,2,3,4,5};
    int b[5] = {array[0], array[1], array[2], array[3], array[4]};
    array[2] = 4;

    for (int i = 0; i < 5; i++){
        cout << b[i] << endl;
    }

    return 0;
}