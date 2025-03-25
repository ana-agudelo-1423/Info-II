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
    problema_3();
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
    int dia, mes;
    cout <<"Ingrese el dia y el mes ejmplo 20 12"<< endl;
    cin >> dia >> mes;
    int dias_por_mes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (mes < 1 || mes > 12) {
        cout << mes << " es un mes invalido." << endl;
    } else if (dia < 1 || dia > dias_por_mes[mes]) {
        if (mes == 2 && dia == 29) {
            cout << dia << "/" << mes << " es valida en bisiesto." << endl;
        } else {
            cout << dia << "/" << mes << " es una fecha invalida." << endl;
        }
    } else {
        cout << dia << "/" << mes << " es una fecha valida." << endl;
    }
    return 0;
}
int problema_5(){
    return 0;
}
