#include <iostream>


using namespace std;
int problema_1();
int problema_3();
int problema_5();
int problema_7();
int problema_9();
int problema_11();
int problema_13();
int problema_15();
int problema_17();

int main()
{
    problema_1();
    return 0;
}
int problema_1(){
    char caracter;
    cout << "Ingrese un solo caracter: ";
    cin >> caracter;

    if (!isalpha(caracter)) {
        cout << "no es una letra." << endl;
    } else if (tolower(caracter) == 'a' || tolower(caracter) == 'e' || tolower(caracter) == 'i' || tolower(caracter) == 'o' || tolower(caracter) == 'u') {
        cout << caracter << " es una vocal." << endl;
    } else {
        cout << caracter << " es una consonante." << endl;
    }

    return 0;
}
int problema_3(){
    return 0;
}
