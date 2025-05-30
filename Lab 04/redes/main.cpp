#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <queue>
#include <algorithm>
#include <utility>
#include <limits>
#include <fstream>
#include <sstream>
#include <random>
#include <string>
#include <stack>
#include <stdexcept>
#include <cctype>

using namespace std;

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void press_enter_to_continue() {
    cout << "\nPresione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

class Router {
private:
    string id;
    unordered_map<string, int> configured_neighbors;
    unordered_map<string, pair<int, string>> routing_table;

public:
    Router() = default;
    explicit Router(string router_id) : id(move(router_id)) {}

    void add_configured_neighbor(const string& neighbor_id, int cost) {
        if (cost <= 0) throw invalid_argument("El costo debe ser positivo");
        if (neighbor_id == id) throw invalid_argument("No se puede conectar consigo mismo");
        configured_neighbors[neighbor_id] = cost;
    }

    void remove_configured_neighbor(const string& neighbor_id) {
        configured_neighbors.erase(neighbor_id);
    }

    void update_routing_table_entry(const string& destination, int cost, const string& next_hop) {
        if (cost < 0) throw invalid_argument("El costo no puede ser negativo");
        routing_table[destination] = make_pair(cost, next_hop);
    }

    void calculate_routing_table(const unordered_map<string, Router>& network) {
        routing_table.clear();
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;
        unordered_map<string, int> dist;
        unordered_map<string, string> prev;

        for (const auto& router : network) {
            dist[router.first] = numeric_limits<int>::max();
        }
        dist[id] = 0;
        pq.push({0, id});

        while (!pq.empty()) {
            string current = pq.top().second;
            pq.pop();

            if (network.find(current) == network.end()) continue;

            for (const auto& neighbor : network.at(current).get_configured_neighbors()) {
                string v = neighbor.first;
                int weight = neighbor.second;

                if (network.find(v) == network.end()) continue;

                if (dist[v] > dist[current] + weight) {
                    dist[v] = dist[current] + weight;
                    prev[v] = current;
                    pq.push({dist[v], v});
                }
            }
        }

        for (const auto& router : network) {
            if (router.first != id && dist[router.first] != numeric_limits<int>::max()) {
                string destination = router.first;
                string next_hop = destination;

                if (prev.find(destination) != prev.end() && prev.at(destination) != id) {
                    next_hop = prev.at(destination);
                    while (prev.find(next_hop) != prev.end() && prev.at(next_hop) != id) {
                        next_hop = prev.at(next_hop);
                    }
                }
                routing_table[destination] = {dist[destination], next_hop};
            }
        }
    }

    int get_cost_to(const string& destination) const {
        auto it = routing_table.find(destination);
        return (it != routing_table.end()) ? it->second.first : -1;
    }

    vector<string> get_path_to(const string& destination, const unordered_map<string, Router>& network) const {
        vector<string> path;
        if (routing_table.find(destination) == routing_table.end()) {
            return path;
        }

        string current = destination;
        stack<string> reverse_path;

        while (current != id) {
            reverse_path.push(current);
            if (network.find(current) == network.end() ||
                network.at(current).routing_table.find(id) == network.at(current).routing_table.end()) {
                break;
            }
            current = network.at(current).routing_table.at(id).second;
        }
        reverse_path.push(id);

        while (!reverse_path.empty()) {
            path.push_back(reverse_path.top());
            reverse_path.pop();
        }

        return path;
    }

    void print_routing_table() const {
        cout << "Tabla de enrutamiento para " << id << ":\n";
        cout << "Destino\tCosto\tSiguiente salto\n";
        for (const auto& entry : routing_table) {
            cout << entry.first << "\t" << entry.second.first << "\t" << entry.second.second << "\n";
        }
    }

    void print_configured_connections() const {
        cout << "Conexiones configuradas para " << id << ":\n";
        cout << "Vecino\tCosto\n";
        for (const auto& neighbor : configured_neighbors) {
            cout << neighbor.first << "\t" << neighbor.second << "\n";
        }
    }

    string get_id() const { return id; }
    const unordered_map<string, int>& get_configured_neighbors() const { return configured_neighbors; }
    const unordered_map<string, pair<int, string>>& get_routing_table() const { return routing_table; }
};

class Network {
private:
    unordered_map<string, Router> routers;

public:
    void add_router(const Router& router) {
        string id = router.get_id();
        if (routers.find(id) != routers.end()) {
            throw invalid_argument("El enrutador '" + id + "' ya existe");
        }
        routers[id] = router;
        update_all_routing_tables();
    }

    void remove_router(const string& router_id) {
        if (routers.find(router_id) == routers.end()) {
            throw invalid_argument("El enrutador '" + router_id + "' no existe");
        }
        routers.erase(router_id);
        for (auto& router : routers) {
            router.second.remove_configured_neighbor(router_id);
        }
        update_all_routing_tables();
    }

    void add_connection(const string& router1_id, const string& router2_id, int cost) {
        if (cost <= 0) throw invalid_argument("El costo debe ser positivo");
        if (router1_id == router2_id) throw invalid_argument("No se puede conectar un router consigo mismo");
        if (routers.find(router1_id) == routers.end() || routers.find(router2_id) == routers.end()) {
            throw invalid_argument("Uno o ambos enrutadores no existen");
        }

        routers[router1_id].add_configured_neighbor(router2_id, cost);
        routers[router2_id].add_configured_neighbor(router1_id, cost);
        update_all_routing_tables();
    }

    void remove_connection(const string& router1_id, const string& router2_id) {
        if (routers.find(router1_id) == routers.end() || routers.find(router2_id) == routers.end()) {
            throw invalid_argument("Uno o ambos enrutadores no existen");
        }
        routers[router1_id].remove_configured_neighbor(router2_id);
        routers[router2_id].remove_configured_neighbor(router1_id);
        update_all_routing_tables();
    }

    void update_all_routing_tables() {
        for (auto& router : routers) {
            router.second.calculate_routing_table(routers);
        }
    }

    void load_config_from_file(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("No se pudo abrir el archivo: " + filename);
        }

        routers.clear();
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string command;
            iss >> command;

            if (command == "router") {
                string router_id;
                if (iss >> router_id) {
                    routers[router_id] = Router(router_id);
                }
            }
            else if (command == "connection") {
                string router1, router2;
                int cost;
                if (iss >> router1 >> router2 >> cost) {
                    if (routers.find(router1) == routers.end()) {
                        routers[router1] = Router(router1);
                    }
                    if (routers.find(router2) == routers.end()) {
                        routers[router2] = Router(router2);
                    }
                    add_connection(router1, router2, cost);
                }
            }
        }
        file.close();
    }

    void save_config_to_file(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("No se pudo crear el archivo: " + filename);
        }

        for (const auto& router : routers) {
            file << "router " << router.first << "\n";
        }

        set<pair<string, string>> saved_connections;
        for (const auto& router : routers) {
            for (const auto& neighbor : router.second.get_configured_neighbors()) {
                string router1 = router.first;
                string router2 = neighbor.first;

                if (router1 > router2) swap(router1, router2);

                if (saved_connections.find({router1, router2}) == saved_connections.end()) {
                    file << "connection " << router1 << " " << router2 << " " << neighbor.second << "\n";
                    saved_connections.insert({router1, router2});
                }
            }
        }

        file.close();
    }

    void save_routing_tables_to_file(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("No se pudo crear el archivo: " + filename);
        }

        for (const auto& router : routers) {
            const auto& routing_table = router.second.get_routing_table();
            for (const auto& entry : routing_table) {
                file << "route " << router.first << " " << entry.first << " "
                     << entry.second.first << " " << entry.second.second << "\n";
            }
        }

        file.close();
    }

    void load_routing_tables_from_file(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("No se pudo abrir el archivo: " + filename);
        }

        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string command;
            iss >> command;

            if (command == "route") {
                string source, dest, next_hop;
                int cost;
                if (iss >> source >> dest >> cost >> next_hop) {
                    if (routers.find(source) != routers.end()) {
                        routers[source].update_routing_table_entry(dest, cost, next_hop);
                    }
                }
            }
        }
        file.close();
    }

    void generate_random_network(int num_routers, double connection_probability, int max_cost = 10) {
        if (num_routers <= 0) throw invalid_argument("Número de enrutadores debe ser positivo");
        if (connection_probability < 0 || connection_probability > 1) {
            throw invalid_argument("Probabilidad debe estar entre 0 y 1");
        }

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> cost_dist(1, max_cost);
        bernoulli_distribution conn_dist(connection_probability);

        routers.clear();

        for (int i = 0; i < num_routers; ++i) {
            string router_id = "R" + to_string(i + 1);
            routers[router_id] = Router(router_id);
        }

        vector<string> router_ids;
        for (const auto& router : routers) {
            router_ids.push_back(router.first);
        }

        for (size_t i = 0; i < router_ids.size(); ++i) {
            for (size_t j = i + 1; j < router_ids.size(); ++j) {
                if (conn_dist(gen)) {
                    int cost = cost_dist(gen);
                    add_connection(router_ids[i], router_ids[j], cost);
                }
            }
        }
    }

    int get_packet_cost(const string& source, const string& destination) const {
        if (routers.find(source) == routers.end() || routers.find(destination) == routers.end()) {
            throw invalid_argument("Uno o ambos enrutadores no existen");
        }
        return routers.at(source).get_cost_to(destination);
    }

    vector<string> get_packet_path(const string& source, const string& destination) const {
        if (routers.find(source) == routers.end() || routers.find(destination) == routers.end()) {
            throw invalid_argument("Uno o ambos enrutadores no existen");
        }
        return routers.at(source).get_path_to(destination, routers);
    }

    void print_network_info() const {
        cout << "Red con " << routers.size() << " enrutadores:\n";
        for (const auto& router : routers) {
            cout << router.first << " (" << router.second.get_configured_neighbors().size() << " conexiones)\n";
        }
    }

    void print_all_routing_tables() const {
        for (const auto& router : routers) {
            router.second.print_routing_table();
            cout << "------------------------\n";
        }
    }

    void print_all_configured_connections() const {
        for (const auto& router : routers) {
            router.second.print_configured_connections();
            cout << "------------------------\n";
        }
    }
};

void interactive_menu() {
    Network network;
    int choice = -1;

    while (true) {
        clear_screen();
        cout << "\n=== Simulador de Red de Enrutadores ===\n";
        cout << "1. Cargar configuracion de red\n";
        cout << "2. Guardar configuracion de red\n";
        cout << "3. Cargar tablas de enrutamiento\n";
        cout << "4. Guardar tablas de enrutamiento\n";
        cout << "5. Generar red aleatoria\n";
        cout << "6. Agregar enrutador\n";
        cout << "7. Eliminar enrutador\n";
        cout << "8. Agregar conexion\n";
        cout << "9. Eliminar conexion\n";
        cout << "10. Calcular costo de envio\n";
        cout << "11. Mostrar ruta optima\n";
        cout << "12. Mostrar informacion de la red\n";
        cout << "13. Mostrar todas las tablas de enrutamiento\n";
        cout << "14. Mostrar conexiones configuradas\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada inválida. Intente nuevamente.\n";
            press_enter_to_continue();
            continue;
        }

        try {
            switch (choice) {
            case 1: {
                string filename;
                cout << "Nombre del archivo de configuracion: ";
                cin >> filename;
                network.load_config_from_file(filename);
                cout << "Configuración cargada exitosamente.\n";
                break;
            }
            case 2: {
                string filename;
                cout << "Nombre del archivo para guardar configuracion: ";
                cin >> filename;
                network.save_config_to_file(filename);
                cout << "Configuración guardada exitosamente.\n";
                break;
            }
            case 3: {
                string filename;
                cout << "Nombre del archivo de tablas de enrutamiento: ";
                cin >> filename;
                network.load_routing_tables_from_file(filename);
                cout << "Tablas de enrutamiento cargadas.\n";
                break;
            }
            case 4: {
                string filename;
                cout << "Nombre del archivo para guardar tablas: ";
                cin >> filename;
                network.save_routing_tables_to_file(filename);
                cout << "Tablas de enrutamiento guardadas.\n";
                break;
            }
            case 5: {
                int num_routers;
                double prob;
                cout << "Numero de enrutadores: ";
                cin >> num_routers;
                cout << "Probabilidad de conexión (0-1): ";
                cin >> prob;
                network.generate_random_network(num_routers, prob);
                cout << "Red aleatoria generada con " << num_routers << " enrutadores.\n";
                break;
            }
            case 6: {
                string id;
                cout << "ID del nuevo enrutador: ";
                cin >> id;
                network.add_router(Router(id));
                cout << "Enrutador '" << id << "' agregado.\n";
                break;
            }
            case 7: {
                string id;
                cout << "ID del enrutador a eliminar: ";
                cin >> id;
                network.remove_router(id);
                cout << "Enrutador '" << id << "' eliminado.\n";
                break;
            }
            case 8: {
                string id1, id2;
                int cost;
                cout << "ID del primer enrutador: ";
                cin >> id1;
                cout << "ID del segundo enrutador: ";
                cin >> id2;
                cout << "Costo de la conexion: ";
                cin >> cost;
                network.add_connection(id1, id2, cost);
                cout << "Conexión entre '" << id1 << "' y '" << id2 << "' agregada.\n";
                break;
            }
            case 9: {
                string id1, id2;
                cout << "ID del primer enrutador: ";
                cin >> id1;
                cout << "ID del segundo enrutador: ";
                cin >> id2;
                network.remove_connection(id1, id2);
                cout << "Conexión entre '" << id1 << "' y '" << id2 << "' eliminada.\n";
                break;
            }
            case 10: {
                string source, dest;
                cout << "ID del enrutador origen: ";
                cin >> source;
                cout << "ID del enrutador destino: ";
                cin >> dest;
                int cost = network.get_packet_cost(source, dest);
                if (cost == -1) {
                    cout << "No existe ruta entre '" << source << "' y '" << dest << "'.\n";
                } else {
                    cout << "Costo total: " << cost << endl;
                }
                break;
            }
            case 11: {
                string source, dest;
                cout << "ID del enrutador origen: ";
                cin >> source;
                cout << "ID del enrutador destino: ";
                cin >> dest;
                vector<string> path = network.get_packet_path(source, dest);
                if (path.empty()) {
                    cout << "No existe ruta entre '" << source << "' y '" << dest << "'.\n";
                } else {
                    cout << "Ruta óptima: ";
                    for (size_t i = 0; i < path.size(); ++i) {
                        if (i != 0) cout << " -> ";
                        cout << path[i];
                    }
                    cout << endl;
                }
                break;
            }
            case 12:
                network.print_network_info();
                break;
            case 13:
                network.print_all_routing_tables();
                break;
            case 14:
                network.print_all_configured_connections();
                break;
            case 0:
                cout << "Saliendo del programa...\n";
                return;
            default:
                cout << "Opción no válida.\n";
            }
        } catch (const exception& e) {
            cerr << "\nError: " << e.what() << "\n";
        }

        press_enter_to_continue();
    }
}

int main() {
    try {
        interactive_menu();
    } catch (const exception& e) {
        cerr << "Error crítico: " << e.what() << endl;
        return 1;
    }
    return 0;
}
