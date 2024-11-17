#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>
#include <cmath>
#include <cfloat> // Necesario para DBL_MAX

using namespace std;

// Leer entrada desde un archivo
void read_input(const string& filename, int& N, vector<vector<int>>& distances,
                vector<vector<int>>& capacities, vector<pair<int, int>>& coordinates) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        throw runtime_error("Error: No se pudo abrir el archivo.");
    }

    infile >> N;

    distances.resize(N, vector<int>(N));
    capacities.resize(N, vector<int>(N));
    coordinates.resize(N);

    // Leer matriz de distancias
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            infile >> distances[i][j];
        }
    }

    // Leer matriz de capacidades
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            infile >> capacities[i][j];
        }
    }

    // Leer coordenadas de las centrales
    string line;
    for (int i = 0; i < N; ++i) {
        infile >> line;
        line = line.substr(1, line.size() - 2); // Eliminar paréntesis
        replace(line.begin(), line.end(), ',', ' '); // Reemplazar ',' por espacio
        stringstream ss(line);
        ss >> coordinates[i].first >> coordinates[i].second;
    }

    infile.close();
}

// Calcular distancia euclidiana entre dos puntos
double euclidean_distance(pair<int, int> p1, pair<int, int> p2) {
    return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}

#endif
