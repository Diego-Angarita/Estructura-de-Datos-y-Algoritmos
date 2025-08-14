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

void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

int main(){
    int n = 100000;
    int arr[n];
    cout << endl;

    for (int i = 0; i < n; i++) {
        arr[i] = generarIntRandom(1, 10000);
    }


    clock_t start = clock();
    shellSort(arr, n);
    clock_t end = clock();
    double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;

    cout << endl;
    cout << "Tiempo de ejecucion: " << elapsed_secs << " segundos" << endl;


    return 0;
}