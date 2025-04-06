#include <iostream>

using namespace std;
void problema_1();
bool problema_3();
int Problema_3();
int problema_5();
int problema_7();
int main()
{
     cout << "Problema 1"<< endl;
    problema_1();
        cout << "\n";
     cout << "Problema 3"<< endl;
    Problema_3();
        cout << "\n";
     cout << "Problema 5"<< endl;
    problema_5();
        cout << "\n";
     cout << "Problema 7"<< endl;
     problema_7();
     return 0;
}
//falta arduino
void problema_1(){

    int denominaciones[] = {50000, 20000, 10000, 5000, 2000, 1000, 500, 200, 100, 50};
    int cantidad[10] = {0};
    int n = sizeof(denominaciones) / sizeof(denominaciones[0]);

    int monto;
    cout << "Ingrese la cantidad de dinero: " <<endl;
    cin >> monto;

    int resto = monto;

    for (int i = 0; i < n; i++) {
        if (resto >= denominaciones[i]) {
            cantidad[i] = resto / denominaciones[i];
            resto = resto % denominaciones[i];
        }
    }


    for (int i = 0; i < n; i++) {
        cout << denominaciones[i] << ": " << cantidad[i] << endl;
    }

    if (resto > 0) {
        cout << "Faltante: " << resto << endl;
    }

}
bool problema_3(const char* cad1, const char* cad2){
    int i = 0;
    while (cad1[i] != '\0' && cad2[i] != '\0') {
        if (cad1[i] != cad2[i]) {
            return false;
        }
        i++;
    }


    return cad1[i] == '\0' && cad2[i] == '\0';
}
int Problema_3 (){
    char cadena1[100];
    char cadena2[100];
    cin.ignore();
    cout << "Ingrese la primera cadena: "<<endl;
    cin.getline(cadena1, 100);

    cout << "Ingrese la segunda cadena: "<< endl;
    cin.getline(cadena2, 100);

    if (problema_3(cadena1, cadena2)) {
        cout << "Las cadenas son iguales." << endl;
    } else {
        cout << "Las cadenas son diferentes." << endl;
    }

    return 0;
}
void enteroACadena(int numero, char* cadena) {

    sprintf(cadena, "%d", numero);
}
int problema_5(){
    int numero;
    char cadena[20];

    cout << "Ingrese un numero entero: ";
    cin >> numero;


    enteroACadena(numero, cadena);


    cout << "El numero como cadena es: " << cadena << endl;

    return 0;
}

void eliminarRepetidos(const char* original, char* sinRepetidos) {
    int i = 0, j = 0;
    bool usado[256] = {false};
    while (original[i] != '\0') {
        unsigned char letra = original[i];
        if (!usado[letra]) {
            sinRepetidos[j++] = letra;
            usado[letra] = true;
        }
        i++;
    }

    sinRepetidos[j] = '\0';
}
int problema_7(){
    char cadena[100];
    char resultado[100];
   cin.ignore();
    cout << "Ingrese una cadena: ";
    cin.getline(cadena, 100);

    eliminarRepetidos(cadena, resultado);

    cout << "Original: " << cadena << endl;
    cout << "Sin repetidos: " << resultado << endl;
    return 0;
}
