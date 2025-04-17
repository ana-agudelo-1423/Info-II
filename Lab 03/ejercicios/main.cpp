#include <iostream>
#include <string>
#include <fstream>
#include <bitset>
#include <vector>
#include <algorithm>
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
            cout << "\n--- Cajero ---\n";
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
string leerArchivoBinario(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo, ios::binary);
    string bitsTotales;
    char c;
    while (archivo.get(c)) {
        bitset<8> bits(c);
        bitsTotales += bits.to_string();
    }
    return bitsTotales;
}

// Método 1
string codificarMetodo1(string binario, int n) {
    vector<string> bloques;
    for (size_t i = 0; i < binario.size(); i += n)
        bloques.push_back(binario.substr(i, n));

    string resultado;
    for (size_t i = 0; i < bloques.size(); ++i) {
        string bloque = bloques[i];
        string codificado;
        if (i == 0) {
            for (char bit : bloque)
                codificado += (bit == '1' ? '0' : '1');
        } else {
            string anterior = bloques[i - 1];
            int unos = count(anterior.begin(), anterior.end(), '1');
            int ceros = anterior.size() - unos;

            if (unos == ceros) {
                for (char bit : bloque)
                    codificado += (bit == '1' ? '0' : '1');
            } else if (ceros > unos) {
                for (size_t j = 0; j < bloque.size(); j += 2)
                    codificado += bloque.substr(j, 2) == "10" ? "01" : bloque.substr(j, 2);
            } else {
                for (size_t j = 0; j < bloque.size(); j += 3)
                    codificado += bloque.substr(j, 3) == "101" ? "010" : bloque.substr(j, 3);
            }
        }
        resultado += codificado;
    }
    return resultado;
}

string codificarMetodo2(string binario, int n) {
    string resultado;
    for (size_t i = 0; i < binario.size(); i += n) {
        string bloque = binario.substr(i, n);
        if ((int)bloque.size() < n) break;        string rotado;
        rotado += bloque[bloque.size() - 1];
        for (size_t j = 0; j < bloque.size() - 1; ++j)
            rotado += bloque[j];
        resultado += rotado;
    }
    return resultado;
}

void guardarBinario(string bin, string nombreSalida) {
    ofstream archivo(nombreSalida, ios::binary);
    for (size_t i = 0; i < bin.size(); i += 8) {
        string byte = bin.substr(i, 8);
        bitset<8> b(byte);
        archivo.put(static_cast<char>(b.to_ulong()));
    }
    archivo.close();
}

void codificacion(){
    string resultado;
    int metodo;
    int semilla;
    string entrada, salida;
    string binario = leerArchivoBinario(entrada);
    cout << "Seleccione el método de codificación:\n";
    cout << "1. Inversión según reglas por bloque\n";
    cout << "2. Rotación circular de bits\n";
    // Pedir datos por consola
    cout << "Archivo fuente: ";
    cin >> entrada;
    cout << "Archivo salida: ";
    cin >> salida;
    cout << "Semilla (n): ";
    cin >> semilla;
    cout << "Método (1 o 2): ";
    cin >> metodo;
    if (metodo == 1) {
        resultado = codificarMetodo1(binario, semilla);
    } else if (metodo == 2) {
        resultado = codificarMetodo2(binario, semilla);
    } else {
        cout << "Método inválido\n";
        return;
    }
}


void cajero(){
    int opcion;
    char admin;
    char claveadmin;
    char usuario;
    char clave;
    cout <<"MENU CAJERO"<<endl;
    cout << "OPCIONES ROLES"<< endl;
    cout <<"1. Administrador"<<endl;
    cout << "2. usuario"<<endl;
    cout << "3. Salir "<<endl;
    cout <<"Escoja una opcion: "<<endl;
    cin>> opcion;

    switch (opcion) {
    case 1:
        cout << "\n--- Administador ---\n";
        cout << "Ingrese Usuario"<< endl;
        cin >> admin;
        cout<< "Ingrese clave"<< endl;
         cin >> claveadmin;
        break;
    case 2:
        cout << "\n--- Usuario ---\n";
        cout << "Ingrese Usuario"<< endl;
        cin >> usuario;
        cout<< "Ingrese clave"<< endl;
        cin >> clave;
        break;
        break;
    case 3:
        cout << "Vuelva pronto.\n";
        break;
    default:
        cout << "Opcion invalida. Intente de nuevo.\n";
        break;
    } while(opcion != 3);


}
