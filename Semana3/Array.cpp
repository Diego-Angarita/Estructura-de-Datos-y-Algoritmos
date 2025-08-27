#include <iostream>
using namespace std;

int main(){
    int u;
    int arr[u] = {1,2,3};
    int n = 2;
    
    if(n < 10){
        arr[n++] = 9;
    }

    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]) ; i++){
        cout<<arr[i]<<"\n";
    }
    
    return 0;
}