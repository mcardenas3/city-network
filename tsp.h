#ifndef TSP_H
#define TSP_H

#include <vector>
#include <cmath>
#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

// Resolver el TSP usando Held-Karp (Programación Dinámica)
pair<int, vector<int>> solve_tsp(const vector<vector<int>>& distances) {
    int N = distances.size();
    int VISITED_ALL = (1 << N) - 1; // Todas las ciudades visitadas

    // Inicializar la tabla DP y la matriz para reconstruir el camino
    vector<vector<int>> dp(1 << N, vector<int>(N, INT_MAX));
    vector<vector<int>> parent(1 << N, vector<int>(N, -1));

    // Caso base: desde la ciudad inicial (0) hacia cualquier otra
    dp[1][0] = 0;

    // Llenar la tabla DP
    for (int mask = 1; mask < (1 << N); ++mask) {
        for (int u = 0; u < N; ++u) {
            if (mask & (1 << u)) { // Si la ciudad "u" está en el subconjunto
                for (int v = 0; v < N; ++v) {
                    if ((mask & (1 << v)) == 0) { // Si "v" no está en el subconjunto
                        int next_mask = mask | (1 << v);
                        int new_dist = dp[mask][u] + distances[u][v];
                        if (dp[mask][u] != INT_MAX && new_dist < dp[next_mask][v]) {
                            dp[next_mask][v] = new_dist;
                            parent[next_mask][v] = u;
                        }
                    }
                }
            }
        }
    }

    // Encontrar la distancia mínima para regresar al punto de inicio (0)
    int min_cost = INT_MAX;
    int last_city = -1;
    for (int i = 1; i < N; ++i) {
        if (dp[VISITED_ALL][i] != INT_MAX && distances[i][0] != INT_MAX) {
            int cost = dp[VISITED_ALL][i] + distances[i][0];
            if (cost < min_cost) {
                min_cost = cost;
                last_city = i;
            }
        }
    }

    // Reconstruir la ruta
    vector<int> path;
    int mask = VISITED_ALL;
    int curr_city = last_city;

    // Reconstruir el camino desde la última ciudad hasta la inicial
    while (curr_city != -1) {
        path.push_back(curr_city);
        int temp = curr_city;
        curr_city = parent[mask][curr_city];
        mask ^= (1 << temp);
    }

    // Asegurarse de regresar al inicio
    if (path.back() != 0) {
        path.push_back(0);
    }

    reverse(path.begin(), path.end());

    return {min_cost, path};
}

#endif
