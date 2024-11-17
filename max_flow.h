#ifndef MAX_FLOW_H
#define MAX_FLOW_H

#include <vector>
#include <queue>
#include <climits>

using namespace std;

// BFS para encontrar un camino aumentante
bool bfs(const vector<vector<int>>& capacity, const vector<vector<int>>& adj, vector<int>& parent, int source, int sink) {
    int n = capacity.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(source);
    visited[source] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (!visited[v] && capacity[u][v] > 0) {
                parent[v] = u;
                visited[v] = true;
                if (v == sink)
                    return true;
                q.push(v);
            }
        }
    }

    return false;
}

// Algoritmo de Ford-Fulkerson para flujo máximo
int ford_fulkerson(const vector<vector<int>>& capacities, int source, int sink) {
    int n = capacities.size();
    vector<vector<int>> capacity = capacities;
    vector<vector<int>> adj(n);

    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (capacities[u][v] > 0) {
                adj[u].push_back(v);
                adj[v].push_back(u); // Para flujo residual
            }
        }
    }

    vector<int> parent(n);
    int max_flow = 0;

    while (bfs(capacity, adj, parent, source, sink)) {
        // Encontrar el flujo mínimo en el camino aumentante
        int path_flow = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, capacity[u][v]);
        }

        // Actualizar capacidades residuales
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            capacity[u][v] -= path_flow;
            capacity[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

#endif
