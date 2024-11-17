#ifndef NEAREST_CENTRAL_H
#define NEAREST_CENTRAL_H

#include <vector>
#include <utility>
#include "utils.h" // Usar la función euclidean_distance de utils.h

using namespace std;

// Encontrar la central más cercana
pair<int, double> find_nearest_central(const pair<int, int>& new_house, const vector<pair<int, int>>& centrals) {
    int nearest_index = -1;
    double min_distance = DBL_MAX;

    for (int i = 0; i < centrals.size(); ++i) {
        double dist = euclidean_distance(new_house, centrals[i]);
        if (dist < min_distance) {
            min_distance = dist;
            nearest_index = i;
        }
    }

    return {nearest_index, min_distance};
}

#endif
