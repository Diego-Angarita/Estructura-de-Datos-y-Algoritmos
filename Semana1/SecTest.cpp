#include<iostream>
using namespace std;

int main()
{
    int edad;

    cout<<"Ingresa tu edad\n";
    cin>>edad;

    if (edad<18)
    {
        cout<<"No puedes entrar si eres menor de edad";
    }else
    {
        cout<<"Bienvenido";
    }
    
    return 0;
}