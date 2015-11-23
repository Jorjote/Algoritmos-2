#include "matriz.cpp"
#include <iostream>

using namespace std;
int main(){
    diccMatriz<int> nueva(5, 5, 0);
    cout << nueva.Obtener(1,1) << endl;
    nueva.Obtener(1,1)++;
        cout << nueva.Obtener(1,1) << endl;

}
