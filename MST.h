#ifndef MST_H
#define MST_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>

// Estructura para representar una arista
struct Edge {
    int u, v, weight;
};

// Encuentra el representante de un conjunto (Union-Find)
int find_set(int v, std::vector<int>& parent) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v], parent); // Path compression
}

// Une dos conjuntos (Union-Find)
void union_sets(int a, int b, std::vector<int>& parent, std::vector<int>& rank) {
    a = find_set(a, parent);
    b = find_set(b, parent);
    if (a != b) {
        if (rank[a] < rank[b])
            std::swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;
    }
}

// Algoritmo de Kruskal para el MST
std::vector<Edge> kruskal(int vertices, std::vector<Edge>& edges, int& total_weight) {
    std::sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    std::vector<int> parent(vertices);
    std::vector<int> rank(vertices, 0);
    for (int i = 0; i < vertices; i++) {
        parent[i] = i;
    }

    std::vector<Edge> mst_edges;
    total_weight = 0;

    for (Edge e : edges) {
        if (find_set(e.u, parent) != find_set(e.v, parent)) {
            union_sets(e.u, e.v, parent, rank);
            mst_edges.push_back(e);
            total_weight += e.weight;
        }
    }

    return mst_edges;
}


#endif
