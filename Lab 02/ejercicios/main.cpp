
#include <iostream>
#include <array>

using namespace std;
void fun_a(int *px, int *py);
int fun_b(int a[], int tam);
void fun_c(double *a, int n, double *promedio, double *suma);
void fun_d();

int main()
{
    int array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
   fun_b(array, 10);

    cout << array << endl;
    cout <<array[3] << endl;

    cout << &fun_b << endl;

    cout << "ejercicio 2"<< endl;

    double arreglo[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    int n = 5;
    double promedio, suma;

    // Llama a la función
    fun_c(arreglo, n, &promedio, &suma);

    // Imprime los resultados
    printf("Suma: %.2f\n", suma);
    printf("Promedio: %.2f\n", promedio);

     cout << "ejercicio 3"<< endl;
     cout<< &fun_d <<endl;
    return 0;
}
//La dirección en memoria de array será asignada por el compilador al ejecutar el código.
// Por cada elemento que hay en array se da 4 bytes por el int ya que usualmente ocupa 4 byte de espacio
void fun_a(int *px,int*py){ int tmp = *px;
    *px = *py;
    *py = tmp;
}
int fun_b(int a[], int tam){
    int f, l;
    int *b = a;
    for (f = 0, l = tam -1; f < l; f++, l--) { fun_a(&b[f], &b[l]);
    }
    return 0;
}
//ejercicio 2
void fun_c(double *a, int n, double *promedio, double *suma) {
    int i;
    *suma = 0.0;
    for (i = 0; i < n; i++) {
        *suma += *(a + i);
    }
    *promedio = *suma / n;
}
//ejercicio 3
void fun_d(){
  array<array<unsigned short, 2>, 4> b = {{
        {77, 50},
        {5, 2},
        {28, 39},
        {99, 3}
    }};
    cout << "b[2][1]: " << b[2][1] << endl;
    cout << "b[3][1]: " << b[3][1] << endl;
      auto*  ptr = b.data();
    std::cout << "ptr + 2 apunta a b[2]: {" << ptr[2][0] << ", " << ptr[2][1] << "}" << std::endl;
    std::cout << "*(*(ptr + 2) + 1): " << ptr[2][1] << std::endl;
}


