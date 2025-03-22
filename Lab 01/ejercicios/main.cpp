#include <iostream>
#include <math.h>
#include <list>
#include <sstream>
#include <cctype>
#include <cmath>

using namespace std;

void punto_uno();
int punto_tres();
int punto_5();
int punto_siete();
void punto_nueve();
int punto_once();
int punto_trece();
int punto_quince();
int punto_17();
int punto_19();
int punto_21();
int punto_23();
void punto_25();
int punto_27();
int punto_29();
int main()
{
    punto_25();
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

int punto_17(){
    list<int> numeros;
    string linea;
    int numero;

    cout << "Ingrese varios numeros (0 para terminar): ";
    getline(cin, linea);

    stringstream ss(linea);
    while (ss >> numero) {
        if (numero == 0) {
            break;
        }
        numeros.push_back(numero);
    }

    if (!numeros.empty()) {
        int mayor = *numeros.begin();
        for (int num : numeros) {
            if (num > mayor) {
                mayor = num;
            }
        }
        cout << "El numero mayor fue: " << mayor << endl;
    } else {
        cout << "No se ingresaron numeros válidos." << endl;
    }

    return 0;
}
int punto_19(){
    int a =0,divisiones=1, residuo =0;
    cout <<"Calcular si un numero es primo"<< endl<< endl;
    cout<<"Ingrese un numero"<< endl;
    cin >>a;
    do {
        if(a % divisiones==0){
            residuo++;
        }
        divisiones ++;
    }while(divisiones <=a);
    if(residuo==2){
        cout << "--> El numero "<< a <<" es primo"<< endl;
    }else {
        cout << "--> El numero "<< a <<" no es primo"<< endl;
    }
    return 0;
}

int punto_21(){
    char letra;
    cout<< "Ingrese una letra"<<endl;
    cin >> letra;
    if (isalpha(letra)) { // Verifica si es una letra
        if (isupper(letra)) {
            letra = tolower(letra);
        } else {
            letra= toupper(letra);
        }
        cout << "Letra convertida: " << letra << endl;
    } else {
        cout << "El carácter ingresado no es una letra." << endl;
    }
    return 0;
}
int punto_23(){
      int a, b,  mcmResultado;
    cout << "Ingrese dos numeros: " << endl;
    cin >> a >>b;
    int originalA = a, originalB = b;
    int tempA = a, tempB = b;
    while (tempB != 0) {
        int temp = tempB;
        tempB = tempA % tempB;
        tempA = temp;
    }
    mcmResultado = (originalA * originalB) / tempA;
    cout << "El MCM de " << originalA << " y " << originalB << " es: " << mcmResultado << endl;
    return 0;
}
void punto_25(){
   int a;
   cout << "Ingrese un numero: ";
   cin >> a;
   int cantidadDigitos = (a == 0) ? 1 :log10(abs(a)) + 1;
   cout << a << " tiene " << cantidadDigitos << " digitos" << endl;

}

