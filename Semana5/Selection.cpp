#include<iostream>
#include<random>
#include<ctime>
using namespace std;

int generarIntRandom(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int actual = arr[i];
        int j = i;
        while (j > 0 && arr[j - 1] > actual) {
            arr[j] = arr[j - 1];
            j--; 
        }    
        arr[j] = actual;
    }
}

int main(){
    int n = 100000;
    int arr[n];

    for (int i = 0; i < n; i++) {
        arr[i] = generarIntRandom(1, 10000);
    }


    clock_t start = clock();
    bubbleSort(arr, n);
    clock_t end = clock();
    double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
    cout << endl;
    cout << "Tiempo de ejecucion: " << elapsed_secs << " segundos" << endl;


    return 0;
}