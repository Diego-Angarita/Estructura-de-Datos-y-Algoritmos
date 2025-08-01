#include "Perro.h"
#include<iostream>
#include<String>
using namespace std;

int main()
{
    Perro kira(15, "Kira", 10.4);
    cout<<kira.getName() + " tiene " + to_string(kira.getAge()) + " y pesa " + to_string(kira.getWeight()) + "\n";

    return 0;    
}