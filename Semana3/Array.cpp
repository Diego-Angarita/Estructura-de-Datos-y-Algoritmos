#include <iostream>
using namespace std;

int main(){
    int arr[10] = {1,2,3};
    int n = 2;
    
    if(n < 10){
        arr[n++] = 9;
    }

    for (int i = 0; i < 10; i++){
        cout << arr[i] << " ";
    }
    
    return 0;
}