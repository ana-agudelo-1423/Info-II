#include <iostream>


using namespace std;
int problema_1();
int problema_3();
int problema_5();
void problema_7();
int problema_9();
int problema_11();
int problema_13();
int problema_15();
int problema_17();

int main()
{
    problema_9();
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
    int n;
    cout << "Ingrese un numero entero impar: ";
    cin >> n;

    if (n % 2 == 0) {
        cout << "Por favor, ingrese un numero impar." << endl;
        return 1;
    }

    int mitad = n / 2;

    for (int i = 0; i <= mitad; i++) {
        for (int j = 0; j < mitad - i; j++) {
            cout << " ";
        }
        for (int j = 0; j < 2 * i + 1; j++) {
            cout << "*";
        }
        cout << endl;
    }

    for (int i = mitad - 1; i >= 0; i--) {
        for (int j = 0; j < mitad - i; j++) {
            cout << " ";
        }
        for (int j = 0; j < 2 * i + 1; j++) {
            cout << "*";
        }
        cout << endl;
    }

    return 0;
}
void problema_7(){
    int n;
    cout << "Ingrese un numero: ";
    cin >> n;

    int a = 1, b = 1, suma = 0;
    while (b <= n) {
        if (b % 2 == 0) {
            suma += b;
        }
        int temp = a + b;
        a = b;
        b = temp;
    }
    cout << "El resultado de la suma es: " << suma << endl;
}
int problema_9(){
    int n;
    cout << "Ingrese un numero: ";
    cin >> n;

    int suma = 0, temp = n;

    while (temp > 0) {
        int digito = temp % 10;


        int potencia = 1;
        for (int i = 0; i < digito; i++) {
            potencia *= digito;
        }

        suma += potencia;
        temp /= 10;
    }

    cout << "El resultado de la suma es: " << suma << endl;
    return 0;
}

