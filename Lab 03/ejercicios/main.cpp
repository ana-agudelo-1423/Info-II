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

    cout << "Seleccione el metodo de codificacion:\n";
    cout << "1. Inversion segun reglas por bloque\n";
    cout << "2. Rotacion circular de bits\n";

    // Pedir datos por consola
    cout << "Archivo fuente: ";
    cin >> entrada;
  string binario = leerArchivoBinario(entrada);
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
        cout << "Metodo invalido\n";
        return;
    }
}

string textoABinario(const string& texto) {
    string binario;
    for (char c : texto) {
        for (int i = 7; i >= 0; --i) {
            binario += ((c >> i) & 1) ? '1' : '0';
        }
    }
    return binario;
}

string invertirBits(const string& bloque) {
    string res = bloque;
    for (char& bit : res) {
        bit = (bit == '1') ? '0' : '1';
    }
    return res;
}

string invertirCadaNBloques(const string& bloque, int n) {
    string res = bloque;
    for (size_t i = 0; i < bloque.size(); i += n) {
        for (int j = 0; j < n && i + j < bloque.size(); ++j) {
            res[i + j] = (bloque[i + j] == '1') ? '0' : '1';
        }
    }
    return res;
}

string encriptar(string texto, int n) {
    string binario = textoABinario(texto);
    vector<string> bloques;
    for (size_t i = 0; i < binario.size(); i += n) {
        bloques.push_back(binario.substr(i, n));
    }

    vector<string> codificado;
    for (size_t i = 0; i < bloques.size(); ++i) {
        if (i == 0) {
            codificado.push_back(invertirBits(bloques[i]));
        } else {
            int unos = count(bloques[i - 1].begin(), bloques[i - 1].end(), '1');
            int ceros = n - unos;

            if (unos == ceros) {
                codificado.push_back(invertirBits(bloques[i]));
            } else if (ceros > unos) {
                codificado.push_back(invertirCadaNBloques(bloques[i], 2));
            } else {
                codificado.push_back(invertirCadaNBloques(bloques[i], 3));
            }
        }
    }

    string resultado;
    for (const string& b : codificado) {
        resultado += b;
    }

    return resultado;
}

void crearSudoTemporal() {
    string clave = "asasd";
    int semilla = 4;
    ofstream archivo("sudo.txt");
    archivo << encriptar(clave, semilla);
    archivo.close();
}
void administrador() {
    string claveIngresada;
    string claveGuardada;
     int semilla = 4;

    cout << "\nIngrese la clave de administrador: ";
    cin >> claveIngresada;
     crearSudoTemporal();
    // Leer clave encriptada del archivo
    ifstream archivo("sudo.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo sudo.txt\n";
        return;
    }
    getline(archivo, claveGuardada);
    archivo.close();

    // Validación (simple aquí, debes comparar con la clave encriptada)
    if (encriptar(claveIngresada,semilla) != claveGuardada) {
        cout << "Clave incorrecta.\n";
        return;
    }

    cout << "\nAcceso permitido.\n";

    // Registro de nuevo usuario
    string cedula, clave;
    int saldo;

    cout << "Ingrese cedula: ";
    cin >> cedula;
    cout << "Ingrese clave: ";
    cin >> clave;
    cout << "Ingrese saldo inicial (COP): ";
    cin >> saldo;

    ofstream usuarios("usuarios.txt", ios::app);  // Modo append
    if (!usuarios.is_open()) {
        cout << "No se pudo abrir el archivo de usuarios.\n";
        return;
    }

    usuarios << cedula << " " << encriptar(clave,semilla) << " " << saldo << endl;
    usuarios.close();

    cout << "Usuario registrado exitosamente.\n";
}

void usuario() {
    int semilla = 4;
    string cedula, clave;
    cout << "\nIngrese su cédula: ";
    cin >> cedula;
    cout << "Ingrese su clave: ";
    cin >> clave;

    // Buscar usuario
    ifstream archivo("usuarios.txt");
    ofstream temp("temp.txt");
    bool encontrado = false;
    string ced, claveArchivo;
    int saldo;

    if (!archivo.is_open() || !temp.is_open()) {
        cout << "Error al abrir archivos.\n";
        return;
    }

    while (archivo >> ced >> claveArchivo >> saldo) {
        if (ced == cedula && claveArchivo == encriptar(clave, semilla)) {
            encontrado = true;

            int opcion;
            cout << "\n1. Consultar saldo\n2. Retirar dinero\nOpción: ";
            cin >> opcion;

            saldo -= 1000; // Costo de transacción

            if (opcion == 1) {
                cout << "Su saldo es: " << saldo << " COP\n";
            } else if (opcion == 2) {
                int retiro;
                cout << "Ingrese cantidad a retirar: ";
                cin >> retiro;

                if (retiro + 1000 > saldo + 1000) {
                    cout << "Fondos insuficientes.\n";
                } else {
                    saldo -= retiro;
                    cout << "Retiro exitoso. Nuevo saldo: " << saldo << " COP\n";
                }
            }
        }
        temp << ced << " " << claveArchivo << " " << saldo << endl;
    }

    archivo.close();
    temp.close();
    remove("usuarios.txt");
    rename("temp.txt", "usuarios.txt");

    if (!encontrado)
        cout << "Usuario o clave incorrecta.\n";
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

    switch (opcion) {
    case 1:
        administrador();

        break;
    case 2:
        usuario();
        break;

    case 3:
        cout << "Vuelva pronto.\n";
        break;
    default:
        cout << "Opcion invalida. Intente de nuevo.\n";
        break;
    } while(opcion != 3);


}
