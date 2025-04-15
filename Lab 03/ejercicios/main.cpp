#include <iostream>
#include <string>
#include <fstream>
using namespace std;


void codificacion();
void cajero();
int main(){
    int opcion;
    cout << "OPCIONES MENU"<< endl;
    cout <<"1. Codificar archivos"<<endl;
    cout << "2. Cajero"<<endl;
    cout << "3. Salir "<<endl;
    cout <<"Escoja una opcion: "<<endl;
    cin>> opcion;

    switch (opcion) {
        case 1:
            cout << "\n--- Codificar archivos de texto ---\n";
            codificacion();
            break;
        case 2:
            cout << "\n--- Problema 3 ---\n";
            cajero();
            break;
        case 3:
             cout << "Vuelva pronto.\n";
             break;
         default:
        cout << "Opcion invalida. Intente de nuevo.\n";
        break;
    } while(opcion != 3);

    return 0;

}
void codificacion(){
    ifstream origen("Archiv04.exe", ios::binary);
    char linea[1];

    if(origen.fail())
        cerr << "Error al abrir el archivo: Archiv04.exe" << endl;
    else
    {
        ofstream destino("Copia.exe", ios::binary);
        if(destino.fail())
            cerr << "Error al crear el archivo: Copia.exe" << endl;
        else
        {
            while(!origen.eof()&&!origen.fail())
            {
                origen.read(linea, sizeof(linea));
                if(origen.good())
                {
                    destino.write(linea, sizeof(linea));
                    if(destino.fail())
                    {
                        cerr << "Error en el archivo: Copia.exe" << endl;
                        exit(1);
                    }
                }
                else if(!origen.eof())
                {
                    cerr << "Error en el archivo: Archiv04.exe" << endl;
                    exit(1);
                }
            }
        }
        destino.close();
    }
    origen.close();
}
void cajero(){
    int opcion;
    cout <<"MENU CAJERO"<<endl;
    cout << "OPCIONES ROLES"<< endl;
    cout <<"1. Administrador"<<endl;
    cout << "2. usuario"<<endl;
    cout << "3. Salir "<<endl;
    cout <<"Escoja una opcion: "<<endl;
    cin>> opcion;
}
