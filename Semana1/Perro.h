//
// Created by diego on 16/07/2025.
//

#ifndef PERRO_H
#define PERRO_H
#include<String>
#include<iostream>
using namespace std;

class Perro
{
  private:
    int age;
    string name;
    double weight;

  public:
    Perro(int a, string n, double w): age(a), name(n), weight(w){};

    void bark()
    {
      cout<<"Woof Woof";
    }

    int getAge() const{return age;}
    string getName() const{return name;}
    double getWeight() const{return weight;}
};



#endif //PERRO_H
