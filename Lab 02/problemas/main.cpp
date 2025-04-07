#include <iostream>
#include <cstring>
#include <cstdlib>
#include <iomanip>
using namespace std;
void problema_1();
bool problema_3();
int Problema_3();
int problema_5();
int problema_7();
int problema_9();
int problema_11();
int problema_13();

const int FILAS = 15;
const int COLUMNAS = 20;
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
     cout << "\n";
     cout << "Problema 9"<< endl;
    problema_9();
     cout << "\n";
     cout << "Problema 11"<< endl;
     problema_11();
     cout << "\n";
     cout << "Problema 13"<< endl;
     problema_13();
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
int problema_9(){
    int n;
    char cadena[20];
    cout << "Ingrese el valor de n (cantidad de cifras por grupo): ";
    cin >> n;

    cout << "Ingrese la cadena de caracteres numericos: ";
    cin >> cadena;

    int longitud = strlen(cadena);
    int resto = longitud % n;
    int cerosNecesarios = (resto == 0) ? 0 : n - resto;

    // Crear nueva cadena con ceros a la izquierda si es necesario
    char completa[110];
    int j = 0;

    // Agregar ceros a la izquierda
    for (int i = 0; i < cerosNecesarios; i++) {
        completa[j++] = '0';
    }

    // Copiar cadena original a la nueva
    for (int i = 0; i < longitud; i++) {
        completa[j++] = cadena[i];
    }

    completa[j] = '\0';  // Finalizar cadena

    // Sumar los números en bloques de n
    int suma = 0;
    for (int i = 0; i < j; i += n) {
        char bloque[10];
        strncpy(bloque, completa + i, n);  // Copiar n caracteres
        bloque[n] = '\0';                  // Agregar terminador
        suma += atoi(bloque);              // Convertir y sumar
    }

    cout << "Original: " << cadena << ". Suma: " << suma << "." << endl;
    return 0;
}


void mostrarSala(char sala[FILAS][COLUMNAS]) {
    cout << "   ";
    for (int j = 0; j < COLUMNAS; j++)
       cout << setw(3) << j + 1;
    cout << endl;

    for (int i = 0; i < FILAS; i++) {
        cout << char('A' + i) << "  ";
        for (int j = 0; j < COLUMNAS; j++) {
           cout << setw(3) << sala[i][j];
        }
        cout << endl;
    }
}

void inicializarSala(char sala[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            sala[i][j] = '-';
        }
    }
}
int problema_11(){
    char sala[FILAS][COLUMNAS];
    inicializarSala(sala);

    char opcion;
    do {
        cout << "\nOpciones:\n";
        cout << "1. Mostrar sala\n";
        cout << "2. Reservar asiento\n";
        cout << "3. Cancelar reserva\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcióon: ";
        cin >> opcion;

        if (opcion == '1') {
            mostrarSala(sala);
        } else if (opcion == '2' || opcion == '3') {
            char filaLetra;
            int asientoNum;
            cout << "Ingrese fila (A-O): ";
            cin >> filaLetra;
            cout << "Ingrese número de asiento (1-20): ";
            cin >> asientoNum;

            int fila = toupper(filaLetra) - 'A';
            int asiento = asientoNum - 1;

            if (fila >= 0 && fila < FILAS && asiento >= 0 && asiento < COLUMNAS) {
                if (opcion == '2') {
                    sala[fila][asiento] = '+';
                    cout << "Asiento reservado.\n";
                } else {
                    sala[fila][asiento] = '-';
                    cout << "Reserva cancelada.\n";
                }
            } else {
                cout << "Fila o asiento inválido.\n";
            }
        } else if (opcion != '4') {
            cout << "Opción inválida.\n";
        }

    } while (opcion != '4');
    return 0;
}

int contarEstrellas(int** matriz, int filas, int columnas) {
    int estrellas = 0;

    for (int i = 1; i < filas - 1; i++) {
        for (int j = 1; j < columnas - 1; j++) {
            int suma = matriz[i][j] + matriz[i][j - 1] + matriz[i][j + 1] +
                       matriz[i - 1][j] + matriz[i + 1][j];
            float promedio = suma / 5.0;

            if (promedio > 6) {
                estrellas++;
            }
        }
    }

    return estrellas;
}
int problema_13(){
    const int filas = 7;
    const int columnas = 10;

    int datos[filas][columnas] = {
        {0, 3, 4, 0, 0, 0, 6, 0, 6, 8},
        {5, 13, 6, 0, 0, 0, 0, 0, 2, 3},
        {2, 6, 2, 7, 3, 0, 8, 10, 0, 0},
        {0, 0, 0, 4, 5, 14, 1, 6, 0, 0},
        {0, 0, 0, 7, 12, 9, 10, 9, 10, 4},
        {5, 0, 0, 10, 6, 4, 8, 4, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    // Convertimos el arreglo 2D en un arreglo de punteros para pasarlo a la función
    int* punteros[filas];
    for (int i = 0; i < filas; i++) {
        punteros[i] = datos[i];
    }

    int resultado = contarEstrellas(punteros, filas, columnas);
    cout << "Estrellas encontradas: " << resultado << endl;

    return 0;
}
