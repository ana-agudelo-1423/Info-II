#include <iostream>

using namespace std;

void punto_uno();
int punto_tres();
int punto_5();
int punto_siete();
int main()
{
    punto_5();
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
    int suma;

    cout << "ingrese un numero " <<endl;
    cin >> a;
    while(b<=a ) {
        suma= suma+b;
        b++;
    }
    cout << "el resultado de la sumatoria es: " << suma << endl;
    return 0;
}


