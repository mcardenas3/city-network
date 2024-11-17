#include <iostream>
#include <vector>
#include "graph.h"
#include "utils.h"
#include "tsp.h"
#include "max_flow.h"
#include "nearest_central.h"

using namespace std;

int main() {
    int N;
    vector<vector<int>> distances;
    vector<vector<int>> capacities;
    vector<pair<int, int>> coordinates;

    // Leer entrada desde el archivo
    try {
        read_input("input.txt", N, distances, capacities, coordinates);
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }

    // Resolver el MST usando Kruskal
    vector<Edge> edges;
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (distances[i][j] > 0) {
                edges.push_back({i, j, distances[i][j]});
            }
        }
    }
    int total_weight = 0;
    vector<Edge> mst_edges = kruskal(N, edges, total_weight);

    // Mostrar resultados del MST
    cout << "Forma de cablear las colonias con fibra:\n";
    for (Edge e : mst_edges) {
        cout << "(" << char('A' + e.u) << "," << char('A' + e.v) << ")\n";
    }
    cout << "Costo total del cableado: " << total_weight << endl;

    // Resolver el TSP
    auto [min_cost, path] = solve_tsp(distances);

    // Mostrar resultados del TSP
    cout << "\nRuta más corta para repartir correspondencia:\n";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << char('A' + path[i]);
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << "\nCosto total de la ruta: " << min_cost << endl;

    // Resolver el flujo máximo
    int source = 0; // Nodo inicial
    int sink = N - 1; // Nodo final
    int max_flow = ford_fulkerson(capacities, source, sink);
    cout << "\nFlujo máximo de información entre nodos " << char('A' + source)
         << " y " << char('A' + sink) << ": " << max_flow << endl;

    // Encontrar la central más cercana
    pair<int, int> new_house = {400, 300}; // Ejemplo de coordenadas para una nueva casa
    auto [nearest_index, distance] = find_nearest_central(new_house, coordinates);
    cout << "\nCentral más cercana a la casa en (" << new_house.first << ", " << new_house.second
         << ") es la central " << nearest_index + 1 << " a una distancia de " << distance << " unidades." << endl;

    return 0;
}
