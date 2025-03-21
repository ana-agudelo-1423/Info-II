#include <iostream>
#include <math.h>

using namespace std;

void punto_uno();
int punto_tres();
int punto_5();
int punto_siete();
void punto_nueve();
int punto_once();
int punto_trece();
int punto_quince();
int main()
{
    punto_quince();
    return 0;
}

void punto_uno(){
    int a;
    int b;
    cout << "Ingrese dos numeros" << endl;
    cin >> a>>b;
    cout << "El residuo de la division "<< a <<"/" << b << " es" << a%b << endl;

}
int punto_tres(){
    int a;
    int b;
    cout << "Ingrese dos numeros" << endl;
    cin >> a>>b;
    if (a>b){
        cout << "El numero " << a << " es mayor que "<< b << endl;
    } else {
        if(a<b){
            cout << "El numero " << b << " es mayor que "<< a << endl;
        } else{
            cout << "los dos numeros son iguales"<< endl;
        }
    }
    return 0;
}
int punto_5(){
    int a;
    int b;

    cout << "Ingrese dos numeros" << endl;
    cin >> a>>b;
    cout << "El residuo de la division "<< a <<"/" << b << " con redondeo es " << a/b << endl;
    return 0;
}
int punto_siete(){
    int a;
    int b=1;
    int suma=0;

    cout << "ingrese un numero " <<endl;
    cin >> a;
    while(b<=a ) {
        suma= suma+b;
        b++;
    }
    cout << "el resultado de la sumatoria desde 0 hasta "<<a<< " es: " << suma << endl;
    return 0;
}
void punto_nueve(){
    int a;
    float perimetro;
    float area;
    float pi;
    pi= 3.1416;


    cout << "Ingrese un numero:" << endl;
    cin >> a;
     area=pi* pow(a,2);
    perimetro= a*2*pi;
    cout << "Perimetro: " << perimetro << endl;
    cout << "Area: " << area << endl;
}
int punto_once(){
    int a;
    int i;
    int multiplicacion;

    cout << "ingrese un numero " <<endl;
    cin >> a;
    for( i = 0; i <= 10; i = i + 1 )
    {
        multiplicacion= a*i;
        cout <<a << "*"<< i << "=" <<  multiplicacion << endl;
    }

    return 0;
}
int punto_trece(){
    int a = 0;
    int divisores;

    cout << "ingrese un numero " <<endl;
    cin >> a;
    divisores= a %2;
     cout << divisores << "\n";
    return 0;
}
int punto_quince(){
    int a, suma = 0;

    cout << "Ingrese numeros (0 para terminar):" << endl;

    while (true) {
        cin >> a;
        if (a == 0) {
            break;
        }
        suma += a;
    }

    cout << "El resultado de la sumatoria es: " << suma << endl;

    return 0;
}
