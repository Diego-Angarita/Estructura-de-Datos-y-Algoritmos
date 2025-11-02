#include <iostream>
#include <filesystem>
using namespace std;

int main(){
    cout << "current path: " << std::filesystem::current_path() << endl;
    return 0;
}